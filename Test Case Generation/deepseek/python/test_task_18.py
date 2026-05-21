import pytest
from your_module import how_many_times

def test_empty_string():
    """Test when the main string is empty."""
    assert how_many_times('', 'a') == 0
    assert how_many_times('', '') == 0
    assert how_many_times('', 'abc') == 0

def test_empty_substring():
    """Test when the substring is empty."""
    assert how_many_times('abc', '') == 0
    assert how_many_times('', '') == 0
    assert how_many_times('a', '') == 0
    assert how_many_times('aaa', '') == 0

def test_single_character_overlapping():
    """Test overlapping occurrences with single character substrings."""
    assert how_many_times('aaa', 'a') == 3
    assert how_many_times('aaaa', 'a') == 4
    assert how_many_times('abc', 'a') == 1
    assert how_many_times('abc', 'd') == 0

def test_longer_substring_overlapping():
    """Test overlapping occurrences with longer substrings."""
    assert how_many_times('aaaa', 'aa') == 3
    assert how_many_times('aaa', 'aa') == 2
    assert how_many_times('ababa', 'aba') == 2
    assert how_many_times('abcabc', 'abc') == 2
    assert how_many_times('aaaaa', 'aaa') == 3

def test_no_overlapping_possible():
    """Test when substring cannot overlap due to length constraints."""
    assert how_many_times('ababa', 'aba') == 2  # Overlaps actually possible
    assert how_many_times('abcde', 'abc') == 1
    assert how_many_times('abcde', 'bcd') == 1
    assert how_many_times('abcde', 'xyz') == 0

def test_substring_longer_than_string():
    """Test when substring is longer than the main string."""
    assert how_many_times('a', 'aa') == 0
    assert how_many_times('abc', 'abcd') == 0
    assert how_many_times('', 'abc') == 0

def test_substring_equal_to_string():
    """Test when substring equals the entire string."""
    assert how_many_times('abc', 'abc') == 1
    assert how_many_times('a', 'a') == 1
    assert how_many_times('', '') == 0

def test_special_characters():
    """Test with special characters and whitespace."""
    assert how_many_times('hello world', 'o') == 2
    assert how_many_times('hello hello', 'hello') == 2
    assert how_many_times('test test test', 'test') == 3
    assert how_many_times('!!!', '!') == 3
    assert how_many_times('abc123abc', 'abc') == 2

def test_case_sensitivity():
    """Test that the function is case-sensitive."""
    assert how_many_times('AaAa', 'a') == 2
    assert how_many_times('ABCabc', 'abc') == 1
    assert how_many_times('Test', 'test') == 0

def test_edge_cases():
    """Test various edge cases."""
    assert how_many_times('a', 'a') == 1
    assert how_many_times('a', 'b') == 0
    assert how_many_times('ab', 'ab') == 1
    assert how_many_times('ab', 'abc') == 0
    assert how_many_times('ababa', 'bab') == 1
    assert how_many_times('aaaaaa', 'aaaa') == 3

def test_numeric_strings():
    """Test with numeric strings."""
    assert how_many_times('123123', '123') == 2
    assert how_many_times('111', '11') == 2
    assert how_many_times('12345', '23') == 1
    assert how_many_times('00000', '00') == 4

def test_large_overlap_pattern():
    """Test patterns that can overlap significantly."""
    assert how_many_times('aaaaa', 'aa') == 4
    assert how_many_times('aaaaa', 'aaa') == 3
    assert how_many_times('aaaaa', 'aaaa') == 2
    assert how_many_times('aaaaa', 'aaaaa') == 1