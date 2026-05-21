#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "filter_by_substring.h"  // Assumes the function is declared here

using namespace std;

// Test fixture for filter_by_substring tests
class FilterBySubstringTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test 1: Empty input vector
TEST_F(FilterBySubstringTest, EmptyVector) {
    vector<string> input;
    string substring = "a";
    vector<string> result = filter_by_substring(input, substring);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(0, result.size());
}

// Test 2: Empty substring
TEST_F(FilterBySubstringTest, EmptySubstring) {
    vector<string> input = {"abc", "def", "abc def"};
    string substring = "";
    vector<string> result = filter_by_substring(input, substring);
    
    // Empty substring is found in every string
    vector<string> expected = {"abc", "def", "abc def"};
    EXPECT_EQ(expected, result);
}

// Test 3: Substring present in multiple elements
TEST_F(FilterBySubstringTest, BasicFiltering) {
    vector<string> input = {"abc", "bacd", "cde", "vector"};
    string substring = "a";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"abc", "bacd", "vector"};
    EXPECT_EQ(expected, result);
}

// Test 4: No matches
TEST_F(FilterBySubstringTest, NoMatches) {
    vector<string> input = {"xyz", "123", "def"};
    string substring = "a";
    vector<string> result = filter_by_substring(input, substring);
    
    EXPECT_TRUE(result.empty());
}

// Test 5: Substring at beginning
TEST_F(FilterBySubstringTest, SubstringAtBeginning) {
    vector<string> input = {"apple", "apricot", "banana", "grape"};
    string substring = "ap";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"apple", "apricot"};
    EXPECT_EQ(expected, result);
}

// Test 6: Substring at end
TEST_F(FilterBySubstringTest, SubstringAtEnd) {
    vector<string> input = {"running", "jumping", "swimming", "walking"};
    string substring = "ing";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"running", "jumping", "swimming", "walking"};
    EXPECT_EQ(expected, result);
}

// Test 7: Substring in middle
TEST_F(FilterBySubstringTest, SubstringInMiddle) {
    vector<string> input = {"hello world", "good morning", "happy birthday", "test"};
    string substring = "o";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"hello world", "good morning"};
    EXPECT_EQ(expected, result);
}

// Test 8: Single element vector with match
TEST_F(FilterBySubstringTest, SingleElementMatch) {
    vector<string> input = {"hello"};
    string substring = "ell";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"hello"};
    EXPECT_EQ(expected, result);
}

// Test 9: Single element vector without match
TEST_F(FilterBySubstringTest, SingleElementNoMatch) {
    vector<string> input = {"hello"};
    string substring = "xyz";
    vector<string> result = filter_by_substring(input, substring);
    
    EXPECT_TRUE(result.empty());
}

// Test 10: Empty strings in vector
TEST_F(FilterBySubstringTest, EmptyStringsInVector) {
    vector<string> input = {"", "abc", "", "def", ""};
    string substring = "abc";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"abc"};
    EXPECT_EQ(expected, result);
}

// Test 11: Empty string in vector with empty substring
TEST_F(FilterBySubstringTest, EmptyStringVectorWithEmptySubstring) {
    vector<string> input = {"", "abc", ""};
    string substring = "";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"", "abc", ""};
    EXPECT_EQ(expected, result);
}

// Test 12: Substring with special characters
TEST_F(FilterBySubstringTest, SpecialCharacters) {
    vector<string> input = {"hello@world", "test#123", "hello#world", "normal"};
    string substring = "#";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"test#123", "hello#world"};
    EXPECT_EQ(expected, result);
}

// Test 13: Substring with spaces
TEST_F(FilterBySubstringTest, SubstringWithSpaces) {
    vector<string> input = {"hello world", "helloworld", "hello  world", "hi there"};
    string substring = "lo w";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"hello world"};
    EXPECT_EQ(expected, result);
}

// Test 14: Large vector
TEST_F(FilterBySubstringTest, LargeVector) {
    vector<string> input;
    for (int i = 0; i < 1000; ++i) {
        input.push_back("string_" + to_string(i));
    }
    
    string substring = "500";
    vector<string> result = filter_by_substring(input, substring);
    
    EXPECT_EQ(1, result.size());
    EXPECT_EQ("string_500", result[0]);
}

// Test 15: Substring appears multiple times in same string
TEST_F(FilterBySubstringTest, MultipleOccurrences) {
    vector<string> input = {"aaaa", "aaab", "baaa", "abc"};
    string substring = "aa";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"aaaa", "aaab", "baaa"};
    EXPECT_EQ(expected, result);
}

// Test 16: Case sensitivity
TEST_F(FilterBySubstringTest, CaseSensitivity) {
    vector<string> input = {"Hello", "hello", "HELLO", "HeLLo"};
    string substring = "Hell";
    vector<string> result = filter_by_substring(input, substring);
    
    // Only exact match with case sensitivity
    vector<string> expected = {"Hello"};
    EXPECT_EQ(expected, result);
}

// Test 17: Single character substring
TEST_F(FilterBySubstringTest, SingleCharacter) {
    vector<string> input = {"abc", "def", "ghi", "jkl"};
    string substring = "d";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"def"};
    EXPECT_EQ(expected, result);
}

// Test 18: Very long substring
TEST_F(FilterBySubstringTest, LongSubstring) {
    vector<string> input = {"short", "this is a very long string for testing", "medium"};
    string substring = "very long string for testing";
    vector<string> result = filter_by_substring(input, substring);
    
    vector<string> expected = {"this is a very long string for testing"};
    EXPECT_EQ(expected, result);
}

// Test 19: Substring longer than any string
TEST_F(FilterBySubstringTest, SubstringLongerThanString) {
    vector<string> input = {"short", "tiny", "small"};
    string substring = "verylongsubstring";
    vector<string> result = filter_by_substring(input, substring);
    
    EXPECT_TRUE(result.empty());
}

// Test 20: Verify no modification of original vector
TEST_F(FilterBySubstringTest, OriginalVectorUnmodified) {
    vector<string> input = {"abc", "def", "ghi"};
    vector<string> original = input;
    string substring = "d";
    
    filter_by_substring(input, substring);
    
    EXPECT_EQ(original, input);
}

// Main function for running tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}