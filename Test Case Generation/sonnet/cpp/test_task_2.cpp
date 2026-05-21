#include <gtest/gtest.h>
#include <cmath>

float truncate_number(float number) {
    return number - int(number);
}

TEST(TruncateNumberTest, BasicDecimal) {
    EXPECT_FLOAT_EQ(truncate_number(3.5f), 0.5f);
}

TEST(TruncateNumberTest, SmallDecimal) {
    EXPECT_NEAR(truncate_number(1.1f), 0.1f, 1e-6f);
}

TEST(TruncateNumberTest, LargeDecimal) {
    EXPECT_NEAR(truncate_number(2.9f), 0.9f, 1e-6f);
}

TEST(TruncateNumberTest, NoDecimalPart) {
    EXPECT_FLOAT_EQ(truncate_number(5.0f), 0.0f);
}

TEST(TruncateNumberTest, OnePointZero) {
    EXPECT_FLOAT_EQ(truncate_number(1.0f), 0.0f);
}

TEST(TruncateNumberTest, SmallNumber) {
    EXPECT_NEAR(truncate_number(0.5f), 0.5f, 1e-6f);
}

TEST(TruncateNumberTest, VerySmallDecimal) {
    EXPECT_NEAR(truncate_number(10.01f), 0.01f, 1e-4f);
}

TEST(TruncateNumberTest, AlmostWholeNumber) {
    EXPECT_NEAR(truncate_number(7.99f), 0.99f, 1e-5f);
}

TEST(TruncateNumberTest, LargeNumber) {
    EXPECT_NEAR(truncate_number(1000.75f), 0.75f, 1e-4f);
}

TEST(TruncateNumberTest, DecimalOnlyNumber) {
    EXPECT_NEAR(truncate_number(0.25f), 0.25f, 1e-6f);
}

TEST(TruncateNumberTest, DecimalPartIsAlwaysLessThanOne) {
    float result = truncate_number(42.999f);
    EXPECT_LT(result, 1.0f);
    EXPECT_GE(result, 0.0f);
}

TEST(TruncateNumberTest, DecimalPartBoundaryLow) {
    float result = truncate_number(3.0001f);
    EXPECT_GE(result, 0.0f);
    EXPECT_LT(result, 1.0f);
}

TEST(TruncateNumberTest, ResultNeverNegativeForPositiveInput) {
    EXPECT_GE(truncate_number(1.5f), 0.0f);
    EXPECT_GE(truncate_number(100.3f), 0.0f);
    EXPECT_GE(truncate_number(0.9f), 0.0f);
}

TEST(TruncateNumberTest, IntegerPartStripped) {
    float val = 99.6f;
    float result = truncate_number(val);
    EXPECT_LT(result, 1.0f);
    EXPECT_NEAR(result, 0.6f, 1e-5f);
}

TEST(TruncateNumberTest, QuarterDecimal) {
    EXPECT_NEAR(truncate_number(4.25f), 0.25f, 1e-6f);
}

TEST(TruncateNumberTest, ThreeQuarterDecimal) {
    EXPECT_NEAR(truncate_number(8.75f), 0.75f, 1e-6f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}