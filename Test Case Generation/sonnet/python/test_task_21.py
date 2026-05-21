import pytest
from typing import List
from solution import rescale_to_unit


def test_basic_example():
    result = rescale_to_unit([1.0, 2.0, 3.0, 4.0, 5.0])
    assert result == [0.0, 0.25, 0.5, 0.75, 1.0]


def test_two_elements():
    result = rescale_to_unit([0.0, 1.0])
    assert result == [0.0, 1.0]


def test_two_elements_arbitrary():
    result = rescale_to_unit([3.0, 7.0])
    assert result == [0.0, 1.0]


def test_negative_numbers():
    result = rescale_to_unit([-5.0, -3.0, -1.0])
    assert result == [0.0, 0.5, 1.0]


def test_mixed_negative_positive():
    result = rescale_to_unit([-1.0, 0.0, 1.0])
    assert result == [0.0, 0.5, 1.0]


def test_large_range():
    result = rescale_to_unit([0.0, 50.0, 100.0])
    assert result == [0.0, 0.5, 1.0]


def test_floats_precision():
    result = rescale_to_unit([1.5, 2.5, 3.5])
    assert pytest.approx(result) == [0.0, 0.5, 1.0]


def test_unsorted_input():
    result = rescale_to_unit([5.0, 1.0, 3.0])
    assert pytest.approx(result) == [1.0, 0.0, 0.5]


def test_min_is_zero_max_is_one():
    result = rescale_to_unit([0.0, 0.5, 1.0])
    assert result == [0.0, 0.5, 1.0]


def test_all_large_values():
    result = rescale_to_unit([1000.0, 2000.0, 3000.0])
    assert pytest.approx(result) == [0.0, 0.5, 1.0]


def test_all_small_values():
    result = rescale_to_unit([0.001, 0.002, 0.003])
    assert pytest.approx(result) == [0.0, 0.5, 1.0]


def test_first_element_becomes_zero():
    result = rescale_to_unit([10.0, 20.0, 30.0, 40.0])
    assert result[0] == 0.0


def test_last_element_becomes_one_when_sorted():
    result = rescale_to_unit([10.0, 20.0, 30.0, 40.0])
    assert result[-1] == 1.0


def test_min_always_zero():
    numbers = [3.0, 1.0, 4.0, 1.5, 9.0, 2.6]
    result = rescale_to_unit(numbers)
    assert min(result) == 0.0


def test_max_always_one():
    numbers = [3.0, 1.0, 4.0, 1.5, 9.0, 2.6]
    result = rescale_to_unit(numbers)
    assert max(result) == 1.0


def test_output_length_matches_input():
    numbers = [1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0]
    result = rescale_to_unit(numbers)
    assert len(result) == len(numbers)


def test_returns_list():
    result = rescale_to_unit([1.0, 2.0])
    assert isinstance(result, list)


def test_all_values_between_zero_and_one():
    numbers = [10.0, 3.0, 7.0, 1.0, 8.0]
    result = rescale_to_unit(numbers)
    for val in result:
        assert 0.0 <= val <= 1.0


def test_negative_to_positive_range():
    result = rescale_to_unit([-10.0, 0.0, 10.0])
    assert pytest.approx(result) == [0.0, 0.5, 1.0]


def test_duplicate_min_values():
    result = rescale_to_unit([1.0, 1.0, 3.0])
    assert pytest.approx(result) == [0.0, 0.0, 1.0]


def test_duplicate_max_values():
    result = rescale_to_unit([1.0, 3.0, 3.0])
    assert pytest.approx(result) == [0.0, 1.0, 1.0]


def test_duplicates_in_middle():
    result = rescale_to_unit([0.0, 2.0, 2.0, 4.0])
    assert pytest.approx(result) == [0.0, 0.5, 0.5, 1.0]


def test_large_list():
    numbers = list(range(1, 101))
    result = rescale_to_unit([float(x) for x in numbers])
    assert result[0] == 0.0
    assert result[-1] == 1.0
    assert len(result) == 100


def test_integer_like_floats():
    result = rescale_to_unit([0.0, 10.0])
    assert result == [0.0, 1.0]


def test_very_close_values():
    result = rescale_to_unit([1.0000001, 1.0000002])
    assert pytest.approx(result, rel=1e-5) == [0.0, 1.0]


def test_descending_order():
    result = rescale_to_unit([5.0, 4.0, 3.0, 2.0, 1.0])
    assert pytest.approx(result) == [1.0, 0.75, 0.5, 0.25, 0.0]