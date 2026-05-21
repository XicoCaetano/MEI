# ANOVA Calculations — Code Explanation Quality Study
**Significance level: α = 0.20 (80% confidence)**  
**Scale: 0–20 | N = 180 observations**

---

## Formulas Reference

| Formula | Expression |
|---------|-----------|
| Sample Mean | $\bar{X} = \sum X_i / n$ |
| Sample Variance | $s^2 = \sum(X_i - \bar{X})^2 / (n-1)$ |
| Standard Deviation | $s = \sqrt{s^2}$ |
| Grand Mean | $GM = \sum n_i \bar{x}_i / \sum n_i$ |
| SS(B) | $\sum n_i(\bar{X}_i - GM)^2$ |
| SS(W) | $\sum df_i \cdot s^2_i$ |
| SS(T) | $SS(B) + SS(W)$ |
| MS(B) | $SS(B) / (k-1)$ |
| MS(W) | $SS(W) / (n-k)$ |
| F | $MS(B) / MS(W)$ |
| SS(AxB) | $SS(M) - SS(A) - SS(B)$ |

---

## H1 — One-Way ANOVA — Effect of Model

### Step 1 — Sample Characteristics

| Model | n | Mean (X̄) | s | s² |
|-------|---|----------|---|-----|
| Claude Sonnet 4.6 | 60 | 17.533 | 0.650 | 0.423 |
| DeepSeek V3 | 60 | 16.617 | 0.922 | 0.851 |
| Gemini 3 Flash | 60 | 14.850 | 0.777 | 0.604 |

**k = 3, n = 60 per group, N = 180**

**Assumption check** — ratio of largest to smallest standard deviation must be < 2:1:

$$\frac{s_{max}}{s_{min}} = \frac{0.922}{0.650} = 1.42 < 2 \checkmark$$

### Step 2 — Grand Mean

$$GM = \frac{\sum n_i \bar{x}_i}{\sum n_i} = \frac{60 \times 17.533 + 60 \times 16.617 + 60 \times 14.850}{180}$$

$$GM = \frac{1051.98 + 997.02 + 891.00}{180} = \frac{2940.00}{180} = \boxed{16.333}$$

### Step 3 — SS(B) Between-Group Sum of Squares

$$SS(B) = \sum n_i(\bar{X}_i - GM)^2$$

- **Claude:** $60 \times (17.533 - 16.333)^2 = 60 \times (1.200)^2 = 60 \times 1.440 = 86.400$
- **DeepSeek:** $60 \times (16.617 - 16.333)^2 = 60 \times (0.284)^2 = 60 \times 0.081 = 4.840$
- **Gemini:** $60 \times (14.850 - 16.333)^2 = 60 \times (-1.483)^2 = 60 \times 2.199 = 131.993$

$$SS(B) = 86.400 + 4.840 + 131.993 = \boxed{223.233}$$

### Step 4 — SS(W) Within-Group Sum of Squares

$$SS(W) = \sum df_i \cdot s^2_i$$

- **Claude:** $(60-1) \times 0.423 = 59 \times 0.423 = 24.957$
- **DeepSeek:** $(60-1) \times 0.851 = 59 \times 0.851 = 50.209$
- **Gemini:** $(60-1) \times 0.604 = 59 \times 0.604 = 35.636$

$$SS(W) = 24.957 + 50.209 + 35.636 = \boxed{110.802}$$

**Verification:** $SS(T) = 223.233 + 110.802 = 334.035 \approx 333.999$ ✓

### Step 5 — MS and F

$$MS(B) = \frac{SS(B)}{k-1} = \frac{223.233}{2} = 111.617$$

$$MS(W) = \frac{SS(W)}{N-k} = \frac{110.802}{177} = 0.626$$

$$F = \frac{MS(B)}{MS(W)} = \frac{111.617}{0.626} = \boxed{178.358}$$

### Step 6 — ANOVA Table

| | SS | df | MS | F | P |
|--|-----|----|----|---|---|
| **Between** | 223.233 | k−1 = 2 | 223.233/2 = 111.617 | 111.617/0.626 = 178.358 | Tail area above F = **< 0.001** |
| **Within** | 110.767 | n−k = 177 | 110.767/177 = 0.626 | | |
| **Total** | 333.999 | n−1 = 179 | | | |

### Step 7 — Decision

- **F_crit** (α = 0.20, df = 2, 177) = **1.624**
- **p-value = < 0.001**

$$F = 178.358 \gg F_{crit} = 1.624 \quad \text{and} \quad p < 0.001 < \alpha = 0.20$$

