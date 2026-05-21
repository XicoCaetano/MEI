import re

path = r'c:\Users\fcaet\Desktop\MEI\ClaudeSonnet4.6\resultsPythonClaude.md'

with open(path, 'r', encoding='utf-8') as f:
    lines = f.readlines()

# Phase 1: Remove ## from false positives
def is_false_positive(content):
    # "Time: ..." and "Space: ..." are complexity details, not headers
    if re.match(r'^(Time|Space):', content):
        return True
    # "Input: content..." and "Output: content..." are inline descriptions
    if re.match(r'^(Input|Output|Inputs|Outputs): .', content):
        return True
    # Formula lines like "CAP - SM"
    if re.match(r'^[A-Z]{2,}\s*[-+]\s*[A-Z]{2,}$', content):
        return True
    # Content sentence starters that are clearly not headers
    content_starters = [
        'Counts how many', 'Counter builds', 'Filters the',
    ]
    for s in content_starters:
        if content.startswith(s):
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

# Phase 2: Add ## to standalone section headers missing it
STANDALONE_HEADERS = {
    "Inputs", "Inputs:", "Input", "Input:",
    "Outputs", "Outputs:", "Output", "Output:",
    "Complexity", "Complexity:",
    "What it does", "What it does:",
    "What It Does", "What It Does:",
    "Edge Cases", "Edge Cases:",
    "Edge cases to consider:", "Edge Cases to consider:",
    "Algorithm", "Algorithm:",
    "Logic", "Logic:",
    "Algorithm / Logic", "Algorithm / Logic:",
    "Logic / Algorithm", "Logic / Algorithm:",
    "Inputs & Outputs", "Inputs & Outputs:",
    "Overview", "Overview:",
    "Performance", "Performance:",
}

result = []
for line in lines:
    raw = line.rstrip('\n').rstrip('\r')
    stripped = raw.strip()

    # Skip lines already with # prefix, in tables, code, or indented
    if raw.startswith('#') or raw.startswith('|') or raw.startswith('`'):
        result.append(line)
        continue
    if raw != raw.lstrip():
        result.append(line)
        continue

    if stripped in STANDALONE_HEADERS:
        result.append('## ' + stripped + '\n')
        continue

    result.append(line)

with open(path, 'w', encoding='utf-8') as f:
    f.writelines(result)

print("Done fixing Python Claude file.")
