## 7. Discussão

A presente secção interpreta os resultados estatísticos da Secção 6 à luz dos dados descritivos da Secção 5, responde às research questions formuladas na Secção 2, e apresenta a recomendação de adopção ao CTO.

### 7.1 Resposta às Research Questions

**RQ1 — Existe diferença significativa na capacidade de geração de código correcto, à primeira tentativa, entre os três modelos LLM avaliados, quando considerados os resultados agregados em Python e C++?**

Sim. Duas das três comparações pareadas ao nível agregado atingem significância estatística ao nível α = 0.20: Claude vs DeepSeek (p = 0.143) e Gemini vs DeepSeek (p = 0.143). Existe evidência estatística de que o DeepSeek apresenta desempenho inferior a Claude e a Gemini na geração de código à primeira tentativa. Não é possível, contudo, distinguir estatisticamente entre Claude e Gemini (p = 1.000), que apresentam desempenho agregado idêntico (61.67% cada).

**RQ2 — O ranking de desempenho entre os modelos mantém-se consistente quando os resultados são analisados por linguagem (Python vs. C++), ou existem inversões de performance dependentes da linguagem alvo?**

A análise por linguagem revela um padrão de **inversão parcial** no ranking dos modelos. Em Python, Gemini é o único modelo estatisticamente superior ao DeepSeek (p = 0.184), enquanto Claude não se distingue significativamente de nenhum dos outros dois. Em C++, é Claude que se destaca como estatisticamente superior ao DeepSeek (p = 0.120), enquanto Gemini perde a posição de liderança e não se distingue significativamente de nenhum dos restantes modelos.

O resultado central desta experiência não é a superioridade de um modelo individual, mas a **dependência do desempenho relativamente à linguagem alvo**. Claude e Gemini atingem a mesma Pass@1 agregada (61.67%) por caminhos opostos: Gemini destaca-se em Python (70.0%) mas degrada-se acentuadamente em C++ (53.3%, −16.67 pp), enquanto Claude mantém desempenho estável entre linguagens (+3.33 pp) e lidera em C++ (63.3%). O DeepSeek mantém a posição mais baixa em ambas as linguagens, com a distância para os outros modelos a acentuar-se em C++ (43.3%).

A análise dos modos de falha (Secção 5) fornece uma explicação possível para esta inversão. A degradação do Gemini em C++ é impulsionada por erros de compilação (9 de 14 falhas em C++ são `SYNTAX_ERROR`), sugerindo que a sua qualidade de geração é mais sensível à complexidade sintáctica e aos requisitos de tipagem estática do C++. Claude, em contraste, distribui as suas falhas de forma mais equilibrada entre categorias e não exibe esta vulnerabilidade específica a uma linguagem. O DeepSeek falha predominantemente por erros lógicos (`FAIL`: 19 de 31 falhas totais) — gera código que compila e executa, mas que não resolve correctamente o problema — um padrão que sugere menor capacidade de raciocínio algorítmico.

### 7.2 Recomendação ao CTO

Com base nos resultados experimentais, apresenta-se a seguinte recomendação:

**Nenhum modelo domina em ambas as linguagens.** Claude e Gemini são estatisticamente indistinguíveis ao nível agregado, e ambos são significativamente superiores ao DeepSeek. A escolha entre Claude e Gemini deve, portanto, depender do contexto tecnológico da organização:

- Para equipas que trabalham **predominantemente em Python**, Gemini (70.0% Pass@1) é o candidato mais forte, com a única vantagem estatisticamente confirmada sobre o DeepSeek nesta linguagem.
- Para equipas que trabalham **predominantemente em C++**, Claude é a escolha mais segura: lidera em C++ (63.3%), é o único modelo com desempenho estável entre linguagens, e apresenta o perfil de falhas mais equilibrado.
- **O DeepSeek não é recomendado** para adopção como ferramenta principal de geração de código em nenhuma das linguagens, dado o seu desempenho significativamente inferior ao nível agregado e o seu modo de falha predominante de erros lógicos.
