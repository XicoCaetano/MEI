import pytest
from typing import List, Optional


def longest(strings: List[str]) -> Optional[str]:
    if not strings:
        return None
    maxlen = max(len(x) for x in strings)
    for s in strings:
        if len(s) == maxlen:
            return s


def test_empty_list_returns_none():
    assert longest([]) is None


def test_single_element():
    assert longest(['a']) == 'a'


def test_single_empty_string():
    assert longest(['']) == ''


def test_all_same_length_returns_first():
    assert longest(['a', 'b', 'c']) == 'a'


def test_clearly_longest():
    assert longest(['a', 'bb', 'ccc']) == 'ccc'


def test_longest_is_first():
    assert longest(['ccc', 'bb', 'a']) == 'ccc'


def test_longest_is_middle():
    assert longest(['a', 'ccc', 'bb']) == 'ccc'


def test_two_strings_same_length_returns_first():
    assert longest(['ab', 'cd']) == 'ab'


def test_two_strings_different_length():
    assert longest(['abc', 'de']) == 'abc'


def test_list_with_empty_strings_and_longer():
    assert longest(['', 'a', '']) == 'a'


def test_all_empty_strings():
    assert longest(['', '', '']) == ''


def test_unicode_strings():
    assert longest(['café', 'bar', 'foobar']) == 'foobar'


def test_strings_with_spaces():
    assert longest(['hello world', 'hi', 'hey']) == 'hello world'


def test_single_character_strings():
    assert longest(['x']) == 'x'


def test_mixed_lengths():
    assert longest(['short', 'medium!!', 'x']) == 'medium!!'


def test_large_list():
    strings = ['a' * i for i in range(1, 101)]
    assert longest(strings) == 'a' * 100


def test_tie_returns_first_occurrence():
    assert longest(['bb', 'cc', 'dd']) == 'bb'


def test_numeric_string_characters():
    assert longest(['123', '45', '6789']) == '6789'


def test_newline_and_special_characters():
    assert longest(['\n\n\n', 'ab']) == '\n\n\n'