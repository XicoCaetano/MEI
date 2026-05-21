#include <gtest/gtest.h>
#include <vector>

// Forward declaration of the function to be tested
std::vector<int> rolling_max(std::vector<int> numbers);

/**
 * Test Suite for rolling_max function.
 * Focuses on path coverage and edge cases.
 * Note: The original implementation initializes max = 0, which implies 
 * behavior specific to non-negative integers.
 */

// Test case for an empty input vector
TEST(RollingMaxTest, HandlesEmptyInput) {
    std::vector<int> input = {};
    std::vector<int> expected = {};
    EXPECT_EQ(rolling_max(input), expected);
}

// Test case for a single element
TEST(RollingMaxTest, HandlesSingleElement) {
    std::vector<int> input = {5};
    std::vector<int> expected = {5};
    EXPECT_EQ(rolling_max(input), expected);
}

// Test case for strictly increasing sequence
TEST(RollingMaxTest, HandlesIncreasingSequence) {
    std::vector<int> input = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

// Test case for strictly decreasing sequence
TEST(RollingMaxTest, HandlesDecreasingSequence) {
    std::vector<int> input = {5, 4, 3, 2, 1};
    std::vector<int> expected = {5, 5, 5, 5, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

// Test case for fluctuating values (The example provided in the docstring)
TEST(RollingMaxTest, HandlesFluctuatingSequence) {
    std::vector<int> input = {1, 2, 3, 2, 3, 4, 2};
    std::vector<int> expected = {1, 2, 3, 3, 3, 4, 4};
    EXPECT_EQ(rolling_max(input), expected);
}

// Test case for duplicate maximum values
TEST(RollingMaxTest, HandlesDuplicateMax) {
    std::vector<int> input = {10, 5, 10, 7, 11};
    std::vector<int> expected = {10, 10, 10, 10, 11};
    EXPECT_EQ(rolling_max(input), expected);
}

// Test case for all identical elements
TEST(RollingMaxTest, HandlesIdenticalElements) {
    std::vector<int> input = {7, 7, 7, 7};
    std::vector<int> expected = {7, 7, 7, 7};
    EXPECT_EQ(rolling_max(input), expected);
}

// Test case verifying behavior with zero
TEST(RollingMaxTest, HandlesZeros) {
    std::vector<int> input = {0, 0, 1, 0};
    std::vector<int> expected = {0, 0, 1, 1};
    EXPECT_EQ(rolling_max(input), expected);
}

/**
 * Edge Case: Negative numbers
 * Current implementation uses 'int max = 0', so if the first numbers are negative, 
 * the rolling max will stay 0 until a positive number is found.
 */
TEST(RollingMaxTest, CurrentImplementationBehaviorWithNegatives) {
    std::vector<int> input = {-5, -2, 1};
    // Based on 'int max = 0' initialization:
    // i=0: -5 > 0 (F) -> out: {0}
    // i=1: -2 > 0 (F) -> out: {0, 0}
    // i=2:  1 > 0 (T) -> max=1, out: {0, 0, 1}
    std::vector<int> expected = {0, 0, 1};
    EXPECT_EQ(rolling_max(input), expected);
}