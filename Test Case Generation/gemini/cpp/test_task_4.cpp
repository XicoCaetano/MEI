#include <gtest/gtest.h>
#include <vector>
#include <cmath>

// Protótipo da função a testar
float mean_absolute_deviation(std::vector<float> numbers);

// Teste de um caso padrão positivo (conforme exemplo fornecido)
TEST(MeanAbsoluteDeviationTest, BasicExample) {
    std::vector<float> numbers = {1.0, 2.0, 3.0, 4.0};
    // Média = 2.5
    // Desvios: |1-2.5|=1.5, |2-2.5|=0.5, |3-2.5|=0.5, |4-2.5|=1.5
    // Soma desvios = 4.0. MAD = 4.0 / 4 = 1.0
    EXPECT_NEAR(mean_absolute_deviation(numbers), 1.0f, 1e-5);
}

// Teste com todos os elementos iguais (Desvio deve ser zero)
TEST(MeanAbsoluteDeviationTest, IdenticalElements) {
    std::vector<float> numbers = {5.0, 5.0, 5.0, 5.0, 5.0};
    EXPECT_NEAR(mean_absolute_deviation(numbers), 0.0f, 1e-5);
}

// Teste com apenas um elemento
TEST(MeanAbsoluteDeviationTest, SingleElement) {
    std::vector<float> numbers = {10.0};
    EXPECT_NEAR(mean_absolute_deviation(numbers), 0.0f, 1e-5);
}

// Teste com números negativos e positivos
TEST(MeanAbsoluteDeviationTest, MixedSignNumbers) {
    std::vector<float> numbers = {-10.0, 10.0};
    // Média = 0
    // Desvios: |-10-0|=10, |10-0|=10
    // MAD = 20 / 2 = 10
    EXPECT_NEAR(mean_absolute_deviation(numbers), 10.0f, 1e-5);
}

// Teste com valores decimais pequenos
TEST(MeanAbsoluteDeviationTest, SmallDecimals) {
    std::vector<float> numbers = {0.1, 0.2, 0.3};
    // Média = 0.2
    // Desvios: 0.1, 0.0, 0.1
    // MAD = 0.2 / 3 = 0.066666...
    EXPECT_NEAR(mean_absolute_deviation(numbers), 0.0666666f, 1e-5);
}

// Teste de robustez: Vetor vazio
// Nota: A implementação original causaria divisão por zero (NaN).
// Como Engenheiro de Qualidade, este teste valida o comportamento atual do sistema.
TEST(MeanAbsoluteDeviationTest, EmptyVectorTriggeringDivisionByZero) {
    std::vector<float> numbers = {};
    float result = mean_absolute_deviation(numbers);
    EXPECT_TRUE(std::isnan(result));
}

// Teste com grandes valores para verificar precisão de float
TEST(MeanAbsoluteDeviationTest, LargeValues) {
    std::vector<float> numbers = {1000000.0, 2000000.0};
    // Média = 1500000.0
    // Desvios: 500000.0, 500000.0
    // MAD = 1000000.0 / 2 = 500000.0
    EXPECT_NEAR(mean_absolute_deviation(numbers), 500000.0f, 1e-1);
}