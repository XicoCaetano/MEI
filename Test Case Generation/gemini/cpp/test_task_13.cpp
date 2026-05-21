#include <gtest/gtest.h>

// Função a ser testada
int greatest_common_divisor(int a, int b){
    int out,m;
    while (true){
        if (a<b) 
        {
            m=a;a=b;b=m;
        }
        a=a%b;
        if (a==0) return b;
    }
}

// Suite de Testes Unitários
class GCDTest : public ::testing::Test {};

// Teste de casos base fornecidos na documentação
TEST_F(GCDTest, HandlesBasicExamples) {
    EXPECT_EQ(greatest_common_divisor(3, 5), 1);
    EXPECT_EQ(greatest_common_divisor(25, 15), 5);
}

// Teste de permutação (a < b) para garantir cobertura do bloco de swap
TEST_F(GCDTest, HandlesSwappedInputs) {
    EXPECT_EQ(greatest_common_divisor(15, 25), 5);
    EXPECT_EQ(greatest_common_divisor(7, 49), 7);
}

// Teste com números primos
TEST_F(GCDTest, HandlesPrimeNumbers) {
    EXPECT_EQ(greatest_common_divisor(13, 17), 1);
    EXPECT_EQ(greatest_common_divisor(2, 3), 1);
}

// Teste onde um número é múltiplo do outro
TEST_F(GCDTest, HandlesMultiples) {
    EXPECT_EQ(greatest_common_divisor(100, 10), 10);
    EXPECT_EQ(greatest_common_divisor(10, 100), 10);
}

// Teste com números iguais
TEST_F(GCDTest, HandlesEqualNumbers) {
    EXPECT_EQ(greatest_common_divisor(42, 42), 42);
}

// Teste de Edge Cases: Um dos valores é 1
TEST_F(GCDTest, HandlesUnitValue) {
    EXPECT_EQ(greatest_common_divisor(1, 500), 1);
    EXPECT_EQ(greatest_common_divisor(500, 1), 1);
}

// Teste de números grandes (Stress test básico)
TEST_F(GCDTest, HandlesLargeNumbers) {
    EXPECT_EQ(greatest_common_divisor(1071, 462), 21);
    EXPECT_EQ(greatest_common_divisor(2147483647, 2147483647), 2147483647);
}

// Teste de cobertura de fluxo: Garante que o loop while(true) executa múltiplas vezes
TEST_F(GCDTest, HandlesMultipleIterations) {
    // 48, 18 -> (48,18) -> 48%18=12 -> (18,12) -> 18%12=6 -> (12,6) -> 12%6=0 -> return 6
    EXPECT_EQ(greatest_common_divisor(48, 18), 6);
}