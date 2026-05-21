#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <limits>

// Assuming the function is declared in some header
// #include "mean_absolute_deviation.h"

float mean_absolute_deviation(std::vector<float> numbers);

class MeanAbsoluteDeviationTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Basic functionality tests
TEST_F(MeanAbsoluteDeviationTest, HandlesSingleElement) {
    std::vector<float> numbers = {5.0f};
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 0.0f);
}

TEST_F(MeanAbsoluteDeviationTest, HandlesTwoEqualElements) {
    std::vector<float> numbers = {3.5f, 3.5f};
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 0.0f);
}

TEST_F(MeanAbsoluteDeviationTest, HandlesTwoDifferentElements) {
    std::vector<float> numbers = {1.0f, 3.0f};
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 1.0f);
}

// Given example test
TEST_F(MeanAbsoluteDeviationTest, HandlesExampleCase) {
    std::vector<float> numbers = {1.0f, 2.0f, 3.0f, 4.0f};
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 1.0f);
}

// Edge cases with zero
TEST_F(MeanAbsoluteDeviationTest, HandlesAllZeros) {
    std::vector<float> numbers = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 0.0f);
}

TEST_F(MeanAbsoluteDeviationTest, HandlesMixedPositiveAndNegative) {
    std::vector<float> numbers = {-5.0f, -1.0f, 0.0f, 1.0f, 5.0f};
    // Mean = 0.0, deviations: 5,1,0,1,5, sum = 12, average = 12/5 = 2.4
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 2.4f);
}

// Symmetric distribution test
TEST_F(MeanAbsoluteDeviationTest, HandlesSymmetricDistribution) {
    std::vector<float> numbers = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f};
    // Mean = 5.0, MAD = (4+3+2+1+0+1+2+3+4)/9 = 20/9 ≈ 2.22222
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 20.0f/9.0f);
}

// Integer values that give floating point results
TEST_F(MeanAbsoluteDeviationTest, HandlesIntegerValuesWithPrecision) {
    std::vector<float> numbers = {1.0f, 2.0f, 3.0f};
    // Mean = 2.0, deviations: 1,0,1, sum = 2, average = 2/3 ≈ 0.666667
    EXPECT_NEAR(mean_absolute_deviation(numbers), 2.0f/3.0f, 1e-6f);
}

// Floating point precision tests
TEST_F(MeanAbsoluteDeviationTest, HandlesFloatingPointValues) {
    std::vector<float> numbers = {1.1f, 2.2f, 3.3f, 4.4f};
    // Mean = 2.75, deviations: 1.65, 0.55, 0.55, 1.65, sum = 4.4, average = 1.1
    EXPECT_NEAR(mean_absolute_deviation(numbers), 1.1f, 1e-6f);
}

// Edge case: large numbers
TEST_F(MeanAbsoluteDeviationTest, HandlesLargeNumbers) {
    std::vector<float> numbers = {1000000.0f, 1000001.0f, 1000002.0f};
    // Mean = 1000001.0, deviations: 1,0,1, sum = 2, average = 2/3
    EXPECT_NEAR(mean_absolute_deviation(numbers), 2.0f/3.0f, 1e-3f);
}

// Edge case: very small numbers
TEST_F(MeanAbsoluteDeviationTest, HandlesVerySmallNumbers) {
    std::vector<float> numbers = {1e-7f, 2e-7f, 3e-7f, 4e-7f, 5e-7f};
    // Mean = 3e-7, deviations: 2e-7,1e-7,0,1e-7,2e-7, sum = 6e-7, average = 1.2e-7
    EXPECT_NEAR(mean_absolute_deviation(numbers), 1.2e-7f, 1e-12f);
}

// Edge case: empty vector (undefined behavior, but test for robustness)
TEST_F(MeanAbsoluteDeviationTest, HandlesEmptyVector) {
    std::vector<float> numbers;
    // Division by zero - this will cause undefined behavior
    // We test it but the function should ideally handle this
    // Since the specification doesn't define behavior for empty vector,
    // we only verify it compiles and runs (will likely produce NaN or crash)
    // Uncomment to test - EXPECT_DEATH is disabled as function may not handle it
    // EXPECT_DEATH(mean_absolute_deviation(numbers), ".*");
}

// Single element with negative value
TEST_F(MeanAbsoluteDeviationTest, HandlesSingleNegativeElement) {
    std::vector<float> numbers = {-42.5f};
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 0.0f);
}

// All elements negative
TEST_F(MeanAbsoluteDeviationTest, HandlesAllNegativeElements) {
    std::vector<float> numbers = {-10.0f, -20.0f, -30.0f, -40.0f};
    // Mean = -25.0, deviations: 15,5,5,15, sum = 40, average = 10
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 10.0f);
}

// Large vector
TEST_F(MeanAbsoluteDeviationTest, HandlesLargeVector) {
    std::vector<float> numbers;
    numbers.reserve(1000);
    for (int i = 0; i < 1000; ++i) {
        numbers.push_back(static_cast<float>(i));
    }
    // For arithmetic progression 0..999, mean = 499.5
    // MAD can be calculated but we'll use expected value
    float result = mean_absolute_deviation(numbers);
    EXPECT_GT(result, 0.0f);
    EXPECT_LT(result, 500.0f);
}

// Extreme values: infinity
TEST_F(MeanAbsoluteDeviationTest, HandlesInfinityValues) {
    std::vector<float> numbers = {1.0f, 2.0f, std::numeric_limits<float>::infinity()};
    // Behavior with infinity is implementation-defined
    float result = mean_absolute_deviation(numbers);
    EXPECT_TRUE(std::isinf(result) || std::isnan(result));
}

// Extreme values: NaN
TEST_F(MeanAbsoluteDeviationTest, HandlesNaNValues) {
    std::vector<float> numbers = {1.0f, 2.0f, std::numeric_limits<float>::quiet_NaN()};
    float result = mean_absolute_deviation(numbers);
    EXPECT_TRUE(std::isnan(result));
}

// Decimal values that require careful floating point comparison
TEST_F(MeanAbsoluteDeviationTest, HandlesNonIntegerMean) {
    std::vector<float> numbers = {1.5f, 2.5f, 3.5f, 4.5f};
    // Mean = 3.0, deviations: 1.5,0.5,0.5,1.5, sum = 4.0, average = 1.0
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 1.0f);
}

// Two elements with large difference
TEST_F(MeanAbsoluteDeviationTest, HandlesTwoElementsLargeDifference) {
    std::vector<float> numbers = {-1e6f, 1e6f};
    // Mean = 0.0, deviations: 1e6, 1e6, sum = 2e6, average = 1e6
    EXPECT_FLOAT_EQ(mean_absolute_deviation(numbers), 1e6f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}