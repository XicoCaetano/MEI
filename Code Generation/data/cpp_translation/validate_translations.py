"""
Validação das traduções C++ (Linux / g++)
==========================================

Para cada um dos 30 ficheiros .cpp traduzidos, este script:
  1. Compila com g++ (-std=c++17)
  2. Executa o binário
  3. Verifica se todos os asserts passam (output "All tests passed")
  4. Regista o resultado num log estruturado

Pré-requisitos:
  - g++ instalado (verificar com `g++ --version`)
  - Ter os ficheiros .cpp em ./translations/{task_id}.cpp
  - Ter o sample_30_problems.jsonl na pasta actual

Output:
  - validation_results.json : log estruturado por task_id
  - validation_summary.md   : sumário human-readable

Uso:
    python3 validate_translations.py
"""

import json
import subprocess
import sys
from pathlib import Path

# ---------- Configuração ----------
TRANSLATIONS_DIR = Path("translations")
JSONL_PATH = Path("sample_30_problems.jsonl")
COMPILE_TIMEOUT = 60
RUN_TIMEOUT = 30


def check_gpp_available():
    try:
        r = subprocess.run(["g++", "--version"], capture_output=True,
                           text=True, timeout=10)
        return r.returncode == 0
    except (FileNotFoundError, subprocess.TimeoutExpired):
        return False


def compile_cpp(cpp_path: Path, exe_path: Path) -> tuple[bool, str]:
    cmd = ["g++", "-std=c++17", "-O2", "-Wall",
           "-o", str(exe_path), str(cpp_path)]
    try:
        r = subprocess.run(cmd, capture_output=True, text=True,
                           timeout=COMPILE_TIMEOUT)
        if r.returncode == 0:
            return True, ""
        return False, (r.stderr or r.stdout)[:2000]
    except subprocess.TimeoutExpired:
        return False, f"Compile timeout (>{COMPILE_TIMEOUT}s)"
    except Exception as e:
        return False, f"Compile exception: {type(e).__name__}: {e}"


def run_executable(exe_path: Path) -> tuple[str, str]:
    try:
        r = subprocess.run([str(exe_path)], capture_output=True,
                           text=True, timeout=RUN_TIMEOUT)
        if r.returncode == 0 and "All tests passed" in r.stdout:
            return "SUCCESS", ""
        if r.returncode == 0:
            return "FAIL", f"Sem 'All tests passed'. stdout: {r.stdout[:500]}"
        stderr_short = r.stderr[:1000] if r.stderr else ""
        stdout_short = r.stdout[:500] if r.stdout else ""
        # Em Linux, asserts falhados produzem SIGABRT (returncode -6 ou 134)
        if r.returncode in (-6, 134) or "Assertion" in stderr_short:
            return "FAIL", f"Assertion failed. stdout: {stdout_short} | stderr: {stderr_short}"
        return "RUNTIME_ERROR", f"Exit {r.returncode}. stdout: {stdout_short} | stderr: {stderr_short}"
    except subprocess.TimeoutExpired:
        return "TIMEOUT", f">{RUN_TIMEOUT}s"
    except Exception as e:
        return "RUNTIME_ERROR", f"{type(e).__name__}: {e}"


def main():
    if not check_gpp_available():
        print("[ERRO] g++ não foi encontrado.")
        print("Instala com: sudo apt install g++")
        sys.exit(1)

    if not TRANSLATIONS_DIR.exists():
        print(f"[ERRO] Pasta {TRANSLATIONS_DIR} não existe.")
        sys.exit(1)

    if not JSONL_PATH.exists():
        print(f"[ERRO] Ficheiro {JSONL_PATH} não existe.")
        sys.exit(1)

    expected = []
    with open(JSONL_PATH, "r", encoding="utf-8") as f:
        for line in f:
            p = json.loads(line)
            expected.append({"task_id": p["task_id"],
                             "difficulty": p["difficulty"]})
    print(f"Esperados {len(expected)} problemas a validar.\n")

    results = []
    for i, p in enumerate(expected, 1):
        task_id = p["task_id"]
        difficulty = p["difficulty"]
        cpp_path = TRANSLATIONS_DIR / f"{task_id}.cpp"
        exe_path = TRANSLATIONS_DIR / task_id

        print(f"[{i:2d}/{len(expected)}] {difficulty:6s} | {task_id} ... ",
              end="", flush=True)

        if not cpp_path.exists():
            print("MISSING")
            results.append({"task_id": task_id, "difficulty": difficulty,
                            "status": "MISSING_FILE", "compile_error": "",
                            "run_error": f"{cpp_path} não existe"})
            continue

        compile_ok, compile_msg = compile_cpp(cpp_path, exe_path)
        if not compile_ok:
            print("COMPILE_ERROR")
            results.append({"task_id": task_id, "difficulty": difficulty,
                            "status": "COMPILE_ERROR",
                            "compile_error": compile_msg, "run_error": ""})
            continue

        run_status, run_msg = run_executable(exe_path)
        print(run_status)
        results.append({"task_id": task_id, "difficulty": difficulty,
                        "status": run_status, "compile_error": "",
                        "run_error": run_msg})

    with open("validation_results.json", "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=2)
    print("\n[OK] validation_results.json")

    success = [r for r in results if r["status"] == "SUCCESS"]
    failed = [r for r in results if r["status"] != "SUCCESS"]

    with open("validation_summary.md", "w", encoding="utf-8") as f:
        f.write("# Sumário de Validação das Traduções C++\n\n")
        f.write(f"- Total: {len(results)}\n")
        f.write(f"- SUCCESS: {len(success)}\n")
        f.write(f"- FAILED: {len(failed)}\n\n")
        if failed:
            f.write("## Problemas com falha\n\n")
            for r in failed:
                f.write(f"### {r['task_id']} ({r['difficulty']}) — {r['status']}\n\n")
                if r["compile_error"]:
                    f.write("**Erro de compilação:**\n```\n"
                            f"{r['compile_error']}\n```\n\n")
                if r["run_error"]:
                    f.write("**Erro em runtime:**\n```\n"
                            f"{r['run_error']}\n```\n\n")
        f.write("## Resultados por dificuldade\n\n")
        for dif in ["Easy", "Medium", "Hard"]:
            ds = [r for r in results if r["difficulty"] == dif]
            ok = [r for r in ds if r["status"] == "SUCCESS"]
            f.write(f"- **{dif}**: {len(ok)}/{len(ds)} OK\n")

    print("[OK] validation_summary.md")
    print(f"\nResultado: {len(success)}/{len(results)} traduções validadas.")


if __name__ == "__main__":
    main()