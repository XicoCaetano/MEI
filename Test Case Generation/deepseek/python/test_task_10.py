import pytest
from your_module import is_palindrome, make_palindrome

class TestIsPalindrome:
    """Test suite for is_palindrome function."""
    
    def test_empty_string(self):
        """Empty string should be considered a palindrome."""
        assert is_palindrome("") == True
    
    def test_single_character(self):
        """Single character should be a palindrome."""
        assert is_palindrome("a") == True
        assert is_palindrome("Z") == True
        assert is_palindrome("5") == True
    
    def test_even_length_palindrome(self):
        """Even-length palindrome strings."""
        assert is_palindrome("aa") == True
        assert is_palindrome("abba") == True
        assert is_palindrome("12344321") == True
    
    def test_odd_length_palindrome(self):
        """Odd-length palindrome strings."""
        assert is_palindrome("aba") == True
        assert is_palindrome("racecar") == True
        assert is_palindrome("12321") == True
    
    def test_non_palindrome_simple(self):
        """Simple non-palindrome strings."""
        assert is_palindrome("ab") == False
        assert is_palindrome("abc") == False
        assert is_palindrome("hello") == False
    
    def test_non_palindrome_almost(self):
        """Strings that are almost palindromes."""
        assert is_palindrome("abca") == False
        assert is_palindrome("racecars") == False
        assert is_palindrome("12345") == False
    
    def test_with_whitespace(self):
        """Strings containing whitespace."""
        assert is_palindrome("a a") == True
        assert is_palindrome("ab ba") == True
        assert is_palindrome("a b") == False
        assert is_palindrome("race car") == False
    
    def test_with_uppercase(self):
        """Case sensitivity tests."""
        assert is_palindrome("Aa") == False
        assert is_palindrome("AbBa") == True  # 'b' and 'B' are different
        assert is_palindrome("Racecar") == False
    
    def test_with_numbers(self):
        """Strings containing numbers."""
        assert is_palindrome("123321") == True
        assert is_palindrome("12345") == False
    
    def test_with_special_characters(self):
        """Strings containing special characters."""
        assert is_palindrome("!@#@!") == True
        assert is_palindrome("a!a") == True
        assert is_palindrome("!a!") == True
    
    def test_long_palindrome(self):
        """Very long palindrome string."""
        long_pal = "a" * 1000
        assert is_palindrome(long_pal) == True
    
    def test_long_non_palindrome(self):
        """Very long non-palindrome string."""
        long_non_pal = "a" * 999 + "b"
        assert is_palindrome(long_non_pal) == False

