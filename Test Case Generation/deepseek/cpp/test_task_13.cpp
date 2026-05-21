#include <gtest/gtest.h>

// Function to test (declaration)
int greatest_common_divisor(int a, int b);

TEST(GreatestCommonDivisorTest, PositiveNumbers) {
    EXPECT_EQ(greatest_common_divisor(3, 5), 1);
    EXPECT_EQ(greatest_common_divisor(25, 15), 5);
    EXPECT_EQ(greatest_common_divisor(48, 18), 6);
    EXPECT_EQ(greatest_common_divisor(100, 75), 25);
    EXPECT_EQ(greatest_common_divisor(17, 19), 1);
}

TEST(GreatestCommonDivisorTest, EqualNumbers) {
    EXPECT_EQ(greatest_common_divisor(10, 10), 10);
    EXPECT_EQ(greatest_common_divisor(7, 7), 7);
    EXPECT_EQ(greatest_common_divisor(1, 1), 1);
    EXPECT_EQ(greatest_common_divisor(0, 0), 0);
}

TEST(GreatestCommonDivisorTest, OneIsZero) {
    EXPECT_EQ(greatest_common_divisor(0, 5), 5);
    EXPECT_EQ(greatest_common_divisor(5, 0), 5);
    EXPECT_EQ(greatest_common_divisor(0, 1), 1);
    EXPECT_EQ(greatest_common_divisor(0, 100), 100);
}

TEST(GreatestCommonDivisorTest, NegativeNumbers) {
    EXPECT_EQ(greatest_common_divisor(-3, 5), 1);
    EXPECT_EQ(greatest_common_divisor(3, -5), 1);
    EXPECT_EQ(greatest_common_divisor(-25, -15), 5);
    EXPECT_EQ(greatest_common_divisor(-48, 18), 6);
    EXPECT_EQ(greatest_common_divisor(48, -18), 6);
    EXPECT_EQ(greatest_common_divisor(-10, -10), 10);
    EXPECT_EQ(greatest_common_divisor(-7, 7), 7);
}

TEST(GreatestCommonDivisorTest, LargeNumbers) {
    EXPECT_EQ(greatest_common_divisor(123456, 789012), 6);
    EXPECT_EQ(greatest_common_divisor(1000000, 500000), 500000);
    EXPECT_EQ(greatest_common_divisor(999999, 111111), 111111);
    EXPECT_EQ(greatest_common_divisor(2147483647, 2147483646), 1);
}

TEST(GreatestCommonDivisorTest, PrimeNumbers) {
    EXPECT_EQ(greatest_common_divisor(13, 17), 1);
    EXPECT_EQ(greatest_common_divisor(23, 29), 1);
    EXPECT_EQ(greatest_common_divisor(31, 37), 1);
    EXPECT_EQ(greatest_common_divisor(13, 39), 13);
}

TEST(GreatestCommonDivisorTest, EdgeCases) {
    EXPECT_EQ(greatest_common_divisor(1, 1000000), 1);
    EXPECT_EQ(greatest_common_divisor(2, 4), 2);
    EXPECT_EQ(greatest_common_divisor(2, 3), 1);
    EXPECT_EQ(greatest_common_divisor(6, 10), 2);
    EXPECT_EQ(greatest_common_divisor(9, 27), 9);
}