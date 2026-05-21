import pytest
from typing import List, Any
from solution import filter_integers


def test_basic_mixed_list():
    assert filter_integers(['a', 3.14, 5]) == [5]


def test_multiple_integers_with_other_types():
    assert filter_integers([1, 2, 3, 'abc', {}, []]) == [1, 2, 3]


def test_empty_list():
    assert filter_integers([]) == []


def test_all_integers():
    assert filter_integers([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]


def test_no_integers():
    assert filter_integers(['a', 'b', 3.14, None, {}, [], ()]) == []


def test_negative_integers():
    assert filter_integers([-1, -2, 3, 'x']) == [-1, -2, 3]


def test_zero_is_integer():
    assert filter_integers([0, 'a', 1.5]) == [0]


def test_booleans_are_excluded():
    # In Python, bool is a subclass of int, so isinstance(True, int) is True
    assert filter_integers([True, False, 1, 2]) == [True, False, 1, 2]


def test_floats_excluded():
    assert filter_integers([1.0, 2.5, 3.9]) == []


def test_none_excluded():
    assert filter_integers([None, 1, 2]) == [1, 2]


def test_strings_excluded():
    assert filter_integers(['1', '2', '3']) == []


def test_dicts_excluded():
    assert filter_integers([{'a': 1}, {}, 5]) == [5]


def test_lists_excluded():
    assert filter_integers([[1, 2], [], 7]) == [7]


def test_tuples_excluded():
    assert filter_integers([(1, 2), (), 9]) == [9]


def test_complex_numbers_excluded():
    assert filter_integers([1+2j, 3, 4.0]) == [3]


def test_large_integers():
    assert filter_integers([10**18, 10**19, 'x']) == [10**18, 10**19]


def test_single_integer():
    assert filter_integers([42]) == [42]


def test_single_non_integer():
    assert filter_integers(['hello']) == []


def test_preserves_order():
    assert filter_integers([3, 'a', 1, None, 2]) == [3, 1, 2]


def test_return_type_is_list():
    result = filter_integers([1, 2, 3])
    assert isinstance(result, list)


def test_mixed_with_bytes():
    assert filter_integers([b'bytes', 10, 20]) == [10, 20]


def test_set_excluded():
    assert filter_integers([{1, 2}, 3]) == [3]