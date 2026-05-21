import pytest
from typing import List
from your_module import filter_by_substring

def test_empty_list():
    """Test with empty list of strings"""
    assert filter_by_substring([], 'a') == []

def test_empty_substring():
    """Test with empty substring (should match all strings)"""
    strings = ['abc', 'def', 'ghi']
    assert filter_by_substring(strings, '') == ['abc', 'def', 'ghi']

def test_single_match():
    """Test with single matching string"""
    strings = ['abc', 'def', 'ghi']
    assert filter_by_substring(strings, 'ab') == ['abc']

def test_multiple_matches():
    """Test with multiple matching strings"""
    strings = ['abc', 'bacd', 'cde', 'array']
    assert filter_by_substring(strings, 'a') == ['abc', 'bacd', 'array']

def test_no_matches():
    """Test with no matching strings"""
    strings = ['abc', 'def', 'ghi']
    assert filter_by_substring(strings, 'z') == []

def test_all_match():
    """Test where all strings contain the substring"""
    strings = ['cat', 'bat', 'hat']
    assert filter_by_substring(strings, 'at') == ['cat', 'bat', 'hat']

def test_substring_at_beginning():
    """Test substring at the beginning of strings"""
    strings = ['prefix1', 'prefix2', 'suffix']
    assert filter_by_substring(strings, 'pre') == ['prefix1', 'prefix2']

def test_substring_at_end():
    """Test substring at the end of strings"""
    strings = ['hello.py', 'world.py', 'test.txt']
    assert filter_by_substring(strings, '.py') == ['hello.py', 'world.py']

def test_substring_in_middle():
    """Test substring in the middle of strings"""
    strings = ['startmiddleend', 'beginmiddlefinish', 'nomatch']
    assert filter_by_substring(strings, 'middle') == ['startmiddleend', 'beginmiddlefinish']

def test_case_sensitivity():
    """Test case-sensitive matching"""
    strings = ['Apple', 'apple', 'APPLE']
    assert filter_by_substring(strings, 'App') == ['Apple']
    assert filter_by_substring(strings, 'app') == ['apple']
    assert filter_by_substring(strings, 'APP') == ['APPLE']

def test_special_characters():
    """Test with special characters in strings and substring"""
    strings = ['hello!@#', 'world$%^', 'test&*(']
    assert filter_by_substring(strings, '!@#') == ['hello!@#']
    assert filter_by_substring(strings, '^&') == []

def test_unicode_characters():
    """Test with unicode characters"""
    strings = ['café', 'école', 'français']
    assert filter_by_substring(strings, 'é') == ['café', 'école', 'français']

def test_numbers():
    """Test with numeric strings and substrings"""
    strings = ['123', '456', '7890']
    assert filter_by_substring(strings, '3') == ['123']
    assert filter_by_substring(strings, '90') == ['7890']

def test_whitespace():
    """Test with whitespace characters"""
    strings = ['hello world', 'hello\tworld', 'helloworld']
    assert filter_by_substring(strings, ' ') == ['hello world']
    assert filter_by_substring(strings, '\t') == ['hello\tworld']

def test_long_strings():
    """Test with very long strings"""
    long_string = 'a' * 1000 + 'target' + 'b' * 1000
    strings = [long_string, 'no match', 'target']
    assert filter_by_substring(strings, 'target') == [long_string, 'target']

def test_duplicate_matches():
    """Test with duplicate strings in input"""
    strings = ['abc', 'abc', 'def', 'abc']
    assert filter_by_substring(strings, 'ab') == ['abc', 'abc', 'abc']

def test_overlapping_substring():
    """Test substring appears in overlapping pattern"""
    strings = ['aaaaaa']
    assert filter_by_substring(strings, 'aa') == ['aaaaaa']

def test_none_list():
    """Test with None as list input should raise TypeError"""
    with pytest.raises(TypeError):
        filter_by_substring(None, 'a')

def test_none_substring():
    """Test with None as substring should raise TypeError"""
    with pytest.raises(TypeError):
        filter_by_substring(['abc', 'def'], None)

def test_non_string_elements():
    """Test with list containing non-string elements"""
    with pytest.raises(TypeError):
        filter_by_substring(['abc', 123, 'def'], 'a')

def test_empty_string_element():
    """Test with empty string in list"""
    strings = ['', 'abc', '', 'def']
    assert filter_by_substring(strings, '') == ['', 'abc', '', 'def']
    assert filter_by_substring(strings, 'a') == ['abc']

def test_single_character_substring():
    """Test with single character substring"""
    strings = ['a', 'b', 'c', 'ab', 'bc']
    assert filter_by_substring(strings, 'a') == ['a', 'ab']

def test_substring_longer_than_string():
    """Test where substring is longer than any string"""
    strings = ['short', 'tiny', 'small']
    assert filter_by_substring(strings, 'verylongsubstring') == []

def test_preserve_order():
    """Test that original order is preserved"""
    strings = ['zebra', 'apple', 'banana', 'grape']
    result = filter_by_substring(strings, 'a')
    assert result == ['apple', 'banana', 'grape']
    assert result.index('apple') < result.index('banana') < result.index('grape')

def test_return_new_list():
    """Test that function returns a new list, not modifying original"""
    original = ['abc', 'def', 'ghi']
    result = filter_by_substring(original, 'a')
    assert result is not original
    assert original == ['abc', 'def', 'ghi']