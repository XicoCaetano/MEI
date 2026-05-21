#include <gtest/gtest.h>
#include <cmath>

/* 
 * Código a testar (incluído para contexto de compilação)
 */
float truncate_number(float number) {
    return number - int(number);
}

/**
 * Suite de Testes Unitários para truncate_number
 * Focada em precisão de vírgula flutuante e casos de fronteira.
 */

// Teste para garantir que a diferença é tratada corretamente com precisão padrão
TEST(TruncateNumberTest, BasicPositiveNumbers) {
    EXPECT_NEAR(truncate_number(3.5f), 0.5f, 1e-6f);
    EXPECT_NEAR(truncate_number(1.1f), 0.1f, 1e-6f);
    EXPECT_NEAR(truncate_number(123.456f), 0.456f, 1e-5f);
}

// Teste de número inteiro (deve resultar em 0)
TEST(TruncateNumberTest, IntegerNumbers) {
    EXPECT_FLOAT_EQ(truncate_number(1.0f), 0.0f);
    EXPECT_FLOAT_EQ(truncate_number(100.0f), 0.0f);
    EXPECT_FLOAT_EQ(truncate_number(0.0f), 0.0f);
}

// Teste de valores menores que 1
TEST(TruncateNumberTest, ValuesLessThanOne) {
    EXPECT_FLOAT_EQ(truncate_number(0.123f), 0.123f);
    EXPECT_FLOAT_EQ(truncate_number(0.0001f), 0.0001f);
}

// Teste de números grandes para verificar comportamento do cast para int
TEST(TruncateNumberTest, LargeNumbers) {
    // Nota: O comportamento depende do limite do tipo 'int' no sistema
    EXPECT_NEAR(truncate_number(12345.678f), 0.678f, 1e-3f);
}

// Teste de comportamento com números negativos 
// (Embora o requisito mencione "positive floating point", um QA sénior valida a robustez)
TEST(TruncateNumberTest, NegativeNumbers) {
    // int(-3.5) é -3 -> -3.5 - (-3) = -0.5
    EXPECT_NEAR(truncate_number(-3.5f), -0.5f, 1e-6f);
}

// Teste de precisão extrema
TEST(TruncateNumberTest, HighPrecisionEdgeCase) {
    float val = 0.999999f;
    EXPECT_FLOAT_EQ(truncate_number(val), 0.999999f);
}