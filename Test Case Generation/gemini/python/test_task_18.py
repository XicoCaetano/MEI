import pytest

def how_many_times(string: str, substring: str) -> int:
    """ Find how many times a given substring can be found in the original string. Count overlaping cases. """
    times = 0

    for i in range(len(string) - len(substring) + 1):
        if string[i:i+len(substring)] == substring:
            times += 1

    return times

def test_empty_string():
    assert how_many_times('', 'a') == 0

def test_empty_substring():
    # As per logic: range(len - 0 + 1) -> range(1). string[0:0] == '' is True.
    assert how_many_times('abc', '') == 4
    assert how_many_times('', '') == 1

def test_no_occurrence():
    assert how_many_times('abcde', 'z') == 0
    assert how_many_times('aaaaa', 'b') == 0

def test_single_character_occurrence():
    assert how_many_times('aaa', 'a') == 3

def test_overlapping_substrings():
    assert how_many_times('aaaa', 'aa') == 3
    assert how_many_times('abababa', 'aba') == 3

def test_substring_longer_than_string():
    assert how_many_times('abc', 'abcd') == 0

def test_exact_match():
    assert how_many_times('python', 'python') == 1

def test_case_sensitivity():
    assert how_many_times('AAAA', 'aa') == 0
    assert how_many_times('AaAa', 'a') == 2

def test_special_characters_and_spaces():
    assert how_many_times('a b a b a', 'a b') == 2
    assert how_many_times('!@#!@#', '!#') == 0
    assert how_many_times('!!!', '!!') == 2

@pytest.mark.parametrize("string, substring, expected", [
    ("xyzxyzxyz", "xyz", 3),
    ("11111", "11", 4),
    ("banana", "ana", 2),
    ("hello", "ll", 1),
])
def test_parameterized_cases(string, substring, expected):
    assert how_many_times(string, substring) == expected