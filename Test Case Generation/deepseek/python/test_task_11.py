import pytest
from typing import List
from your_module import string_xor

def test_basic_xor():
    """Test basic XOR operation with simple cases"""
    assert string_xor('010', '110') == '100'
    assert string_xor('000', '000') == '000'
    assert string_xor('111', '111') == '000'
    assert string_xor('101', '010') == '111'

def test_single_char():
    """Test with single character strings"""
    assert string_xor('0', '0') == '0'
    assert string_xor('1', '1') == '0'
    assert string_xor('0', '1') == '1'
    assert string_xor('1', '0') == '1'

def test_different_lengths():
    """Test with strings of same length (function assumes equal lengths)"""
    assert string_xor('00', '11') == '11'
    assert string_xor('1010', '0101') == '1111'
    assert string_xor('1111', '0000') == '1111'

def test_edge_cases():
    """Test edge cases including empty strings and long strings"""
    assert string_xor('', '') == ''
    assert string_xor('0', '0') == '0'
    assert string_xor('1', '1') == '0'

def test_long_strings():
    """Test with longer binary strings"""
    a = '1010101010101010'
    b = '0101010101010101'
    expected = '1111111111111111'
    assert string_xor(a, b) == expected
    
    a = '1111111111111111'
    b = '1111111111111111'
    expected = '0000000000000000'
    assert string_xor(a, b) == expected

def test_alternating_patterns():
    """Test with alternating patterns"""
    assert string_xor('1010', '1010') == '0000'
    assert string_xor('0101', '0101') == '0000'
    assert string_xor('1010', '0101') == '1111'

def test_mixed_patterns():
    """Test with various mixed patterns"""
    test_cases = [
        ('110011', '001100', '111111'),
        ('111000', '000111', '111111'),
        ('100100', '011011', '111111'),
        ('101010', '110011', '011001'),
    ]
    for a, b, expected in test_cases:
        assert string_xor(a, b) == expected

def test_all_zeros():
    """Test when one string is all zeros"""
    assert string_xor('0000', '1111') == '1111'
    assert string_xor('1111', '0000') == '1111'
    assert string_xor('000', '101') == '101'

def test_all_ones():
    """Test when one string is all ones"""
    assert string_xor('111', '010') == '101'
    assert string_xor('010', '111') == '101'

def test_large_strings():
    """Test with large binary strings to ensure performance"""
    a = '1' * 1000
    b = '0' * 1000
    expected = '1' * 1000
    assert string_xor(a, b) == expected
    
    a = '1' * 1000
    b = '1' * 1000
    expected = '0' * 1000
    assert string_xor(a, b) == expected

def test_realistic_examples():
    """Test with realistic binary strings"""
    assert string_xor('001', '001') == '000'
    assert string_xor('1100', '1010') == '0110'
    assert string_xor('11110000', '00001111') == '11111111'