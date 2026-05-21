import pytest
from typing import List, Tuple
from src.sum_product import sum_product  # Adjust import path as needed

class TestSumProduct:
    """Test suite for sum_product function."""
    
    def test_empty_list(self):
        """Test that empty list returns (0, 1)."""
        assert sum_product([]) == (0, 1)
    
    def test_single_element(self):
        """Test list with single element."""
        assert sum_product([5]) == (5, 5)
        assert sum_product([-3]) == (-3, -3)
        assert sum_product([0]) == (0, 0)
    
    def test_two_elements(self):
        """Test list with two elements."""
        assert sum_product([2, 3]) == (5, 6)
        assert sum_product([-1, 5]) == (4, -5)
        assert sum_product([0, 10]) == (10, 0)
    
    def test_multiple_elements(self):
        """Test list with multiple elements."""
        assert sum_product([1, 2, 3, 4]) == (10, 24)
        assert sum_product([1, 1, 1, 1]) == (4, 1)
        assert sum_product([-1, -2, -3, -4]) == (-10, 24)
    
    def test_with_zeros(self):
        """Test lists containing zeros."""
        assert sum_product([0, 1, 2, 3]) == (6, 0)
        assert sum_product([0, 0, 5]) == (5, 0)
        assert sum_product([0, 0, 0]) == (0, 0)
    
    def test_with_negative_numbers(self):
        """Test lists with negative numbers."""
        assert sum_product([-1, -2, 3]) == (0, 6)
        assert sum_product([-5, -5, -5]) == (-15, -125)
        assert sum_product([-1, 2, -3, 4]) == (2, 24)
    
    def test_large_numbers(self):
        """Test with large integers."""
        assert sum_product([1000, 2000, 3000]) == (6000, 6000000000)
        assert sum_product([-1000, 1000]) == (0, -1000000)
    
    def test_product_overflow_behavior(self):
        """Test with numbers that might cause overflow (Python handles big ints)."""
        result = sum_product([2, 3, 5, 7, 11, 13, 17, 19])
        expected_sum = 2 + 3 + 5 + 7 + 11 + 13 + 17 + 19
        expected_product = 2 * 3 * 5 * 7 * 11 * 13 * 17 * 19
        assert result == (expected_sum, expected_product)
    
    def test_single_zero(self):
        """Test single zero element."""
        assert sum_product([0]) == (0, 0)
    
    def test_single_negative_zero(self):
        """Test single negative zero (identical to zero)."""
        assert sum_product([-0]) == (0, 0)
    
    def test_alternating_signs(self):
        """Test alternating positive and negative numbers."""
        assert sum_product([-1, 2, -3, 4, -5]) == (-3, -120)
        assert sum_product([1, -2, 3, -4, 5]) == (3, -120)
    
    def test_very_large_list(self):
        """Test with a large list to verify performance and correctness."""
        numbers = list(range(1, 101))  # 1 to 100
        expected_sum = 5050  # Sum of 1..100
        # Product is huge, but Python handles it
        result = sum_product(numbers)
        assert result[0] == expected_sum
        # Only verify product has correct sign (positive since all numbers positive)
        assert result[1] > 0
    
    def test_repeated_same_number(self):
        """Test list with repeated same number."""
        assert sum_product([3, 3, 3]) == (9, 27)
        assert sum_product([-2, -2, -2, -2]) == (-8, 16)
    
    def test_one_and_negative_one_combinations(self):
        """Test combinations of 1 and -1."""
        assert sum_product([1, -1, 1, -1]) == (0, 1)
        assert sum_product([-1, -1, -1]) == (-3, -1)
    
    def test_mixed_positive_negative_with_zero(self):
        """Test mixed signs including zero."""
        assert sum_product([-1, 0, 1, -2, 2]) == (0, 0)
        assert sum_product([-5, 3, 0, -2, 4]) == (0, 0)