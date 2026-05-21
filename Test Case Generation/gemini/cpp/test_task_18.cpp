#include <gtest/gtest.h>
#include <string>

// A função a ser testada
int how_many_times(std::string str, std::string substring) {
    int out = 0;
    if (str.length() == 0) return 0;
    // Nota: str.length() - substring.length() pode resultar em overflow se for negativo 
    // devido ao tipo size_t (unsigned). Contudo, mantemos a lógica original para o teste.
    if (substring.length() > str.length()) return 0;

    for (int i = 0; i <= (int)(str.length() - substring.length()); i++) {
        if (str.substr(i, substring.length()) == substring) {
            out += 1;
        }
    }
    return out;
}

class HowManyTimesTest : public ::testing::Test {};

// Teste de Strings Vazias
TEST_F(HowManyTimesTest, HandlesEmptyStrings) {
    EXPECT_EQ(how_many_times("", "a"), 0);
    EXPECT_EQ(how_many_times("aaa", ""), 0); // Dependendo da semântica, mas seguindo o loop original
    EXPECT_EQ(how_many_times("", ""), 0);
}

// Testes de Casos Básicos (Exemplos do Docstring)
TEST_F(HowManyTimesTest, HandlesBasicCases) {
    EXPECT_EQ(how_many_times("aaa", "a"), 3);
    EXPECT_EQ(how_many_times("aaaa", "aa"), 3);
}

// Teste de Sobreposição (Overlapping)
TEST_F(HowManyTimesTest, HandlesOverlappingSubstrings) {
    EXPECT_EQ(how_many_times("banana", "ana"), 2);
    EXPECT_EQ(how_many_times("aaaaa", "aaa"), 3);
}

// Teste de Substring não encontrada
TEST_F(HowManyTimesTest, SubstringNotFound) {
    EXPECT_EQ(how_many_times("abcdef", "gh"), 0);
    EXPECT_EQ(how_many_times("hello", "world"), 0);
}

// Teste onde a substring é maior que a string original
TEST_F(HowManyTimesTest, SubstringLongerThanString) {
    EXPECT_EQ(how_many_times("a", "aa"), 0);
}

// Teste de correspondência exata
TEST_F(HowManyTimesTest, ExactMatch) {
    EXPECT_EQ(how_many_times("exact", "exact"), 1);
}

// Teste de Case Sensitivity
TEST_F(HowManyTimesTest, CaseSensitivity) {
    EXPECT_EQ(how_many_times("AaaA", "a"), 2);
    EXPECT_EQ(how_many_times("aaaa", "A"), 0);
}

// Teste com caracteres especiais e espaços
TEST_F(HowManyTimesTest, SpecialCharactersAndSpaces) {
    EXPECT_EQ(how_many_times("a b a b a", "a b"), 2);
    EXPECT_EQ(how_many_times("!!!", "!"), 3);
    EXPECT_EQ(how_many_times("! ! !", "! !"), 2);
}