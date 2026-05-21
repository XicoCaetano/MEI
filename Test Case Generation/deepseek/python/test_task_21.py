import pytest
from typing import List
from your_module import rescale_to_unit

def test_rescale_to_unit_typical_case():
    """Test with a typical list of positive numbers."""
    assert rescale_to_unit([1.0, 2.0, 3.0, 4.0, 5.0]) == [0.0, 0.25, 0.5, 0.75, 1.0]

def test_rescale_to_unit_with_negative_numbers():
    """Test with negative numbers."""
    assert rescale_to_unit([-5.0, -3.0, 0.0, 2.0, 4.0]) == [0.0, 0.2222222222222222, 0.5555555555555556, 0.7777777777777778, 1.0]

def test_rescale_to_unit_all_identical_numbers():
    """Test when all numbers are identical (should raise ZeroDivisionError)."""
    with pytest.raises(ZeroDivisionError):
        rescale_to_unit([5.0, 5.0, 5.0])

def test_rescale_to_unit_two_elements():
    """Test with exactly two elements (minimum requirement)."""
    assert rescale_to_unit([10.0, 20.0]) == [0.0, 1.0]
    assert rescale_to_unit([-10.0, 5.0]) == [0.0, 1.0]
    assert rescale_to_unit([100.0, 100.0]) == [0.0, 0.0]  # Will raise ZeroDivisionError

def test_rescale_to_unit_with_zero_range():
    """Test when max and min are equal."""
    with pytest.raises(ZeroDivisionError):
        rescale_to_unit([1.0, 1.0, 1.0])

def test_rescale_to_unit_descending_order():
    """Test with input in descending order."""
    assert rescale_to_unit([5.0, 4.0, 3.0, 2.0, 1.0]) == [1.0, 0.75, 0.5, 0.25, 0.0]

def test_rescale_to_unit_unsorted():
    """Test with unsorted input."""
    assert rescale_to_unit([3.0, 1.0, 5.0, 2.0, 4.0]) == [0.5, 0.0, 1.0, 0.25, 0.75]

def test_rescale_to_unit_with_floating_point_precision():
    """Test with floating point numbers that might cause precision issues."""
    result = rescale_to_unit([0.1, 0.3, 0.5])
    expected = [0.0, 0.5, 1.0]
    assert all(abs(r - e) < 1e-10 for r, e in zip(result, expected))

def test_rescale_to_unit_with_decimal_values():
    """Test with decimal values."""
    result = rescale_to_unit([0.0, 2.5, 5.0, 7.5, 10.0])
    assert result == [0.0, 0.25, 0.5, 0.75, 1.0]

def test_rescale_to_unit_min_at_end():
    """Test with minimum value at the end of the list."""
    assert rescale_to_unit([5.0, 4.0, 3.0, 2.0, 1.0]) == [1.0, 0.75, 0.5, 0.25, 0.0]

def test_rescale_to_unit_max_at_beginning():
    """Test with maximum value at the beginning of the list."""
    assert rescale_to_unit([5.0, 4.0, 3.0, 2.0, 1.0]) == [1.0, 0.75, 0.5, 0.25, 0.0]

def test_rescale_to_unit_same_min_max():
    """Test with same minimum and maximum."""
    with pytest.raises(ZeroDivisionError):
        rescale_to_unit([42.0, 42.0])

def test_rescale_to_unit_with_large_numbers():
    """Test with very large numbers."""
    large_numbers = [1e10, 2e10, 3e10, 4e10, 5e10]
    result = rescale_to_unit(large_numbers)
    assert result == [0.0, 0.25, 0.5, 0.75, 1.0]

def test_rescale_to_unit_with_small_numbers():
    """Test with very small numbers."""
    small_numbers = [1e-10, 2e-10, 3e-10, 4e-10, 5e-10]
    result = rescale_to_unit(small_numbers)
    assert result == [0.0, 0.25, 0.5, 0.75, 1.0]

def test_rescale_to_unit_preserves_order():
    """Test that the function preserves the original order of elements."""
    input_list = [3.0, 1.0, 4.0, 2.0, 5.0]
    result = rescale_to_unit(input_list)
    # Check that the relative order is preserved (min stays at same index, etc.)
    assert result.index(0.0) == input_list.index(1.0)
    assert result.index(1.0) == input_list.index(5.0)

def test_rescale_to_unit_negative_and_positive():
    """Test with mix of negative and positive numbers."""
    assert rescale_to_unit([-10.0, -5.0, 0.0, 5.0, 10.0]) == [0.0, 0.25, 0.5, 0.75, 1.0]