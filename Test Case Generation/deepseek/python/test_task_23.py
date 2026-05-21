import pytest
from your_module import strlen  # Replace 'your_module' with the actual module name

class TestStrlen:
    """Test suite for strlen function"""
    
    def test_empty_string(self):
        """Test that empty string returns length 0"""
        assert strlen("") == 0
    
    def test_single_character(self):
        """Test string with single character"""
        assert strlen("a") == 1
        assert strlen(" ") == 1
        assert strlen("\n") == 1
        assert strlen("\t") == 1
    
    def test_multiple_characters(self):
        """Test string with multiple characters"""
        assert strlen("abc") == 3
        assert strlen("Hello World") == 11
        assert strlen("12345") == 5
    
    def test_special_characters(self):
        """Test string containing special characters"""
        assert strlen("!@#$%^&*()") == 10
        assert strlen("ñáéíóú") == 6
        assert strlen("αβγδεζ") == 6
    
    def test_unicode_characters(self):
        """Test string with Unicode characters"""
        assert strlen("😀😁😂") == 3
        assert strlen("こんにちは") == 5
        assert strlen("Привет") == 6
    
    def test_whitespace_strings(self):
        """Test strings containing only whitespace"""
        assert strlen("   ") == 3
        assert strlen("\n\n\n") == 3
        assert strlen("\t\t") == 2
        assert strlen(" \n\t ") == 4
    
    def test_long_string(self):
        """Test long string to ensure no performance issues"""
        long_str = "a" * 10000
        assert strlen(long_str) == 10000
    
    def test_string_with_numbers(self):
        """Test string containing numeric characters"""
        assert strlen("0") == 1
        assert strlen("1234567890") == 10
        assert strlen("abc123def456") == 12
    
    def test_mixed_case_string(self):
        """Test string with mixed case characters"""
        assert strlen("AbCdEfG") == 7
        assert strlen("UPPERlower") == 10
    
    def test_string_with_escape_sequences(self):
        """Test string containing escape sequences"""
        assert strlen("\\n") == 2  # Backslash + n
        assert strlen("\\\\") == 2  # Double backslash
        assert strlen("\\\"") == 2  # Backslash + quote
    
    @pytest.mark.parametrize("input_string,expected_length", [
        ("", 0),
        ("a", 1),
        ("abc", 3),
        ("Hello World", 11),
        ("123", 3),
        ("   ", 3),
        ("😀😁", 2),
        ("\x00", 1),  # Null character
        ("\x01\x02\x03", 3),  # Control characters
    ])
    def test_parametrized_cases(self, input_string, expected_length):
        """Test multiple cases using parametrize"""
        assert strlen(input_string) == expected_length
    
    def test_type_preservation(self):
        """Test that function returns integer type"""
        result = strlen("test")
        assert isinstance(result, int)
        assert result == 4
    
    def test_string_with_newline_and_whitespace(self):
        """Test string containing newline and various whitespace"""
        assert strlen("line1\nline2\n") == 12
        assert strlen("\r\n") == 2
        assert strlen(" \r \n \t") == 6