import pytest
from flip_case_module import flip_case

class TestFlipCase:
    """Comprehensive test suite for flip_case function."""
    
    # Basic functionality tests
    def test_empty_string(self):
        """Test with empty string."""
        assert flip_case("") == ""
    
    def test_all_lowercase(self):
        """Test string with all lowercase characters."""
        assert flip_case("hello") == "HELLO"
    
    def test_all_uppercase(self):
        """Test string with all uppercase characters."""
        assert flip_case("WORLD") == "world"
    
    def test_mixed_case(self):
        """Test string with mixed case characters."""
        assert flip_case("Hello World") == "hELLO wORLD"
    
    def test_single_lowercase_char(self):
        """Test with single lowercase character."""
        assert flip_case("a") == "A"
    
    def test_single_uppercase_char(self):
        """Test with single uppercase character."""
        assert flip_case("Z") == "z"
    
    # Edge cases with non-alphabetic characters
    def test_with_numbers(self):
        """Test string containing numbers."""
        assert flip_case("abc123") == "ABC123"
    
    def test_with_special_characters(self):
        """Test string containing special characters."""
        assert flip_case("Hello!@#") == "hELLO!@#"
    
    def test_with_spaces(self):
        """Test string with multiple spaces."""
        assert flip_case("  HELLO  ") == "  hello  "
    
    def test_with_whitespace_chars(self):
        """Test string with various whitespace characters."""
        assert flip_case("\tHello\nWorld\r") == "\thELLO\nwORLD\r"
    
    def test_with_punctuation(self):
        """Test string with punctuation marks."""
        assert flip_case("Hello, World!") == "hELLO, wORLD!"
    
    # Edge cases with unicode characters
    def test_with_unicode_lowercase(self):
        """Test with Unicode lowercase characters."""
        assert flip_case("äöüß") == "ÄÖÜẞ"
    
    def test_with_unicode_uppercase(self):
        """Test with Unicode uppercase characters."""
        assert flip_case("ÄÖÜẞ") == "äöüß"
    
    def test_with_mixed_unicode(self):
        """Test string with mixed Unicode characters."""
        assert flip_case("Straße") == "sTRASSE"
    
    # Case-sensitive edge cases
    def test_sensitive_characters(self):
        """Test with characters that have case variants."""
        assert flip_case("AaBbCc") == "aAbBcC"
    
    def test_alternating_chars(self):
        """Test with alternating case pattern."""
        assert flip_case("TeXt") == "tExT"
    
    def test_long_string(self):
        """Test with long string."""
        input_str = "A" * 1000 + "b" * 1000
        expected = "a" * 1000 + "B" * 1000
        assert flip_case(input_str) == expected
    
    # Edge case with unicode character that has no case
    def test_unicode_without_case(self):
        """Test with Unicode characters that have no case distinction."""
        assert flip_case("😀🎉汉字") == "😀🎉汉字"
    
    def test_mixed_unicode_alphabets(self):
        """Test with different Unicode alphabet systems."""
        assert flip_case("Παράδειγμα") == "πΑΡΆΔΕΙΓΜΑ"
    
    # Edge case for identity operation
    def test_no_chars_in_range(self):
        """Test string with characters that don't have case."""
        assert flip_case("123!@#") == "123!@#"
    
    # Multiple line strings
    def test_multiline_string(self):
        """Test with multiline string."""
        input_str = "Hello\nWorld\r\nPython"
        expected = "hELLO\nwORLD\r\npYTHON"
        assert flip_case(input_str) == expected
    
    # Numeric strings
    def test_numeric_string(self):
        """Test purely numeric string."""
        assert flip_case("1234567890") == "1234567890"
    
    # Edge case with escape characters
    def test_with_escape_chars(self):
        """Test string with escape sequences."""
        assert flip_case("Hello\\nWorld") == "hELLO\\NwORLD"
    
    # Edge case for string with only one type of character
    def test_identical_chars_different_case(self):
        """Test string with same letters in different case."""
        assert flip_case("aAaA") == "AaAa"
    
    def test_string_with_symbols_that_are_uppercase_in_unicode(self):
        """Test with symbols that have uppercase variants in Unicode."""
        # Example: the Unicode character 'ß' (sharp s) transforms to 'SS'
        # Note: Python's swapcase() handles ß correctly
        assert flip_case("ß") == "SS"
    
    # Additional business logic verification
    def test_two_flips_return_original(self):
        """Test that applying flip_case twice returns original string."""
        original = "Hello World 123!@#"
        once = flip_case(original)
        twice = flip_case(once)
        assert twice == original
    
    def test_immutable_behavior(self):
        """Test that function doesn't modify original string in calling scope."""
        original = "Test String"
        _ = flip_case(original)
        assert original == "Test String"