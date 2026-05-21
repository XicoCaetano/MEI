import pytest
from solution import greatest_common_divisor


def test_coprime_numbers():
    assert greatest_common_divisor(3, 5) == 1


def test_common_divisor_5():
    assert greatest_common_divisor(25, 15) == 5


def test_one_is_multiple_of_other():
    assert greatest_common_divisor(12, 4) == 4


def test_same_numbers():
    assert greatest_common_divisor(7, 7) == 7


def test_b_is_zero():
    assert greatest_common_divisor(9, 0) == 9


def test_a_is_zero():
    assert greatest_common_divisor(0, 5) == 5


def test_both_zero():
    assert greatest_common_divisor(0, 0) == 0


def test_large_numbers():
    assert greatest_common_divisor(1000000, 500000) == 500000


def test_large_coprime_numbers():
    assert greatest_common_divisor(999983, 999979) == 1


def test_a_equals_one():
    assert greatest_common_divisor(1, 100) == 1


def test_b_equals_one():
    assert greatest_common_divisor(100, 1) == 1


def test_negative_a():
    assert greatest_common_divisor(-12, 4) == 4


def test_negative_b():
    assert greatest_common_divisor(12, -4) == -4


def test_both_negative():
    assert greatest_common_divisor(-12, -4) == -4


def test_a_less_than_b():
    assert greatest_common_divisor(4, 16) == 4


def test_fibonacci_consecutive():
    assert greatest_common_divisor(55, 34) == 1


def test_power_of_two():
    assert greatest_common_divisor(64, 32) == 32


def test_prime_numbers():
    assert greatest_common_divisor(13, 17) == 1


def test_gcd_is_a():
    assert greatest_common_divisor(6, 18) == 6