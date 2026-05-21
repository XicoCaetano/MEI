import pytest
from typing import Any, List
from your_module import filter_integers

class TestFilterIntegers:
    """Test suite for filter_integers function"""
    
    def test_empty_list_returns_empty_list(self):
        """Test that empty list returns empty list"""
        assert filter_integers([]) == []
    
    def test_only_integers_returns_same_list(self):
        """Test list with only integers returns unchanged list"""
        input_list = [1, 2, 3, 4, 5]
        expected = [1, 2, 3, 4, 5]
        assert filter_integers(input_list) == expected
    
    def test_no_integers_returns_empty_list(self):
        """Test list with no integers returns empty list"""
        input_list = ['a', 'b', 'c', 3.14, [1, 2], {'key': 'value'}, None, True]
        assert filter_integers(input_list) == []
    
    def test_mixed_types_returns_only_integers(self):
        """Test mixed list returns only integer values"""
        input_list = [1, 'hello', 2, 3.14, 3, None, [1, 2], 4, {}, 5]
        expected = [1, 2, 3, 4, 5]
        assert filter_integers(input_list) == expected
    
    def test_negative_integers_are_included(self):
        """Test negative integers are correctly filtered"""
        input_list = [-1, -2, 3.14, -3, 'text', 0]
        expected = [-1, -2, -3, 0]
        assert filter_integers(input_list) == expected
    
    def test_large_integers_are_included(self):
        """Test large integers are correctly filtered"""
        large_int = 10**100
        input_list = [large_int, 1, 2.5, 'big']
        expected = [large_int, 1]
        assert filter_integers(input_list) == expected
    
    def test_boolean_values_are_not_included(self):
        """Test boolean values (subclass of int) are not included"""
        # Note: In Python, bool is a subclass of int, but the function
        # should only filter for int, not bool based on typical requirements
        input_list = [True, False, 1, 0, 'text']
        # True and False are bool, not int, so they should be excluded
        expected = [1, 0]
        assert filter_integers(input_list) == expected
    
    def test_float_values_are_excluded(self):
        """Test float values are correctly excluded"""
        input_list = [1.0, 2.5, 3.14, 4, 5.0]
        expected = [4]
        assert filter_integers(input_list) == expected
    
    def test_nested_structures_are_excluded(self):
        """Test nested lists, dicts, sets are excluded"""
        input_list = [[1, 2], {'a': 1}, {1, 2, 3}, 42, (1, 2)]
        expected = [42]
        assert filter_integers(input_list) == expected
    
    def test_none_values_are_excluded(self):
        """Test None values are excluded"""
        input_list = [None, 1, None, 2, None, 3]
        expected = [1, 2, 3]
        assert filter_integers(input_list) == expected
    
    def test_string_numbers_are_excluded(self):
        """Test string representations of numbers are excluded"""
        input_list = ['1', '2', '3', 4, 5, '6']
        expected = [4, 5]
        assert filter_integers(input_list) == expected
    
    def test_zero_is_included(self):
        """Test zero is included as integer"""
        input_list = [0, '0', 0.0, False]
        expected = [0]
        assert filter_integers(input_list) == expected
    
    def test_single_element_list_with_integer(self):
        """Test single element list containing integer"""
        assert filter_integers([42]) == [42]
    
    def test_single_element_list_with_non_integer(self):
        """Test single element list containing non-integer"""
        assert filter_integers(['hello']) == []
    
    def test_large_list_with_mixed_types(self):
        """Test performance with larger mixed list"""
        input_list = list(range(100)) + [f'str{i}' for i in range(50)] + [float(i) for i in range(50)]
        expected = list(range(100))
        assert filter_integers(input_list) == expected
    
    def test_duplicate_integers_are_preserved(self):
        """Test duplicate integers are preserved in order"""
        input_list = [1, 2, 1, 3, 2, 1, 'a', 3.14]
        expected = [1, 2, 1, 3, 2, 1]
        assert filter_integers(input_list) == expected
    
    def test_order_is_preserved(self):
        """Test original order of integers is preserved"""
        input_list = [3, 'a', 1, 2.5, 2, 'b', 0, -1]
        expected = [3, 1, 2, 0, -1]
        assert filter_integers(input_list) == expected
    
    def test_special_numeric_values_are_excluded(self):
        """Test float('inf'), float('-inf'), float('nan') are excluded"""
        import math
        input_list = [1, float('inf'), 2, float('-inf'), 3, float('nan')]
        expected = [1, 2, 3]
        result = filter_integers(input_list)
        assert result == expected
        assert all(isinstance(x, int) for x in result)