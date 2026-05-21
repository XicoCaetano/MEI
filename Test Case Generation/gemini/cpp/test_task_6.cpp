#include <gtest/gtest.h>
#include <vector>
#include <string>

// Protótipo da função a ser testada
std::vector<int> parse_nested_parens(std::string paren_string);

// Teste para o exemplo fornecido na documentação
TEST(ParseNestedParensTest, ProvidedExample) {
    std::string input = "(()()) ((())) () ((())()())";
    std::vector<int> expected = {2, 3, 1, 3};
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste com string vazia
TEST(ParseNestedParensTest, EmptyString) {
    std::string input = "";
    std::vector<int> expected = {};
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste com apenas um par de parênteses simples
TEST(ParseNestedParensTest, SimpleParen) {
    std::string input = "()";
    std::vector<int> expected = {1};
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste com múltiplos grupos simples separados por espaços
TEST(ParseNestedParensTest, MultipleSimpleGroups) {
    std::string input = "() () ()";
    std::vector<int> expected = {1, 1, 1};
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste com profundidade maior
TEST(ParseNestedParensTest, DeepNesting) {
    std::string input = "((((()))))";
    std::vector<int> expected = {5};
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste com caracteres que não são parênteses (devem ser ignorados pela lógica da função)
TEST(ParseNestedParensTest, IgnoreOtherCharacters) {
    // A função ignora qualquer char que não seja '(' ou ')'
    // Espaços reiniciam o estado apenas se level chegar a 0
    std::string input = "( ( ) )"; 
    std::vector<int> expected = {2};
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste para garantir que o estado é resetado corretamente entre grupos
TEST(ParseNestedParensTest, ResetStateBetweenGroups) {
    std::string input = "(( )) ()";
    std::vector<int> expected = {2, 1};
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste de Edge Case: Parênteses mal formados (fechar sem abrir)
// Nota: Baseado na implementação fornecida, level diminuiria, mas push_back só ocorre se level == 0
TEST(ParseNestedParensTest, MalformedClosingOnly) {
    std::string input = ")))";
    std::vector<int> expected = {}; // Level nunca sobe, então nunca atinge level == 0 após incremento
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste de Edge Case: Parênteses mal formados (abrir sem fechar)
TEST(ParseNestedParensTest, MalformedOpeningOnly) {
    std::string input = "(((";
    std::vector<int> expected = {}; // Level nunca volta a 0
    EXPECT_EQ(parse_nested_parens(input), expected);
}

// Teste de Edge Case: Espaços extras no início, fim e entre grupos
TEST(ParseNestedParensTest, ExtraSpaces) {
    std::string input = "  (() )   (( ))  ";
    std::vector<int> expected = {2, 2};
    EXPECT_EQ(parse_nested_parens(input), expected);
}