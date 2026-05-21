# 6. Aplicação do Método Estatístico

Esta secção aplica os testes estatísticos apropriados às hipóteses formuladas na Secção 3. Para as comparações entre modelos é utilizado o **two-proportion z-test**, adequado para comparar duas proporções amostrais independentes — neste caso, as taxas de Pass@1 de cada par de modelos. O teste avalia se a diferença observada entre as proporções de sucesso de dois modelos é estatisticamente significativa ou se é atribuível à variabilidade amostral.

Em todos os testes, é adoptado um nível de significância de $\alpha = 0.20$ (80% de confiança) com formulação **bilateral** (não-direccional). 

## 6.1 Two-proportion z-test — fórmula geral

Para comparar dois modelos A e B com $n$ problemas para cada modelo:

**Proporções amostrais:**
$$\hat{p}_A = \frac{x_A}{n}, \quad \hat{p}_B = \frac{x_B}{n}$$

**Proporção combinada:**
$$\hat{p} = \frac{x_A + x_B}{2n}$$

**Estatística do teste:**
$$z = \frac{\hat{p}_A - \hat{p}_B}{\sqrt{\hat{p}(1 - \hat{p}) \left(\frac{1}{n} + \frac{1}{n}\right)}}$$

**P-value (teste bilateral):**
$$\text{p-value} = 2 \times P(Z \geq |z|)$$

onde $Z$ segue a distribuição normal padrão.


## 6.2 Comparação Agregada de Modelos (ambas as linguagens)

Para as comparações agregadas, os resultados binários obtidos em Python (30 problemas) e C++ (30 problemas) são combinados, resultando em $n = 60$ observações por modelo. Esta análise fornece uma visão global do desempenho de cada modelo, independentemente da linguagem alvo.

| Comparação | $\hat{p}_A$ | $\hat{p}_B$ | $z$ | p-value | Decisão  |
| :--- | :---: | :---: | :---: | :---: | :---: |
| H_overall_CG (Claude vs Gemini) | 0.6167 | 0.6167 | 0.000 | 1.000 | Não rejeita H0 |
| H_overall_CD (Claude vs DeepSeek) | 0.6167 | 0.4833 | +1.466 | 0.143 | **Rejeita H0** |
| H_overall_GD (Gemini vs DeepSeek) | 0.6167 | 0.4833 | +1.466 | 0.143 | **Rejeita H0** |

Quando ambas as linguagens são agregadas, a igualdade exacta entre Claude e Gemini (37/60 cada) impede qualquer distinção entre estes dois modelos (p = 1.000). As comparações de Claude e Gemini contra o DeepSeek atingem significância estatística ao nível $\alpha = 0.20$ (p = 0.143 em ambos os casos), permitindo concluir que existe evidência estatística de diferença entre estes modelos e o DeepSeek ao nível agregado.


## 6.3 Hipóteses Específicas: Modelos em Python

As subsecções seguintes aplicam o mesmo two-proportion z-test às comparações pareadas restritas a Python, com $n = 30$ problemas por modelo.

| Comparação | $\hat{p}_A$ | $\hat{p}_B$ | $z$ | p-value | Decisão ($\alpha=0.20$) |
| :--- | :---: | :---: | :---: | :---: | :---: |
| H_py_CG (Claude vs Gemini) | 0.6000 | 0.7000 | −0.812 | 0.417 | Não rejeita H0 |
| H_py_CD (Claude vs DeepSeek) | 0.6000 | 0.5333 | +0.521 | 0.602 | Não rejeita H0 |
| H_py_GD (Gemini vs DeepSeek) | 0.7000 | 0.5333 | +1.328 | 0.184 | **Rejeita H0** |

Em Python, apenas a comparação Gemini vs DeepSeek atinge significância estatística (p = 0.184 < 0.20), confirmando que Gemini apresenta desempenho significativamente superior ao DeepSeek nesta linguagem. As restantes comparações não atingem significância: a diferença de 10 pp entre Claude e Gemini (p = 0.417) e de 6.67 pp entre Claude e DeepSeek (p = 0.602) são consistentes com a variabilidade amostral.


## 6.4 Hipóteses Específicas: Modelos em C++

À semelhança da análise em Python, as subsecções seguintes aplicam o two-proportion z-test às comparações pareadas restritas a C++, igualmente com $n = 30$ problemas por modelo.

| Comparação | $\hat{p}_A$ | $\hat{p}_B$ | $z$ | p-value | Decisão ($\alpha=0.20$) |
| :--- | :---: | :---: | :---: | :---: | :---: |
| H_cpp_CG (Claude vs Gemini) | 0.6333 | 0.5333 | +0.786 | 0.432 | Não rejeita H0 |
| H_cpp_CD (Claude vs DeepSeek) | 0.6333 | 0.4333 | +1.553 | 0.120 | **Rejeita H0** |
| H_cpp_GD (Gemini vs DeepSeek) | 0.5333 | 0.4333 | +0.775 | 0.438 | Não rejeita H0 |

Em C++, apenas a comparação Claude vs DeepSeek atinge significância estatística (p = 0.120 < 0.20), confirmando que Claude apresenta desempenho significativamente superior ao DeepSeek nesta linguagem. As restantes comparações não atingem significância: a diferença de 10 pp entre Claude e Gemini (p = 0.432) e entre Gemini e DeepSeek (p = 0.438) são consistentes com a variabilidade amostral.


