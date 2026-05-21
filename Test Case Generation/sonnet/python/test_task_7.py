import pytest
from typing import List
from solution import filter_by_substring


def test_empty_list():
    assert filter_by_substring([], 'a') == []


def test_basic_filter():
    assert filter_by_substring(['abc', 'bacd', 'cde', 'array'], 'a') == ['abc', 'bacd', 'array']


def test_no_matches():
    assert filter_by_substring(['xyz', 'def', 'ghi'], 'a') == []


def test_all_match():
    assert filter_by_substring(['abc', 'aaa', 'xa'], 'a') == ['abc', 'aaa', 'xa']


def test_single_element_match():
    assert filter_by_substring(['hello'], 'ell') == ['hello']


def test_single_element_no_match():
    assert filter_by_substring(['hello'], 'xyz') == []


def test_substring_full_word():
    assert filter_by_substring(['apple', 'banana', 'cherry'], 'banana') == ['banana']


def test_substring_longer_than_strings():
    assert filter_by_substring(['ab', 'cd'], 'abcd') == []


def test_empty_substring():
    assert filter_by_substring(['abc', 'def', 'ghi'], '') == ['abc', 'def', 'ghi']


def test_empty_substring_empty_list():
    assert filter_by_substring([], '') == []


def test_case_sensitive_no_match():
    assert filter_by_substring(['Hello', 'World'], 'hello') == []


def test_case_sensitive_match():
    assert filter_by_substring(['Hello', 'hello', 'HELLO'], 'Hello') == ['Hello']


def test_substring_with_spaces():
    assert filter_by_substring(['hello world', 'helloworld', 'hello'], 'hello world') == ['hello world']


def test_special_characters():
    assert filter_by_substring(['abc!', 'def@', 'ghi#'], '!') == ['abc!']


def test_numeric_strings():
    assert filter_by_substring(['123', '456', '789'], '45') == ['456']


def test_mixed_types_strings():
    assert filter_by_substring(['abc123', '123abc', 'abc'], '123') == ['abc123', '123abc']


def test_substring_at_start():
    assert filter_by_substring(['prefix_word', 'word', 'another'], 'prefix') == ['prefix_word']


def test_substring_at_end():
    assert filter_by_substring(['word_suffix', 'word', 'another'], 'suffix') == ['word_suffix']


def test_substring_in_middle():
    assert filter_by_substring(['word_mid_dle', 'word', 'another'], 'mid') == ['word_mid_dle']


def test_repeated_substring_in_string():
    assert filter_by_substring(['aaa', 'bbb', 'aba'], 'a') == ['aaa', 'aba']


def test_newline_in_strings():
    assert filter_by_substring(['hello\nworld', 'hello', 'world'], '\n') == ['hello\nworld']


def test_tab_in_strings():
    assert filter_by_substring(['hello\tworld', 'hello', 'world'], '\t') == ['hello\tworld']


def test_unicode_strings():
    assert filter_by_substring(['café', 'coffee', 'caf'], 'é') == ['café']


def test_unicode_substring():
    assert filter_by_substring(['日本語', 'english', '日本'], '日本') == ['日本語', '日本']


def test_returns_list_type():
    result = filter_by_substring(['abc', 'def'], 'a')
    assert isinstance(result, list)


def test_preserves_order():
    input_list = ['zoo', 'apple', 'mango', 'ant', 'banana']
    result = filter_by_substring(input_list, 'an')
    assert result == ['mango', 'ant', 'banana']


def test_does_not_modify_original_list():
    original = ['abc', 'def', 'ghi']
    original_copy = original.copy()
    filter_by_substring(original, 'a')
    assert original == original_copy


def test_string_equal_to_substring():
    assert filter_by_substring(['abc', 'a', 'bc'], 'a') == ['abc', 'a']


def test_multiple_occurrences_same_substring():
    assert filter_by_substring(['xax', 'xbx', 'xax'], 'a') == ['xax', 'xax']