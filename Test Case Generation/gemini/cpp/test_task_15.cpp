#include <gtest/gtest.h>
#include <string>

// Função a ser testada
std::string string_sequence(int n) {
    std::string out = "0";
    for (int i = 1; i <= n; i++)
        out = out + " " + std::to_string(i);
    return out;
}

/**
 * Suite de Testes Unitários para string_sequence
 */

// Testa o limite inferior (n = 0)
TEST(StringSequenceTest, HandlesZeroInput) {
    EXPECT_EQ(string_sequence(0), "0");
}

// Testa um valor pequeno positivo
TEST(StringSequenceTest, HandlesSmallPositiveInput) {
    EXPECT_EQ(string_sequence(1), "0 1");
    EXPECT_EQ(string_sequence(2), "0 1 2");
}

// Testa um valor médio para garantir a formatação correta de espaços
TEST(StringSequenceTest, HandlesStandardSequence) {
    EXPECT_EQ(string_sequence(5), "0 1 2 3 4 5");
}

// Testa o comportamento com números negativos (Edge Case)
// De acordo com a lógica atual (i=1; i<=n), o loop não deve executar se n < 1.
TEST(StringSequenceTest, HandlesNegativeInput) {
    EXPECT_EQ(string_sequence(-1), "0");
    EXPECT_EQ(string_sequence(-100), "0");
}

// Testa a transição para múltiplos dígitos
TEST(StringSequenceTest, HandlesMultiDigitNumbers) {
    std::string result = string_sequence(10);
    std::string expected = "0 1 2 3 4 5 6 7 8 9 10";
    EXPECT_EQ(result, expected);
}

// Teste de stress leve para verificar consistência em sequências maiores
TEST(StringSequenceTest, HandlesLargerInput) {
    int n = 20;
    std::string result = string_sequence(n);
    
    // Verifica se começa com 0 e termina com 20
    EXPECT_TRUE(result.find("0 ") == 0);
    EXPECT_TRUE(result.substr(result.length() - 3) == " 20");
    
    // Conta o número de espaços para validar a quantidade de elementos (n espaços para n+1 elementos)
    int spaces = 0;
    for(char c : result) if(c == ' ') spaces++;
    EXPECT_EQ(spaces, n);
}