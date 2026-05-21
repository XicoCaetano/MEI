#include <gtest/gtest.h>
#include <string>
#include <limits>

using namespace std;

// Include the function definitions or the header file here
// For testing purposes, assuming the functions are defined above
// bool is_palindrome(string str)
// string make_palindrome(string str)

class PalindromeTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Tests for is_palindrome function
TEST_F(PalindromeTest, IsPalindrome_EmptyString_ReturnsTrue) {
    EXPECT_TRUE(is_palindrome(""));
}

TEST_F(PalindromeTest, IsPalindrome_SingleCharacter_ReturnsTrue) {
    EXPECT_TRUE(is_palindrome("a"));
    EXPECT_TRUE(is_palindrome("Z"));
    EXPECT_TRUE(is_palindrome("5"));
}

TEST_F(PalindromeTest, IsPalindrome_TwoIdenticalCharacters_ReturnsTrue) {
    EXPECT_TRUE(is_palindrome("aa"));
    EXPECT_TRUE(is_palindrome("BB"));
    EXPECT_TRUE(is_palindrome("11"));
}

TEST_F(PalindromeTest, IsPalindrome_TwoDifferentCharacters_ReturnsFalse) {
    EXPECT_FALSE(is_palindrome("ab"));
    EXPECT_FALSE(is_palindrome("aB"));
    EXPECT_FALSE(is_palindrome("12"));
}

TEST_F(PalindromeTest, IsPalindrome_OddLengthPalindrome_ReturnsTrue) {
    EXPECT_TRUE(is_palindrome("aba"));
    EXPECT_TRUE(is_palindrome("racecar"));
    EXPECT_TRUE(is_palindrome("12321"));
    EXPECT_TRUE(is_palindrome("aabaa"));
}

TEST_F(PalindromeTest, IsPalindrome_EvenLengthPalindrome_ReturnsTrue) {
    EXPECT_TRUE(is_palindrome("abba"));
    EXPECT_TRUE(is_palindrome("123321"));
    EXPECT_TRUE(is_palindrome("aabbaa"));
    EXPECT_TRUE(is_palindrome("racecar"));
}

TEST_F(PalindromeTest, IsPalindrome_NonPalindromeOddLength_ReturnsFalse) {
    EXPECT_FALSE(is_palindrome("abc"));
    EXPECT_FALSE(is_palindrome("hello"));
    EXPECT_FALSE(is_palindrome("12345"));
}

TEST_F(PalindromeTest, IsPalindrome_NonPalindromeEvenLength_ReturnsFalse) {
    EXPECT_FALSE(is_palindrome("abcd"));
    EXPECT_FALSE(is_palindrome("test"));
    EXPECT_FALSE(is_palindrome("1234"));
}

TEST_F(PalindromeTest, IsPalindrome_WithMixedCase_ReturnsFalse) {
    EXPECT_FALSE(is_palindrome("AbA"));
    EXPECT_FALSE(is_palindrome("Racecar"));
}

TEST_F(PalindromeTest, IsPalindrome_WithSpaces_WorksCorrectly) {
    EXPECT_FALSE(is_palindrome("a b a"));
    EXPECT_FALSE(is_palindrome("race car"));
}

// Tests for make_palindrome function
TEST_F(PalindromeTest, MakePalindrome_EmptyString_ReturnsEmptyString) {
    EXPECT_EQ(make_palindrome(""), "");
}

TEST_F(PalindromeTest, MakePalindrome_SingleCharacter_ReturnsSameString) {
    EXPECT_EQ(make_palindrome("a"), "a");
    EXPECT_EQ(make_palindrome("Z"), "Z");
    EXPECT_EQ(make_palindrome("5"), "5");
}

TEST_F(PalindromeTest, MakePalindrome_TwoIdenticalCharacters_ReturnsSameString) {
    EXPECT_EQ(make_palindrome("aa"), "aa");
    EXPECT_EQ(make_palindrome("BB"), "BB");
}

TEST_F(PalindromeTest, MakePalindrome_TwoDifferentCharacters_ReturnsPalindrome) {
    EXPECT_EQ(make_palindrome("ab"), "aba");
    EXPECT_EQ(make_palindrome("ba"), "bab");
    EXPECT_EQ(make_palindrome("12"), "121");
}

