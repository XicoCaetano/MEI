import pytest
from solution import how_many_times


def test_empty_string_returns_zero():
    assert how_many_times('', 'a') == 0


def test_single_char_substring_no_overlap():
    assert how_many_times('aaa', 'a') == 3


def test_overlapping_substring():
    assert how_many_times('aaaa', 'aa') == 3


def test_empty_substring_returns_zero():
    assert how_many_times('abc', '') == 0


def test_both_empty():
    assert how_many_times('', '') == 0


def test_substring_longer_than_string():
    assert how_many_times('ab', 'abc') == 0


def test_substring_equals_string():
    assert how_many_times('abc', 'abc') == 1


def test_no_match():
    assert how_many_times('abcdef', 'xyz') == 0


def test_single_match_in_middle():
    assert how_many_times('abcdef', 'cd') == 1


def test_multiple_non_overlapping():
    assert how_many_times('abababab', 'ab') == 4


def test_overlapping_three_chars():
    assert how_many_times('aaa', 'aa') == 2


def test_full_overlap():
    assert how_many_times('aaaaa', 'aaa') == 3


def test_substring_at_start():
    assert how_many_times('abcxyz', 'abc') == 1


def test_substring_at_end():
    assert how_many_times('xyzabc', 'abc') == 1


def test_single_char_string_match():
    assert how_many_times('a', 'a') == 1


def test_single_char_string_no_match():
    assert how_many_times('a', 'b') == 0


def test_repeated_pattern():
    assert how_many_times('ababab', 'aba') == 2


def test_special_characters():
    assert how_many_times('a!a!a', '!') == 2


def test_spaces():
    assert how_many_times('a b a b', 'a b') == 2


def test_numeric_string():
    assert how_many_times('12312312', '123') == 2


def test_newline_characters():
    assert how_many_times('a\na\na', 'a\n') == 2


def test_returns_int():
    result = how_many_times('abc', 'a')
    assert isinstance(result, int)