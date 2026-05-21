#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

vector<string> filter_by_prefix(vector<string> strings, string prefix);

TEST(FilterByPrefixTest, EmptyInputVector) {
    vector<string> result = filter_by_prefix({}, "a");
    EXPECT_TRUE(result.empty());
}

TEST(FilterByPrefixTest, EmptyPrefix) {
    vector<string> input = {"abc", "bcd", "cde"};
    vector<string> result = filter_by_prefix(input, "");
    EXPECT_EQ(result, input);
}

TEST(FilterByPrefixTest, EmptyInputAndEmptyPrefix) {
    vector<string> result = filter_by_prefix({}, "");
    EXPECT_TRUE(result.empty());
}

TEST(FilterByPrefixTest, SingleMatchAtStart) {
    vector<string> input = {"abc", "bcd", "cde", "vector"};
    vector<string> result = filter_by_prefix(input, "a");
    vector<string> expected = {"abc"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, NoMatches) {
    vector<string> input = {"abc", "bcd", "cde"};
    vector<string> result = filter_by_prefix(input, "z");
    EXPECT_TRUE(result.empty());
}

TEST(FilterByPrefixTest, AllMatch) {
    vector<string> input = {"abc", "abd", "abe"};
    vector<string> result = filter_by_prefix(input, "ab");
    EXPECT_EQ(result, input);
}

TEST(FilterByPrefixTest, MultipleMatchesMixed) {
    vector<string> input = {"abc", "bcd", "axy", "cde", "aaa"};
    vector<string> result = filter_by_prefix(input, "a");
    vector<string> expected = {"abc", "axy", "aaa"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, PrefixLongerThanSomeStrings) {
    vector<string> input = {"a", "ab", "abc", "abcd"};
    vector<string> result = filter_by_prefix(input, "abc");
    vector<string> expected = {"abc", "abcd"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, PrefixEqualToString) {
    vector<string> input = {"abc", "abcd", "ab"};
    vector<string> result = filter_by_prefix(input, "abc");
    vector<string> expected = {"abc", "abcd"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, PrefixLongerThanAllStrings) {
    vector<string> input = {"a", "ab", "b"};
    vector<string> result = filter_by_prefix(input, "abcdef");
    EXPECT_TRUE(result.empty());
}

TEST(FilterByPrefixTest, SingleElementMatchingVector) {
    vector<string> input = {"hello"};
    vector<string> result = filter_by_prefix(input, "hel");
    vector<string> expected = {"hello"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, SingleElementNotMatchingVector) {
    vector<string> input = {"world"};
    vector<string> result = filter_by_prefix(input, "hel");
    EXPECT_TRUE(result.empty());
}

TEST(FilterByPrefixTest, CaseSensitiveNoMatch) {
    vector<string> input = {"Abc", "ABC", "abc"};
    vector<string> result = filter_by_prefix(input, "abc");
    vector<string> expected = {"abc"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, CaseSensitiveUpperCase) {
    vector<string> input = {"Abc", "ABC", "abc"};
    vector<string> result = filter_by_prefix(input, "A");
    vector<string> expected = {"Abc"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, NumericStrings) {
    vector<string> input = {"123", "456", "124", "789", "12"};
    vector<string> result = filter_by_prefix(input, "12");
    vector<string> expected = {"123", "124", "12"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, SpecialCharacterPrefix) {
    vector<string> input = {"!abc", "!xyz", "abc", "xyz"};
    vector<string> result = filter_by_prefix(input, "!");
    vector<string> expected = {"!abc", "!xyz"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, WhitespacePrefix) {
    vector<string> input = {" abc", "abc", " xyz", "xyz"};
    vector<string> result = filter_by_prefix(input, " ");
    vector<string> expected = {" abc", " xyz"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, PrefixIsEntireString) {
    vector<string> input = {"exact", "exactmatch", "exa"};
    vector<string> result = filter_by_prefix(input, "exact");
    vector<string> expected = {"exact", "exactmatch"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, OrderPreserved) {
    vector<string> input = {"apple", "banana", "apricot", "cherry", "avocado"};
    vector<string> result = filter_by_prefix(input, "a");
    vector<string> expected = {"apple", "apricot", "avocado"};
    EXPECT_EQ(result, expected);
}

TEST(FilterByPrefixTest, EmptyStringInVector) {
    vector<string> input = {"", "abc", "", "def"};
    vector<string> result = filter_by_prefix(input, "");
    EXPECT_EQ(result, input);
}

TEST(FilterByPrefixTest, EmptyStringInVectorWithNonEmptyPrefix) {
    vector<string> input = {"", "abc", "", "def"};
    vector<string> result = filter_by_prefix(input, "a");
    vector<string> expected = {"abc"};
    EXPECT_EQ(result, expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}