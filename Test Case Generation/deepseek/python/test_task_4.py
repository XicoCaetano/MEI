import pytest
from typing import List
from your_module import mean_absolute_deviation  # Replace with actual module name

class TestMeanAbsoluteDeviation:
    
    def test_basic_case_from_docstring(self):
        """Test the example provided in the docstring"""
        assert mean_absolute_deviation([1.0, 2.0, 3.0, 4.0]) == 1.0
    
    def test_single_element_list(self):
        """Test with a single number - MAD should be 0"""
        assert mean_absolute_deviation([5.0]) == 0.0
        assert mean_absolute_deviation([-3.5]) == 0.0
        assert mean_absolute_deviation([0.0]) == 0.0
    
    def test_two_elements_symmetric(self):
        """Test with two symmetric numbers around the mean"""
        assert mean_absolute_deviation([1.0, 3.0]) == 1.0
        assert mean_absolute_deviation([-2.0, 2.0]) == 2.0
    
    def test_two_elements_asymmetric(self):
        """Test with two asymmetric numbers"""
        result = mean_absolute_deviation([10.0, 20.0])
        # Mean = 15, |10-15|=5, |20-15|=5, average = 5
        assert result == 5.0
    
    def test_negative_numbers(self):
        """Test with negative numbers only"""
        result = mean_absolute_deviation([-5.0, -3.0, -1.0])
        # Mean = -3, differences: 2, 0, 2, average = 4/3 ≈ 1.333...
        assert result == pytest.approx(4.0/3.0)
    
    def test_mixed_positive_and_negative(self):
        """Test with mixed positive and negative numbers"""
        result = mean_absolute_deviation([-10.0, 0.0, 10.0])
        # Mean = 0, differences: 10, 0, 10, average = 20/3 ≈ 6.666...
        assert result == pytest.approx(20.0/3.0)
    
    def test_all_identical_numbers(self):
        """Test when all numbers are identical - MAD should be 0"""
        assert mean_absolute_deviation([7.0, 7.0, 7.0, 7.0]) == 0.0
        assert mean_absolute_deviation([-2.5, -2.5, -2.5]) == 0.0
    
    def test_zero_values(self):
        """Test with zeros"""
        assert mean_absolute_deviation([0.0, 0.0, 0.0]) == 0.0
        assert mean_absolute_deviation([0.0, 1.0, 2.0]) == pytest.approx(2.0/3.0)
    
    def test_floating_point_precision(self):
        """Test with floating point numbers that might have precision issues"""
        result = mean_absolute_deviation([1.1, 2.2, 3.3])
        expected = (abs(1.1 - 2.2) + abs(2.2 - 2.2) + abs(3.3 - 2.2)) / 3
        assert result == pytest.approx(expected)
    
    def test_large_numbers(self):
        """Test with large numbers"""
        result = mean_absolute_deviation([1000000.0, 2000000.0, 3000000.0])
        # Mean = 2000000, differences: 1000000, 0, 1000000, average = 2000000/3
        assert result == pytest.approx(2000000.0/3.0)
    
    def test_small_numbers(self):
        """Test with very small numbers"""
        result = mean_absolute_deviation([1e-10, 2e-10, 3e-10])
        expected = (1e-10 + 0 + 1e-10) / 3
        assert result == pytest.approx(expected)
    
    def test_three_elements_uneven(self):
        """Test with three elements where mean is not an element"""
        result = mean_absolute_deviation([1.0, 2.0, 6.0])
        # Mean = 3, differences: 2, 1, 3, average = 6/3 = 2
        assert result == 2.0
    
    def test_five_elements_symmetric_around_mean(self):
        """Test with five elements symmetric around the mean"""
        result = mean_absolute_deviation([2.0, 4.0, 6.0, 8.0, 10.0])
        # Mean = 6, differences: 4, 2, 0, 2, 4, average = 12/5 = 2.4
        assert result == 2.4
    
    def test_decimal_numbers(self):
        """Test with decimal numbers that require precise calculation"""
        result = mean_absolute_deviation([0.1, 0.2, 0.3, 0.4, 0.5])
        # Mean = 0.3, differences: 0.2, 0.1, 0, 0.1, 0.2, average = 0.6/5 = 0.12
        assert result == pytest.approx(0.12)
    
    def test_very_small_deviations(self):
        """Test where deviations are very small"""
        result = mean_absolute_deviation([5.0001, 5.0002, 5.0003])
        # Mean = 5.0002, differences: 0.0001, 0, 0.0001, average = 0.0002/3 ≈ 0.00006667
        assert result == pytest.approx(0.0002/3.0)
    
    @pytest.mark.parametrize("input_list,expected", [
        ([1.0], 0.0),
        ([1.0, 1.0], 0.0),
        ([1.0, 2.0], 0.5),
        ([1.0, 2.0, 3.0], pytest.approx(2.0/3.0)),
        ([1.0, 1.0, 1.0, 1.0], 0.0),
        ([-1.0, -2.0, -3.0], pytest.approx(2.0/3.0)),
        ([0.0, 0.0, 5.0, 5.0], 2.5),
    ])
    def test_parametrized_cases(self, input_list, expected):
        """Parametrized test for various input combinations"""
        assert mean_absolute_deviation(input_list) == expected
    
    def test_preserves_input_list(self):
        """Test that the function doesn't modify the input list"""
        original = [1.0, 2.0, 3.0, 4.0]
        input_copy = original.copy()
        mean_absolute_deviation(original)
        assert original == input_copy
    
    def test_return_type(self):
        """Test that the function returns a float"""
        result = mean_absolute_deviation([1.0, 2.0, 3.0])
        assert isinstance(result, float)
    
    def test_empty_list_raises_error(self):
        """Test that empty list raises ZeroDivisionError"""
        with pytest.raises(ZeroDivisionError):
            mean_absolute_deviation([])