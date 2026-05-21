#include <gtest/gtest.h>
#include <string>
#include "how_many_times.h"  // Assuming the function is declared here

// Test fixture for how_many_times function
class HowManyTimesTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Setup code if needed
    }
    
    void TearDown() override {
        // Cleanup code if needed
    }
};

// Test case 1: Empty string with non-empty substring
TEST_F(HowManyTimesTest, EmptyStringShouldReturnZero) {
    EXPECT_EQ(how_many_times("", "a"), 0);
    EXPECT_EQ(how_many_times("", "abc"), 0);
    EXPECT_EQ(how_many_times("", ""), 0);
}

// Test case 2: Empty substring (edge case - substring length 0)
TEST_F(HowManyTimesTest, EmptySubstringShouldNavigateLoopCorrectly) {
    EXPECT_EQ(how_many_times("", ""), 0);
    EXPECT_EQ(how_many_times("a", ""), 0);  // Loop condition: i <= 1-0 = 1
    EXPECT_EQ(how_many_times("abc", ""), 0);  // Loop condition: i <= 3-0 = 3
}

// Test case 3: Single character substring in single character string
TEST_F(HowManyTimesTest, SingleCharInSingleCharString) {
    EXPECT_EQ(how_many_times("a", "a"), 1);
    EXPECT_EQ(how_many_times("b", "a"), 0);
}

// Test case 4: Overlapping occurrences - single character
TEST_F(HowManyTimesTest, OverlappingCasesWithSingleChar) {
    EXPECT_EQ(how_many_times("aaa", "a"), 3);
    EXPECT_EQ(how_many_times("aaaaa", "a"), 5);
    EXPECT_EQ(how_many_times("ababa", "a"), 3);
}

// Test case 5: Overlapping occurrences - multiple characters
TEST_F(HowManyTimesTest, OverlappingCasesWithMultipleChars) {
    EXPECT_EQ(how_many_times("aaaa", "aa"), 3);
    EXPECT_EQ(how_many_times("aaaaa", "aa"), 4);
    EXPECT_EQ(how_many_times("abababa", "aba"), 3);
    EXPECT_EQ(how_many_times("ababab", "bab"), 2);
}

// Test case 6: Non-overlapping occurrences
TEST_F(HowManyTimesTest, NonOverlappingOccurrences) {
    EXPECT_EQ(how_many_times("abcabcabc", "abc"), 3);
    EXPECT_EQ(how_many_times("ababab", "ab"), 3);
    EXPECT_EQ(how_many_times("test test test", "test"), 3);
}

// Test case 7: Substring longer than string
TEST_F(HowManyTimesTest, SubstringLongerThanString) {
    EXPECT_EQ(how_many_times("abc", "abcd"), 0);
    EXPECT_EQ(how_many_times("a", "ab"), 0);
    EXPECT_EQ(how_many_times("", "abc"), 0);
}

// Test case 8: Substring equal to string
TEST_F(HowManyTimesTest, SubstringEqualToFullString) {
    EXPECT_EQ(how_many_times("abc", "abc"), 1);
    EXPECT_EQ(how_many_times("a", "a"), 1);
    EXPECT_EQ(how_many_times("", ""), 0);
}

// Test case 9: Mixed case sensitivity
TEST_F(HowManyTimesTest, CaseSensitiveSearch) {
    EXPECT_EQ(how_many_times("AbAbA", "A"), 2);
    EXPECT_EQ(how_many_times("TestTest", "test"), 0);
    EXPECT_EQ(how_many_times("HelloHELLO", "HELLO"), 1);
}

// Test case 10: Special characters and whitespace
TEST_F(HowManyTimesTest, SpecialCharactersAndWhitespace) {
    EXPECT_EQ(how_many_times("!@#$%!@#$%", "!@#$%"), 2);
    EXPECT_EQ(how_many_times("hello world hello", " "), 2);
    EXPECT_EQ(how_many_times("\t\n\t\n", "\n"), 2);
    EXPECT_EQ(how_many_times("\\\\\\", "\\\\"), 2);  // Escaped backslashes
}

