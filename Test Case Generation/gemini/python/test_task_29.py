import pytest
from typing import List

# A função é importada ou definida localmente para garantir a execução dos testes
def filter_by_prefix(strings: List[str], prefix: str) -> List[str]:
    """ Filter an input list of strings only for ones that start with a given prefix. """
    return [x for x in strings if x.startswith(prefix)]

def test_filter_by_prefix_empty_list():
    """Garante que uma lista vazia retorna uma lista vazia."""
    assert filter_by_prefix([], 'a') == []

def test_filter_by_prefix_no_matches():
    """Garante que retorna lista vazia se nenhum elemento coincidir com o prefixo."""
    assert filter_by_prefix(['bcd', 'cde', 'fgh'], 'a') == []

def test_filter_by_prefix_multiple_matches():
    """Garante que filtra múltiplos elementos corretamente conforme o docstring."""
    assert filter_by_prefix(['abc', 'bcd', 'cde', 'array'], 'a') == ['abc', 'array']

def test_filter_by_prefix_exact_match():
    """Garante que strings que são exatamente iguais ao prefixo são incluídas."""
    assert filter_by_prefix(['apple', 'a', 'banana'], 'a') == ['apple', 'a']

def test_filter_by_prefix_case_sensitivity():
    """Garante que a função é case-sensitive (comportamento padrão do startswith)."""
    assert filter_by_prefix(['Apple', 'apple', 'APple'], 'Ap') == ['Apple']
    assert filter_by_prefix(['apple'], 'A') == []

def test_filter_by_prefix_empty_prefix():
    """
    Garante que um prefixo vazio retorna todos os elementos da lista,
    visto que qualquer string começa com "".
    """
    input_list = ['abc', 'def', 'ghi']
    assert filter_by_prefix(input_list, '') == input_list

def test_filter_by_prefix_special_characters():
    """Garante que funciona com caracteres especiais e espaços."""
    assert filter_by_prefix([' hello', 'world', ' he'], ' ') == [' hello', ' he']
    assert filter_by_prefix(['$100', '€200', '$50'], '$') == ['$100', '$50']

def test_filter_by_prefix_unicode():
    """Garante suporte a caracteres Unicode."""
    assert filter_by_prefix(['Olá', 'Olé', 'Oi'], 'Ol') == ['Olá', 'Olé']

def test_filter_by_prefix_all_match():
    """Garante que funciona quando todos os itens da lista satisfazem a condição."""
    assert filter_by_prefix(['test1', 'test2', 'test3'], 'test') == ['test1', 'test2', 'test3']

def test_filter_by_prefix_type_error():
    """Verifica comportamento com tipos inesperados para garantir robustez (opcional)."""
    with pytest.raises(TypeError):
        filter_by_prefix([123, 'abc'], 'a')