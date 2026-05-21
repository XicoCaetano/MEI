import pytest
from typing import List
from your_module import rolling_max  # Replace 'your_module' with the actual module name

def test_rolling_max_empty_list():
    """Test rolling_max with an empty list."""
    assert rolling_max([]) == []

def test_rolling_max_single_element():
    """Test rolling_max with a single element."""
    assert rolling_max([5]) == [5]

def test_rolling_max_increasing_sequence():
    """Test rolling_max with a strictly increasing sequence."""
    assert rolling_max([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

def test_rolling_max_decreasing_sequence():
    """Test rolling_max with a strictly decreasing sequence."""
    assert rolling_max([5, 4, 3, 2, 1]) == [5, 5, 5, 5, 5]

def test_rolling_max_constant_sequence():
    """Test rolling_max with a sequence of identical numbers."""
    assert rolling_max([3, 3, 3, 3, 3]) == [3, 3, 3, 3, 3]

def test_rolling_max_given_example():
    """Test rolling_max with the example from the docstring."""
    assert rolling_max([1, 2, 3, 2, 3, 4, 2]) == [1, 2, 3, 3, 3, 4, 4]

def test_rolling_max_with_negative_numbers():
    """Test rolling_max with negative numbers."""
    assert rolling_max([-5, -3, -4, -2, -1, -3]) == [-5, -3, -3, -2, -1, -1]

def test_rolling_max_mixed_positive_negative():
    """Test rolling_max with mixed positive and negative numbers."""
    assert rolling_max([-1, 5, 0, -2, 10, 3, -5]) == [-1, 5, 5, 5, 10, 10, 10]

def test_rolling_max_with_large_numbers():
    """Test rolling_max with large integer values."""
    large_numbers = [1000000, 999999, 1000001, 1000000]
    assert rolling_max(large_numbers) == [1000000, 1000000, 1000001, 1000001]

def test_rolling_max_with_zero():
    """Test rolling_max with zero in various positions."""
    assert rolling_max([0, -1, 5, 0, 3]) == [0, 0, 5, 5, 5]

def test_rolling_max_alternating_values():
    """Test rolling_max with alternating high and low values."""
    assert rolling_max([10, 1, 9, 2, 8, 3, 7]) == [10, 10, 10, 10, 10, 10, 10]

def test_rolling_max_duplicates_at_beginning():
    """Test rolling_max with duplicate values at the beginning."""
    assert rolling_max([5, 5, 5, 1, 2, 3]) == [5, 5, 5, 5, 5, 5]

def test_rolling_max_duplicates_at_end():
    """Test rolling_max with duplicate values at the end."""
    assert rolling_max([1, 2, 3, 5, 5, 5]) == [1, 2, 3, 5, 5, 5]

def test_rolling_max_single_element_negative():
    """Test rolling_max with a single negative element."""
    assert rolling_max([-10]) == [-10]

def test_rolling_max_two_elements_increasing():
    """Test rolling_max with two elements that increase."""
    assert rolling_max([3, 5]) == [3, 5]

def test_rolling_max_two_elements_decreasing():
    """Test rolling_max with two elements that decrease."""
    assert rolling_max([5, 3]) == [5, 5]

def test_rolling_max_two_elements_equal():
    """Test rolling_max with two equal elements."""
    assert rolling_max([4, 4]) == [4, 4]