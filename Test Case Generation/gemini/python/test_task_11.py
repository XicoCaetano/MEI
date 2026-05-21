import pytest
from typing import List

def string_xor(a: str, b: str) -> str:
    """ Input are two strings a and b consisting only of 1s and 0s.
    Perform binary XOR on these inputs and return result also as a string.
    >>> string_xor('010', '110')
    '100'
    """
    def xor(i, j):
        if i == j:
            return '0'
        else:
            return '1'

    return ''.join(xor(x, y) for x, y in zip(a, b))

def test_string_xor_basic():
    """Tests basic XOR functionality with provided example."""
    assert string_xor('010', '110') == '100'

def test_string_xor_identical():
    """Tests XOR with identical strings (should return all zeros)."""
    assert string_xor('111', '111') == '000'
    assert string_xor('000', '000') == '000'

def test_string_xor_opposites():
    """Tests XOR with opposite strings (should return all ones)."""
    assert string_xor('111', '000') == '111'
    assert string_xor('0101', '1010') == '1111'

def test_string_xor_empty_strings():
    """Tests XOR with empty strings."""
    assert string_xor('', '') == ''

def test_string_xor_different_lengths():
    """
    Tests XOR with strings of different lengths.
    zip stops at the shortest input, so the result length should match the shortest string.
    """
    assert string_xor('111', '01') == '10'
    assert string_xor('01', '111') == '10'
    assert string_xor('', '111') == ''

@pytest.mark.parametrize("a, b, expected", [
    ('1', '1', '0'),
    ('1', '0', '1'),
    ('0', '1', '1'),
    ('0', '0', '0'),
    ('101010', '101010', '000000'),
    ('111000', '000111', '111111'),
])
def test_string_xor_parametrized(a, b, expected):
    """Parametrized tests covering all bit combinations and longer strings."""
    assert string_xor(a, b) == expected

def test_string_xor_line_coverage_branching():
    """Explicitly triggers both branches of the internal xor function."""
    # Triggers i == j (returns '0')
    assert string_xor('1', '1') == '0'
    # Triggers i != j (returns '1')
    assert string_xor('1', '0') == '1'