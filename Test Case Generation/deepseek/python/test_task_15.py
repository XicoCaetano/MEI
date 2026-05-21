import pytest
from your_module import string_sequence

def test_zero():
    """Test with n = 0"""
    assert string_sequence(0) == '0'

def test_positive_number():
    """Test with a typical positive integer"""
    assert string_sequence(5) == '0 1 2 3 4 5'

def test_one():
    """Test with n = 1"""
    assert string_sequence(1) == '0 1'

def test_two():
    """Test with n = 2"""
    assert string_sequence(2) == '0 1 2'

def test_large_number():
    """Test with a larger number to ensure correct spacing"""
    result = string_sequence(10)
    expected = '0 1 2 3 4 5 6 7 8 9 10'
    assert result == expected

def test_negative_number():
    """Test with negative integer - should still work as range handles negatives"""
    result = string_sequence(-5)
    expected = ' '.join([str(x) for x in range(-5 + 1)])
    assert result == expected

def test_very_large_number():
    """Test with a very large number to ensure performance and correctness"""
    n = 1000
    result = string_sequence(n)
    expected = ' '.join([str(x) for x in range(n + 1)])
    assert result == expected

def test_return_type():
    """Test that the function always returns a string"""
    assert isinstance(string_sequence(0), str)
    assert isinstance(string_sequence(1), str)
    assert isinstance(string_sequence(100), str)
    assert isinstance(string_sequence(-10), str)

def test_no_trailing_spaces():
    """Test that there are no trailing spaces in the output"""
    result = string_sequence(5)
    assert not result.endswith(' ')
    assert result[-1] != ' ' if result else True

def test_no_leading_spaces():
    """Test that there are no leading spaces in the output"""
    result = string_sequence(5)
    assert not result.startswith(' ')
    assert result[0] != ' ' if result else True

def test_consecutive_numbers():
    """Test that numbers are consecutive and properly spaced"""
    result = string_sequence(10)
    numbers = [int(x) for x in result.split()]
    assert numbers == list(range(11))
    assert all(numbers[i] + 1 == numbers[i+1] for i in range(len(numbers)-1))

def test_string_format():
    """Test the exact string format with multiple numbers"""
    n = 3
    result = string_sequence(n)
    expected = '0 1 2 3'
    assert result == expected
    assert result.count(' ') == n  # n+1 numbers produce n spaces

def test_boundary_large_range():
    """Test boundary with maximum reasonable number"""
    n = 10000
    result = string_sequence(n)
    assert isinstance(result, str)
    assert len(result.split()) == n + 1