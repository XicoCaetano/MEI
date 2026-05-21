#include <gtest/gtest.h>
#include <vector>
using namespace std;

bool below_zero(vector<int> operations){
    int num=0;
    for (int i=0;i<operations.size();i++)
    {
        num+=operations[i];
        if (num<0) return true;
    }
    return false;
}

TEST(BelowZeroTest, EmptyVector) {
    EXPECT_FALSE(below_zero({}));
}

TEST(BelowZeroTest, AllPositiveOperations) {
    EXPECT_FALSE(below_zero({1, 2, 3}));
}

TEST(BelowZeroTest, NegativeAfterPositive) {
    EXPECT_TRUE(below_zero({1, 2, -4, 5}));
}

TEST(BelowZeroTest, SinglePositiveOperation) {
    EXPECT_FALSE(below_zero({10}));
}

TEST(BelowZeroTest, SingleNegativeOperation) {
    EXPECT_TRUE(below_zero({-1}));
}

TEST(BelowZeroTest, SingleZeroOperation) {
    EXPECT_FALSE(below_zero({0}));
}

TEST(BelowZeroTest, BalanceExactlyZero) {
    EXPECT_FALSE(below_zero({5, -5}));
}

TEST(BelowZeroTest, BalanceDropsToZeroThenNegative) {
    EXPECT_TRUE(below_zero({5, -5, -1}));
}

TEST(BelowZeroTest, NegativeAtStart) {
    EXPECT_TRUE(below_zero({-1, 10, 20}));
}

TEST(BelowZeroTest, RecoversButWentNegative) {
    EXPECT_TRUE(below_zero({3, -5, 10}));
}

TEST(BelowZeroTest, NeverGoesNegativeLargeValues) {
    EXPECT_FALSE(below_zero({1000, 2000, 3000, -500}));
}

TEST(BelowZeroTest, GoesNegativeAtEnd) {
    EXPECT_TRUE(below_zero({10, 20, 30, -100}));
}

TEST(BelowZeroTest, AllZeros) {
    EXPECT_FALSE(below_zero({0, 0, 0, 0}));
}

TEST(BelowZeroTest, AllNegatives) {
    EXPECT_TRUE(below_zero({-1, -2, -3}));
}

TEST(BelowZeroTest, LargePositiveThenLargeNegative) {
    EXPECT_FALSE(below_zero({1000000, -999999}));
}

TEST(BelowZeroTest, LargePositiveThenExceedingNegative) {
    EXPECT_TRUE(below_zero({1000000, -1000001}));
}

TEST(BelowZeroTest, AlternatingSignsNeverNegative) {
    EXPECT_FALSE(below_zero({5, -3, 4, -2, 6, -1}));
}

TEST(BelowZeroTest, AlternatingSignsGoesNegative) {
    EXPECT_TRUE(below_zero({1, -3, 5, -2}));
}

TEST(BelowZeroTest, MultipleZeroOperations) {
    EXPECT_FALSE(below_zero({0, 0, 5, 0, -3, 0}));
}

TEST(BelowZeroTest, ExactlyBelowZeroByOne) {
    EXPECT_TRUE(below_zero({5, -6}));
}

TEST(BelowZeroTest, NegativeImmediatelyAfterFirstOperation) {
    EXPECT_TRUE(below_zero({3, -4, 100}));
}

TEST(BelowZeroTest, SingleElementZero) {
    EXPECT_FALSE(below_zero({0}));
}

TEST(BelowZeroTest, BalanceFluctuatesButStaysNonNegative) {
    EXPECT_FALSE(below_zero({10, -5, 3, -7, 2, -1}));
}

TEST(BelowZeroTest, NegativeOnlyAtMiddle) {
    EXPECT_TRUE(below_zero({10, 5, -20, 30, 40}));
}