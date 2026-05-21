## Choices

This section documents the key decisions made by the group before running the experiments, covering the selection of LLM models, coding tasks, programming languages, and the confidence level adopted for statistical testing.

### LLM Models

The experiment evaluates three models — **Claude Sonnet 4.6** (Anthropic), **Gemini 3 Flash** (Google), and **DeepSeek V3** (DeepSeek) — accessed through their free-tier web interfaces. This setup reflects the most representative scenario of how the majority of developers interact with these tools on a daily basis: through conversational web UIs, without API access or local deployment. The selection of models from three distinct providers also ensures that the evaluation covers the current competitive landscape without favouring a single ecosystem.

### Coding Tasks

The assignment identifies four fundamental coding-related tasks where LLM-based tools can be used: code generation, code explanation, code review (bug discovery), and test case generation. Since the group consists of four members, each member was assigned one task, allowing the group to cover all four tasks recommended in the assignment specification. The present chapter covers the **Code Generation** experiment.

### Programming Languages

Two programming languages were selected: **Python** and **C++**. This choice covers two ends of the language spectrum relevant to a software company. Python represents high-level, dynamically typed languages, widely adopted in data science, scripting, and web development. C++ represents low-level, statically typed languages, used in performance-critical systems, game engines, and embedded software. Evaluating the same problems in both languages allows the experiment to assess whether model performance is consistent across language paradigms or exhibits language-dependent variations.

### Confidence Level

A significance level of α = 0.20 (80% confidence) was adopted for all statistical tests. This choice reflects the non-critical nature of the decision under evaluation: recommending a development tool to a CTO does not carry the same risk profile as decisions in medical, safety, or financial contexts, where α = 0.05 or stricter levels are standard. In this scenario, the cost of a false negative (failing to detect a real difference between models and potentially recommending an inferior tool) outweighs the cost of a false positive, justifying a higher tolerance for Type I error.