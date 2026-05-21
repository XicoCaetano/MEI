#include <gtest/gtest.h>
#include <vector>
#include <cmath>

// A função original fornecida para teste
std::vector<float> rescale_to_unit(std::vector<float> numbers) { 
    float min = 100000, max = -100000;
    for (int i = 0; i < numbers.size(); i++)
    {
        if (numbers[i] < min) min = numbers[i];
        if (numbers[i] > max) max = numbers[i];
    }
    for (int i = 0; i < numbers.size(); i++)
        numbers[i] = (numbers[i] - min) / (max - min);
    return numbers;
}

// Suite de testes unitários
class RescaleToUnitTest : public ::testing::Test {
protected:
    const float abs_error = 1e-5;
};

TEST_F(RescaleToUnitTest, BasicExample) {
    std::vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    std::vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    std::vector<float> result = rescale_to_unit(input);
    
    ASSERT_EQ(result.size(), expected.size());
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], abs_error);
    }
}

TEST_F(RescaleToUnitTest, TwoElementsMinMax) {
    std::vector<float> input = {10.0f, 20.0f};
    std::vector<float> expected = {0.0f, 1.0f};
    std::vector<float> result = rescale_to_unit(input);
    
    EXPECT_NEAR(result[0], expected[0], abs_error);
    EXPECT_NEAR(result[1], expected[1], abs_error);
}

TEST_F(RescaleToUnitTest, NegativeNumbers) {
    std::vector<float> input = {-10.0f, -5.0f, 0.0f};
    std::vector<float> expected = {0.0f, 0.5f, 1.0f};
    std::vector<float> result = rescale_to_unit(input);
    
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], abs_error);
    }
}

TEST_F(RescaleToUnitTest, LargeValuesBeyondInitialMinMax) {
    // Testa se a função lida com valores fora do range hardcoded de 100000/-100000
    std::vector<float> input = {-200000.0f, 200000.0f};
    std::vector<float> expected = {0.0f, 1.0f};
    std::vector<float> result = rescale_to_unit(input);
    
    EXPECT_NEAR(result[0], expected[0], abs_error);
    EXPECT_NEAR(result[1], expected[1], abs_error);
}

TEST_F(RescaleToUnitTest, UnorderedInput) {
    std::vector<float> input = {5.0f, 1.0f, 3.0f, 2.0f, 4.0f};
    std::vector<float> expected = {1.0f, 0.0f, 0.5f, 0.25f, 0.75f};
    std::vector<float> result = rescale_to_unit(input);
    
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_NEAR(result[i], expected[i], abs_error);
    }
}

TEST_F(RescaleToUnitTest, AllElementsSameProducesNaN) {
    // Quando todos os elementos são iguais, max - min = 0, resultando em divisão por zero (NaN)
    // Este teste garante cobertura de linha e verifica o comportamento atual da implementação
    std::vector<float> input = {10.0f, 10.0f};
    std::vector<float> result = rescale_to_unit(input);
    
    for (float val : result) {
        EXPECT_TRUE(std::isnan(val));
    }
}

TEST_F(RescaleToUnitTest, ValuesCloseToZero) {
    std::vector<float> input = {0.001f, 0.002f};
    std::vector<float> expected = {0.0f, 1.0f};
    std::vector<float> result = rescale_to_unit(input);
    
    EXPECT_NEAR(result[0], expected[0], abs_error);
    EXPECT_NEAR(result[1], expected[1], abs_error);
}