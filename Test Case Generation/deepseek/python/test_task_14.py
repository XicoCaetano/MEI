import pytest
from typing import List
from your_module import all_prefixes  # Replace with actual module name

def test_empty_string():
    """Test with empty string"""
    assert all_prefixes("") == []

def test_single_character():
    """Test with single character string"""
    assert all_prefixes("a") == ["a"]

def test_two_characters():
    """Test with two character string"""
    assert all_prefixes("ab") == ["a", "ab"]

def test_three_characters():
    """Test with three character string (docstring example)"""
    assert all_prefixes("abc") == ["a", "ab", "abc"]

def test_long_string():
    """Test with longer string"""
    assert all_prefixes("hello") == ["h", "he", "hel", "hell", "hello"]

def test_string_with_spaces():
    """Test string containing spaces"""
    assert all_prefixes("a b") == ["a", "a ", "a b"]

def test_string_with_numbers():
    """Test string containing numbers"""
    assert all_prefixes("123") == ["1", "12", "123"]

def test_string_with_special_characters():
    """Test string containing special characters"""
    assert all_prefixes("@#$") == ["@", "@#", "@#$"]

def test_unicode_string():
    """Test with unicode characters"""
    assert all_prefixes("café") == ["c", "ca", "caf", "café"]

def test_very_long_string():
    """Test with very long string"""
    long_string = "x" * 1000
    result = all_prefixes(long_string)
    assert len(result) == 1000
    assert result[0] == "x"
    assert result[-1] == long_string
    assert all(len(result[i]) == i + 1 for i in range(len(result)))

def test_string_result_length():
    """Test that number of prefixes equals string length"""
    test_strings = ["", "a", "ab", "abc", "abcd", "hello world"]
    for s in test_strings:
        result = all_prefixes(s)
        assert len(result) == len(s)

def test_prefix_incremental_building():
    """Test that each prefix builds upon the previous one"""
    test_string = "testing"
    result = all_prefixes(test_string)
    
    for i in range(1, len(result)):
        assert result[i].startswith(result[i-1])
        assert len(result[i]) == len(result[i-1]) + 1

def test_output_type():
    """Test that return type is List[str]"""
    result = all_prefixes("test")
    assert isinstance(result, list)
    assert all(isinstance(item, str) for item in result)

def test_non_mutability():
    """Test that function doesn't have side effects"""
    original = "abc"
    result = all_prefixes(original)
    assert original == "abc"
    assert result == ["a", "ab", "abc"]

def test_verify_all_prefixes_correct():
    """Test explicit verification of all prefixes for a given string"""
    test_string = "python"
    result = all_prefixes(test_string)
    expected = ["p", "py", "pyt", "pyth", "pytho", "python"]
    assert result == expected

def test_repeated_characters():
    """Test string with repeated characters"""
    assert all_prefixes("aaa") == ["a", "aa", "aaa"]

def test_mixed_case():
    """Test string with mixed case"""
    assert all_prefixes("AbC") == ["A", "Ab", "AbC"]