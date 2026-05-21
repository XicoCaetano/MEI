import pytest
from typing import List

# A função é importada ou definida aqui para o contexto do teste
def separate_paren_groups(paren_string: str) -> List[str]:
    result = []
    current_string = []
    current_depth = 0

    for c in paren_string:
        if c == '(':
            current_depth += 1
            current_string.append(c)
        elif c == ')':
            current_depth -= 1
            current_string.append(c)

            if current_depth == 0:
                result.append(''.join(current_string))
                current_string.clear()

    return result

def test_basic_functionality():
    """Testa o exemplo básico fornecido na docstring."""
    assert separate_paren_groups('( ) (( )) (( )( ))') == ['()', '(())', '(()())']

def test_empty_input():
    """Testa strings vazias ou apenas com espaços."""
    assert separate_paren_groups('') == []
    assert separate_paren_groups('   ') == []

def test_no_parentheses():
    """Testa strings com caracteres que não são parênteses (devem ser ignorados)."""
    assert separate_paren_groups('abc 123') == []

def test_single_group():
    """Testa um único par de parênteses."""
    assert separate_paren_groups('()') == ['()']
    assert separate_paren_groups(' ( ) ') == ['()']

def test_deeply_nested_groups():
    """Testa múltiplos níveis de aninhamento."""
    assert separate_paren_groups('((((()))))') == ['((((()))))']
    assert separate_paren_groups('((())) (()) ()') == ['((()))', '(())', '()']

def test_multiple_separate_groups():
    """Testa vários grupos independentes e sequenciais."""
    assert separate_paren_groups('()()()') == ['()', '()', '()']

def test_complex_nesting_with_spaces():
    """Testa aninhamento complexo com espaços intercalados."""
    input_str = ' ( ( ) ( ) ) (( )) '
    expected = ['(())()', '(())']
    # Nota: A implementação atual remove espaços mas mantém a estrutura interna.
    # ' ( ( ) ( ) )' torna-se '(())()' devido à ordem de processamento.
    assert separate_paren_groups(input_str) == ['(())()', '(())']

def test_unbalanced_input_ignored():
    """Testa comportamento com parênteses não balanceados (cobertura de fluxo)."""
    # Se a string termina e o depth não é 0, o último grupo incompleto é descartado.
    assert separate_paren_groups('(()') == []
    assert separate_paren_groups('())') == ['()'] # Fecha no primeiro ')' e ignora o segundo

def test_only_opening_or_closing():
    """Testa strings compostas apenas por um tipo de parêntese."""
    assert separate_paren_groups('(((((') == []
    assert separate_paren_groups(')))))') == []

def test_interleaved_content():
    """Testa se conteúdo não-parêntese entre grupos é totalmente ignorado."""
    assert separate_paren_groups('(a) b (c)') == ['()', '()']