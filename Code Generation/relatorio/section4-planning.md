# 4. Protocolo Experimental

Esta secção descreve o procedimento operacional adoptado para garantir a reprodutibilidade da experiência e a manutenção das variáveis controladas definidas na secção 2.4.

## 4.1 Selecção da amostra

A amostra é constituída por 30 problemas extraídos do **LeetCodeDataset v0.3.1** (split de teste, 228 problemas no total), disponível publicamente no Hugging Face. A selecção é feita em duas etapas:

1. **Remoção de problemas duplicados.** Alguns problemas do dataset correspondem ao mesmo enunciado base, repetido em múltiplas variantes. Estes duplicados são removidos antes da selecção, evitando que o mesmo problema seja apresentado mais do que uma vez aos modelos e amplificando a contaminação dos dados de treino.
2. **Estratificação por dificuldade.** Para cada nível (Easy, Medium, Hard) são seleccionados os 10 problemas com data estimada mais recente, totalizando 30. Esta estratégia maximiza a probabilidade de os problemas serem posteriores ao knowledge cutoff dos modelos avaliados (Janeiro de 2025).

## 4.2 Prompt template

O prompt enviado a cada modelo é idêntico para todos os 30 problemas e para os três modelos avaliados, alterando apenas o conteúdo dos campos `{problem_description}` (descrição completa do problema, incluindo exemplos e restrições) e `{starter_code}` (assinatura da função a implementar). Ambos os campos são extraídos do LeetCodeDataset sem pré-processamento.

```text
Solve the following programming problem in Python.

Problem:
{problem_description}

Function signature:
{starter_code}

Requirements:
- Provide your complete solution in a single Python code block.
- Include all necessary imports at the top of the code block.
- Do not include any text or explanation outside and inside the code block.
- The function must match the signature exactly.
```

Para a fase em C++, o prompt é estruturalmente idêntico, alterando apenas as referências à linguagem-alvo: `Python` é substituído por `C++` na primeira linha e nas restantes referências ao longo do prompt.


## 4.3 Pipeline de recolha das respostas

Esta subsecção descreve como são obtidas, junto dos três modelos, as respostas a cada um dos 30 problemas da amostra.

### Procedimento de recolha

Para cada combinação (modelo × problema × linguagem), o procedimento é o seguinte:

1. Abrir uma **nova sessão de conversação** na interface web do modelo, garantindo isolamento de contexto entre problemas.
2. Colar o prompt completo (gerado a partir do template e dos campos do problema).
3. Aguardar a resposta completa do modelo.
4. Copiar o código gerado e guardá-lo num ficheiro identificado por modelo, dificuldade e problema, organizado de forma consistente para a fase de avaliação.

Esta recolha é realizada duas vezes — uma para Python e outra para C++ — totalizando 180 respostas (30 problemas × 3 modelos × 2 linguagens).

## 4.4 Pipeline de avaliação

O objectivo desta etapa é determinar, para cada par (modelo × problema), se o código gerado é correcto. A avaliação corre numa única máquina do grupo, eliminando potenciais discrepâncias entre versões de Python, de C++ ou de bibliotecas.

### 4.4.1 Avaliação Python

A test suite oficial fornecida pelo LeetCodeDataset é executada contra cada uma das 90 soluções Python recolhidas. Esta test suite cobre os exemplos mostrados no enunciado e adiciona casos de teste extra (incluindo edge cases) que validam a correcção da implementação para todo o domínio de inputs definido pelas restrições do problema.

A execução é feita por um script Python que itera pelos 90 ficheiros de resposta e, para cada um, lança a sua execução num **processo isolado** com **timeout de 30 segundos**. Este isolamento é essencial: se o código gerado contiver um loop infinito, recursão sem caso base, ou outra anomalia, o processo isolado pode ser terminado pelo timeout sem afectar o programa principal nem os restantes resultados.

### 4.4.2 Avaliação C++

A test suite original do LeetCodeDataset está apenas disponível em Python. Para a fase C++, foi gerada uma versão equivalente da test suite em C++ recorrendo a um modelo LLM de tradução (Claude Opus 4.7), seguida de um passo de validação automático: cada test suite traduzida é executada contra a solução de referência (também traduzida para C++), confirmando que todos os asserts passam. As 30 traduções foram validadas com sucesso através deste procedimento.


### 4.4.3 Critério comum

O timeout de 30 segundos foi escolhido como compromisso entre tolerância para problemas Hard com soluções correctas mas pouco optimizadas e rejeição de soluções patologicamente ineficientes.

No fim de cada execução completa do pipeline, é produzida uma matriz de 90 resultados por linguagem (30 problemas × 3 modelos), totalizando 180 resultados, prontos para análise estatística.


## 4.5 Definição operacional de "pass" e categorias de falha

Para cada par (modelo × problema), o resultado é classificado numa de cinco categorias mutuamente exclusivas:

| Categoria | Critério | Pass@1 |
|---|---|---|
| `PASS` | A execução termina sem erros, dentro do timeout, e todos os asserts da test suite passam. | 1 |
| `FAIL` | A execução termina com `AssertionError`. O código compilou, executou, mas falhou pelo menos um caso de teste. | 0 |
| `RUNTIME_ERROR` | A execução termina com qualquer outra excepção (`IndexError`, `TypeError`, `KeyError`, etc.; em C++, comportamento como segmentation fault ou access violation). | 0 |
| `SYNTAX_ERROR` | O código submetido falha em compilar (`SyntaxError`/`IndentationError` em Python; erros do compilador em C++). | 0 |
| `TIMEOUT` | A execução excede 30 segundos sem terminar. | 0 |

A variável dependente principal **Pass@1** é definida como a proporção de problemas em que o resultado é `PASS`, calculada por modelo dentro de cada linguagem.