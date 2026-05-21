import pytest
from solution import flip_case


def test_mixed_case():
    assert flip_case('Hello') == 'hELLO'

def test_all_lowercase():
    assert flip_case('hello') == 'HELLO'

def test_all_uppercase():
    assert flip_case('HELLO') == 'hello'

def test_empty_string():
    assert flip_case('') == ''

def test_numbers_unchanged():
    assert flip_case('abc123') == 'ABC123'

def test_special_chars_unchanged():
    assert flip_case('!@#$%') == '!@#$%'

def test_mixed_with_numbers_and_special():
    assert flip_case('Hello World! 123') == 'hELLO wORLD! 123'

def test_single_lowercase():
    assert flip_case('a') == 'A'

def test_single_uppercase():
    assert flip_case('A') == 'a'

def test_spaces_unchanged():
    assert flip_case('   ') == '   '

def test_newline_unchanged():
    assert flip_case('Hello\nWorld') == 'hELLO\nwORLD'

def test_tab_unchanged():
    assert flip_case('Hello\tWorld') == 'hELLO\tWORLD'

def test_unicode_letters():
    assert flip_case('café') == 'CAFÉ'

def test_already_swapped():
    assert flip_case('hELLO') == 'Hello'

def test_numbers_only():
    assert flip_case('1234567890') == '1234567890'