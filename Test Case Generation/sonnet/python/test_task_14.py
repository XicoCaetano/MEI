import pytest
from typing import List


def all_prefixes(string: str) -> List[str]:
    result = []
    for i in range(len(string)):
        result.append(string[:i+1])
    return result


def test_basic_string():
    assert all_prefixes('abc') == ['a', 'ab', 'abc']

def test_empty_string():
    assert all_prefixes('') == []

def test_single_character():
    assert all_prefixes('a') == ['a']

def test_two_characters():
    assert all_prefixes('ab') == ['a', 'ab']

def test_returns_list():
    assert isinstance(all_prefixes('abc'), list)

def test_length_matches_input():
    s = 'hello'
    result = all_prefixes(s)
    assert len(result) == len(s)

def test_last_element_is_full_string():
    s = 'python'
    result = all_prefixes(s)
    assert result[-1] == s

def test_first_element_is_first_char():
    s = 'world'
    result = all_prefixes(s)
    assert result[0] == 'w'

def test_prefixes_increasing_length():
    result = all_prefixes('abcd')
    for i, prefix in enumerate(result):
        assert len(prefix) == i + 1

def test_with_spaces():
    assert all_prefixes('a b') == ['a', 'a ', 'a b']

def test_with_numbers():
    assert all_prefixes('123') == ['1', '12', '123']

def test_with_special_characters():
    assert all_prefixes('!@#') == ['!', '!@', '!@#']

def test_with_unicode():
    assert all_prefixes('áéí') == ['á', 'áé', 'áéí']

def test_with_repeated_characters():
    assert all_prefixes('aaa') == ['a', 'aa', 'aaa']

def test_each_prefix_is_substring_of_next():
    result = all_prefixes('hello')
    for i in range(len(result) - 1):
        assert result[i+1].startswith(result[i])

def test_long_string():
    s = 'a' * 100
    result = all_prefixes(s)
    assert len(result) == 100
    assert result[0] == 'a'
    assert result[-1] == s

def test_no_mutation_of_input():
    s = 'test'
    original = s
    all_prefixes(s)
    assert s == original