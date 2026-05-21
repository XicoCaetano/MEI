#include <gtest/gtest.h>

extern int greatest_common_divisor(int a, int b);

TEST(GreatestCommonDivisorTest, CoprimeNumbers) {
    EXPECT_EQ(1, greatest_common_divisor(3, 5));
}

TEST(GreatestCommonDivisorTest, CommonDivisorFifteen) {
    EXPECT_EQ(5, greatest_common_divisor(25, 15));
}

TEST(GreatestCommonDivisorTest, SameNumbers) {
    EXPECT_EQ(7, greatest_common_divisor(7, 7));
}

TEST(GreatestCommonDivisorTest, OneIsOne) {
    EXPECT_EQ(1, greatest_common_divisor(1, 1));
}

TEST(GreatestCommonDivisorTest, FirstArgIsOne) {
    EXPECT_EQ(1, greatest_common_divisor(1, 100));
}

TEST(GreatestCommonDivisorTest, SecondArgIsOne) {
    EXPECT_EQ(1, greatest_common_divisor(100, 1));
}

TEST(GreatestCommonDivisorTest, FirstArgLarger) {
    EXPECT_EQ(5, greatest_common_divisor(20, 15));
}

TEST(GreatestCommonDivisorTest, SecondArgLarger) {
    EXPECT_EQ(5, greatest_common_divisor(15, 20));
}

TEST(GreatestCommonDivisorTest, FirstArgMultipleOfSecond) {
    EXPECT_EQ(5, greatest_common_divisor(5, 25));
}

TEST(GreatestCommonDivisorTest, SecondArgMultipleOfFirst) {
    EXPECT_EQ(5, greatest_common_divisor(25, 5));
}

TEST(GreatestCommonDivisorTest, LargeCoprimeNumbers) {
    EXPECT_EQ(1, greatest_common_divisor(13, 17));
}

TEST(GreatestCommonDivisorTest, LargeCommonDivisor) {
    EXPECT_EQ(100, greatest_common_divisor(100, 200));
}

TEST(GreatestCommonDivisorTest, BothEven) {
    EXPECT_EQ(4, greatest_common_divisor(8, 12));
}

TEST(GreatestCommonDivisorTest, OneEvenOneOdd) {
    EXPECT_EQ(1, greatest_common_divisor(9, 28));
}

TEST(GreatestCommonDivisorTest, PrimeNumbers) {
    EXPECT_EQ(1, greatest_common_divisor(11, 13));
}

TEST(GreatestCommonDivisorTest, SamePrimeNumber) {
    EXPECT_EQ(11, greatest_common_divisor(11, 11));
}

TEST(GreatestCommonDivisorTest, LargeNumbers) {
    EXPECT_EQ(12, greatest_common_divisor(144, 60));
}

TEST(GreatestCommonDivisorTest, FibonacciLikeConsecutive) {
    EXPECT_EQ(1, greatest_common_divisor(8, 13));
}

TEST(GreatestCommonDivisorTest, PowersOfTwo) {
    EXPECT_EQ(8, greatest_common_divisor(16, 24));
}

TEST(GreatestCommonDivisorTest, IdenticalLargeValues) {
    EXPECT_EQ(1000, greatest_common_divisor(1000, 1000));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}