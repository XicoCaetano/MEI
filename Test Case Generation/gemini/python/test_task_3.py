import pytest
from typing import List

# Importação assumindo que a função está no mesmo ficheiro ou acessível via namespace
# Caso esteja num ficheiro separado, usar: from main import below_zero

def below_zero(operations: List[int]) -> bool:
    """ You're given a list of deposit and withdrawal operations on a bank account that starts with
    zero balance. Your task is to detect if at any point the balance of account fallls below zero, and
    at that point function should return True. Otherwise it should return False.
    """
    balance = 0

    for op in operations:
        balance += op
        if balance < 0:
            return True

    return False

def test_below_zero_empty_list():
    """Garante que uma lista vazia retorna False (o saldo nunca fica < 0)."""
    assert below_zero([]) is False

def test_below_zero_all_positive():
    """Garante que depósitos sucessivos não acionam o True."""
    assert below_zero([1, 2, 3, 10, 100]) is False

def test_below_zero_reaches_zero_exactly():
    """Garante que chegar a zero exato (limite) não retorna True."""
    assert below_zero([10, -10]) is False
    assert below_zero([5, -2, -3]) is False

def test_below_zero_drops_below_immediately():
    """Garante que uma primeira operação negativa ativa o retorno imediato."""
    assert below_zero([-1]) is True
    assert below_zero([-100, 50]) is True

def test_below_zero_drops_below_at_end():
    """Garante que deteta quando o saldo fica negativo no último movimento."""
    assert below_zero([10, 20, -31]) is True

def test_below_zero_drops_below_in_middle():
    """Garante que deteta saldo negativo a meio e ignora operações posteriores."""
    # O saldo fica -1, depois voltaria a positivo, mas deve parar no -1
    assert below_zero([10, -11, 20]) is True

def test_below_zero_large_values():
    """Testa com valores elevados para garantir integridade básica."""
    assert below_zero([1000000, -1000001]) is True
    assert below_zero([1000000, -999999]) is False

@pytest.mark.parametrize("operations, expected", [
    ([1, 2, 3], False),
    ([1, 2, -4, 5], True),
    ([0, 0, 0], False),
    ([-0.5], True), # Python lida com floats na soma se passados, embora a tipagem sugira int
])
def test_below_zero_parametrized(operations, expected):
    """Testes rápidos baseados nos exemplos da docstring e casos simples."""
    assert below_zero(operations) == expected