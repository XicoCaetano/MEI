# Validation log — Tradução Python → C++

## minimum-cost-to-reach-every-position

- Status: SUCCESS
- Difficulty: Easy
- Notes: Tradução directa do Python (in-place min prefix). Função recebe `vector<int>` por valor (não por referência) para suportar rvalues nos asserts.

## maximum-containers-on-a-ship

- Status: SUCCESS
- Difficulty: Easy
- Notes: Multiplicação `n*n*w` pode chegar a ~1e9; promovido a `long long` por segurança antes do `min` e da divisão.

## reverse-degree-of-a-string

- Status: SUCCESS
- Difficulty: Easy
- Notes: `enumerate(s, 1)` traduzido com `i+1` no índice do loop. Acumulador em `long long` (somatórios podem exceder `int` para strings longas).

## maximum-unique-subarray-sum-after-deletion

- Status: SUCCESS
- Difficulty: Easy
- Notes: `set` Python → `unordered_set<int>`. `max(nums)` → `*max_element(...)`.

## phone-number-prefix

- Status: SUCCESS
- Difficulty: Easy
- Notes: `numbers.sort(key=len)` → `sort` com lambda comparando `size()`. `s.startswith(t)` → `s.compare(0, t.size(), t) == 0` com guarda de tamanho.

## unique-3-digit-even-numbers

- Status: SUCCESS
- Difficulty: Easy
- Notes: Triplo loop com `set`; tradução directa para `unordered_set<int>`.

## find-the-largest-almost-missing-integer

- Status: SUCCESS
- Difficulty: Easy
- Notes: `Counter` → `unordered_map<int,int>`. `max(... default=-1)` → fold manual com `best=-1`.

## transform-array-by-parity

- Status: SUCCESS
- Difficulty: Easy
- Notes: Tradução directa; contagem de pares e atribuição posicional.

## find-special-substring-of-length-k

- Status: SUCCESS
- Difficulty: Easy
- Notes: Two-pointer sobre runs de caracteres iguais.

## maximum-students-on-a-single-bench

- Status: SUCCESS
- Difficulty: Easy
- Notes: `defaultdict(set)` → `unordered_map<int, unordered_set<int>>`. Empty input devolve 0.

## properties-graph

- Status: SUCCESS
- Difficulty: Medium
- Notes: `set(properties[i])` → `unordered_set<int>` por linha; intersecção computada percorrendo o set menor. DFS com `function<void(int)>` recursiva.

## find-the-minimum-amount-of-time-to-brew-potions

- Status: SUCCESS
- Difficulty: Medium
- Notes: Produtos `skill[i] * mana[j]` podem chegar a 5000*5000 = 2.5e7; somatórios em `long long` para evitar overflow.

## maximize-score-after-pair-deletions

- Status: SUCCESS
- Difficulty: Medium
- Notes: `pairwise(nums)` → loop sobre `i, i+1`. Acumuladores em `long long`. Tipo de retorno `long long`.

## closest-equal-element-queries

- Status: SUCCESS
- Difficulty: Medium
- Notes: Truque do array duplicado de tamanho 2n para ciclicidade. `dict` Python → `unordered_map<int,int>`.

## zero-array-transformation-iv

- Status: SUCCESS
- Difficulty: Medium
- Notes: Tradução directa do algoritmo de subset-sums por índice. `set` → `unordered_set<int>`. Cuidado com a actualização: snapshot dos valores antes de inserir.

## choose-k-elements-with-maximum-sum

- Status: SUCCESS
- Difficulty: Medium
- Notes: `heapq` (min-heap) → `priority_queue<int, vector<int>, greater<int>>`. Retorno em `vector<long long>` para evitar overflow nos somatórios.

## fruits-into-baskets-iii

- Status: SUCCESS
- Difficulty: Medium
- Notes: Segment tree + discretização. Sentinela `MN = 1e10` requer `long long`. `defaultdict(deque)` → `unordered_map<int, deque<int>>`.

