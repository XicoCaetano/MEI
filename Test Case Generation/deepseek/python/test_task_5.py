import pytest
from typing import List
from your_module import intersperse  # Replace with actual module name

def test_empty_list():
    """Test with empty list"""
    assert intersperse([], 4) == []
    assert intersperse([], 0) == []
    assert intersperse([], -1) == []

def test_single_element():
    """Test with list containing one element"""
    assert intersperse([1], 4) == [1]
    assert intersperse([42], 0) == [42]
    assert intersperse([-5], 10) == [-5]

def test_two_elements():
    """Test with list containing two elements"""
    assert intersperse([1, 2], 4) == [1, 4, 2]
    assert intersperse([-1, 5], 0) == [-1, 0, 5]

def test_three_elements():
    """Test with list containing three elements"""
    assert intersperse([1, 2, 3], 4) == [1, 4, 2, 4, 3]
    assert intersperse([10, 20, 30], 0) == [10, 0, 20, 0, 30]

def test_four_elements():
    """Test with list containing four elements"""
    assert intersperse([1, 2, 3, 4], 4) == [1, 4, 2, 4, 3, 4, 4]
    assert intersperse([5, 6, 7, 8], 0) == [5, 0, 6, 0, 7, 0, 8]

def test_negative_delimeter():
    """Test with negative delimiter values"""
    assert intersperse([1, 2, 3], -1) == [1, -1, 2, -1, 3]
    assert intersperse([0, 0, 0], -5) == [0, -5, 0, -5, 0]

def test_zero_delimeter():
    """Test with zero as delimiter"""
    assert intersperse([1, 2, 3], 0) == [1, 0, 2, 0, 3]
    assert intersperse([42, 100], 0) == [42, 0, 100]

def test_identical_numbers():
    """Test with all elements having the same value"""
    assert intersperse([5, 5, 5], 5) == [5, 5, 5, 5, 5]
    assert intersperse([0, 0, 0, 0], 0) == [0, 0, 0, 0, 0, 0, 0]

def test_negative_numbers_in_list():
    """Test with negative numbers in the input list"""
    assert intersperse([-1, -2, -3], 5) == [-1, 5, -2, 5, -3]
    assert intersperse([-5, -10], 100) == [-5, 100, -10]

def test_mixed_sign_numbers():
    """Test with mixed positive and negative numbers"""
    assert intersperse([-1, 0, 1], 10) == [-1, 10, 0, 10, 1]
    assert intersperse([-10, 5, -3, 7], -2) == [-10, -2, 5, -2, -3, -2, 7]

def test_large_numbers():
    """Test with very large integer values"""
    large_num = 10**9
    assert intersperse([large_num, large_num + 1, large_num + 2], 100) == [
        large_num, 100, large_num + 1, 100, large_num + 2
    ]

def test_no_modification_of_original():
    """Test that original list is not modified (if needed)"""
    original = [1, 2, 3]
    original_copy = original[:]
    intersperse(original, 4)
    assert original == original_copy

def test_edge_case_delimeter_same_as_element():
    """Test with delimiter equal to elements in list"""
    assert intersperse([1, 1, 1], 1) == [1, 1, 1, 1, 1]

def test_edge_case_large_randint_values():
    """Test with random large integer values"""
    huge_list = list(range(1000, 2000))
    result = intersperse(huge_list, 999)
    
    assert len(result) == 2 * len(huge_list) - 1
    for i, elem in enumerate(result):
        if i % 2 == 0:
            assert elem == huge_list[i // 2]
        else:
            assert elem == 999