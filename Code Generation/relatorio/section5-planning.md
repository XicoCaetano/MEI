# 5. Recolha de Resultados

## 5.1 Visão geral

Esta secção apresenta os resultados obtidos pela aplicação do protocolo experimental descrito na secção 4. Seguindo a estrutura definida nas hipóteses, os resultados são reportados em três níveis: (i) desempenho agregado entre as duas linguagens ($n=60$), (ii) desempenho isolado por linguagem ($n=30$) e (iii) análise qualitativa dos modos de falha. A apresentação é puramente descritiva, servindo de base para a análise inferencial apresentada na secção 6.

## 5.2 Resultados Agregados (ambas as linguagens)

Esta análise combina os resultados obtidos em Python e C++ para fornecer uma visão do desempenho geral de cada modelo através de 60 problemas de programação.

### Pass@1 Agregada por Modelo

| Modelo | Total PASS | Pass@1 (Agregada) |
|---|---|---|
| Claude | 37/60 | 61.67% |
| Gemini | 37/60 | 61.67% |
| DeepSeek | 29/60 | 48.33% |

A nível agregado, observa-se um equilíbrio exato entre o **Claude** e o **Gemini**, ambos com uma taxa de sucesso de 61,67%. O **DeepSeek** apresenta um desempenho inferior, situando-se abaixo da barreira dos 50%. Esta visão agregada, no entanto, oculta variações significativas de performance que ocorrem quando se isola cada linguagem de programação.

## 5.3 Resultados em Python

### Pass@1 por modelo e dificuldade

| Modelo | Total PASS | Pass@1 | Easy | Medium | Hard |
|---|---|---|---|---|---|
| Claude | 18/30 | 60.00% | 10/10 | 4/10 | 4/10 |
| Gemini | 21/30 | 70.00% | 10/10 | 7/10 | 4/10 |
| DeepSeek | 16/30 | 53.33% | 9/10 | 5/10 | 2/10 |

### Distribuição das categorias

| Modelo | PASS | FAIL | SYNTAX_ERROR | RUNTIME_ERROR | TIMEOUT |
|---|---|---|---|---|---|
| Claude | 18 | 8 | 0 | 4 | 0 |
| Gemini | 21 | 4 | 0 | 4 | 1 |
| DeepSeek | 16 | 9 | 1 | 4 | 0 |

Em Python, o **Gemini** apresentou o melhor desempenho individual da experiência, com uma Pass@1 de 70%. A análise por dificuldade revela que o cenário *Easy* foi resolvido quase na totalidade por todos os modelos. As diferenças tornam-se nítidas no nível *Medium*, onde o Gemini (7/10) superou o Claude (4/10) e o DeepSeek (5/10). No nível *Hard*, Claude e Gemini empatam, enquanto o DeepSeek demonstra maior dificuldade (2/10).

A análise das categorias de falha mostra que nenhum modelo apresentou erros sintácticos significativos em Python: zero casos em Claude e Gemini, e apenas um caso no DeepSeek. O modo de falha dominante foi `FAIL` (assert falhado), ou seja, os modelos geraram código que corre mas que não respeita totalmente a especificação do problema.

## 5.4 Resultados em C++

### Pass@1 por modelo e dificuldade

| Modelo | Total PASS | Pass@1 | Easy | Medium | Hard |
|---|---|---|---|---|---|
| Claude | 19/30 | 63.33% | 10/10 | 4/10 | 5/10 |
| Gemini | 16/30 | 53.33% | 10/10 | 3/10 | 3/10 |
| DeepSeek | 13/30 | 43.33% | 9/10 | 3/10 | 1/10 |

### Distribuição das categorias

| Modelo | PASS | FAIL | SYNTAX_ERROR | RUNTIME_ERROR | TIMEOUT |
|---|---|---|---|---|---|
| Claude | 19 | 4 | 6 | 1 | 0 |
| Gemini | 16 | 3 | 9 | 2 | 0 |
| DeepSeek | 13 | 10 | 5 | 1 | 1 |

Em C++, o ranking inverte-se face ao observado em Python: o **Claude** assume a liderança com 63,33%, seguido pelo **Gemini** (53,33%) e pelo **DeepSeek** (43,33%). O Claude destaca-se particularmente nos problemas *Hard*, resolvendo metade da amostra (5/10), enquanto o DeepSeek revela uma degradação severa neste estrato, conseguindo apenas 1 solução correcta em 10.

A análise das categorias de falha revela um padrão distinto do observado em Python. Erros de compilação (`SYNTAX_ERROR`) tornam-se relevantes nas três famílias de modelos, com particular incidência no Gemini (9 casos) e no Claude (6 casos), reflectindo a maior complexidade sintáctica e a tipagem estática do C++. O modo de falha `FAIL` continua presente, sobretudo no DeepSeek (10 casos).

## 5.5 Comparação de Desempenho entre Linguagens

A tabela seguinte sintetiza a variação de desempenho entre Python e C++, evidenciando a consistência de cada modelo:

| Modelo | Pass@1 Python | Pass@1 C++ | Δ (C++ – Python) |
|---|---|---|---|
| Claude | 60.00% | 63.33% | +3.33 pp |
| Gemini | 70.00% | 53.33% | −16.67 pp |
| DeepSeek | 53.33% | 43.33% | −10.00 pp |

O **Claude** revela-se o modelo mais estável, sendo o único a apresentar uma ligeira melhoria na transição para C++. Em contraste, o **Gemini** sofre a maior queda de desempenho (−16,67 pp), perdendo a posição de liderança que detinha em Python. O **DeepSeek** apresenta uma degradação intermédia (−10 pp), mantendo a posição mais baixa nas duas linguagens.

## 5.6 Análise Qualitativa dos Modos de Falha

Para uma visão integrada dos perfis de erro de cada modelo, a tabela seguinte agrega as categorias de resultado entre as duas linguagens (180 respostas no total):

| Modelo | PASS | FAIL (Lógica) | SYNTAX | RUNTIME | TIMEOUT |
|---|---|---|---|---|---|
| Claude | 37 | 12 | 6 | 5 | 0 |
| Gemini | 37 | 7 | 9 | 6 | 1 |
| DeepSeek | 29 | 19 | 6 | 5 | 1 |

A análise qualitativa indica perfis de erro distintos entre os três modelos:

* O **DeepSeek** falha predominantemente por `FAIL` (erros de lógica funcional, 19 casos em 31 falhas), indicando que gera código que compila e executa, mas que não resolve correctamente o problema proposto.
* O **Gemini** apresenta a maior proporção relativa de `SYNTAX_ERROR` entre as suas falhas (9 em 23, cerca de 39%), sugerindo que a complexidade sintáctica do C++ é o seu maior desafio.
* O **Claude** revela uma distribuição mais equilibrada entre os modos de falha, sem um padrão de erro dominante.
* Erros de execução (`RUNTIME_ERROR`) e interrupções por tempo (`TIMEOUT`) foram residuais e distribuídos de forma equilibrada entre os modelos.