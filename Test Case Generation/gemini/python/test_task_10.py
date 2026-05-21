import pytest

def is_palindrome(string: str) -> bool:
    """ Test if given string is a palindrome """
    return string == string[::-1]


def make_palindrome(string: str) -> str:
    """ Find the shortest palindrome that begins with a supplied string. """
    if not string:
        return ''

    beginning_of_suffix = 0

    while not is_palindrome(string[beginning_of_suffix:]):
        beginning_of_suffix += 1

    return string + string[:beginning_of_suffix][::-1]


# --- Unit Tests ---

def test_is_palindrome_empty_string():
    assert is_palindrome("") is True

def test_is_palindrome_single_char():
    assert is_palindrome("a") is True

def test_is_palindrome_valid():
    assert is_palindrome("racecar") is True
    assert is_palindrome("aba") is True

def test_is_palindrome_invalid():
    assert is_palindrome("abc") is False
    assert is_palindrome("hello") is False

def test_is_palindrome_case_sensitive():
    # Standard behavior: 'A' != 'a'
    assert is_palindrome("Abba") is False

def test_make_palindrome_empty_string():
    assert make_palindrome("") == ""

def test_make_palindrome_already_palindrome():
    assert make_palindrome("racecar") == "racecar"
    assert make_palindrome("a") == "a"
    assert make_palindrome("aa") == "aa"

def test_make_palindrome_basic():
    assert make_palindrome("cat") == "catac"
    assert make_palindrome("cata") == "catac"

def test_make_palindrome_single_char_prefix():
    # Longest suffix palindrome is 'cc', prefix is 'a'
    assert make_palindrome("acc") == "acca"

def test_make_palindrome_no_suffix_palindrome():
    # Longest suffix palindrome is 'd', prefix 'abc'
    assert make_palindrome("abcd") == "abcdcba"

def test_make_palindrome_long_string():
    assert make_palindrome("xyz") == "xyzya" or "xyz" + "yx"
    assert make_palindrome("xyz") == "xyzyx"

def test_make_palindrome_with_spaces():
    assert make_palindrome("race car") == "race car acecar"

def test_make_palindrome_numeric_strings():
    assert make_palindrome("123") == "12321"