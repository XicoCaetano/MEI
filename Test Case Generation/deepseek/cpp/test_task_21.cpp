#include <gtest/gtest.h>
#include <vector>
#include <cmath>
#include <algorithm>

// Function to test (assuming it's in the same file or included)
// For completeness, we include the function here, but in real tests it would be from the source
vector<float> rescale_to_unit(vector<float> numbers);

class RescaleToUnitTest : public ::testing::Test {
protected:
    const float epsilon = 1e-5f;
    
    void assertVectorNear(const vector<float>& expected, const vector<float>& actual) {
        ASSERT_EQ(expected.size(), actual.size());
        for (size_t i = 0; i < expected.size(); ++i) {
            EXPECT_NEAR(expected[i], actual[i], epsilon);
        }
    }
};

TEST_F(RescaleToUnitTest, BasicIncreasingSequence) {
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, DecreasingSequence) {
    vector<float> input = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    vector<float> expected = {1.0f, 0.75f, 0.5f, 0.25f, 0.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, AllEqualNumbers) {
    vector<float> input = {3.0f, 3.0f, 3.0f, 3.0f};
    vector<float> expected = {0.0f, 0.0f, 0.0f, 0.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, TwoElements) {
    vector<float> input = {10.0f, 20.0f};
    vector<float> expected = {0.0f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, NegativeNumbers) {
    vector<float> input = {-5.0f, -3.0f, -1.0f, 0.0f, 2.0f};
    vector<float> expected = {0.0f, 0.285714f, 0.571429f, 0.714286f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, MixedPositiveAndNegative) {
    vector<float> input = {-10.0f, -5.0f, 0.0f, 5.0f, 10.0f};
    vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, DecimalNumbers) {
    vector<float> input = {1.5f, 2.7f, 3.9f, 5.1f};
    vector<float> expected = {0.0f, 0.333333f, 0.666667f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, MinAtEnd) {
    vector<float> input = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    vector<float> expected = {1.0f, 0.75f, 0.5f, 0.25f, 0.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, MaxAtEnd) {
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, SingleElement) {
    vector<float> input = {42.0f};
    vector<float> expected = {0.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, LargeNumbers) {
    vector<float> input = {1000.0f, 2000.0f, 3000.0f, 4000.0f, 5000.0f};
    vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, VerySmallNumbers) {
    vector<float> input = {0.0001f, 0.0002f, 0.0003f, 0.0004f};
    vector<float> expected = {0.0f, 0.333333f, 0.666667f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, ZeroRangeAfterMinMax) {
    vector<float> input = {5.0f, 5.0f, 5.0f};
    vector<float> expected = {0.0f, 0.0f, 0.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, UnsortedRandomOrder) {
    vector<float> input = {7.0f, 2.0f, 9.0f, 1.0f, 5.0f};
    vector<float> expected = {0.75f, 0.125f, 1.0f, 0.0f, 0.5f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

TEST_F(RescaleToUnitTest, ContainsZero) {
    vector<float> input = {-2.0f, -1.0f, 0.0f, 1.0f, 2.0f};
    vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}

// Edge case: floating point precision
TEST_F(RescaleToUnitTest, FloatingPointPrecision) {
    vector<float> input = {0.1f, 0.2f, 0.3f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    vector<float> result = rescale_to_unit(input);
    assertVectorNear(expected, result);
}