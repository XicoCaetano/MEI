import pytest
from typing import List
from solution import rolling_max


def test_example_from_docstring():
    assert rolling_max([1, 2, 3, 2, 3, 4, 2]) == [1, 2, 3, 3, 3, 4, 4]

def test_empty_list():
    assert rolling_max([]) == []

def test_single_element():
    assert rolling_max([5]) == [5]

def test_single_negative_element():
    assert rolling_max([-3]) == [-3]

def test_all_same_elements():
    assert rolling_max([4, 4, 4, 4]) == [4, 4, 4, 4]

def test_strictly_increasing():
    assert rolling_max([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

def test_strictly_decreasing():
    assert rolling_max([5, 4, 3, 2, 1]) == [5, 5, 5, 5, 5]

def test_all_negative_numbers():
    assert rolling_max([-5, -3, -7, -1, -4]) == [-5, -3, -3, -1, -1]

def test_mixed_positive_and_negative():
    assert rolling_max([-1, 2, -3, 4, -5]) == [-1, 2, 2, 4, 4]

def test_starts_with_negative_then_positive():
    assert rolling_max([-10, -5, 0, 5, 10]) == [-10, -5, 0, 5, 10]

def test_starts_with_positive_then_negative():
    assert rolling_max([10, 5, 0, -5, -10]) == [10, 10, 10, 10, 10]

def test_zeros():
    assert rolling_max([0, 0, 0]) == [0, 0, 0]

def test_zero_and_positives():
    assert rolling_max([0, 1, 0, 2]) == [0, 1, 1, 2]

def test_zero_and_negatives():
    assert rolling_max([-2, -1, 0, -3]) == [-2, -1, 0, 0]

def test_large_values():
    assert rolling_max([10**9, 10**9 - 1, 10**9 + 1]) == [10**9, 10**9, 10**9 + 1]

def test_two_elements_increasing():
    assert rolling_max([1, 2]) == [1, 2]

def test_two_elements_decreasing():
    assert rolling_max([2, 1]) == [2, 2]

def test_two_equal_elements():
    assert rolling_max([3, 3]) == [3, 3]

def test_max_in_middle():
    assert rolling_max([1, 3, 2]) == [1, 3, 3]

def test_max_at_end():
    assert rolling_max([1, 2, 5]) == [1, 2, 5]

def test_max_at_start():
    assert rolling_max([5, 2, 1]) == [5, 5, 5]

def test_duplicate_max_values():
    assert rolling_max([3, 1, 3, 1]) == [3, 3, 3, 3]

def test_output_length_matches_input():
    input_list = [5, 3, 8, 1, 9, 2]
    result = rolling_max(input_list)
    assert len(result) == len(input_list)

def test_output_is_non_decreasing():
    input_list = [3, 1, 4, 1, 5, 9, 2, 6]
    result = rolling_max(input_list)
    for i in range(1, len(result)):
        assert result[i] >= result[i - 1]

def test_first_element_preserved():
    input_list = [7, 1, 2, 3]
    result = rolling_max(input_list)
    assert result[0] == input_list[0]

def test_last_element_is_global_max_when_at_end():
    input_list = [1, 2, 3, 4, 100]
    result = rolling_max(input_list)
    assert result[-1] == 100

def test_result_values_are_always_from_input():
    input_list = [4, 2, 7, 1, 5]
    result = rolling_max(input_list)
    for val in result:
        assert val in input_list

def test_large_list():
    n = 1000
    input_list = list(range(n))
    result = rolling_max(input_list)
    assert result == list(range(n))

def test_large_list_decreasing():
    n = 1000
    input_list = list(range(n, 0, -1))
    result = rolling_max(input_list)
    assert result == [n] * n

def test_alternating_values():
    assert rolling_max([1, 10, 1, 10, 1]) == [1, 10, 10, 10, 10]

def test_plateau_then_spike():
    assert rolling_max([3, 3, 3, 10, 3, 3]) == [3, 3, 3, 10, 10, 10]

def test_negative_to_zero():
    assert rolling_max([-5, -4, -3, -2, -1, 0]) == [-5, -4, -3, -2, -1, 0]

def test_returns_list_type():
    result = rolling_max([1, 2, 3])
    assert isinstance(result, list)

def test_single_zero():
    assert rolling_max([0]) == [0]

def test_negative_max_throughout():
    assert rolling_max([-10, -20, -30]) == [-10, -10, -10]