import re

def is_section_header(lines, i, code_block_count):
    if code_block_count % 2 == 1:
        return False

    line = lines[i]
    stripped = line.rstrip('\n').rstrip('\r')
    content = stripped.strip()

    if not content:
        return False
    if content.startswith('#'):
        return False
    if content[0] in '|-`[!>*':
        return False
    if stripped != stripped.lstrip():
        return False
    if len(content) > 80:
        return False
    if content.endswith('.') and not content.endswith('...'):
        return False
    if content[0].islower():
        return False

    # Must be preceded by blank line or - Function line
    prev_blank = False
    for j in range(i - 1, -1, -1):
        prev = lines[j].rstrip('\n').rstrip('\r').strip()
        if prev == '':
            prev_blank = True
            break
        if re.match(r'^- Function \d+', prev):
            prev_blank = True
            break
        prev_blank = False
        break

    if not prev_blank:
        return False

    # Exclude lines with en dash that are content bullets
    if '–' in content:  # en dash –
        return False

    # Allow em dash only in known header patterns
    if ' — ' in content:  # em dash —
        has_header_kw = any(kw in content for kw in [
            'Function', 'Analysis', 'Explanation', 'Overview',
            'Breakdown', 'Helper', 'Main', 'Tribonacci', 'Code'
        ])
        if not has_header_kw:
            return False

    # Exclude known content starters
    content_starters = [
        'True', 'False', 'Returns ', 'Checks ', 'If ', 'When ', 'Where ',
        'Since ', 'Because ', 'Note:', 'See ', 'So ', 'Both ', 'All ',
        'Each ', 'No ', 'One ', 'Two ', 'Three ', 'Only ', 'Then ',
        'After ', 'Before ', 'During ', 'While ', 'With ', 'By ',
        'From ', 'To ', 'For ', 'In ', 'The function', 'The code',
        'The algorithm', 'The result', 'The loop', 'The ',
        'It ', 'A ', 'An ', 'This code', 'This is', 'This function',
        'This snippet', 'This expression', 'This line', 'This Python',
        'This C++', 'Similar to', 'Same as',
        'Assume', 'Pass ', 'Step ',
        'Given ', 'Converts ', 'Computes ', 'Finds ', 'Filters ',
        'Creates ', 'Builds ', 'Generates ', 'Calculates ',
        'Determines ', 'Removes ', 'Returns', 'Sorts ', 'Scans ',
        'Splits ', 'Reads ', 'Writes ', 'Uses ', 'Applies ',
        'Iterates ', 'Performs ', 'Implements ', 'Handles ',
        'Despite ', 'Without ', 'Unlike ', 'As ',
        'Initialization', 'Division ', 'Filtering ', 'Counting ',
        'Sorting ', 'Mapping ', 'Slicing ',
    ]
    for starter in content_starters:
        if content.startswith(starter):
            return False

    # Exclude digit-prefixed lines (numbered steps)
    if re.match(r'^\d+\.', content):
        return False

    return True

def transform_file(input_path, remove_banner=False):
    with open(input_path, 'r', encoding='utf-8') as f:
        lines = f.readlines()

    if remove_banner:
        start_idx = 0
        for i, line in enumerate(lines):
            if re.match(r'^- Function \d+', line.strip()):
                start_idx = i
                break
        lines = lines[start_idx:]

    result = []
    code_block_count = 0

    for i, line in enumerate(lines):
        stripped_line = line.rstrip('\n').rstrip('\r')

        if stripped_line.strip().startswith('```'):
            code_block_count += 1

        if is_section_header(lines, i, code_block_count):
            result.append('## ' + stripped_line.lstrip() + '\n')
        else:
            result.append(line)

    with open(input_path, 'w', encoding='utf-8') as f:
        f.writelines(result)

    print(f"Transformed: {input_path}")

files = [
    (r'c:\Users\fcaet\Desktop\MEI\ClaudeSonnet4.6\resultsCppClaude.md', False),
    (r'c:\Users\fcaet\Desktop\MEI\ClaudeSonnet4.6\resultsPythonClaude.md', False),
    (r'c:\Users\fcaet\Desktop\MEI\DeepSeekV3\resultsPythonDeepSeek.md', True),
    (r'c:\Users\fcaet\Desktop\MEI\DeepSeekV3\resultsCppDeepSeek.md', True),
]
for path, remove_banner in files:
    transform_file(path, remove_banner)