**→ H0 is Rejected.**

Post-hoc Tukey HSD confirms all pairwise comparisons significant:  
**Claude (17.53) > DeepSeek (16.62) > Gemini (14.85)**

---

## H2 — One-Way ANOVA — Effect of Programming Language

### Step 1 — Sample Characteristics

| Language | n | Mean (X̄) | s | s² |
|----------|---|----------|---|-----|
| Python | 90 | 16.511 | 1.309 | 1.713 |
| C++ | 90 | 16.156 | 1.406 | 1.976 |

**k = 2, n = 90 per group, N = 180**

**Assumption check:**

$$\frac{s_{max}}{s_{min}} = \frac{1.406}{1.309} = 1.07 < 2 \checkmark$$

### Step 2 — Grand Mean

$$GM = \frac{90 \times 16.511 + 90 \times 16.156}{180} = \frac{1485.99 + 1454.04}{180} = \frac{2940.03}{180} = \boxed{16.333}$$

### Step 3 — SS(B)

$$SS(B) = \sum n_i(\bar{X}_i - GM)^2$$

- **Python:** $90 \times (16.511 - 16.333)^2 = 90 \times (0.178)^2 = 90 \times 0.0317 = 2.844$
- **C++:** $90 \times (16.156 - 16.333)^2 = 90 \times (-0.177)^2 = 90 \times 0.0314 = 2.844$

$$SS(B) = 2.844 + 2.844 = \boxed{5.689}$$

### Step 4 — SS(W)

$$SS(W) = \sum df_i \cdot s^2_i$$

- **Python:** $89 \times 1.713 = 152.457$
- **C++:** $89 \times 1.976 = 175.864$

$$SS(W) = 152.457 + 175.864 = \boxed{328.321}$$

**Verification:** $SS(T) = 5.689 + 328.321 = 334.010 \approx 333.999$ ✓

### Step 5 — MS and F

$$MS(B) = \frac{SS(B)}{k-1} = \frac{5.689}{1} = 5.689$$

$$MS(W) = \frac{SS(W)}{N-k} = \frac{328.321}{178} = 1.845$$

$$F = \frac{MS(B)}{MS(W)} = \frac{5.689}{1.845} = \boxed{3.084}$$

### Step 6 — ANOVA Table

| | SS | df | MS | F | P |
|--|-----|----|----|---|---|
| **Between** | 5.689 | k−1 = 1 | 5.689/1 = 5.689 | 5.689/1.845 = 3.084 | Tail area above F = **0.081** |
| **Within** | 328.311 | n−k = 178 | 328.311/178 = 1.845 | | |
| **Total** | 333.999 | n−1 = 179 | | | |

### Step 7 — Decision

- **F_crit** (α = 0.20, df = 1, 178) = **1.655**
- **p-value = 0.081**

$$F = 3.084 > F_{crit} = 1.655 \quad \text{and} \quad p = 0.081 < \alpha = 0.20$$

**→ H0 is Rejected.**  
Models perform significantly better in Python (M = 16.51) than in C++ (M = 16.16).

---

## H3 — One-Way ANOVA — Effect of Function Complexity

### Step 1 — Sample Characteristics

| Complexity | n | Mean (X̄) | s | s² |
|------------|---|----------|---|-----|
| Easy | 60 | 16.400 | 1.532 | 2.346 |
| Medium | 60 | 16.333 | 1.188 | 1.412 |
| Hard | 60 | 16.267 | 1.376 | 1.894 |

**k = 3, n = 60 per group, N = 180**

**Assumption check:**

$$\frac{s_{max}}{s_{min}} = \frac{1.532}{1.188} = 1.29 < 2 \checkmark$$

### Step 2 — Grand Mean

$$GM = \frac{60 \times 16.400 + 60 \times 16.333 + 60 \times 16.267}{180} = \frac{2940.00}{180} = \boxed{16.333}$$

### Step 3 — SS(B)

$$SS(B) = \sum n_i(\bar{X}_i - GM)^2$$

- **Easy:** $60 \times (16.400 - 16.333)^2 = 60 \times (0.067)^2 = 60 \times 0.00449 = 0.267$
- **Medium:** $60 \times (16.333 - 16.333)^2 = 60 \times 0 = 0$
- **Hard:** $60 \times (16.267 - 16.333)^2 = 60 \times (-0.066)^2 = 60 \times 0.00436 = 0.267$

$$SS(B) = 0.267 + 0 + 0.267 = \boxed{0.533}$$

### Step 4 — SS(W)

