import pytest
from typing import List
from solution import intersperse


def test_empty_list():
    assert intersperse([], 4) == []


def test_basic_example():
    assert intersperse([1, 2, 3], 4) == [1, 4, 2, 4, 3]


def test_single_element():
    assert intersperse([5], 9) == [5]


def test_two_elements():
    assert intersperse([1, 2], 0) == [1, 0, 2]


def test_delimiter_zero():
    assert intersperse([1, 2, 3], 0) == [1, 0, 2, 0, 3]


def test_delimiter_negative():
    assert intersperse([1, 2, 3], -1) == [1, -1, 2, -1, 3]


def test_negative_numbers():
    assert intersperse([-1, -2, -3], 0) == [-1, 0, -2, 0, -3]


def test_all_zeros():
    assert intersperse([0, 0, 0], 0) == [0, 0, 0, 0, 0]


def test_large_list():
    numbers = list(range(10))
    result = intersperse(numbers, 99)
    expected = []
    for i, n in enumerate(numbers):
        expected.append(n)
        if i < len(numbers) - 1:
            expected.append(99)
    assert result == expected


def test_delimiter_same_as_elements():
    assert intersperse([7, 7, 7], 7) == [7, 7, 7, 7, 7]


def test_return_type_is_list():
    result = intersperse([1, 2, 3], 0)
    assert isinstance(result, list)


def test_return_type_empty():
    result = intersperse([], 5)
    assert isinstance(result, list)


def test_original_list_not_modified():
    numbers = [1, 2, 3]
    original = numbers.copy()
    intersperse(numbers, 99)
    assert numbers == original


def test_result_length_multiple_elements():
    numbers = [1, 2, 3, 4, 5]
    result = intersperse(numbers, 0)
    assert len(result) == 2 * len(numbers) - 1


def test_result_length_single_element():
    result = intersperse([42], 0)
    assert len(result) == 1


def test_result_length_two_elements():
    result = intersperse([1, 2], 0)
    assert len(result) == 3


def test_delimiter_large_value():
    assert intersperse([1, 2, 3], 10**9) == [1, 10**9, 2, 10**9, 3]


def test_delimiter_appears_between_every_pair():
    delimiter = 55
    numbers = [1, 2, 3, 4]
    result = intersperse(numbers, delimiter)
    for i in range(1, len(result) - 1, 2):
        assert result[i] == delimiter


def test_original_elements_preserved_in_order():
    numbers = [10, 20, 30, 40]
    result = intersperse(numbers, 0)
    extracted = [result[i] for i in range(0, len(result), 2)]
    assert extracted == numbers


def test_two_element_list_structure():
    result = intersperse([3, 7], 5)
    assert result[0] == 3
    assert result[1] == 5
    assert result[2] == 7