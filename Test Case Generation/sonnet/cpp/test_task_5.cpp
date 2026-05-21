#include <gtest/gtest.h>
#include <vector>
using namespace std;

vector<int> intersperse(vector<int> numbers, int delimeter){
    vector<int> out={};
    if (numbers.size()>0) out.push_back(numbers[0]);
    for (int i=1;i<numbers.size();i++)
    {
        out.push_back(delimeter);
        out.push_back(numbers[i]);
    }
    return out;
}

TEST(IntersperseTest, EmptyVector) {
    vector<int> result = intersperse({}, 4);
    EXPECT_TRUE(result.empty());
}

TEST(IntersperseTest, SingleElement) {
    vector<int> result = intersperse({7}, 4);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 7);
}

TEST(IntersperseTest, TwoElements) {
    vector<int> result = intersperse({1, 2}, 4);
    vector<int> expected = {1, 4, 2};
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, ThreeElements) {
    vector<int> result = intersperse({1, 2, 3}, 4);
    vector<int> expected = {1, 4, 2, 4, 3};
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, MultipleElements) {
    vector<int> result = intersperse({10, 20, 30, 40, 50}, 0);
    vector<int> expected = {10, 0, 20, 0, 30, 0, 40, 0, 50};
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, NegativeDelimeter) {
    vector<int> result = intersperse({1, 2, 3}, -1);
    vector<int> expected = {1, -1, 2, -1, 3};
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, NegativeNumbers) {
    vector<int> result = intersperse({-3, -2, -1}, 0);
    vector<int> expected = {-3, 0, -2, 0, -1};
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, ZeroDelimeter) {
    vector<int> result = intersperse({1, 2, 3}, 0);
    vector<int> expected = {1, 0, 2, 0, 3};
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, DelimeterSameAsElements) {
    vector<int> result = intersperse({5, 5, 5}, 5);
    vector<int> expected = {5, 5, 5, 5, 5};
    ASSERT_EQ(result.size(), expected.size());
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, OutputSizeIsCorrect) {
    vector<int> input = {1, 2, 3, 4, 5};
    vector<int> result = intersperse(input, 9);
    size_t expected_size = 2 * input.size() - 1;
    EXPECT_EQ(result.size(), expected_size);
}

TEST(IntersperseTest, OutputSizeSingleElement) {
    vector<int> input = {42};
    vector<int> result = intersperse(input, 9);
    EXPECT_EQ(result.size(), 1u);
}

TEST(IntersperseTest, OutputSizeEmpty) {
    vector<int> input = {};
    vector<int> result = intersperse(input, 9);
    EXPECT_EQ(result.size(), 0u);
}

TEST(IntersperseTest, LargeVector) {
    vector<int> input(100, 1);
    vector<int> result = intersperse(input, 2);
    ASSERT_EQ(result.size(), 199u);
    for (int i = 0; i < 199; i++) {
        if (i % 2 == 0) {
            EXPECT_EQ(result[i], 1) << "Expected 1 at index " << i;
        } else {
            EXPECT_EQ(result[i], 2) << "Expected delimiter 2 at index " << i;
        }
    }
}

TEST(IntersperseTest, DelimeterAppearsCorrectNumberOfTimes) {
    vector<int> input = {1, 2, 3, 4};
    int delimeter = 99;
    vector<int> result = intersperse(input, delimeter);
    int count = 0;
    for (int val : result) {
        if (val == delimeter) count++;
    }
    EXPECT_EQ(count, (int)input.size() - 1);
}

TEST(IntersperseTest, OriginalVectorUnchanged) {
    vector<int> input = {1, 2, 3};
    vector<int> original = input;
    intersperse(input, 4);
    EXPECT_EQ(input, original);
}

TEST(IntersperseTest, IntMinDelimeter) {
    vector<int> result = intersperse({1, 2}, INT_MIN);
    vector<int> expected = {1, INT_MIN, 2};
    EXPECT_EQ(result, expected);
}

TEST(IntersperseTest, IntMaxDelimeter) {
    vector<int> result = intersperse({1, 2}, INT_MAX);
    vector<int> expected = {1, INT_MAX, 2};
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}