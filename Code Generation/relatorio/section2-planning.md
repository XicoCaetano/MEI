# 2. Perguntas e Variáveis

## 2.1 Research Questions

A questão de investigação principal desta experiência decorre directamente do problema colocado pelo CTO no enunciado, instanciado para a tarefa de code generation:

> **RQ1 — Existe diferença significativa na capacidade de geração de código correcto, à primeira tentativa, entre os três modelos LLM avaliados (Claude Sonnet 4.6, Gemini 3.1 Pro, DeepSeek V3), quando considerados os resultados agregados em Python e C++?**

A RQ1 identifica o modelo mais fiável a nível global, considerando o desempenho conjunto nas duas linguagens cobertas pela experiência. A resposta a esta questão constitui a base para a recomendação de adopção a apresentar ao CTO.

Decorre desta uma questão complementar, focada na consistência do desempenho entre linguagens:

> **RQ2 — O ranking de desempenho entre os modelos mantém-se consistente quando os resultados são analisados por linguagem (Python vs. C++), ou existem inversões de performance dependentes da linguagem alvo?**

A RQ2 verifica se a recomendação derivada da RQ1 deve ser ajustada consoante a linguagem predominante na empresa. Um modelo pode apresentar bom desempenho global mas degradar-se numa linguagem específica — informação relevante para decisões de adopção em organizações com stack tecnológico heterogéneo.

A resposta a ambas as questões é construída a partir de comparações pareadas entre cada par de modelos, em três níveis de análise: agregado (Python + C++), Python isoladamente, e C++ isoladamente (ver secção 3).



## 2.2 Variáveis Independentes

A experiência manipula três variáveis independentes, sendo o **modelo LLM** a variável independente principal e as restantes (**dificuldade do problema** e **linguagem de programação**) factores adicionais que permitem analisar o desempenho dos modelos sob diferentes condições.

### 2.2.1 Modelo LLM (variável independente principal)

Variável categórica com três níveis: **Claude Sonnet 4.6**, **Gemini 3.1 Pro** e **DeepSeek V3**. A selecção destes três modelos teve como critério a representatividade do uso real: trata-se de três modelos comerciais de gama média-alta, acessíveis através de interfaces web com tier gratuito, e provenientes de fornecedores distintos (Anthropic, Google, DeepSeek),


### 2.2.2 Dificuldade do problema

Variável categórica com três níveis, definidos de acordo com a classificação oficial do LeetCode: **Easy**, **Medium**, **Hard**. A amostra é estratificada de forma equilibrada, com 10 problemas por nível, totalizando 30 problemas.

A inclusão deste factor permite avaliar não apenas o desempenho global de cada modelo, mas também a sua robustez face a problemas de complexidade crescente — informação relevante para a decisão de adopção, dado que um modelo pode ter desempenho competitivo em problemas simples mas degradar-se em cenários mais exigentes.

### 2.2.3 Linguagem de programação

Variável categórica com dois níveis: **Python** e **C++**.

A escolha destas duas linguagens cobre um espectro relevante para uma empresa de software: Python representa as linguagens de alto nível, com tipagem dinâmica, amplamente utilizadas em data science, scripting e desenvolvimento web; C++ representa as linguagens de baixo-nível, com tipagem estática, utilizadas em sistemas críticos, motores de jogo e aplicações com requisitos de performance.

Os mesmos 30 problemas são avaliados em ambas as linguagens, permitindo isolar o efeito da linguagem (para o mesmo modelo, sobre o mesmo problema) sem o confundir com diferenças entre conjuntos de problemas.


## 2.3 Variáveis Dependentes

A variável dependente principal é a **correcção funcional do código gerado**, operacionalizada através da métrica **Pass@1**.

**Definição operacional de Pass@1.** Para cada par (problema, modelo), é calculado um valor binário:

- **1** — o código gerado pelo modelo passa todos os casos de teste oficiais do problema, à primeira tentativa.
- **0** — caso contrário.

A Pass@1 do modelo é calculada como a média desses valores binários sobre os 30 problemas da amostra, podendo ser apresentada de forma global ou estratificada por nível de dificuldade.

O que se pretende medir é a probabilidade de o developer obter código funcional do modelo sem necessidade de revisão ou regeneração — ou seja, a fiabilidade do output em cenário de uso real, alinhada com a questão de "reliability" colocada pelo CTO. A Pass@1 operacionaliza directamente este conceito ao reportar a proporção de problemas em que o modelo, à primeira tentativa, produz código que satisfaz os critérios de correcção definidos pela test suite oficial.

O pipeline de avaliação regista, adicionalmente, a categoria de falha em cada caso negativo. Esta informação não constitui variável dependente principal, mas será utilizada na análise qualitativa dos modos de falha. As categorias são:

- `SYNTAX_ERROR` — código não compila;
- `RUNTIME_ERROR` — exceção durante a execução;
- `TIMEOUT` — execução excede 30 segundos;
- `FAIL` — código corre sem erros mas falha pelo menos um caso de teste.


## 2.4 Variáveis Controladas

Para isolar o efeito das variáveis independentes, as seguintes variáveis são mantidas constantes ao longo de toda a experiência:

**Conjunto de problemas.** Os 30 problemas seleccionados são exactamente os mesmos para os três modelos. Cada modelo é avaliado contra a mesma amostra, garantindo paired design (medições pareadas por problema).

**Prompt template.** O prompt enviado a cada modelo é idêntico, palavra por palavra, alterando apenas o conteúdo do problema e a indicação da linguagem alvo. O template explicita a assinatura da função esperada e o formato da resposta.

**Formato de input.** Cada problema é apresentado na forma completa fornecida pelo dataset — descrição em linguagem natural, exemplos de input/output e restrições — sem qualquer pré-processamento ou edição pelo experimentador.

**Número de tentativas.** Cada problema é apresentado a cada modelo uma única vez. Não são permitidas regenerações nem follow-up turns.

**Isolamento de contexto.** Cada interacção com cada modelo decorre numa sessão conversacional independente, sem histórico de problemas anteriores, eliminando o efeito de contaminação cross-prompt dentro da mesma sessão.