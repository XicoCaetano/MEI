import pytest

def greatest_common_divisor(a: int, b: int) -> int:
    """ Return a greatest common divisor of two integers a and b
    >>> greatest_common_divisor(3, 5)
    1
    >>> greatest_common_divisor(25, 15)
    5
    """
    while b:
        a, b = b, a % b
    return a

@pytest.mark.parametrize("a, b, expected", [
    # Casos base fornecidos na docstring
    (3, 5, 1),
    (25, 15, 5),
    # Casos com números primos
    (13, 17, 1),
    (7, 49, 7),
    # Casos onde um número é múltiplo do outro
    (10, 20, 10),
    (100, 10, 10),
    # Casos com o número 1
    (1, 5, 1),
    (10, 1, 1),
    # Casos com Zero (Edge cases)
    (0, 5, 5),
    (5, 0, 5),
    (0, 0, 0),
    # Números grandes
    (10**9, 10**6, 10**6),
    (123456, 789012, 12),
    # Números negativos (O comportamento do operador % em Python garante a execução)
    (-25, 15, 5),
    (25, -15, -5),
    (-25, -15, -5),
])
def test_greatest_common_divisor_scenarios(a, b, expected):
    """Testa múltiplos cenários para garantir correção e cobertura."""
    assert greatest_common_divisor(a, b) == expected

def test_gcd_identity():
    """Testa a propriedade de identidade (GCD de um número com ele próprio)."""
    assert greatest_common_divisor(42, 42) == 42

def test_gcd_is_commutative():
    """Testa se a ordem dos argumentos não altera o resultado."""
    assert greatest_common_divisor(18, 12) == greatest_common_divisor(12, 18)

def test_gcd_with_primes():
    """Testa explicitamente com números primos grandes."""
    assert greatest_common_divisor(7919, 7907) == 1