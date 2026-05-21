import pytest
from typing import List

# A função é importada ou definida aqui para o contexto do teste
def has_close_elements(numbers: List[float], threshold: float) -> bool:
    for idx, elem in enumerate(numbers):
        for idx2, elem2 in enumerate(numbers):
            if idx != idx2:
                distance = abs(elem - elem2)
                if distance < threshold:
                    return True
    return False

def test_has_close_elements_empty_list():
    """Testa uma lista vazia, que deve retornar False."""
    assert has_close_elements([], 1.0) is False

def test_has_close_elements_single_element():
    """Testa uma lista com apenas um elemento, que deve retornar False."""
    assert has_close_elements([1.0], 1.0) is False

def test_has_close_elements_false_positive():
    """Testa casos onde os elementos estão fora do threshold."""
    assert has_close_elements([1.0, 2.0, 3.0], 0.5) is False
    assert has_close_elements([1.0, 2.0, 3.0], 0.99) is False

def test_has_close_elements_true_positive():
    """Testa casos onde existem elementos mais próximos que o threshold."""
    assert has_close_elements([1.0, 2.0, 2.4], 0.5) is True
    assert has_close_elements([1.0, 2.8, 3.0, 4.0, 5.0, 2.0], 0.3) is True

def test_has_close_elements_exact_threshold():
    """Testa o comportamento no limite exato do threshold (deve ser False pois usa <)."""
    assert has_close_elements([1.0, 2.0], 1.0) is False

def test_has_close_elements_negative_numbers():
    """Testa o comportamento com números negativos."""
    assert has_close_elements([-1.0, -1.2, -3.0], 0.3) is True
    assert has_close_elements([-1.0, -2.0, -3.0], 0.5) is False

def test_has_close_elements_mixed_numbers():
    """Testa a proximidade entre números positivos e negativos."""
    assert has_close_elements([-0.1, 0.1], 0.3) is True
    assert has_close_elements([-0.1, 0.1], 0.1) is False

def test_has_close_elements_duplicate_elements():
    """Testa se elementos idênticos acionam o threshold (distância 0)."""
    assert has_close_elements([1.0, 1.0], 0.01) is True

def test_has_close_elements_large_threshold():
    """Testa um threshold muito grande que abrange todos os elementos."""
    assert has_close_elements([1.0, 10.0, 100.0], 1000.0) is True

def test_has_close_elements_zero_threshold():
    """Testa threshold zero (nenhuma distância estrita < 0 é possível exceto se implementado diferente)."""
    assert has_close_elements([1.0, 2.0, 3.0], 0.0) is False
    assert has_close_elements([1.0, 1.0], 0.0) is False

def test_has_close_elements_floating_point_precision():
    """Testa precisão de ponto flutuante."""
    assert has_close_elements([1.0000001, 1.0000002], 0.00000015) is True