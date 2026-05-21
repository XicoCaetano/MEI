#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <algorithm>

// Protótipo da função conforme fornecido
std::vector<float> find_closest_elements(std::vector<float> numbers);

// Teste para o exemplo básico fornecido na documentação
TEST(FindClosestElementsTest, BasicExample) {
    std::vector<float> input = {1.0, 2.0, 3.0, 4.0, 5.0, 2.2};
    std::vector<float> expected = {2.0, 2.2};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

// Teste para elementos idênticos
TEST(FindClosestElementsTest, DuplicateElements) {
    std::vector<float> input = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    std::vector<float> expected = {2.0, 2.0};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

// Teste com o tamanho mínimo permitido (dois elementos)
TEST(FindClosestElementsTest, MinimumInputSize) {
    std::vector<float> input = {10.5, 5.5};
    std::vector<float> expected = {5.5, 10.5};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

// Teste para garantir a ordenação (o par já está ordenado no input)
TEST(FindClosestElementsTest, AlreadySortedOutput) {
    std::vector<float> input = {1.0, 1.1, 5.0};
    std::vector<float> expected = {1.0, 1.1};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

// Teste para garantir a ordenação (o par precisa ser invertido)
TEST(FindClosestElementsTest, UnsortedOutputReversal) {
    std::vector<float> input = {5.0, 1.1, 1.0};
    std::vector<float> expected = {1.0, 1.1};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

// Teste com números negativos
TEST(FindClosestElementsTest, NegativeNumbers) {
    std::vector<float> input = {-10.0, -20.0, -10.5, -5.0};
    std::vector<float> expected = {-10.5, -10.0};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

// Teste com números decimais muito próximos (precisão de float)
TEST(FindClosestElementsTest, HighPrecision) {
    std::vector<float> input = {1.00001, 2.0, 1.00002, 3.0};
    std::vector<float> expected = {1.00001, 1.00002};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_NEAR(result[0], expected[0], 1e-6);
    EXPECT_NEAR(result[1], expected[1], 1e-6);
}

// Teste com elementos em extremos opostos e par próximo no meio
TEST(FindClosestElementsTest, DistantExtremesWithCloseMiddle) {
    std::vector<float> input = {-1000.0, 0.0, 0.01, 1000.0};
    std::vector<float> expected = {0.0, 0.01};
    std::vector<float> result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}