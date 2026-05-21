import pytest
from typing import List
from below_zero import below_zero  # assuming the function is in below_zero.py

def test_empty_list_returns_false():
    """Test with empty list of operations."""
    assert below_zero([]) is False

def test_single_positive_operation_returns_false():
    """Test with single positive deposit."""
    assert below_zero([5]) is False

def test_single_zero_operation_returns_false():
    """Test with single zero operation."""
    assert below_zero([0]) is False

def test_single_negative_operation_returns_true():
    """Test with single negative withdrawal that makes balance negative."""
    assert below_zero([-1]) is True

def test_multiple_positive_operations_returns_false():
    """Test with operations that keep balance positive or zero."""
    assert below_zero([1, 2, 3]) is False
    assert below_zero([0, 0, 0]) is False
    assert below_zero([5, 10, 15]) is False

def test_balance_never_negative_returns_false():
    """Test with mix of deposits and withdrawals but balance never negative."""
    assert below_zero([10, -5, 3, -2, 1]) is False
    assert below_zero([100, -50, -30, 20]) is False

def test_balance_becomes_negative_mid_sequence_returns_true():
    """Test where balance becomes negative during operations."""
    assert below_zero([1, -2, 3]) is True  # 1 -> -1 (negative)
    assert below_zero([5, -10, 2]) is True  # 5 -> -5 (negative)
    assert below_zero([1, 2, -4, 5]) is True  # 1,3,-1 (negative)
    assert below_zero([-5, 10]) is True  # -5 (immediately negative)

def test_balance_negative_at_last_operation_returns_true():
    """Test where balance becomes negative only at the final operation."""
    assert below_zero([3, 2, -6]) is True  # 3,5,-1 (negative at end)
    assert below_zero([10, 5, -20]) is True  # 10,15,-5 (negative at end)

def test_balance_zero_after_operations_returns_false():
    """Test where balance hits zero but never negative."""
    assert below_zero([5, -5, 2, -2]) is False
    assert below_zero([10, -5, -5]) is False

def test_large_numbers_handled_correctly():
    """Test with large integer values."""
    assert below_zero([1000000, -500000, -600000]) is True
    assert below_zero([1000000, -500000, -499999]) is False
    assert below_zero([-9223372036854775808]) is True  # min int

def test_balance_becomes_negative_then_positive_returns_true():
    """Test where balance becomes negative, then recovers - should still return True."""
    assert below_zero([5, -10, 20]) is True  # Goes to -5 at second operation
    assert below_zero([1, -2, 1, 5]) is True  # Goes to -1 at second operation

def test_consecutive_withdrawals_cause_negative():
    """Test with multiple withdrawals in a row causing negative balance."""
    assert below_zero([10, -3, -4, -5]) is True  # 10,7,3,-2 (negative)
    assert below_zero([20, -5, -10, -6]) is True  # 20,15,5,-1 (negative)

def test_balance_remains_positive_zero_never_negative():
    """Test various scenarios where balance never falls below zero."""
    assert below_zero([0, 0, 0, 0]) is False
    assert below_zero([1, -1, 2, -2, 3, -3]) is False
    assert below_zero([100, -50, -30, -20]) is False
    assert below_zero([5, 5, -2, -3, -5]) is False  # 5,10,8,5,0

def test_single_element_zero_returns_false():
    """Test with single zero operation."""
    assert below_zero([0]) is False

def test_first_operation_causes_negative():
    """Test where the very first operation makes balance negative."""
    assert below_zero([-10, 20, 30]) is True
    assert below_zero([-1, 100]) is True