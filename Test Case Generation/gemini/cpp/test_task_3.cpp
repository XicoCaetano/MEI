#include <gtest/gtest.h>
#include <vector>

using namespace std;

// Função a testar
bool below_zero(vector<int> operations) {
    int num = 0;
    for (int i = 0; i < operations.size(); i++) {
        num += operations[i];
        if (num < 0) return true;
    }
    return false;
}

// Teste para garantir que um vetor vazio retorna falso (balanço inicial é 0)
TEST(BelowZeroTest, EmptyOperations) {
    EXPECT_FALSE(below_zero({}));
}

// Teste com operações positivas que nunca descem abaixo de zero
TEST(BelowZeroTest, AllPositiveOperations) {
    EXPECT_FALSE(below_zero({1, 2, 3, 10}));
}

// Teste com balanço que chega a zero, mas nunca fica negativo
TEST(BelowZeroTest, ReachesZeroButNotBelow) {
    EXPECT_FALSE(below_zero({10, -5, -5}));
    EXPECT_FALSE(below_zero({0, 0, 0}));
}

// Teste onde o balanço cai abaixo de zero no meio das operações
TEST(BelowZeroTest, DropsBelowZeroInMiddle) {
    EXPECT_TRUE(below_zero({1, 2, -4, 5}));
}

// Teste onde o balanço cai abaixo de zero logo na primeira operação
TEST(BelowZeroTest, StartsBelowZero) {
    EXPECT_TRUE(below_zero({-1, 10, 10}));
}

// Teste onde o balanço cai abaixo de zero apenas na última operação
TEST(BelowZeroTest, DropsBelowZeroAtEnd) {
    EXPECT_TRUE(below_zero({10, -5, -6}));
}

// Teste com valores grandes (Boundary conditions)
TEST(BelowZeroTest, LargeValues) {
    EXPECT_FALSE(below_zero({1000000, -500000, -499999}));
    EXPECT_TRUE(below_zero({1000000, -2000000}));
}

// Teste de sequência complexa que flutua sem atingir negativo
TEST(BelowZeroTest, ComplexFluctuationStayPositive) {
    EXPECT_FALSE(below_zero({10, -9, 5, -3, 2, -1}));
}

// Teste de sequência complexa que eventualmente atinge negativo
TEST(BelowZeroTest, ComplexFluctuationHitNegative) {
    EXPECT_TRUE(below_zero({5, -2, -2, -2, 10}));
}