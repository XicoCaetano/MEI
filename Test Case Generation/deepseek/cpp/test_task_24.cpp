#include <gtest/gtest.h>

// Function declaration (assuming it's in the global namespace)
int largest_divisor(int n);

class LargestDivisorTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test prime numbers - should return 1
TEST_F(LargestDivisorTest, PrimeNumbers) {
    EXPECT_EQ(largest_divisor(2), 1);
    EXPECT_EQ(largest_divisor(3), 1);
    EXPECT_EQ(largest_divisor(5), 1);
    EXPECT_EQ(largest_divisor(7), 1);
    EXPECT_EQ(largest_divisor(11), 1);
    EXPECT_EQ(largest_divisor(13), 1);
    EXPECT_EQ(largest_divisor(17), 1);
    EXPECT_EQ(largest_divisor(19), 1);
    EXPECT_EQ(largest_divisor(23), 1);
    EXPECT_EQ(largest_divisor(29), 1);
}

// Test composite numbers with various divisors
TEST_F(LargestDivisorTest, CompositeNumbers) {
    EXPECT_EQ(largest_divisor(4), 2);   // 4/2 = 2
    EXPECT_EQ(largest_divisor(6), 3);   // 6/2 = 3
    EXPECT_EQ(largest_divisor(8), 4);   // 8/2 = 4
    EXPECT_EQ(largest_divisor(9), 3);   // 9/3 = 3
    EXPECT_EQ(largest_divisor(10), 5);  // 10/2 = 5
    EXPECT_EQ(largest_divisor(12), 6);  // 12/2 = 6
    EXPECT_EQ(largest_divisor(14), 7);  // 14/2 = 7
    EXPECT_EQ(largest_divisor(15), 5);  // 15/3 = 5
    EXPECT_EQ(largest_divisor(16), 8);  // 16/2 = 8
    EXPECT_EQ(largest_divisor(18), 9);  // 18/2 = 9
    EXPECT_EQ(largest_divisor(20), 10); // 20/2 = 10
    EXPECT_EQ(largest_divisor(21), 7);  // 21/3 = 7
    EXPECT_EQ(largest_divisor(22), 11); // 22/2 = 11
    EXPECT_EQ(largest_divisor(24), 12); // 24/2 = 12
    EXPECT_EQ(largest_divisor(25), 5);  // 25/5 = 5
    EXPECT_EQ(largest_divisor(26), 13); // 26/2 = 13
    EXPECT_EQ(largest_divisor(27), 9);  // 27/3 = 9
    EXPECT_EQ(largest_divisor(28), 14); // 28/2 = 14
    EXPECT_EQ(largest_divisor(30), 15); // 30/2 = 15
}

// Test perfect squares
TEST_F(LargestDivisorTest, PerfectSquares) {
    EXPECT_EQ(largest_divisor(4), 2);
    EXPECT_EQ(largest_divisor(9), 3);
    EXPECT_EQ(largest_divisor(16), 8);
    EXPECT_EQ(largest_divisor(25), 5);
    EXPECT_EQ(largest_divisor(36), 18);  // 36/2 = 18
    EXPECT_EQ(largest_divisor(49), 7);
    EXPECT_EQ(largest_divisor(64), 32);  // 64/2 = 32
    EXPECT_EQ(largest_divisor(81), 27);  // 81/3 = 27
    EXPECT_EQ(largest_divisor(100), 50); // 100/2 = 50
    EXPECT_EQ(largest_divisor(121), 11);
    EXPECT_EQ(largest_divisor(144), 72); // 144/2 = 72
}

// Test edge cases with large numbers
TEST_F(LargestDivisorTest, EdgeCases) {
    EXPECT_EQ(largest_divisor(1), 1);   // Loop doesn't execute (2*2 > 1)
    EXPECT_EQ(largest_divisor(2), 1);   // Smallest prime
    EXPECT_EQ(largest_divisor(3), 1);   // Smallest odd prime
    EXPECT_EQ(largest_divisor(4), 2);   // Smallest composite
    EXPECT_EQ(largest_divisor(6), 3);   // Smallest with two prime factors
    EXPECT_EQ(largest_divisor(99991), 1); // Large prime number
    EXPECT_EQ(largest_divisor(100000), 50000); // 100000/2 = 50000
}

// Test numbers where divisor is found at sqrt(n)
TEST_F(LargestDivisorTest, DivisorAtSquareRoot) {
    EXPECT_EQ(largest_divisor(25), 5);   // sqrt(25)=5, divisor=5
    EXPECT_EQ(largest_divisor(49), 7);   // sqrt(49)=7, divisor=7
    EXPECT_EQ(largest_divisor(121), 11); // sqrt(121)=11, divisor=11
    EXPECT_EQ(largest_divisor(169), 13); // sqrt(169)=13, divisor=13
    EXPECT_EQ(largest_divisor(289), 17); // sqrt(289)=17, divisor=17
}

