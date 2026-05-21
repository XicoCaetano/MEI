# Code Review (Bug Discovery) — 60 chunks selected from HumanEvalPack

This file contains the **60 chunks** to be submitted to the three LLMs (Claude Sonnet 4.6, Gemini 3.1 Pro, DeepSeek V3) for the *bug discovery* experiment.

**Structure:** 30 Python + 30 C++. Within each language: 10 *easy* + 10 *medium* + 10 *hard*. Within each difficulty: 5 with bug + 5 without bug (clean control set).

**For each chunk:**
1. A **ready-to-paste prompt block** (just copy the whole code block into the LLM chat — no edits needed).
2. The **answer key** — what the correct response is. For buggy chunks: type and exact location. For clean chunks: the LLM should respond `NO BUGS`.

**Source for each chunk** is given via the `task_id_source` from `bigcode/humanevalpack` (e.g. `Python/0`, `CPP/3`). All Python docstrings have been removed from the prompt.

---

# PYTHON

## PYTHON — EASY

### Chunk `PY-01`  (source: `Python/2` — `truncate_number`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def truncate_number(number: float) -> float:
    return number % 1.0 + 1.0
```
````

**Code (with line numbers, for reference and classification):**

```python
1  def truncate_number(number: float) -> float:
2      return number % 1.0 + 1.0  <-- BUG
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `excess logic`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 1** was changed:
    - buggy:    `return number % 1.0 + 1.0`
    - correct:  `return number % 1.0`

---

### Chunk `PY-02`  (source: `Python/4` — `mean_absolute_deviation`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def mean_absolute_deviation(numbers: List[float]) -> float:
    mean = sum(numbers) / len(numbers)
    return sum(abs(x - mean) for x in numbers) / mean
```
````

**Code (with line numbers, for reference and classification):**

```python
1  from typing import List
2  
3  
4  def mean_absolute_deviation(numbers: List[float]) -> float:
5      mean = sum(numbers) / len(numbers)
6      return sum(abs(x - mean) for x in numbers) / mean  <-- BUG
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `variable misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 2** was changed:
    - buggy:    `return sum(abs(x - mean) for x in numbers) / mean`
    - correct:  `return sum(abs(x - mean) for x in numbers) / len(numbers)`

---

### Chunk `PY-03`  (source: `Python/15` — `string_sequence`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def string_sequence(n: int) -> str:
    return ' '.join([str(x) for x in range(n)])
```
````

**Code (with line numbers, for reference and classification):**

```python
1  def string_sequence(n: int) -> str:
2      return ' '.join([str(x) for x in range(n)])  <-- BUG
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 1** was changed:
    - buggy:    `return ' '.join([str(x) for x in range(n)])`
    - correct:  `return ' '.join([str(x) for x in range(n + 1)])`

---

### Chunk `PY-04`  (source: `Python/16` — `count_distinct_characters`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def count_distinct_characters(string: str) -> int:
    return len(set(string))
```
````

**Code (with line numbers, for reference and classification):**

```python
1  def count_distinct_characters(string: str) -> int:
2      return len(set(string))  <-- BUG
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `missing logic`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 1** was changed:
    - buggy:    `return len(set(string))`
    - correct:  `return len(set(string.lower()))`

---

### Chunk `PY-05`  (source: `Python/17` — `parse_music`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def parse_music(music_string: str) -> List[int]:
    note_map = {'o': 3, 'o|': 2, '.|': 1}
    return [note_map[x] for x in music_string.split(' ') if x]
```
````

**Code (with line numbers, for reference and classification):**

```python
1  from typing import List
2  
3  
4  def parse_music(music_string: str) -> List[int]:
5      note_map = {'o': 3, 'o|': 2, '.|': 1}  <-- BUG
6      return [note_map[x] for x in music_string.split(' ') if x]
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 1** was changed:
    - buggy:    `note_map = {'o': 3, 'o|': 2, '.|': 1}`
    - correct:  `note_map = {'o': 4, 'o|': 2, '.|': 1}`

---

### Chunk `PY-06`  (source: `Python/7` — `filter_by_substring`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def filter_by_substring(strings: List[str], substring: str) -> List[str]:
    return [x for x in strings if substring in x]
```
````

**Code (with line numbers, for reference and classification):**

