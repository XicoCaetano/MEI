import re

# Known section headers for DeepSeek files (exact matches, case-insensitive check)
SECTION_HEADERS = {
    # Function-level titles
    "function explanation", "function overview", "function analysis",
    "function breakdown", "function purpose",
    # What it does
    "what the function does", "what the function does:",
    "what it does", "what it does:", "what this function does",
    "what this function does:", "what does this double-encoding do?",
    "what the code does", "what the code does:", "what this code does",
    # Inputs/Outputs
    "inputs", "inputs:", "input", "input:",
    "outputs", "outputs:", "output", "output:",
    "inputs and outputs", "inputs and outputs:",
    "inputs & outputs", "inputs & outputs:",
    "inputs & output", "inputs & output:",
    "input and output", "input and output:",
    "input and outputs",
    "inputs (implied)", "inputs/outputs",
    # Algorithm
    "algorithm", "algorithm:",
    "algorithm / logic used", "algorithm / logic used:",
    "algorithm / logic", "algorithm / logic:",
    "algorithm/logic used", "algorithm/logic used:",
    "algorithm/logic", "algorithm/logic:",
    "algorithm & logic", "algorithm & logic:",
    "algorithm used", "algorithm used:",
    "logic / algorithm", "logic / algorithm:",
    "logic/algorithm", "logic/algorithm:",
    "logic & algorithm",
    "logic", "logic:",
    # Edge Cases
    "edge cases", "edge cases:", "edge cases & limitations",
    "edge cases & behavior to note", "edge cases & considerations",
    "edge cases & issues", "edge cases and issues",
    "edge cases & potential issues", "edge cases to consider",
    "edge cases to watch",
    "potential edge cases",
    # Examples
    "examples", "example", "example:", "examples:",
    "example usage", "example usage:",
    "example walkthrough", "example walkthrough:",
    "example outputs", "example outputs:",
    "example run", "example run:",
    "example runs", "example runs:",
    "example behavior",
    # Other common sections
    "complexity", "complexity:",
    "performance", "performance:",
    "overview", "overview:",
    "the algorithm: trial division",
    "mathematical logic",
    "purpose", "purpose:",
    "practical example",
    "key characteristics",
    "step-by-step logic", "step-by-step logic:",
    "logic breakdown", "logic breakdown:",
    "core logic", "core logic:",
    "the logic (algorithm)",
    "the scoring rule",
    "scoring rule",
    "note (implied)",
    "important detail",
    "algorithm (implied)",
    # Specific to some functions
    "what does this double-encoding do?",
    "helper function check(s)",
    "main logic",
    "the bug",
    "bug/edge issue",
}


def normalize(s):
    return s.strip().lower().rstrip(':')


def fix_deepseek_file(path):
    with open(path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    result = []
    for i, line in enumerate(lines):
        raw = line.rstrip('\n').rstrip('\r')
        stripped = raw.strip()

        # If this line has ## prefix
        if raw.startswith('## '):
            content = raw[3:].strip()
            norm = normalize(content)

            # Check if it's a known section header
            if norm in SECTION_HEADERS:
                result.append(line)  # Keep the ##
                continue

            # Check for close variants (with/without colon)
            if norm.rstrip(':') in SECTION_HEADERS:
                result.append(line)
                continue

            # Not a known header → remove ##
            result.append(content + '\n')
            continue

        result.append(line)

    with open(path, 'w', encoding='utf-8') as f:
        f.writelines(result)

    print(f"Fixed: {path}")


fix_deepseek_file(r'c:\Users\fcaet\Desktop\MEI\DeepSeekV3\resultsPythonDeepSeek.md')
fix_deepseek_file(r'c:\Users\fcaet\Desktop\MEI\DeepSeekV3\resultsCppDeepSeek.md')
