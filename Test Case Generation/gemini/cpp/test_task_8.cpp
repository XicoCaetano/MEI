#include <gtest/gtest.h>
#include <vector>

// Função a ser testada
std::vector<int> sum_product(std::vector<int> numbers) {
    int sum = 0, product = 1;
    for (int i = 0; i < (int)numbers.size(); i++) {
        sum += numbers[i];
        product *= numbers[i];
    }
    return {sum, product};
}

// Teste para caso de vetor vazio (Edge Case)
TEST(SumProductTest, EmptyVector) {
    std::vector<int> input = {};
    std::vector<int> expected = {0, 1};
    EXPECT_EQ(sum_product(input), expected);
}

// Teste com elementos positivos (Caso Comum)
TEST(SumProductTest, PositiveNumbers) {
    std::vector<int> input = {1, 2, 3, 4};
    std::vector<int> expected = {10, 24};
    EXPECT_EQ(sum_product(input), expected);
}

// Teste com um único elemento (Edge Case)
TEST(SumProductTest, SingleElement) {
    std::vector<int> input = {5};
    std::vector<int> expected = {5, 5};
    EXPECT_EQ(sum_product(input), expected);
}

// Teste com o número zero (Impacto no produto)
TEST(SumProductTest, IncludingZero) {
    std::vector<int> input = {0, 1, 2, 3};
    std::vector<int> expected = {6, 0};
    EXPECT_EQ(sum_product(input), expected);
}

// Teste com números negativos
TEST(SumProductTest, NegativeNumbers) {
    std::vector<int> input = {-1, -2, 3};
    std::vector<int> expected = {0, 6};
    EXPECT_EQ(sum_product(input), expected);
}

// Teste com múltiplos zeros
TEST(SumProductTest, MultipleZeros) {
    std::vector<int> input = {0, 0, 0};
    std::vector<int> expected = {0, 0};
    EXPECT_EQ(sum_product(input), expected);
}

// Teste com valores grandes (Verificação de sanidade)
TEST(SumProductTest, LargerValues) {
    std::vector<int> input = {10, 20, 30};
    std::vector<int> expected = {60, 6000};
    EXPECT_EQ(sum_product(input), expected);
}