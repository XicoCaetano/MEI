import pytest
from typing import List, Tuple
from your_module import find_closest_elements

def test_basic_case_with_distinct_closest():
    """Test basic functionality with distinct closest elements."""
    numbers = [1.0, 2.0, 3.0, 4.0, 5.0, 2.2]
    result = find_closest_elements(numbers)
    assert result == (2.0, 2.2)

def test_duplicate_closest_elements():
    """Test when closest elements are the same value."""
    numbers = [1.0, 2.0, 3.0, 4.0, 5.0, 2.0]
    result = find_closest_elements(numbers)
    assert result == (2.0, 2.0)

def test_minimum_length_list_two_elements():
    """Test edge case with exactly two elements."""
    numbers = [1.5, 3.5]
    result = find_closest_elements(numbers)
    assert result == (1.5, 3.5)

def test_negative_numbers():
    """Test with negative numbers."""
    numbers = [-5.0, -1.0, -3.0, -2.0, -4.0]
    result = find_closest_elements(numbers)
    assert result == (-2.0, -1.0)

def test_mixed_positive_and_negative():
    """Test with both positive and negative numbers."""
    numbers = [-5.0, 0.0, 5.0, 2.0, -2.0]
    result = find_closest_elements(numbers)
    assert result == (0.0, 2.0)

def test_floating_point_precision():
    """Test with floating point numbers that require precision handling."""
    numbers = [1.1, 1.2, 1.3, 1.4, 1.5]
    result = find_closest_elements(numbers)
    assert result == (1.1, 1.2)

def test_identical_numbers():
    """Test when all numbers are identical."""
    numbers = [3.0, 3.0, 3.0, 3.0]
    result = find_closest_elements(numbers)
    assert result == (3.0, 3.0)

def test_descending_order_input():
    """Test with input in descending order."""
    numbers = [5.0, 4.0, 3.0, 2.0, 1.0]
    result = find_closest_elements(numbers)
    assert result == (1.0, 2.0)

def test_unsorted_input():
    """Test with unsorted input."""
    numbers = [10.0, 1.0, 5.0, 3.0, 8.0, 2.0]
    result = find_closest_elements(numbers)
    assert result == (1.0, 2.0)

def test_large_numbers():
    """Test with large numbers."""
    numbers = [1000000.0, 1000001.0, 1000002.0, 999999.0]
    result = find_closest_elements(numbers)
    assert result == (999999.0, 1000000.0)

def test_small_decimal_differences():
    """Test with very small decimal differences."""
    numbers = [1.0, 1.0001, 1.0002, 1.0003]
    result = find_closest_elements(numbers)
    assert result == (1.0001, 1.0002)

def test_multiple_pairs_with_same_distance():
    """Test when multiple pairs have the same minimum distance."""
    numbers = [1.0, 2.0, 3.0, 4.0, 5.0]
    result = find_closest_elements(numbers)
    # Should return the first encountered pair (1.0, 2.0) based on enumeration order
    assert result == (1.0, 2.0)

def test_large_list_performance():
    """Test with a larger list to ensure implementation works."""
    numbers = [float(i) for i in range(1000)]
    result = find_closest_elements(numbers)
    assert result == (0.0, 1.0)

def test_negative_floating_point_precision():
    """Test with negative floating point numbers requiring precision."""
    numbers = [-1.1, -1.2, -1.3, -1.4]
    result = find_closest_elements(numbers)
    assert result == (-1.2, -1.1)

def test_zeros_and_small_numbers():
    """Test with zeros and very small numbers."""
    numbers = [0.0, 0.0001, 0.0002, 0.0003]
    result = find_closest_elements(numbers)
    assert result == (0.0001, 0.0002)

def test_duplicate_min_distance_with_later_pair():
    """Test when a later pair has the same distance as an earlier pair."""
    numbers = [1.0, 5.0, 2.0, 3.0]
    result = find_closest_elements(numbers)
    assert result == (1.0, 2.0)