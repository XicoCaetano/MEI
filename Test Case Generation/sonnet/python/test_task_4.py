import pytest
from typing import List
from solution import mean_absolute_deviation


def test_docstring_example():
    assert mean_absolute_deviation([1.0, 2.0, 3.0, 4.0]) == 1.0


def test_single_element():
    assert mean_absolute_deviation([5.0]) == 0.0


def test_two_elements():
    result = mean_absolute_deviation([1.0, 3.0])
    assert result == pytest.approx(1.0)


def test_all_same_elements():
    assert mean_absolute_deviation([7.0, 7.0, 7.0, 7.0]) == 0.0


def test_negative_numbers():
    result = mean_absolute_deviation([-1.0, -2.0, -3.0, -4.0])
    assert result == pytest.approx(1.0)


def test_mixed_positive_negative():
    result = mean_absolute_deviation([-2.0, -1.0, 1.0, 2.0])
    assert result == pytest.approx(1.5)


def test_zeros():
    assert mean_absolute_deviation([0.0, 0.0, 0.0]) == 0.0


def test_mixed_with_zero():
    result = mean_absolute_deviation([-1.0, 0.0, 1.0])
    assert result == pytest.approx(2/3)


def test_large_values():
    result = mean_absolute_deviation([1000.0, 2000.0, 3000.0])
    assert result == pytest.approx(666.6666666666666)


def test_floats_precision():
    result = mean_absolute_deviation([0.1, 0.2, 0.3])
    assert result == pytest.approx(0.08888888888888889, rel=1e-6)


def test_integers_as_floats():
    result = mean_absolute_deviation([1, 2, 3, 4, 5])
    assert result == pytest.approx(1.2)


def test_symmetrical_distribution():
    result = mean_absolute_deviation([1.0, 2.0, 3.0, 4.0, 5.0])
    assert result == pytest.approx(1.2)


def test_returns_float():
    result = mean_absolute_deviation([1.0, 2.0, 3.0])
    assert isinstance(result, float)


def test_empty_list_raises():
    with pytest.raises((ZeroDivisionError, ValueError)):
        mean_absolute_deviation([])


def test_large_dataset():
    numbers = list(range(1, 101))
    result = mean_absolute_deviation(numbers)
    assert result == pytest.approx(25.0)


def test_single_negative():
    assert mean_absolute_deviation([-42.0]) == 0.0


def test_non_uniform_distribution():
    result = mean_absolute_deviation([1.0, 1.0, 1.0, 100.0])
    mean = (1 + 1 + 1 + 100) / 4
    expected = (abs(1 - mean) * 3 + abs(100 - mean)) / 4
    assert result == pytest.approx(expected)


def test_very_small_floats():
    result = mean_absolute_deviation([1e-10, 2e-10, 3e-10])
    assert result == pytest.approx(6.666666666666667e-11, rel=1e-6)


def test_two_element_symmetry():
    result = mean_absolute_deviation([0.0, 10.0])
    assert result == pytest.approx(5.0)