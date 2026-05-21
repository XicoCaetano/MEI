#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

// Include the function to test (in real test file, this would be in a header)
// vector<int> remove_duplicates(vector<int> numbers);

class RemoveDuplicatesTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(RemoveDuplicatesTest, EmptyVector) {
    vector<int> input;
    vector<int> expected;
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, SingleElement) {
    vector<int> input = {1};
    vector<int> expected = {1};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, AllUniqueElements) {
    vector<int> input = {1, 2, 3, 4, 5};
    vector<int> expected = {1, 2, 3, 4, 5};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, AllDuplicates) {
    vector<int> input = {1, 1, 1, 1, 1};
    vector<int> expected = {};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, ConsecutiveDuplicates) {
    vector<int> input = {1, 2, 2, 3, 4, 4, 5};
    vector<int> expected = {1, 3, 5};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, NonConsecutiveDuplicates) {
    vector<int> input = {1, 2, 3, 2, 4, 1, 5};
    vector<int> expected = {3, 4, 5};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, MultipleOccurrences) {
    vector<int> input = {1, 2, 1, 3, 2, 4, 3, 5, 1, 2};
    vector<int> expected = {4, 5};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, NegativeNumbers) {
    vector<int> input = {-1, 2, -1, 3, 2, -2};
    vector<int> expected = {3, -2};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, MixedPositiveNegative) {
    vector<int> input = {0, -1, 0, 1, 2, -1, 3};
    vector<int> expected = {1, 2, 3};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, ZeroAndDuplicates) {
    vector<int> input = {0, 5, 0, 3, 5, 2, 0};
    vector<int> expected = {3, 2};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, AllElementsSameValue) {
    vector<int> input = {42, 42, 42, 42};
    vector<int> expected = {};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, TwoElementsSame) {
    vector<int> input = {5, 5};
    vector<int> expected = {};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, TwoElementsDifferent) {
    vector<int> input = {5, 6};
    vector<int> expected = {5, 6};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, LargeValues) {
    vector<int> input = {1000, 2000, 1000, 3000, 2000, 4000};
    vector<int> expected = {3000, 4000};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, TripletAppearsTwice) {
    vector<int> input = {1, 2, 3, 1, 2, 3};
    vector<int> expected = {};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, SingleElementRemoved) {
    vector<int> input = {1, 2, 1, 3, 4};
    vector<int> expected = {2, 3, 4};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, FirstElementDuplicate) {
    vector<int> input = {1, 2, 3, 4, 1};
    vector<int> expected = {2, 3, 4};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, LastElementDuplicate) {
    vector<int> input = {1, 2, 3, 4, 4};
    vector<int> expected = {1, 2, 3};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, AlternatingDuplicates) {
    vector<int> input = {1, 2, 1, 2, 1, 2};
    vector<int> expected = {};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, NoRemovalSingleEach) {
    vector<int> input = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> expected = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    vector<int> result = remove_duplicates(input);
    EXPECT_EQ(result, expected);
}

TEST_F(RemoveDuplicatesTest, LargeVectorPerformance) {
    vector<int> input;
    for (int i = 0; i < 1000; i++) {
        input.push_back(i % 100);
    }
    vector<int> result = remove_duplicates(input);
    for (int i = 0; i < 100; i++) {
        int count = 0;
        for (int val : input) {
            if (val == i) count++;
        }
        if (count == 1) {
            EXPECT_NE(find(result.begin(), result.end(), i), result.end());
        } else if (count > 1) {
            EXPECT_EQ(find(result.begin(), result.end(), i), result.end());
        }
    }
}
