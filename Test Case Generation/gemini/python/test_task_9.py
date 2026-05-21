import pytest
from typing import List

# Importação da função a testar (assumindo que o ficheiro se chama solution.py)
# Caso o código esteja no mesmo ficheiro para o teste, pode-se omitir o import.
# from solution import rolling_max

def rolling_max(numbers: List[int]) -> List[int]:
    """ From a given list of integers, generate a list of rolling maximum element found until given moment
    in the sequence.
    >>> rolling_max([1, 2, 3, 2, 3, 4, 2])
    [1, 2, 3, 3, 3, 4, 4]
    """
    running_max = None
    result = []

    for n in numbers:
        if running_max is None:
            running_max = n
        else:
            running_max = max(running_max, n)

        result.append(running_max)

    return result

def test_rolling_max_empty_list():
    """Garante que uma lista vazia retorna uma lista vazia (Edge Case)."""
    assert rolling_max([]) == []

def test_rolling_max_single_element():
    """Garante o comportamento correto com apenas um elemento."""
    assert rolling_max([5]) == [5]

def test_rolling_max_increasing_sequence():
    """Garante o cálculo correto numa sequência estritamente crescente."""
    assert rolling_max([1, 5, 10, 15]) == [1, 5, 10, 15]

def test_rolling_max_decreasing_sequence():
    """Garante que o primeiro elemento se mantém como máximo se for o maior (Edge Case)."""
    assert rolling_max([20, 15, 10, 5]) == [20, 20, 20, 20]

def test_rolling_max_mixed_sequence():
    """Testa o exemplo fornecido na docstring e variações de flutuação."""
    assert rolling_max([1, 2, 3, 2, 3, 4, 2]) == [1, 2, 3, 3, 3, 4, 4]

def test_rolling_max_duplicate_elements():
    """Verifica o comportamento com valores duplicados."""
    assert rolling_max([7, 7, 8, 8, 7]) == [7, 7, 8, 8, 8]

def test_rolling_max_negative_numbers():
    """Garante que a lógica funciona corretamente com inteiros negativos (Edge Case)."""
    assert rolling_max([-5, -2, -10, -1]) == [-5, -2, -2, -1]

def test_rolling_max_large_integers():
    """Verifica a estabilidade com números de grande magnitude."""
    assert rolling_max([10**10, 10**2, 10**11]) == [10000000000, 10000000000, 100000000000]

def test_rolling_max_with_zero():
    """Verifica a inclusão do zero na sequência."""
    assert rolling_max([0, -1, 1, 0]) == [0, 0, 1, 1]