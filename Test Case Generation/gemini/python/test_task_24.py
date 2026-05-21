import pytest

def largest_divisor(n: int) -> int:
    """ For a given number n, find the largest number that divides n evenly, smaller than n
    >>> largest_divisor(15)
    5
    """
    for i in reversed(range(n)):
        if n % i == 0:
            return i

def test_largest_divisor_basic():
    """Tests standard composite numbers."""
    assert largest_divisor(15) == 5
    assert largest_divisor(25) == 5
    assert largest_divisor(100) == 50
    assert largest_divisor(9) == 3

def test_largest_divisor_primes():
    """Tests prime numbers where the largest divisor should be 1."""
    assert largest_divisor(7) == 1
    assert largest_divisor(13) == 1
    assert largest_divisor(2) == 1
    assert largest_divisor(101) == 1

def test_largest_divisor_even_numbers():
    """Tests even numbers (should return n/2)."""
    assert largest_divisor(10) == 5
    assert largest_divisor(20) == 10
    assert largest_divisor(1000) == 500

def test_largest_divisor_small_integers():
    """Tests the smallest valid input for the range logic."""
    assert largest_divisor(1) is None  # range(1) is [0], 1 % 0 raises ZeroDivisionError/returns nothing
    assert largest_divisor(2) == 1

def test_largest_divisor_zero_division():
    """
    Validates behavior with n=1 or n=0.
    Note: range(0) is empty, function returns None.
    range(1) contains 0, 1 % 0 raises ZeroDivisionError.
    """
    with pytest.raises(ZeroDivisionError):
        largest_divisor(1)

def test_largest_divisor_large_number():
    """Tests performance and correctness with a larger prime."""
    assert largest_divisor(997) == 1

def test_largest_divisor_negative():
    """Tests behavior with negative numbers (range(negative) is empty)."""
    assert largest_divisor(-5) is None
    assert largest_divisor(0) is None