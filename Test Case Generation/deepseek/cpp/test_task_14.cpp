#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "all_prefixes.h" // Assume the function is declared in this header

using namespace std;

TEST(AllPrefixesTest, EmptyString) {
    vector<string> result = all_prefixes("");
    EXPECT_TRUE(result.empty());
}

TEST(AllPrefixesTest, SingleCharacter) {
    vector<string> result = all_prefixes("a");
    vector<string> expected = {"a"};
    EXPECT_EQ(result, expected);
}

TEST(AllPrefixesTest, ThreeCharacters) {
    vector<string> result = all_prefixes("abc");
    vector<string> expected = {"a", "ab", "abc"};
    EXPECT_EQ(result, expected);
}

TEST(AllPrefixesTest, StringWithSpaces) {
    vector<string> result = all_prefixes("hello world");
    vector<string> expected = {"h", "he", "hel", "hell", "hello", "hello ", "hello w", "hello wo", "hello wor", "hello worl", "hello world"};
    EXPECT_EQ(result, expected);
}

TEST(AllPrefixesTest, StringWithNumbers) {
    vector<string> result = all_prefixes("123");
    vector<string> expected = {"1", "12", "123"};
    EXPECT_EQ(result, expected);
}

TEST(AllPrefixesTest, StringWithSpecialCharacters) {
    vector<string> result = all_prefixes("!@#");
    vector<string> expected = {"!", "!@", "!@#"};
    EXPECT_EQ(result, expected);
}

TEST(AllPrefixesTest, LongString) {
    string longStr(100, 'x');
    vector<string> result = all_prefixes(longStr);
    EXPECT_EQ(result.size(), 100);
    for (size_t i = 0; i < 100; ++i) {
        EXPECT_EQ(result[i], string(i + 1, 'x'));
    }
}

TEST(AllPrefixesTest, UnicodeCharacters) {
    vector<string> result = all_prefixes("こんにちは");
    vector<string> expected = {"こ", "こん", "こんに", "こんにち", "こんにちは"};
    EXPECT_EQ(result, expected);
}

TEST(AllPrefixesTest, MixedCase) {
    vector<string> result = all_prefixes("AbC");
    vector<string> expected = {"A", "Ab", "AbC"};
    EXPECT_EQ(result, expected);
}

TEST(AllPrefixesTest, RepeatedCharacters) {
    vector<string> result = all_prefixes("aaaa");
    vector<string> expected = {"a", "aa", "aaa", "aaaa"};
    EXPECT_EQ(result, expected);
}