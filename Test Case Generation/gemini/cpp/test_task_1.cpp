#include <gtest/gtest.h>
#include <vector>
#include <string>

// Protótipo da função a ser testada
std::vector<std::string> separate_paren_groups(std::string paren_string);

TEST(SeparateParenGroupsTest, BasicGroups) {
    std::string input = "() (()) ((()()))";
    std::vector<std::string> expected = {"()", "(())", "((()()))"};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, IgnoreSpaces) {
    std::string input = "( ) (( )) (( )( ))";
    std::vector<std::string> expected = {"()", "(())", "(()())"};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, NoSpaces) {
    std::string input = "()(())((()))";
    std::vector<std::string> expected = {"()", "(())", "((()))"};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, MultipleNestedGroups) {
    std::string input = "(()()) ((())) ()";
    std::vector<std::string> expected = {"(()())", "((()))", "()"};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, EmptyString) {
    std::string input = "";
    std::vector<std::string> expected = {};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, OnlySpaces) {
    std::string input = "     ";
    std::vector<std::string> expected = {};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, NonParenthesesCharacters) {
    // A função atual ignora caracteres que não sejam '(' ou ')' 
    // devido à estrutura dos condicionais if.
    std::string input = " ( a ) ( b ( c ) ) ";
    std::vector<std::string> expected = {"()", "(())"};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, UnbalancedOpen) {
    // Testa comportamento com parênteses abertos sem fechar
    std::string input = "(()";
    std::vector<std::string> expected = {}; 
    // level nunca volta a 0, então nada é adicionado a all_parens
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, UnbalancedClose) {
    // Testa comportamento com parênteses fechados extras
    std::string input = "())()";
    std::vector<std::string> expected = {"()", "()"};
    EXPECT_EQ(separate_paren_groups(input), expected);
}

TEST(SeparateParenGroupsTest, DeeplyNested) {
    std::string input = "((((()))))";
    std::vector<std::string> expected = {"((((()))))"};
    EXPECT_EQ(separate_paren_groups(input), expected);
}