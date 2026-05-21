import pytest
from typing import List, Any

# A função a ser testada (assumindo que está no mesmo ficheiro ou importada corretamente)
def filter_integers(values: List[Any]) -> List[int]:
    """ Filter given list of any python values only for integers """
    return [x for x in values if isinstance(x, int)]

def test_filter_integers_basic():
    """Testa filtragem básica com tipos mistos."""
    input_data = [1, 'a', 2, 3.14, 5, True, False]
    # Nota: Em Python, bool é subclasse de int, por isso True/False são mantidos.
    # Se o requisito fosse estritamente int e não bool, a função precisaria de type(x) is int.
    # Com base no código fornecido (isinstance), True e False passam.
    assert filter_integers(input_data) == [1, 2, 5, True, False]

def test_filter_integers_only_integers():
    """Testa uma lista que contém apenas inteiros."""
    input_data = [10, 20, 30, -5, 0]
    assert filter_integers(input_data) == [10, 20, 30, -5, 0]

def test_filter_integers_no_integers():
    """Testa uma lista que não contém nenhum inteiro."""
    input_data = ['abc', 1.1, [1, 2], {'key': 'val'}, None]
    assert filter_integers(input_data) == []

def test_filter_integers_empty_list():
    """Testa o comportamento com uma lista vazia."""
    assert filter_integers([]) == []

def test_filter_integers_large_integers():
    """Testa inteiros de grande dimensão."""
    large_val = 10**18
    assert filter_integers([large_val, "test"]) == [large_val]

def test_filter_integers_complex_structures():
    """Testa estruturas complexas e objetos."""
    class Sample:
        pass
    
    input_data = [Sample(), (1, 2), {1, 2, 3}, 42]
    assert filter_integers(input_data) == [42]

def test_filter_integers_docstring_examples():
    """Garante que os exemplos fornecidos na docstring funcionam como esperado."""
    assert filter_integers(['a', 3.14, 5]) == [5]
    assert filter_integers([1, 2, 3, 'abc', {}, []]) == [1, 2, 3]

@pytest.mark.parametrize("input_val, expected", [
    ([1, 2.0, "3"], [1]),
    (["apple", "banana"], []),
    ([0, -1, 1], [0, -1, 1]),
    ([0x10, 0b10], [16, 2]), # Hexadecimal e Binário
])
def test_filter_integers_parametrized(input_val, expected):
    """Testes parametrizados para cobrir múltiplos cenários rapidamente."""
    assert filter_integers(input_val) == expected