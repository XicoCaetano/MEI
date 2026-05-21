# 3. Hipóteses

A presente experiência testa hipóteses organizadas em dois níveis: primeiro uma análise agregada que combina os resultados das duas linguagens, e depois uma análise específica por linguagem. Esta estrutura permite identificar o modelo mais fiável globalmente e, em seguida, investigar se existem variações de desempenho dependendo da linguagem alvo.

As comparações entre os modelos são realizadas através de **comparações pareadas**, de forma a identificar diferenças estatisticamente significativas entre cada par de ferramentas avaliadas.

## 3.1 Comparação agregada de modelos (ambas as linguagens)

Esta análise investiga se existe um modelo dominante quando se consideram os resultados das duas linguagens em conjunto. Esta visão responde à questão prática de qual o modelo com melhor desempenho geral para a organização.

* **H0_overall_CG** — Claude e Gemini têm igual Pass@1 considerando ambas as linguagens (Python e C++).
* **H1_overall_CG** — Claude e Gemini diferem em Pass@1 considerando ambas as linguagens.

* **H0_overall_CD** — Claude e DeepSeek têm igual Pass@1 considerando ambas as linguagens (Python e C++).
* **H1_overall_CD** — Claude e DeepSeek diferem em Pass@1 considerando ambas as linguagens.

* **H0_overall_GD** — Gemini e DeepSeek têm igual Pass@1 considerando ambas as linguagens (Python e C++).
* **H1_overall_GD** — Gemini e DeepSeek diferem em Pass@1 considerando ambas as linguagens.

## 3.2 Hipóteses Específicas por Linguagem

Após a análise agregada, as hipóteses seguintes verificam se o ranking dos modelos se mantém consistente ou se existem inversões de performance específicas a cada linguagem.

### 3.2.1 Modelos em Python

* **H0_py_CG** — Claude e Gemini têm igual Pass@1 em Python.
* **H1_py_CG** — Claude e Gemini diferem em Pass@1 em Python.

* **H0_py_CD** — Claude e DeepSeek têm igual Pass@1 em Python.
* **H1_py_CD** — Claude e DeepSeek diferem em Pass@1 em Python.

* **H0_py_GD** — Gemini e DeepSeek têm igual Pass@1 em Python.
* **H1_py_GD** — Gemini e DeepSeek diferem em Pass@1 em Python.

### 3.2.2 Modelos em C++

* **H0_cpp_CG** — Claude e Gemini têm igual Pass@1 em C++.
* **H1_cpp_CG** — Claude e Gemini diferem em Pass@1 em C++.

* **H0_cpp_CD** — Claude e DeepSeek têm igual Pass@1 em C++.
* **H1_cpp_CD** — Claude e DeepSeek diferem em Pass@1 em C++.

* **H0_cpp_GD** — Gemini e DeepSeek têm igual Pass@1 em C++.
* **H1_cpp_GD** — Gemini e DeepSeek diferem em Pass@1 em C++.