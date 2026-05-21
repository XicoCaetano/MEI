import pytest
from typing import List

def all_prefixes(string: str) -> List[str]:
    """ Return list of all prefixes from shortest to longest of the input string
    >>> all_prefixes('abc')
    ['a', 'ab', 'abc']
    """
    result = []

    for i in range(len(string)):
        result.append(string[:i+1])
    return result

def test_all_prefixes_standard_string():
    """Tests a standard string with multiple characters."""
    assert all_prefixes('abc') == ['a', 'ab', 'abc']
    assert all_prefixes('test') == ['t', 'te', 'tes', 'test']

def test_all_prefixes_empty_string():
    """Tests the edge case of an empty string."""
    assert all_prefixes('') == []

def test_all_prefixes_single_character():
    """Tests a string with only one character."""
    assert all_prefixes('a') == ['a']

def test_all_prefixes_whitespace():
    """Tests strings containing whitespace."""
    assert all_prefixes(' ') == [' ']
    assert all_prefixes(' a b') == [' ', ' a', ' a ', ' a b']

def test_all_prefixes_special_characters():
    """Tests strings with special characters and numbers."""
    assert all_prefixes('12@') == ['1', '12', '12@']

def test_all_prefixes_long_string():
    """Tests a relatively long string to ensure loop integrity."""
    input_str = "quality"
    expected = ['q', 'qu', 'qua', 'qual', 'quali', 'qualit', 'quality']
    assert all_prefixes(input_str) == expected

def test_all_prefixes_unicode():
    """Tests strings with unicode/multi-byte characters."""
    assert all_prefixes('🚀⭐') == ['🚀', '🚀⭐']

@pytest.mark.parametrize("input_val, expected_output", [
    ("cat", ["c", "ca", "cat"]),
    ("A", ["A"]),
    ("", []),
])
def test_all_prefixes_parametrized(input_val, expected_output):
    """Parametrized test for multiple scenarios."""
    assert all_prefixes(input_val) == expected_output