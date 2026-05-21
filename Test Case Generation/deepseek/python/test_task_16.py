import pytest
from your_module import count_distinct_characters

def test_empty_string():
    """Test empty string should return 0"""
    assert count_distinct_characters("") == 0

def test_single_character():
    """Test string with single character"""
    assert count_distinct_characters("a") == 1
    assert count_distinct_characters("Z") == 1

def test_all_same_character_case_insensitive():
    """Test all characters are the same regardless of case"""
    assert count_distinct_characters("aaaa") == 1
    assert count_distinct_characters("AaAa") == 1
    assert count_distinct_characters("ZZZZZZ") == 1

def test_mixed_case_unique_characters():
    """Test characters that are unique but in different cases"""
    assert count_distinct_characters("xyzXYZ") == 3
    assert count_distinct_characters("aAbBcC") == 3
    assert count_distinct_characters("HelloHELLO") == 4

def test_all_distinct_characters():
    """Test all characters are distinct"""
    assert count_distinct_characters("abc") == 3
    assert count_distinct_characters("ABCD") == 4
    assert count_distinct_characters("xyz123") == 6

def test_whitespace_characters():
    """Test whitespace characters are treated as distinct"""
    assert count_distinct_characters(" ") == 1
    assert count_distinct_characters("a b") == 3  # 'a', ' ', 'b'
    assert count_distinct_characters("\t\n\r") == 3

def test_special_characters():
    """Test special characters and punctuation"""
    assert count_distinct_characters("!@#$%") == 5
    assert count_distinct_characters("a!a@a") == 3  # 'a', '!', '@'
    assert count_distinct_characters(".,;:") == 4

def test_numeric_characters():
    """Test numeric characters"""
    assert count_distinct_characters("12345") == 5
    assert count_distinct_characters("112233") == 3
    assert count_distinct_characters("0") == 1

def test_mixed_all_character_types():
    """Test combination of letters, numbers, and special characters"""
    assert count_distinct_characters("aA1!bB2@") == 7  # a, 1, !, b, 2, @

def test_long_string():
    """Test longer strings to ensure no performance issues"""
    long_string = "abcdefghijklmnopqrstuvwxyz" * 100
    assert count_distinct_characters(long_string) == 26

def test_unicode_characters():
    """Test Unicode characters (beyond ASCII)"""
    assert count_distinct_characters("café") == 4
    assert count_distinct_characters("αβγδ") == 4
    assert count_distinct_characters("ααα") == 1

def test_case_insensitive_unicode():
    """Test case insensitivity with Unicode characters"""
    assert count_distinct_characters("SSß") == 2  # 's' and 'ß' (German sharp s)
    assert count_distinct_characters("áÁ") == 1

def test_string_with_only_spaces_and_tabs():
    """Test strings consisting only of different whitespace characters"""
    assert count_distinct_characters("  ") == 1  # just space
    assert count_distinct_characters("\t\t") == 1  # just tab
    assert count_distinct_characters(" \t\n") == 3  # space, tab, newline

def test_very_long_distinct_string():
    """Test maximum possible distinct characters in a string"""
    alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    assert count_distinct_characters(alphabet) == 52

def test_string_with_repeating_patterns():
    """Test strings with repeating patterns after case normalization"""
    assert count_distinct_characters("abcABC") == 3
    assert count_distinct_characters("HelloWorld" * 10) == 7  # H,e,l,o,W,r,d