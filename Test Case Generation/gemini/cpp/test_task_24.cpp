#include <gtest/gtest.h>

/*
 * Função original para teste
 */
int largest_divisor(int n) {
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0) return n / i;
    return 1;
}

/**
 * Suite de testes unitários para a função largest_divisor
 * Foco: Cobertura de linha, números primos, números compostos e edge cases.
 */

// Testa números compostos onde o menor divisor é 2 (resultado deve ser n/2)
TEST(LargestDivisorTest, CompositeNumbersEven) {
    EXPECT_EQ(largest_divisor(4), 2);
    EXPECT_EQ(largest_divisor(10), 5);
    EXPECT_EQ(largest_divisor(100), 50);
}

// Testa números compostos ímpares
TEST(LargestDivisorTest, CompositeNumbersOdd) {
    EXPECT_EQ(largest_divisor(15), 5);
    EXPECT_EQ(largest_divisor(9), 3);
    EXPECT_EQ(largest_divisor(25), 5);
    EXPECT_EQ(largest_divisor(27), 9);
}

// Testa números primos (o maior divisor menor que n deve ser sempre 1)
TEST(LargestDivisorTest, PrimeNumbers) {
    EXPECT_EQ(largest_divisor(2), 1);
    EXPECT_EQ(largest_divisor(3), 1);
    EXPECT_EQ(largest_divisor(7), 1);
    EXPECT_EQ(largest_divisor(13), 1);
    EXPECT_EQ(largest_divisor(101), 1);
}

// Testa o limite superior do loop (i * i == n)
TEST(LargestDivisorTest, PerfectSquares) {
    EXPECT_EQ(largest_divisor(4), 2);
    EXPECT_EQ(largest_divisor(49), 7);
}

// Testa edge cases e valores pequenos conforme a lógica da função
TEST(LargestDivisorTest, EdgeCases) {
    // Para n < 2, o loop não executa, retorna 1
    EXPECT_EQ(largest_divisor(1), 1);
    EXPECT_EQ(largest_divisor(0), 1);
    EXPECT_EQ(largest_divisor(-1), 1);
}

// Testa números grandes para validar performance e correção
TEST(LargestDivisorTest, LargeNumbers) {
    // 100000000 é par, divisor 2 -> 50000000
    EXPECT_EQ(largest_divisor(100000000), 50000000);
    // 999999937 é um número primo conhecido
    EXPECT_EQ(largest_divisor(999999937), 1);
}