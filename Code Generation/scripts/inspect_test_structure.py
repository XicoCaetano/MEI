"""
Inspecção dos campos do LeetCodeDataset para perceber a estrutura
dos testes antes de construir o pipeline de avaliação.

Output: imprime no terminal exemplos detalhados dos campos relevantes
        para 2 problemas (1 fácil, 1 difícil) da nossa amostra.
"""

import json

# Carregar a amostra que já seleccionámos
with open("sample_30_problems.jsonl", "r", encoding="utf-8") as f:
    sample = [json.loads(line) for line in f]

print(f"Total de problemas na amostra: {len(sample)}\n")

# Pegar 2 exemplos (1 Easy, 1 Hard) para inspeccionar
exemplos = []
for p in sample:
    if p["difficulty"] == "Easy" and len(exemplos) == 0:
        exemplos.append(p)
    if p["difficulty"] == "Hard" and len(exemplos) == 1:
        exemplos.append(p)
    if len(exemplos) == 2:
        break

# ---------- Inspecionar cada exemplo ----------
for ex in exemplos:
    print("=" * 80)
    print(f"PROBLEMA: {ex['task_id']}  ({ex['difficulty']})")
    print("=" * 80)

    print("\n--- CAMPOS DISPONÍVEIS ---")
    print(list(ex.keys()))

    print("\n--- entry_point ---")
    print(repr(ex["entry_point"]))

    print("\n--- starter_code (primeiros 300 chars) ---")
    print(ex["starter_code"][:300])

    print("\n--- prompt (primeiros 300 chars) ---")
    print(ex["prompt"][:300])

    print("\n--- completion (primeiros 500 chars da solução de referência) ---")
    print(ex["completion"][:500])

    print("\n--- test (TIPO + primeiros 800 chars) ---")
    print(f"Tipo: {type(ex['test']).__name__}")
    if isinstance(ex["test"], str):
        print(ex["test"][:800])
    else:
        print(repr(ex["test"])[:800])

    print("\n--- input_output (TIPO + estrutura) ---")
    io = ex["input_output"]
    print(f"Tipo: {type(io).__name__}")
    if isinstance(io, str):
        # Pode ser uma string JSON
        try:
            parsed = json.loads(io)
            print(f"  É string JSON. Após parse: {type(parsed).__name__}")
            if isinstance(parsed, dict):
                print(f"  Keys: {list(parsed.keys())}")
                for k, v in parsed.items():
                    print(f"    {k} (tipo {type(v).__name__}, len={len(v) if hasattr(v, '__len__') else 'N/A'}): "
                          f"{repr(v)[:200]}")
        except json.JSONDecodeError:
            print(f"  É string mas não JSON. Primeiros 500 chars:")
            print(io[:500])
    elif isinstance(io, dict):
        print(f"  Keys: {list(io.keys())}")
        for k, v in io.items():
            print(f"    {k} (tipo {type(v).__name__}): {repr(v)[:200]}")
    else:
        print(f"  Conteúdo: {repr(io)[:500]}")

    print("\n")

print("=" * 80)
print("Cola este output completo no chat para definirmos o pipeline de avaliação.")
print("=" * 80)