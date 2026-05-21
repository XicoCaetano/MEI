import pytest
from typing import List

# A função é importada ou definida aqui para o contexto do teste
def remove_duplicates(numbers: List[int]) -> List[int]:
    """ From a list of integers, remove all elements that occur more than once.
    Keep order of elements left the same as in the input.
    >>> remove_duplicates([1, 2, 3, 2, 4])
    [1, 3, 4]
    """
    import collections
    c = collections.Counter(numbers)
    return [n for n in numbers if c[n] <= 1]

def test_remove_duplicates_standard_case():
    """Testa o exemplo básico fornecido na docstring."""
    assert remove_duplicates([1, 2, 3, 2, 4]) == [1, 3, 4]

def test_remove_duplicates_empty_list():
    """Testa o comportamento com uma lista vazia (edge case)."""
    assert remove_duplicates([]) == []

def test_remove_duplicates_no_duplicates():
    """Testa uma lista onde todos os elementos são únicos."""
    assert remove_duplicates([1, 2, 3, 4, 5]) == [1, 2, 3, 4, 5]

def test_remove_duplicates_all_duplicates():
    """Testa uma lista onde todos os elementos ocorrem mais de uma vez."""
    assert remove_duplicates([1, 1, 2, 2, 3, 3]) == []

def test_remove_duplicates_single_element():
    """Testa uma lista com apenas um elemento."""
    assert remove_duplicates([10]) == [10]

def test_remove_duplicates_negative_numbers():
    """Testa a função com números negativos."""
    assert remove_duplicates([-1, -2, -1, -3, 4]) == [-2, -3, 4]

def test_remove_duplicates_large_counts():
    """Testa elementos que aparecem muitas vezes."""
    assert remove_duplicates([1, 1, 1, 1, 1, 2]) == [2]

def test_remove_duplicates_order_preservation():
    """Garante que a ordem original dos elementos não duplicados é mantida."""
    assert remove_duplicates([5, 1, 9, 1, 3]) == [5, 9, 3]

def test_remove_duplicates_zeros():
    """Testa o comportamento com zeros, garantindo tratamento correto de falsy values."""
    assert remove_duplicates([0, 1, 0, 2]) == [1, 2]

@pytest.mark.parametrize("input_list, expected", [
    ([1, 2, 2, 3], [1, 3]),
    ([7, 8, 9], [7, 8, 9]),
    ([1, 1, 1], []),
    ([100, 200, 100, 300], [200, 300]),
])
def test_remove_duplicates_parametrized(input_list, expected):
    """Testes parametrizados para cobrir múltiplos cenários rapidamente."""
    assert remove_duplicates(input_list) == expected