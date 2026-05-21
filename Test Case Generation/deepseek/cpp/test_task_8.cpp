#include <gtest/gtest.h>
#include <vector>
#include "sum_product.h"  // Assume the function is declared here

using namespace std;

// Test fixture for sum_product function
class SumProductTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test empty vector case
TEST_F(SumProductTest, EmptyVector) {
    vector<int> numbers = {};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 0);  // Sum of empty vector should be 0
    EXPECT_EQ(result[1], 1);  // Product of empty vector should be 1
}

// Test single element vector
TEST_F(SumProductTest, SingleElement) {
    vector<int> numbers = {5};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 5);
}

// Test multiple positive integers
TEST_F(SumProductTest, MultiplePositiveIntegers) {
    vector<int> numbers = {1, 2, 3, 4};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 10);  // 1+2+3+4 = 10
    EXPECT_EQ(result[1], 24);  // 1*2*3*4 = 24
}

// Test with zero (product edge case)
TEST_F(SumProductTest, WithZero) {
    vector<int> numbers = {5, 0, 3};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 8);   // 5+0+3 = 8
    EXPECT_EQ(result[1], 0);   // 5*0*3 = 0
}

// Test with negative integers
TEST_F(SumProductTest, WithNegativeIntegers) {
    vector<int> numbers = {-2, -3, -4};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], -9);  // (-2)+(-3)+(-4) = -9
    EXPECT_EQ(result[1], -24); // (-2)*(-3)*(-4) = -24
}

// Test with mixed positive and negative integers
TEST_F(SumProductTest, MixedPositiveNegative) {
    vector<int> numbers = {-1, 2, -3, 4};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 2);   // (-1)+2+(-3)+4 = 2
    EXPECT_EQ(result[1], 24);  // (-1)*2*(-3)*4 = 24
}

// Test large values (potential overflow is implementation-defined)
TEST_F(SumProductTest, LargeNumbers) {
    vector<int> numbers = {1000000, 2000000, 3000000};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 6000000);  // 1e6+2e6+3e6 = 6e6
    EXPECT_EQ(result[1], 6000000000000LL);  // Product may overflow int on some systems
}

// Test with single zero element
TEST_F(SumProductTest, SingleZero) {
    vector<int> numbers = {0};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
}

// Test with alternating signs
TEST_F(SumProductTest, AlternatingSigns) {
    vector<int> numbers = {1, -1, 2, -2, 3, -3};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 0);   // 1-1+2-2+3-3 = 0
    EXPECT_EQ(result[1], -36); // 1*(-1)*2*(-2)*3*(-3) = -36
}

// Test with all same positive numbers
TEST_F(SumProductTest, AllSamePositive) {
    vector<int> numbers = {2, 2, 2, 2};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 8);   // 2+2+2+2 = 8
    EXPECT_EQ(result[1], 16);  // 2*2*2*2 = 16
}

// Test with all same negative numbers (even count)
TEST_F(SumProductTest, AllSameNegativeEven) {
    vector<int> numbers = {-3, -3, -3, -3};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], -12); // (-3)+(-3)+(-3)+(-3) = -12
    EXPECT_EQ(result[1], 81);  // (-3)*(-3)*(-3)*(-3) = 81
}

// Test with all same negative numbers (odd count)
TEST_F(SumProductTest, AllSameNegativeOdd) {
    vector<int> numbers = {-3, -3, -3};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], -9);  // (-3)+(-3)+(-3) = -9
    EXPECT_EQ(result[1], -27); // (-3)*(-3)*(-3) = -27
}

// Test with maximum number of elements (performance test)
TEST_F(SumProductTest, ManyElements) {
    vector<int> numbers(1000, 1);  // 1000 elements of 1
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 1000);  // Sum of 1000 ones = 1000
    EXPECT_EQ(result[1], 1);     // Product of 1000 ones = 1
}

// Test with two elements
TEST_F(SumProductTest, TwoElements) {
    vector<int> numbers = {5, 7};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 12);
    EXPECT_EQ(result[1], 35);
}

// Test with increasing sequence
TEST_F(SumProductTest, IncreasingSequence) {
    vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 55);   // Arithmetic series sum
    EXPECT_EQ(result[1], 3628800);  // 10!
}

// Test with descending sequence
TEST_F(SumProductTest, DescendingSequence) {
    vector<int> numbers = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
    vector<int> result = sum_product(numbers);
    
    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 55);
    EXPECT_EQ(result[1], 3628800);
}