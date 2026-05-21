#include <gtest/gtest.h>
#include <string>
using namespace std;

int how_many_times(string str, string substring);

TEST(HowManyTimesTest, EmptyString) {
    EXPECT_EQ(how_many_times("", "a"), 0);
}

TEST(HowManyTimesTest, SingleCharMatch) {
    EXPECT_EQ(how_many_times("aaa", "a"), 3);
}

TEST(HowManyTimesTest, OverlappingMatch) {
    EXPECT_EQ(how_many_times("aaaa", "aa"), 3);
}

TEST(HowManyTimesTest, NoMatch) {
    EXPECT_EQ(how_many_times("hello", "z"), 0);
}

TEST(HowManyTimesTest, ExactMatch) {
    EXPECT_EQ(how_many_times("abc", "abc"), 1);
}

TEST(HowManyTimesTest, SubstringLongerThanString) {
    EXPECT_EQ(how_many_times("ab", "abc"), 0);
}

TEST(HowManyTimesTest, SubstringEqualLengthNoMatch) {
    EXPECT_EQ(how_many_times("abc", "xyz"), 0);
}

TEST(HowManyTimesTest, MultipleNonOverlapping) {
    EXPECT_EQ(how_many_times("abab", "ab"), 2);
}

TEST(HowManyTimesTest, OverlappingThreeChars) {
    EXPECT_EQ(how_many_times("aaa", "aa"), 2);
}

TEST(HowManyTimesTest, SingleCharString) {
    EXPECT_EQ(how_many_times("a", "a"), 1);
}

TEST(HowManyTimesTest, SingleCharStringNoMatch) {
    EXPECT_EQ(how_many_times("a", "b"), 0);
}

TEST(HowManyTimesTest, SubstringAtStart) {
    EXPECT_EQ(how_many_times("abcdef", "abc"), 1);
}

TEST(HowManyTimesTest, SubstringAtEnd) {
    EXPECT_EQ(how_many_times("abcdef", "def"), 1);
}

TEST(HowManyTimesTest, SubstringInMiddle) {
    EXPECT_EQ(how_many_times("abcdef", "cde"), 1);
}

TEST(HowManyTimesTest, RepeatedPattern) {
    EXPECT_EQ(how_many_times("ababab", "ab"), 3);
}

TEST(HowManyTimesTest, OverlappingComplex) {
    EXPECT_EQ(how_many_times("aaaaa", "aaa"), 3);
}

TEST(HowManyTimesTest, WhitespaceSubstring) {
    EXPECT_EQ(how_many_times("a b c", " "), 2);
}

TEST(HowManyTimesTest, StringWithSpaces) {
    EXPECT_EQ(how_many_times("hello world hello", "hello"), 2);
}

TEST(HowManyTimesTest, NumericCharacters) {
    EXPECT_EQ(how_many_times("12312312", "123"), 2);
}

TEST(HowManyTimesTest, OverlappingNumeric) {
    EXPECT_EQ(how_many_times("1111", "11"), 3);
}

TEST(HowManyTimesTest, SubstringSameLengthMatch) {
    EXPECT_EQ(how_many_times("xyz", "xyz"), 1);
}

TEST(HowManyTimesTest, AllSameCharsLongOverlap) {
    EXPECT_EQ(how_many_times("aaaaaa", "aa"), 5);
}

TEST(HowManyTimesTest, SubstringNotPresentInLongString) {
    EXPECT_EQ(how_many_times("abcdefghij", "xy"), 0);
}

TEST(HowManyTimesTest, SingleCharRepeatedSubstring) {
    EXPECT_EQ(how_many_times("bbbbb", "b"), 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}