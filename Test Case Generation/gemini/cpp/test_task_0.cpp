#include <gtest/gtest.h>
#include <vector>
#include <cmath>

using namespace std;

// Function under test
bool has_close_elements(vector<float> numbers, float threshold){
    int i,j;
    
    for (i=0;i<numbers.size();i++)
    for (j=i+1;j<numbers.size();j++)
    if (abs(numbers[i]-numbers[j])<threshold)
    return true;

    return false;
}

// Test Suite
class HasCloseElementsTest : public ::testing::Test {};

// Test empty vector
TEST_F(HasCloseElementsTest, EmptyVector) {
    EXPECT_FALSE(has_close_elements({}, 1.0f));
}

// Test single element vector
TEST_F(HasCloseElementsTest, SingleElement) {
    EXPECT_FALSE(has_close_elements({1.0f}, 1.0f));
}

// Test two elements exactly at threshold (should be false because comparison is <)
TEST_F(HasCloseElementsTest, ExactlyAtThreshold) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f}, 1.0f));
}

// Test two elements closer than threshold
TEST_F(HasCloseElementsTest, ElementsCloserThanThreshold) {
    EXPECT_TRUE(has_close_elements({1.0f, 1.5f}, 0.6f));
}

// Test two elements further than threshold
TEST_F(HasCloseElementsTest, ElementsFurtherThanThreshold) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f}, 0.5f));
}

// Test provided example 1
TEST_F(HasCloseElementsTest, ProvidedExampleFalse) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f, 3.0f}, 0.5f));
}

// Test provided example 2
TEST_F(HasCloseElementsTest, ProvidedExampleTrue) {
    EXPECT_TRUE(has_close_elements({1.0f, 2.8f, 3.0f, 4.0f, 5.0f, 2.0f}, 0.3f));
}

// Test negative numbers close to each other
TEST_F(HasCloseElementsTest, NegativeNumbersClose) {
    EXPECT_TRUE(has_close_elements({-1.0f, -1.1f}, 0.2f));
}

// Test negative and positive numbers
TEST_F(HasCloseElementsTest, MixedSignNumbers) {
    EXPECT_TRUE(has_close_elements({-0.1f, 0.1f}, 0.3f));
    EXPECT_FALSE(has_close_elements({-10.0f, 10.0f}, 5.0f));
}

// Test duplicate elements (distance is 0, should be true for any threshold > 0)
TEST_F(HasCloseElementsTest, DuplicateElements) {
    EXPECT_TRUE(has_close_elements({1.0f, 1.0f}, 0.00001f));
}

// Test zero threshold
TEST_F(HasCloseElementsTest, ZeroThreshold) {
    EXPECT_FALSE(has_close_elements({1.0f, 2.0f}, 0.0f));
    EXPECT_FALSE(has_close_elements({1.0f, 1.0f}, 0.0f));
}

// Test large vectors to ensure nested loops complete
TEST_F(HasCloseElementsTest, LargeVectorNoMatch) {
    vector<float> large_vec;
    for(int i = 0; i < 100; ++i) {
        large_vec.push_back((float)i * 2.0f);
    }
    EXPECT_FALSE(has_close_elements(large_vec, 1.0f));
}

// Test precision edge cases
TEST_F(HasCloseElementsTest, FloatingPointPrecision) {
    // 1.000001 - 1.0 is 0.000001
    EXPECT_TRUE(has_close_elements({1.0f, 1.000001f}, 0.00001f));
}