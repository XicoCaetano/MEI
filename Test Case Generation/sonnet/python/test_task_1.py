import pytest
from typing import List
from solution import separate_paren_groups


def test_example_from_docstring():
    assert separate_paren_groups('( ) (( )) (( )( ))') == ['()', '(())', '(()())']


def test_empty_string():
    assert separate_paren_groups('') == []


def test_single_pair():
    assert separate_paren_groups('()') == ['()']


def test_single_pair_with_spaces():
    assert separate_paren_groups('( )') == ['()']


def test_two_simple_groups():
    assert separate_paren_groups('()()') == ['()', '()']


def test_nested_group():
    assert separate_paren_groups('(())') == ['(())']


def test_deeply_nested_group():
    assert separate_paren_groups('(((())))') == ['(((())))']


def test_multiple_nested_groups():
    assert separate_paren_groups('(()) (())') == ['(())', '(())']


def test_spaces_only_between_groups():
    assert separate_paren_groups('()   ()') == ['()', '()']


def test_spaces_inside_groups():
    assert separate_paren_groups('( ( ) )') == ['(())']


def test_three_groups():
    assert separate_paren_groups('()()()') == ['()', '()', '()']


def test_complex_nested():
    assert separate_paren_groups('(()())') == ['(()())']


def test_mixed_depth_groups():
    assert separate_paren_groups('() (()) ((()))') == ['()', '(())', '((()))']


def test_all_spaces():
    assert separate_paren_groups('   ') == []


def test_leading_and_trailing_spaces():
    assert separate_paren_groups('  ()  ') == ['()']


def test_groups_with_multiple_children():
    assert separate_paren_groups('(()()())') == ['(()()())']


def test_returns_list():
    result = separate_paren_groups('()')
    assert isinstance(result, list)


def test_returns_list_of_strings():
    result = separate_paren_groups('() (())')
    assert all(isinstance(item, str) for item in result)


def test_no_spaces_in_output():
    result = separate_paren_groups('( ) ( ( ) )')
    for group in result:
        assert ' ' not in group


def test_each_group_is_balanced():
    result = separate_paren_groups('() (()) ((()))')
    for group in result:
        depth = 0
        for c in group:
            if c == '(':
                depth += 1
            elif c == ')':
                depth -= 1
        assert depth == 0


def test_four_groups():
    assert separate_paren_groups('()()()()')  == ['()', '()', '()', '()']


def test_complex_mixed():
    assert separate_paren_groups('(())(()())((()))') == ['(())', '(()())', '((()))']


def test_single_nested_three_levels():
    assert separate_paren_groups('((()))') == ['((()))']


def test_group_count():
    result = separate_paren_groups('() () ()')
    assert len(result) == 3


def test_preserves_order():
    result = separate_paren_groups('() (()) ((()))')
    assert result[0] == '()'
    assert result[1] == '(())'
    assert result[2] == '((()))'


def test_spaces_everywhere():
    assert separate_paren_groups(' ( ) ( ( ) ) ') == ['()', '(())']


def test_two_deep_nested():
    assert separate_paren_groups('((())) ((()))') == ['((()))', '((()))']


def test_alternating_nesting():
    assert separate_paren_groups('(())(())(())') == ['(())', '(())', '(())']