// Test case 11: Long strings (performance edge case)
TEST_F(HowManyTimesTest, LongStrings) {
    std::string long_str(1000, 'a');
    EXPECT_EQ(how_many_times(long_str, "a"), 1000);
    
    std::string pattern_10 = "aaaaaaaaaa";
    EXPECT_EQ(how_many_times(long_str, pattern_10), 991);  // 1000 - 10 + 1
}

// Test case 12: Single character string with substring length 1
TEST_F(HowManyTimesTest, SingleCharStringBoundsTest) {
    EXPECT_EQ(how_many_times("x", "x"), 1);
    EXPECT_EQ(how_many_times("x", "y"), 0);
}

// Test case 13: Loop boundary testing
TEST_F(HowManyTimesTest, LoopBoundaryTesting) {
    // Testing the condition i <= str.length() - substring.length()
    EXPECT_EQ(how_many_times("ab", "ab"), 1);  // i <= 2-2 = 0, one iteration
    EXPECT_EQ(how_many_times("abc", "ab"), 1);  // i <= 3-2 = 1, two iterations
    EXPECT_EQ(how_many_times("abc", "c"), 1);  // i <= 3-1 = 2, three iterations
}

// Test case 14: Unicode/wide characters (if supported by std::string)
TEST_F(HowManyTimesTest, UTF8Characters) {
    EXPECT_EQ(how_many_times("café café", "café"), 2);
    EXPECT_EQ(how_many_times("🌟🌟🌟", "🌟"), 3);
}

// Test case 15: Zero-length substring with non-zero length string
TEST_F(HowManyTimesTest, ZeroLengthSubstringEdgeCase) {
    EXPECT_EQ(how_many_times("hello", ""), 0);
    EXPECT_EQ(how_many_times("world", ""), 0);
}

// Test case 16: Both string and substring empty
TEST_F(HowManyTimesTest, BothStringAndSubstringEmpty) {
    EXPECT_EQ(how_many_times("", ""), 0);
}

// Test case 17: Substring exactly at string boundaries
TEST_F(HowManyTimesTest, SubstringAtBoundaries) {
    EXPECT_EQ(how_many_times("abcde", "ab"), 1);  // At start
    EXPECT_EQ(how_many_times("abcde", "de"), 1);  // At end
    EXPECT_EQ(how_many_times("abcde", "abcde"), 1);  // Exact match
}

// Test case 18: Multiple overlapping patterns with different lengths
TEST_F(HowManyTimesTest, MultipleOverlappingPatterns) {
    EXPECT_EQ(how_many_times("banana", "ana"), 2);  // "banana" has "ana" at positions 1 and 3
    EXPECT_EQ(how_many_times("aaaaaa", "aaa"), 4);  // 6-3+1 = 4 overlapping
}

// Test case 19: Pattern of all different characters
TEST_F(HowManyTimesTest, NoMatchingPattern) {
    EXPECT_EQ(how_many_times("abcdefg", "xyz"), 0);
    EXPECT_EQ(how_many_times("123456789", "0"), 0);
    EXPECT_EQ(how_many_times("abc123def", "456"), 0);
}

// Test case 20: Stress test with short string
TEST_F(HowManyTimesTest, ShortStringStress) {
    // Test all possible substrings of a short string
    std::string test_str = "abc";
    EXPECT_EQ(how_many_times(test_str, "a"), 1);
    EXPECT_EQ(how_many_times(test_str, "b"), 1);
    EXPECT_EQ(how_many_times(test_str, "c"), 1);
    EXPECT_EQ(how_many_times(test_str, "ab"), 1);
    EXPECT_EQ(how_many_times(test_str, "bc"), 1);
    EXPECT_EQ(how_many_times(test_str, "abc"), 1);
    EXPECT_EQ(how_many_times(test_str, "abcd"), 0);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}