import pytest
from typing import List, Optional
from longest_function import longest  # Assuming the function is in longest_function.py

def test_empty_list_returns_none():
    """Test that an empty list returns None."""
    assert longest([]) is None


def test_single_element_list():
    """Test a list with a single string."""
    assert longest(["hello"]) == "hello"
    assert longest([""]) == ""


def test_all_strings_same_length():
    """Test when all strings have the same length - should return first."""
    assert longest(["a", "b", "c"]) == "a"
    assert longest(["ab", "cd", "ef"]) == "ab"
    assert longest(["", "", ""]) == ""


def test_unique_longest_string():
    """Test when there is a single unique longest string."""
    assert longest(["a", "bb", "ccc"]) == "ccc"
    assert longest(["short", "mediummm", "longestttt"]) == "longestttt"
    assert longest(["x", "xy", "xyz", "xyzw"]) == "xyzw"


def test_multiple_strings_same_max_length():
    """Test when multiple strings share the maximum length - should return first occurrence."""
    assert longest(["aa", "bb", "cc"]) == "aa"
    assert longest(["hello", "world", "python", "code"]) == "hello"  # hello and world both length 5
    assert longest(["abc", "def", "ghi", "jkl"]) == "abc"


def test_empty_string_in_list():
    """Test lists that contain empty strings."""
    assert longest(["", "a", "bb"]) == "bb"
    assert longest(["", "", "c"]) == "c"
    assert longest(["", ""]) == ""


def test_strings_with_spaces():
    """Test strings that contain spaces."""
    assert longest(["a b", "ab", "abc"]) == "a b"  # length 3
    assert longest(["  ", " ", "   "]) == "  "  # first with length 2


def test_special_characters():
    """Test strings with special characters."""
    assert longest(["!@#", "!@#$%", "!@#"]) == "!@#$%"
    assert longest(["\n", "\t\n", "\n\r\n"]) == "\n\r\n"


def test_unicode_strings():
    """Test strings with unicode characters."""
    assert longest(["café", "cafeteria", "caf"]) == "cafeteria"
    assert longest(["😀", "😀😁", "😀"]) == "😀😁"


def test_large_strings():
    """Test with significantly large strings."""
    long_str1 = "a" * 1000
    long_str2 = "b" * 2000
    long_str3 = "c" * 1500
    
    assert longest([long_str1, long_str2, long_str3]) == long_str2


def test_first_element_is_longest():
    """Test when the first element is already the longest."""
    assert longest(["longest string", "short", "shrt"]) == "longest string"


def test_last_element_is_longest():
    """Test when the last element is the longest."""
    assert longest(["short", "shrt", "longest string"]) == "longest string"


def test_middle_element_is_longest():
    """Test when a middle element is the longest."""
    assert longest(["short", "longest string", "shrt"]) == "longest string"


def test_all_empty_strings():
    """Test when all strings are empty."""
    assert longest(["", "", ""]) == ""


def test_none_values_not_allowed():
    """Test that None values are not passed (based on type hint, though Python allows)."""
    # Based on type hint List[str], but if None were passed, it would cause TypeError
    with pytest.raises(TypeError):
        longest([None, "a", "b"])  # type: ignore


def test_mixed_length_with_duplicates():
    """Test mixed lengths with duplicate strings."""
    assert longest(["same", "same", "differentlength", "same"]) == "differentlength"
    assert longest(["ab", "ab", "abc", "ab"]) == "abc"


def test_single_character_strings():
    """Test with single character strings."""
    assert longest(["x", "y", "z"]) == "x"
    assert longest(["a", "bb", "c"]) == "bb"


def test_numeric_strings():
    """Test strings that contain digits."""
    assert longest(["123", "12345", "12"]) == "12345"
    assert longest(["1", "22", "333", "22"]) == "333"


def test_whitespace_strings():
    """Test strings with different whitespace characters."""
    assert longest(["\t", "    ", "\t\t\t"]) == "    "  # 4 spaces
    assert longest([" \n ", "\n\n", "   "]) == "   "  # 3 spaces