import pytest
from largest_divisor import largest_divisor


def test_largest_divisor_15():
    assert largest_divisor(15) == 5


def test_largest_divisor_prime_7():
    assert largest_divisor(7) == 1


def test_largest_divisor_prime_13():
    assert largest_divisor(13) == 1


def test_largest_divisor_even_number():
    assert largest_divisor(10) == 5


def test_largest_divisor_power_of_two():
    assert largest_divisor(8) == 4


def test_largest_divisor_4():
    assert largest_divisor(4) == 2


def test_largest_divisor_6():
    assert largest_divisor(6) == 3


def test_largest_divisor_9():
    assert largest_divisor(9) == 3


def test_largest_divisor_12():
    assert largest_divisor(12) == 6


def test_largest_divisor_100():
    assert largest_divisor(100) == 50


def test_largest_divisor_large_prime():
    assert largest_divisor(97) == 1


def test_largest_divisor_large_composite():
    assert largest_divisor(1000) == 500


def test_largest_divisor_2():
    assert largest_divisor(2) == 1


def test_largest_divisor_3():
    assert largest_divisor(3) == 1


def test_largest_divisor_perfect_square():
    assert largest_divisor(36) == 18


def test_largest_divisor_returns_int():
    result = largest_divisor(15)
    assert isinstance(result, int)


def test_largest_divisor_result_less_than_n():
    n = 20
    result = largest_divisor(n)
    assert result < n


def test_largest_divisor_result_divides_n():
    n = 28
    result = largest_divisor(n)
    assert n % result == 0


def test_largest_divisor_composite_odd():
    assert largest_divisor(21) == 7


def test_largest_divisor_highly_composite():
    assert largest_divisor(24) == 12


def test_largest_divisor_large_even():
    assert largest_divisor(10000) == 5000