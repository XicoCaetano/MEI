#include <gtest/gtest.h>
#include <string>
#include <vector>
#include <algorithm>

// Function prototype
int count_distinct_characters(std::string str);

// Test case for basic functionality with unique lowercase characters
TEST(CountDistinctCharactersTest, BasicUniqueCharacters) {
    EXPECT_EQ(count_distinct_characters("abc"), 3);
    EXPECT_EQ(count_distinct_characters("xyz"), 3);
}

// Test case for case insensitivity (Requirement: regardless of case)
TEST(CountDistinctCharactersTest, CaseInsensitivity) {
    EXPECT_EQ(count_distinct_characters("xyzXYZ"), 3);
    EXPECT_EQ(count_distinct_characters("aA"), 1);
    EXPECT_EQ(count_distinct_characters("Jerry"), 4); // J, e, r, y
}

// Test case for empty string (Edge case)
TEST(CountDistinctCharactersTest, EmptyString) {
    EXPECT_EQ(count_distinct_characters(""), 0);
}

// Test case for strings with all identical characters
TEST(CountDistinctCharactersTest, IdenticalCharacters) {
    EXPECT_EQ(count_distinct_characters("aaaaa"), 1);
    EXPECT_EQ(count_distinct_characters("AAAAA"), 1);
}

// Test case for strings with numbers and special characters
TEST(CountDistinctCharactersTest, SpecialCharactersAndNumbers) {
    EXPECT_EQ(count_distinct_characters("112233"), 3);
    EXPECT_EQ(count_distinct_characters("!@#!@#"), 3);
    EXPECT_EQ(count_distinct_characters("a1!A1!"), 3); // a, 1, !
}

// Test case for strings with spaces
TEST(CountDistinctCharactersTest, Spaces) {
    EXPECT_EQ(count_distinct_characters("a b c"), 4); // a, b, c, space
    EXPECT_EQ(count_distinct_characters("   "), 1);   // single distinct space
}

// Test case for long strings to ensure loop logic consistency
TEST(CountDistinctCharactersTest, LongString) {
    std::string longStr = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    // 26 letters + 10 digits = 36 distinct
    EXPECT_EQ(count_distinct_characters(longStr), 36);
}