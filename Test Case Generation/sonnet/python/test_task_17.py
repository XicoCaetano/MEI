import pytest
from typing import List
from solution import parse_music


def test_example_from_docstring():
    assert parse_music('o o| .| o| o| .| .| .| .| o o') == [4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4]


def test_empty_string():
    assert parse_music('') == []


def test_single_whole_note():
    assert parse_music('o') == [4]


def test_single_half_note():
    assert parse_music('o|') == [2]


def test_single_quarter_note():
    assert parse_music('.|') == [1]


def test_only_whole_notes():
    assert parse_music('o o o') == [4, 4, 4]


def test_only_half_notes():
    assert parse_music('o| o| o|') == [2, 2, 2]


def test_only_quarter_notes():
    assert parse_music('.| .| .|') == [1, 1, 1]


def test_multiple_spaces_between_notes():
    assert parse_music('o  o|') == [4, 2]


def test_leading_spaces():
    assert parse_music(' o o|') == [4, 2]


def test_trailing_spaces():
    assert parse_music('o o| ') == [4, 2]


def test_only_spaces():
    assert parse_music('   ') == []


def test_two_notes_whole_and_half():
    assert parse_music('o o|') == [4, 2]


def test_two_notes_half_and_quarter():
    assert parse_music('o| .|') == [2, 1]


def test_two_notes_whole_and_quarter():
    assert parse_music('o .|') == [4, 1]


def test_all_note_types_in_sequence():
    assert parse_music('o o| .|') == [4, 2, 1]


def test_returns_list():
    result = parse_music('o')
    assert isinstance(result, list)


def test_returns_list_of_integers():
    result = parse_music('o o| .|')
    assert all(isinstance(x, int) for x in result)


def test_long_sequence():
    input_str = 'o ' * 10 + 'o| ' * 10 + '.| ' * 10
    expected = [4] * 10 + [2] * 10 + [1] * 10
    assert parse_music(input_str.strip()) == expected


def test_invalid_token_raises_key_error():
    with pytest.raises(KeyError):
        parse_music('x')


def test_invalid_token_mixed_raises_key_error():
    with pytest.raises(KeyError):
        parse_music('o x o|')


def test_note_values_are_correct_whole():
    result = parse_music('o')
    assert result[0] == 4


def test_note_values_are_correct_half():
    result = parse_music('o|')
    assert result[0] == 2


def test_note_values_are_correct_quarter():
    result = parse_music('.|')
    assert result[0] == 1


def test_order_is_preserved():
    result = parse_music('.| o| o')
    assert result == [1, 2, 4]


def test_single_space_string():
    assert parse_music(' ') == []