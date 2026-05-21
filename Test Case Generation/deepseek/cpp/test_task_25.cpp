#include <gtest/gtest.h>
#include <vector>
#include <cmath>

using namespace std;

// Function to test (would be in a header file in practice)
vector<int> factorize(int n);

class FactorizeTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test prime numbers
TEST_F(FactorizeTest, PrimeNumber2) {
    vector<int> result = factorize(2);
    vector<int> expected = {2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PrimeNumber3) {
    vector<int> result = factorize(3);
    vector<int> expected = {3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PrimeNumber7) {
    vector<int> result = factorize(7);
    vector<int> expected = {7};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PrimeNumber13) {
    vector<int> result = factorize(13);
    vector<int> expected = {13};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PrimeNumber97) {
    vector<int> result = factorize(97);
    vector<int> expected = {97};
    EXPECT_EQ(result, expected);
}

// Test perfect squares
TEST_F(FactorizeTest, SquareOf2) {
    vector<int> result = factorize(4);
    vector<int> expected = {2, 2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, SquareOf3) {
    vector<int> result = factorize(9);
    vector<int> expected = {3, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, SquareOf5) {
    vector<int> result = factorize(25);
    vector<int> expected = {5, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, SquareOf11) {
    vector<int> result = factorize(121);
    vector<int> expected = {11, 11};
    EXPECT_EQ(result, expected);
}

// Test cubes
TEST_F(FactorizeTest, CubeOf2) {
    vector<int> result = factorize(8);
    vector<int> expected = {2, 2, 2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, CubeOf3) {
    vector<int> result = factorize(27);
    vector<int> expected = {3, 3, 3};
    EXPECT_EQ(result, expected);
}

// Test higher powers
TEST_F(FactorizeTest, PowerOf2ToThe4th) {
    vector<int> result = factorize(16);
    vector<int> expected = {2, 2, 2, 2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PowerOf2ToThe5th) {
    vector<int> result = factorize(32);
    vector<int> expected = {2, 2, 2, 2, 2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PowerOf3ToThe4th) {
    vector<int> result = factorize(81);
    vector<int> expected = {3, 3, 3, 3};
    EXPECT_EQ(result, expected);
}

// Test product of two distinct primes
TEST_F(FactorizeTest, Product2x3) {
    vector<int> result = factorize(6);
    vector<int> expected = {2, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product2x7) {
    vector<int> result = factorize(14);
    vector<int> expected = {2, 7};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product3x5) {
    vector<int> result = factorize(15);
    vector<int> expected = {3, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product2x13) {
    vector<int> result = factorize(26);
    vector<int> expected = {2, 13};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product5x7) {
    vector<int> result = factorize(35);
    vector<int> expected = {5, 7};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product2x31) {
    vector<int> result = factorize(62);
    vector<int> expected = {2, 31};
    EXPECT_EQ(result, expected);
}

// Test product of three distinct primes
TEST_F(FactorizeTest, Product2x3x5) {
    vector<int> result = factorize(30);
    vector<int> expected = {2, 3, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product2x5x7) {
    vector<int> result = factorize(70);
    vector<int> expected = {2, 5, 7};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product2x3x11) {
    vector<int> result = factorize(66);
    vector<int> expected = {2, 3, 11};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Product3x5x7) {
    vector<int> result = factorize(105);
    vector<int> expected = {3, 5, 7};
    EXPECT_EQ(result, expected);
}

// Test mixed powers and primes
TEST_F(FactorizeTest, Mixed2SquareTimes3) {
    vector<int> result = factorize(12);
    vector<int> expected = {2, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed2CubedTimes3) {
    vector<int> result = factorize(24);
    vector<int> expected = {2, 2, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed2SquareTimes5) {
    vector<int> result = factorize(20);
    vector<int> expected = {2, 2, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed3SquareTimes5) {
    vector<int> result = factorize(45);
    vector<int> expected = {3, 3, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed2SquareTimes3Times5) {
    vector<int> result = factorize(60);
    vector<int> expected = {2, 2, 3, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed2To4thTimes3) {
    vector<int> result = factorize(48);
    vector<int> expected = {2, 2, 2, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed2CubedTimes3Square) {
    vector<int> result = factorize(72);
    vector<int> expected = {2, 2, 2, 3, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed2Times5Square) {
    vector<int> result = factorize(50);
    vector<int> expected = {2, 5, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Mixed2SquareTimes7Times11) {
    vector<int> result = factorize(308);
    vector<int> expected = {2, 2, 7, 11};
    EXPECT_EQ(result, expected);
}

// Test large numbers
TEST_F(FactorizeTest, LargeNumber1) {
    vector<int> result = factorize(99991);  // prime number
    vector<int> expected = {99991};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, LargeNumber2) {
    vector<int> result = factorize(100000);
    vector<int> expected = {2, 2, 2, 2, 2, 5, 5, 5, 5, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, LargeNumber3) {
    vector<int> result = factorize(6469693230);  // product of first 10 primes
    vector<int> expected = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, ProductOfLargePrimes) {
    vector<int> result = factorize(999983 * 999979);  // product of two large primes
    vector<int> expected = {999979, 999983};
    EXPECT_EQ(result, expected);
}

// Edge cases
TEST_F(FactorizeTest, Number1) {
    vector<int> result = factorize(1);
    vector<int> expected = {1};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, Number0) {
    vector<int> result = factorize(0);
    // This will be an infinite loop in the implementation
    // Test is included to document behavior
    vector<int> expected = {};
    EXPECT_EQ(result, expected);
}

// Negative numbers (if supported)
TEST_F(FactorizeTest, NegativeNumberMinus2) {
    vector<int> result = factorize(-2);
    vector<int> expected = {-2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, NegativeNumberMinus4) {
    vector<int> result = factorize(-4);
    vector<int> expected = {-2, -2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, NegativeNumberMinus12) {
    vector<int> result = factorize(-12);
    vector<int> expected = {-2, -2, -3};
    EXPECT_EQ(result, expected);
}

// Additional boundary tests
TEST_F(FactorizeTest, NumberWithRepeatedFactor3) {
    vector<int> result = factorize(243);  // 3^5
    vector<int> expected = {3, 3, 3, 3, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, ProductWithHighPower) {
    vector<int> result = factorize(1024);  // 2^10
    vector<int> expected = {2, 2, 2, 2, 2, 2, 2, 2, 2, 2};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PrimeSquareTimesPrime) {
    vector<int> result = factorize(75);  // 3 * 5^2
    vector<int> expected = {3, 5, 5};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, MultiplePower2And3) {
    vector<int> result = factorize(864);  // 2^5 * 3^3
    vector<int> expected = {2, 2, 2, 2, 2, 3, 3, 3};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, TwoPowerTimesLargePrime) {
    vector<int> result = factorize(2 * 2 * 999983);
    vector<int> expected = {2, 2, 999983};
    EXPECT_EQ(result, expected);
}

// Test for integer limits (if using larger types, but n is int)
TEST_F(FactorizeTest, MaximumPrimeLessThanSqrtIntMax) {
    vector<int> result = factorize(46337);  // prime near sqrt(2^31-1)
    vector<int> expected = {46337};
    EXPECT_EQ(result, expected);
}

// Test numbers that are perfect powers
TEST_F(FactorizeTest, PowerOf7) {
    vector<int> result = factorize(2401);  // 7^4
    vector<int> expected = {7, 7, 7, 7};
    EXPECT_EQ(result, expected);
}

TEST_F(FactorizeTest, PowerOf13) {
    vector<int> result = factorize(28561);  // 13^4
    vector<int> expected = {13, 13, 13, 13};
    EXPECT_EQ(result, expected);
}

// Main function to run the tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}