$$SS(W) = \sum df_i \cdot s^2_i$$

- **Easy:** $59 \times 2.346 = 138.414$
- **Medium:** $59 \times 1.412 = 83.308$
- **Hard:** $59 \times 1.894 = 111.746$

$$SS(W) = 138.414 + 83.308 + 111.746 = \boxed{333.467}$$

**Verification:** $SS(T) = 0.533 + 333.467 = 334.000 \approx 333.999$ ✓

### Step 5 — MS and F

$$MS(B) = \frac{0.533}{2} = 0.267$$

$$MS(W) = \frac{333.467}{177} = 1.884$$

$$F = \frac{0.267}{1.884} = \boxed{0.142}$$

### Step 6 — ANOVA Table

| | SS | df | MS | F | P |
|--|-----|----|----|---|---|
| **Between** | 0.533 | k−1 = 2 | 0.533/2 = 0.267 | 0.267/1.884 = 0.142 | Tail area above F = **0.868** |
| **Within** | 333.467 | n−k = 177 | 333.467/177 = 1.884 | | |
| **Total** | 333.999 | n−1 = 179 | | | |

### Step 7 — Decision

- **F_crit** (α = 0.20, df = 2, 177) = **1.624**
- **p-value = 0.868**

$$F = 0.142 \ll F_{crit} = 1.624 \quad \text{and} \quad p = 0.868 > \alpha = 0.20$$

**→ H0 is Not Rejected.**  
No significant difference across Easy (16.40), Medium (16.33) and Hard (16.27).

---

## H4 — Two-Way ANOVA — Model × Language Interaction

### Step 1 — Cell Means (n = 30 per cell)

| Model | Python (X̄) | C++ (X̄) | Marginal Mean |
|-------|-----------|---------|---------------|
| Claude Sonnet 4.6 | 17.633 | 17.433 | 17.533 |
| DeepSeek V3 | 16.867 | 16.367 | 16.617 |
| Gemini 3 Flash | 15.033 | 14.667 | 14.850 |
| **Marginal Mean** | **16.511** | **16.156** | **16.333** |

**GM = 16.333 | a = 3 models | b = 2 languages | N = 180**

### Step 2 — SS(A) Effect of Model (n per marginal = 60)

$$SS(A) = \sum 60(\bar{X}_i - GM)^2$$

- Claude: $60 \times (17.533 - 16.333)^2 = 60 \times 1.440 = 86.400$
- DeepSeek: $60 \times (16.617 - 16.333)^2 = 60 \times 0.081 = 4.840$
- Gemini: $60 \times (14.850 - 16.333)^2 = 60 \times 2.199 = 131.993$

$$SS(A) = 86.400 + 4.840 + 131.993 = \boxed{223.233}$$

### Step 3 — SS(B) Effect of Language (n per marginal = 90)

$$SS(B) = \sum 90(\bar{X}_j - GM)^2$$

- Python: $90 \times (16.511 - 16.333)^2 = 90 \times 0.0317 = 2.844$
- C++: $90 \times (16.156 - 16.333)^2 = 90 \times 0.0314 = 2.844$

$$SS(B) = 2.844 + 2.844 = \boxed{5.689}$$

### Step 4 — SS(M) All Cells Combined (n per cell = 30)

$$SS(M) = \sum 30(\bar{X}_{ij} - GM)^2$$

- Claude/Python: $30 \times (17.633 - 16.333)^2 = 30 \times 1.690 = 50.700$
- Claude/C++: $30 \times (17.433 - 16.333)^2 = 30 \times 1.210 = 36.300$
- DeepSeek/Python: $30 \times (16.867 - 16.333)^2 = 30 \times 0.285 = 8.547$
- DeepSeek/C++: $30 \times (16.367 - 16.333)^2 = 30 \times 0.00116 = 0.034$
- Gemini/Python: $30 \times (15.033 - 16.333)^2 = 30 \times 1.690 = 50.700$
- Gemini/C++: $30 \times (14.667 - 16.333)^2 = 30 \times 2.778 = 83.334$

$$SS(M) = 50.700 + 36.300 + 8.547 + 0.034 + 50.700 + 83.334 = \boxed{229.600}$$

### Step 5 — SS(A×B) Interaction

$$SS(A \times B) = SS(M) - SS(A) - SS(B) = 229.600 - 223.233 - 5.689 = \boxed{0.678}$$

### Step 6 — SS(W) Within-Group Error

$$SS(W) = \sum(n_{ij} - 1) \times s^2_{ij} = \boxed{104.400}$$

