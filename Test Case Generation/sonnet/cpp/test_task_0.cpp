#include <gtest/gtest.h>
#include <vector>
#include <cmath>
using namespace std;

bool has_close_elements(vector<float> numbers, float threshold);

TEST(HasCloseElementsTest, ReturnsFalseForDocstringExample1) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f, 3.0f}, 0.5f));
}

TEST(HasCloseElementsTest, ReturnsTrueForDocstringExample2) {
    EXPECT_TRUE(has_close_elements({1.0f, 2.8f, 3.0f, 4.0f, 5.0f, 2.0f}, 0.3f));
}

TEST(HasCloseElementsTest, EmptyVector) {
    EXPECT_FALSE(has_close_elements({}, 1.0f));
}

TEST(HasCloseElementsTest, SingleElement) {
    EXPECT_FALSE(has_close_elements({5.0f}, 1.0f));
}

TEST(HasCloseElementsTest, TwoElementsCloserThanThreshold) {
    EXPECT_TRUE(has_close_elements({1.0f, 1.4f}, 0.5f));
}

TEST(HasCloseElementsTest, TwoElementsExactlyAtThreshold) {
    EXPECT_FALSE(has_close_elements({1.0f, 1.5f}, 0.5f));
}

TEST(HasCloseElementsTest, TwoElementsFartherThanThreshold) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f}, 0.5f));
}

TEST(HasCloseElementsTest, TwoIdenticalElements) {
    EXPECT_TRUE(has_close_elements({3.0f, 3.0f}, 0.1f));
}

TEST(HasCloseElementsTest, NegativeNumbers) {
    EXPECT_TRUE(has_close_elements({-1.0f, -1.05f, -2.0f}, 0.1f));
}

TEST(HasCloseElementsTest, MixedNegativeAndPositive) {
    EXPECT_FALSE(has_close_elements({-10.0f, 0.0f, 10.0f}, 5.0f));
}

TEST(HasCloseElementsTest, MixedNegativeAndPositiveClose) {
    EXPECT_TRUE(has_close_elements({-0.1f, 0.1f}, 0.3f));
}

TEST(HasCloseElementsTest, ZeroThreshold) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f, 3.0f}, 0.0f));
}

TEST(HasCloseElementsTest, ZeroThresholdWithIdenticalElements) {
    EXPECT_FALSE(has_close_elements({1.0f, 1.0f}, 0.0f));
}

TEST(HasCloseElementsTest, LargeThreshold) {
    EXPECT_TRUE(has_close_elements({1.0f, 1000.0f}, 10000.0f));
}

TEST(HasCloseElementsTest, CloseElementsAtEndOfVector) {
    EXPECT_TRUE(has_close_elements({1.0f, 5.0f, 10.0f, 10.2f}, 0.5f));
}

TEST(HasCloseElementsTest, CloseElementsAtBeginningOfVector) {
    EXPECT_TRUE(has_close_elements({1.0f, 1.1f, 5.0f, 10.0f}, 0.5f));
}

TEST(HasCloseElementsTest, AllElementsSame) {
    EXPECT_TRUE(has_close_elements({2.0f, 2.0f, 2.0f, 2.0f}, 0.5f));
}

TEST(HasCloseElementsTest, LargeVectorNoCloseElements) {
    vector<float> v;
    for (int i = 0; i < 100; i++) v.push_back(i * 10.0f);
    EXPECT_FALSE(has_close_elements(v, 1.0f));
}

TEST(HasCloseElementsTest, LargeVectorWithCloseElements) {
    vector<float> v;
    for (int i = 0; i < 100; i++) v.push_back(i * 10.0f);
    v.push_back(v[50] + 0.1f);
    EXPECT_TRUE(has_close_elements(v, 1.0f));
}

TEST(HasCloseElementsTest, VerySmallDifference) {
    EXPECT_TRUE(has_close_elements({1.0f, 1.0001f}, 0.001f));
}

TEST(HasCloseElementsTest, ZeroElements) {
    EXPECT_TRUE(has_close_elements({0.0f, 0.0f}, 0.5f));
}

TEST(HasCloseElementsTest, ZeroAndSmallPositive) {
    EXPECT_TRUE(has_close_elements({0.0f, 0.1f}, 0.5f));
}

TEST(HasCloseElementsTest, NegativeThresholdNoClose) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f, 3.0f}, -1.0f));
}

TEST(HasCloseElementsTest, OrderDoesNotMatter) {
    EXPECT_TRUE(has_close_elements({10.0f, 1.0f, 1.05f}, 0.1f));
}