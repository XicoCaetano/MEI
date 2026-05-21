import re

path = r'c:\Users\fcaet\Desktop\MEI\ClaudeSonnet4.6\resultsCppClaude.md'

with open(path, 'r', encoding='utf-8') as f:
    lines = f.readlines()

# Phase 1: Remove ## from false positives
def is_false_positive(content):
    # Content lines: "Input: text...", "Output: text..."
    if re.match(r'^(Input|Output|Inputs|Outputs): .', content):
        return True
    # Algorithm step lines
    false_starters = [
        'Start with ', 'Iterate ', 'Loop through', 'Sort ',
        'Count ', 'GCD(', 'Sum = ',
    ]
    for s in false_starters:
        if content.startswith(s):
            return True
    # Numbered content bullet
    if re.match(r'^\d+', content) and 'contributes' in content:
        return True
    return False

result = []
for line in lines:
    stripped = line.rstrip('\n').rstrip('\r')
    if stripped.startswith('## '):
        content = stripped[3:]
        if is_false_positive(content):
            result.append(content + '\n')
            continue
    result.append(line)

lines = result

# Phase 2: Add ## to missed section headers (whitelist approach)
# These are exact phrases used as section headers in this file
SECTION_HEADERS = {
    "What it does", "What It Does", "What It Does:",
    "Inputs & Outputs", "Inputs & Output", "Input & Output",
    "Input", "Output", "Inputs", "Outputs",
    "Logic / Algorithm", "Algorithm / Logic", "Algorithm & Logic",
    "Algorithm",
    "Edge Cases", "Edge Cases & Issues", "Edge Cases & Concerns",
    "Edge Cases & Notes", "Issues & Edge Cases", "Edge Cases & Issues",
    "Complexity",
    "Overview",
    "Performance",
    "same_chars Function Analysis",
    "match_parens Function Explanation",
    "Strongest_Extension Function Breakdown",
    "make_palindrome — Code Explanation",
    "tri(int n) — Tribonacci-like Sequence Generator",
    "is_sorted Function Explanation",
}

result = []
for i, line in enumerate(lines):
    raw = line.rstrip('\n').rstrip('\r')
    stripped = raw.strip()

    # Skip lines already with ## or # or in tables or code
    if raw.startswith('#') or raw.startswith('|') or raw.startswith('`'):
        result.append(line)
        continue

    # Skip indented lines
    if raw != raw.lstrip():
        result.append(line)
        continue

    # Check if this is a known header not yet prefixed with ##
    if stripped in SECTION_HEADERS:
        result.append('## ' + stripped + '\n')
        continue

    result.append(line)

with open(path, 'w', encoding='utf-8') as f:
    f.writelines(result)

print("Done fixing C++ Claude file.")
