#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "longest.h" // Assuming the function is declared here

using namespace std;

TEST(LongestTest, EmptyVectorReturnsEmptyString) {
    vector<string> input;
    string result = longest(input);
    EXPECT_TRUE(result.empty());
}

TEST(LongestTest, SingleElementReturnsThatElement) {
    vector<string> input = {"hello"};
    string result = longest(input);
    EXPECT_EQ(result, "hello");
}

TEST(LongestTest, AllStringsSameLengthReturnsFirst) {
    vector<string> input = {"a", "b", "c"};
    string result = longest(input);
    EXPECT_EQ(result, "a");
}

TEST(LongestTest, IncreasingLengthsReturnsLongest) {
    vector<string> input = {"a", "bb", "ccc"};
    string result = longest(input);
    EXPECT_EQ(result, "ccc");
}

TEST(LongestTest, DecreasingLengthsReturnsLongest) {
    vector<string> input = {"ccc", "bb", "a"};
    string result = longest(input);
    EXPECT_EQ(result, "ccc");
}

TEST(LongestTest, MultipleLongestStringsReturnsFirstOccurrence) {
    vector<string> input = {"abc", "def", "ghi", "ab"};
    string result = longest(input);
    EXPECT_EQ(result, "abc");
}

TEST(LongestTest, EmptyStringInVector) {
    vector<string> input = {"", "a", "bb"};
    string result = longest(input);
    EXPECT_EQ(result, "bb");
}

TEST(LongestTest, AllEmptyStrings) {
    vector<string> input = {"", "", ""};
    string result = longest(input);
    EXPECT_TRUE(result.empty());
}

TEST(LongestTest, EmptyStringAndSingleChar) {
    vector<string> input = {"", "x"};
    string result = longest(input);
    EXPECT_EQ(result, "x");
}

TEST(LongestTest, VeryLongString) {
    string longStr = string(1000, 'a');
    vector<string> input = {"short", longStr, "medium"};
    string result = longest(input);
    EXPECT_EQ(result, longStr);
}

TEST(LongestTest, UnicodeStrings) {
    vector<string> input = {"árvore", "cão", "pássaro"};
    string result = longest(input);
    // Using length() which counts bytes, not codepoints
    // "árvore" has 7 bytes (á is 2 bytes in UTF-8)
    // "pássaro" has 8 bytes (á and ã are 2 bytes each)
    // "cão" has 4 bytes (ã is 2 bytes)
    EXPECT_EQ(result, "pássaro");
}

TEST(LongestTest, SingleCharacterVariations) {
    vector<string> input = {"a", "b", "c"};
    string result = longest(input);
    EXPECT_EQ(result, "a");
}

TEST(LongestTest, LargeVector) {
    vector<string> input;
    for (int i = 0; i < 10000; i++) {
        input.push_back(string(i % 100, 'a'));
    }
    string result = longest(input);
    EXPECT_EQ(result.length(), 99);
}

TEST(LongestTest, ExactlySameLengthDifferentContent) {
    vector<string> input = {"apple", "banana", "cherry"};
    // "apple" length 5, "banana" length 6, "cherry" length 6
    string result = longest(input);
    EXPECT_EQ(result, "banana");
}

TEST(LongestTest, WhitespaceStrings) {
    vector<string> input = {"   ", " ", "\t\t"};
    string result = longest(input);
    EXPECT_EQ(result, "   ");
}