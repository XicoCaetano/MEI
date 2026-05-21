import pytest
from typing import List

# A função a testar é importada ou definida aqui para o contexto do teste
def filter_by_substring(strings: List[str], substring: str) -> List[str]:
    """ Filter an input list of strings only for ones that contain given substring """
    return [x for x in strings if substring in x]

def test_filter_by_substring_empty_list():
    """Garante que uma lista vazia retorna uma lista vazia."""
    assert filter_by_substring([], 'a') == []

def test_filter_by_substring_no_matches():
    """Garante que retorna lista vazia quando nenhuma string contém o padrão."""
    strings = ['abc', 'def', 'ghi']
    substring = 'z'
    assert filter_by_substring(strings, substring) == []

def test_filter_by_substring_all_matches():
    """Garante que retorna todos os elementos quando todos contêm o padrão."""
    strings = ['apple', 'apply', 'appetizer']
    substring = 'app'
    assert filter_by_substring(strings, substring) == ['apple', 'apply', 'appetizer']

def test_filter_by_substring_partial_matches():
    """Garante a filtragem correta baseada no exemplo do docstring."""
    strings = ['abc', 'bacd', 'cde', 'array']
    substring = 'a'
    expected = ['abc', 'bacd', 'array']
    assert filter_by_substring(strings, substring) == expected

def test_filter_by_substring_empty_substring():
    """Garante que uma substring vazia faz match com todas as strings (comportamento padrão do Python 'in')."""
    strings = ['a', 'b', 'c']
    substring = ''
    assert filter_by_substring(strings, substring) == ['a', 'b', 'c']

def test_filter_by_substring_case_sensitivity():
    """Garante que a função é case-sensitive."""
    strings = ['Apple', 'apple', 'APPLE']
    substring = 'app'
    assert filter_by_substring(strings, substring) == ['apple']

def test_filter_by_substring_special_characters():
    """Garante o funcionamento com caracteres especiais e espaços."""
    strings = ['hello world', 'world', 'python!']
    substring = ' '
    assert filter_by_substring(strings, substring) == ['hello world']

def test_filter_by_substring_exact_match():
    """Garante que strings idênticas à substring são incluídas."""
    strings = ['python', 'py', 'java']
    substring = 'python'
    assert filter_by_substring(strings, substring) == ['python']

def test_filter_by_substring_with_numeric_strings():
    """Garante o funcionamento com strings numéricas."""
    strings = ['123', '456', '234']
    substring = '23'
    assert filter_by_substring(strings, substring) == ['123', '234']