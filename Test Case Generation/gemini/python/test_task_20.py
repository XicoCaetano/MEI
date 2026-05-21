import pytest
from typing import List, Tuple

def find_closest_elements(numbers: List[float]) -> Tuple[float, float]:
    """ From a supplied list of numbers (of length at least two) select and return two that are the closest to each
    other and return them in order (smaller number, larger number).
    >>> find_closest_elements([1.0, 2.0, 3.0, 4.0, 5.0, 2.2])
    (2.0, 2.2)
    >>> find_closest_elements([1.0, 2.0, 3.0, 4.0, 5.0, 2.0])
    (2.0, 2.0)
    """
    closest_pair = None
    distance = None

    for idx, elem in enumerate(numbers):
        for idx2, elem2 in enumerate(numbers):
            if idx != idx2:
                if distance is None:
                    distance = abs(elem - elem2)
                    closest_pair = tuple(sorted([elem, elem2]))
                else:
                    new_distance = abs(elem - elem2)
                    if new_distance < distance:
                        distance = new_distance
                        closest_pair = tuple(sorted([elem, elem2]))

    return closest_pair

def test_find_closest_elements_basic():
    assert find_closest_elements([1.0, 2.0, 3.0, 4.0, 5.0, 2.2]) == (2.0, 2.2)

def test_find_closest_elements_identical_values():
    assert find_closest_elements([1.0, 2.0, 3.0, 4.0, 5.0, 2.0]) == (2.0, 2.0)

def test_find_closest_elements_minimal_input():
    assert find_closest_elements([10.0, 20.0]) == (10.0, 20.0)

def test_find_closest_elements_negative_numbers():
    assert find_closest_elements([-10.0, -5.0, -2.0, -2.1]) == (-2.1, -2.0)

def test_find_closest_elements_mixed_signs():
    assert find_closest_elements([-1.0, 0.0, 1.0]) == (-1.0, 0.0) or (0.0, 1.0)

def test_find_closest_elements_floats_precision():
    assert find_closest_elements([1.0, 1.000001, 1.00001]) == (1.0, 1.000001)

def test_find_closest_elements_large_gap():
    assert find_closest_elements([100.0, 1000.0, 0.0]) == (0.0, 100.0)

def test_find_closest_elements_unsorted_input():
    assert find_closest_elements([10.0, 2.0, 30.0, 4.0]) == (2.0, 4.0)

def test_find_closest_elements_all_same():
    assert find_closest_elements([5.0, 5.0, 5.0]) == (5.0, 5.0)

def test_find_closest_elements_empty_or_single_returns_none():
    # Testing logic for lists shorter than 2 if not explicitly handled by an exception
    # based on the current implementation it would return None
    assert find_closest_elements([1.0]) is None
    assert find_closest_elements([]) is None