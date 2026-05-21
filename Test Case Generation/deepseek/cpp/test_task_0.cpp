#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <limits>

// Function to test (assuming it's in the same namespace or accessible)
bool has_close_elements(std::vector<float> numbers, float threshold);

TEST(HasCloseElementsTest, EmptyVectorReturnsFalse) {
    EXPECT_FALSE(has_close_elements({}, 0.5));
}

TEST(HasCloseElementsTest, SingleElementReturnsFalse) {
    EXPECT_FALSE(has_close_elements({1.0}, 0.5));
    EXPECT_FALSE(has_close_elements({-5.3}, 0.1));
    EXPECT_FALSE(has_close_elements({0.0}, 1.0));
}

TEST(HasCloseElementsTest, TwoElements_Close_ReturnsTrue) {
    EXPECT_TRUE(has_close_elements({1.0, 1.4}, 0.5));
    EXPECT_TRUE(has_close_elements({-2.0, -1.6}, 0.5));
    EXPECT_TRUE(has_close_elements({0.0, 0.0}, 0.0001));
}

TEST(HasCloseElementsTest, TwoElements_NotClose_ReturnsFalse) {
    EXPECT_FALSE(has_close_elements({1.0, 2.0}, 0.5));
    EXPECT_FALSE(has_close_elements({-5.0, -3.0}, 1.5));
    EXPECT_FALSE(has_close_elements({100.0, 200.0}, 50.0));
}

TEST(HasCloseElementsTest, MultipleElements_CloseElementsExist_ReturnsTrue) {
    EXPECT_TRUE(has_close_elements({1.0, 2.8, 3.0, 4.0, 5.0, 2.0}, 0.3));
    EXPECT_TRUE(has_close_elements({10.0, 20.0, 30.0, 30.1, 40.0}, 0.2));
    EXPECT_TRUE(has_close_elements({-1.5, -1.4, 0.0, 1.0}, 0.2));
    EXPECT_TRUE(has_close_elements({0.5, 1.0, 1.5, 2.0, 2.1}, 0.15));
}

TEST(HasCloseElementsTest, MultipleElements_NoCloseElements_ReturnsFalse) {
    EXPECT_FALSE(has_close_elements({1.0, 2.0, 3.0, 4.0, 5.0}, 0.5));
    EXPECT_FALSE(has_close_elements({-10.0, -5.0, 0.0, 5.0, 10.0}, 1.0));
    EXPECT_FALSE(has_close_elements({0.1, 0.5, 0.9, 1.3}, 0.3));
}

TEST(HasCloseElementsTest, ThresholdZero_ExactlyEqual_ReturnsTrue) {
    EXPECT_TRUE(has_close_elements({1.0, 1.0, 2.0}, 0.0));
    EXPECT_TRUE(has_close_elements({5.0, 5.0}, 0.0));
    EXPECT_TRUE(has_close_elements({-3.0, -3.0}, 0.0));
}

TEST(HasCloseElementsTest, ThresholdZero_NoEqualElements_ReturnsFalse) {
    EXPECT_FALSE(has_close_elements({1.0, 1.1, 2.0}, 0.0));
    EXPECT_FALSE(has_close_elements({0.0, 0.001}, 0.0));
}

TEST(HasCloseElementsTest, NegativeThreshold_AlwaysFalse) {
    EXPECT_FALSE(has_close_elements({1.0, 1.0}, -0.5));
    EXPECT_FALSE(has_close_elements({1.0, 2.0, 3.0}, -0.1));
    EXPECT_FALSE(has_close_elements({0.0, 0.0, 0.0}, -0.001));
}

TEST(HasCloseElementsTest, VerySmallThreshold_Epsilon) {
    float epsilon = std::numeric_limits<float>::epsilon();
    EXPECT_FALSE(has_close_elements({1.0, 1.0 + epsilon}, epsilon / 2));
    EXPECT_TRUE(has_close_elements({1.0, 1.0 + epsilon * 2}, epsilon * 1.5));
}

TEST(HasCloseElementsTest, VeryLargeValues) {
    float large = 1e30f;
    float large_diff = 1e20f;
    EXPECT_FALSE(has_close_elements({large, large + large_diff}, large_diff / 2));
    EXPECT_TRUE(has_close_elements({large, large + large_diff}, large_diff * 2));
}

TEST(HasCloseElementsTest, VerySmallValues) {
    float small = 1e-30f;
    float small_diff = 1e-35f;
    EXPECT_FALSE(has_close_elements({small, small + small_diff}, small_diff / 2));
    EXPECT_TRUE(has_close_elements({small, small + small_diff}, small_diff * 2));
}

TEST(HasCloseElementsTest, MixedPositiveAndNegative) {
    EXPECT_TRUE(has_close_elements({-1.0, -0.9, 0.0, 1.0}, 0.15));
    EXPECT_FALSE(has_close_elements({-10.0, -5.0, 0.0, 5.0, 10.0}, 4.9));
    EXPECT_TRUE(has_close_elements({-5.0, -4.99, 0.0}, 0.02));
}

TEST(HasCloseElementsTest, DuplicateValues) {
    EXPECT_TRUE(has_close_elements({1.0, 1.0, 1.0, 2.0, 3.0}, 0.1));
    EXPECT_TRUE(has_close_elements({5.0, 5.0, 5.0, 5.0}, 0.0));
    EXPECT_FALSE(has_close_elements({1.0, 2.0, 3.0, 4.0, 5.0, 1.000001}, 0.0000005));
}

TEST(HasCloseElementsTest, SortedAndUnsortedInputs) {
    // Both should work the same
    std::vector<float> sorted = {1.0, 1.5, 2.0, 2.5, 3.0};
    std::vector<float> unsorted = {2.5, 1.0, 3.0, 1.5, 2.0};
    
    EXPECT_TRUE(has_close_elements(sorted, 0.6));
    EXPECT_TRUE(has_close_elements(unsorted, 0.6));
    
    EXPECT_FALSE(has_close_elements(sorted, 0.4));
    EXPECT_FALSE(has_close_elements(unsorted, 0.4));
}

TEST(HasCloseElementsTest, InfinityAndNaN) {
    float inf = std::numeric_limits<float>::infinity();
    float nan = std::numeric_limits<float>::quiet_NaN();
    
    EXPECT_FALSE(has_close_elements({inf, 1.0}, 0.5));
    EXPECT_FALSE(has_close_elements({-inf, inf}, 1000.0));
    EXPECT_FALSE(has_close_elements({nan, 1.0}, 0.5));
    EXPECT_FALSE(has_close_elements({nan, nan}, 0.5));
}