TEST_F(PalindromeTest, MakePalindrome_AlreadyPalindromeOddLength_ReturnsSameString) {
    EXPECT_EQ(make_palindrome("aba"), "aba");
    EXPECT_EQ(make_palindrome("racecar"), "racecar");
    EXPECT_EQ(make_palindrome("12321"), "12321");
}

TEST_F(PalindromeTest, MakePalindrome_AlreadyPalindromeEvenLength_ReturnsSameString) {
    EXPECT_EQ(make_palindrome("abba"), "abba");
    EXPECT_EQ(make_palindrome("123321"), "123321");
}

TEST_F(PalindromeTest, MakePalindrome_Cat_ReturnsCatac) {
    EXPECT_EQ(make_palindrome("cat"), "catac");
}

TEST_F(PalindromeTest, MakePalindrome_Cata_ReturnsCatac) {
    EXPECT_EQ(make_palindrome("cata"), "catac");
}

TEST_F(PalindromeTest, MakePalindrome_Abc_ReturnsAbcba) {
    EXPECT_EQ(make_palindrome("abc"), "abcba");
}

TEST_F(PalindromeTest, MakePalindrome_Abcd_ReturnsAbcdcba) {
    EXPECT_EQ(make_palindrome("abcd"), "abcdcba");
}

TEST_F(PalindromeTest, MakePalindrome_PalindromicPrefix_ReturnsCorrectPalindrome) {
    EXPECT_EQ(make_palindrome("aaaa"), "aaaa");
    EXPECT_EQ(make_palindrome("aaab"), "aaabaaa");
}

TEST_F(PalindromeTest, MakePalindrome_StringWithRepeatingPattern_WorksCorrectly) {
    EXPECT_EQ(make_palindrome("abcabc"), "abcabccba");
    EXPECT_EQ(make_palindrome("abca"), "abcba");
}

TEST_F(PalindromeTest, MakePalindrome_SuffixPalindromeLongerThanOne_WorksCorrectly) {
    EXPECT_EQ(make_palindrome("abcba"), "abcba");
    EXPECT_EQ(make_palindrome("abcbaX"), "abcbaXabcba");
    EXPECT_EQ(make_palindrome("aabcdcba"), "aabcdcbaa");
}

TEST_F(PalindromeTest, MakePalindrome_NoPalindromicSuffix_WorksCorrectly) {
    EXPECT_EQ(make_palindrome("abcdef"), "abcdefedcba");
    EXPECT_EQ(make_palindrome("xyz"), "xyzzyx");
}

TEST_F(PalindromeTest, MakePalindrome_LongString_HandlesEfficiently) {
    string longStr(1000, 'a');
    string expected = longStr;
    EXPECT_EQ(make_palindrome(longStr), expected);
    
    string longStr2 = string(500, 'a') + "b";
    string expected2 = longStr2 + string(500, 'a');
    EXPECT_EQ(make_palindrome(longStr2), expected2);
}

TEST_F(PalindromeTest, MakePalindrome_MixedCase_WorksCorrectly) {
    EXPECT_EQ(make_palindrome("AbC"), "AbCCbA");
    EXPECT_NE(make_palindrome("AbC"), "AbCbA");
}

TEST_F(PalindromeTest, MakePalindrome_NumericString_WorksCorrectly) {
    EXPECT_EQ(make_palindrome("123"), "12321");
    EXPECT_EQ(make_palindrome("1234"), "1234321");
    EXPECT_EQ(make_palindrome("1234321"), "1234321");
}

TEST_F(PalindromeTest, MakePalindrome_WithSpace_WorksCorrectly) {
    EXPECT_EQ(make_palindrome("ab "), "ab  ba");
    EXPECT_EQ(make_palindrome("a b"), "a b a");
}

TEST_F(PalindromeTest, MakePalindrome_SpecialCharacters_WorksCorrectly) {
    EXPECT_EQ(make_palindrome("!@#"), "!@##@!");
    EXPECT_EQ(make_palindrome("!@#!"), "!@#!!#@!");
}

TEST_F(PalindromeTest, MakePalindrome_StringWithPalindromicCore_ReturnsMinimalPalindrome) {
    EXPECT_EQ(make_palindrome("xabba"), "xabbax");
    EXPECT_EQ(make_palindrome("yracecar"), "yracecary");
}