## apply-substitutions

- Status: SUCCESS
- Difficulty: Medium
- Notes: DFS recursiva com `function<string(const string&)>`. `s.find('%')` em vez de slicing.

## longest-palindromic-subsequence-after-at-most-k-operations

- Status: SUCCESS
- Difficulty: Medium
- Notes: DP 3D com memoização. **Atenção**: o teste `"step on no pets"` contém espaços (não-letras), o que faz `t = min(d, 26-d)` ficar negativo. Em Python o `@cache` aceita qualquer `kk - t`, mas em C++ um `kk - t > k` quebra os limites do array. Fix: clamping de `new_kk` ao intervalo `[0, k]` (ops extra não ajudam vs. k ops).

## sum-of-k-subarrays-with-length-at-least-m

- Status: SUCCESS
- Difficulty: Medium
- Notes: DP com estado `(i, ongoing, kk)` e sentinela `INF = 2e7` (preservada literal para os testes onde a saída é `-19999850 = -INF + 150`). Memo inicializado a `LLONG_MIN`.

## longest-palindrome-after-substring-concatenation-ii

- Status: SUCCESS
- Difficulty: Hard
- Notes: DP de substring-comum + expansão central a partir de `s`. Vector `mx[i]` = max comum começando em qualquer posição.

## minimum-operations-to-make-elements-within-k-subarrays-equal

- Status: SUCCESS
- Difficulty: Hard
- Notes: LazyHeap (heap com remoção preguiçosa) + janela deslizante de mediana + DP. Sentinela `INF = 4e18` para casos infeasíveis. **Atenção**: 2 testes esperam `inf` em Python — substituídos por `4000000000000000000` no string de teste (preprocessing) para igualar a constante C++.

## minimum-operations-to-make-array-elements-zero

- Status: SUCCESS
- Difficulty: Hard
- Notes: Inputs incluem `2500000000` que excede `INT_MAX`. Assinatura do parâmetro `queries` muda para `vector<vector<long long>>`. Retorno em `long long`.

## minimum-cost-to-divide-array-into-subarrays

- Status: SUCCESS
- Difficulty: Hard
- Notes: DP O(n²) com prefix sums. Acumuladores em `long long`.

## maximize-active-section-with-trade-ii

- Status: SUCCESS
- Difficulty: Hard
- Notes: Sparse table + binary searches manuais sobre array de pares (em vez de `bisect_left/right` com `key`). Sentinelas `(-1,-1)` e `(n+1,n+1)` em `a` preservadas.

## count-beautiful-numbers

- Status: SUCCESS
- Difficulty: Hard
- Notes: Digit DP com estado `(i, tight, isLeadingZero, hasZero, sum, prod)`. Memo via `unordered_map<long long, long long>` com chave codificada num único `long long` (multiplicadores: prod até 9⁹ < 4e8). Fast-path quando `hasZero` já é true e `!tight`.

## maximize-subarrays-after-removing-one-conflicting-pair

- Status: SUCCESS
- Difficulty: Hard
- Notes: Sweep com `maxLeft`/`secondMaxLeft`. Acumulador `validSubarrays` em `long long`.

## longest-common-prefix-of-k-strings-after-removal

- Status: SUCCESS
- Difficulty: Hard
- Notes: Trie com contador por nó. `SortedList` Python → `set<int, greater<int>>` (front é o maior). Inserir/remover unicamente quando contador atravessa `k`.

## longest-special-path-ii

- Status: SUCCESS
- Difficulty: Hard
- Notes: DFS sobre árvore com prefix sums e `lastSeenDepth`. `leftBoundary` mantido como `array<int,2>`. Após DFS, restauro `lastSeenDepth` ao valor anterior (incluindo apagar a entrada se `prevDepth == 0`).

## lexicographically-smallest-generated-string

- Status: SUCCESS
- Difficulty: Hard
- Notes: 3 fases (T fix, fill 'a', F violations). `'\0'` como sentinela de "não atribuído" em `string`.
