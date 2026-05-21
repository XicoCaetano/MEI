"""
Geração dos prompts finais para a Experiência 1: Code Generation
=================================================================

Pega no template do prompt e nos campos `problem_description` e `starter_code`
de cada problema da amostra, e gera 30 ficheiros .txt prontos a copy-paste
para os websites dos modelos.

Input:  sample_30_problems.jsonl  (output do select_sample_v4.py)
Output: prompts/{difficulty}/{task_id}.txt  (30 ficheiros)
        prompts_index.md                     (índice navegável)

Uso:
    python generate_prompts.py
"""

import json
import os

# ---------- Template do prompt ----------
TEMPLATE = """Solve the following programming problem in Python.

Problem:
{problem_description}

Function signature:
{starter_code}

Requirements:
- Provide your complete solution in a single Python code block.
- Include all necessary imports at the top of the code block.
- Do not include any text or explanation outside the code block.
- The function must match the signature exactly."""


# ---------- 1. Carregar amostra ----------
print("A carregar sample_30_problems.jsonl...")
with open("sample_30_problems.jsonl", "r", encoding="utf-8") as f:
    sample = [json.loads(line) for line in f]
print(f"   {len(sample)} problemas carregados.")
print()

# ---------- 2. Criar estrutura de pastas ----------
os.makedirs("prompts/easy", exist_ok=True)
os.makedirs("prompts/medium", exist_ok=True)
os.makedirs("prompts/hard", exist_ok=True)

# ---------- 3. Gerar um .txt por problema ----------
print("A gerar prompts...")
generated = {"Easy": 0, "Medium": 0, "Hard": 0}

for p in sample:
    prompt = TEMPLATE.format(
        problem_description=p["problem_description"],
        starter_code=p["starter_code"],
    )
    difficulty_lower = p["difficulty"].lower()
    out_path = f"prompts/{difficulty_lower}/{p['task_id']}.txt"
    with open(out_path, "w", encoding="utf-8") as f:
        f.write(prompt)
    generated[p["difficulty"]] += 1

for dif, count in generated.items():
    print(f"   {dif}: {count} prompts gerados em prompts/{dif.lower()}/")
print()

# ---------- 4. Gerar índice em Markdown ----------
print("A gerar índice...")
with open("prompts_index.md", "w", encoding="utf-8") as f:
    f.write("# Índice dos prompts gerados\n\n")
    f.write(f"Total: {len(sample)} prompts (10 Easy + 10 Medium + 10 Hard)\n\n")

    for dif in ["Easy", "Medium", "Hard"]:
        f.write(f"## {dif}\n\n")
        problems = [p for p in sample if p["difficulty"] == dif]
        for n, p in enumerate(problems, 1):
            f.write(f"{n}. [`{p['task_id']}`]"
                    f"(prompts/{dif.lower()}/{p['task_id']}.txt)\n")
        f.write("\n")

print("   prompts_index.md gerado.")
print()
print("Pronto. Os prompts estão em prompts/{easy,medium,hard}/{task_id}.txt")
print("Para cada problema, abres o .txt, Ctrl+A, Ctrl+C, e colas no website do modelo.")