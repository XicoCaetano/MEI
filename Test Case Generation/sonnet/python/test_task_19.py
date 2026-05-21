import pytest
from solution import sort_numbers


def test_docstring_example():
    assert sort_numbers('three one five') == 'one three five'

def test_already_sorted():
    assert sort_numbers('zero one two three') == 'zero one two three'

def test_reverse_order():
    assert sort_numbers('nine eight seven six five four three two one zero') == 'zero one two three four five six seven eight nine'

def test_single_number_zero():
    assert sort_numbers('zero') == 'zero'

def test_single_number_nine():
    assert sort_numbers('nine') == 'nine'

def test_all_ten_numbers_unsorted():
    assert sort_numbers('five three nine zero two eight one seven four six') == 'zero one two three four five six seven eight nine'

def test_two_numbers_sorted():
    assert sort_numbers('one two') == 'one two'

def test_two_numbers_unsorted():
    assert sort_numbers('two one') == 'one two'

def test_duplicate_numbers():
    assert sort_numbers('three three three') == 'three three three'

def test_duplicates_mixed():
    assert sort_numbers('five one five two one') == 'one one two five five'

def test_all_same_number():
    assert sort_numbers('seven seven seven seven') == 'seven seven seven seven'

def test_empty_string():
    assert sort_numbers('') == ''

def test_returns_string_type():
    result = sort_numbers('one two three')
    assert isinstance(result, str)

def test_all_numbers_individually():
    words = ['zero', 'one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']
    for word in words:
        assert sort_numbers(word) == word

def test_zero_and_nine_only():
    assert sort_numbers('nine zero') == 'zero nine'

def test_four_five_six():
    assert sort_numbers('six four five') == 'four five six'

def test_multiple_duplicates_different_values():
    assert sort_numbers('two nine two nine') == 'two two nine nine'

def test_large_duplicate_set():
    assert sort_numbers('one one one one one') == 'one one one one one'

def test_sort_stability_preserves_order_for_equals():
    result = sort_numbers('three three')
    assert result == 'three three'

def test_eight_comes_before_nine():
    assert sort_numbers('nine eight') == 'eight nine'

def test_zero_smallest():
    assert sort_numbers('one zero') == 'zero one'

def test_nine_largest():
    assert sort_numbers('nine one') == 'one nine'