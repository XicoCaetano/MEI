"""
Selecção da amostra para Experiência 1: Code Generation (v4)
=============================================================

Trabalho: MEI 2025/2026 - Experimental Methods in Computer Science
Modelos sob teste: Claude Sonnet 4.6, Gemini 3.1 Pro, DeepSeek V3

Estratégia (v4):
    1. Filtrar duplicados "i/ii/iii" — quando dois ou mais problemas partilham
       o mesmo stem (task_id sem sufixo), manter apenas a versão mais escalada
       (preferência: -iii > -ii > -i > sem sufixo). Esta filtragem reduz a
       dependência estatística entre observações na amostra final.
    2. Para cada nível de dificuldade (Easy / Medium / Hard), seleccionar os 10
       problemas com `estimated_date` mais recente do conjunto filtrado.

Limitação assumida (a declarar no relatório):
    O LeetCodeDataset (split test) cobre apenas Ago/2024 a Mar/2025. Os modelos
    avaliados (Claude Sonnet 4.6, Gemini 3.1 Pro, DeepSeek V3) têm knowledge
    cutoff em Jan/2025, pelo que TODOS os problemas seleccionados podem ter
    sido vistos durante o treino. Esta contaminação é assumida como constante
    experimental (afecta os três modelos igualmente) e é discutida no relatório.

Output:
    - sample_30_problems.jsonl  : amostra completa (problema + testes + sol. ref.)
    - sample_overview.csv       : visão resumida
    - sample_summary.md         : sumário human-readable da amostra
    - excluded_pairs.md         : log dos pares i/ii excluídos (rastreabilidade)

Reprodutibilidade:
    Selecção é determinística. Não há aleatoriedade.

Changelog v4:
    - Detecção e exclusão de duplicados i/ii/iii baseada em stem do task_id
    - Log dos problemas excluídos guardado em ficheiro separado
"""

from datasets import load_dataset
from collections import Counter, defaultdict
from datetime import datetime
import json
import csv
import re

# ---------- Configuração ----------
N_PER_DIFFICULTY = 10
DIFFICULTIES = ["Easy", "Medium", "Hard"]

# Sufixos romanos a detectar; ordenados por prioridade (maior = preferido)
SUFFIX_PRIORITY = {"-iii": 3, "-ii": 2, "-i": 1, "": 0}
SUFFIX_PATTERN = re.compile(r"-(i{1,3})$")  # -i, -ii, -iii no fim do task_id


# ---------- Helpers ----------
def date_to_str(d):
    if isinstance(d, datetime):
        return d.strftime("%Y-%m-%d")
    if isinstance(d, str) and d:
        return d
    return ""


def parse_date(d):
    if isinstance(d, datetime):
        return d
    if isinstance(d, str) and d:
        try:
            return datetime.strptime(d, "%Y-%m-%d")
        except ValueError:
            return datetime.min
    return datetime.min


def json_default(obj):
    if isinstance(obj, datetime):
        return obj.strftime("%Y-%m-%d")
    raise TypeError(f"Type {type(obj).__name__} not JSON serializable")


def split_stem_suffix(task_id):
    """
    Separa task_id em (stem, suffix).
    Exemplos:
        'find-the-power-of-k-size-subarrays-ii' -> ('find-the-power-of-k-size-subarrays', '-ii')
        'snake-in-matrix' -> ('snake-in-matrix', '')
    """
    m = SUFFIX_PATTERN.search(task_id)
    if m:
        suffix = "-" + m.group(1)  # '-i', '-ii', '-iii'
        stem = task_id[:m.start()]
        return stem, suffix
    return task_id, ""


# ---------- 1. Carregar dataset ----------
print("A carregar LeetCodeDataset (split test)...")
ds = load_dataset("newfacade/LeetCodeDataset", split="test")
print(f"   Total no split test: {len(ds)} problemas")
print()

# ---------- 2. Diagnóstico inicial ----------
all_difs = Counter(ds["difficulty"])
print(f"Distribuição de dificuldade: {dict(all_difs)}")