### Step 7 — Degrees of Freedom

| Source | df |
|--------|----|
| Factor A (Model) | a−1 = 3−1 = **2** |
| Factor B (Language) | b−1 = 2−1 = **1** |
| Interaction A×B | (a−1)(b−1) = 2×1 = **2** |
| Within (error) | N−a·b = 180−6 = **174** |
| Total | N−1 = **179** |

### Step 8 — MS and F for Each Term

$$MS(A) = \frac{223.233}{2} = 111.617 \quad \Rightarrow \quad F_A = \frac{111.617}{0.600} = 186.028$$

$$MS(B) = \frac{5.689}{1} = 5.689 \quad \Rightarrow \quad F_B = \frac{5.689}{0.600} = 9.481$$

$$MS(A \times B) = \frac{0.678}{2} = 0.339 \quad \Rightarrow \quad F_{A \times B} = \frac{0.339}{0.600} = 0.565$$

$$MS(W) = \frac{104.400}{174} = 0.600$$

### Step 9 — ANOVA Table

| | SS | df | MS | F | Decision |
|--|-----|----|----|---|----------|
| **Factor A (Model)** | 223.233 | a−1 = 2 | 223.233/2 = 111.617 | 111.617/0.600 = 186.028 | Tail area above F = **< 0.001** |
| **Factor B (Language)** | 5.689 | b−1 = 1 | 5.689/1 = 5.689 | 5.689/0.600 = 9.481 | Tail area above F = **0.002** |
| **Interaction (A×B)** | 0.678 | (a−1)(b−1) = 2 | 0.678/2 = 0.339 | 0.339/0.600 = 0.565 | Tail area above F = **0.570** |
| **Within (error)** | 104.400 | N−a·b = 174 | 104.400/174 = 0.600 | | |
| **Total** | 333.999 | N−1 = 179 | | | |

### Step 10 — Decision

F critical values (α = 0.20): F(2,174) = 1.624 · F(1,174) = 1.655

| Term | F | F_crit | p-value | Decision |
|------|---|--------|---------|----------|
| Model | 186.028 | 1.624 | < 0.001 | **Reject H0** |
| Language | 9.481 | 1.655 | 0.002 | **Reject H0** |
| **Interaction A×B** | **0.565** | **1.624** | **0.570** | **→ H0 Not Rejected** |

The interaction term has $p = 0.570 > \alpha = 0.20$. **The model ranking does not change between Python and C++.**

---

## H5 — Two-Way ANOVA — Model × Complexity Interaction

### Step 1 — Cell Means (n = 20 per cell)

| Model | Easy (X̄) | Medium (X̄) | Hard (X̄) | Marginal Mean |
|-------|----------|-----------|---------|---------------|
| Claude Sonnet 4.6 | 17.850 | 17.350 | 17.400 | 17.533 |
| DeepSeek V3 | 16.450 | 16.650 | 16.750 | 16.617 |
| Gemini 3 Flash | 14.900 | 15.000 | 14.650 | 14.850 |
| **Marginal Mean** | **16.400** | **16.333** | **16.267** | **16.333** |

**GM = 16.333 | a = 3 models | c = 3 complexity levels | N = 180**

### Step 2 — SS(A) Effect of Model (n per marginal = 60)

$$SS(A) = 60(17.533-16.333)^2 + 60(16.617-16.333)^2 + 60(14.850-16.333)^2 = \boxed{223.233}$$

*(same calculation as H1 and H4)*

### Step 3 — SS(C) Effect of Complexity (n per marginal = 60)

$$SS(C) = \sum 60(\bar{X}_c - GM)^2$$

- Easy: $60 \times (16.400 - 16.333)^2 = 60 \times 0.00449 = 0.267$
- Medium: $60 \times (16.333 - 16.333)^2 = 60 \times 0 = 0$
- Hard: $60 \times (16.267 - 16.333)^2 = 60 \times 0.00436 = 0.267$

$$SS(C) = 0.267 + 0 + 0.267 = \boxed{0.533}$$

### Step 4 — SS(M) All Cells Combined (n per cell = 20)

$$SS(M) = \sum 20(\bar{X}_{ic} - GM)^2$$

