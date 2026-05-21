import pytest
from typing import List, Optional

# A função é importada ou definida aqui para contexto do teste
def longest(strings: List[str]) -> Optional[str]:
    """ Out of list of strings, return the longest one. Return the first one in case of multiple
    strings of the same length. Return None in case the input list is empty.
    """
    if not strings:
        return None

    maxlen = max(len(x) for x in strings)
    for s in strings:
        if len(s) == maxlen:
            return s

def test_longest_empty_list():
    """Garante que retorna None para uma lista vazia."""
    assert longest([]) is None

def test_longest_single_element():
    """Garante que funciona com apenas um elemento."""
    assert longest(['a']) == 'a'

def test_longest_different_lengths():
    """Garante que encontra a string mais longa em comprimentos crescentes."""
    assert longest(['a', 'bb', 'ccc']) == 'ccc'

def test_longest_different_lengths_shuffled():
    """Garante que encontra a string mais longa independentemente da posição."""
    assert longest(['ccc', 'a', 'bb']) == 'ccc'

def test_longest_tie_break():
    """Garante que retorna a primeira ocorrência em caso de empate (requisito explícito)."""
    assert longest(['a', 'b', 'c']) == 'a'
    assert longest(['apple', 'berry', 'cherry']) == 'apple'

def test_longest_with_empty_strings():
    """Garante o comportamento correto com strings vazias dentro da lista."""
    assert longest(['', '']) == ''
    assert longest(['', 'a', '']) == 'a'

def test_longest_whitespace_strings():
    """Testa strings compostas por espaços em branco."""
    assert longest([' ', '  ', '   ']) == '   '

def test_longest_special_characters():
    """Testa strings com caracteres especiais e emojis."""
    assert longest(['short', 'longer_string', '🌟🌟🌟🌟🌟']) == 'longer_string'

def test_longest_very_large_list():
    """Teste de performance/escala simples."""
    input_list = ['a'] * 1000 + ['long_string'] + ['b'] * 1000
    assert longest(input_list) == 'long_string'