all_dates_sorted = sorted([parse_date(d) for d in ds["estimated_date"]])
print(f"Range temporal: {all_dates_sorted[0].strftime('%Y-%m-%d')}  ->  "
      f"{all_dates_sorted[-1].strftime('%Y-%m-%d')}")
print()

# ---------- 3. Identificar grupos de duplicados (mesmo stem) ----------
# stems_to_indices: { stem: [(suffix, idx), ...] }
stems_to_indices = defaultdict(list)
for i in range(len(ds)):
    stem, suffix = split_stem_suffix(ds[i]["task_id"])
    stems_to_indices[stem].append((suffix, i))

# Manter apenas a versão com sufixo de maior prioridade em cada grupo
kept_indices = set()
excluded = []  # (kept_task_id, excluded_task_id, kept_suffix, excluded_suffix)

for stem, members in stems_to_indices.items():
    if len(members) == 1:
        # único, manter
        kept_indices.add(members[0][1])
    else:
        # múltiplos: manter só o de maior prioridade
        members_sorted = sorted(members,
                                key=lambda x: SUFFIX_PRIORITY.get(x[0], -1),
                                reverse=True)
        kept_suffix, kept_idx = members_sorted[0]
        kept_indices.add(kept_idx)
        for ex_suffix, ex_idx in members_sorted[1:]:
            excluded.append({
                "stem": stem,
                "kept": ds[kept_idx]["task_id"],
                "kept_suffix": kept_suffix or "(nenhum)",
                "excluded": ds[ex_idx]["task_id"],
                "excluded_suffix": ex_suffix or "(nenhum)",
                "kept_difficulty": ds[kept_idx]["difficulty"],
                "kept_date": date_to_str(ds[kept_idx]["estimated_date"]),
            })

print(f"Grupos com duplicados detectados: "
      f"{sum(1 for m in stems_to_indices.values() if len(m) > 1)}")
print(f"Problemas excluídos (versões 'i' quando 'ii' existe, etc.): "
      f"{len(excluded)}")
print(f"Problemas elegíveis após filtragem: {len(kept_indices)}")
print()

# Distribuição de dificuldade após filtragem
filtered_difs = Counter(ds[i]["difficulty"] for i in kept_indices)
print(f"Distribuição após filtragem: {dict(filtered_difs)}")
print()

# Sanity check
for dif in DIFFICULTIES:
    if filtered_difs[dif] < N_PER_DIFFICULTY:
        print(f"AVISO: só {filtered_difs[dif]} problemas '{dif}' após filtragem; "
              f"precisas de {N_PER_DIFFICULTY}")

# ---------- 4. Selecção: top-N mais recentes por dificuldade ----------
selected_indices = []
print(f"Selecção (top-{N_PER_DIFFICULTY} mais recentes por dificuldade):")

for dif in DIFFICULTIES:
    pool = [(i, parse_date(ds[i]["estimated_date"])) for i in kept_indices
            if ds[i]["difficulty"] == dif]
    pool.sort(key=lambda x: x[1], reverse=True)
    chosen = [i for i, _ in pool[:N_PER_DIFFICULTY]]
    selected_indices.extend(chosen)

    if chosen:
        dates_chosen = sorted([date_to_str(ds[i]["estimated_date"]) for i in chosen])
        print(f"   {dif}: {len(chosen)} problemas, "
              f"datas {dates_chosen[0]} a {dates_chosen[-1]}")
    else:
        print(f"   {dif}: 0 problemas (pool vazio)")
print()

# ---------- 5. Exportar JSONL completo ----------
output_jsonl = "sample_30_problems.jsonl"
with open(output_jsonl, "w", encoding="utf-8") as f:
    for i in selected_indices:
        record = {k: ds[i][k] for k in ds.column_names}
        f.write(json.dumps(record, ensure_ascii=False, default=json_default) + "\n")
print(f"OK Amostra completa: {output_jsonl}")

