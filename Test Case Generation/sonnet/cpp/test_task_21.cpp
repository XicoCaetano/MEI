#include <gtest/gtest.h>
#include <vector>
#include <cmath>
using namespace std;

vector<float> rescale_to_unit(vector<float> numbers) {
    float min = 100000, max = -100000;
    for (int i = 0; i < numbers.size(); i++) {
        if (numbers[i] < min) min = numbers[i];
        if (numbers[i] > max) max = numbers[i];
    }
    for (int i = 0; i < numbers.size(); i++)
        numbers[i] = (numbers[i] - min) / (max - min);
    return numbers;
}

const float EPSILON = 1e-5f;

// Helper to compare float vectors
void assertVectorsNear(const vector<float>& actual, const vector<float>& expected, float eps = EPSILON) {
    ASSERT_EQ(actual.size(), expected.size());
    for (size_t i = 0; i < actual.size(); i++) {
        EXPECT_NEAR(actual[i], expected[i], eps) << "Mismatch at index " << i;
    }
}

// Basic example from docstring
TEST(RescaleToUnit, BasicFiveElements) {
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    vector<float> expected = {0.0f, 0.25f, 0.5f, 0.75f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Minimum two elements: min and max
TEST(RescaleToUnit, TwoElements) {
    vector<float> input = {3.0f, 7.0f};
    vector<float> expected = {0.0f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Two elements reversed order
TEST(RescaleToUnit, TwoElementsReversed) {
    vector<float> input = {7.0f, 3.0f};
    vector<float> expected = {1.0f, 0.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// All positive numbers
TEST(RescaleToUnit, AllPositive) {
    vector<float> input = {10.0f, 20.0f, 30.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// All negative numbers
TEST(RescaleToUnit, AllNegative) {
    vector<float> input = {-30.0f, -20.0f, -10.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Mix of negative and positive numbers
TEST(RescaleToUnit, MixedNegativeAndPositive) {
    vector<float> input = {-1.0f, 0.0f, 1.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Input containing zero
TEST(RescaleToUnit, ContainsZero) {
    vector<float> input = {0.0f, 5.0f, 10.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Input with negative zero boundary
TEST(RescaleToUnit, NegativeToZero) {
    vector<float> input = {-4.0f, -2.0f, 0.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Input already in [0,1] range
TEST(RescaleToUnit, AlreadyNormalized) {
    vector<float> input = {0.0f, 0.5f, 1.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Large values
TEST(RescaleToUnit, LargeValues) {
    vector<float> input = {1000.0f, 5000.0f, 9000.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Values near the hardcoded min boundary (100000)
TEST(RescaleToUnit, ValuesNearHardcodedMin) {
    vector<float> input = {99998.0f, 99999.0f, 100000.0f};
    // min will be set correctly since all < 100000 initial min
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Values near the hardcoded max boundary (-100000)
TEST(RescaleToUnit, ValuesNearHardcodedMax) {
    vector<float> input = {-100000.0f, -99999.0f, -99998.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Unsorted input
TEST(RescaleToUnit, UnsortedInput) {
    vector<float> input = {3.0f, 1.0f, 4.0f, 2.0f, 5.0f};
    vector<float> expected = {0.5f, 0.0f, 0.75f, 0.25f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Descending input
TEST(RescaleToUnit, DescendingInput) {
    vector<float> input = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    vector<float> expected = {1.0f, 0.75f, 0.5f, 0.25f, 0.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Floating point precision values
TEST(RescaleToUnit, FloatingPointPrecision) {
    vector<float> input = {0.1f, 0.2f, 0.3f};
    vector<float> result = rescale_to_unit(input);
    EXPECT_NEAR(result[0], 0.0f, EPSILON);
    EXPECT_NEAR(result[2], 1.0f, EPSILON);
    EXPECT_NEAR(result[1], 0.5f, 1e-4f);
}

// Output min is exactly 0
TEST(RescaleToUnit, MinIsExactlyZero) {
    vector<float> input = {2.0f, 5.0f, 8.0f};
    vector<float> result = rescale_to_unit(input);
    EXPECT_FLOAT_EQ(result[0], 0.0f);
}

// Output max is exactly 1
TEST(RescaleToUnit, MaxIsExactlyOne) {
    vector<float> input = {2.0f, 5.0f, 8.0f};
    vector<float> result = rescale_to_unit(input);
    EXPECT_FLOAT_EQ(result[2], 1.0f);
}

// Single duplicate in list (two elements, one repeated value handled via two-element test)
TEST(RescaleToUnit, ThreeElementsWithDuplicateAtEnds) {
    vector<float> input = {1.0f, 3.0f, 5.0f};
    vector<float> expected = {0.0f, 0.5f, 1.0f};
    assertVectorsNear(rescale_to_unit(input), expected);
}

// Input is not modified externally (pass by value)
TEST(RescaleToUnit, OriginalInputUnchanged) {
    vector<float> input = {1.0f, 2.0f, 3.0f};
    vector<float> original = input;
    rescale_to_unit(input);
    EXPECT_EQ(input, original);
}

// Result has same size as input
TEST(RescaleToUnit, OutputSizeMatchesInput) {
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f};
    vector<float> result = rescale_to_unit(input);
    EXPECT_EQ(result.size(), input.size());
}

// All values in result are in [0, 1]
TEST(RescaleToUnit, AllResultsInUnitInterval) {
    vector<float> input = {-50.0f, 0.0f, 25.0f, 75.0f, 100.0f};
    vector<float> result = rescale_to_unit(input);
    for (size_t i = 0; i < result.size(); i++) {
        EXPECT_GE(result[i], 0.0f) << "Element " << i << " is below 0";
        EXPECT_LE(result[i], 1.0f) << "Element " << i << " is above 1";
    }
}

// Large vector
TEST(RescaleToUnit, LargeVector) {
    vector<float> input;
    for (int i = 0; i <= 1000; i++) input.push_back((float)i);
    vector<float> result = rescale_to_unit(input);
    EXPECT_NEAR(result.front(), 0.0f, EPSILON);
    EXPECT_NEAR(result.back(), 1.0f, EPSILON);
    EXPECT_NEAR(result[500], 0.5f, EPSILON);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}