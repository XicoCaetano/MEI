# Amostra da Experiência 1 - Code Generation

**Dataset:** LeetCodeDataset v0.3.1 (split test)
  
**Total de problemas:** 30 (10 Easy + 10 Medium + 10 Hard)
  
**Estratégia de selecção:** 
1. Excluir problemas 'i' quando existe a versão 'ii' (ou 'ii' quando existe 'iii')
   para reduzir dependência estatística entre observações.
2. Top-10 mais recentes por dificuldade (ordenação por `estimated_date` descendente).

## Limitação assumida

O LeetCodeDataset (split test) cobre apenas Ago/2024 a Mar/2025. Os modelos avaliados (Claude Sonnet 4.6, Gemini 3.1 Pro, DeepSeek V3) têm knowledge cutoff em Jan/2025, pelo que problemas anteriores a essa data podem ter sido vistos durante o treino. A contaminação é tratada como constante experimental (afecta os três modelos igualmente).

## Easy

| # | task_id | question_id | estimated_date | tags |
|---|---------|-------------|----------------|------|
| 1 | `minimum-cost-to-reach-every-position` | 3502 | 2025-03-30 | - |
| 2 | `maximum-containers-on-a-ship` | 3492 | 2025-03-23 | Math |
| 3 | `reverse-degree-of-a-string` | 3498 | 2025-03-23 | - |
| 4 | `maximum-unique-subarray-sum-after-deletion` | 3487 | 2025-03-16 | Greedy, Array, Hash Table |
| 5 | `phone-number-prefix` | 3491 | 2025-03-16 | Trie, Array, String, Sorting |
| 6 | `unique-3-digit-even-numbers` | 3483 | 2025-03-09 | Recursion, Array, Hash Table, Enumeration |
| 7 | `find-the-largest-almost-missing-integer` | 3471 | 2025-03-02 | Array, Hash Table |
| 8 | `transform-array-by-parity` | 3467 | 2025-02-23 | Array, Counting, Sorting |
| 9 | `find-special-substring-of-length-k` | 3456 | 2025-02-16 | String |
| 10 | `maximum-students-on-a-single-bench` | 3450 | 2025-02-09 | Array, Hash Table |

## Medium

| # | task_id | question_id | estimated_date | tags |
|---|---------|-------------|----------------|------|
| 1 | `properties-graph` | 3493 | 2025-03-23 | Depth-First Search, Breadth-First Search, Union Find, Graph, Array, Hash Table |
| 2 | `find-the-minimum-amount-of-time-to-brew-potions` | 3494 | 2025-03-23 | Array, Prefix Sum, Simulation |
| 3 | `maximize-score-after-pair-deletions` | 3496 | 2025-03-23 | - |
| 4 | `closest-equal-element-queries` | 3488 | 2025-03-16 | Array, Hash Table, Binary Search |
| 5 | `zero-array-transformation-iv` | 3489 | 2025-03-16 | Array, Dynamic Programming |
| 6 | `choose-k-elements-with-maximum-sum` | 3478 | 2025-03-09 | Array, Sorting, Heap (Priority Queue) |
| 7 | `fruits-into-baskets-iii` | 3479 | 2025-03-09 | Segment Tree, Array, Binary Search, Ordered Set |
| 8 | `apply-substitutions` | 3481 | 2025-03-09 | Depth-First Search, Breadth-First Search, Graph, Topological Sort, Array, Hash Table, String |
| 9 | `longest-palindromic-subsequence-after-at-most-k-operations` | 3472 | 2025-03-02 | String, Dynamic Programming |
| 10 | `sum-of-k-subarrays-with-length-at-least-m` | 3473 | 2025-03-02 | Array, Dynamic Programming, Prefix Sum |

## Hard

| # | task_id | question_id | estimated_date | tags |
|---|---------|-------------|----------------|------|
| 1 | `longest-palindrome-after-substring-concatenation-ii` | 3504 | 2025-03-30 | - |
| 2 | `minimum-operations-to-make-elements-within-k-subarrays-equal` | 3505 | 2025-03-30 | - |
| 3 | `minimum-operations-to-make-array-elements-zero` | 3495 | 2025-03-23 | Bit Manipulation, Array, Math |
| 4 | `minimum-cost-to-divide-array-into-subarrays` | 3500 | 2025-03-23 | - |
| 5 | `maximize-active-section-with-trade-ii` | 3501 | 2025-03-23 | - |
| 6 | `count-beautiful-numbers` | 3490 | 2025-03-16 | Dynamic Programming |
| 7 | `maximize-subarrays-after-removing-one-conflicting-pair` | 3480 | 2025-03-09 | Segment Tree, Array, Enumeration, Prefix Sum |
| 8 | `longest-common-prefix-of-k-strings-after-removal` | 3485 | 2025-03-09 | Trie, Array, String |
| 9 | `longest-special-path-ii` | 3486 | 2025-03-09 | Tree, Depth-First Search, Array, Hash Table, Prefix Sum |
| 10 | `lexicographically-smallest-generated-string` | 3474 | 2025-03-02 | Greedy, String, String Matching |

