import pytest
from typing import Any

def strlen(string: str) -> int:
    """ Return length of given string
    >>> strlen('')
    0
    >>> strlen('abc')
    3
    """
    return len(string)

class TestStrlen:
    """Suite de testes unitários exaustiva para a função strlen."""

    def test_empty_string(self):
        """Garante que uma string vazia retorna comprimento 0."""
        assert strlen("") == 0

    def test_single_character(self):
        """Garante que um único caráter retorna comprimento 1."""
        assert strlen("a") == 1
        assert strlen(" ") == 1
        assert strlen("\n") == 1

    def test_regular_string(self):
        """Garante que strings comuns retornam o comprimento correto."""
        assert strlen("abc") == 3
        assert strlen("software quality") == 16

    def test_unicode_and_emojis(self):
        """Garante o suporte correto a carateres Unicode e Emojis."""
        assert strlen("🚀") == 1
        assert strlen("café") == 4
        assert strlen("你好") == 2

    def test_long_string(self):
        """Garante a performance e exatidão com strings de grande dimensão."""
        size = 10**6
        assert strlen("a" * size) == size

    def test_numeric_string(self):
        """Garante que strings compostas por números são processadas corretamente."""
        assert strlen("12345") == 5

    @pytest.mark.parametrize("invalid_input", [
        None,
        123,
        ["a", "b"],
        {"key": "val"},
        1.5
    ])
    def test_invalid_types(self, invalid_input: Any):
        """
        Verifica o comportamento perante tipos de dados inválidos.
        Como a função usa len(), deve lançar TypeError.
        """
        with pytest.raises(TypeError):
            strlen(invalid_input)