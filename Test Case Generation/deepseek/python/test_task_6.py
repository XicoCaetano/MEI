import pytest
from typing import List
from your_module import parse_nested_parens

class TestParseNestedParens:
    """Test suite for parse_nested_parens function"""
    
    def test_basic_example(self):
        """Test the example from the docstring"""
        result = parse_nested_parens('(()()) ((())) () ((())()())')
        assert result == [2, 3, 1, 3]
    
    def test_single_group_simple(self):
        """Test a single group with simple parentheses"""
        assert parse_nested_parens('()') == [1]
        assert parse_nested_parens('(())') == [2]
        assert parse_nested_parens('((()))') == [3]
    
    def test_single_group_complex(self):
        """Test a single group with varying nesting levels"""
        assert parse_nested_parens('(()())') == [2]
        assert parse_nested_parens('((())())') == [3]
        assert parse_nested_parens('(()(()))') == [3]
    
    def test_multiple_groups(self):
        """Test multiple groups with spaces"""
        assert parse_nested_parens('() ()') == [1, 1]
        assert parse_nested_parens('(()) ()') == [2, 1]
        assert parse_nested_parens('((())) (())') == [3, 2]
        assert parse_nested_parens('(()()) ((()))') == [2, 3]
    
    def test_empty_string(self):
        """Test empty string input"""
        assert parse_nested_parens('') == []
    
    def test_string_with_only_spaces(self):
        """Test string containing only spaces"""
        assert parse_nested_parens('   ') == []
        assert parse_nested_parens(' ') == []
    
    def test_trailing_and_leading_spaces(self):
        """Test string with leading and trailing spaces"""
        assert parse_nested_parens('  ()  ') == [1]
        assert parse_nested_parens('  (())  ()  ') == [2, 1]
    
    def test_multiple_consecutive_spaces(self):
        """Test string with multiple spaces between groups"""
        assert parse_nested_parens('()   ()') == [1, 1]
        assert parse_nested_parens('(())     ((()))') == [2, 3]
    
    def test_complex_nested_patterns(self):
        """Test complex nested parentheses patterns"""
        assert parse_nested_parens('((())(()))') == [3]
        assert parse_nested_parens('(()()(()))') == [3]
        assert parse_nested_parens('((((()))))') == [5]
    
    def test_multiple_complex_groups(self):
        """Test multiple complex groups together"""
        assert parse_nested_parens('((())) (()()) ((())())') == [3, 2, 3]
        assert parse_nested_parens('(((()))) (()(())) ()') == [4, 3, 1]
    
    def test_deep_nesting(self):
        """Test very deep nesting levels"""
        deep_string = '(' * 100 + ')' * 100
        assert parse_nested_parens(deep_string) == [100]
        
        deep_strings = ' '.join(['(' * i + ')' * i for i in [10, 20, 30, 40]])
        expected = [10, 20, 30, 40]
        assert parse_nested_parens(deep_strings) == expected
    
    def test_mixed_order_groups(self):
        """Test groups with different nesting orders"""
        assert parse_nested_parens('(()()) ((())) () ((())()())') == [2, 3, 1, 3]
        assert parse_nested_parens('((())) () (()()) ((())()())') == [3, 1, 2, 3]
    
    def test_alternating_patterns(self):
        """Test alternating parentheses patterns"""
        assert parse_nested_parens('()(())') == [2]  # Should be parsed as one group
        assert parse_nested_parens('(()())') == [2]
        assert parse_nested_parens('(())()') == [2]  # One continuous group
    
    def test_single_parenthesis_malformed(self):
        """Test malformed input with unbalanced parentheses (function handles anyway)"""
        # The function doesn't validate balanced parentheses, just counts nesting
        assert parse_nested_parens('(') == [1]
        assert parse_nested_parens(')(') == [0]  # depth becomes negative
        assert parse_nested_parens('(()') == [2]  # Unclosed
    
    def test_mixed_malformed_with_valid(self):
        """Test mixture of malformed and valid groups"""
        assert parse_nested_parens('( (()) )') == [2, 2, 1]  # Bare parentheses treated as groups
        assert parse_nested_parens('(() ())') == [2, 1, 1]
    
    def test_no_parentheses(self):
        """Test groups with no parentheses"""
        assert parse_nested_parens('abc def') == [0, 0]
        assert parse_nested_parens('no parentheses here') == [0, 0, 0, 0]
        assert parse_nested_parens('') == []
    
    def test_mixed_characters(self):
        """Test strings with mixed characters (though function ignores non-parens)"""
        assert parse_nested_parens('(a(b)c)') == [2]
        assert parse_nested_parens('(())abc(())') == [2]  # Treated as one group
        assert parse_nested_parens('a (()) b () c') == [0, 2, 0, 1, 0]
    
    def test_whitespace_only_after_split(self):
        """Test that empty strings from split are filtered out"""
        # The function uses 'if x' to filter empty strings
        result = parse_nested_parens('()   ')
        assert result == [1]
        
        result = parse_nested_parens('   ()   ')
        assert result == [1]
    
    def test_edge_case_single_character(self):
        """Test single character inputs"""
        assert parse_nested_parens('(') == [1]
        assert parse_nested_parens(')') == [0]
        assert parse_nested_parens('a') == [0]
        assert parse_nested_parens(' ') == []
    
    def test_performance_large_input(self):
        """Test with large input to ensure function handles it"""
        groups = ['(' * i + ')' * i for i in range(1, 101)]
        large_string = ' '.join(groups)
        result = parse_nested_parens(large_string)
        expected = list(range(1, 101))
        assert result == expected

if __name__ == '__main__':
    pytest.main([__file__, '-v', '--cov=.'])