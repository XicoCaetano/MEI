import pytest
from src.truncate_number import truncate_number  # adjust import path as needed

class TestTruncateNumber:
    """Test suite for truncate_number function."""
    
    def test_positive_float_with_decimal(self):
        """Test normal positive float with decimal part."""
        assert truncate_number(3.5) == 0.5
        assert truncate_number(2.7) == 0.7
        assert truncate_number(10.123) == 0.123
    
    def test_positive_float_without_decimal(self):
        """Test positive whole numbers should return 0.0."""
        assert truncate_number(5.0) == 0.0
        assert truncate_number(100.0) == 0.0
        assert truncate_number(1.0) == 0.0
    
    def test_small_positive_numbers(self):
        """Test numbers between 0 and 1."""
        assert truncate_number(0.1) == 0.1
        assert truncate_number(0.999) == 0.999
        assert truncate_number(0.0) == 0.0
    
    def test_large_numbers(self):
        """Test large positive floating point numbers."""
        assert truncate_number(123456789.987654321) == pytest.approx(0.987654321)
        assert truncate_number(1e6 + 0.5) == 0.5
        assert truncate_number(1e10 + 0.001) == 0.001
    
    def test_floating_point_precision(self):
        """Test floating point precision edge cases."""
        result = truncate_number(0.1 + 0.2)  # 0.30000000000000004
        assert result == pytest.approx(0.30000000000000004)
        
        result = truncate_number(1.999999999999999)
        assert result == 0.999999999999999
        result = truncate_number(1.9999999999999999)
        assert result == 0.9999999999999999
    
    def test_numbers_close_to_integer(self):
        """Test numbers extremely close to integers from below."""
        assert truncate_number(5.999999999999999) == 0.999999999999999
        assert truncate_number(2.0000000000000004) == 0.0000000000000004
    
    def test_scientific_notation(self):
        """Test numbers in scientific notation."""
        assert truncate_number(1.23e-5) == 1.23e-5
        assert truncate_number(1.5e10 + 0.75) == 0.75
    
    def test_very_small_decimals(self):
        """Test very small decimal portions."""
        assert truncate_number(1e-10) == 1e-10
        assert truncate_number(1e-15) == 1e-15
    
    def test_edge_cases(self):
        """Test various edge cases."""
        # Maximum finite float
        import sys
        max_float = sys.float_info.max
        fractional_part = max_float % 1.0
        assert 0 <= fractional_part < 1.0
        
        # Minimum positive float
        min_float = sys.float_info.min
        assert truncate_number(min_float) == min_float
        
        # Very large integer part with small decimal
        assert truncate_number(1e308 + 0.5) == 0.5
    
    def test_pi_and_e(self):
        """Test common mathematical constants."""
        import math
        assert truncate_number(math.pi) == math.pi - 3
        assert truncate_number(math.e) == math.e - 2
    
    def test_repeated_calls_consistency(self):
        """Test that repeated calls return consistent results."""
        numbers = [0.1, 1.5, 2.3, 10.999, 100.001, 0.5, 1.0]
        for num in numbers:
            assert truncate_number(num) == truncate_number(num)
    
    def test_no_side_effects(self):
        """Test that function doesn't modify input (immutable)."""
        original = 3.14
        result = truncate_number(original)
        assert original == 3.14
        assert result == 0.14
    
    def test_negative_numbers_raise(self):
        """Test that negative numbers raise an error (if documented)."""
        # Note: Documentation says "positive floating point number"
        # Depending on implementation, negative numbers might be allowed or raise error
        # This test checks that if negative numbers are passed, the behavior is handled
        # The modulo operation with negative numbers behaves differently
        # Adjust assertion based on actual requirements
        with pytest.raises(Exception):
            truncate_number(-3.5)
    
    def test_zero_edge_case(self):
        """Test zero as boundary case."""
        assert truncate_number(0.0) == 0.0
        assert truncate_number(0.0000000001) == 0.0000000001