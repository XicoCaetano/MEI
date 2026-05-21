import pytest
from typing import List, Tuple
from solution import find_closest_elements


def test_basic_example_from_docstring():
    result = find_closest_elements([1.0, 2.0, 3.0, 4.0, 5.0, 2.2])
    assert result == (2.0, 2.2)


def test_duplicate_values_from_docstring():
    result = find_closest_elements([1.0, 2.0, 3.0, 4.0, 5.0, 2.0])
    assert result == (2.0, 2.0)


def test_two_elements_minimum():
    result = find_closest_elements([1.0, 3.0])
    assert result == (1.0, 3.0)


def test_two_elements_returns_smaller_first():
    result = find_closest_elements([5.0, 2.0])
    assert result == (2.0, 5.0)


def test_two_identical_elements():
    result = find_closest_elements([7.0, 7.0])
    assert result == (7.0, 7.0)


def test_negative_numbers():
    result = find_closest_elements([-5.0, -3.0, -1.0, 0.0])
    assert result == (-1.0, 0.0)


def test_mixed_negative_and_positive():
    result = find_closest_elements([-1.0, 0.0, 1.0, 2.0])
    assert result == (-1.0, 0.0)


def test_closest_pair_at_beginning():
    result = find_closest_elements([1.0, 1.1, 5.0, 10.0, 20.0])
    assert result == (1.0, 1.1)


def test_closest_pair_at_end():
    result = find_closest_elements([1.0, 5.0, 10.0, 20.0, 20.1])
    assert result == (20.0, 20.1)


def test_closest_pair_in_middle():
    result = find_closest_elements([1.0, 10.0, 10.05, 20.0, 50.0])
    assert result == (10.0, 10.05)


def test_all_identical_elements():
    result = find_closest_elements([3.0, 3.0, 3.0, 3.0])
    assert result == (3.0, 3.0)


def test_large_distances():
    result = find_closest_elements([0.0, 1000.0, 999.0, 500.0])
    assert result == (999.0, 1000.0)


def test_very_small_difference():
    result = find_closest_elements([1.0, 2.0, 3.0, 3.0000001])
    assert result == (3.0, 3.0000001)


def test_integers_as_floats():
    result = find_closest_elements([1.0, 2.0, 3.0, 4.0])
    assert result == (1.0, 2.0)


def test_result_is_tuple():
    result = find_closest_elements([1.0, 2.0, 3.0])
    assert isinstance(result, tuple)


def test_result_has_two_elements():
    result = find_closest_elements([1.0, 2.0, 3.0])
    assert len(result) == 2


def test_smaller_number_first():
    result = find_closest_elements([10.0, 1.0, 5.0, 4.9])
    assert result[0] <= result[1]


def test_three_elements():
    result = find_closest_elements([1.0, 5.0, 5.5])
    assert result == (5.0, 5.5)


def test_unsorted_input():
    result = find_closest_elements([5.0, 1.0, 4.0, 2.0, 3.0])
    assert result == (1.0, 2.0)


def test_floats_with_many_decimals():
    result = find_closest_elements([0.123456, 0.123457, 1.0, 2.0])
    assert result == (0.123456, 0.123457)


def test_negative_close_pair():
    result = find_closest_elements([-10.0, -9.9, -5.0, 0.0])
    assert result == (-10.0, -9.9)


def test_zero_in_list():
    result = find_closest_elements([0.0, 0.1, 1.0, 10.0])
    assert result == (0.0, 0.1)


def test_single_zero_pair():
    result = find_closest_elements([0.0, 0.0])
    assert result == (0.0, 0.0)


def test_large_list():
    numbers = [float(i) for i in range(100)]
    result = find_closest_elements(numbers)
    assert result == (0.0, 1.0)


def test_reversed_large_list():
    numbers = [float(i) for i in range(100, 0, -1)]
    result = find_closest_elements(numbers)
    assert result[0] + 1 == result[1]


def test_tie_in_distance_returns_valid_pair():
    result = find_closest_elements([1.0, 2.0, 3.0, 4.0])
    assert result in [(1.0, 2.0), (2.0, 3.0), (3.0, 4.0)]


def test_very_large_numbers():
    result = find_closest_elements([1e15, 1e15 + 1, 1e16])
    assert result == (1e15, 1e15 + 1)


def test_very_small_numbers():
    result = find_closest_elements([1e-10, 2e-10, 1e-5])
    assert result == (1e-10, 2e-10)