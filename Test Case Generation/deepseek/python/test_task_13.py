import pytest
from your_module import greatest_common_divisor

def test_positive_numbers():
    assert greatest_common_divisor(3, 5) == 1
    assert greatest_common_divisor(25, 15) == 5
    assert greatest_common_divisor(48, 18) == 6
    assert greatest_common_divisor(100, 25) == 25
    assert greatest_common_divisor(17, 19) == 1

def test_equal_numbers():
    assert greatest_common_divisor(7, 7) == 7
    assert greatest_common_divisor(42, 42) == 42
    assert greatest_common_divisor(1, 1) == 1
    assert greatest_common_divisor(0, 0) == 0

def test_with_zero():
    assert greatest_common_divisor(0, 5) == 5
    assert greatest_common_divisor(5, 0) == 5
    assert greatest_common_divisor(0, 0) == 0
    assert greatest_common_divisor(0, 1) == 1

def test_negative_numbers():
    assert greatest_common_divisor(-3, 5) == 1
    assert greatest_common_divisor(3, -5) == 1
    assert greatest_common_divisor(-3, -5) == 1
    assert greatest_common_divisor(-25, 15) == 5
    assert greatest_common_divisor(25, -15) == 5
    assert greatest_common_divisor(-25, -15) == 5
    assert greatest_common_divisor(-48, -18) == 6
    assert greatest_common_divisor(-7, 7) == 7

def test_one_as_argument():
    assert greatest_common_divisor(1, 100) == 1
    assert greatest_common_divisor(100, 1) == 1
    assert greatest_common_divisor(1, 1) == 1
    assert greatest_common_divisor(1, 0) == 1
    assert greatest_common_divisor(0, 1) == 1

def test_prime_numbers():
    assert greatest_common_divisor(2, 3) == 1
    assert greatest_common_divisor(13, 17) == 1
    assert greatest_common_divisor(31, 37) == 1
    assert greatest_common_divisor(2, 4) == 2

def test_large_numbers():
    assert greatest_common_divisor(1000000, 500000) == 500000
    assert greatest_common_divisor(999999, 333333) == 333333
    assert greatest_common_divisor(123456789, 987654321) == 9

def test_consecutive_numbers():
    assert greatest_common_divisor(10, 11) == 1
    assert greatest_common_divisor(100, 101) == 1
    assert greatest_common_divisor(1000, 1001) == 1

def test_even_and_odd():
    assert greatest_common_divisor(6, 9) == 3
    assert greatest_common_divisor(10, 15) == 5
    assert greatest_common_divisor(14, 21) == 7

def test_same_absolute_value():
    assert greatest_common_divisor(-10, 10) == 10
    assert greatest_common_divisor(10, -10) == 10
    assert greatest_common_divisor(-10, -10) == 10

def test_large_prime_difference():
    assert greatest_common_divisor(1000003, 1000003 * 2) == 1000003
    assert greatest_common_divisor(1000003, 1000003 * 3) == 1000003