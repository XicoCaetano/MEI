import pytest
from typing import List
from your_module import parse_music  # Replace with actual module name

def test_basic_example():
    """Test the example provided in the docstring."""
    result = parse_music('o o| .| o| o| .| .| .| .| o o')
    expected = [4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4]
    assert result == expected

def test_single_note_variants():
    """Test each note type individually."""
    assert parse_music('o') == [4]
    assert parse_music('o|') == [2]
    assert parse_music('.|') == [1]

def test_empty_string():
    """Test empty string input."""
    assert parse_music('') == []

def test_string_with_only_spaces():
    """Test string containing only spaces."""
    assert parse_music('   ') == []
    assert parse_music(' ') == []

def test_trailing_whitespace():
    """Test string with leading/trailing spaces."""
    assert parse_music('  o o| .|  ') == [4, 2, 1]
    assert parse_music('\to o|\n') == [4, 2]

def test_multiple_whitespace_between_notes():
    """Test multiple spaces between notes."""
    assert parse_music('o   o|  .|') == [4, 2, 1]

def test_repeated_notes():
    """Test sequences of same note types."""
    assert parse_music('o o o') == [4, 4, 4]
    assert parse_music('o| o| o| o|') == [2, 2, 2, 2]
    assert parse_music('.| .| .|') == [1, 1, 1]

def test_mixed_notes():
    """Test various combinations of different notes."""
    assert parse_music('o o| .|') == [4, 2, 1]
    assert parse_music('o .| o| o') == [4, 1, 2, 4]
    assert parse_music('o| .| .| o') == [2, 1, 1, 4]

def test_long_sequence():
    """Test a long sequence of notes."""
    sequence = 'o ' * 10 + 'o| ' * 10 + '.| ' * 10
    sequence = sequence.strip()
    result = parse_music(sequence)
    expected = [4] * 10 + [2] * 10 + [1] * 10
    assert result == expected

def test_invalid_note_raises_keyerror():
    """Test that invalid note types raise KeyError."""
    with pytest.raises(KeyError):
        parse_music('x')
    
    with pytest.raises(KeyError):
        parse_music('o o| x .|')
    
    with pytest.raises(KeyError):
        parse_music('invalid')
    
    with pytest.raises(KeyError):
        parse_music('o|o')  # No space between notes

def test_partially_valid_with_invalid():
    """Test mixture of valid and invalid notes raises KeyError."""
    with pytest.raises(KeyError):
        parse_music('o o| invalid .|')

def test_unicode_or_special_chars():
    """Test handling of unicode or special characters."""
    with pytest.raises(KeyError):
        parse_music('o o| .| 你好')
    
    with pytest.raises(KeyError):
        parse_music('@ # $')

def test_newline_and_tab_separators():
    """Test that newlines and tabs are treated as whitespace."""
    result = parse_music('o\to|\n.|')
    assert result == [4, 2, 1]
    
    result = parse_music('o  \t o| \n .|')
    assert result == [4, 2, 1]

def test_single_character_notes():
    """Test that partial matches don't work."""
    with pytest.raises(KeyError):
        parse_music('o|')  # This works
    
    # All of these should fail because they're not exact matches
    with pytest.raises(KeyError):
        parse_music('o ')
    
    with pytest.raises(KeyError):
        parse_music(' o')
    
    with pytest.raises(KeyError):
        parse_music('o||')

def test_very_large_input():
    """Test performance and correctness with large input."""
    large_sequence = 'o ' * 1000 + 'o| ' * 1000 + '.| ' * 1000
    large_sequence = large_sequence.strip()
    result = parse_music(large_sequence)
    assert len(result) == 3000
    assert result[:1000] == [4] * 1000
    assert result[1000:2000] == [2] * 1000
    assert result[2000:] == [1] * 1000

def test_input_immutability():
    """Test that input string is not modified."""
    original = 'o o| .|'
    parse_music(original)
    assert original == 'o o| .|'

def test_empty_string_with_whitespace_only_variants():
    """Test various whitespace-only strings."""
    assert parse_music('\n') == []
    assert parse_music('\t') == []
    assert parse_music(' \n \t ') == []
    assert parse_music('  \t\n  ') == []

def test_mixed_separators():
    """Test mixing spaces, tabs, and newlines as separators."""
    result = parse_music('o\to|\n.| o  o|\t.|')
    expected = [4, 2, 1, 4, 2, 1]
    assert result == expected