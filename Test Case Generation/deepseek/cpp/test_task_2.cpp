#include <gtest/gtest.h>
#include <cmath>
#include <limits>

extern float truncate_number(float number);

TEST(TruncateNumberTest, PositiveInteger) {
    EXPECT_FLOAT_EQ(truncate_number(1.0f), 0.0f);
    EXPECT_FLOAT_EQ(truncate_number(5.0f), 0.0f);
    EXPECT_FLOAT_EQ(truncate_number(100.0f), 0.0f);
}

TEST(TruncateNumberTest, PositiveFractional) {
    EXPECT_FLOAT_EQ(truncate_number(3.5f), 0.5f);
    EXPECT_FLOAT_EQ(truncate_number(2.25f), 0.25f);
    EXPECT_FLOAT_EQ(truncate_number(7.125f), 0.125f);
    EXPECT_FLOAT_EQ(truncate_number(0.75f), 0.75f);
    EXPECT_FLOAT_EQ(truncate_number(0.001f), 0.001f);
}

TEST(TruncateNumberTest, LargeNumbers) {
    EXPECT_FLOAT_EQ(truncate_number(12345.6789f), 0.6789f);
    EXPECT_FLOAT_EQ(truncate_number(1e6f + 0.5f), 0.5f);
    EXPECT_FLOAT_EQ(truncate_number(1e7f - 0.25f), 0.75f);
}

TEST(TruncateNumberTest, VerySmallNumbers) {
    EXPECT_FLOAT_EQ(truncate_number(0.000001f), 0.000001f);
    EXPECT_FLOAT_EQ(truncate_number(1e-7f), 1e-7f);
}

TEST(TruncateNumberTest, EdgeCasesNearIntegers) {
    EXPECT_FLOAT_EQ(truncate_number(1.0f - 1e-7f), 1.0f - 1e-7f);
    EXPECT_FLOAT_EQ(truncate_number(2.0f + 1e-7f), 1e-7f);
    EXPECT_FLOAT_EQ(truncate_number(999.999999f), 0.999999f);
}

TEST(TruncateNumberTest, SpecialFloatingPointValues) {
    EXPECT_FLOAT_EQ(truncate_number(0.0f), 0.0f);
    EXPECT_FLOAT_EQ(truncate_number(1.0f), 0.0f);
    EXPECT_FLOAT_EQ(truncate_number(2.0f), 0.0f);
}

TEST(TruncateNumberTest, PrecisionTest) {
    float num = 3.14159265f;
    float expected = num - static_cast<int>(num);
    EXPECT_FLOAT_EQ(truncate_number(num), expected);
    
    float num2 = 2.718281828f;
    float expected2 = num2 - static_cast<int>(num2);
    EXPECT_FLOAT_EQ(truncate_number(num2), expected2);
}

TEST(TruncateNumberTest, MaxPositiveFloat) {
    float maxFloat = std::numeric_limits<float>::max();
    float integralPart = static_cast<float>(static_cast<int>(maxFloat));
    float expected = maxFloat - integralPart;
    EXPECT_FLOAT_EQ(truncate_number(maxFloat), expected);
}