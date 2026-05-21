import pytest
from typing import List

def parse_nested_parens(paren_string: str) -> List[int]:
    """ Input to this function is a string represented multiple groups for nested parentheses separated by spaces.
    For each of the group, output the deepest level of nesting of parentheses.
    E.g. (()()) has maximum two levels of nesting while ((())) has three.

    >>> parse_nested_parens('(()()) ((())) () ((())()())')
    [2, 3, 1, 3]
    """
    def parse_paren_group(s):
        depth = 0
        max_depth = 0
        for c in s:
            if c == '(':
                depth += 1
                max_depth = max(depth, max_depth)
            else:
                depth -= 1

        return max_depth

    return [parse_paren_group(x) for x in paren_string.split(' ') if x]

def test_provided_example():
    """Tests the example provided in the function docstring."""
    input_str = '(()()) ((())) () ((())()())'
    expected = [2, 3, 1, 3]
    assert parse_nested_parens(input_str) == expected

def test_empty_string():
    """Tests that an empty string returns an empty list."""
    assert parse_nested_parens("") == []

def test_only_spaces():
    """Tests that a string with only spaces returns an empty list."""
    assert parse_nested_parens("   ") == []

def test_single_level():
    """Tests simple non-nested parentheses."""
    assert parse_nested_parens("() () ()") == [1, 1, 1]

def test_deep_nesting():
    """Tests high levels of nesting."""
    assert parse_nested_parens("((((((()))))))") == [7]

def test_varying_whitespace():
    """Tests handling of multiple spaces between groups."""
    assert parse_nested_parens("()    (( ))") == [1, 2]

def test_mismatched_closing_first():
    """
    Tests edge case behavior with closing parens. 
    Based on the provided logic, depth goes negative but max_depth tracks the peak.
    """
    assert parse_nested_parens(")))(((") == [1]

def test_unbalanced_open():
    """Tests groups that never close."""
    assert parse_nested_parens("(((") == [3]

def test_complex_mixed_nesting():
    """Tests a complex sequence of nested and sequential parens."""
    assert parse_nested_parens("(()(())) ((()()()))") == [3, 3]

@pytest.mark.parametrize("input_val, expected_val", [
    ("()", [1]),
    ("(())", [2]),
    ("((()))", [3]),
    ("(()())", [2]),
    ("()()", [1]),
])
def test_parametrized_cases(input_val, expected_val):
    """Parametrized test for standard balanced cases."""
    assert parse_nested_parens(input_val) == expected_val