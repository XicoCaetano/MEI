import pytest
from typing import List
from solution import has_close_elements


def test_docstring_example_false():
    assert has_close_elements([1.0, 2.0, 3.0], 0.5) == False


def test_docstring_example_true():
    assert has_close_elements([1.0, 2.8, 3.0, 4.0, 5.0, 2.0], 0.3) == True


def test_empty_list():
    assert has_close_elements([], 1.0) == False


def test_single_element():
    assert has_close_elements([5.0], 1.0) == False


def test_two_elements_close():
    assert has_close_elements([1.0, 1.4], 0.5) == True


def test_two_elements_not_close():
    assert has_close_elements([1.0, 2.0], 0.5) == False


def test_two_elements_exactly_at_threshold():
    assert has_close_elements([1.0, 1.5], 0.5) == False


def test_two_elements_just_below_threshold():
    assert has_close_elements([1.0, 1.499], 0.5) == True


def test_identical_elements():
    assert has_close_elements([3.0, 3.0], 0.1) == True


def test_identical_elements_zero_threshold():
    assert has_close_elements([3.0, 3.0], 0.0) == False


def test_zero_threshold_no_duplicates():
    assert has_close_elements([1.0, 2.0, 3.0], 0.0) == False


def test_negative_numbers_close():
    assert has_close_elements([-1.0, -1.2], 0.5) == True


def test_negative_numbers_not_close():
    assert has_close_elements([-1.0, -3.0], 0.5) == False


def test_mixed_positive_negative_close():
    assert has_close_elements([-0.1, 0.1], 0.3) == True


def test_mixed_positive_negative_not_close():
    assert has_close_elements([-1.0, 1.0], 0.5) == False


def test_large_threshold_all_close():
    assert has_close_elements([1.0, 100.0, 1000.0], 10000.0) == True


def test_very_small_threshold():
    assert has_close_elements([1.0, 1.0000001], 0.000001) == True


def test_very_small_threshold_not_close():
    assert has_close_elements([1.0, 2.0], 0.000001) == False


def test_large_list_no_close_elements():
    numbers = [float(i * 10) for i in range(100)]
    assert has_close_elements(numbers, 5.0) == False


def test_large_list_with_close_elements():
    numbers = [float(i * 10) for i in range(100)]
    numbers.append(numbers[50] + 1.0)
    assert has_close_elements(numbers, 2.0) == True


def test_close_elements_at_end_of_list():
    assert has_close_elements([10.0, 20.0, 30.0, 40.0, 40.1], 0.5) == True


def test_close_elements_at_beginning_of_list():
    assert has_close_elements([1.0, 1.1, 10.0, 20.0, 30.0], 0.5) == True


def test_all_same_elements():
    assert has_close_elements([5.0, 5.0, 5.0, 5.0], 0.1) == True


def test_floating_point_precision():
    assert has_close_elements([0.1 + 0.2, 0.3], 1e-9) == True


def test_negative_threshold_no_close():
    assert has_close_elements([1.0, 2.0, 3.0], -1.0) == False


def test_two_elements_reversed_order():
    assert has_close_elements([2.0, 1.0], 1.5) == True


def test_symmetry_of_comparison():
    result1 = has_close_elements([1.0, 2.0], 1.5)
    result2 = has_close_elements([2.0, 1.0], 1.5)
    assert result1 == result2


def test_non_adjacent_close_elements():
    assert has_close_elements([1.0, 10.0, 20.0, 1.05], 0.1) == True


def test_zeros():
    assert has_close_elements([0.0, 0.0], 0.1) == True


def test_single_zero():
    assert has_close_elements([0.0], 0.5) == False


def test_large_positive_values():
    assert has_close_elements([1e15, 1e15 + 1], 10.0) == True


def test_large_negative_values():
    assert has_close_elements([-1e15, -1e15 - 1], 10.0) == True