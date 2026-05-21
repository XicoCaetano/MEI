import pytest
from typing import List
from your_module import separate_paren_groups

def test_empty_string():
    assert separate_paren_groups("") == []

def test_single_group():
    assert separate_paren_groups("()") == ["()"]
    assert separate_paren_groups("( )") == ["()"]
    assert separate_paren_groups("(hello)") == ["()"]

def test_nested_groups():
    assert separate_paren_groups("(())") == ["(())"]
    assert separate_paren_groups("((()))") == ["((()))"]
    assert separate_paren_groups("(()())") == ["(()())"]

def test_multiple_groups():
    assert separate_paren_groups("()()") == ["()", "()"]
    assert separate_paren_groups("(())()") == ["(())", "()"]
    assert separate_paren_groups("()(())") == ["()", "(())"]
    assert separate_paren_groups("(())(())") == ["(())", "(())"]

def test_with_spaces():
    assert separate_paren_groups("( ) (( )) (( )( ))") == ["()", "(())", "(()())"]
    assert separate_paren_groups("  (  )  (  (  )  )  ") == ["()", "(())"]
    assert separate_paren_groups("( ) ( )") == ["()", "()"]
    assert separate_paren_groups("(   (   )   )") == ["(())"]

def test_complex_nested_with_spaces():
    assert separate_paren_groups("(( ( )) ) (( ( ) ))") == ["((()))", "((()))"]
    assert separate_paren_groups("( ( ( ) ) ) ( )") == ["((()))", "()"]

def test_no_groups():
    assert separate_paren_groups("") == []
    assert separate_paren_groups("   ") == []
    assert separate_paren_groups("abc") == []
    assert separate_paren_groups("hello world") == []

def test_only_open_parentheses():
    with pytest.raises(Exception):
        separate_paren_groups("(((")

def test_only_closed_parentheses():
    with pytest.raises(Exception):
        separate_paren_groups(")))")

def test_mismatched_parentheses():
    with pytest.raises(Exception):
        separate_paren_groups("(()")
    
    with pytest.raises(Exception):
        separate_paren_groups("())")
    
    with pytest.raises(Exception):
        separate_paren_groups("((())")
    
    with pytest.raises(Exception):
        separate_paren_groups("()))(()")

def test_mixed_characters():
    assert separate_paren_groups("(a)b(c)d") == ["()", "()"]
    assert separate_paren_groups("(x(y)z)") == ["(())"]
    assert separate_paren_groups("(abc)(def)") == ["()", "()"]

def test_large_nested_structure():
    input_str = "(" * 1000 + ")" * 1000
    result = separate_paren_groups(input_str)
    assert len(result) == 1
    assert len(result[0]) == 2000
    assert result[0] == "(" * 1000 + ")" * 1000

def test_consecutive_groups():
    assert separate_paren_groups("()()()()") == ["()", "()", "()", "()"]
    assert separate_paren_groups("(()) (()) (())") == ["(())", "(())", "(())"]

def test_interleaved_groups():
    result = separate_paren_groups("(()()) (()) ()")
    assert result == ["(()())", "(())", "()"]

def test_whitespace_variations():
    assert separate_paren_groups("( \t )\n( ( ) )") == ["()", "(())"]
    assert separate_paren_groups("  (\n)\t\r\n  ") == ["()"]
    assert separate_paren_groups("(  (  )  )  (  )") == ["(())", "()"]