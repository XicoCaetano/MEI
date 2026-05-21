import pytest
from collections import Counter
from typing import List


def remove_duplicates(numbers: List[int]) -> List[int]:
    import collections
    c = collections.Counter(numbers)
    return [n for n in numbers if c[n] <= 1]


def test_example_from_docstring():
    assert remove_duplicates([1, 2, 3, 2, 4]) == [1, 3, 4]

def test_empty_list():
    assert remove_duplicates([]) == []

def test_single_element():
    assert remove_duplicates([42]) == [42]

def test_all_unique():
    assert remove_duplicates([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

def test_all_duplicates():
    assert remove_duplicates([1, 1, 2, 2, 3, 3]) == []

def test_all_same_element():
    assert remove_duplicates([7, 7, 7, 7]) == []

def test_preserves_order():
    assert remove_duplicates([5, 3, 1, 3, 2, 5, 4]) == [1, 2, 4]

def test_duplicate_at_start():
    assert remove_duplicates([1, 1, 2, 3, 4]) == [2, 3, 4]

def test_duplicate_at_end():
    assert remove_duplicates([1, 2, 3, 4, 4]) == [1, 2, 3]

def test_duplicate_appears_three_times():
    assert remove_duplicates([1, 2, 1, 2, 1]) == []

def test_negative_numbers():
    assert remove_duplicates([-1, -2, -3, -2, -4]) == [-1, -3, -4]

def test_mixed_positive_and_negative():
    assert remove_duplicates([-1, 1, -1, 2, 1]) == [2]

def test_zeros():
    assert remove_duplicates([0, 0, 1, 2]) == [1, 2]

def test_single_zero():
    assert remove_duplicates([0]) == [0]

def test_large_numbers():
    assert remove_duplicates([10**9, 10**9, 10**6]) == [10**6]

def test_returns_list():
    result = remove_duplicates([1, 2, 3])
    assert isinstance(result, list)

def test_two_elements_both_unique():
    assert remove_duplicates([1, 2]) == [1, 2]

def test_two_elements_both_duplicate():
    assert remove_duplicates([1, 1]) == []

def test_many_duplicates_one_unique():
    assert remove_duplicates([3, 3, 3, 3, 7, 3]) == [7]

def test_one_unique_at_start():
    assert remove_duplicates([9, 1, 1, 2, 2]) == [9]

def test_interleaved_duplicates():
    assert remove_duplicates([1, 2, 1, 2, 3]) == [3]

def test_does_not_mutate_input():
    original = [1, 2, 3, 2, 4]
    copy = original[:]
    remove_duplicates(original)
    assert original == copy

def test_large_list_performance():
    numbers = list(range(1000)) + list(range(500))
    result = remove_duplicates(numbers)
    assert result == list(range(500, 1000))

def test_all_same_negative():
    assert remove_duplicates([-5, -5, -5]) == []

def test_mixed_with_zero_duplicate():
    assert remove_duplicates([0, 1, 0, 2]) == [1, 2]