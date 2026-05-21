#include <gtest/gtest.h>
#include <vector>

// Função a testar
std::vector<int> factorize(int n) {
    std::vector<int> out = {};
    for (int i = 2; i * i <= n; i++)
        if (n % i == 0)
        {
            n = n / i;
            out.push_back(i);
            i -= 1;
        }
    out.push_back(n);
    return out;
}

// Suite de Testes Unitários
class FactorizeTest : public ::testing::Test {};

TEST_F(FactorizeTest, HandlesPrimeNumbers) {
    EXPECT_EQ(factorize(2), std::vector<int>({2}));
    EXPECT_EQ(factorize(3), std::vector<int>({3}));
    EXPECT_EQ(factorize(7), std::vector<int>({7}));
    EXPECT_EQ(factorize(13), std::vector<int>({13}));
}

TEST_F(FactorizeTest, HandlesPerfectPowers) {
    EXPECT_EQ(factorize(4), std::vector<int>({2, 2}));
    EXPECT_EQ(factorize(8), std::vector<int>({2, 2, 2}));
    EXPECT_EQ(factorize(9), std::vector<int>({3, 3}));
    EXPECT_EQ(factorize(25), std::vector<int>({5, 5}));
    EXPECT_EQ(factorize(27), std::vector<int>({3, 3, 3}));
}

TEST_F(FactorizeTest, HandlesCompositeNumbers) {
    EXPECT_EQ(factorize(6), std::vector<int>({2, 3}));
    EXPECT_EQ(factorize(10), std::vector<int>({2, 5}));
    EXPECT_EQ(factorize(70), std::vector<int>({2, 5, 7}));
    EXPECT_EQ(factorize(100), std::vector<int>({2, 2, 5, 5}));
}

TEST_F(FactorizeTest, HandlesLargePrimesAndProducts) {
    // 323 = 17 * 19
    EXPECT_EQ(factorize(323), std::vector<int>({17, 19}));
    // Teste com um primo maior para garantir que o loop termina corretamente
    EXPECT_EQ(factorize(997), std::vector<int>({997}));
}

TEST_F(FactorizeTest, LineCoverageEdgeCases) {
    // Testa o limite i*i <= n quando i*i == n
    EXPECT_EQ(factorize(49), std::vector<int>({7, 7}));
    // Garante que o push_back final de 'n' ocorre após o loop esgotar
    EXPECT_EQ(factorize(2), std::vector<int>({2}));
}

TEST_F(FactorizeTest, HandlesExampleCases) {
    EXPECT_EQ(factorize(8), std::vector<int>({2, 2, 2}));
    EXPECT_EQ(factorize(25), std::vector<int>({5, 5}));
    EXPECT_EQ(factorize(70), std::vector<int>({2, 5, 7}));
}