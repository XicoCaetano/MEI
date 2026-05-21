#include <gtest/gtest.h>
#include <vector>
using namespace std;

vector<int> rolling_max(vector<int> numbers){
    vector<int> out;
    int max=0;
    for (int i=0;i<numbers.size();i++)
    {
        if (numbers[i]>max) max=numbers[i];
        out.push_back(max);
    }
    return out;
}

TEST(RollingMaxTest, ExampleFromDocstring) {
    vector<int> input = {1, 2, 3, 2, 3, 4, 2};
    vector<int> expected = {1, 2, 3, 3, 3, 4, 4};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, EmptyVector) {
    vector<int> input = {};
    vector<int> expected = {};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, SingleElement) {
    vector<int> input = {5};
    vector<int> expected = {5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, SingleZeroElement) {
    vector<int> input = {0};
    vector<int> expected = {0};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, AllSameElements) {
    vector<int> input = {3, 3, 3, 3};
    vector<int> expected = {3, 3, 3, 3};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, StrictlyIncreasing) {
    vector<int> input = {1, 2, 3, 4, 5};
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, StrictlyDecreasing) {
    vector<int> input = {5, 4, 3, 2, 1};
    vector<int> expected = {5, 5, 5, 5, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, AllZeros) {
    vector<int> input = {0, 0, 0, 0};
    vector<int> expected = {0, 0, 0, 0};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, AllNegativeNumbers) {
    // NOTE: Due to max initialized to 0, negative-only input returns 0s
    vector<int> input = {-1, -2, -3};
    vector<int> expected = {0, 0, 0};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, MixedPositiveAndNegative) {
    vector<int> input = {-3, -1, 2, 1, 4, -2};
    vector<int> expected = {0, 0, 2, 2, 4, 4};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, NegativeFollowedByPositive) {
    vector<int> input = {-5, -3, 1, 0, 3};
    vector<int> expected = {0, 0, 1, 1, 3};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, MaxAtEnd) {
    vector<int> input = {1, 1, 1, 10};
    vector<int> expected = {1, 1, 1, 10};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, MaxAtBeginning) {
    vector<int> input = {10, 1, 1, 1};
    vector<int> expected = {10, 10, 10, 10};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, MaxInMiddle) {
    vector<int> input = {1, 5, 3, 2};
    vector<int> expected = {1, 5, 5, 5};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, TwoElements_Increasing) {
    vector<int> input = {1, 2};
    vector<int> expected = {1, 2};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, TwoElements_Decreasing) {
    vector<int> input = {2, 1};
    vector<int> expected = {2, 2};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, TwoElements_Equal) {
    vector<int> input = {3, 3};
    vector<int> expected = {3, 3};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, LargeValues) {
    vector<int> input = {1000000, 999999, 1000001, 500000};
    vector<int> expected = {1000000, 1000000, 1000001, 1000001};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, OutputSizeMatchesInputSize) {
    vector<int> input = {4, 2, 7, 1, 9};
    vector<int> result = rolling_max(input);
    EXPECT_EQ(result.size(), input.size());
}

TEST(RollingMaxTest, OutputIsNonDecreasing) {
    vector<int> input = {3, 1, 4, 1, 5, 9, 2, 6};
    vector<int> result = rolling_max(input);
    for (size_t i = 1; i < result.size(); i++) {
        EXPECT_GE(result[i], result[i-1]);
    }
}

TEST(RollingMaxTest, FirstElementReflectedCorrectly_Positive) {
    vector<int> input = {7, 1, 2};
    vector<int> result = rolling_max(input);
    EXPECT_EQ(result[0], 7);
}

TEST(RollingMaxTest, FirstElementReflectedCorrectly_Zero) {
    vector<int> input = {0, 5, 3};
    vector<int> result = rolling_max(input);
    EXPECT_EQ(result[0], 0);
}

TEST(RollingMaxTest, SingleNegativeElement) {
    // max initialized to 0, so negative single element yields 0
    vector<int> input = {-10};
    vector<int> expected = {0};
    EXPECT_EQ(rolling_max(input), expected);
}

TEST(RollingMaxTest, AlternatingUpDown) {
    vector<int> input = {1, 3, 2, 5, 4, 7, 6};
    vector<int> expected = {1, 3, 3, 5, 5, 7, 7};
    EXPECT_EQ(rolling_max(input), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}