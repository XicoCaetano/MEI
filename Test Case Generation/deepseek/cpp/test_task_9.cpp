#include <gtest/gtest.h>
#include <vector>
#include <climits>

using namespace std;

// Assuming the function to test is in the global namespace
vector<int> rolling_max(vector<int> numbers);

class RollingMaxTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RollingMaxTest, EmptyVector) {
    vector<int> input;
    vector<int> expected;
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, SingleElement) {
    vector<int> input = {42};
    vector<int> expected = {42};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, StrictlyIncreasing) {
    vector<int> input = {1, 2, 3, 4, 5};
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, StrictlyDecreasing) {
    vector<int> input = {5, 4, 3, 2, 1};
    vector<int> expected = {5, 5, 5, 5, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, ProvidedExample) {
    vector<int> input = {1, 2, 3, 2, 3, 4, 2};
    vector<int> expected = {1, 2, 3, 3, 3, 4, 4};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, AllEqual) {
    vector<int> input = {7, 7, 7, 7};
    vector<int> expected = {7, 7, 7, 7};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, NegativeNumbers) {
    vector<int> input = {-5, -2, -10, -3, -1};
    vector<int> expected = {-5, -2, -2, -2, -1};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, MixedPositiveAndNegative) {
    vector<int> input = {-3, 5, -1, 2, 0, -2};
    vector<int> expected = {-3, 5, 5, 5, 5, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, ZeroHandling) {
    vector<int> input = {0, -1, 0, 5, 0};
    vector<int> expected = {0, 0, 0, 5, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, LargeNumbers) {
    vector<int> input = {1000000, 999999, 1000001, 1000000};
    vector<int> expected = {1000000, 1000000, 1000001, 1000001};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, SingleNegativeMaximum) {
    vector<int> input = {-1, -5, -2, -3};
    vector<int> expected = {-1, -1, -1, -1};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, WithINT_MIN) {
    vector<int> input = {INT_MIN, -100, 0, 50, INT_MIN};
    vector<int> expected = {INT_MIN, -100, 0, 50, 50};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, WithINT_MAX) {
    vector<int> input = {10, INT_MAX, -100, 200};
    vector<int> expected = {10, INT_MAX, INT_MAX, INT_MAX};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, AlternatingValues) {
    vector<int> input = {1, 3, 1, 3, 1, 3};
    vector<int> expected = {1, 3, 3, 3, 3, 3};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, SingleElementZero) {
    vector<int> input = {0};
    vector<int> expected = {0};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST_F(RollingMaxTest, LargeDecreasingThenIncreasing) {
    vector<int> input = {10, 9, 8, 7, 11, 12, 6};
    vector<int> expected = {10, 10, 10, 10, 11, 12, 12};
    EXPECT_EQ(rolling_max(input), expected);
}