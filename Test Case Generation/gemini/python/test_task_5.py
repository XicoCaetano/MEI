import pytest
from typing import List

# Assumindo que a função está no mesmo ficheiro ou importada corretamente
# from modulo_original import intersperse

def intersperse(numbers: List[int], delimeter: int) -> List[int]:
    """ Insert a number 'delimeter' between every two consecutive elements of input list `numbers'
    >>> intersperse([], 4)
    []
    >>> intersperse([1, 2, 3], 4)
    [1, 4, 2, 4, 3]
    """
    if not numbers:
        return []

    result = []

    for n in numbers[:-1]:
        result.append(n)
        result.append(delimeter)

    result.append(numbers[-1])

    return result

@pytest.mark.parametrize("numbers, delimeter, expected", [
    # Teste de lista vazia (Edge Case: Input vazio)
    ([], 4, []),
    # Teste com apenas um elemento (Edge Case: Sem pares para intercalar)
    ([1], 4, [1]),
    # Teste com dois elementos
    ([1, 2], 4, [1, 4, 2]),
    # Teste padrão do docstring
    ([1, 2, 3], 4, [1, 4, 2, 4, 3]),
    # Teste com números negativos
    ([-1, -2], -3, [-1, -3, -2]),
    # Teste com zeros
    ([0, 0, 0], 0, [0, 0, 0, 0, 0]),
    # Teste com lista grande
    (list(range(5)), 99, [0, 99, 1, 99, 2, 99, 3, 99, 4]),
    # Teste com delimitador sendo o mesmo que os números
    ([1, 1, 1], 1, [1, 1, 1, 1, 1]),
])
def test_intersperse_scenarios(numbers: List[int], delimeter: int, expected: List[int]):
    """Valida múltiplos cenários para garantir 100% de cobertura de linha e lógica."""
    assert intersperse(numbers, delimeter) == expected

def test_intersperse_immutability():
    """Garante que a lista original não é modificada (Side effect check)."""
    original = [1, 2, 3]
    copy_original = original.copy()
    intersperse(original, 4)
    assert original == copy_original

def test_intersperse_with_large_integers():
    """Teste com inteiros de grande magnitude."""
    assert intersperse([10**18, 10**18], 1) == [10**18, 1, 10**18]