import pytest
from typing import Any

def truncate_number(number: float) -> float:
    """ Given a positive floating point number, it can be decomposed into
    and integer part (largest integer smaller than given number) and decimals
    (leftover part always smaller than 1).

    Return the decimal part of the number.
    >>> truncate_number(3.5)
    0.5
    """
    return number % 1.0

def test_truncate_number_standard_float():
    """Test standard positive floats with common decimal parts."""
    assert truncate_number(3.5) == pytest.approx(0.5)
    assert truncate_number(1.2) == pytest.approx(0.2)
    assert truncate_number(10.99) == pytest.approx(0.99)

def test_truncate_number_integer():
    """Test behavior with whole numbers (should return 0.0)."""
    assert truncate_number(1.0) == pytest.approx(0.0)
    assert truncate_number(100.0) == pytest.approx(0.0)
    assert truncate_number(0.0) == pytest.approx(0.0)

def test_truncate_number_less_than_one():
    """Test numbers that are already purely decimal."""
    assert truncate_number(0.5) == pytest.approx(0.5)
    assert truncate_number(0.00001) == pytest.approx(0.00001)

def test_truncate_number_large_float():
    """Test very large floating point numbers."""
    assert truncate_number(1234567.89) == pytest.approx(0.89)

def test_truncate_number_precision():
    """Test floating point arithmetic precision handling."""
    # 1.333 % 1.0 often results in 0.33299999999999996 due to binary representation
    assert truncate_number(1.333) == pytest.approx(0.333)

def test_truncate_number_negative():
    """
    Test negative numbers. 
    Note: Python's % operator returns a result with the same sign as the divisor (1.0).
    -0.5 % 1.0 is 0.5. While the docstring mentions positive floats, a senior engineer
    verifies behavior for out-of-contract inputs.
    """
    assert truncate_number(-0.5) == pytest.approx(0.5)
    assert truncate_number(-1.2) == pytest.approx(0.8)

def test_truncate_number_type_error():
    """Test with non-float/int inputs to ensure expected Python behavior."""
    with pytest.raises(TypeError):
        truncate_number("3.5") # type: ignore