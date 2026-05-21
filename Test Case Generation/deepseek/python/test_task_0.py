import pytest
from typing import List
from your_module import has_close_elements  # Ajuste o nome do módulo conforme necessário

class TestHasCloseElements:
    
    def test_empty_list_returns_false(self):
        """Test with empty list"""
        assert has_close_elements([], 0.5) is False
    
    def test_single_element_returns_false(self):
        """Test with single element"""
        assert has_close_elements([1.0], 0.5) is False
        assert has_close_elements([-100.5], 0.1) is False
    
    def test_two_elements_within_threshold_returns_true(self):
        """Test with two elements that are closer than threshold"""
        assert has_close_elements([1.0, 1.2], 0.3) is True
        assert has_close_elements([5.0, 5.05], 0.1) is True
        assert has_close_elements([-10.0, -9.8], 0.3) is True
    
    def test_two_elements_exactly_threshold_returns_false(self):
        """Test with distance exactly equal to threshold"""
        assert has_close_elements([1.0, 1.5], 0.5) is False
    
    def test_two_elements_beyond_threshold_returns_false(self):
        """Test with two elements farther than threshold"""
        assert has_close_elements([1.0, 2.0], 0.5) is False
        assert has_close_elements([10.0, 15.0], 4.0) is False
    
    def test_multiple_elements_with_close_pairs_returns_true(self):
        """Test with multiple elements where a close pair exists"""
        assert has_close_elements([1.0, 2.0, 3.0, 3.1, 4.0], 0.15) is True
        assert has_close_elements([0.1, 0.2, 0.3, 0.31, 0.4], 0.02) is True
        assert has_close_elements([-1.0, -0.5, 0.0, 0.01, 1.0], 0.02) is True
    
    def test_multiple_elements_no_close_pairs_returns_false(self):
        """Test with multiple elements where no pair is within threshold"""
        assert has_close_elements([1.0, 2.0, 3.0, 4.0, 5.0], 0.5) is False
        assert has_close_elements([0.1, 0.3, 0.5, 0.7, 0.9], 0.15) is False
    
    def test_zero_threshold(self):
        """Test with threshold = 0"""
        assert has_close_elements([1.0, 1.0], 0.0) is False  # distance = 0, not < 0
        assert has_close_elements([1.0, 1.0001], 0.0) is False
        assert has_close_elements([5.0, 5.0], 0.0) is False
    
    def test_negative_threshold(self):
        """Test with negative threshold (should always return False)"""
        assert has_close_elements([1.0, 1.0], -0.1) is False
        assert has_close_elements([1.0, 1.5], -0.5) is False
        assert has_close_elements([10.0, 10.05], -0.01) is False
    
    def test_negative_numbers(self):
        """Test with negative numbers"""
        assert has_close_elements([-5.0, -4.9, -4.8], 0.15) is True
        assert has_close_elements([-10.0, -9.0, -8.0], 0.5) is False
    
    def test_mixed_positive_and_negative_numbers(self):
        """Test with mixed positive and negative numbers"""
        assert has_close_elements([-1.0, -0.5, 0.0, 0.4, 0.5], 0.2) is True
        assert has_close_elements([-100.0, -50.0, 0.0, 50.0, 100.0], 10.0) is False
    
    def test_very_small_threshold(self):
        """Test with very small threshold values"""
        assert has_close_elements([1.0, 1.000001], 0.0000005) is False
        assert has_close_elements([1.0, 1.0000001], 0.0000002) is True
        assert has_close_elements([2.5, 2.50000001], 0.000000005) is False
    
    def test_duplicate_elements(self):
        """Test with duplicate elements (distance = 0)"""
        assert has_close_elements([1.0, 1.0], 0.1) is True  # distance 0 < 0.1
        assert has_close_elements([2.5, 2.5, 2.5], 0.0) is False  # 0 < 0 is False
        assert has_close_elements([1.0, 2.0, 2.0, 3.0], 0.01) is True
    
    def test_large_numbers(self):
        """Test with large numbers"""
        assert has_close_elements([1e10, 1e10 + 100], 50) is False
        assert has_close_elements([1e10, 1e10 + 10], 20) is True
        assert has_close_elements([1e10, 2e10, 2e10 + 5e9], 6e9) is True
    
    def test_very_small_numbers(self):
        """Test with very small numbers"""
        assert has_close_elements([1e-10, 2e-10, 2.1e-10], 0.5e-10) is True
        assert has_close_elements([1e-10, 2e-10, 3e-10], 0.9e-10) is False
    
    def test_floating_point_precision(self):
        """Test floating point precision edge cases"""
        assert has_close_elements([0.1 + 0.2, 0.3], 0.0000001) is True  # 0.1+0.2 vs 0.3
        assert has_close_elements([1.0/3.0, 0.3333333333333333], 1e-15) is True
    
    def test_threshold_as_float_inf(self):
        """Test with infinite threshold"""
        assert has_close_elements([1.0, 2.0, 1000.0], float('inf')) is True
    
    def test_first_element_zero(self):
        """Test where first element is zero"""
        assert has_close_elements([0.0, 0.1, 0.2], 0.05) is False
        assert has_close_elements([0.0, 0.01, 0.02], 0.02) is True
    
    def test_all_identical_elements(self):
        """Test with all elements identical"""
        assert has_close_elements([5.0, 5.0, 5.0, 5.0], 0.001) is True
        assert has_close_elements([5.0, 5.0, 5.0, 5.0], 0.0) is False
