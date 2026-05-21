"""
Pipeline de Avaliação C++ — Code Generation (Linux / g++)
==========================================================

Avalia as 90 respostas dos modelos (3 modelos × 30 problemas) em C++.

Para cada par (modelo, problema):
  1. Lê o código C++ da resposta do modelo
  2. Constrói um .cpp combinado (resposta do modelo + main com asserts)
  3. Compila com g++ (-std=c++17)
  4. Executa com timeout
  5. Classifica em PASS / FAIL / SYNTAX_ERROR / RUNTIME_ERROR / TIMEOUT

Pré-requisitos:
  - g++ instalado
  - ./translations/{task_id}.cpp (saídas do agente, validadas pelo
    validate_translations.py)
  - ./responses_cpp/{modelo}/{difficulty}/{task_id}.cpp (respostas dos modelos)

Output:
  - results_cpp.csv          : matriz com status por par
  - results_cpp.json         : log detalhado
  - results_cpp_summary.md   : Pass@1 e distribuição por categoria

Uso:
    python3 evaluate_cpp.py
"""

import json
import subprocess
import re
import sys
import csv
from pathlib import Path

# ---------- Configuração ----------
# Caminhos relativos à raiz do projeto (script deve ser corrido de lá)
TRANSLATIONS_DIR = Path("data/cpp_translation/translations")
RESPONSES_DIR = Path("responses/cpp")
JSONL_PATH = Path("data/cpp_translation/sample_30_problems.jsonl")
RESULTS_DIR = Path("results/cpp")
WORK_DIR = RESULTS_DIR / "eval_work"
MODELS = ["claude", "gemini", "deepseek"]
COMPILE_TIMEOUT = 60
RUN_TIMEOUT = 30


def check_gpp_available():
    try:
        r = subprocess.run(["g++", "--version"], capture_output=True,
                           text=True, timeout=10)
        return r.returncode == 0
    except (FileNotFoundError, subprocess.TimeoutExpired):
        return False


def extract_main_with_asserts(translation_cpp: str) -> str:
    """Extrai o `int main()` (asserts + return) da tradução validada."""
    match = re.search(r"int\s+main\s*\([^)]*\)\s*\{", translation_cpp)
    if not match:
        return ""
    return translation_cpp[match.start():]


def extract_helpers_and_includes(translation_cpp: str) -> str:
    """Extrai includes + helpers (struct ListNode etc.) até `class Solution`."""
    match = re.search(r"class\s+Solution", translation_cpp)
    if not match:
        return translation_cpp
    return translation_cpp[:match.start()]


def build_combined_cpp(model_response: str, translation: str) -> str:
    """Combina includes/helpers + resposta do modelo + main()."""
    helpers = extract_helpers_and_includes(translation)
    main_block = extract_main_with_asserts(translation)
    return (f"{helpers}\n"
            f"// === MODEL RESPONSE ===\n{model_response}\n\n"
            f"// === TEST HARNESS ===\n{main_block}")


def compile_cpp(cpp_path: Path, exe_path: Path) -> tuple[str, str]:
    cmd = ["g++", "-std=c++17", "-O2",
           "-o", str(exe_path), str(cpp_path)]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True,
                           timeout=COMPILE_TIMEOUT)
        if r.returncode == 0:
            return "OK", ""
        return "SYNTAX_ERROR", (r.stderr or r.stdout)[:2000]
    except subprocess.TimeoutExpired:
        return "SYNTAX_ERROR", f"Compile timeout (>{COMPILE_TIMEOUT}s)"


def run_exe(exe_path: Path) -> tuple[str, str]:
    try:
        r = subprocess.run([str(exe_path)], capture_output=True,
                           text=True, timeout=RUN_TIMEOUT)
        if r.returncode == 0 and "All tests passed" in r.stdout:
            return "PASS", ""
        if r.returncode == 0:
            return "FAIL", f"Sem 'All tests passed'. stdout: {r.stdout[:500]}"
        stderr = (r.stderr or "")[:800]
        stdout = (r.stdout or "")[:400]
        # SIGABRT (-6 ou 134) tipicamente vem de asserts
        if r.returncode in (-6, 134) or "Assertion" in stderr:
            return "FAIL", f"Assertion failed. stdout: {stdout} | stderr: {stderr}"
        return "RUNTIME_ERROR", f"Exit {r.returncode}. stdout: {stdout} | stderr: {stderr}"
    except subprocess.TimeoutExpired:
        return "TIMEOUT", f">{RUN_TIMEOUT}s"


