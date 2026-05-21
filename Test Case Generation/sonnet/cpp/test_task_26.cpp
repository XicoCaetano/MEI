#include <gtest/gtest.h>
#include <vector>
using namespace std;

vector<int> remove_duplicates(vector<int> numbers);

TEST(RemoveDuplicatesTest, EmptyVector) {
    EXPECT_EQ(remove_duplicates({}), vector<int>{});
}

TEST(RemoveDuplicatesTest, SingleElement) {
    EXPECT_EQ(remove_duplicates({42}), vector<int>{42});
}

TEST(RemoveDuplicatesTest, AllUnique) {
    EXPECT_EQ(remove_duplicates({1, 2, 3, 4, 5}), (vector<int>{1, 2, 3, 4, 5}));
}

TEST(RemoveDuplicatesTest, AllDuplicates) {
    EXPECT_EQ(remove_duplicates({1, 1, 2, 2, 3, 3}), vector<int>{});
}

TEST(RemoveDuplicatesTest, ExampleFromDocstring) {
    EXPECT_EQ(remove_duplicates({1, 2, 3, 2, 4}), (vector<int>{1, 3, 4}));
}

TEST(RemoveDuplicatesTest, DuplicateAtBeginning) {
    EXPECT_EQ(remove_duplicates({1, 1, 2, 3}), (vector<int>{2, 3}));
}

TEST(RemoveDuplicatesTest, DuplicateAtEnd) {
    EXPECT_EQ(remove_duplicates({1, 2, 3, 3}), (vector<int>{1, 2}));
}

TEST(RemoveDuplicatesTest, DuplicateInMiddle) {
    EXPECT_EQ(remove_duplicates({1, 2, 2, 3}), (vector<int>{1, 3}));
}

TEST(RemoveDuplicatesTest, TriplicateElement) {
    EXPECT_EQ(remove_duplicates({1, 2, 2, 2, 3}), (vector<int>{1, 3}));
}

TEST(RemoveDuplicatesTest, MultipleTriplicates) {
    EXPECT_EQ(remove_duplicates({1, 1, 1, 2, 2, 2}), vector<int>{});
}

TEST(RemoveDuplicatesTest, ElementAppearsMoreThanThreeTimes) {
    EXPECT_EQ(remove_duplicates({5, 5, 5, 5, 5}), vector<int>{});
}

TEST(RemoveDuplicatesTest, PreservesOrderOfUniqueElements) {
    EXPECT_EQ(remove_duplicates({4, 3, 2, 1}), (vector<int>{4, 3, 2, 1}));
}

TEST(RemoveDuplicatesTest, PreservesOrderWithDuplicatesRemoved) {
    EXPECT_EQ(remove_duplicates({3, 1, 2, 1, 4, 3}), (vector<int>{2, 4}));
}

TEST(RemoveDuplicatesTest, NegativeNumbers) {
    EXPECT_EQ(remove_duplicates({-1, -2, -1, -3}), (vector<int>{-2, -3}));
}

TEST(RemoveDuplicatesTest, NegativeAndPositiveNumbers) {
    EXPECT_EQ(remove_duplicates({-1, 1, -1, 2}), (vector<int>{1, 2}));
}

TEST(RemoveDuplicatesTest, ZeroElement) {
    EXPECT_EQ(remove_duplicates({0, 1, 0, 2}), (vector<int>{1, 2}));
}

TEST(RemoveDuplicatesTest, ZeroNotDuplicated) {
    EXPECT_EQ(remove_duplicates({0, 1, 2}), (vector<int>{0, 1, 2}));
}

TEST(RemoveDuplicatesTest, TwoElementsBothSame) {
    EXPECT_EQ(remove_duplicates({7, 7}), vector<int>{});
}

TEST(RemoveDuplicatesTest, TwoElementsBothDifferent) {
    EXPECT_EQ(remove_duplicates({7, 8}), (vector<int>{7, 8}));
}

TEST(RemoveDuplicatesTest, LargeVectorAllUnique) {
    vector<int> input;
    for (int i = 0; i < 1000; i++) input.push_back(i);
    EXPECT_EQ(remove_duplicates(input), input);
}

TEST(RemoveDuplicatesTest, LargeVectorAllDuplicates) {
    vector<int> input;
    for (int i = 0; i < 500; i++) { input.push_back(i); input.push_back(i); }
    EXPECT_EQ(remove_duplicates(input), vector<int>{});
}

TEST(RemoveDuplicatesTest, MixedWithLargeValues) {
    EXPECT_EQ(remove_duplicates({INT_MAX, INT_MIN, INT_MAX}), (vector<int>{INT_MIN}));
}

TEST(RemoveDuplicatesTest, NonContiguousDuplicates) {
    EXPECT_EQ(remove_duplicates({1, 2, 3, 1}), (vector<int>{2, 3}));
}

TEST(RemoveDuplicatesTest, MultipleDuplicateGroupsMixed) {
    EXPECT_EQ(remove_duplicates({1, 2, 3, 2, 4, 1, 5}), (vector<int>{3, 4, 5}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}