# ---------- 6. Exportar CSV resumido ----------
output_csv = "sample_overview.csv"
with open(output_csv, "w", newline="", encoding="utf-8") as f:
    writer = csv.writer(f)
    writer.writerow(["task_id", "question_id", "difficulty",
                     "estimated_date", "tags"])
    for i in selected_indices:
        writer.writerow([
            ds[i]["task_id"],
            ds[i]["question_id"],
            ds[i]["difficulty"],
            date_to_str(ds[i]["estimated_date"]),
            ", ".join(ds[i]["tags"]) if ds[i]["tags"] else "",
        ])
print(f"OK Visão resumida: {output_csv}")

# ---------- 7. Exportar sumário Markdown da amostra ----------
output_md = "sample_summary.md"
with open(output_md, "w", encoding="utf-8") as f:
    f.write("# Amostra da Experiência 1 - Code Generation\n\n")
    f.write("**Dataset:** LeetCodeDataset v0.3.1 (split test)\n  \n")
    f.write(f"**Total de problemas:** {len(selected_indices)} "
            f"({N_PER_DIFFICULTY} Easy + {N_PER_DIFFICULTY} Medium + "
            f"{N_PER_DIFFICULTY} Hard)\n  \n")
    f.write("**Estratégia de selecção:** \n")
    f.write("1. Excluir problemas 'i' quando existe a versão 'ii' (ou 'ii' quando existe 'iii')\n")
    f.write("   para reduzir dependência estatística entre observações.\n")
    f.write("2. Top-10 mais recentes por dificuldade (ordenação por `estimated_date` descendente).\n\n")

    f.write("## Limitação assumida\n\n")
    f.write("O LeetCodeDataset (split test) cobre apenas Ago/2024 a Mar/2025. ")
    f.write("Os modelos avaliados (Claude Sonnet 4.6, Gemini 3.1 Pro, DeepSeek V3) ")
    f.write("têm knowledge cutoff em Jan/2025, pelo que problemas anteriores a essa ")
    f.write("data podem ter sido vistos durante o treino. A contaminação é tratada ")
    f.write("como constante experimental (afecta os três modelos igualmente).\n\n")

    for dif in DIFFICULTIES:
        f.write(f"## {dif}\n\n")
        f.write("| # | task_id | question_id | estimated_date | tags |\n")
        f.write("|---|---------|-------------|----------------|------|\n")
        dif_indices = [i for i in selected_indices if ds[i]["difficulty"] == dif]
        dif_indices.sort(key=lambda i: parse_date(ds[i]["estimated_date"]),
                         reverse=True)
        for n, i in enumerate(dif_indices, 1):
            tags = ", ".join(ds[i]["tags"]) if ds[i]["tags"] else "-"
            f.write(f"| {n} | `{ds[i]['task_id']}` | {ds[i]['question_id']} | "
                    f"{date_to_str(ds[i]['estimated_date'])} | {tags} |\n")
        f.write("\n")

print(f"OK Sumário Markdown: {output_md}")

# ---------- 8. Exportar log dos pares excluídos ----------
output_excl = "excluded_pairs.md"
with open(output_excl, "w", encoding="utf-8") as f:
    f.write("# Pares duplicados excluídos da amostra\n\n")
    f.write(f"Total excluídos: **{len(excluded)}**\n\n")
    f.write("Critério: quando dois ou mais problemas partilham o mesmo stem ")
    f.write("de `task_id`, mantém-se apenas a versão com sufixo de maior ")
    f.write("prioridade (-iii > -ii > -i > sem sufixo).\n\n")
    f.write("| Stem | Mantido | Sufixo mantido | Excluído | Sufixo excluído | Dificuldade |\n")
    f.write("|------|---------|----------------|----------|-----------------|-------------|\n")
    for e in sorted(excluded, key=lambda x: x["stem"]):
        f.write(f"| `{e['stem']}` | `{e['kept']}` | `{e['kept_suffix']}` | "
                f"`{e['excluded']}` | `{e['excluded_suffix']}` | {e['kept_difficulty']} |\n")
print(f"OK Log de exclusões: {output_excl}")
print()
print("Pronto. Manda-me o conteúdo de `sample_summary.md` para validarmos.")