```python
1  from typing import List
2  
3  
4  def filter_by_substring(strings: List[str], substring: str) -> List[str]:
5      return [x for x in strings if substring in x]
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-07`  (source: `Python/13` — `greatest_common_divisor`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def greatest_common_divisor(a: int, b: int) -> int:
    while b:
        a, b = b, a % b
    return a
```
````

**Code (with line numbers, for reference and classification):**

```python
1  def greatest_common_divisor(a: int, b: int) -> int:
2      while b:
3          a, b = b, a % b
4      return a
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-08`  (source: `Python/21` — `rescale_to_unit`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def rescale_to_unit(numbers: List[float]) -> List[float]:
    min_number = min(numbers)
    max_number = max(numbers)
    return [(x - min_number) / (max_number - min_number) for x in numbers]
```
````

**Code (with line numbers, for reference and classification):**

```python
1  from typing import List
2  
3  
4  def rescale_to_unit(numbers: List[float]) -> List[float]:
5      min_number = min(numbers)
6      max_number = max(numbers)
7      return [(x - min_number) / (max_number - min_number) for x in numbers]
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-09`  (source: `Python/22` — `filter_integers`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List, Any


def filter_integers(values: List[Any]) -> List[int]:
    return [x for x in values if isinstance(x, int)]
```
````

**Code (with line numbers, for reference and classification):**

```python
1  from typing import List, Any
2  
3  
4  def filter_integers(values: List[Any]) -> List[int]:
5      return [x for x in values if isinstance(x, int)]
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-10`  (source: `Python/23` — `strlen`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def strlen(string: str) -> int:
    return len(string)
```
````

**Code (with line numbers, for reference and classification):**

```python
1  def strlen(string: str) -> int:
2      return len(string)
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

## PYTHON — MEDIUM

### Chunk `PY-11`  (source: `Python/0` — `has_close_elements`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def has_close_elements(numbers: List[float], threshold: float) -> bool:
    for idx, elem in enumerate(numbers):
        for idx2, elem2 in enumerate(numbers):
            if idx != idx2:
                distance = elem - elem2
                if distance < threshold:
                    return True

    return False
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List
 2  
 3  
 4  def has_close_elements(numbers: List[float], threshold: float) -> bool:
 5      for idx, elem in enumerate(numbers):
 6          for idx2, elem2 in enumerate(numbers):
 7              if idx != idx2:
 8                  distance = elem - elem2  <-- BUG
 9                  if distance < threshold:
10                      return True
11  
12      return False
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `missing logic`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 4** was changed:
    - buggy:    `distance = elem - elem2`
    - correct:  `distance = abs(elem - elem2)`

---

### Chunk `PY-12`  (source: `Python/3` — `below_zero`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def below_zero(operations: List[int]) -> bool:
    balance = 0

    for op in operations:
        balance += op
        if balance == 0:
            return True

    return False
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List
 2  
 3  
 4  def below_zero(operations: List[int]) -> bool:
 5      balance = 0
 6  
 7      for op in operations:
 8          balance += op
 9          if balance == 0:  <-- BUG
10              return True
11  
12      return False
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `operator misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 5** was changed:
    - buggy:    `if balance == 0:`
    - correct:  `if balance < 0:`

---

### Chunk `PY-13`  (source: `Python/8` — `sum_product`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List, Tuple


def sum_product(numbers: List[int]) -> Tuple[int, int]:
    sum_value = 0
    prod_value = 0

    for n in numbers:
        sum_value += n
        prod_value *= n
    return sum_value, prod_value
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List, Tuple
 2  
 3  
 4  def sum_product(numbers: List[int]) -> Tuple[int, int]:
 5      sum_value = 0
 6      prod_value = 0  <-- BUG
 7  
 8      for n in numbers:
 9          sum_value += n
10          prod_value *= n
11      return sum_value, prod_value
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 2** was changed:
    - buggy:    `prod_value = 0`
    - correct:  `prod_value = 1`

---

### Chunk `PY-14`  (source: `Python/9` — `rolling_max`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List, Tuple


def rolling_max(numbers: List[int]) -> List[int]:
    running_max = None
    result = []

    for n in numbers:
        if running_max is None:
            running_max = n
        else:
            running_max = max(numbers)

        result.append(running_max)

    return result
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List, Tuple
 2  
 3  
 4  def rolling_max(numbers: List[int]) -> List[int]:
 5      running_max = None
 6      result = []
 7  
 8      for n in numbers:
 9          if running_max is None:
10              running_max = n
11          else:
12              running_max = max(numbers)  <-- BUG
13  
14          result.append(running_max)
15  
16      return result
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `variable misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 8** was changed:
    - buggy:    `running_max = max(numbers)`
    - correct:  `running_max = max(running_max, n)`

---

### Chunk `PY-15`  (source: `Python/10` — `make_palindrome`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def is_palindrome(string: str) -> bool:
    return string == string[::-1]


def make_palindrome(string: str) -> str:
    if not string:
        return ''

    beginning_of_suffix = 0

    while not is_palindrome(string):
        beginning_of_suffix += 1

    return string + string[:beginning_of_suffix][::-1]
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def is_palindrome(string: str) -> bool:
 2      return string == string[::-1]
 3  
 4  
 5  def make_palindrome(string: str) -> str:
 6      if not string:
 7          return ''
 8  
 9      beginning_of_suffix = 0
10  
11      while not is_palindrome(string):  <-- BUG
12          beginning_of_suffix += 1
13  
14      return string + string[:beginning_of_suffix][::-1]
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `missing logic`
- **Failure symptom:** `stackoverflow`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 6** was changed:
    - buggy:    `while not is_palindrome(string):`
    - correct:  `while not is_palindrome(string[beginning_of_suffix:]):`

---

### Chunk `PY-16`  (source: `Python/5` — `intersperse`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def intersperse(numbers: List[int], delimeter: int) -> List[int]:
    if not numbers:
        return []

    result = []

    for n in numbers[:-1]:
        result.append(n)
        result.append(delimeter)

    result.append(numbers[-1])

    return result
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List
 2  
 3  
 4  def intersperse(numbers: List[int], delimeter: int) -> List[int]:
 5      if not numbers:
 6          return []
 7  
 8      result = []
 9  
10      for n in numbers[:-1]:
11          result.append(n)
12          result.append(delimeter)
13  
14      result.append(numbers[-1])
15  
16      return result
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-17`  (source: `Python/11` — `string_xor`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def string_xor(a: str, b: str) -> str:
    def xor(i, j):
        if i == j:
            return '0'
        else:
            return '1'

    return ''.join(xor(x, y) for x, y in zip(a, b))
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List
 2  
 3  
 4  def string_xor(a: str, b: str) -> str:
 5      def xor(i, j):
 6          if i == j:
 7              return '0'
 8          else:
 9              return '1'
10  
11      return ''.join(xor(x, y) for x, y in zip(a, b))
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-18`  (source: `Python/12` — `longest`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List, Optional


def longest(strings: List[str]) -> Optional[str]:
    if not strings:
        return None

    maxlen = max(len(x) for x in strings)
    for s in strings:
        if len(s) == maxlen:
            return s
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List, Optional
 2  
 3  
 4  def longest(strings: List[str]) -> Optional[str]:
 5      if not strings:
 6          return None
 7  
 8      maxlen = max(len(x) for x in strings)
 9      for s in strings:
10          if len(s) == maxlen:
11              return s
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-19`  (source: `Python/31` — `is_prime`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def is_prime(n):
    if n < 2:
        return False
    for k in range(2, n - 1):
        if n % k == 0:
            return False
    return True
```
````

**Code (with line numbers, for reference and classification):**

```python
1  def is_prime(n):
2      if n < 2:
3          return False
4      for k in range(2, n - 1):
5          if n % k == 0:
6              return False
7      return True
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-20`  (source: `Python/36` — `fizz_buzz`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def fizz_buzz(n: int):
    ns = []
    for i in range(n):
        if i % 11 == 0 or i % 13 == 0:
            ns.append(i)
    s = ''.join(list(map(str, ns)))
    ans = 0
    for c in s:
        ans += (c == '7')
    return ans
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def fizz_buzz(n: int):
 2      ns = []
 3      for i in range(n):
 4          if i % 11 == 0 or i % 13 == 0:
 5              ns.append(i)
 6      s = ''.join(list(map(str, ns)))
 7      ans = 0
 8      for c in s:
 9          ans += (c == '7')
10      return ans
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

## PYTHON — HARD

### Chunk `PY-21`  (source: `Python/1` — `separate_paren_groups`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def separate_paren_groups(paren_string: str) -> List[str]:
    result = []
    current_string = []
    current_depth = 0

    for c in paren_string:
        if c == '(':
            current_depth += 1
            current_string.append(c)
        elif c == ')':
            current_depth -= 1
            current_string.append(c)

            if current_depth < 0:
                result.append(''.join(current_string))
                current_string.clear()

    return result
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List
 2  
 3  
 4  def separate_paren_groups(paren_string: str) -> List[str]:
 5      result = []
 6      current_string = []
 7      current_depth = 0
 8  
 9      for c in paren_string:
10          if c == '(':
11              current_depth += 1
12              current_string.append(c)
13          elif c == ')':
14              current_depth -= 1
15              current_string.append(c)
16  
17              if current_depth < 0:  <-- BUG
18                  result.append(''.join(current_string))
19                  current_string.clear()
20  
21      return result
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `operator misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 13** was changed:
    - buggy:    `if current_depth < 0:`
    - correct:  `if current_depth == 0:`

---

### Chunk `PY-22`  (source: `Python/19` — `sort_numbers`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List


def sort_numbers(numbers: str) -> str:
    value_map = {
        'zero': 0,
        'one': 1,
        'two': 2,
        'three': 3,
        'four': 4,
        'five': 5,
        'six': 6,
        'seven': 7,
        'eight': 8,
        'nine': 9
    }
    return ' '.join([x for x in numbers.split(' ') if x])
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List
 2  
 3  
 4  def sort_numbers(numbers: str) -> str:
 5      value_map = {
 6          'zero': 0,
 7          'one': 1,
 8          'two': 2,
 9          'three': 3,
10          'four': 4,
11          'five': 5,
12          'six': 6,
13          'seven': 7,
14          'eight': 8,
15          'nine': 9
16      }
17      return ' '.join([x for x in numbers.split(' ') if x])  <-- BUG
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `missing logic`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 13** was changed:
    - buggy:    `return ' '.join([x for x in numbers.split(' ') if x])`
    - correct:  `return ' '.join(sorted([x for x in numbers.split(' ') if x], key=lambda x: value_map[x]))`

---

### Chunk `PY-23`  (source: `Python/39` — `prime_fib`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def prime_fib(n: int):
    import math

    def is_prime(p):
        if p < 2:
            return False
        for k in range(2, min(int(math.sqrt(p)), p)):
            if p % k == 0:
                return False
        return True
    f = [0, 1]
    while True:
        f.append(f[-1] + f[-2])
        if is_prime(f[-1]):
            n -= 1
        if n == 0:
            return f[-1]
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def prime_fib(n: int):
 2      import math
 3  
 4      def is_prime(p):
 5          if p < 2:
 6              return False
 7          for k in range(2, min(int(math.sqrt(p)), p)):  <-- BUG
 8              if p % k == 0:
 9                  return False
10          return True
11      f = [0, 1]
12      while True:
13          f.append(f[-1] + f[-2])
14          if is_prime(f[-1]):
15              n -= 1
16          if n == 0:
17              return f[-1]
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 6** was changed:
    - buggy:    `for k in range(2, min(int(math.sqrt(p)), p)):`
    - correct:  `for k in range(2, min(int(math.sqrt(p)) + 1, p - 1)):`

---

### Chunk `PY-24`  (source: `Python/81` — `numerical_letter_grade`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def numerical_letter_grade(grades):

   
    letter_grade = []
    for gpa in grades:
        if gpa == 4.0:
            letter_grade.append("A+")
        elif gpa > 3.7:
            letter_grade.append("A")
        elif gpa > 3.3:
            letter_grade.append("A-")
        elif gpa > 3.0:
            letter_grade.append("B+")
        elif gpa > 2.7:
            letter_grade.append("B")
        elif gpa > 2.3:
            letter_grade.append("B-")
        elif gpa > 2.0:
            letter_grade.append("C+")
        elif gpa > 1.7:
            letter_grade.append("C")
        elif gpa > 1.3:
            letter_grade.append("C-")
        elif gpa > 1.0:
            letter_grade.append("D+")
        elif gpa > 0.7:
            letter_grade.append("D")
        elif gpa > 0.0:
            letter_grade.append("D-")
        else:
            letter_grade.append("E+")
    return letter_grade
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def numerical_letter_grade(grades):
 2  
 3     
 4      letter_grade = []
 5      for gpa in grades:
 6          if gpa == 4.0:
 7              letter_grade.append("A+")
 8          elif gpa > 3.7:
 9              letter_grade.append("A")
10          elif gpa > 3.3:
11              letter_grade.append("A-")
12          elif gpa > 3.0:
13              letter_grade.append("B+")
14          elif gpa > 2.7:
15              letter_grade.append("B")
16          elif gpa > 2.3:
17              letter_grade.append("B-")
18          elif gpa > 2.0:
19              letter_grade.append("C+")
20          elif gpa > 1.7:
21              letter_grade.append("C")
22          elif gpa > 1.3:
23              letter_grade.append("C-")
24          elif gpa > 1.0:
25              letter_grade.append("D+")
26          elif gpa > 0.7:
27              letter_grade.append("D")
28          elif gpa > 0.0:
29              letter_grade.append("D-")
30          else:
31              letter_grade.append("E+")
32      return letter_grade
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `excess logic`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 30** was changed:
    - buggy:    `letter_grade.append("E+")`
    - correct:  `letter_grade.append("E")`

---

### Chunk `PY-25`  (source: `Python/94` — `skjkasdkd`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def skjkasdkd(lst):
    def isPrime(n):
        for i in range(2,int(n**0.5)+1):
            if n%i==0:
                return True

        return False
    maxx = 0
    i = 0
    while i < len(lst):
        if(lst[i] > maxx and isPrime(lst[i])):
            maxx = lst[i]
        i+=1
    result = sum(int(digit) for digit in str(maxx))
    return result
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def skjkasdkd(lst):
 2      def isPrime(n):
 3          for i in range(2,int(n**0.5)+1):
 4              if n%i==0:
 5                  return True  <-- BUG
 6  
 7          return False  <-- BUG
 8      maxx = 0
 9      i = 0
10      while i < len(lst):
11          if(lst[i] > maxx and isPrime(lst[i])):
12              maxx = lst[i]
13          i+=1
14      result = sum(int(digit) for digit in str(maxx))
15      return result
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `operator misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 4** was changed:
    - buggy:    `return True`
    - correct:  `return False`
  - **Body line 6** was changed:
    - buggy:    `return False`
    - correct:  `return True`

---

### Chunk `PY-26`  (source: `Python/20` — `find_closest_elements`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
from typing import List, Tuple


def find_closest_elements(numbers: List[float]) -> Tuple[float, float]:
    closest_pair = None
    distance = None

    for idx, elem in enumerate(numbers):
        for idx2, elem2 in enumerate(numbers):
            if idx != idx2:
                if distance is None:
                    distance = abs(elem - elem2)
                    closest_pair = tuple(sorted([elem, elem2]))
                else:
                    new_distance = abs(elem - elem2)
                    if new_distance < distance:
                        distance = new_distance
                        closest_pair = tuple(sorted([elem, elem2]))

    return closest_pair
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  from typing import List, Tuple
 2  
 3  
 4  def find_closest_elements(numbers: List[float]) -> Tuple[float, float]:
 5      closest_pair = None
 6      distance = None
 7  
 8      for idx, elem in enumerate(numbers):
 9          for idx2, elem2 in enumerate(numbers):
10              if idx != idx2:
11                  if distance is None:
12                      distance = abs(elem - elem2)
13                      closest_pair = tuple(sorted([elem, elem2]))
14                  else:
15                      new_distance = abs(elem - elem2)
16                      if new_distance < distance:
17                          distance = new_distance
18                          closest_pair = tuple(sorted([elem, elem2]))
19  
20      return closest_pair
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-27`  (source: `Python/75` — `is_multiply_prime`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def is_multiply_prime(a):
    def is_prime(n):
        for j in range(2,n):
            if n%j == 0:
                return False
        return True

    for i in range(2,101):
        if not is_prime(i): continue
        for j in range(2,101):
            if not is_prime(j): continue
            for k in range(2,101):
                if not is_prime(k): continue
                if i*j*k == a: return True
    return False
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def is_multiply_prime(a):
 2      def is_prime(n):
 3          for j in range(2,n):
 4              if n%j == 0:
 5                  return False
 6          return True
 7  
 8      for i in range(2,101):
 9          if not is_prime(i): continue
10          for j in range(2,101):
11              if not is_prime(j): continue
12              for k in range(2,101):
13                  if not is_prime(k): continue
14                  if i*j*k == a: return True
15      return False
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-28`  (source: `Python/95` — `check_dict_case`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def check_dict_case(dict):
    if len(dict.keys()) == 0:
        return False
    else:
        state = "start"
        for key in dict.keys():

            if isinstance(key, str) == False:
                state = "mixed"
                break
            if state == "start":
                if key.isupper():
                    state = "upper"
                elif key.islower():
                    state = "lower"
                else:
                    break
            elif (state == "upper" and not key.isupper()) or (state == "lower" and not key.islower()):
                    state = "mixed"
                    break
            else:
                break
        return state == "upper" or state == "lower" 
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def check_dict_case(dict):
 2      if len(dict.keys()) == 0:
 3          return False
 4      else:
 5          state = "start"
 6          for key in dict.keys():
 7  
 8              if isinstance(key, str) == False:
 9                  state = "mixed"
10                  break
11              if state == "start":
12                  if key.isupper():
13                      state = "upper"
14                  elif key.islower():
15                      state = "lower"
16                  else:
17                      break
18              elif (state == "upper" and not key.isupper()) or (state == "lower" and not key.islower()):
19                      state = "mixed"
20                      break
21              else:
22                  break
23          return state == "upper" or state == "lower" 
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-29`  (source: `Python/99` — `closest_integer`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def closest_integer(value):
    from math import floor, ceil

    if value.count('.') == 1:
        # remove trailing zeros
        while (value[-1] == '0'):
            value = value[:-1]

    num = float(value)
    if value[-2:] == '.5':
        if num > 0:
            res = ceil(num)
        else:
            res = floor(num)
    elif len(value) > 0:
        res = int(round(num))
    else:
        res = 0

    return res
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def closest_integer(value):
 2      from math import floor, ceil
 3  
 4      if value.count('.') == 1:
 5          # remove trailing zeros
 6          while (value[-1] == '0'):
 7              value = value[:-1]
 8  
 9      num = float(value)
10      if value[-2:] == '.5':
11          if num > 0:
12              res = ceil(num)
13          else:
14              res = floor(num)
15      elif len(value) > 0:
16          res = int(round(num))
17      else:
18          res = 0
19  
20      return res
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `PY-30`  (source: `Python/105` — `by_length`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a python function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```python
def by_length(arr):
    dic = {
        1: "One",
        2: "Two",
        3: "Three",
        4: "Four",
        5: "Five",
        6: "Six",
        7: "Seven",
        8: "Eight",
        9: "Nine",
    }
    sorted_arr = sorted(arr, reverse=True)
    new_arr = []
    for var in sorted_arr:
        try:
            new_arr.append(dic[var])
        except:
            pass
    return new_arr
```
````

**Code (with line numbers, for reference and classification):**

```python
 1  def by_length(arr):
 2      dic = {
 3          1: "One",
 4          2: "Two",
 5          3: "Three",
 6          4: "Four",
 7          5: "Five",
 8          6: "Six",
 9          7: "Seven",
10          8: "Eight",
11          9: "Nine",
12      }
13      sorted_arr = sorted(arr, reverse=True)
14      new_arr = []
15      for var in sorted_arr:
16          try:
17              new_arr.append(dic[var])
18          except:
19              pass
20      return new_arr
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

# C++

## C++ — EASY

### Chunk `CPP-01`  (source: `CPP/2` — `truncate_number`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
using namespace std;
#include<algorithm>
#include<stdlib.h>
float truncate_number(float number){
    return number-int(number)+1;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
1  #include<stdio.h>
2  #include<math.h>
3  using namespace std;
4  #include<algorithm>
5  #include<stdlib.h>
6  float truncate_number(float number){
7      return number-int(number)+1;  <-- BUG
8  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `excess logic`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 1** was changed:
    - buggy:    `return number-int(number)+1;`
    - correct:  `return number-int(number);`

---

### Chunk `CPP-02`  (source: `CPP/15` — `string_sequence`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;
#include<algorithm>
#include<stdlib.h>
string string_sequence(int n){
    string out="0";
    for (int i=1;i<n;i++)
    out=out+" "+to_string(i);
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<string>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<stdlib.h>
 7  string string_sequence(int n){
 8      string out="0";
 9      for (int i=1;i<n;i++)  <-- BUG
10      out=out+" "+to_string(i);
11      return out;
12  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 2** was changed:
    - buggy:    `for (int i=1;i<n;i++)`
    - correct:  `for (int i=1;i<=n;i++)`

---

### Chunk `CPP-03`  (source: `CPP/24` — `largest_divisor`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
using namespace std;
#include<algorithm>
#include<stdlib.h>
int largest_divisor(int n){
    for (int i=2;i*i<=n;i++)
        if (n-i==0) return  n/i;
    return 1;

}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<stdlib.h>
 6  int largest_divisor(int n){
 7      for (int i=2;i*i<=n;i++)
 8          if (n-i==0) return  n/i;  <-- BUG
 9      return 1;
10  
11  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `operator misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 2** was changed:
    - buggy:    `if (n-i==0) return  n/i;`
    - correct:  `if (n%i==0) return  n/i;`

---

### Chunk `CPP-04`  (source: `CPP/29` — `filter_by_prefix`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
#include<string>
using namespace std;
#include<algorithm>
#include<stdlib.h>
vector<string> filter_by_prefix(vector<string> strings, string prefix){
    vector<string> out={};
    for (int i=0;i<strings.size();i++)
        if (strings[i].substr(0,prefix.length())!=prefix) out.push_back(strings[i]);
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  #include<string>
 5  using namespace std;
 6  #include<algorithm>
 7  #include<stdlib.h>
 8  vector<string> filter_by_prefix(vector<string> strings, string prefix){
 9      vector<string> out={};
10      for (int i=0;i<strings.size();i++)
11          if (strings[i].substr(0,prefix.length())!=prefix) out.push_back(strings[i]);  <-- BUG
12      return out;
13  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `function misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 3** was changed:
    - buggy:    `if (strings[i].substr(0,prefix.length())!=prefix) out.push_back(strings[i]);`
    - correct:  `if (strings[i].substr(0,prefix.length())==prefix) out.push_back(strings[i]);`

---

### Chunk `CPP-05`  (source: `CPP/30` — `get_positive`)

- **Difficulty:** easy
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<stdlib.h>
vector<float> get_positive(vector<float> l){
    vector<float> out={};
    for (int i=0;i<l.size();i++)
        if (l[i]<0) out.push_back(l[i]);
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<stdlib.h>
 7  vector<float> get_positive(vector<float> l){
 8      vector<float> out={};
 9      for (int i=0;i<l.size();i++)
10          if (l[i]<0) out.push_back(l[i]);  <-- BUG
11      return out;
12  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `operator misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 3** was changed:
    - buggy:    `if (l[i]<0) out.push_back(l[i]);`
    - correct:  `if (l[i]>0) out.push_back(l[i]);`

---

### Chunk `CPP-06`  (source: `CPP/23` — `strlen`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<string>
using namespace std;
#include<algorithm>
#include<stdlib.h>
int strlen(string str){
    return str.length();
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
1  #include<stdio.h>
2  #include<math.h>
3  #include<string>
4  using namespace std;
5  #include<algorithm>
6  #include<stdlib.h>
7  int strlen(string str){
8      return str.length();
9  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-07`  (source: `CPP/28` — `concatenate`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
#include<string>
using namespace std;
#include<algorithm>
#include<stdlib.h>
string concatenate(vector<string> strings){
    string out="";
    for (int i=0;i<strings.size();i++)
        out=out+strings[i];
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  #include<string>
 5  using namespace std;
 6  #include<algorithm>
 7  #include<stdlib.h>
 8  string concatenate(vector<string> strings){
 9      string out="";
10      for (int i=0;i<strings.size();i++)
11          out=out+strings[i];
12      return out;
13  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-08`  (source: `CPP/31` — `is_prime`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
using namespace std;
#include<algorithm>
#include<stdlib.h>
bool is_prime(long long n){
    if (n<2) return false;
    for (long long i=2;i*i<=n;i++)
        if (n%i==0) return false;
    return true;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<stdlib.h>
 6  bool is_prime(long long n){
 7      if (n<2) return false;
 8      for (long long i=2;i*i<=n;i++)
 9          if (n%i==0) return false;
10      return true;
11  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-09`  (source: `CPP/35` — `max_element`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;
#include<stdlib.h>
float max_element(vector<float> l){
  float max=-10000;
  for (int i=0;i<l.size();i++)
  if (max<l[i]) max=l[i];
  return max;

}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  #include<algorithm>
 5  using namespace std;
 6  #include<stdlib.h>
 7  float max_element(vector<float> l){
 8    float max=-10000;
 9    for (int i=0;i<l.size();i++)
10    if (max<l[i]) max=l[i];
11    return max;
12  
13  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-10`  (source: `CPP/41` — `car_race_collision`)

- **Difficulty:** easy
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
using namespace std;
#include<algorithm>
#include<stdlib.h>
int car_race_collision(int n){
    return n*n;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
1  #include<stdio.h>
2  #include<math.h>
3  using namespace std;
4  #include<algorithm>
5  #include<stdlib.h>
6  int car_race_collision(int n){
7      return n*n;
8  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

## C++ — MEDIUM

### Chunk `CPP-11`  (source: `CPP/3` — `below_zero`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
bool below_zero(vector<int> operations){
    int num=0;
    for (int i=0;i<operations.size();i++)
    {
        num+=operations[i];
        if (num==0) return true;
    }
    return false;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<math.h>
 6  #include<stdlib.h>
 7  bool below_zero(vector<int> operations){
 8      int num=0;
 9      for (int i=0;i<operations.size();i++)
10      {
11          num+=operations[i];
12          if (num==0) return true;  <-- BUG
13      }
14      return false;
15  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `operator misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 5** was changed:
    - buggy:    `if (num==0) return true;`
    - correct:  `if (num<0) return true;`

---

### Chunk `CPP-12`  (source: `CPP/4` — `mean_absolute_deviation`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<stdlib.h>
float mean_absolute_deviation(vector<float> numbers){
    float sum=0;
    float avg,msum,mavg;
    int i=0;
    for (i=0;i<numbers.size();i++)
        sum+=numbers[i];
    avg=sum/numbers.size();
    msum=0;
    for (i=0;i<numbers.size();i++)
        msum+=abs(numbers[i]-avg);
    return msum/avg;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<stdlib.h>
 7  float mean_absolute_deviation(vector<float> numbers){
 8      float sum=0;
 9      float avg,msum,mavg;
10      int i=0;
11      for (i=0;i<numbers.size();i++)
12          sum+=numbers[i];
13      avg=sum/numbers.size();
14      msum=0;
15      for (i=0;i<numbers.size();i++)
16          msum+=abs(numbers[i]-avg);
17      return msum/avg;  <-- BUG
18  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `variable misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 10** was changed:
    - buggy:    `return msum/avg;`
    - correct:  `return msum/numbers.size();`

---

### Chunk `CPP-13`  (source: `CPP/5` — `intersperse`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
vector<int> intersperse(vector<int> numbers, int delimeter){ 
    vector<int> out={};
    for (int i=1;i<numbers.size();i++)
    {
        out.push_back(delimeter);
        out.push_back(numbers[i]);

    }
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<math.h>
 6  #include<stdlib.h>
 7  vector<int> intersperse(vector<int> numbers, int delimeter){ 
 8      vector<int> out={};
 9      for (int i=1;i<numbers.size();i++)  <-- BUG
10      {
11          out.push_back(delimeter);
12          out.push_back(numbers[i]);
13  
14      }
15      return out;
16  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `missing logic`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **A statement is missing** near body line 2: the correct version contains `if (numbers.size()>0) out.push_back(numbers[0]);` which is absent from the buggy version.

---

### Chunk `CPP-14`  (source: `CPP/8` — `sum_product`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
vector<int> sum_product(vector<int> numbers){
    int sum=0,product=0;
    for (int i=0;i<numbers.size();i++)
    {
        sum+=numbers[i];
        product*=numbers[i];
    }
    return {sum,product};
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<math.h>
 6  #include<stdlib.h>
 7  vector<int> sum_product(vector<int> numbers){
 8      int sum=0,product=0;  <-- BUG
 9      for (int i=0;i<numbers.size();i++)
10      {
11          sum+=numbers[i];
12          product*=numbers[i];
13      }
14      return {sum,product};
15  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 1** was changed:
    - buggy:    `int sum=0,product=0;`
    - correct:  `int sum=0,product=1;`

---

### Chunk `CPP-15`  (source: `CPP/9` — `rolling_max`)

- **Difficulty:** medium
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
vector<int> rolling_max(vector<int> numbers){
    vector<int> out;
    int max=0;
    for (int i=0;i<numbers.size();i++)
    {
        if (numbers[i]>max) max=numbers[i];
        out.push_back(numbers[i]);
    }
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<math.h>
 6  #include<stdlib.h>
 7  vector<int> rolling_max(vector<int> numbers){
 8      vector<int> out;
 9      int max=0;
10      for (int i=0;i<numbers.size();i++)
11      {
12          if (numbers[i]>max) max=numbers[i];
13          out.push_back(numbers[i]);  <-- BUG
14      }
15      return out;
16  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `variable misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 6** was changed:
    - buggy:    `out.push_back(numbers[i]);`
    - correct:  `out.push_back(max);`

---

### Chunk `CPP-16`  (source: `CPP/7` — `filter_by_substring`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
#include<string>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
vector<string> filter_by_substring(vector<string> strings, string substring){
    vector<string> out;
    for (int i=0;i<strings.size();i++)
    {
        if (strings[i].find(substring)!=strings[i].npos)
        out.push_back(strings[i]);
    }
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  #include<string>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<math.h>
 7  #include<stdlib.h>
 8  vector<string> filter_by_substring(vector<string> strings, string substring){
 9      vector<string> out;
10      for (int i=0;i<strings.size();i++)
11      {
12          if (strings[i].find(substring)!=strings[i].npos)
13          out.push_back(strings[i]);
14      }
15      return out;
16  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-17`  (source: `CPP/13` — `greatest_common_divisor`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
int greatest_common_divisor(int a, int b){
    int out,m;
    while (true){
        if (a<b) 
        {
            m=a;a=b;b=m;
        }
        a=a%b;
        if (a==0) return b;
    }
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  using namespace std;
 3  #include<algorithm>
 4  #include<math.h>
 5  #include<stdlib.h>
 6  int greatest_common_divisor(int a, int b){
 7      int out,m;
 8      while (true){
 9          if (a<b) 
10          {
11              m=a;a=b;b=m;
12          }
13          a=a%b;
14          if (a==0) return b;
15      }
16  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-18`  (source: `CPP/14` — `all_prefixes`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
#include<string>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
vector<string> all_prefixes(string str){
    vector<string> out;
    string current="";
    for (int i=0;i<str.length();i++)
    {
        current=current+str[i];
        out.push_back(current);
    }
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  #include<string>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<math.h>
 7  #include<stdlib.h>
 8  vector<string> all_prefixes(string str){
 9      vector<string> out;
10      string current="";
11      for (int i=0;i<str.length();i++)
12      {
13          current=current+str[i];
14          out.push_back(current);
15      }
16      return out;
17  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-19`  (source: `CPP/20` — `find_closest_elements`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<stdlib.h>
vector<float> find_closest_elements(vector<float> numbers){
    vector<float> out={};
    for (int i=0;i<numbers.size();i++)
    for (int j=i+1;j<numbers.size();j++)
        if (out.size()==0 or abs(numbers[i]-numbers[j])<abs(out[0]-out[1]))
            out={numbers[i],numbers[j]};
    if (out[0]>out[1])
        out={out[1],out[0]};
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<stdlib.h>
 7  vector<float> find_closest_elements(vector<float> numbers){
 8      vector<float> out={};
 9      for (int i=0;i<numbers.size();i++)
10      for (int j=i+1;j<numbers.size();j++)
11          if (out.size()==0 or abs(numbers[i]-numbers[j])<abs(out[0]-out[1]))
12              out={numbers[i],numbers[j]};
13      if (out[0]>out[1])
14          out={out[1],out[0]};
15      return out;
16  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-20`  (source: `CPP/21` — `rescale_to_unit`)

- **Difficulty:** medium
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<stdlib.h>
vector<float> rescale_to_unit(vector<float> numbers){ 
    float min=100000,max=-100000;
    for (int i=0;i<numbers.size();i++)
        {
            if (numbers[i]<min) min=numbers[i];
            if (numbers[i]>max) max=numbers[i];
        }
    for (int i=0;i<numbers.size();i++)
        numbers[i]=(numbers[i]-min)/(max-min);
    return numbers;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<stdlib.h>
 7  vector<float> rescale_to_unit(vector<float> numbers){ 
 8      float min=100000,max=-100000;
 9      for (int i=0;i<numbers.size();i++)
10          {
11              if (numbers[i]<min) min=numbers[i];
12              if (numbers[i]>max) max=numbers[i];
13          }
14      for (int i=0;i<numbers.size();i++)
15          numbers[i]=(numbers[i]-min)/(max-min);
16      return numbers;
17  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

## C++ — HARD

### Chunk `CPP-21`  (source: `CPP/1` — `separate_paren_groups`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
#include<string>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
vector<string> separate_paren_groups(string paren_string){
    vector<string> all_parens;
    string current_paren;
    int level=0;
    char chr;
    int i;
    for (i=0;i<paren_string.length();i++)
    {
        chr=paren_string[i];
        if (chr=='(')
        {
        level+=1;
        current_paren+=chr;
        }
        if (chr==')')
        {
            level-=1;
            current_paren+=chr;
            if (level<0){
                all_parens.push_back(current_paren);
                current_paren="";
            }
        }
    }
    return all_parens;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  #include<string>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<math.h>
 7  #include<stdlib.h>
 8  vector<string> separate_paren_groups(string paren_string){
 9      vector<string> all_parens;
10      string current_paren;
11      int level=0;
12      char chr;
13      int i;
14      for (i=0;i<paren_string.length();i++)
15      {
16          chr=paren_string[i];
17          if (chr=='(')
18          {
19          level+=1;
20          current_paren+=chr;
21          }
22          if (chr==')')
23          {
24              level-=1;
25              current_paren+=chr;
26              if (level<0){  <-- BUG
27                  all_parens.push_back(current_paren);
28                  current_paren="";
29              }
30          }
31      }
32      return all_parens;
33  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `operator misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 18** was changed:
    - buggy:    `if (level<0){`
    - correct:  `if (level==0){`

---

### Chunk `CPP-22`  (source: `CPP/6` — `parse_nested_parens`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<vector>
#include<string>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
vector<int> parse_nested_parens(string paren_string){
    vector<int> all_levels;
    string current_paren;
    int level=0,max_level=0;
    char chr;
    int i;
    for (i=0;i<paren_string.length();i++)
    {
        chr=paren_string[i];
        if (chr=='(')
        {
        level+=1;
        if (level>max_level) max_level=level;
        current_paren+=chr;
        }
        if (chr==')')
        {
            max_level-=1;
            current_paren+=chr;
            if (level==0){
                all_levels.push_back(max_level);
                current_paren="";
                max_level=0;
            }
        }
    }
    return all_levels;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<vector>
 3  #include<string>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<math.h>
 7  #include<stdlib.h>
 8  vector<int> parse_nested_parens(string paren_string){
 9      vector<int> all_levels;
10      string current_paren;
11      int level=0,max_level=0;
12      char chr;
13      int i;
14      for (i=0;i<paren_string.length();i++)
15      {
16          chr=paren_string[i];
17          if (chr=='(')
18          {
19          level+=1;
20          if (level>max_level) max_level=level;
21          current_paren+=chr;
22          }
23          if (chr==')')
24          {
25              max_level-=1;  <-- BUG
26              current_paren+=chr;
27              if (level==0){
28                  all_levels.push_back(max_level);
29                  current_paren="";
30                  max_level=0;
31              }
32          }
33      }
34      return all_levels;
35  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `variable misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 17** was changed:
    - buggy:    `max_level-=1;`
    - correct:  `level-=1;`

---

### Chunk `CPP-23`  (source: `CPP/10` — `make_palindrome`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<string>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
bool is_palindrome(string str){
    string s(str.rbegin(),str.rend());
    return s==str;
}
string make_palindrome(string str){
   int i;
   for (i=0;i<str.length();i++)
   {
        if (is_palindrome(str))
        {
            string nstr;
            nstr=str.substr(0,i);
            string n2str(nstr.rbegin(),nstr.rend());
            return str+n2str;
        }
   }
   string n2str(str.rbegin(),str.rend());
   return str+n2str;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<string>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<math.h>
 6  #include<stdlib.h>
 7  bool is_palindrome(string str){
 8      string s(str.rbegin(),str.rend());
 9      return s==str;
10  }
11  string make_palindrome(string str){
12     int i;
13     for (i=0;i<str.length();i++)
14     {
15          if (is_palindrome(str))  <-- BUG
16          {
17              string nstr;
18              nstr=str.substr(0,i);
19              string n2str(nstr.rbegin(),nstr.rend());
20              return str+n2str;
21          }
22     }
23     string n2str(str.rbegin(),str.rend());
24     return str+n2str;
25  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `missing logic`
- **Failure symptom:** `stackoverflow`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 4** was changed:
    - buggy:    `if (is_palindrome(str))`
    - correct:  `string rstr=str.substr(i);`
  - **Body line None** was changed:
    - buggy:    ``
    - correct:  `if (is_palindrome(rstr))`

---

### Chunk `CPP-24`  (source: `CPP/11` — `string_xor`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<string>
using namespace std;
#include<algorithm>
#include<math.h>
#include<stdlib.h>
string string_xor(string a,string b){
    string output="";
    for (int i=0;(i<a.length() and i<b.length());i++)
    {
        if (i<a.length() and i<b.length())
        {
            if (a[i]== b[i]) 
            {
                output+='1';
            }  
            else output+='0';
        }
        else
        {
            if (i>=a.length()) 
            {
            output+=b[i];
            }
            else output+=a[i];
        }
    }
    return output;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<string>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<math.h>
 6  #include<stdlib.h>
 7  string string_xor(string a,string b){
 8      string output="";
 9      for (int i=0;(i<a.length() and i<b.length());i++)
10      {
11          if (i<a.length() and i<b.length())
12          {
13              if (a[i]== b[i]) 
14              {
15                  output+='1';  <-- BUG
16              }  
17              else output+='0';  <-- BUG
18          }
19          else
20          {
21              if (i>=a.length()) 
22              {
23              output+=b[i];
24              }
25              else output+=a[i];
26          }
27      }
28      return output;
29  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 8** was changed:
    - buggy:    `output+='1';`
    - correct:  `output+='0';`
  - **Body line 10** was changed:
    - buggy:    `else output+='0';`
    - correct:  `else output+='1';`

---

### Chunk `CPP-25`  (source: `CPP/17` — `parse_music`)

- **Difficulty:** hard
- **Has bug:** YES

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
#include<string>
using namespace std;
#include<algorithm>
#include<stdlib.h>
vector<int> parse_music(string music_string){ 
    string current="";
    vector<int> out={};
    if (music_string.length()>0)
        music_string=music_string+' ';
    for (int i=0;i<music_string.length();i++)
    {
        if (music_string[i]==' ')
        {
            if (current=="o") out.push_back(3);
            if (current=="o|") out.push_back(2);
            if (current==".|") out.push_back(1);
            current="";
        }
        else current+=music_string[i];
    }
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  #include<string>
 5  using namespace std;
 6  #include<algorithm>
 7  #include<stdlib.h>
 8  vector<int> parse_music(string music_string){ 
 9      string current="";
10      vector<int> out={};
11      if (music_string.length()>0)
12          music_string=music_string+' ';
13      for (int i=0;i<music_string.length();i++)
14      {
15          if (music_string[i]==' ')
16          {
17              if (current=="o") out.push_back(3);  <-- BUG
18              if (current=="o|") out.push_back(2);
19              if (current==".|") out.push_back(1);
20              current="";
21          }
22          else current+=music_string[i];
23      }
24      return out;
25  }
```

**Answer key:**

- **Bug type (HumanEvalPack taxonomy):** `value misuse`
- **Failure symptom:** `incorrect output`
- **Where (line numbers refer to the *body* of the function, i.e. excluding the declaration/signature):**
  - **Body line 9** was changed:
    - buggy:    `if (current=="o") out.push_back(3);`
    - correct:  `if (current=="o") out.push_back(4);`

---

### Chunk `CPP-26`  (source: `CPP/19` — `sort_numbers`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<string>
#include<map>
using namespace std;
#include<algorithm>
#include<stdlib.h>
string sort_numbers(string numbers){
    map<string,int> tonum={{"zero",0},{"one",1},{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},{"seven",7},{"eight",8},{"nine",9}};
    map<int,string> numto={{0,"zero"},{1,"one"},{2,"two"},{3,"three"},{4,"four"},{5,"five"},{6,"six"},{7,"seven"},{8,"eight"},{9,"nine"}};
    int count[10];
    for (int i=0;i<10;i++)
        count[i]=0;
    string out="",current="";
    if (numbers.length()>0) numbers=numbers+' ';
    for (int i=0;i<numbers.length();i++)
        if (numbers[i]==' ')
        {
            count[tonum[current]]+=1;
            current="";
        }
        else current+=numbers[i];
    for (int i=0;i<10;i++)
        for (int j=0;j<count[i];j++)
            out=out+numto[i]+' ';
    if (out.length()>0) out.pop_back();
    return out;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<string>
 4  #include<map>
 5  using namespace std;
 6  #include<algorithm>
 7  #include<stdlib.h>
 8  string sort_numbers(string numbers){
 9      map<string,int> tonum={{"zero",0},{"one",1},{"two",2},{"three",3},{"four",4},{"five",5},{"six",6},{"seven",7},{"eight",8},{"nine",9}};
10      map<int,string> numto={{0,"zero"},{1,"one"},{2,"two"},{3,"three"},{4,"four"},{5,"five"},{6,"six"},{7,"seven"},{8,"eight"},{9,"nine"}};
11      int count[10];
12      for (int i=0;i<10;i++)
13          count[i]=0;
14      string out="",current="";
15      if (numbers.length()>0) numbers=numbers+' ';
16      for (int i=0;i<numbers.length();i++)
17          if (numbers[i]==' ')
18          {
19              count[tonum[current]]+=1;
20              current="";
21          }
22          else current+=numbers[i];
23      for (int i=0;i<10;i++)
24          for (int j=0;j<count[i];j++)
25              out=out+numto[i]+' ';
26      if (out.length()>0) out.pop_back();
27      return out;
28  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-27`  (source: `CPP/26` — `remove_duplicates`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
#include<algorithm>
using namespace std;
#include<stdlib.h>
vector<int> remove_duplicates(vector<int> numbers){
    vector<int> out={};
    vector<int> has1={};
    vector<int> has2={};
    for (int i=0;i<numbers.size();i++)
    {
        if (find(has2.begin(),has2.end(),numbers[i])!=has2.end()) continue;
        if (find(has1.begin(),has1.end(),numbers[i])!=has1.end())
        {

            has2.push_back(numbers[i]);
        }
        else has1.push_back(numbers[i]);
    }
    for (int i=0;i<numbers.size();i++)
    if (find(has2.begin(),has2.end(),numbers[i])==has2.end())
        out.push_back(numbers[i]);
    return out;


}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  #include<algorithm>
 5  using namespace std;
 6  #include<stdlib.h>
 7  vector<int> remove_duplicates(vector<int> numbers){
 8      vector<int> out={};
 9      vector<int> has1={};
10      vector<int> has2={};
11      for (int i=0;i<numbers.size();i++)
12      {
13          if (find(has2.begin(),has2.end(),numbers[i])!=has2.end()) continue;
14          if (find(has1.begin(),has1.end(),numbers[i])!=has1.end())
15          {
16  
17              has2.push_back(numbers[i]);
18          }
19          else has1.push_back(numbers[i]);
20      }
21      for (int i=0;i<numbers.size();i++)
22      if (find(has2.begin(),has2.end(),numbers[i])==has2.end())
23          out.push_back(numbers[i]);
24      return out;
25  
26  
27  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-28`  (source: `CPP/32` — `find_zero`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<stdlib.h>
double poly(vector<double> xs, double x){
    double sum=0;
    int i;
    for (i=0;i<xs.size();i++)
    {
        sum+=xs[i]*pow(x,i);
    }
    return sum;
}

double find_zero(vector<double> xs){
    double ans=0;
    double value;
    value=poly(xs,ans);
    while (abs(value)>1e-6)
    {
        double driv=0;
        for (int i=1;i<xs.size();i++)
        {
            driv+=xs[i]*pow(ans,i-1)*i;
        }
        ans=ans-value/driv;
        value=poly(xs,ans);
    }
    return ans;

}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<stdlib.h>
 7  double poly(vector<double> xs, double x){
 8      double sum=0;
 9      int i;
10      for (i=0;i<xs.size();i++)
11      {
12          sum+=xs[i]*pow(x,i);
13      }
14      return sum;
15  }
16  
17  double find_zero(vector<double> xs){
18      double ans=0;
19      double value;
20      value=poly(xs,ans);
21      while (abs(value)>1e-6)
22      {
23          double driv=0;
24          for (int i=1;i<xs.size();i++)
25          {
26              driv+=xs[i]*pow(ans,i-1)*i;
27          }
28          ans=ans-value/driv;
29          value=poly(xs,ans);
30      }
31      return ans;
32  
33  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-29`  (source: `CPP/39` — `prime_fib`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
using namespace std;
#include<algorithm>
#include<stdlib.h>
int prime_fib(int n){
    int f1,f2,m;
    f1=1;f2=2;
    int count=0;
    while (count<n)
    {
        f1=f1+f2;
        m=f1;f1=f2;f2=m;
        bool isprime=true;
        for (int w=2;w*w<=f1;w++)
            if (f1%w==0)
            {
             isprime=false; break;
            }
        if (isprime) count+=1;
        if (count==n) return f1;
    }

}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  using namespace std;
 4  #include<algorithm>
 5  #include<stdlib.h>
 6  int prime_fib(int n){
 7      int f1,f2,m;
 8      f1=1;f2=2;
 9      int count=0;
10      while (count<n)
11      {
12          f1=f1+f2;
13          m=f1;f1=f2;f2=m;
14          bool isprime=true;
15          for (int w=2;w*w<=f1;w++)
16              if (f1%w==0)
17              {
18               isprime=false; break;
19              }
20          if (isprime) count+=1;
21          if (count==n) return f1;
22      }
23  
24  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

### Chunk `CPP-30`  (source: `CPP/69` — `search`)

- **Difficulty:** hard
- **Has bug:** NO (clean control)

**Ready-to-paste prompt** (copy the whole block including the prompt header into the LLM chat):

````text
You are a senior software engineer performing a code review. Below is a cpp function. Review it for bugs that would cause incorrect behaviour.
For each bug you should identify the bug itself and where it is (line number within the code you received). If you are confident that the function has no bugs, respond with exactly the string: "NO BUGS".
CODE:
```cpp
#include<stdio.h>
#include<math.h>
#include<vector>
using namespace std;
#include<algorithm>
#include<stdlib.h>
int search(vector<int> lst){
    vector<vector<int>> freq={};
    int max=-1;
    for (int i=0;i<lst.size();i++)
    {
        bool has=false;
        for (int j=0;j<freq.size();j++)
            if (lst[i]==freq[j][0]) 
            {
            freq[j][1]+=1;
            has=true;
            if (freq[j][1]>=freq[j][0] and freq[j][0]>max) max=freq[j][0];
            }
        if (not(has)) 
        {
        freq.push_back({lst[i],1});
        if (max==-1 and lst[i]==1) max=1;
        }
    }
    return max;
}
```
````

**Code (with line numbers, for reference and classification):**

```cpp
 1  #include<stdio.h>
 2  #include<math.h>
 3  #include<vector>
 4  using namespace std;
 5  #include<algorithm>
 6  #include<stdlib.h>
 7  int search(vector<int> lst){
 8      vector<vector<int>> freq={};
 9      int max=-1;
10      for (int i=0;i<lst.size();i++)
11      {
12          bool has=false;
13          for (int j=0;j<freq.size();j++)
14              if (lst[i]==freq[j][0]) 
15              {
16              freq[j][1]+=1;
17              has=true;
18              if (freq[j][1]>=freq[j][0] and freq[j][0]>max) max=freq[j][0];
19              }
20          if (not(has)) 
21          {
22          freq.push_back({lst[i],1});
23          if (max==-1 and lst[i]==1) max=1;
24          }
25      }
26      return max;
27  }
```

**Answer key:**

**No bug.** Reference response: `NO BUGS`

---

