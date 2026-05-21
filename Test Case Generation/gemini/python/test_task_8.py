import pytest
from typing import List, Tuple

# Assuming the function is in a file named solution.py
# If testing in a single script context, the function definition is required:
def sum_product(numbers: List[int]) -> Tuple[int, int]:
    """ For a given list of integers, return a tuple consisting of a sum and a product of all the integers in a list.
    Empty sum should be equal to 0 and empty product should be equal to 1.
    """
    sum_value = 0
    prod_value = 1

    for n in numbers:
        sum_value += n
        prod_value *= n
    return sum_value, prod_value

def test_sum_product_empty_list():
    """Tests the edge case of an empty list."""
    assert sum_product([]) == (0, 1)

def test_sum_product_single_element():
    """Tests a list with a single positive integer."""
    assert sum_product([5]) == (5, 5)

def test_sum_product_multiple_elements():
    """Tests a standard list of positive integers."""
    assert sum_product([1, 2, 3, 4]) == (10, 24)

def test_sum_product_with_zero():
    """Tests a list containing zero, which affects the product."""
    assert sum_product([1, 2, 0, 4]) == (7, 0)

def test_sum_product_all_zeros():
    """Tests a list of multiple zeros."""
    assert sum_product([0, 0, 0]) == (0, 0)

def test_sum_product_negative_numbers():
    """Tests a list with negative integers."""
    assert sum_product([-1, -2, 3]) == (0, 6)

def test_sum_product_large_numbers():
    """Tests behavior with larger integer values."""
    assert sum_product([100, 200, 300]) == (600, 6000000)

def test_sum_product_identical_elements():
    """Tests a list where all elements are the same."""
    assert sum_product([2, 2, 2]) == (6, 8)

@pytest.mark.parametrize("input_list, expected_output", [
    ([], (0, 1)),
    ([10], (10, 10)),
    ([-5, 5], (0, -25)),
    ([1, 2, 3], (6, 6)),
])
def test_sum_product_parameterized(input_list, expected_output):
    """Parameterized test for various scenarios to ensure robustness."""
    assert sum_product(input_list) == expected_output