- Claude/Easy: $20 \times (17.850 - 16.333)^2 = 20 \times 2.301 = 45.920$
- Claude/Medium: $20 \times (17.350 - 16.333)^2 = 20 \times 1.034 = 20.680$
- Claude/Hard: $20 \times (17.400 - 16.333)^2 = 20 \times 1.138 = 22.760$
- DeepSeek/Easy: $20 \times (16.450 - 16.333)^2 = 20 \times 0.0137 = 0.274$
- DeepSeek/Medium: $20 \times (16.650 - 16.333)^2 = 20 \times 0.1005 = 2.010$
- DeepSeek/Hard: $20 \times (16.750 - 16.333)^2 = 20 \times 0.1739 = 3.478$
- Gemini/Easy: $20 \times (14.900 - 16.333)^2 = 20 \times 2.054 = 41.080$
- Gemini/Medium: $20 \times (15.000 - 16.333)^2 = 20 \times 1.777 = 35.540$
- Gemini/Hard: $20 \times (14.650 - 16.333)^2 = 20 \times 2.832 = 56.640$

$$SS(M) = 45.920 + 20.680 + 22.760 + 0.274 + 2.010 + 3.478 + 41.080 + 35.540 + 56.640 = \boxed{228.382}$$

### Step 5 — SS(A×C) Interaction

$$SS(A \times C) = SS(M) - SS(A) - SS(C) = 228.382 - 223.233 - 0.533 = \boxed{4.616}$$

### Step 6 — SS(W) Within-Group Error

$$SS(W) = \sum(n_{ic} - 1) \times s^2_{ic} = \boxed{105.500}$$

### Step 7 — Degrees of Freedom

| Source | df |
|--------|----|
| Factor A (Model) | a−1 = 3−1 = **2** |
| Factor C (Complexity) | c−1 = 3−1 = **2** |
| Interaction A×C | (a−1)(c−1) = 2×2 = **4** |
| Within (error) | N−a·c = 180−9 = **171** |
| Total | N−1 = **179** |

### Step 8 — MS and F for Each Term

$$MS(A) = \frac{223.233}{2} = 111.617 \quad \Rightarrow \quad F_A = \frac{111.617}{0.617} = 180.914$$

$$MS(C) = \frac{0.533}{2} = 0.267 \quad \Rightarrow \quad F_C = \frac{0.267}{0.617} = 0.432$$

$$MS(A \times C) = \frac{4.616}{4} = 1.154 \quad \Rightarrow \quad F_{A \times C} = \frac{1.154}{0.617} = 1.870$$

$$MS(W) = \frac{105.500}{171} = 0.617$$

### Step 9 — ANOVA Table

| | SS | df | MS | F | Decision |
|--|-----|----|----|---|----------|
| **Factor A (Model)** | 223.233 | a−1 = 2 | 223.233/2 = 111.617 | 111.617/0.617 = 180.914 | Tail area above F = **< 0.001** |
| **Factor C (Complexity)** | 0.533 | c−1 = 2 | 0.533/2 = 0.267 | 0.267/0.617 = 0.432 | Tail area above F = **0.650** |
| **Interaction (A×C)** | 4.616 | (a−1)(c−1) = 4 | 4.616/4 = 1.154 | 1.154/0.617 = 1.870 | Tail area above F = **0.118** |
| **Within (error)** | 105.500 | N−a·c = 171 | 105.500/171 = 0.617 | | |
| **Total** | 333.882 | N−1 = 179 | | | |

### Step 10 — Decision

F critical values (α = 0.20): F(2,171) = 1.625 · F(4,171) = 1.515

| Term | F | F_crit | p-value | Decision |
|------|---|--------|---------|----------|
| Model | 180.914 | 1.625 | < 0.001 | **Reject H0** |
| Complexity | 0.432 | 1.625 | 0.650 | H0 Not Rejected |
| **Interaction A×C** | **1.870** | **1.515** | **0.118** | **→ Reject H0** |

The interaction term has $p = 0.118 < \alpha = 0.20$. **The performance gap between models is not constant across complexity levels — H0 is Rejected.**

---

## Summary Table — All Hypotheses (α = 0.20)

| H | Factor | F | df | p-value | F_crit (α=0.20) | Decision |
|---|--------|---|----|---------|--------------------|----------|
| H1 | Model (one-way) | 178.358 | (2, 177) | < 0.001 | 1.624 | **Reject H0** |
| H2 | Language (one-way) | 3.084 | (1, 178) | 0.081 | 1.655 | **Reject H0** |
| H3 | Complexity (one-way) | 0.142 | (2, 177) | 0.868 | 1.624 | Not Reject H0 |
| H4 | Model × Language interaction | 0.565 | (2, 174) | 0.570 | 1.624 | Not Reject H0 |
| H5 | Model × Complexity interaction | 1.870 | (4, 171) | 0.118 | 1.515 | **Reject H0** |
