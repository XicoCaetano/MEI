#include <gtest/gtest.h>
#include <vector>
#include "intersperse.h" // Assume the function is declared here

using namespace std;

TEST(IntersperseTest, EmptyVector) {
    vector<int> input = {};
    vector<int> expected = {};
    EXPECT_EQ(intersperse(input, 4), expected);
}

TEST(IntersperseTest, SingleElementVector) {
    vector<int> input = {42};
    vector<int> expected = {42};
    EXPECT_EQ(intersperse(input, 99), expected);
}

TEST(IntersperseTest, TwoElements) {
    vector<int> input = {1, 2};
    vector<int> expected = {1, 5, 2};
    EXPECT_EQ(intersperse(input, 5), expected);
}

TEST(IntersperseTest, ThreeElements) {
    vector<int> input = {1, 2, 3};
    vector<int> expected = {1, 4, 2, 4, 3};
    EXPECT_EQ(intersperse(input, 4), expected);
}

TEST(IntersperseTest, FiveElements) {
    vector<int> input = {10, 20, 30, 40, 50};
    vector<int> expected = {10, 0, 20, 0, 30, 0, 40, 0, 50};
    EXPECT_EQ(intersperse(input, 0), expected);
}

TEST(IntersperseTest, NegativeDelimeter) {
    vector<int> input = {5, 10, 15};
    vector<int> expected = {5, -1, 10, -1, 15};
    EXPECT_EQ(intersperse(input, -1), expected);
}

TEST(IntersperseTest, ZeroDelimeter) {
    vector<int> input = {100, 200};
    vector<int> expected = {100, 0, 200};
    EXPECT_EQ(intersperse(input, 0), expected);
}

TEST(IntersperseTest, LargeDelimeter) {
    vector<int> input = {1, 2};
    vector<int> expected = {1, 999999, 2};
    EXPECT_EQ(intersperse(input, 999999), expected);
}

TEST(IntersperseTest, NegativeNumbersInInput) {
    vector<int> input = {-5, -10, -15};
    vector<int> expected = {-5, 99, -10, 99, -15};
    EXPECT_EQ(intersperse(input, 99), expected);
}

TEST(IntersperseTest, MixedPositiveAndNegativeInput) {
    vector<int> input = {-1, 2, -3, 4};
    vector<int> expected = {-1, 0, 2, 0, -3, 0, 4};
    EXPECT_EQ(intersperse(input, 0), expected);
}

TEST(IntersperseTest, LargeVector) {
    vector<int> input(1000, 1);
    vector<int> expected;
    expected.push_back(1);
    for (int i = 1; i < 1000; i++) {
        expected.push_back(7);
        expected.push_back(1);
    }
    EXPECT_EQ(intersperse(input, 7), expected);
}

TEST(IntersperseTest, VeryLargeDelimeter) {
    vector<int> input = {10, 20};
    vector<int> expected = {10, 2147483647, 20};
    EXPECT_EQ(intersperse(input, 2147483647), expected);
}

TEST(IntersperseTest, SingleElementWithExtremeDelimeter) {
    vector<int> input = {0};
    vector<int> expected = {0};
    EXPECT_EQ(intersperse(input, -2147483648), expected);
}