#include <gtest/gtest.h>
#include <string>

// Função a ser testada
int strlen(std::string str) {
    return str.length();
}

/**
 * Suite de testes unitários para a função strlen utilizando Google Test.
 * Foco em 100% de cobertura de linha e tratamento de casos de fronteira.
 */

// Testa o caso base de uma string vazia
TEST(StrLenTest, ReturnsZeroForEmptyString) {
    EXPECT_EQ(strlen(""), 0);
}

// Testa strings com comprimentos variados (caracteres padrão)
TEST(StrLenTest, ReturnsCorrectLengthForStandardStrings) {
    EXPECT_EQ(strlen("a"), 1);
    EXPECT_EQ(strlen("abc"), 3);
    EXPECT_EQ(strlen("Hello World"), 11);
}

// Testa strings que contenham espaços em branco (Leading, Trailing e Internal)
TEST(StrLenTest, HandlesWhitespaceCorrectly) {
    EXPECT_EQ(strlen(" "), 1);
    EXPECT_EQ(strlen("  "), 2);
    EXPECT_EQ(strlen(" a b "), 5);
}

// Testa strings com caracteres especiais e sequências de escape
TEST(StrLenTest, HandlesSpecialCharacters) {
    EXPECT_EQ(strlen("\n\t\r"), 3);
    EXPECT_EQ(strlen("!@#$%^&*()"), 10);
}

// Testa strings que contenham o caractere nulo explicitamente 
// Nota: std::string lida com '\0' se construída corretamente, 
// mas a passagem de literal termina no primeiro nulo.
TEST(StrLenTest, HandlesNullTerminatorInLiteral) {
    // Literais de C terminam no \0, então o comprimento esperado é 3
    EXPECT_EQ(strlen("abc\0def"), 3);
}

// Testa strings de grande dimensão para verificar integridade do tipo de retorno
TEST(StrLenTest, HandlesLargeStrings) {
    std::string largeStr(10000, 'x');
    EXPECT_EQ(strlen(largeStr), 10000);
}

// Testa strings com caracteres numéricos
TEST(StrLenTest, HandlesNumericStrings) {
    EXPECT_EQ(strlen("1234567890"), 10);
}

// Testa caracteres não-ASCII (UTF-8)
// Nota: std::string::length() retorna o número de bytes, não de glifos.
TEST(StrLenTest, HandlesMultibyteUtf8Consistency) {
    // "á" em UTF-8 ocupa 2 bytes
    std::string utf8Str = "á";
    EXPECT_EQ(strlen(utf8Str), 2);
}