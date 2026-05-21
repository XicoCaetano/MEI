import pytest
from typing import List
from your_module import sort_numbers

def test_sort_numbers_valid_input():
    """Test sorting of valid number strings"""
    assert sort_numbers('three one five') == 'one three five'
    assert sort_numbers('zero nine eight seven six five four three two one') == 'zero one two three four five six seven eight nine'
    assert sort_numbers('five five five') == 'five five five'
    assert sort_numbers('nine zero') == 'zero nine'
    assert sort_numbers('one two three four five six seven eight nine zero') == 'zero one two three four five six seven eight nine'

def test_sort_numbers_single_number():
    """Test with single number input"""
    assert sort_numbers('zero') == 'zero'
    assert sort_numbers('five') == 'five'
    assert sort_numbers('nine') == 'nine'

def test_sort_numbers_empty_input():
    """Test with empty string"""
    assert sort_numbers('') == ''

def test_sort_numbers_with_spaces():
    """Test with extra spaces and edge cases"""
    assert sort_numbers('   ') == ''
    assert sort_numbers('   one   two   ') == 'one two'
    assert sort_numbers('two  one  three') == 'one three two'
    assert sort_numbers('  zero  one  ') == 'zero one'

def test_sort_numbers_already_sorted():
    """Test with already sorted input"""
    assert sort_numbers('one two three') == 'one two three'
    assert sort_numbers('zero one two three four') == 'zero one two three four'

def test_sort_numbers_reverse_order():
    """Test with reverse order input"""
    assert sort_numbers('nine eight seven six five four three two one zero') == 'zero one two three four five six seven eight nine'
    assert sort_numbers('five four three two one') == 'one two three four five'

def test_sort_numbers_duplicate_values():
    """Test with duplicate number values"""
    assert sort_numbers('one one one') == 'one one one'
    assert sort_numbers('two one two three one') == 'one one two two three'
    assert sort_numbers('nine nine zero zero') == 'zero zero nine nine'

def test_sort_numbers_mixed_unsorted():
    """Test with various unsorted combinations"""
    assert sort_numbers('eight two nine one') == 'one two eight nine'
    assert sort_numbers('six three seven one eight') == 'one three six seven eight'
    assert sort_numbers('four nine zero two seven') == 'zero two four seven nine'

def test_sort_numbers_all_numbers_once():
    """Test with all numbers exactly once in random order"""
    assert sort_numbers('five eight zero four six two nine seven three one') == 'zero one two three four five six seven eight nine'
    assert sort_numbers('seven one six three nine four two eight zero five') == 'zero one two three four five six seven eight nine'

def test_sort_numbers_leading_trailing_whitespace():
    """Test with leading and trailing whitespace"""
    assert sort_numbers('  one three two  ') == 'one three two'
    assert sort_numbers('\tone three two\n') == 'one three two'
    assert sort_numbers('  \t  one three two  \n  ') == 'one three two'

def test_sort_numbers_multiple_whitespace_between():
    """Test with multiple whitespace characters between numbers"""
    assert sort_numbers('one   three    two') == 'one three two'
    assert sort_numbers('zero  \t  one  \n  two') == 'zero one two'