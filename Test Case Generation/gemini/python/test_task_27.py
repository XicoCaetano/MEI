import pytest

def flip_case(string: str) -> str:
    """ For a given string, flip lowercase characters to uppercase and uppercase to lowercase.
    >>> flip_case('Hello')
    'hELLO'
    """
    return string.swapcase()

def test_flip_case_basic_mixed():
    """Test standard mixed case string."""
    assert flip_case("Hello") == "hELLO"

def test_flip_case_all_lower():
    """Test string with only lowercase characters."""
    assert flip_case("python") == "PYTHON"

def test_flip_case_all_upper():
    """Test string with only uppercase characters."""
    assert flip_case("PYTEST") == "pytest"

def test_flip_case_empty_string():
    """Test handling of an empty string."""
    assert flip_case("") == ""

def test_flip_case_non_alphabetic():
    """Test strings containing numbers and symbols."""
    assert flip_case("123!@#") == "123!@#"
    assert flip_case("Go! 2") == "gO! 2"

def test_flip_case_whitespace():
    """Test strings with various whitespace characters."""
    assert flip_case(" \t\n") == " \t\n"

def test_flip_case_unicode():
    """Test unicode characters (accented letters)."""
    assert flip_case("áÉîØ") == "ÁéÎø"

def test_flip_case_long_string():
    """Test a long string to ensure performance and correctness."""
    input_str = "aB" * 1000
    expected_str = "Ab" * 1000
    assert flip_case(input_str) == expected_str

def test_flip_case_single_character():
    """Test single character edge cases."""
    assert flip_case("a") == "A"
    assert flip_case("Z") == "z"

@pytest.mark.parametrize("input_val, expected", [
    ("Lower", "lOWER"),
    ("uPPER", "Upper"),
    ("1a2B", "1A2b"),
    (None, None) # This test will naturally fail if input isn't validated, 
                 # but serves to document current behavior for types.
], ids=["lower-start", "upper-start", "alphanumeric", "null-check"])
def test_flip_case_parameterized(input_val, expected):
    if input_val is None:
        with pytest.raises(AttributeError):
            flip_case(input_val)
    else:
        assert flip_case(input_val) == expected