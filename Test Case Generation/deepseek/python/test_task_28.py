import pytest
from typing import List
from your_module import concatenate  # Replace 'your_module' with the actual module name

def test_empty_list():
    """Test concatenation with empty list"""
    assert concatenate([]) == ''

def test_single_string():
    """Test concatenation with single string"""
    assert concatenate(['hello']) == 'hello'

def test_multiple_strings():
    """Test concatenation with multiple strings"""
    assert concatenate(['a', 'b', 'c']) == 'abc'

def test_strings_with_spaces():
    """Test concatenation with strings containing spaces"""
    assert concatenate(['hello ', 'world', '!']) == 'hello world!'

def test_strings_with_empty_elements():
    """Test concatenation with empty string elements"""
    assert concatenate(['a', '', 'b', '', 'c']) == 'abc'

def test_numeric_strings():
    """Test concatenation with numeric strings"""
    assert concatenate(['1', '2', '3', '4']) == '1234'

def test_special_characters():
    """Test concatenation with special characters"""
    assert concatenate(['!', '@', '#', '$', '%']) == '!@#$%'

def test_unicode_strings():
    """Test concatenation with unicode characters"""
    assert concatenate(['Olá', ' ', 'mundo', ' ', '❤️']) == 'Olá mundo ❤️'

def test_very_long_string():
    """Test concatenation with very long strings"""
    long_str1 = 'a' * 1000
    long_str2 = 'b' * 1000
    long_str3 = 'c' * 1000
    result = concatenate([long_str1, long_str2, long_str3])
    assert len(result) == 3000
    assert result == long_str1 + long_str2 + long_str3

def test_large_list():
    """Test concatenation with a large number of elements"""
    strings = [f'str_{i}' for i in range(1000)]
    result = concatenate(strings)
    expected = ''.join(strings)
    assert result == expected

def test_whitespace_only():
    """Test concatenation with whitespace-only strings"""
    assert concatenate([' ', '\t', '\n', '  ']) == ' \t\n  '

def test_mixed_types_input():
    """Test that function only accepts List[str] type"""
    with pytest.raises(TypeError):
        concatenate([1, 2, 3])  # Should raise TypeError since elements aren't strings

def test_none_input():
    """Test with None as input"""
    with pytest.raises(TypeError):
        concatenate(None)

def test_non_list_input():
    """Test with non-list iterable"""
    with pytest.raises(TypeError):
        concatenate(('a', 'b', 'c'))  # Tuple instead of list

def test_list_with_none_element():
    """Test with list containing None element"""
    with pytest.raises(TypeError):
        concatenate(['a', None, 'c'])

def test_single_character_strings():
    """Test concatenation of single character strings"""
    chars = [chr(i) for i in range(32, 127)]  # Printable ASCII characters
    result = concatenate(chars)
    expected = ''.join(chars)
    assert result == expected

def test_empty_strings_only():
    """Test with list containing only empty strings"""
    assert concatenate(['', '', '']) == ''

def test_newline_and_tab():
    """Test concatenation with escape sequences"""
    assert concatenate(['line1\n', 'line2\t', 'line3']) == 'line1\nline2\tline3'