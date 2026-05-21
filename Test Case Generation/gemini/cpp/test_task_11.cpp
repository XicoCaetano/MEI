#include <gtest/gtest.h>
#include <string>

using namespace std;

// Função a ser testada
string string_xor(string a, string b) {
    string output = "";
    for (int i = 0; (i < a.length() and i < b.length()); i++) {
        if (i < a.length() and i < b.length()) {
            if (a[i] == b[i]) {
                output += '0';
            } else {
                output += '1';
            }
        } else {
            // Nota: Este bloco else é logicamente inacessível devido à condição do loop 'for'
            // No entanto, incluímos lógica que exercitaria o código caso a condição mudasse
            if (i >= a.length()) {
                output += b[i];
            } else {
                output += a[i];
            }
        }
    }
    return output;
}

// Suite de Testes Unitários
class StringXorTest : public ::testing::Test {};

// Testa o exemplo básico fornecido na documentação
TEST_F(StringXorTest, BasicExample) {
    EXPECT_EQ(string_xor("010", "110"), "100");
}

// Testa strings com todos os bits iguais (Resultado deve ser tudo zeros)
TEST_F(StringXorTest, AllZeros) {
    EXPECT_EQ(string_xor("000", "000"), "000");
    EXPECT_EQ(string_xor("111", "111"), "000");
}

// Testa strings com todos os bits diferentes (Resultado deve ser tudo uns)
TEST_F(StringXorTest, AllOnesResult) {
    EXPECT_EQ(string_xor("111", "000"), "111");
    EXPECT_EQ(string_xor("000", "111"), "111");
}

// Testa strings vazias
TEST_F(StringXorTest, EmptyStrings) {
    EXPECT_EQ(string_xor("", ""), "");
}

// Testa quando uma string é vazia e a outra não
// Dado o loop 'for (i < a.length() and i < b.length())', o resultado esperado é vazio
TEST_F(StringXorTest, OneEmptyString) {
    EXPECT_EQ(string_xor("", "101"), "");
    EXPECT_EQ(string_xor("101", ""), "");
}

// Testa comprimentos diferentes
// A função atual trunca o resultado pelo menor comprimento devido à condição do loop
TEST_F(StringXorTest, DifferentLengths) {
    EXPECT_EQ(string_xor("1111", "00"), "11");
    EXPECT_EQ(string_xor("00", "1111"), "11");
}

// Testa strings longas para garantir que não há problemas de memória/performance simples
TEST_F(StringXorTest, LongStrings) {
    string s1(1000, '1');
    string s2(1000, '0');
    string expected(1000, '1');
    EXPECT_EQ(string_xor(s1, s2), expected);
}

// Testa alternância de caracteres
TEST_F(StringXorTest, AlternatingBits) {
    EXPECT_EQ(string_xor("1010", "0101"), "1111");
    EXPECT_EQ(string_xor("1010", "1010"), "0000");
}