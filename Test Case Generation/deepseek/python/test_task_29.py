import pytest
from typing import List
from your_module import filter_by_prefix


class TestFilterByPrefix:
    """Test suite for filter_by_prefix function."""
    
    def test_empty_list_returns_empty_list(self):
        """Test that empty list always returns empty list regardless of prefix."""
        assert filter_by_prefix([], 'a') == []
        assert filter_by_prefix([], '') == []
        assert filter_by_prefix([], 'nonempty') == []
    
    def test_empty_prefix_matches_all_strings(self):
        """Test that empty prefix matches every string."""
        assert filter_by_prefix(['abc', 'bcd', 'cde', 'array'], '') == ['abc', 'bcd', 'cde', 'array']
        assert filter_by_prefix(['single'], '') == ['single']
        assert filter_by_prefix([''], '') == ['']
    
    def test_basic_functionality_with_valid_prefix(self):
        """Test basic filtering with non-empty prefix."""
        result = filter_by_prefix(['abc', 'bcd', 'cde', 'array'], 'a')
        assert result == ['abc', 'array']
    
    def test_no_matching_strings_returns_empty_list(self):
        """Test when no strings start with the given prefix."""
        assert filter_by_prefix(['abc', 'bcd', 'cde', 'array'], 'z') == []
        assert filter_by_prefix(['hello', 'world'], 'xyz') == []
    
    def test_prefix_longer_than_string(self):
        """Test when prefix is longer than any string."""
        assert filter_by_prefix(['ab', 'a', ''], 'abc') == []
        assert filter_by_prefix(['short'], 'longer') == []
    
    def test_exact_match(self):
        """Test when string exactly equals the prefix."""
        assert filter_by_prefix(['prefix', 'prefix_suffix', 'pre', 'prefix'], 'prefix') == ['prefix', 'prefix']
        assert filter_by_prefix(['test', 'testing', 'test'], 'test') == ['test', 'test']
    
    def test_case_sensitivity(self):
        """Test that filtering is case-sensitive."""
        assert filter_by_prefix(['Apple', 'apple', 'Apples', 'apricot'], 'App') == ['Apple', 'Apples']
        assert filter_by_prefix(['Hello', 'HELLO', 'hello'], 'he') == ['hello']
        assert filter_by_prefix(['Hello', 'HELLO', 'hello'], 'He') == ['Hello']
    
    def test_special_characters_in_prefix(self):
        """Test filtering with special characters in prefix."""
        assert filter_by_prefix(['$special', '$start', 'normal'], '$') == ['$special', '$start']
        assert filter_by_prefix(['123abc', '123xyz', '456def'], '123') == ['123abc', '123xyz']
        assert filter_by_prefix(['  spaced', 'spaced', '  space'], '  ') == ['  spaced', '  space']
    
    def test_unicode_characters(self):
        """Test filtering with Unicode characters."""
        assert filter_by_prefix(['café', 'cafeteria', 'bar'], 'caf') == ['café', 'cafeteria']
        assert filter_by_prefix(['über', 'übung', 'uber'], 'ü') == ['über', 'übung']
    
    def test_strings_with_embedded_prefix(self):
        """Test that only prefix at start matters, not elsewhere."""
        assert filter_by_prefix(['prefixed', 'nonprefixed', 'prepre'], 'pre') == ['prefixed', 'prepre']
        assert filter_by_prefix(['start', 'startup', 'restart'], 'start') == ['start', 'startup']
    
    def test_whitespace_strings(self):
        """Test with whitespace and empty strings."""
        assert filter_by_prefix(['', ' ', '  ', 'text'], '') == ['', ' ', '  ', 'text']
        assert filter_by_prefix(['', ' ', '  ', 'text'], ' ') == [' ', '  ']
        assert filter_by_prefix(['', ' ', '  ', 'text'], '  ') == ['  ']
    
    def test_single_element_list(self):
        """Test with single element lists."""
        assert filter_by_prefix(['single'], 'sin') == ['single']
        assert filter_by_prefix(['single'], 'out') == []
        assert filter_by_prefix([''], 'a') == []
    
    def test_list_with_none_values(self):
        """Test handling of None values (should raise exception)."""
        with pytest.raises(AttributeError):
            filter_by_prefix([None, 'string'], 'a')
    
    def test_list_with_integer_values(self):
        """Test handling of non-string values (should raise exception)."""
        with pytest.raises(AttributeError):
            filter_by_prefix([1, 'string'], 'a')
    
    def test_list_with_mixed_types(self):
        """Test handling of mixed type values (should raise exception)."""
        with pytest.raises(AttributeError):
            filter_by_prefix([123, 'string', None], 'a')
    
    def test_return_value_is_new_list(self):
        """Test that the function returns a new list, not a view or reference."""
        strings = ['apple', 'apricot', 'banana']
        result = filter_by_prefix(strings, 'ap')
        result.append('modified')
        assert result != strings
        assert 'modified' not in strings
    
    def test_original_list_unchanged(self):
        """Test that the original list is not modified."""
        original = ['apple', 'banana', 'apricot']
        original_copy = original.copy()
        filter_by_prefix(original, 'ap')
        assert original == original_copy
    
    def test_large_list_performance_edge_case(self):
        """Test with large list to ensure function works (edge case for implementation)."""
        large_list = [f"prefix_{i}" for i in range(1000)] + [f"no_match_{i}" for i in range(1000)]
        result = filter_by_prefix(large_list, 'prefix_')
        assert len(result) == 1000
        assert all(s.startswith('prefix_') for s in result)
    
    def test_all_strings_match(self):
        """Test when all strings match the prefix."""
        assert filter_by_prefix(['prefix1', 'prefix2', 'prefix3'], 'prefix') == ['prefix1', 'prefix2', 'prefix3']
    
    def test_numeric_prefix_as_string(self):
        """Test with numeric prefix passed as string."""
        assert filter_by_prefix(['123abc', '123def', '456ghi'], '123') == ['123abc', '123def']
    
    def test_docstring_examples(self):
        """Test the examples from the docstring."""
        assert filter_by_prefix([], 'a') == []
        assert filter_by_prefix(['abc', 'bcd', 'cde', 'array'], 'a') == ['abc', 'array']