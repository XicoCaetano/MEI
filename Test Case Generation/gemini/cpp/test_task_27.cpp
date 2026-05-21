#include <gtest/gtest.h>
#include <string>

// Função a ser testada
std::string flip_case(std::string str) {
    std::string out = "";
    for (int i = 0; i < str.length(); i++) {
        char w = str[i];
        if (w >= 97 && w <= 122) {
            w -= 32;
        } else if (w >= 65 && w <= 90) {
            w += 32;
        }
        out = out + w;
    }
    return out;
}

// Suite de Testes Unitários
class FlipCaseTest : public ::testing::Test {};

// Testa strings vazias (Edge Case)
TEST_F(FlipCaseTest, HandlesEmptyString) {
    EXPECT_EQ(flip_case(""), "");
}

// Testa transformação de minúsculas para maiúsculas (Line Coverage: if block)
TEST_F(FlipCaseTest, ConvertsLowercaseToUppercase) {
    EXPECT_EQ(flip_case("abc"), "ABC");
    EXPECT_EQ(flip_case("z"), "Z");
}

// Testa transformação de maiúsculas para minúsculas (Line Coverage: else if block)
TEST_F(FlipCaseTest, ConvertsUppercaseToLowercase) {
    EXPECT_EQ(flip_case("ABC"), "abc");
    EXPECT_EQ(flip_case("Z"), "z");
}

// Testa strings com mistura de casos
TEST_F(FlipCaseTest, HandlesMixedCase) {
    EXPECT_EQ(flip_case("Hello World"), "hELLO wORLD");
    EXPECT_EQ(flip_case("tEsTInG"), "TeStinG");
}

// Testa caracteres não alfabéticos (Line Coverage: bypass both conditions)
TEST_F(FlipCaseTest, IgnoresNonAlphabeticCharacters) {
    EXPECT_EQ(flip_case("123!@#"), "123!@#");
    EXPECT_EQ(flip_case(" "), " ");
    EXPECT_EQ(flip_case("C++ 2026!"), "c++ 2026!");
}

// Testa limites exatos da tabela ASCII (Edge Cases)
TEST_F(FlipCaseTest, HandlesAsciiBoundaries) {
    // 'a' = 97, 'z' = 122
    EXPECT_EQ(flip_case("az"), "AZ");
    // 'A' = 65, 'Z' = 90
    EXPECT_EQ(flip_case("AZ"), "az");
    // Caracteres imediatamente antes e depois dos intervalos
    EXPECT_EQ(flip_case("@"), "@"); // ASCII 64
    EXPECT_EQ(flip_case("["), "["); // ASCII 91
    EXPECT_EQ(flip_case("`"), "`"); // ASCII 96
    EXPECT_EQ(flip_case("{"), "{"); // ASCII 123
}

// Testa strings longas
TEST_F(FlipCaseTest, HandlesLongStrings) {
    std::string input(1000, 'a');
    std::string expected(1000, 'A');
    EXPECT_EQ(flip_case(input), expected);
}