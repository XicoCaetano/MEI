"""
Geração dos prompts C++ para a Experiência 1: Code Generation
==============================================================

Para cada problema do `sample_30_problems.jsonl`, gera um prompt em texto
contendo:
  - O `problem_description` original (em inglês, do dataset)
  - O `starter_code` em C++ extraído da tradução validada em ./translations/

Os 30 ficheiros `.txt` gerados ficam prontos a copy-paste para os websites
dos modelos.

Input:
    - sample_30_problems.jsonl
    - translations/{task_id}.cpp  (tradução validada pelo agente)

Output:
    - prompts_cpp/{difficulty}/{task_id}.txt   (30 ficheiros)
    - prompts_cpp_index.md                     (índice navegável)

Uso:
    python3 generate_prompts_cpp.py
"""

import json
import os
import re
from pathlib import Path

# ---------- Configuração ----------
JSONL_PATH = Path("sample_30_problems.jsonl")
TRANSLATIONS_DIR = Path("translations")
PROMPTS_DIR = Path("prompts_cpp")

# ---------- Template do prompt ----------
TEMPLATE = """Solve the following programming problem in C++.

Problem:
{problem_description}

Starter code:
```cpp
{starter_code}
```

Requirements:
- Provide your complete solution in a single C++ code block.
- Include all necessary headers at the top of the code block.
- Do not include any text or explanation outside the code block.
- The class and function signature must match the starter code exactly.
- Do not include a `main()` function — only the `class Solution` (and any helper structs already shown in the starter code)."""


def extract_cpp_starter(translation_cpp: str) -> str:
    """
    Extrai o starter code em C++ da tradução validada:
      - Includes
      - Eventuais structs auxiliares (ListNode, TreeNode, etc.)
      - Declaração da classe Solution com assinatura(s) de função(ões),
        mas SEM o corpo da solução.

    Estratégia:
      1. Pegar tudo desde o início até `class Solution`
      2. Dentro da `class Solution`, pegar a(s) assinatura(s) das funções
         e substituir o corpo por `        // your code here`
    """
    # 1. Pegar tudo até `class Solution`
    match = re.search(r"class\s+Solution\s*\{", translation_cpp)
    if not match:
        raise ValueError("Não foi encontrada `class Solution` na tradução.")

    pre_class = translation_cpp[:match.start()].rstrip() + "\n\n"
    rest = translation_cpp[match.start():]

    # 2. Encontrar onde a `class Solution { ... };` acaba
    # (procurar o `};` que fecha a classe — é o primeiro `};` após o `class Solution {`)
    # Mas atenção: structs internas podem confundir. Aqui assumimos que `};`
    # da Solution é o último antes de `int main()` (ou fim de ficheiro se não há main).
    main_match = re.search(r"int\s+main\s*\([^)]*\)\s*\{", rest)
    class_block_end = main_match.start() if main_match else len(rest)
    class_block = rest[:class_block_end].rstrip()

    # Garantir que termina com `};`
    if not class_block.rstrip().endswith("};"):
        # cortar até ao último `};` antes do main
        last_close = class_block.rfind("};")
        if last_close == -1:
            raise ValueError("Não foi encontrado o `};` que fecha a classe Solution.")
        class_block = class_block[:last_close + 2]

    # 3. Substituir corpos das funções dentro da Solution por placeholder
    # Estratégia: encontrar cada função `... <nome>(...) {` dentro da Solution
    # e substituir o conteúdo entre `{` e o `}` correspondente por placeholder.
    starter_class = _strip_function_bodies(class_block)

    return pre_class + starter_class


