import pytest
from typing import List

# A função é importada ou definida aqui para o contexto dos testes
def rescale_to_unit(numbers: List[float]) -> List[float]:
    min_number = min(numbers)
    max_number = max(numbers)
    return [(x - min_number) / (max_number - min_number) for x in numbers]

def test_rescale_basic_sequence():
    """Testa uma sequência simples de números inteiros convertidos para float."""
    input_data = [1.0, 2.0, 3.0, 4.0, 5.0]
    expected = [0.0, 0.25, 0.5, 0.75, 1.0]
    assert rescale_to_unit(input_data) == expected

def test_rescale_two_elements():
    """Testa o caso mínimo de dois elementos conforme a docstring."""
    input_data = [10.0, 20.0]
    expected = [0.0, 1.0]
    assert rescale_to_unit(input_data) == expected

def test_rescale_negative_numbers():
    """Testa a lógica com números negativos."""
    input_data = [-10.0, 0.0, 10.0]
    expected = [0.0, 0.5, 1.0]
    assert rescale_to_unit(input_data) == expected

def test_rescale_unordered_list():
    """Garante que a função identifica corretamente o min e max em listas desordenadas."""
    input_data = [5.0, 1.0, 3.0, 2.0, 4.0]
    expected = [1.0, 0.0, 0.5, 0.25, 0.75]
    assert rescale_to_unit(input_data) == expected

def test_rescale_large_floats():
    """Testa precisão com valores decimais mais complexos."""
    input_data = [0.5, 1.5, 2.5]
    expected = [0.0, 0.5, 1.0]
    assert rescale_to_unit(input_data) == expected

def test_rescale_all_identical_elements_raises_zero_division():
    """
    Testa o edge case onde min == max (divisão por zero).
    Baseado na implementação fornecida, isto deve lançar ZeroDivisionError.
    """
    input_data = [2.0, 2.0, 2.0]
    with pytest.raises(ZeroDivisionError):
        rescale_to_unit(input_data)

def test_rescale_empty_list_raises_value_error():
    """Testa o comportamento com lista vazia (min/max falham)."""
    input_data = []
    with pytest.raises(ValueError):
        rescale_to_unit(input_data)

def test_rescale_single_element_raises_zero_division():
    """Testa o comportamento com apenas um elemento (min == max)."""
    input_data = [1.0]
    with pytest.raises(ZeroDivisionError):
        rescale_to_unit(input_data)

def test_rescale_extreme_values():
    """Testa com valores muito grandes para verificar estabilidade numérica básica."""
    input_data = [1e10, 2e10, 3e10]
    expected = [0.0, 0.5, 1.0]
    assert rescale_to_unit(input_data) == expected