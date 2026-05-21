import pytest
from typing import List
from solution import factorize


def test_factorize_8():
    assert factorize(8) == [2, 2, 2]


def test_factorize_25():
    assert factorize(25) == [5, 5]


def test_factorize_70():
    assert factorize(70) == [2, 5, 7]


def test_factorize_prime_2():
    assert factorize(2) == [2]


def test_factorize_prime_3():
    assert factorize(3) == [3]


def test_factorize_prime_7():
    assert factorize(7) == [7]


def test_factorize_prime_13():
    assert factorize(13) == [13]


def test_factorize_prime_97():
    assert factorize(97) == [97]


def test_factorize_prime_large():
    assert factorize(9973) == [9973]


def test_factorize_4():
    assert factorize(4) == [2, 2]


def test_factorize_9():
    assert factorize(9) == [3, 3]


def test_factorize_16():
    assert factorize(16) == [2, 2, 2, 2]


def test_factorize_27():
    assert factorize(27) == [3, 3, 3]


def test_factorize_32():
    assert factorize(32) == [2, 2, 2, 2, 2]


def test_factorize_36():
    assert factorize(36) == [2, 2, 3, 3]


def test_factorize_100():
    assert factorize(100) == [2, 2, 5, 5]


def test_factorize_12():
    assert factorize(12) == [2, 2, 3]


def test_factorize_18():
    assert factorize(18) == [2, 3, 3]


def test_factorize_30():
    assert factorize(30) == [2, 3, 5]


def test_factorize_42():
    assert factorize(42) == [2, 3, 7]


def test_factorize_60():
    assert factorize(60) == [2, 2, 3, 5]


def test_factorize_210():
    assert factorize(210) == [2, 3, 5, 7]


def test_factorize_2310():
    assert factorize(2310) == [2, 3, 5, 7, 11]


def test_factorize_product_equals_n():
    for n in [8, 25, 70, 12, 100, 360, 1024]:
        factors = factorize(n)
        product = 1
        for f in factors:
            product *= f
        assert product == n, f"Product of factors {factors} != {n}"


def test_factorize_factors_sorted():
    for n in [8, 25, 70, 12, 100, 360, 2310]:
        factors = factorize(n)
        assert factors == sorted(factors), f"Factors {factors} are not sorted for n={n}"


def test_factorize_all_factors_prime():
    def is_prime(num):
        if num < 2:
            return False
        for j in range(2, int(num**0.5) + 1):
            if num % j == 0:
                return False
        return True

    for n in [8, 25, 70, 12, 100, 360, 2310, 9973]:
        factors = factorize(n)
        for f in factors:
            assert is_prime(f), f"Factor {f} is not prime in factorization of {n}"


def test_factorize_1():
    result = factorize(1)
    assert result == []


def test_factorize_large_prime_product():
    assert factorize(77) == [7, 11]


def test_factorize_semiprime():
    assert factorize(91) == [7, 13]


def test_factorize_perfect_square_prime():
    assert factorize(49) == [7, 7]


def test_factorize_large_number():
    result = factorize(1000000)
    assert result == [2, 2, 2, 2, 2, 2, 5, 5, 5, 5, 5, 5]
    product = 1
    for f in result:
        product *= f
    assert product == 1000000


def test_factorize_360():
    assert factorize(360) == [2, 2, 2, 3, 3, 5]


def test_factorize_1024():
    assert factorize(1024) == [2] * 10


def test_factorize_returns_list():
    result = factorize(12)
    assert isinstance(result, list)


def test_factorize_elements_are_integers():
    result = factorize(70)
    for factor in result:
        assert isinstance(factor, int)


def test_factorize_consecutive_same_prime():
    assert factorize(2**10) == [2] * 10
    assert factorize(3**5) == [3] * 5


def test_factorize_two_large_primes():
    assert factorize(143) == [11, 13]


def test_factorize_multiplicity_preserved():
    factors = factorize(72)
    assert factors.count(2) == 3
    assert factors.count(3) == 2
    assert factors == [2, 2, 2, 3, 3]