def main():
    if not check_gpp_available():
        print("[ERRO] g++ não está disponível. sudo apt install g++")
        sys.exit(1)

    for required in [TRANSLATIONS_DIR, RESPONSES_DIR, JSONL_PATH]:
        if not Path(required).exists():
            print(f"[ERRO] Falta {required}")
            sys.exit(1)

    RESULTS_DIR.mkdir(parents=True, exist_ok=True)
    WORK_DIR.mkdir(parents=True, exist_ok=True)

    problems = []
    with open(JSONL_PATH, "r", encoding="utf-8") as f:
        for line in f:
            p = json.loads(line)
            problems.append({
                "task_id": p["task_id"],
                "difficulty": p["difficulty"].lower(),
            })

    print(f"A avaliar {len(problems)} × {len(MODELS)} = "
          f"{len(problems) * len(MODELS)} execuções\n")

    results = []
    total = len(problems) * len(MODELS)
    counter = 0

    for problem in problems:
        task_id = problem["task_id"]
        difficulty = problem["difficulty"]

        translation_path = TRANSLATIONS_DIR / f"{task_id}.cpp"
        if not translation_path.exists():
            print(f"[AVISO] Tradução {translation_path} não existe — "
                  f"todos os modelos para este problema são MISSING")
            for m in MODELS:
                results.append({"task_id": task_id, "difficulty": difficulty,
                                "model": m, "status": "MISSING_TRANSLATION",
                                "details": ""})
                counter += 1
            continue

        translation_cpp = translation_path.read_text(encoding="utf-8")

        for model in MODELS:
            counter += 1
            response_path = (RESPONSES_DIR / model / difficulty /
                             f"{task_id}.cpp")
            print(f"[{counter:3d}/{total}] {model:9s} | {difficulty:6s} | "
                  f"{task_id} ... ", end="", flush=True)

            if not response_path.exists():
                print("MISSING")
                results.append({"task_id": task_id, "difficulty": difficulty,
                                "model": model, "status": "MISSING_FILE",
                                "details": str(response_path)})
                continue

            model_response = response_path.read_text(encoding="utf-8")
            combined = build_combined_cpp(model_response, translation_cpp)
            combined_path = WORK_DIR / f"{model}_{difficulty}_{task_id}.cpp"
            exe_path = WORK_DIR / f"{model}_{difficulty}_{task_id}"
            combined_path.write_text(combined, encoding="utf-8")

            compile_status, compile_msg = compile_cpp(combined_path, exe_path)
            if compile_status != "OK":
                print("SYNTAX_ERROR")
                results.append({"task_id": task_id, "difficulty": difficulty,
                                "model": model, "status": "SYNTAX_ERROR",
                                "details": compile_msg})
                continue

            run_status, run_msg = run_exe(exe_path)
            print(run_status)
            results.append({"task_id": task_id, "difficulty": difficulty,
                            "model": model, "status": run_status,
                            "details": run_msg})

    # CSV
    with open(RESULTS_DIR / "results_cpp.csv", "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["task_id", "difficulty"] + MODELS)
        for problem in problems:
            row = [problem["task_id"], problem["difficulty"]]
            for m in MODELS:
                r = next((x for x in results if x["task_id"] == problem["task_id"]
                          and x["model"] == m), None)
                row.append(r["status"] if r else "MISSING")
            w.writerow(row)
    print(f"\n[OK] {RESULTS_DIR / 'results_cpp.csv'}")

    # JSON
    with open(RESULTS_DIR / "results_cpp.json", "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=2)
    print(f"[OK] {RESULTS_DIR / 'results_cpp.json'}")

    # Sumário
    with open(RESULTS_DIR / "results_cpp_summary.md", "w", encoding="utf-8") as f:
        f.write("# Resultados da Avaliação C++\n\n")
        f.write("## Pass@1 por modelo\n\n")
        f.write("| Modelo | Total PASS | Pass@1 |\n|---|---|---|\n")
        for m in MODELS:
            mr = [r for r in results if r["model"] == m]
            passes = sum(1 for r in mr if r["status"] == "PASS")
            p1 = passes / len(mr) if mr else 0
            f.write(f"| {m.capitalize()} | {passes}/{len(mr)} | {p1:.2%} |\n")

        f.write("\n## Pass@1 por modelo e dificuldade\n\n")
        f.write("| Modelo | Easy | Medium | Hard |\n|---|---|---|---|\n")
        for m in MODELS:
            row = [m.capitalize()]
            for dif in ["easy", "medium", "hard"]:
                rs = [r for r in results if r["model"] == m
                      and r["difficulty"] == dif]
                p = sum(1 for r in rs if r["status"] == "PASS")
                row.append(f"{p}/{len(rs)}" if rs else "0/0")
            f.write("| " + " | ".join(row) + " |\n")

        f.write("\n## Distribuição de categorias\n\n")
        f.write("| Modelo | PASS | FAIL | SYNTAX_ERROR | RUNTIME_ERROR | TIMEOUT |\n")
        f.write("|---|---|---|---|---|---|\n")
        for m in MODELS:
            rs = [r for r in results if r["model"] == m]
            counts = {s: sum(1 for r in rs if r["status"] == s)
                      for s in ["PASS", "FAIL", "SYNTAX_ERROR",
                                "RUNTIME_ERROR", "TIMEOUT"]}
            f.write(f"| {m.capitalize()} | " +
                    " | ".join(str(counts[s]) for s in
                               ["PASS", "FAIL", "SYNTAX_ERROR",
                                "RUNTIME_ERROR", "TIMEOUT"]) + " |\n")
    print(f"[OK] {RESULTS_DIR / 'results_cpp_summary.md'}")
    print("\nAvaliação concluída.")


if __name__ == "__main__":
    main()