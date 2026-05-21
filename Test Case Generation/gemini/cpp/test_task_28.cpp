#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

// Função original para teste
string concatenate(vector<string> strings) {
    string out = "";
    for (int i = 0; i < strings.size(); i++)
        out = out + strings[i];
    return out;
}

// Suite de testes unitários
class ConcatenateTest : public ::testing::Test {};

// Teste de caso base: Vetor vazio
TEST_F(ConcatenateTest, HandlesEmptyVector) {
    vector<string> input = {};
    EXPECT_EQ(concatenate(input), "");
}

// Teste de caso base: Vetor com strings simples
TEST_F(ConcatenateTest, HandlesStandardInput) {
    vector<string> input = {"a", "b", "c"};
    EXPECT_EQ(concatenate(input), "abc");
}

// Edge Case: Vetor com uma única string vazia
TEST_F(ConcatenateTest, HandlesSingleEmptyString) {
    vector<string> input = {""};
    EXPECT_EQ(concatenate(input), "");
}

// Edge Case: Vetor com múltiplas strings vazias
TEST_F(ConcatenateTest, HandlesMultipleEmptyStrings) {
    vector<string> input = {"", "", ""};
    EXPECT_EQ(concatenate(input), "");
}

// Edge Case: Strings com espaços e caracteres especiais
TEST_F(ConcatenateTest, HandlesSpacesAndSpecialCharacters) {
    vector<string> input = {"Hello ", "World!", " @2026"};
    EXPECT_EQ(concatenate(input), "Hello World! @2026");
}

// Edge Case: Apenas uma string longa
TEST_F(ConcatenateTest, HandlesSingleElementVector) {
    vector<string> input = {"LongStringWithoutSeparation"};
    EXPECT_EQ(concatenate(input), "LongStringWithoutSeparation");
}

// Edge Case: Strings numéricas
TEST_F(ConcatenateTest, HandlesNumericStrings) {
    vector<string> input = {"1", "2", "3", "4"};
    EXPECT_EQ(concatenate(input), "1234");
}

// Teste de Performance/Volume (Breve)
TEST_F(ConcatenateTest, HandlesLargeNumberOfSmallStrings) {
    vector<string> input(1000, "a");
    string expected(1000, 'a');
    EXPECT_EQ(concatenate(input), expected);
}