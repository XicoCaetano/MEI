import pytest
from typing import List
from your_module import remove_duplicates

def test_empty_list():
    """Test with empty list"""
    assert remove_duplicates([]) == []

def test_single_element():
    """Test with single element"""
    assert remove_duplicates([1]) == [1]

def test_all_unique_elements():
    """Test with all elements occurring exactly once"""
    assert remove_duplicates([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

def test_all_duplicates():
    """Test with all elements occurring more than once"""
    assert remove_duplicates([1, 1, 1, 1]) == []
    assert remove_duplicates([2, 2, 2]) == []

def test_mixed_duplicates():
    """Test with mix of unique and duplicate elements"""
    assert remove_duplicates([1, 2, 3, 2, 4]) == [1, 3, 4]

def test_multiple_occurrences():
    """Test with elements occurring more than twice"""
    assert remove_duplicates([1, 1, 1, 2, 2, 3]) == [3]

def test_no_duplicates_after_removal():
    """Test where duplicates are removed and only uniques remain"""
    assert remove_duplicates([5, 5, 5, 1, 2, 2, 3, 4, 4]) == [1, 3]

def test_negative_numbers():
    """Test with negative integers"""
    assert remove_duplicates([-1, -2, -1, -3, -2]) == [-3]
    assert remove_duplicates([-1, -1, -1]) == []

def test_zero():
    """Test with zero values"""
    assert remove_duplicates([0, 0, 1, 2, 0]) == [1, 2]
    assert remove_duplicates([0, 1, 0, 2, 0, 3]) == [1, 2, 3]

def test_mixed_positive_negative():
    """Test with mix of positive and negative numbers"""
    assert remove_duplicates([-5, 1, -5, 2, 3, 1, 4]) == [2, 3, 4]

def test_order_preservation():
    """Test that order of unique elements is preserved"""
    assert remove_duplicates([3, 1, 4, 1, 5, 3, 2, 6, 5]) == [4, 2, 6]

def test_large_numbers():
    """Test with large integers"""
    assert remove_duplicates([1000000, 2000000, 1000000, 3000000]) == [2000000, 3000000]

def test_alternating_duplicates():
    """Test with alternating duplicate pattern"""
    assert remove_duplicates([1, 2, 1, 2, 1, 2, 3]) == [3]

def test_consecutive_duplicates():
    """Test with consecutive duplicate elements"""
    assert remove_duplicates([1, 1, 2, 2, 3, 3, 4]) == [4]

def test_sparse_duplicates():
    """Test with duplicates far apart"""
    assert remove_duplicates([1, 2, 3, 4, 5, 1, 6, 7, 2, 8]) == [3, 4, 5, 6, 7, 8]

def test_single_duplicate_pair():
    """Test with exactly one pair of duplicates"""
    assert remove_duplicates([1, 2, 3, 1, 4, 5]) == [2, 3, 4, 5]

def test_all_same_element():
    """Test with all identical elements"""
    assert remove_duplicates([42, 42, 42, 42, 42]) == []

def test_two_distinct_elements_both_duplicated():
    """Test with two distinct elements both appearing multiple times"""
    assert remove_duplicates([1, 2, 1, 2, 1, 2]) == []

def test_single_element_with_duplicates():
    """Test with single element type appearing multiple times"""
    assert remove_duplicates([7, 7, 7, 7]) == []

def test_complex_mixed():
    """Test with complex mixed pattern"""
    assert remove_duplicates([-10, 5, -10, 5, 3, 8, 3, 2, 9, 9, 1]) == [8, 2, 1]

def test_verify_counter_usage():
    """Test that counter correctly handles frequency counting"""
    result = remove_duplicates([1, 2, 2, 3, 3, 3, 4, 4, 4, 4])
    assert result == [1]
    
    result2 = remove_duplicates([1, 1, 2, 3, 3, 4, 5, 5, 6])
    assert result2 == [2, 4, 6]