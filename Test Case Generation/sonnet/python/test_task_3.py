import pytest
from typing import List
from solution import below_zero


def test_all_positive_operations():
    assert below_zero([1, 2, 3]) == False


def test_goes_below_zero():
    assert below_zero([1, 2, -4, 5]) == True


def test_empty_list():
    assert below_zero([]) == False


def test_single_positive():
    assert below_zero([10]) == False


def test_single_negative():
    assert below_zero([-1]) == True


def test_single_zero():
    assert below_zero([0]) == False


def test_balance_exactly_zero_never_negative():
    assert below_zero([5, -5, 3, -3]) == False


def test_balance_reaches_zero_then_negative():
    assert below_zero([5, -5, -1]) == True


def test_first_operation_negative():
    assert below_zero([-1, 10, 20]) == True


def test_last_operation_causes_negative():
    assert below_zero([10, 5, -20]) == True


def test_large_deposit_then_withdrawals():
    assert below_zero([100, -50, -30, -10]) == False


def test_large_deposit_then_overdraft():
    assert below_zero([100, -50, -30, -25]) == True


def test_all_zeros():
    assert below_zero([0, 0, 0, 0]) == False


def test_all_negative():
    assert below_zero([-1, -2, -3]) == True


def test_alternating_operations_no_negative():
    assert below_zero([5, -3, 4, -2, 1]) == False


def test_alternating_operations_goes_negative():
    assert below_zero([3, -5, 4, -2]) == True


def test_recovers_after_going_negative():
    assert below_zero([5, -10, 20]) == True


def test_large_numbers_no_negative():
    assert below_zero([1000000, -999999, 500000]) == False


def test_large_numbers_goes_negative():
    assert below_zero([1000000, -1000001]) == True


def test_returns_true_on_first_negative_not_last():
    assert below_zero([10, -20, 100]) == True


def test_multiple_zeros_then_negative():
    assert below_zero([0, 0, 0, -1]) == True


def test_cumulative_small_withdrawals():
    assert below_zero([3, -1, -1, -1, -1]) == True


def test_cumulative_small_withdrawals_no_negative():
    assert below_zero([4, -1, -1, -1, -1]) == False


def test_exact_balance_boundary():
    assert below_zero([10, -10]) == False


def test_one_over_boundary():
    assert below_zero([10, -11]) == True