def _strip_function_bodies(class_block: str) -> str:
    """
    Recebe o texto da `class Solution { ... };` e substitui o corpo
    de cada função pública por um placeholder, mantendo apenas a assinatura.

    Heurística: procurar padrões `<tipo> <nome>(<args>) {` e substituir
    o conteúdo do `{...}` correspondente.
    """
    result = []
    i = 0
    inside_class_body = False

    # Estado: percorrer caracteres do bloco
    while i < len(class_block):
        # Detectar abertura da classe
        if not inside_class_body:
            class_match = re.match(r"class\s+Solution\s*\{", class_block[i:])
            if class_match:
                result.append(class_block[i:i + class_match.end()])
                i += class_match.end()
                inside_class_body = True
                continue
            result.append(class_block[i])
            i += 1
            continue

        # Dentro do corpo da classe, procurar próxima função
        # Padrão: assinatura termina com `) {` ou `) const {`
        func_match = re.search(
            r"([^;{}]+\([^)]*\)(?:\s*const)?)\s*\{",
            class_block[i:]
        )
        if func_match:
            # Verificar se o que vem antes é mesmo uma assinatura de função
            # (e não algo aleatório dentro do corpo)
            sig_text = func_match.group(1).strip()
            if "public:" in sig_text or sig_text.startswith("//"):
                # Não é função; saltar este match
                result.append(class_block[i:i + func_match.start() + 1])
                i += func_match.start() + 1
                continue

            # Adicionar tudo até à `{` de abertura
            result.append(class_block[i:i + func_match.end()])
            # Encontrar o `}` correspondente (matching braces)
            brace_count = 1
            j = i + func_match.end()
            while j < len(class_block) and brace_count > 0:
                if class_block[j] == "{":
                    brace_count += 1
                elif class_block[j] == "}":
                    brace_count -= 1
                j += 1
            # Substituir corpo por placeholder
            result.append("\n        // your code here\n    }")
            i = j
        else:
            # Não há mais funções; copiar o resto
            result.append(class_block[i:])
            break

    return "".join(result)


# ---------- 1. Carregar amostra ----------
print("A carregar sample_30_problems.jsonl...")
with open(JSONL_PATH, "r", encoding="utf-8") as f:
    sample = [json.loads(line) for line in f]
print(f"   {len(sample)} problemas carregados.\n")


# ---------- 2. Criar estrutura de pastas ----------
os.makedirs(PROMPTS_DIR / "easy", exist_ok=True)
os.makedirs(PROMPTS_DIR / "medium", exist_ok=True)
os.makedirs(PROMPTS_DIR / "hard", exist_ok=True)


# ---------- 3. Gerar prompts ----------
print("A gerar prompts C++...")
generated = {"Easy": 0, "Medium": 0, "Hard": 0}
errors = []

for p in sample:
    task_id = p["task_id"]
    difficulty = p["difficulty"]
    translation_path = TRANSLATIONS_DIR / f"{task_id}.cpp"

    if not translation_path.exists():
        errors.append((task_id, "Tradução não existe"))
        continue

    translation_cpp = translation_path.read_text(encoding="utf-8")

    try:
        starter_cpp = extract_cpp_starter(translation_cpp)
    except Exception as e:
        errors.append((task_id, f"Erro a extrair starter: {e}"))
        continue

    prompt = TEMPLATE.format(
        problem_description=p["problem_description"],
        starter_code=starter_cpp,
    )

    out_path = PROMPTS_DIR / difficulty.lower() / f"{task_id}.txt"
    out_path.write_text(prompt, encoding="utf-8")
    generated[difficulty] += 1

for dif, count in generated.items():
    print(f"   {dif}: {count} prompts gerados em prompts_cpp/{dif.lower()}/")

if errors:
    print("\n[AVISOS] Problemas com erros:")
    for task_id, err in errors:
        print(f"   - {task_id}: {err}")


# ---------- 4. Gerar índice ----------
print("\nA gerar índice...")
with open("prompts_cpp_index.md", "w", encoding="utf-8") as f:
    f.write("# Índice dos prompts C++ gerados\n\n")
    f.write(f"Total: {sum(generated.values())} prompts "
            f"(10 Easy + 10 Medium + 10 Hard)\n\n")
    for dif in ["Easy", "Medium", "Hard"]:
        f.write(f"## {dif}\n\n")
        problems = [p for p in sample if p["difficulty"] == dif]
        for n, p in enumerate(problems, 1):
            f.write(f"{n}. [`{p['task_id']}`]"
                    f"(prompts_cpp/{dif.lower()}/{p['task_id']}.txt)\n")
        f.write("\n")

print("   prompts_cpp_index.md gerado.\n")
print("Pronto.")
print()
print("VERIFICAÇÃO RECOMENDADA antes de copy-paste para os websites:")
print("  1. Abre 1-2 ficheiros .txt aleatórios em prompts_cpp/")
print("  2. Confirma que o starter code mostra a class Solution mas NÃO mostra")
print("     o corpo da solução (deve aparecer '// your code here')")
print("  3. Confirma que structs auxiliares (ListNode, TreeNode) aparecem")
print("     antes da class Solution se forem relevantes para o problema")