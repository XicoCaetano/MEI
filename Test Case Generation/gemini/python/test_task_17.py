import pytest
from typing import List

# A função a ser testada (incluída para garantir que os testes correm autonomamente)
def parse_music(music_string: str) -> List[int]:
    note_map = {'o': 4, 'o|': 2, '.|': 1}
    return [note_map[x] for x in music_string.split(' ') if x]

def test_parse_music_basic_example():
    """Testa o exemplo fornecido no docstring."""
    input_str = 'o o| .| o| o| .| .| .| .| o o'
    expected = [4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4]
    assert parse_music(input_str) == expected

def test_parse_music_empty_string():
    """Testa uma string vazia, que deve retornar uma lista vazia."""
    assert parse_music('') == []

def test_parse_music_single_notes():
    """Testa cada nota individualmente."""
    assert parse_music('o') == [4]
    assert parse_music('o|') == [2]
    assert parse_music('.|') == [1]

def test_parse_music_multiple_spaces():
    """Testa o comportamento com espaços extras (deve ignorar devido ao 'if x')."""
    input_str = 'o  o|   .|'
    expected = [4, 2, 1]
    assert parse_music(input_str) == expected

def test_parse_music_leading_trailing_spaces():
    """Testa espaços no início e no fim da string."""
    assert parse_music(' o ') == [4]
    assert parse_music('  o| .|  ') == [2, 1]

def test_parse_music_all_same_notes():
    """Testa uma sequência da mesma nota."""
    assert parse_music('o o o') == [4, 4, 4]
    assert parse_music('.| .| .| .|') == [1, 1, 1, 1]

def test_parse_music_invalid_note():
    """Testa o comportamento ao encontrar uma nota inválida (deve lançar KeyError)."""
    with pytest.raises(KeyError):
        parse_music('o x| .|')

def test_parse_music_invalid_format_no_spaces():
    """Testa notas coladas sem espaços (deve lançar KeyError pois 'oo|' não existe no mapa)."""
    with pytest.raises(KeyError):
        parse_music('oo|')

def test_parse_music_newline_tabs():
    """Testa se outros caracteres de whitespace (não espaços) causam erro ou comportamento inesperado."""
    # Como o split é explicitamente por ' ', um \n resultaria em uma chave inválida 'o\no'
    input_with_newline = 'o\no'
    with pytest.raises(KeyError):
        parse_music(input_with_newline)