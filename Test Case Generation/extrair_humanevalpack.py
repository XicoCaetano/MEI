"""
extrair_humanevalpack.py
-----------------------
Extrai as primeiras 30 instancias de Python e C++ do dataset
'bigcode/humanevalpack' e guarda cada algoritmo num ficheiro separado
dentro de experiencia_dataset/{python,cpp}/.
"""

import subprocess
import sys
import io

# Forcar UTF-8 no stdout para evitar UnicodeEncodeError no Windows (cp1252)
sys.stdout = io.TextIOWrapper(sys.stdout.buffer, encoding="utf-8", errors="replace")

# ── 1. Garantir que a biblioteca datasets está instalada ──────────────────────
try:
    import datasets  # noqa: F401
    print("[OK] biblioteca 'datasets' já está instalada.")
except ImportError:
    print("[INFO] A instalar 'datasets' via pip...")
    subprocess.check_call([sys.executable, "-m", "pip", "install", "datasets"])
    print("[OK] 'datasets' instalada com sucesso.")

# ── 2. Imports ────────────────────────────────────────────────────────────────
import re
from pathlib import Path
from datasets import load_dataset

# ── 3. Configuração ───────────────────────────────────────────────────────────
BASE_DIR    = Path("experiencia_dataset")
N_INSTANCES = 30

CONFIGS = {
    "python": {"subdir": BASE_DIR / "python", "ext": ".py"},
    "cpp":    {"subdir": BASE_DIR / "cpp",    "ext": ".cpp"},
}

# ── 4. Criar directórios ──────────────────────────────────────────────────────
for lang, cfg in CONFIGS.items():
    cfg["subdir"].mkdir(parents=True, exist_ok=True)
    print(f"[DIR] {cfg['subdir']} criada/já existe.")

# ── 5. Função auxiliar: limpar task_id → nome de ficheiro ────────────────────
def task_id_to_filename(task_id: str, ext: str) -> str:
    """
    Converte 'HumanEval/0' → 'task_0.py'  (ou .cpp, etc.)
    Mantém apenas dígitos finais após a barra.
    """
    number = re.sub(r"[^/]+/", "", task_id)          # remove tudo antes de '/'
    number = re.sub(r"[^\w]", "_", number)             # sanitiza caracteres
    return f"task_{number}{ext}"

# ── 6. Processar cada linguagem ───────────────────────────────────────────────
total_written = 0

for lang, cfg in CONFIGS.items():
    print(f"\n[LOAD] A carregar configuração '{lang}' do dataset…")
    dataset = load_dataset(
        "bigcode/humanevalpack",
        lang,
        split="test",
        trust_remote_code=True,
    )

    instances = dataset.select(range(N_INSTANCES))
    print(f"  >> {len(instances)} instancias seleccionadas para '{lang}'.")

    for row in instances:
        task_id  = row["task_id"]          # ex: "HumanEval/0"
        prompt   = row["prompt"]           # imports + assinatura
        solution = row["canonical_solution"]  # implementação correcta

        code     = prompt + solution       # código completo
        filename = task_id_to_filename(task_id, cfg["ext"])
        filepath = cfg["subdir"] / filename

        filepath.write_text(code, encoding="utf-8")
        total_written += 1
        print(f"  [WRITE] {filepath}")

# ── 7. Resumo final ───────────────────────────────────────────────────────────
print(f"\n{'='*60}")
print(f"  Concluído! {total_written} ficheiros criados em '{BASE_DIR}/'")
print(f"  • {BASE_DIR}/python/  → {N_INSTANCES} ficheiros .py")
print(f"  • {BASE_DIR}/cpp/     → {N_INSTANCES} ficheiros .cpp")
print(f"{'='*60}")
