import pytest
from solution import string_sequence


def test_zero():
    assert string_sequence(0) == '0'

def test_five():
    assert string_sequence(5) == '0 1 2 3 4 5'

def test_one():
    assert string_sequence(1) == '0 1'

def test_large():
    result = string_sequence(100)
    parts = result.split(' ')
    assert len(parts) == 101
    assert parts[0] == '0'
    assert parts[-1] == '100'

def test_return_type():
    assert isinstance(string_sequence(3), str)

def test_space_delimited():
    result = string_sequence(4)
    assert result == '0 1 2 3 4'
    assert '  ' not in result

def test_starts_with_zero():
    for n in [1, 5, 10]:
        assert string_sequence(n).startswith('0')

def test_ends_with_n():
    for n in [1, 5, 10]:
        assert string_sequence(n).endswith(str(n))

def test_count_of_numbers():
    for n in [0, 3, 7]:
        parts = string_sequence(n).split(' ')
        assert len(parts) == n + 1

def test_sequential_values():
    result = string_sequence(10)
    parts = result.split(' ')
    for i, part in enumerate(parts):
        assert int(part) == i