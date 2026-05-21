#include <gtest/gtest.h>
#include <vector>
#include <cmath>
using namespace std;

vector<float> find_closest_elements(vector<float> numbers){
    vector<float> out={};
    for (int i=0;i<numbers.size();i++)
    for (int j=i+1;j<numbers.size();j++)
        if (out.size()==0 or abs(numbers[i]-numbers[j])<abs(out[0]-out[1]))
            out={numbers[i],numbers[j]};
    if (out[0]>out[1])
        out={out[1],out[0]};
    return out;
}

TEST(FindClosestElementsTest, BasicExampleWithDistinctClosest) {
    vector<float> input = {1.0, 2.0, 3.0, 4.0, 5.0, 2.2};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 2.0f);
    EXPECT_FLOAT_EQ(result[1], 2.2f);
}

TEST(FindClosestElementsTest, BasicExampleWithDuplicates) {
    vector<float> input = {1.0, 2.0, 3.0, 4.0, 5.0, 2.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 2.0f);
    EXPECT_FLOAT_EQ(result[1], 2.0f);
}

TEST(FindClosestElementsTest, TwoElementsAlreadySorted) {
    vector<float> input = {1.0, 5.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 1.0f);
    EXPECT_FLOAT_EQ(result[1], 5.0f);
}

TEST(FindClosestElementsTest, TwoElementsReversed) {
    vector<float> input = {5.0, 1.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 1.0f);
    EXPECT_FLOAT_EQ(result[1], 5.0f);
}

TEST(FindClosestElementsTest, TwoIdenticalElements) {
    vector<float> input = {3.0, 3.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 3.0f);
    EXPECT_FLOAT_EQ(result[1], 3.0f);
}

TEST(FindClosestElementsTest, ResultOrderedSmallerFirst) {
    vector<float> input = {10.0, 3.0, 7.0, 3.5};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], 3.0f);
    EXPECT_FLOAT_EQ(result[1], 3.5f);
}

TEST(FindClosestElementsTest, NegativeNumbers) {
    vector<float> input = {-5.0, -3.0, -1.0, -4.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], -5.0f);
    EXPECT_FLOAT_EQ(result[1], -4.0f);
}

TEST(FindClosestElementsTest, MixedPositiveAndNegative) {
    vector<float> input = {-1.0, 0.0, 1.0, 5.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], -1.0f);
    EXPECT_FLOAT_EQ(result[1], 0.0f);
}

TEST(FindClosestElementsTest, AllIdenticalElements) {
    vector<float> input = {7.0, 7.0, 7.0, 7.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 7.0f);
    EXPECT_FLOAT_EQ(result[1], 7.0f);
}

TEST(FindClosestElementsTest, LargeVector) {
    vector<float> input;
    for (int i = 0; i < 100; i++) {
        input.push_back(static_cast<float>(i * 10));
    }
    input.push_back(505.0f);
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], 500.0f);
    EXPECT_FLOAT_EQ(result[1], 505.0f);
}

TEST(FindClosestElementsTest, FloatingPointPrecision) {
    vector<float> input = {1.0f, 1.1f, 1.11f, 5.0f};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], 1.1f);
    EXPECT_FLOAT_EQ(result[1], 1.11f);
}

TEST(FindClosestElementsTest, ClosestPairAtEnd) {
    vector<float> input = {1.0, 10.0, 20.0, 30.0, 29.5};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], 29.5f);
    EXPECT_FLOAT_EQ(result[1], 30.0f);
}

TEST(FindClosestElementsTest, ClosestPairAtBeginning) {
    vector<float> input = {1.0, 1.5, 10.0, 20.0, 30.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], 1.0f);
    EXPECT_FLOAT_EQ(result[1], 1.5f);
}

TEST(FindClosestElementsTest, NegativeAndZero) {
    vector<float> input = {-0.5f, 0.0f, -10.0f, 100.0f};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
    EXPECT_FLOAT_EQ(result[0], -0.5f);
    EXPECT_FLOAT_EQ(result[1], 0.0f);
}

TEST(FindClosestElementsTest, ReturnSizeIsAlwaysTwo) {
    vector<float> input = {3.0, 1.0, 4.0, 1.5, 9.0, 2.6};
    vector<float> result = find_closest_elements(input);
    EXPECT_EQ(result.size(), 2);
}

TEST(FindClosestElementsTest, OutputAlwaysSortedAscending) {
    vector<float> input = {9.0, 8.9, 1.0, 50.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_LE(result[0], result[1]);
}

TEST(FindClosestElementsTest, ThreeElementsClosestIsFirstTwo) {
    vector<float> input = {1.0, 1.2, 5.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 1.0f);
    EXPECT_FLOAT_EQ(result[1], 1.2f);
}

TEST(FindClosestElementsTest, ThreeElementsClosestIsLastTwo) {
    vector<float> input = {1.0, 4.8, 5.0};
    vector<float> result = find_closest_elements(input);
    ASSERT_EQ(result.size(), 2);
    EXPECT_FLOAT_EQ(result[0], 4.8f);
    EXPECT_FLOAT_EQ(result[1], 5.0f);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}