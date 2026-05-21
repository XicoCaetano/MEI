import pytest
from solution import is_palindrome, make_palindrome


# Tests for is_palindrome
def test_is_palindrome_empty_string():
    assert is_palindrome('') is True

def test_is_palindrome_single_char():
    assert is_palindrome('a') is True

def test_is_palindrome_two_same_chars():
    assert is_palindrome('aa') is True

def test_is_palindrome_two_diff_chars():
    assert is_palindrome('ab') is False

def test_is_palindrome_odd_length_true():
    assert is_palindrome('racecar') is True

def test_is_palindrome_even_length_true():
    assert is_palindrome('abba') is True

def test_is_palindrome_odd_length_false():
    assert is_palindrome('hello') is False

def test_is_palindrome_even_length_false():
    assert is_palindrome('abcd') is False

def test_is_palindrome_numeric_string_true():
    assert is_palindrome('12321') is True

def test_is_palindrome_numeric_string_false():
    assert is_palindrome('12345') is False

def test_is_palindrome_mixed_case_not_palindrome():
    assert is_palindrome('Aba') is False

def test_is_palindrome_spaces():
    assert is_palindrome('a a') is True

def test_is_palindrome_all_same_chars():
    assert is_palindrome('aaaa') is True


# Tests for make_palindrome
def test_make_palindrome_empty_string():
    assert make_palindrome('') == ''

def test_make_palindrome_single_char():
    assert make_palindrome('a') == 'a'

def test_make_palindrome_already_palindrome_odd():
    assert make_palindrome('racecar') == 'racecar'

def test_make_palindrome_already_palindrome_even():
    assert make_palindrome('abba') == 'abba'

def test_make_palindrome_cat():
    assert make_palindrome('cat') == 'catac'

def test_make_palindrome_cata():
    assert make_palindrome('cata') == 'catac'

def test_make_palindrome_single_char_non_palindrome_prefix():
    assert make_palindrome('ab') == 'aba'

def test_make_palindrome_result_is_palindrome():
    for s in ['cat', 'cata', 'hello', 'xyz', 'ab', 'abcd', 'race']:
        result = make_palindrome(s)
        assert is_palindrome(result), f"make_palindrome('{s}') = '{result}' is not a palindrome"

def test_make_palindrome_result_starts_with_input():
    for s in ['cat', 'cata', 'hello', 'xyz', 'ab']:
        result = make_palindrome(s)
        assert result.startswith(s), f"make_palindrome('{s}') = '{result}' does not start with '{s}'"

def test_make_palindrome_all_same_chars():
    assert make_palindrome('aaa') == 'aaa'

def test_make_palindrome_two_chars_same():
    assert make_palindrome('aa') == 'aa'

def test_make_palindrome_two_chars_diff():
    assert make_palindrome('ab') == 'aba'

def test_make_palindrome_palindrome_suffix_exists():
    # 'aab' -> suffix 'b' is palindrome, prepend reverse of 'aa' -> 'aab' + 'aa' = 'aabaa'
    result = make_palindrome('aab')
    assert is_palindrome(result)
    assert result.startswith('aab')

def test_make_palindrome_numeric_string():
    result = make_palindrome('123')
    assert is_palindrome(result)
    assert result.startswith('123')

def test_make_palindrome_shortest():
    # Result should be the shortest palindrome beginning with the string
    result = make_palindrome('cat')
    assert result == 'catac'
    assert len(result) == 5

def test_make_palindrome_race():
    result = make_palindrome('race')
    assert is_palindrome(result)
    assert result.startswith('race')