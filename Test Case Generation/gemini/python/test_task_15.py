import pytest

def string_sequence(n: int) -> str:
    """ Return a string containing space-delimited numbers starting from 0 upto n inclusive.
    >>> string_sequence(0)
    '0'
    >>> string_sequence(5)
    '0 1 2 3 4 5'
    """
    return ' '.join([str(x) for x in range(n + 1)])

def test_string_sequence_zero():
    """Test the base case with n=0."""
    assert string_sequence(0) == '0'

def test_string_sequence_positive_small():
    """Test with a small positive integer."""
    assert string_sequence(1) == '0 1'

def test_string_sequence_positive_large():
    """Test with a larger positive integer."""
    assert string_sequence(5) == '0 1 2 3 4 5'

def test_string_sequence_negative():
    """Test with a negative integer, which should return an empty string because range(0) is empty."""
    assert string_sequence(-1) == ''
    assert string_sequence(-10) == ''

def test_string_sequence_large_n():
    """Test with a relatively large n to ensure formatting remains consistent."""
    n = 10
    expected = "0 1 2 3 4 5 6 7 8 9 10"
    assert string_sequence(n) == expected

@pytest.mark.parametrize("n, expected", [
    (0, "0"),
    (2, "0 1 2"),
    (3, "0 1 2 3"),
])
def test_string_sequence_parametrized(n, expected):
    """Parametrized test for multiple standard cases."""
    assert string_sequence(n) == expected

def test_string_sequence_type_error():
    """Check behavior with invalid types (optional, based on Python's dynamic nature)."""
    with pytest.raises(TypeError):
        string_sequence("5") # type: ignore