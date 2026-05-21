import pytest
from largest_divisor import largest_divisor

def test_largest_divisor_with_prime_number():
    """Test with a prime number where the largest divisor should be 1"""
    assert largest_divisor(13) == 1

def test_largest_divisor_with_composite_number():
    """Test with a composite number that has multiple divisors"""
    assert largest_divisor(15) == 5

def test_largest_divisor_with_perfect_square():
    """Test with a perfect square number"""
    assert largest_divisor(16) == 8

def test_largest_divisor_with_even_number():
    """Test with an even number"""
    assert largest_divisor(20) == 10

def test_largest_divisor_with_number_4():
    """Test with number 4 where largest divisor should be 2"""
    assert largest_divisor(4) == 2

def test_largest_divisor_with_number_2():
    """Test with number 2 where largest divisor should be 1"""
    assert largest_divisor(2) == 1

def test_largest_divisor_with_number_1():
    """Test with number 1 - edge case where range(1) gives range(0) only"""
    assert largest_divisor(1) == None  # Function will not find any divisor, returns None

def test_largest_divisor_with_large_number():
    """Test with a large number"""
    assert largest_divisor(1000000) == 500000

def test_largest_divisor_with_odd_composite():
    """Test with an odd composite number"""
    assert largest_divisor(21) == 7

def test_largest_divisor_with_power_of_two():
    """Test with a power of 2"""
    assert largest_divisor(32) == 16

def test_largest_divisor_returns_immediate_largest():
    """Test that the function returns the first (largest) divisor found"""
    result = largest_divisor(30)
    # The largest divisor less than 30 should be 15 (not 10 or 6)
    assert result == 15

def test_largest_divisor_with_number_3():
    """Test with number 3 - prime number"""
    assert largest_divisor(3) == 1

def test_largest_divisor_with_number_6():
    """Test with number 6"""
    assert largest_divisor(6) == 3

def test_largest_divisor_with_number_9():
    """Test with number 9"""
    assert largest_divisor(9) == 3

def test_largest_divisor_with_number_25():
    """Test with number 25"""
    assert largest_divisor(25) == 5

def test_largest_divisor_with_number_49():
    """Test with number 49"""
    assert largest_divisor(49) == 7