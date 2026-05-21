#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

vector<string> filter_by_substring(vector<string> strings, string substring);

TEST(FilterBySubstringTest, EmptyInputVector) {
    EXPECT_EQ(filter_by_substring({}, "a"), vector<string>{});
}

TEST(FilterBySubstringTest, BasicExample) {
    vector<string> input = {"abc", "bacd", "cde", "vector"};
    vector<string> expected = {"abc", "bacd", "vector"};
    EXPECT_EQ(filter_by_substring(input, "a"), expected);
}

TEST(FilterBySubstringTest, NoMatchFound) {
    vector<string> input = {"hello", "world", "foo"};
    EXPECT_EQ(filter_by_substring(input, "z"), vector<string>{});
}

TEST(FilterBySubstringTest, AllMatch) {
    vector<string> input = {"apple", "application", "apt"};
    vector<string> expected = {"apple", "application", "apt"};
    EXPECT_EQ(filter_by_substring(input, "ap"), expected);
}

TEST(FilterBySubstringTest, EmptySubstring) {
    vector<string> input = {"abc", "def", "ghi"};
    vector<string> expected = {"abc", "def", "ghi"};
    EXPECT_EQ(filter_by_substring(input, ""), expected);
}

TEST(FilterBySubstringTest, EmptySubstringEmptyInput) {
    EXPECT_EQ(filter_by_substring({}, ""), vector<string>{});
}

TEST(FilterBySubstringTest, SubstringEqualsFullString) {
    vector<string> input = {"abc", "ab", "a"};
    vector<string> expected = {"abc"};
    EXPECT_EQ(filter_by_substring(input, "abc"), expected);
}

TEST(FilterBySubstringTest, SubstringLongerThanStrings) {
    vector<string> input = {"ab", "cd", "ef"};
    EXPECT_EQ(filter_by_substring(input, "abcd"), vector<string>{});
}

TEST(FilterBySubstringTest, SingleCharSubstring) {
    vector<string> input = {"cat", "dog", "car", "bar"};
    vector<string> expected = {"cat", "car", "bar"};
    EXPECT_EQ(filter_by_substring(input, "a"), expected);
}

TEST(FilterBySubstringTest, SubstringAtBeginning) {
    vector<string> input = {"prefix_one", "prefix_two", "other"};
    vector<string> expected = {"prefix_one", "prefix_two"};
    EXPECT_EQ(filter_by_substring(input, "prefix"), expected);
}

TEST(FilterBySubstringTest, SubstringAtEnd) {
    vector<string> input = {"one_suffix", "two_suffix", "other"};
    vector<string> expected = {"one_suffix", "two_suffix"};
    EXPECT_EQ(filter_by_substring(input, "suffix"), expected);
}

TEST(FilterBySubstringTest, SubstringInMiddle) {
    vector<string> input = {"abcde", "fghij", "xbcdz"};
    vector<string> expected = {"abcde", "xbcdz"};
    EXPECT_EQ(filter_by_substring(input, "bcd"), expected);
}

TEST(FilterBySubstringTest, CaseSensitive) {
    vector<string> input = {"Hello", "hello", "HELLO"};
    vector<string> expected = {"hello"};
    EXPECT_EQ(filter_by_substring(input, "hello"), expected);
}

TEST(FilterBySubstringTest, CaseSensitiveUppercase) {
    vector<string> input = {"Hello", "hello", "HELLO"};
    vector<string> expected = {"HELLO"};
    EXPECT_EQ(filter_by_substring(input, "HELLO"), expected);
}

TEST(FilterBySubstringTest, EmptyStringsInVector) {
    vector<string> input = {"", "", ""};
    vector<string> expected = {"", "", ""};
    EXPECT_EQ(filter_by_substring(input, ""), expected);
}

TEST(FilterBySubstringTest, EmptyStringInVectorNoMatch) {
    vector<string> input = {"", "abc", ""};
    vector<string> expected = {"abc"};
    EXPECT_EQ(filter_by_substring(input, "abc"), expected);
}

TEST(FilterBySubstringTest, SingleElementMatchingVector) {
    vector<string> input = {"hello"};
    vector<string> expected = {"hello"};
    EXPECT_EQ(filter_by_substring(input, "ell"), expected);
}

TEST(FilterBySubstringTest, SingleElementNonMatchingVector) {
    vector<string> input = {"hello"};
    EXPECT_EQ(filter_by_substring(input, "xyz"), vector<string>{});
}

TEST(FilterBySubstringTest, SpecialCharacters) {
    vector<string> input = {"he.lo", "wor*d", "foo"};
    vector<string> expected = {"he.lo"};
    EXPECT_EQ(filter_by_substring(input, "."), expected);
}

TEST(FilterBySubstringTest, SubstringWithSpaces) {
    vector<string> input = {"hello world", "hello", "world"};
    vector<string> expected = {"hello world"};
    EXPECT_EQ(filter_by_substring(input, "hello world"), expected);
}

TEST(FilterBySubstringTest, RepeatedSubstring) {
    vector<string> input = {"aaa", "aa", "a", "b"};
    vector<string> expected = {"aaa", "aa", "a"};
    EXPECT_EQ(filter_by_substring(input, "a"), expected);
}

TEST(FilterBySubstringTest, NumericStrings) {
    vector<string> input = {"123", "456", "12", "789"};
    vector<string> expected = {"123", "12"};
    EXPECT_EQ(filter_by_substring(input, "12"), expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}