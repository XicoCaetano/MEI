import pytest
from typing import List
from solution import parse_nested_parens


def test_example_from_docstring():
    assert parse_nested_parens('(()()) ((())) () ((())()())') == [2, 3, 1, 3]


def test_single_pair():
    assert parse_nested_parens('()') == [1]


def test_double_nested():
    assert parse_nested_parens('(())') == [2]


def test_triple_nested():
    assert parse_nested_parens('((()))') == [3]


def test_flat_multiple_pairs():
    assert parse_nested_parens('()()()') == [1]


def test_two_groups_simple():
    assert parse_nested_parens('() ()') == [1, 1]


def test_two_groups_different_depths():
    assert parse_nested_parens('(()) ((()))') == [2, 3]


def test_deeply_nested():
    assert parse_nested_parens('(((())))') == [4]


def test_deeply_nested_five_levels():
    assert parse_nested_parens('((((()))))') == [5]


def test_mixed_flat_and_nested():
    assert parse_nested_parens('(()()) ((())) () ((())()())') == [2, 3, 1, 3]


def test_single_group_wide():
    assert parse_nested_parens('(()())') == [2]


def test_multiple_groups_same_depth():
    assert parse_nested_parens('(()) (()) (())') == [2, 2, 2]


def test_empty_string():
    assert parse_nested_parens('') == []


def test_multiple_spaces_between_groups():
    result = parse_nested_parens('(())  (())')
    assert result == [2, 2]


def test_leading_space():
    result = parse_nested_parens(' (())')
    assert result == [2]


def test_trailing_space():
    result = parse_nested_parens('(()) ')
    assert result == [2]


def test_group_with_siblings_at_same_level():
    assert parse_nested_parens('(()()())') == [2]


def test_complex_nesting():
    assert parse_nested_parens('((()()))') == [3]


def test_four_groups():
    assert parse_nested_parens('() (()) ((())) ((((""))))') == [1, 2, 3, 4]


def test_returns_list():
    result = parse_nested_parens('()')
    assert isinstance(result, list)


def test_returns_list_of_ints():
    result = parse_nested_parens('() (())')
    assert all(isinstance(x, int) for x in result)


def test_large_input():
    group = '(' * 10 + ')' * 10
    input_str = ' '.join([group] * 5)
    assert parse_nested_parens(input_str) == [10] * 5


def test_alternating_depths():
    assert parse_nested_parens('() (()) () ((()))') == [1, 2, 1, 3]


def test_single_group_no_nesting():
    assert parse_nested_parens('()') == [1]


def test_groups_count_matches_output_length():
    input_str = '() (()) ((()))'
    result = parse_nested_parens(input_str)
    assert len(result) == 3


def test_empty_groups_filtered_by_split():
    result = parse_nested_parens('(())   ((()))')
    assert result == [2, 3]


def test_max_depth_not_affected_by_closing_parens():
    assert parse_nested_parens('((()))') == [3]


def test_wide_then_deep():
    assert parse_nested_parens('()()() ((()))') == [1, 3]


def test_deep_then_wide():
    assert parse_nested_parens('((())) ()()()') == [3, 1]