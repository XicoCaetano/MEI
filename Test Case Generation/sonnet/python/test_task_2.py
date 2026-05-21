import pytest
from solution import truncate_number


def test_basic_example():
    assert truncate_number(3.5) == 0.5


def test_integer_returns_zero():
    assert truncate_number(1.0) == 0.0


def test_zero():
    assert truncate_number(0.0) == 0.0


def test_small_decimal():
    assert truncate_number(1.1) == pytest.approx(0.1)


def test_large_number():
    assert truncate_number(100.75) == pytest.approx(0.75)


def test_decimal_only():
    assert truncate_number(0.9) == pytest.approx(0.9)


def test_near_one():
    assert truncate_number(0.999) == pytest.approx(0.999)


def test_exact_half():
    assert truncate_number(2.5) == pytest.approx(0.5)


def test_large_integer():
    assert truncate_number(9999.0) == 0.0


def test_large_integer_with_decimal():
    assert truncate_number(9999.99) == pytest.approx(0.99)


def test_return_type_is_float():
    result = truncate_number(3.5)
    assert isinstance(result, float)


def test_result_always_less_than_one():
    for number in [1.1, 2.9, 100.5, 0.999, 50.01]:
        assert truncate_number(number) < 1.0


def test_result_always_non_negative():
    for number in [0.0, 1.0, 5.5, 100.25]:
        assert truncate_number(number) >= 0.0


def test_multiple_decimal_places():
    assert truncate_number(3.14159) == pytest.approx(0.14159)


def test_very_small_decimal():
    assert truncate_number(5.0001) == pytest.approx(0.0001)