import pytest
from typing import List

def sort_numbers(numbers: str) -> str:
    """ Input is a space-delimited string of numberals from 'zero' to 'nine'.
    Valid choices are 'zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight' and 'nine'.
    Return the string with numbers sorted from smallest to largest
    >>> sort_numbers('three one five')
    'one three five'
    """
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
    return ' '.join(sorted([x for x in numbers.split(' ') if x], key=lambda x: value_map[x]))

def test_sort_numbers_basic():
    """Test standard functionality with basic unsorted input."""
    assert sort_numbers('three one five') == 'one three five'

def test_sort_numbers_all_elements():
    """Test all valid mapping keys in reverse order to ensure full coverage and sorting."""
    input_str = 'nine eight seven six five four three two one zero'
    expected = 'zero one two three four five six seven eight nine'
    assert sort_numbers(input_str) == expected

def test_sort_numbers_empty_string():
    """Test behavior with an empty string."""
    assert sort_numbers('') == ''

def test_sort_numbers_duplicates():
    """Test sorting when multiple instances of the same word exist."""
    assert sort_numbers('zero five two zero five') == 'zero zero two five five'

def test_sort_numbers_multiple_spaces():
    """Test that multiple spaces are handled correctly by the list comprehension (if x)."""
    assert sort_numbers('one  three   two') == 'one two three'

def test_sort_numbers_single_element():
    """Test a single valid element."""
    assert sort_numbers('seven') == 'seven'

def test_sort_numbers_already_sorted():
    """Test input that is already in the correct order."""
    assert sort_numbers('zero one two') == 'zero one two'

def test_sort_numbers_invalid_key():
    """Test that an invalid key (not in value_map) raises a KeyError."""
    with pytest.raises(KeyError):
        sort_numbers('one ten five')

def test_sort_numbers_trailing_leading_spaces():
    """Test input with leading and trailing whitespace."""
    assert sort_numbers(' nine zero ') == 'zero nine'