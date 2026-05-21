import pytest
from typing import List
from solution import filter_by_prefix


def test_empty_list():
    assert filter_by_prefix([], 'a') == []


def test_basic_prefix_filter():
    assert filter_by_prefix(['abc', 'bcd', 'cde', 'array'], 'a') == ['abc', 'array']


def test_no_matches():
    assert filter_by_prefix(['abc', 'bcd', 'cde'], 'z') == []


def test_all_match():
    assert filter_by_prefix(['apple', 'apricot', 'avocado'], 'a') == ['apple', 'apricot', 'avocado']


def test_empty_prefix():
    assert filter_by_prefix(['abc', 'bcd', 'cde'], '') == ['abc', 'bcd', 'cde']


def test_empty_prefix_empty_list():
    assert filter_by_prefix([], '') == []


def test_prefix_longer_than_strings():
    assert filter_by_prefix(['ab', 'a', 'abc'], 'abcd') == []


def test_exact_match_prefix():
    assert filter_by_prefix(['abc', 'ab', 'a'], 'abc') == ['abc']


def test_single_character_prefix():
    assert filter_by_prefix(['apple', 'banana', 'avocado', 'cherry'], 'a') == ['apple', 'avocado']


def test_multicharacter_prefix():
    assert filter_by_prefix(['foobar', 'foo', 'foobaz', 'bar'], 'foo') == ['foobar', 'foo', 'foobaz']


def test_case_sensitive_prefix():
    assert filter_by_prefix(['Apple', 'apple', 'APPLE'], 'apple') == ['apple']


def test_case_sensitive_uppercase_prefix():
    assert filter_by_prefix(['Apple', 'apple', 'APPLE'], 'A') == ['Apple']


def test_numeric_strings():
    assert filter_by_prefix(['123', '456', '12', '1'], '12') == ['123', '12']


def test_special_characters_prefix():
    assert filter_by_prefix(['@home', '@work', 'home', 'work'], '@') == ['@home', '@work']


def test_whitespace_prefix():
    assert filter_by_prefix([' hello', 'hello', ' world'], ' ') == [' hello', ' world']


def test_string_equal_to_prefix():
    assert filter_by_prefix(['abc', 'ab', 'a'], 'ab') == ['abc', 'ab']


def test_single_element_list_match():
    assert filter_by_prefix(['abc'], 'a') == ['abc']


def test_single_element_list_no_match():
    assert filter_by_prefix(['abc'], 'z') == []


def test_preserves_order():
    result = filter_by_prefix(['ant', 'bear', 'ape', 'cat', 'arrow'], 'a')
    assert result == ['ant', 'ape', 'arrow']


def test_unicode_strings():
    assert filter_by_prefix(['café', 'car', 'casa', 'bar'], 'ca') == ['café', 'car', 'casa']


def test_strings_with_newlines():
    assert filter_by_prefix(['foo\nbar', 'foobar', 'bar'], 'foo') == ['foo\nbar', 'foobar']


def test_prefix_is_full_string():
    assert filter_by_prefix(['hello', 'hello world', 'hell'], 'hello') == ['hello', 'hello world']


def test_list_with_empty_strings():
    assert filter_by_prefix(['', 'abc', ''], '') == ['', 'abc', '']


def test_empty_string_in_list_non_empty_prefix():
    assert filter_by_prefix(['', 'abc', 'ade'], 'a') == ['abc', 'ade']


def test_returns_list_type():
    result = filter_by_prefix(['abc', 'bcd'], 'a')
    assert isinstance(result, list)


def test_does_not_modify_original_list():
    original = ['abc', 'bcd', 'cde']
    filter_by_prefix(original, 'a')
    assert original == ['abc', 'bcd', 'cde']