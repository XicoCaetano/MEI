#include <gtest/gtest.h>
#include <vector>
#include <algorithm>

using namespace std;

// Função original para teste
vector<int> remove_duplicates(vector<int> numbers) {
    vector<int> out = {};
    vector<int> has1 = {};
    vector<int> has2 = {};
    for (int i = 0; i < numbers.size(); i++) {
        if (find(has2.begin(), has2.end(), numbers[i]) != has2.end()) continue;
        if (find(has1.begin(), has1.end(), numbers[i]) != has1.end()) {
            has2.push_back(numbers[i]);
        }
        else has1.push_back(numbers[i]);
    }
    for (int i = 0; i < numbers.size(); i++)
        if (find(has2.begin(), has2.end(), numbers[i]) == has2.end())
            out.push_back(numbers[i]);
    return out;
}

// Suite de Testes Unitários
class RemoveDuplicatesTest : public ::testing::Test {};

TEST_F(RemoveDuplicatesTest, HandlesEmptyVector) {
    vector<int> input = {};
    vector<int> expected = {};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesNoDuplicates) {
    vector<int> input = {1, 2, 3, 4, 5};
    vector<int> expected = {1, 2, 3, 4, 5};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesSingleDuplicate) {
    vector<int> input = {1, 2, 3, 2, 4};
    vector<int> expected = {1, 3, 4};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesMultipleDuplicates) {
    vector<int> input = {1, 2, 1, 3, 2, 4};
    vector<int> expected = {3, 4};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesAllIdenticalElements) {
    vector<int> input = {7, 7, 7, 7};
    vector<int> expected = {};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesTriplicates) {
    vector<int> input = {1, 2, 2, 2, 3};
    vector<int> expected = {1, 3};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, MaintainsOriginalOrder) {
    vector<int> input = {10, 5, 8, 5, 2};
    vector<int> expected = {10, 8, 2};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesNegativeNumbers) {
    vector<int> input = {-1, -2, -1, 0, 5};
    vector<int> expected = {-2, 0, 5};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesSingleElement) {
    vector<int> input = {42};
    vector<int> expected = {42};
    EXPECT_EQ(remove_duplicates(input), expected);
}

TEST_F(RemoveDuplicatesTest, HandlesConsecutiveDuplicates) {
    vector<int> input = {1, 1, 2, 2, 3, 3};
    vector<int> expected = {};
    EXPECT_EQ(remove_duplicates(input), expected);
}