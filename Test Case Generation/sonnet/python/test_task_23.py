import pytest
from solution import strlen


def test_empty_string():
    assert strlen('') == 0


def test_simple_string():
    assert strlen('abc') == 3


def test_single_character():
    assert strlen('a') == 1


def test_whitespace_string():
    assert strlen('   ') == 3


def test_string_with_newlines():
    assert strlen('a\nb\nc') == 5


def test_string_with_tabs():
    assert strlen('a\tb') == 3


def test_numeric_string():
    assert strlen('12345') == 5


def test_special_characters():
    assert strlen('!@#$%^&*()') == 10


def test_unicode_string():
    assert strlen('héllo') == 5


def test_emoji_string():
    assert strlen('😀😁😂') == 3


def test_long_string():
    s = 'a' * 10000
    assert strlen(s) == 10000


def test_mixed_content():
    assert strlen('abc 123 !@#') == 11


def test_null_character():
    assert strlen('\x00') == 1


def test_string_with_only_spaces():
    assert strlen(' ') == 1