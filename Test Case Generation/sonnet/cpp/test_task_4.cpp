#include <gtest/gtest.h>
#include <vector>
#include <cmath>
using namespace std;

float mean_absolute_deviation(vector<float> numbers){
    float sum=0;
    float avg,msum,mavg;
    int i=0;
    for (i=0;i<numbers.size();i++)
        sum+=numbers[i];
    avg=sum/numbers.size();
    msum=0;
    for (i=0;i<numbers.size();i++)
        msum+=abs(numbers[i]-avg);
    return msum/numbers.size();
}

const float EPSILON = 1e-4f;

TEST(MeanAbsoluteDeviationTest, ExampleFromDocstring) {
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 1.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, SingleElement) {
    vector<float> input = {42.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 0.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, TwoElements) {
    vector<float> input = {0.0f, 10.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 5.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, AllSameElements) {
    vector<float> input = {5.0f, 5.0f, 5.0f, 5.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 0.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, AllZeros) {
    vector<float> input = {0.0f, 0.0f, 0.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 0.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, NegativeNumbers) {
    vector<float> input = {-4.0f, -3.0f, -2.0f, -1.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 1.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, MixedPositiveAndNegative) {
    vector<float> input = {-2.0f, -1.0f, 1.0f, 2.0f};
    float expected = 1.5f;
    EXPECT_NEAR(mean_absolute_deviation(input), expected, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, MixedPositiveAndNegativeSymmetric) {
    vector<float> input = {-3.0f, 0.0f, 3.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 2.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, FloatingPointValues) {
    vector<float> input = {1.5f, 2.5f, 3.5f, 4.5f};
    EXPECT_NEAR(mean_absolute_deviation(input), 1.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, LargeValues) {
    vector<float> input = {1000.0f, 2000.0f, 3000.0f, 4000.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 1000.0f, 0.1f);
}

TEST(MeanAbsoluteDeviationTest, SmallDecimalValues) {
    vector<float> input = {0.1f, 0.2f, 0.3f, 0.4f};
    EXPECT_NEAR(mean_absolute_deviation(input), 0.1f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, TwoElementsNegative) {
    vector<float> input = {-10.0f, -20.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 5.0f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, ThreeElementsKnownResult) {
    vector<float> input = {2.0f, 4.0f, 6.0f};
    float expected = (4.0f/3.0f);
    EXPECT_NEAR(mean_absolute_deviation(input), expected, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, FiveElements) {
    vector<float> input = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    EXPECT_NEAR(mean_absolute_deviation(input), 1.2f, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, ReturnsFloat) {
    vector<float> input = {1.0f, 2.0f, 3.0f};
    float result = mean_absolute_deviation(input);
    EXPECT_TRUE(std::is_same<decltype(result), float>::value);
}

TEST(MeanAbsoluteDeviationTest, NonSymmetricValues) {
    vector<float> input = {1.0f, 1.0f, 1.0f, 7.0f};
    float mean = 10.0f / 4.0f;
    float expected = (3 * abs(1.0f - mean) + abs(7.0f - mean)) / 4.0f;
    EXPECT_NEAR(mean_absolute_deviation(input), expected, EPSILON);
}

TEST(MeanAbsoluteDeviationTest, ZeroAndPositive) {
    vector<float> input = {0.0f, 0.0f, 6.0f};
    float expected = 2.0f * (2.0f / 3.0f) + (1.0f * 4.0f / 3.0f);
    float mean = 2.0f;
    float e = (abs(0.0f - mean) + abs(0.0f - mean) + abs(6.0f - mean)) / 3.0f;
    EXPECT_NEAR(mean_absolute_deviation(input), e, EPSILON);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}