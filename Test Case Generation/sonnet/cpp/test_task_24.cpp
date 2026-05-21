#include <gtest/gtest.h>

extern int largest_divisor(int n);

TEST(LargestDivisorTest, ExampleFromDocstring) {
    EXPECT_EQ(largest_divisor(15), 5);
}

TEST(LargestDivisorTest, PrimeNumber) {
    EXPECT_EQ(largest_divisor(7), 1);
    EXPECT_EQ(largest_divisor(13), 1);
    EXPECT_EQ(largest_divisor(97), 1);
}

TEST(LargestDivisorTest, SmallestInput) {
    EXPECT_EQ(largest_divisor(2), 1);
    EXPECT_EQ(largest_divisor(3), 1);
}

TEST(LargestDivisorTest, PerfectSquare) {
    EXPECT_EQ(largest_divisor(4), 2);
    EXPECT_EQ(largest_divisor(9), 3);
    EXPECT_EQ(largest_divisor(25), 5);
    EXPECT_EQ(largest_divisor(36), 6);
    EXPECT_EQ(largest_divisor(100), 10);
}

TEST(LargestDivisorTest, EvenNumbers) {
    EXPECT_EQ(largest_divisor(6), 3);
    EXPECT_EQ(largest_divisor(8), 4);
    EXPECT_EQ(largest_divisor(10), 5);
    EXPECT_EQ(largest_divisor(12), 6);
    EXPECT_EQ(largest_divisor(20), 10);
}

TEST(LargestDivisorTest, OddCompositeNumbers) {
    EXPECT_EQ(largest_divisor(15), 5);
    EXPECT_EQ(largest_divisor(21), 7);
    EXPECT_EQ(largest_divisor(27), 9);
    EXPECT_EQ(largest_divisor(45), 15);
}

TEST(LargestDivisorTest, LargeCompositeNumber) {
    EXPECT_EQ(largest_divisor(1000), 500);
    EXPECT_EQ(largest_divisor(999), 333);
    EXPECT_EQ(largest_divisor(998), 499);
}

TEST(LargestDivisorTest, LargePrimeNumber) {
    EXPECT_EQ(largest_divisor(997), 1);
    EXPECT_EQ(largest_divisor(991), 1);
}

TEST(LargestDivisorTest, PowersOfTwo) {
    EXPECT_EQ(largest_divisor(2), 1);
    EXPECT_EQ(largest_divisor(4), 2);
    EXPECT_EQ(largest_divisor(8), 4);
    EXPECT_EQ(largest_divisor(16), 8);
    EXPECT_EQ(largest_divisor(32), 16);
    EXPECT_EQ(largest_divisor(64), 32);
    EXPECT_EQ(largest_divisor(128), 64);
}

TEST(LargestDivisorTest, SmallestDivisorIsTwo) {
    EXPECT_EQ(largest_divisor(2 * 97), 97);
    EXPECT_EQ(largest_divisor(2 * 89), 89);
}

TEST(LargestDivisorTest, ProductOfTwoPrimes) {
    EXPECT_EQ(largest_divisor(3 * 5), 5);
    EXPECT_EQ(largest_divisor(5 * 7), 7);
    EXPECT_EQ(largest_divisor(11 * 13), 13);
}

TEST(LargestDivisorTest, HighlyCompositeNumbers) {
    EXPECT_EQ(largest_divisor(24), 12);
    EXPECT_EQ(largest_divisor(48), 24);
    EXPECT_EQ(largest_divisor(60), 30);
    EXPECT_EQ(largest_divisor(120), 60);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}