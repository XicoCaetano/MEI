#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "filter_by_prefix.h" // Assume the function is declared here

using namespace std;

// Test fixture for filter_by_prefix function
class FilterByPrefixTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test empty input vector
TEST_F(FilterByPrefixTest, EmptyVector) {
    vector<string> input = {};
    string prefix = "a";
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_TRUE(result.empty());
}

// Test empty prefix
TEST_F(FilterByPrefixTest, EmptyPrefix) {
    vector<string> input = {"abc", "bcd", "cde", "test"};
    string prefix = "";
    vector<string> expected = {"abc", "bcd", "cde", "test"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test prefix matches some elements
TEST_F(FilterByPrefixTest, PrefixMatchesSomeElements) {
    vector<string> input = {"abc", "bcd", "cde", "vector"};
    string prefix = "a";
    vector<string> expected = {"abc", "vector"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test prefix matches all elements
TEST_F(FilterByPrefixTest, PrefixMatchesAllElements) {
    vector<string> input = {"alpha", "alphabet", "alpine", "altitude"};
    string prefix = "al";
    vector<string> expected = {"alpha", "alphabet", "alpine", "altitude"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test prefix matches no elements
TEST_F(FilterByPrefixTest, PrefixMatchesNoElements) {
    vector<string> input = {"beta", "gamma", "delta", "omega"};
    string prefix = "x";
    vector<string> expected = {};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_TRUE(result.empty());
}

// Test single element vector
TEST_F(FilterByPrefixTest, SingleElementMatching) {
    vector<string> input = {"hello"};
    string prefix = "he";
    vector<string> expected = {"hello"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

TEST_F(FilterByPrefixTest, SingleElementNotMatching) {
    vector<string> input = {"hello"};
    string prefix = "wo";
    vector<string> expected = {};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_TRUE(result.empty());
}

// Test prefix longer than string
TEST_F(FilterByPrefixTest, PrefixLongerThanString) {
    vector<string> input = {"abc", "abcdef", "ab"};
    string prefix = "abcdefg";
    vector<string> expected = {};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_TRUE(result.empty());
}

// Test prefix exactly matches some strings
TEST_F(FilterByPrefixTest, PrefixExactlyMatchesString) {
    vector<string> input = {"cat", "caterpillar", "cat", "dog", "cat"};
    string prefix = "cat";
    vector<string> expected = {"cat", "caterpillar", "cat", "cat"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test with special characters
TEST_F(FilterByPrefixTest, SpecialCharactersInPrefix) {
    vector<string> input = {"@test", "@example", "#comment", "@@user"};
    string prefix = "@";
    vector<string> expected = {"@test", "@example", "@@user"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test with numbers
TEST_F(FilterByPrefixTest, NumericPrefix) {
    vector<string> input = {"123abc", "123", "124abc", "12"};
    string prefix = "123";
    vector<string> expected = {"123abc", "123"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test case sensitivity
TEST_F(FilterByPrefixTest, CaseSensitive) {
    vector<string> input = {"Apple", "apple", "App", "apricot"};
    string prefix = "Ap";
    vector<string> expected = {"Apple", "App"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test with very long strings
TEST_F(FilterByPrefixTest, VeryLongStrings) {
    string longString1(1000, 'a');
    string longString2(1000, 'b');
    string prefix(500, 'a');
    
    vector<string> input = {longString1, longString2, "short"};
    vector<string> expected = {longString1};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test multiple matching characters
TEST_F(FilterByPrefixTest, MultipleCharacterPrefix) {
    vector<string> input = {"prefix_test", "prefix_example", "postfix", "pre"};
    string prefix = "pre";
    vector<string> expected = {"prefix_test", "prefix_example"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}

// Test whitespace handling
TEST_F(FilterByPrefixTest, WhitespacePrefix) {
    vector<string> input = {" hello", "  hello", " world", "hello"};
    string prefix = " ";
    vector<string> expected = {" hello", "  hello"};
    vector<string> result = filter_by_prefix(input, prefix);
    EXPECT_EQ(result, expected);
}