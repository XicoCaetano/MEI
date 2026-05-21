"""
Pipeline de Avaliação Python — Code Generation (Linux)
=======================================================

Avalia as 90 respostas dos modelos (3 modelos × 30 problemas) em Python.

Para cada par (modelo, problema):
  1. Lê a resposta Python do modelo (class Solution)
  2. Constrói um harness Python combinado:
       - Imports gerais (do campo `prompt` do dataset)
       - Resposta do modelo (class Solution com a sua implementação)
       - Função `check(candidate)` (do campo `test` do dataset)
       - Linha de invocação (do campo `entry_point`)
  3. Executa num subprocesso Python isolado, com timeout
  4. Classifica em PASS / FAIL / SYNTAX_ERROR / RUNTIME_ERROR / TIMEOUT

Pré-requisitos:
  - python3 instalado
  - ./responses/{modelo}/{difficulty}/{task_id}.py
  - ./sample_30_problems.jsonl

Output:
  - results_python.csv          : matriz com status por par
  - results_python.json         : log detalhado
  - results_python_summary.md   : Pass@1 e distribuição por categoria

Uso:
    python3 evaluate_python.py
"""

import json
import subprocess
import sys
import csv
from pathlib import Path

# ---------- Configuração ----------
# Caminhos relativos à raiz do projeto (script deve ser corrido de lá)
RESPONSES_DIR = Path("responses/python")
JSONL_PATH = Path("data/cpp_translation/sample_30_problems.jsonl")
RESULTS_DIR = Path("results/python")
WORK_DIR = RESULTS_DIR / "eval_work"
MODELS = ["claude", "gemini", "deepseek"]
RUN_TIMEOUT = 30


def build_harness(model_response: str, problem: dict) -> str:
    """
    Constrói o harness Python que será executado num subprocesso:
      1. Imports gerais (campo `prompt` do dataset)
      2. Resposta do modelo (class Solution)
      3. Função check (campo `test`)
      4. Invocação (chama check com entry_point)
    """
    imports_block = problem.get("prompt", "")
    test_block = problem["test"]
    entry_point = problem["entry_point"]  # ex: 'Solution().minCosts'

    return f"""# === IMPORTS GERAIS (do dataset) ===
{imports_block}

# === MODEL RESPONSE ===
{model_response}

# === TEST FUNCTION (do dataset) ===
{test_block}

# === INVOCATION ===
check({entry_point})
print("All tests passed")
"""


def classify_run(returncode: int, stdout: str, stderr: str) -> tuple[str, str]:
    """
    Classifica o resultado da execução Python.
    Devolve (status, mensagem).
    """
    # PASS: terminou OK e imprimiu "All tests passed"
    if returncode == 0 and "All tests passed" in stdout:
        return "PASS", ""

    # Imprimiu OK mas sem mensagem (estranho mas pode acontecer)
    if returncode == 0:
        return "FAIL", f"Sem 'All tests passed'. stdout: {stdout[:500]}"

    # Códigos != 0: distinguir entre tipos de erro pelo conteúdo do stderr
    stderr_short = stderr[:1500] if stderr else ""
    stdout_short = stdout[:300] if stdout else ""

    # SyntaxError ou IndentationError → SYNTAX_ERROR
    if "SyntaxError" in stderr_short or "IndentationError" in stderr_short:
        return "SYNTAX_ERROR", stderr_short

    # AssertionError → FAIL (algum assert da test suite falhou)
    if "AssertionError" in stderr_short:
        return "FAIL", stderr_short

    # Outras excepções → RUNTIME_ERROR
    return "RUNTIME_ERROR", f"Exit {returncode}. stderr: {stderr_short}"


def run_harness(harness_path: Path) -> tuple[str, str]:
    """Executa um ficheiro harness e devolve (status, mensagem)."""
    try:
        r = subprocess.run(
            ["python3", str(harness_path)],
            capture_output=True,
            text=True,
            timeout=RUN_TIMEOUT,
        )
        return classify_run(r.returncode, r.stdout, r.stderr)
    except subprocess.TimeoutExpired:
        return "TIMEOUT", f">{RUN_TIMEOUT}s"
    except Exception as e:
        return "RUNTIME_ERROR", f"Subprocess exception: {type(e).__name__}: {e}"


def main():
    # 1. Verificações
    if not RESPONSES_DIR.exists():
        print(f"[ERRO] Pasta {RESPONSES_DIR} não existe.")
        sys.exit(1)

    if not JSONL_PATH.exists():
        print(f"[ERRO] {JSONL_PATH} não existe.")
        sys.exit(1)

    RESULTS_DIR.mkdir(parents=True, exist_ok=True)
    WORK_DIR.mkdir(parents=True, exist_ok=True)

    # 2. Carregar problemas com todos os campos necessários
    problems = []
    with open(JSONL_PATH, "r", encoding="utf-8") as f:
        for line in f:
            p = json.loads(line)
            problems.append({
                "task_id": p["task_id"],
                "difficulty": p["difficulty"].lower(),
                "prompt": p["prompt"],         # imports gerais do dataset
                "test": p["test"],             # função check
                "entry_point": p["entry_point"],
            })
    print(f"A avaliar {len(problems)} × {len(MODELS)} = "
          f"{len(problems) * len(MODELS)} execuções\n")

    # 3. Iterar e avaliar
    results = []
    total = len(problems) * len(MODELS)
    counter = 0

    for problem in problems:
        task_id = problem["task_id"]
        difficulty = problem["difficulty"]

        for model in MODELS:
            counter += 1
            response_path = (RESPONSES_DIR / model / difficulty /
                             f"{task_id}.py")
            print(f"[{counter:3d}/{total}] {model:9s} | {difficulty:6s} | "
                  f"{task_id} ... ", end="", flush=True)

            if not response_path.exists():
                print("MISSING")
                results.append({
                    "task_id": task_id, "difficulty": difficulty,
                    "model": model, "status": "MISSING_FILE",
                    "details": str(response_path),
                })
                continue

            model_response = response_path.read_text(encoding="utf-8")

            # Construir e gravar harness
            harness = build_harness(model_response, problem)
            harness_path = WORK_DIR / f"{model}_{difficulty}_{task_id}.py"
            harness_path.write_text(harness, encoding="utf-8")

            # Executar
            status, details = run_harness(harness_path)
            print(status)
            results.append({
                "task_id": task_id, "difficulty": difficulty,
                "model": model, "status": status, "details": details,
            })

    # 4. CSV
    with open(RESULTS_DIR / "results_python.csv", "w", newline="", encoding="utf-8") as f:
        w = csv.writer(f)
        w.writerow(["task_id", "difficulty"] + MODELS)
        for problem in problems:
            row = [problem["task_id"], problem["difficulty"]]
            for m in MODELS:
                r = next((x for x in results if x["task_id"] == problem["task_id"]
                          and x["model"] == m), None)
                row.append(r["status"] if r else "MISSING")
            w.writerow(row)
    print(f"\n[OK] {RESULTS_DIR / 'results_python.csv'}")

    # 5. JSON
    with open(RESULTS_DIR / "results_python.json", "w", encoding="utf-8") as f:
        json.dump(results, f, ensure_ascii=False, indent=2)
    print(f"[OK] {RESULTS_DIR / 'results_python.json'}")

    # 6. Sumário Markdown
    with open(RESULTS_DIR / "results_python_summary.md", "w", encoding="utf-8") as f:
        f.write("# Resultados da Avaliação Python\n\n")
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
    print(f"[OK] {RESULTS_DIR / 'results_python_summary.md'}")
    print("\nAvaliação Python concluída.")


if __name__ == "__main__":
    main()