#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <limits>

using namespace std;

// Include the function to test (in real scenario, this would be in a header)
vector<float> find_closest_elements(vector<float> numbers);

TEST(FindClosestElementsTest, BasicFunctionality) {
    vector<float> input = {1.0, 2.0, 3.0, 4.0, 5.0, 2.2};
    vector<float> expected = {2.0, 2.2};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, ExactDuplicateValues) {
    vector<float> input = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    vector<float> expected = {2.0, 2.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, TwoElementsOnly) {
    vector<float> input = {1.5, 3.7};
    vector<float> expected = {1.5, 3.7};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, NegativeNumbers) {
    vector<float> input = {-5.0, -3.0, -4.0, -1.0, -2.0};
    vector<float> expected = {-2.0, -1.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, MixedPositiveNegative) {
    vector<float> input = {-10.0, 0.5, -9.8, 15.0, -9.9};
    vector<float> expected = {-10.0, -9.9};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, VeryCloseNumbers) {
    vector<float> input = {1.0001, 1.0002, 2.0, 3.0, 4.0};
    vector<float> expected = {1.0001, 1.0002};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, EqualSpacingAll) {
    vector<float> input = {0.0, 1.0, 2.0, 3.0, 4.0};
    vector<float> expected = {0.0, 1.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, AlreadyOrderedInput) {
    vector<float> input = {10.0, 20.0, 30.0, 40.0, 45.0, 50.0};
    vector<float> expected = {40.0, 45.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, UnsortedInput) {
    vector<float> input = {9.0, 1.0, 8.0, 2.0, 7.0, 3.0};
    vector<float> expected = {2.0, 3.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, DecimalNumbers) {
    vector<float> input = {1.1, 1.3, 1.2, 2.5, 2.6, 3.0};
    vector<float> expected = {1.1, 1.2};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, MultipleEqualDifferences) {
    vector<float> input = {0.0, 2.0, 4.0, 6.0, 8.0};
    vector<float> expected = {0.0, 2.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, SingleDuplicatePair) {
    vector<float> input = {3.0, 5.0, 5.0, 7.0, 9.0};
    vector<float> expected = {5.0, 5.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, VeryLargeNumbers) {
    vector<float> input = {1e10, 1e10 + 1.0, 1e20, 1e20 + 100.0};
    vector<float> expected = {1e10, 1e10 + 1.0};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, VerySmallNumbers) {
    vector<float> input = {1e-10, 2e-10, 1e-5, 2e-5};
    vector<float> expected = {1e-10, 2e-10};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, NearFloatPrecision) {
    vector<float> input = {1.0, 1.0 + 1e-7, 2.0, 3.0};
    vector<float> expected = {1.0, 1.0 + 1e-7};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, ZeroValues) {
    vector<float> input = {0.0, 0.0, 5.0, 10.0};
    vector<float> expected = {0.0, 0.0};
    EXPECT_EQ(find_closest_elements(input), expected);
}

TEST(FindClosestElementsTest, NegativeZero) {
    vector<float> input = {-0.0, 0.0, 1.0, 2.0};
    vector<float> expected = {-0.0, 0.0};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, LargeVectorPerformance) {
    vector<float> input;
    for (int i = 0; i < 1000; i++) {
        input.push_back(i * 1.0);
    }
    input.push_back(500.1);
    vector<float> expected = {500.0, 500.1};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, WithInfinityValue) {
    vector<float> input = {1.0, 2.0, INFINITY, 2.1};
    vector<float> expected = {2.0, 2.1};
    auto result = find_closest_elements(input);
    EXPECT_FLOAT_EQ(result[0], expected[0]);
    EXPECT_FLOAT_EQ(result[1], expected[1]);
}

TEST(FindClosestElementsTest, MaximumFloatValues) {
    float huge = std::numeric_limits<float>::max();
    vector<float> input = {huge, huge - 1e30, 0.0, 1.0};
    vector<float> expected = {huge - 1e30, huge};
    auto result = find_closest_elements(input);
    EXPECT_EQ(result.size(), 2);
}