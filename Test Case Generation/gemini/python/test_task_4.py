import pytest
from typing import List

def mean_absolute_deviation(numbers: List[float]) -> float:
    """ For a given list of input numbers, calculate Mean Absolute Deviation
    around the mean of this dataset.
    Mean Absolute Deviation is the average absolute difference between each
    element and a centerpoint (mean in this case):
    MAD = average | x - x_mean |
    >>> mean_absolute_deviation([1.0, 2.0, 3.0, 4.0])
    1.0
    """
    mean = sum(numbers) / len(numbers)
    return sum(abs(x - mean) for x in numbers) / len(numbers)

def test_mad_basic_example():
    """Tests the example provided in the docstring."""
    assert mean_absolute_deviation([1.0, 2.0, 3.0, 4.0]) == 1.0

def test_mad_identical_elements():
    """Tests that a list of identical elements results in a MAD of 0.0."""
    assert mean_absolute_deviation([5.0, 5.0, 5.0]) == 0.0

def test_mad_single_element():
    """Tests a list with a single element."""
    assert mean_absolute_deviation([10.0]) == 0.0

def test_mad_negative_numbers():
    """Tests the function with negative values."""
    # Mean: (-2 + -4) / 2 = -3
    # Absolute differences: |-2 - (-3)| = 1, |-4 - (-3)| = 1
    # MAD: (1 + 1) / 2 = 1.0
    assert mean_absolute_deviation([-2.0, -4.0]) == 1.0

def test_mad_mixed_numbers():
    """Tests a mix of positive and negative numbers."""
    # Mean: (-10 + 0 + 10) / 3 = 0
    # Absolute differences: 10, 0, 10
    # MAD: 20 / 3
    assert mean_absolute_deviation([-10.0, 0.0, 10.0]) == pytest.approx(6.666666666666667)

def test_mad_large_floats():
    """Tests precision with larger floating point numbers."""
    data = [100.5, 200.5, 300.5]
    # Mean: 200.5
    # Diffs: 100, 0, 100
    # MAD: 200 / 3
    assert mean_absolute_deviation(data) == pytest.approx(66.66666666666667)

def test_mad_empty_list_raises_error():
    """
    Verifies that an empty list raises ZeroDivisionError.
    This ensures 100% branch/logic coverage regarding the division.
    """
    with pytest.raises(ZeroDivisionError):
        mean_absolute_deviation([])

def test_mad_integers_as_input():
    """Tests that the function handles a list of integers correctly."""
    # Mean: (1 + 2 + 3) / 3 = 2
    # Diffs: 1, 0, 1
    # MAD: 2 / 3
    assert mean_absolute_deviation([1, 2, 3]) == pytest.approx(0.6666666666666666)