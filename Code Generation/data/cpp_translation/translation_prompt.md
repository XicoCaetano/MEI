# Tradução de problemas LeetCode: Python → C++ (Linux / g++)

## Contexto

Tenho 30 problemas LeetCode em Python no ficheiro `sample_30_problems.jsonl`. Cada problema tem 4 campos relevantes em Python:
- `problem_description`: enunciado em texto
- `starter_code`: assinatura da função em Python
- `completion`: solução de referência em Python
- `test`: função `check(candidate)` com `assert`s que validam a solução

Preciso de traduzir cada problema para **C++17** mantendo a mesma lógica algorítmica. O resultado deve ser um ficheiro `.cpp` por problema, compilável com `g++ -std=c++17` e executável em Linux.

## Para cada problema, gerar `translations/{task_id}.cpp` com a seguinte estrutura

```cpp
// task_id: <task_id do problema>
// difficulty: <Easy|Medium|Hard>

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <cmath>
#include <climits>
// ... outros includes necessários

using namespace std;

// === STARTER CODE EM C++ ===
class Solution {
public:
    <tipo_retorno> <nome_funcao>(<parâmetros>) {
        // SOLUÇÃO DE REFERÊNCIA TRADUZIDA DO PYTHON
        // (equivalente ao campo `completion` do dataset)
    }
};

// === TESTES TRADUZIDOS ===
int main() {
    Solution sol;
    
    assert(sol.<nome_funcao>(<args1>) == <expected1>);
    assert(sol.<nome_funcao>(<args2>) == <expected2>);
    // ... todos os asserts originais traduzidos
    
    cout << "All tests passed for <task_id>" << endl;
    return 0;
}
```

## Regras CRÍTICAS de tradução (não violar)

### 1. Preservar a equivalência semântica dos testes

**Os valores dos asserts não podem ser alterados.** Se o teste Python diz `assert candidate(cost=[1,10]) == [1,1]`, a versão C++ deve testar exactamente o mesmo input e esperar exactamente o mesmo output. Se a tradução literal não funciona em C++, o problema está na **solução** (ou na conversão de tipos), nunca no valor esperado do teste.

### 2. Não modificar testes para "fazer passar"

Se a solução de referência traduzida **falha** num teste, **NÃO modificar o teste** para a fazer passar. Em vez disso:
- Verificar se a solução está correctamente traduzida
- Verificar se há problemas de tipos numéricos (regra 4)
- Se mesmo assim falhar, registar o problema no `validation_log.md` com o erro exacto e parar nesse problema

### 3. Lidar com tipos LeetCode-específicos

Se um problema usa estruturas LeetCode como `ListNode` ou `TreeNode`, definir a classe no início do `.cpp`:

```cpp
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};
```

E criar funções helper para construir estas estruturas a partir de listas/arrays nos asserts (ex: `buildList({1,2,3})`).

### 4. Cuidado com tipos numéricos

Python tem `int` ilimitado; C++ não. Se o problema envolve:
- Multiplicação de números grandes
- Acumuladores de muitos elementos
- Restrições com `10^9`, `10^18`, etc.

→ usar `long long` em vez de `int`. Verificar as restrições no `problem_description`.

### 5. Comparação de containers

Em C++, `vector<int> a == vector<int> b` funciona elemento a elemento (igual ao Python). Para `unordered_set` ou `unordered_map`, a comparação também é por conteúdo, não ordem. Para problemas onde a ordem do output não importa (ex: "return any valid permutation"), pode ser necessário ordenar antes de comparar.

### 6. `sort()` e funções equivalentes

- Python `sorted(arr)` → C++ `sort(arr.begin(), arr.end())`
- Python `sorted(arr, reverse=True)` → C++ `sort(arr.begin(), arr.end(), greater<int>())`
- Python `Counter(arr)` → C++ `unordered_map<int,int>` com loop manual
- Python `defaultdict(int)` → C++ `unordered_map<int,int>` (default value 0 ao indexar)

### 7. Strings

- Python `s[::-1]` → C++ `string(s.rbegin(), s.rend())`
- Python `"".join(arr)` → C++ loop manual com `+= `

## Workflow para cada problema

1. Ler o problema do `sample_30_problems.jsonl` (procurar pelo `task_id`)
2. Traduzir os 4 campos para C++ no ficheiro `translations/{task_id}.cpp`
3. Compilar: `g++ -std=c++17 -O2 -o translations/{task_id} translations/{task_id}.cpp`
4. Executar: `./translations/{task_id}`
5. **Validação:**
   - Se compila + todos os asserts passam + imprime "All tests passed" → SUCCESS
   - Se compila mas algum assert falha → FAIL (registar input que falhou)
   - Se não compila → COMPILE_ERROR (registar erro do compilador)
6. Registar resultado no `validation_log.md` com formato:

```markdown
## {task_id}

- Status: SUCCESS | FAIL | COMPILE_ERROR
- Difficulty: {Easy|Medium|Hard}
- Notes: <qualquer observação relevante; se FAIL/COMPILE_ERROR, qual foi o erro>
```

## Início

Começar pelo primeiro problema Easy. Após cada SUCCESS, avançar para o próximo. Após cada FAIL/COMPILE_ERROR, **parar e reportar** para revisão manual antes de continuar.

Lista de problemas (extrair `task_id`s do `sample_30_problems.jsonl` e processar nesta ordem):
1. Todos os 10 Easy
2. Todos os 10 Medium
3. Todos os 10 Hard

Output esperado:
- 30 ficheiros em `translations/{task_id}.cpp`
- 1 ficheiro `validation_log.md` com 30 entradas
- 0 modificações nos valores esperados dos testes (regras críticas 1 e 2)