// Test numbers with small prime factors
TEST_F(LargestDivisorTest, SmallPrimeFactors) {
    EXPECT_EQ(largest_divisor(2 * 97), 97);     // 2*97 = 194
    EXPECT_EQ(largest_divisor(3 * 101), 101);   // 3*101 = 303
    EXPECT_EQ(largest_divisor(5 * 103), 103);   // 5*103 = 515
    EXPECT_EQ(largest_divisor(7 * 107), 107);   // 7*107 = 749
}

// Test numbers where smallest divisor is > 2
TEST_F(LargestDivisorTest, OddCompositeNumbers) {
    EXPECT_EQ(largest_divisor(9), 3);    // 9/3 = 3
    EXPECT_EQ(largest_divisor(15), 5);   // 15/3 = 5
    EXPECT_EQ(largest_divisor(21), 7);   // 21/3 = 7
    EXPECT_EQ(largest_divisor(25), 5);   // 25/5 = 5
    EXPECT_EQ(largest_divisor(27), 9);   // 27/3 = 9
    EXPECT_EQ(largest_divisor(33), 11);  // 33/3 = 11
    EXPECT_EQ(largest_divisor(35), 7);   // 35/5 = 7
    EXPECT_EQ(largest_divisor(39), 13);  // 39/3 = 13
    EXPECT_EQ(largest_divisor(45), 15);  // 45/3 = 15
    EXPECT_EQ(largest_divisor(49), 7);   // 49/7 = 7
    EXPECT_EQ(largest_divisor(51), 17);  // 51/3 = 17
    EXPECT_EQ(largest_divisor(55), 11);  // 55/5 = 11
    EXPECT_EQ(largest_divisor(57), 19);  // 57/3 = 19
    EXPECT_EQ(largest_divisor(63), 21);  // 63/3 = 21
    EXPECT_EQ(largest_divisor(65), 13);  // 65/5 = 13
    EXPECT_EQ(largest_divisor(69), 23);  // 69/3 = 23
    EXPECT_EQ(largest_divisor(75), 25);  // 75/3 = 25
    EXPECT_EQ(largest_divisor(77), 11);  // 77/7 = 11
    EXPECT_EQ(largest_divisor(81), 27);  // 81/3 = 27
    EXPECT_EQ(largest_divisor(85), 17);  // 85/5 = 17
    EXPECT_EQ(largest_divisor(87), 29);  // 87/3 = 29
    EXPECT_EQ(largest_divisor(91), 13);  // 91/7 = 13
    EXPECT_EQ(largest_divisor(93), 31);  // 93/3 = 31
    EXPECT_EQ(largest_divisor(95), 19);  // 95/5 = 19
    EXPECT_EQ(largest_divisor(99), 33);  // 99/3 = 33
}

// Additional boundary tests
TEST_F(LargestDivisorTest, BoundaryValues) {
    EXPECT_EQ(largest_divisor(0), 0);  // Undefined behavior but testing it
}

// Test numbers with multiple divisors
TEST_F(LargestDivisorTest, MultipleDivisors) {
    // n = 30, divisors: 2,3,5,6,10,15; largest < 30 is 15
    EXPECT_EQ(largest_divisor(30), 15);
    
    // n = 36, divisors: 2,3,4,6,9,12,18; largest < 36 is 18
    EXPECT_EQ(largest_divisor(36), 18);
    
    // n = 48, divisors: 2,3,4,6,8,12,16,24; largest < 48 is 24
    EXPECT_EQ(largest_divisor(48), 24);
    
    // n = 60, divisors: 2,3,4,5,6,10,12,15,20,30; largest < 60 is 30
    EXPECT_EQ(largest_divisor(60), 30);
    
    // n = 84, divisors: 2,3,4,6,7,12,14,21,28,42; largest < 84 is 42
    EXPECT_EQ(largest_divisor(84), 42);
}

// Test even numbers (should always return n/2 if n is even)
TEST_F(LargestDivisorTest, EvenNumbers) {
    for (int i = 4; i <= 1000; i += 2) {
        if (i % 2 == 0) {
            EXPECT_EQ(largest_divisor(i), i / 2);
        }
    }
}

// Test numbers near powers of 2
TEST_F(LargestDivisorTest, PowersOfTwo) {
    EXPECT_EQ(largest_divisor(64), 32);
    EXPECT_EQ(largest_divisor(128), 64);
    EXPECT_EQ(largest_divisor(256), 128);
    EXPECT_EQ(largest_divisor(512), 256);
    EXPECT_EQ(largest_divisor(1024), 512);
}