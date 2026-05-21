#include <gtest/gtest.h>
#include <string>
using namespace std;

int count_distinct_characters(string str);

TEST(CountDistinctCharactersTest, EmptyString) {
    EXPECT_EQ(count_distinct_characters(""), 0);
}

TEST(CountDistinctCharactersTest, SingleCharacter) {
    EXPECT_EQ(count_distinct_characters("a"), 1);
    EXPECT_EQ(count_distinct_characters("Z"), 1);
}

TEST(CountDistinctCharactersTest, AllSameCharacterLowercase) {
    EXPECT_EQ(count_distinct_characters("aaaa"), 1);
}

TEST(CountDistinctCharactersTest, AllSameCharacterUppercase) {
    EXPECT_EQ(count_distinct_characters("BBBB"), 1);
}

TEST(CountDistinctCharactersTest, MixedCaseSameCharacter) {
    EXPECT_EQ(count_distinct_characters("aAaA"), 1);
    EXPECT_EQ(count_distinct_characters("zZzZ"), 1);
}

TEST(CountDistinctCharactersTest, CaseInsensitiveXyzExample) {
    EXPECT_EQ(count_distinct_characters("xyzXYZ"), 3);
}

TEST(CountDistinctCharactersTest, JerryExample) {
    EXPECT_EQ(count_distinct_characters("Jerry"), 4);
}

TEST(CountDistinctCharactersTest, AllLowercaseDistinct) {
    EXPECT_EQ(count_distinct_characters("abcd"), 4);
}

TEST(CountDistinctCharactersTest, AllUppercaseDistinct) {
    EXPECT_EQ(count_distinct_characters("ABCD"), 4);
}

TEST(CountDistinctCharactersTest, MixedCaseDistinct) {
    EXPECT_EQ(count_distinct_characters("AbCd"), 4);
}

TEST(CountDistinctCharactersTest, RepeatedCharactersDifferentCase) {
    EXPECT_EQ(count_distinct_characters("AaBbCc"), 3);
}

TEST(CountDistinctCharactersTest, SingleRepeatedWithOthers) {
    EXPECT_EQ(count_distinct_characters("aAbB"), 2);
}

TEST(CountDistinctCharactersTest, WithSpaces) {
    EXPECT_EQ(count_distinct_characters("a b"), 3);
}

TEST(CountDistinctCharactersTest, WithDigits) {
    EXPECT_EQ(count_distinct_characters("a1b2"), 4);
}

TEST(CountDistinctCharactersTest, WithDigitsRepeated) {
    EXPECT_EQ(count_distinct_characters("1122"), 2);
}

TEST(CountDistinctCharactersTest, WithSpecialCharacters) {
    EXPECT_EQ(count_distinct_characters("!@#"), 3);
}

TEST(CountDistinctCharactersTest, WithSpecialCharactersRepeated) {
    EXPECT_EQ(count_distinct_characters("!!@@"), 2);
}

TEST(CountDistinctCharactersTest, MixedAlphanumericAndSpecial) {
    EXPECT_EQ(count_distinct_characters("a1!a1!"), 3);
}

TEST(CountDistinctCharactersTest, LongerMixedString) {
    EXPECT_EQ(count_distinct_characters("Hello World"), 8);
}

TEST(CountDistinctCharactersTest, AllAlphabetLowercase) {
    EXPECT_EQ(count_distinct_characters("abcdefghijklmnopqrstuvwxyz"), 26);
}

TEST(CountDistinctCharactersTest, AllAlphabetUppercase) {
    EXPECT_EQ(count_distinct_characters("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), 26);
}

TEST(CountDistinctCharactersTest, AllAlphabetMixedCase) {
    EXPECT_EQ(count_distinct_characters("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"), 26);
}

TEST(CountDistinctCharactersTest, StringWithOnlySpaces) {
    EXPECT_EQ(count_distinct_characters("   "), 1);
}

TEST(CountDistinctCharactersTest, TwoDistinctCharsAlternating) {
    EXPECT_EQ(count_distinct_characters("ababababab"), 2);
}

TEST(CountDistinctCharactersTest, TwoDistinctCharsMixedCase) {
    EXPECT_EQ(count_distinct_characters("aAbB"), 2);
}

TEST(CountDistinctCharactersTest, NumericOnlyString) {
    EXPECT_EQ(count_distinct_characters("1234567890"), 10);
}

TEST(CountDistinctCharactersTest, NumericStringWithRepeats) {
    EXPECT_EQ(count_distinct_characters("112233"), 3);
}

TEST(CountDistinctCharactersTest, SingleUppercaseChar) {
    EXPECT_EQ(count_distinct_characters("A"), 1);
}

TEST(CountDistinctCharactersTest, TwoSameCharsLower) {
    EXPECT_EQ(count_distinct_characters("aa"), 1);
}

TEST(CountDistinctCharactersTest, TwoDifferentCharsLower) {
    EXPECT_EQ(count_distinct_characters("ab"), 2);
}

TEST(CountDistinctCharactersTest, CaseInsensitivityEdge) {
    EXPECT_EQ(count_distinct_characters("Aa"), 1);
    EXPECT_EQ(count_distinct_characters("Zz"), 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}