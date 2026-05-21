import pytest
from typing import List

def factorize(n: int) -> List[int]:
    """ Return list of prime factors of given integer in the order from smallest to largest.
    Each of the factors should be listed number of times corresponding to how many times it appeares in factorization.
    Input number should be equal to the product of all factors
    """
    import math
    fact = []
    i = 2
    while i <= int(math.sqrt(n) + 1):
        if n % i == 0:
            fact.append(i)
            n //= i
        else:
            i += 1

    if n > 1:
        fact.append(n)
    return fact

@pytest.mark.parametrize("n, expected", [
    (2, [2]),
    (3, [3]),
    (4, [2, 2]),
    (8, [2, 2, 2]),
    (25, [5, 5]),
    (70, [2, 5, 7]),
    (57, [3, 19]),
    (324, [2, 2, 3, 3, 3, 3]),
    (997, [997]),  # Large prime
    (1001, [7, 11, 13]),
])
def test_factorize_valid_inputs(n, expected):
    """Tests standard cases including primes, powers, and composites."""
    assert factorize(n) == expected

def test_factorize_product_property():
    """Ensures the product of factors equals the original input."""
    import math
    n = 123456
    factors = factorize(n)
    product = 1
    for x in factors:
        product *= x
    assert product == n

def test_factorize_edge_case_two():
    """Specifically tests the smallest prime to ensure loop logic starts correctly."""
    assert factorize(2) == [2]

def test_factorize_one():
    """Tests the behavior with 1, which has no prime factors according to the logic."""
    # i <= sqrt(1)+1 (2) -> while 2 <= 2: if 1%2 == 0 (False) else i=3. Loop ends. n=1. 
    # Result is empty list.
    assert factorize(1) == []

def test_factorize_large_prime():
    """Ensures the 'if n > 1' logic is covered for primes where the loop ends early."""
    assert factorize(13) == [13]

def test_line_coverage_inner_while_branch():
    """Ensures the logic handles multiple divisions by the same factor."""
    # 12: i=2, 12%2==0, fact=[2], n=6; 6%2==0, fact=[2,2], n=3; 
    # 3%2!=0, i=3; Loop ends; n > 1, fact=[2,2,3]
    assert factorize(12) == [2, 2, 3]