class TestMakePalindrome:
    """Test suite for make_palindrome function."""
    
    def test_empty_string(self):
        """Empty string should return empty string."""
        assert make_palindrome("") == ""
    
    def test_single_character(self):
        """Single character should return itself."""
        assert make_palindrome("a") == "a"
        assert make_palindrome("z") == "z"
        assert make_palindrome("1") == "1"
    
    def test_already_palindrome_even(self):
        """Even-length palindrome should return itself."""
        assert make_palindrome("aa") == "aa"
        assert make_palindrome("abba") == "abba"
        assert make_palindrome("123321") == "123321"
    
    def test_already_palindrome_odd(self):
        """Odd-length palindrome should return itself."""
        assert make_palindrome("aba") == "aba"
        assert make_palindrome("racecar") == "racecar"
        assert make_palindrome("12321") == "12321"
    
    def test_no_suffix_palindrome(self):
        """When no suffix palindrome exists, append reverse of whole string except last char."""
        assert make_palindrome("ab") == "aba"  # "ab" + "a"
        assert make_palindrome("abc") == "abcba"  # "abc" + "ba" (reverse of "ab")
        assert make_palindrome("abcd") == "abcdcba"  # "abcd" + "cba"
    
    def test_suffix_palindrome_with_length_one(self):
        """When last character alone is the palindrome suffix."""
        assert make_palindrome("cat") == "catac"  # palindrome suffix "t"
        assert make_palindrome("hello") == "helloleh"  # palindrome suffix "o"
    
    def test_suffix_palindrome_odd_length(self):
        """When there's an odd-length palindrome suffix."""
        assert make_palindrome("cata") == "catac"  # palindrome suffix "ata"
        assert make_palindrome("racecar") == "racecar"  # already palindrome
    
    def test_suffix_palindrome_even_length(self):
        """When there's an even-length palindrome suffix."""
        assert make_palindrome("abba") == "abba"  # already palindrome
        assert make_palindrome("xyzzyxw") == "xyzzyxwxyzz"  # suffix "zyxw" not palindrome
    
    def test_documentation_examples(self):
        """Examples from docstring."""
        assert make_palindrome("") == ""
        assert make_palindrome("cat") == "catac"
        assert make_palindrome("cata") == "catac"
    
    def test_repeated_characters(self):
        """Strings with repeated characters."""
        assert make_palindrome("aaaa") == "aaaa"
        assert make_palindrome("aaab") == "aaabaaa"
        assert make_palindrome("abbb") == "abbba"  # suffix "bbb" is palindrome
    
    def test_with_alternating_characters(self):
        """Strings with alternating characters."""
        assert make_palindrome("abab") == "ababa"  # suffix "bab" is palindrome
        assert make_palindrome("ababa") == "ababa"  # already palindrome
    
    def test_with_numbers(self):
        """Strings containing numbers."""
        assert make_palindrome("123") == "12321"
        assert make_palindrome("1234") == "1234321"
        assert make_palindrome("12321") == "12321"
    
    def test_with_uppercase(self):
        """Case-sensitive behavior."""
        assert make_palindrome("AbC") == "AbCbA"
        assert make_palindrome("ABBA") == "ABBA"
    
    def test_with_special_characters(self):
        """Strings containing special characters."""
        assert make_palindrome("!@#") == "!@#@!"
        assert make_palindrome("a!!a") == "a!!a"  # already palindrome
        assert make_palindrome("?a?") == "?a?"
    
    def test_long_string_with_longest_palindrome_suffix(self):
        """Long string where longest palindrome suffix is not at the end."""
        result = make_palindrome("abacdfgdcaba")
        # The longest palindrome suffix might be "aba" at the end
        # So we'd need to verify it's a valid palindrome
        assert is_palindrome(result)
        assert result.startswith("abacdfgdcaba")
    
    def test_string_where_all_but_first_char_form_palindrome(self):
        """When string[1:] is a palindrome."""
        assert make_palindrome("ababa") == "ababa"
        assert make_palindrome("abcba") == "abcba"
    
    def test_string_where_only_last_char_form_palindrome(self):
        """When only the last character is a palindrome."""
        assert make_palindrome("abcdefg") == "abcdefggfedcba"
        assert make_palindrome("hello") == "helloleh"
    
    def test_palindrome_property(self):
        """Ensure result is always a palindrome."""
        test_strings = ["", "a", "ab", "abc", "abcd", "cat", "cata", "racecar", 
                       "hello", "world", "123", "!@#", "a!b!c", "abba", "xyzzy"]
        for s in test_strings:
            result = make_palindrome(s)
            assert is_palindrome(result), f"Failed for input '{s}': result '{result}' is not a palindrome"
            assert result.startswith(s), f"Result '{result}' does not start with original string '{s}'"
    
    def test_minimal_addition(self):
        """Verify that the algorithm adds minimal characters to form a palindrome."""
        test_cases = [
            ("ab", "aba", 1),
            ("abc", "abcba", 2),
            ("abcd", "abcdcba", 3),
            ("cat", "catac", 2),
            ("cata", "catac", 1),
        ]
        for input_str, expected, min_additions in test_cases:
            result = make_palindrome(input_str)
            assert len(result) - len(input_str) <= min_additions + 1
            assert result == expected