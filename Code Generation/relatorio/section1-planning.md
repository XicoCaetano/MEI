# 1. Contexto da Tarefa: Code Generation

## 1.1 O que é Code Generation?

Code generation, no contexto de ferramentas baseadas em LLMs, refere-se à produção automática de código-fonte a partir de uma especificação em linguagem natural ou parcialmente formal. O developer descreve o problema a resolver — frequentemente acompanhado de assinatura de função, restrições e exemplos — e o modelo devolve uma implementação em código executável.

Na presente experiência, é avaliada a forma mais directa desta tarefa: **geração one-shot de uma função isolada**. Em concreto, cada modelo recebe a descrição completa de um problema (texto, exemplos de input/output e restrições), juntamente com a assinatura da função a implementar, e devolve uma única resposta com o código que considera correcto. Não há interacção iterativa, nem acesso a ferramentas externas. O modelo tem uma única tentativa para produzir uma solução funcional.


## 1.2 Relevância para uma empresa de software

A geração assistida de código tornou-se uma componente central da prática de engenharia de software empresarial. Dois indicadores ilustram a escala desta adopção:

- **90% das empresas Fortune 100** adoptaram o GitHub Copilot como ferramenta padrão de desenvolvimento [referencia: https://techcrunch.com/2025/07/30/github-copilot-crosses-20-million-all-time-users/]
- Em estudos controlados com 95 developers, a conclusão de tarefas de coding foi **55% mais rápida** com assistência de LLM. [referencia: https://arxiv.org/pdf/2302.06590]

Para uma empresa de software, esta tecnologia representa simultaneamente uma oportunidade competitiva (custos reduzidos, time-to-market acelerado) e um risco operacional (qualidade variável, dependência tecnológica). A decisão de adoptar uma ferramenta específica em vez de outra — o cenário descrito no enunciado — não é trivial: implica avaliar trade-offs entre desempenho técnico, custo e maturidade do fornecedor.


## 1.3 Como os LLMs são usados nesta experiência

Esta experiência adopta o cenário de **geração one-shot via interface conversacional**, replicando o uso que muitos developers fazem das versões web destes modelos. O fluxo é o seguinte:

1. O problema é apresentado ao modelo num prompt único, contendo a descrição completa, os exemplos e a assinatura da função esperada.
2. O modelo gera uma resposta única (sem oportunidade de iteração ou correcção).
3. O código é extraído da resposta e avaliado contra a test suite oficial do problema.
4. O resultado é binário: o código passa todos os testes ou não passa.


## 1.4 Limitações e desafios da experiência

A presente experiência apresenta limitações específicas que importa identificar antes de discutir os resultados.

### 1.4.1 Contaminação dos dados de avaliação

O principal desafio metodológico é a possível **contaminação de benchmarks**: os datasets clássicos de avaliação de LLMs foram amplamente disseminados na Internet e provavelmente integraram os corpora de treino dos modelos avaliados. Quando um modelo "resolve" um problema que viu durante o treino, a sua performance reflecte memorização e não capacidade genuína de raciocínio. Se a amostra contiver problemas conhecidos pelos modelos, deixamos de medir capacidade de geração de código e passamos a medir capacidade de recuperação de soluções memorizadas.

Para mitigar este risco, a amostra é seleccionada a partir do split de teste do LeetCodeDataset, optando pelos problemas mais recentes disponíveis (Fevereiro a Março de 2025) — todos eles posteriores ao knowledge cutoff de Janeiro de 2025 anunciado para o modelo mais recente do conjunto avaliado. Esta filtragem temporal reduz substancialmente, embora não elimine completamente, a probabilidade de contaminação.

### 1.4.2 Hallucinations em código

Mesmo em modelos de fronteira, os LLMs apresentam três classes de alucinações relevantes para esta experiência:

- **Alucinações sintácticas** — código que falha em compilar (parêntesis mal fechados, indentação inválida, output truncado).
- **Alucinações de execução** — código que compila mas falha em runtime, omissão de imports, ou referências a símbolos inexistentes.
- **Alucinações de correcção funcional** — código que compila e executa, mas produz resultado errado.

Estas três classes mapeiam-se directamente nas categorias de erro que o pipeline de avaliação irá registar (`SYNTAX_ERROR`, `RUNTIME_ERROR`, `FAIL`), enriquecendo a análise para além do simples binário pass/fail e permitindo discussão qualitativa sobre os modos de falha de cada modelo.

### 1.4.3 Ausência de acesso via API

Os três modelos avaliados (Claude Sonnet 4.6, Gemini 3.1 Pro, DeepSeek V3) são modelos comerciais de gama média-alta — categoria que representa as ferramentas efectivamente usadas por developers em ambiente profissional.

A avaliação destes modelos foi conduzida através das suas interfaces web conversacionais, e não via API. Esta opção decorre de duas restrições práticas: (i) o acesso programático via API a estes modelos é pago e implicaria custos relevantes para o número de queries necessário, e (ii) a sua execução local não é viável — Claude e Gemini são modelos proprietários sem pesos disponíveis publicamente, e o DeepSeek V3, embora open-weight, exige recursos computacionais que excedem amplamente o hardware disponível ao grupo.
Esta limitação operacional, ainda que alinhada com o cenário real de utilização individual destes modelos por developers, introduz restrições experimentais relevantes:

- **Impossibilidade de controlar parâmetros de geração** (temperatura, top-p, max-tokens), que ficam fixados pelos valores por defeito de cada interface.
- **Recolha manual de respostas**: o pipeline experimental não pode ser totalmente automatizado, exigindo introdução manual de cada prompt e cópia da resposta correspondente.
- **Variabilidade não controlada** introduzida pela infraestrutura conversacional (system prompts ocultos, possíveis filtros de conteúdo, formatação aplicada pela UI).

Estas limitações reflectem fielmente o cenário típico de utilização individual destes modelos e devem ser discutidas como ameaças à validade interna da experiência..