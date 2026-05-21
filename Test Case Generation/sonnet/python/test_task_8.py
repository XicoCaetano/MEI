import pytest
from typing import List, Tuple
from solution import sum_product


def test_empty_list():
    assert sum_product([]) == (0, 1)

def test_single_element():
    assert sum_product([5]) == (5, 5)

def test_single_zero():
    assert sum_product([0]) == (0, 0)

def test_single_one():
    assert sum_product([1]) == (1, 1)

def test_multiple_elements():
    assert sum_product([1, 2, 3, 4]) == (10, 24)

def test_two_elements():
    assert sum_product([3, 7]) == (10, 21)

def test_all_zeros():
    assert sum_product([0, 0, 0]) == (0, 0)

def test_all_ones():
    assert sum_product([1, 1, 1, 1]) == (4, 1)

def test_negative_numbers():
    assert sum_product([-1, -2, -3]) == (-6, -6)

def test_mixed_positive_negative():
    assert sum_product([-1, 2, -3, 4]) == (2, 24)

def test_even_negatives_product_positive():
    assert sum_product([-2, -3]) == (-5, 6)

def test_odd_negatives_product_negative():
    assert sum_product([-2, -3, -4]) == (-9, -24)

def test_large_numbers():
    assert sum_product([1000, 2000, 3000]) == (6000, 6_000_000_000)

def test_contains_zero_product_is_zero():
    assert sum_product([1, 2, 0, 4]) == (7, 0)

def test_single_negative():
    assert sum_product([-7]) == (-7, -7)

def test_returns_tuple():
    result = sum_product([1, 2, 3])
    assert isinstance(result, tuple)
    assert len(result) == 2

def test_sum_type_is_int():
    s, p = sum_product([1, 2, 3])
    assert isinstance(s, int)

def test_product_type_is_int():
    s, p = sum_product([1, 2, 3])
    assert isinstance(p, int)

def test_empty_sum_is_zero():
    s, _ = sum_product([])
    assert s == 0

def test_empty_product_is_one():
    _, p = sum_product([])
    assert p == 1

def test_large_list():
    numbers = list(range(1, 11))
    assert sum_product(numbers) == (55, 3628800)

def test_repeated_elements():
    assert sum_product([3, 3, 3]) == (9, 27)

def test_two_negatives_and_zero():
    assert sum_product([-2, -3, 0]) == (-5, 0)