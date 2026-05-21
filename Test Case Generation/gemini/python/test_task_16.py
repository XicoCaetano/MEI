import pytest

def count_distinct_characters(string: str) -> int:
    """ Given a string, find out how many distinct characters (regardless of case) does it consist of
    >>> count_distinct_characters('xyzXYZ')
    3
    >>> count_distinct_characters('Jerry')
    4
    """
    return len(set(string.lower()))

def test_count_distinct_characters_basic():
    """Tests standard strings with mixed casing."""
    assert count_distinct_characters('xyzXYZ') == 3
    assert count_distinct_characters('Jerry') == 4
    assert count_distinct_characters('abc') == 3

def test_count_distinct_characters_empty_string():
    """Tests the edge case of an empty string."""
    assert count_distinct_characters('') == 0

def test_count_distinct_characters_single_character():
    """Tests strings with only one character (repeated or single)."""
    assert count_distinct_characters('a') == 1
    assert count_distinct_characters('aaaaa') == 1
    assert count_distinct_characters('AaAaA') == 1

def test_count_distinct_characters_special_chars_and_numbers():
    """Tests numbers and special characters which do not have 'casing'."""
    assert count_distinct_characters('123123') == 3
    assert count_distinct_characters('!@#!@#') == 3
    assert count_distinct_characters('123abcABC!!!') == 7

def test_count_distinct_characters_whitespace():
    """Tests handling of spaces and different types of whitespace."""
    assert count_distinct_characters('   ') == 1
    assert count_distinct_characters('a b c') == 4  # a, b, c, and space
    assert count_distinct_characters('a\nb\t') == 4 # a, b, newline, tab

def test_count_distinct_characters_unicode():
    """Tests non-ASCII characters."""
    assert count_distinct_characters('çÇ') == 1
    assert count_distinct_characters('éÉèÈ') == 2

@pytest.mark.parametrize("input_str, expected", [
    ("apple", 4),
    ("Mississippi", 4),
    ("12345", 5),
    ("", 0),
    ("AaBbCc", 3),
])
def test_count_distinct_characters_parametrized(input_str, expected):
    """Data-driven tests for various scenarios."""
    assert count_distinct_characters(input_str) == expected