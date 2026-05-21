import pytest
from typing import List
from solution import concatenate


def test_empty_list():
    assert concatenate([]) == ''


def test_single_string():
    assert concatenate(['a']) == 'a'


def test_multiple_strings():
    assert concatenate(['a', 'b', 'c']) == 'abc'


def test_strings_with_spaces():
    assert concatenate(['hello', ' ', 'world']) == 'hello world'


def test_strings_with_numbers():
    assert concatenate(['1', '2', '3']) == '123'


def test_strings_with_special_characters():
    assert concatenate(['!', '@', '#']) == '!@#'


def test_long_strings():
    assert concatenate(['foo', 'bar', 'baz']) == 'foobarbaz'


def test_strings_with_newlines():
    assert concatenate(['line1', '\n', 'line2']) == 'line1\nline2'


def test_strings_with_unicode():
    assert concatenate(['héllo', ' ', 'wörld']) == 'héllo wörld'


def test_single_empty_string():
    assert concatenate(['']) == ''


def test_multiple_empty_strings():
    assert concatenate(['', '', '']) == ''


def test_mixed_empty_and_non_empty():
    assert concatenate(['a', '', 'b']) == 'ab'


def test_return_type_is_str():
    result = concatenate(['a', 'b'])
    assert isinstance(result, str)


def test_return_type_empty_list():
    result = concatenate([])
    assert isinstance(result, str)


def test_whitespace_strings():
    assert concatenate(['   ', '\t', '\n']) == '   \t\n'


def test_large_list():
    strings = ['a'] * 1000
    assert concatenate(strings) == 'a' * 1000