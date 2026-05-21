import pytest
from solution import count_distinct_characters


def test_mixed_case_same_chars():
    assert count_distinct_characters('xyzXYZ') == 3


def test_mixed_case_distinct():
    assert count_distinct_characters('Jerry') == 4


def test_empty_string():
    assert count_distinct_characters('') == 0


def test_single_character():
    assert count_distinct_characters('a') == 1


def test_single_character_uppercase():
    assert count_distinct_characters('A') == 1


def test_all_same_lowercase():
    assert count_distinct_characters('aaaa') == 1


def test_all_same_uppercase():
    assert count_distinct_characters('BBBB') == 1


def test_all_same_mixed_case():
    assert count_distinct_characters('aAaA') == 1


def test_all_unique_lowercase():
    assert count_distinct_characters('abcd') == 4


def test_all_unique_uppercase():
    assert count_distinct_characters('ABCD') == 4


def test_numbers():
    assert count_distinct_characters('1234') == 4


def test_repeated_numbers():
    assert count_distinct_characters('1121') == 2


def test_special_characters():
    assert count_distinct_characters('!@#$') == 4


def test_repeated_special_characters():
    assert count_distinct_characters('!!!') == 1


def test_spaces():
    assert count_distinct_characters('a b c') == 4


def test_only_spaces():
    assert count_distinct_characters('   ') == 1


def test_alphanumeric():
    assert count_distinct_characters('aB1') == 3


def test_alphanumeric_with_repeats():
    assert count_distinct_characters('aAbB11') == 3


def test_letters_and_special_chars():
    assert count_distinct_characters('aA!aA!') == 2


def test_long_string_all_same():
    assert count_distinct_characters('z' * 1000) == 1


def test_long_string_all_unique():
    s = 'abcdefghijklmnopqrstuvwxyz'
    assert count_distinct_characters(s) == 26


def test_full_alphabet_uppercase():
    s = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
    assert count_distinct_characters(s) == 26


def test_full_alphabet_mixed():
    s = 'abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ'
    assert count_distinct_characters(s) == 26


def test_newline_character():
    assert count_distinct_characters('a\nb') == 3


def test_tab_character():
    assert count_distinct_characters('a\tb') == 3


def test_unicode_characters():
    assert count_distinct_characters('café') == 4


def test_unicode_case_insensitive():
    assert count_distinct_characters('aAbBcC') == 3


def test_returns_int():
    result = count_distinct_characters('hello')
    assert isinstance(result, int)


def test_case_insensitivity_comprehensive():
    assert count_distinct_characters('HeLLo WoRLd') == count_distinct_characters('hello world')