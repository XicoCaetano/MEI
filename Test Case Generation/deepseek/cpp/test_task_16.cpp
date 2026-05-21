#include <gtest/gtest.h>
#include <string>
#include "count_distinct_characters.h"  // Assumes the function is declared here

class CountDistinctCharactersTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test empty string
TEST_F(CountDistinctCharactersTest, EmptyString) {
    EXPECT_EQ(count_distinct_characters(""), 0);
}

// Test single character
TEST_F(CountDistinctCharactersTest, SingleCharacter) {
    EXPECT_EQ(count_distinct_characters("a"), 1);
    EXPECT_EQ(count_distinct_characters("A"), 1);
    EXPECT_EQ(count_distinct_characters("z"), 1);
    EXPECT_EQ(count_distinct_characters("Z"), 1);
}

// Test identical characters (case insensitive)
TEST_F(CountDistinctCharactersTest, IdenticalCharactersCaseInsensitive) {
    EXPECT_EQ(count_distinct_characters("aaa"), 1);
    EXPECT_EQ(count_distinct_characters("AAA"), 1);
    EXPECT_EQ(count_distinct_characters("aAaAaA"), 1);
    EXPECT_EQ(count_distinct_characters("aA"), 1);
}

// Test mixed case with same characters
TEST_F(CountDistinctCharactersTest, MixedCaseSameCharacters) {
    EXPECT_EQ(count_distinct_characters("xXxXx"), 1);
    EXPECT_EQ(count_distinct_characters("JjJjJ"), 1);
}

// Test all distinct characters
TEST_F(CountDistinctCharactersTest, AllDistinctCharacters) {
    EXPECT_EQ(count_distinct_characters("abc"), 3);
    EXPECT_EQ(count_distinct_characters("abcdef"), 6);
    EXPECT_EQ(count_distinct_characters("ABCDEF"), 6);
}

// Test mixed case with distinct characters
TEST_F(CountDistinctCharactersTest, MixedCaseDistinctCharacters) {
    EXPECT_EQ(count_distinct_characters("aBcDeF"), 6);
    EXPECT_EQ(count_distinct_characters("xYz"), 3);
}

// Test provided examples
TEST_F(CountDistinctCharactersTest, ProvidedExamples) {
    EXPECT_EQ(count_distinct_characters("xyzXYZ"), 3);
    EXPECT_EQ(count_distinct_characters("Jerry"), 4);
}

// Test string with spaces
TEST_F(CountDistinctCharactersTest, StringWithSpaces) {
    EXPECT_EQ(count_distinct_characters("hello world"), 7);  // h,e,l,o, ,w,r,d
    EXPECT_EQ(count_distinct_characters("a b c"), 3);
}

// Test string with numbers and special characters
TEST_F(CountDistinctCharactersTest, AlphanumericAndSpecialChars) {
    EXPECT_EQ(count_distinct_characters("abc123!@#"), 9);
    EXPECT_EQ(count_distinct_characters("a1b2c3"), 6);
}

// Test string with repeated characters throughout
TEST_F(CountDistinctCharactersTest, RepeatedPattern) {
    EXPECT_EQ(count_distinct_characters("abababab"), 2);
    EXPECT_EQ(count_distinct_characters("ABCabcABCabc"), 3);
}

// Test longer string
TEST_F(CountDistinctCharactersTest, LongerString) {
    EXPECT_EQ(count_distinct_characters("The quick brown fox jumps over the lazy dog"), 26);  // All letters
}

// Test string with all same case
TEST_F(CountDistinctCharactersTest, AllSameCase) {
    EXPECT_EQ(count_distinct_characters("abcdefghijklmnopqrstuvwxyz"), 26);
    EXPECT_EQ(count_distinct_characters("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 26);
}

// Test string with single character repeated many times
TEST_F(CountDistinctCharactersTest, SingleCharRepeatedManyTimes) {
    EXPECT_EQ(count_distinct_characters(std::string(1000, 'a')), 1);
    EXPECT_EQ(count_distinct_characters(std::string(1000, 'A')), 1);
}

// Test empty string with whitespace
TEST_F(CountDistinctCharactersTest, WhitespaceOnly) {
    EXPECT_EQ(count_distinct_characters("   "), 1);
    EXPECT_EQ(count_distinct_characters("\t\n\r"), 3);
}