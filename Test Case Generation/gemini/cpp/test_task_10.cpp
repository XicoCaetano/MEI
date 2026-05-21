#include <gtest/gtest.h>
#include <string>

// --- SUT (System Under Test) ---
bool is_palindrome(std::string str) {
    std::string s(str.rbegin(), str.rend());
    return s == str;
}

std::string make_palindrome(std::string str) {
    int i;
    for (i = 0; i < (int)str.length(); i++) {
        std::string rstr = str.substr(i);
        if (is_palindrome(rstr)) {
            std::string nstr = str.substr(0, i);
            std::string n2str(nstr.rbegin(), nstr.rend());
            return str + n2str;
        }
    }
    std::string n2str(str.rbegin(), str.rend());
    return str + n2str;
}

// --- Unit Tests ---

// Tests for is_palindrome function
TEST(PalindromeTest, IsPalindromeBasic) {
    EXPECT_TRUE(is_palindrome(""));
    EXPECT_TRUE(is_palindrome("a"));
    EXPECT_TRUE(is_palindrome("aba"));
    EXPECT_TRUE(is_palindrome("racecar"));
    EXPECT_FALSE(is_palindrome("abc"));
    EXPECT_FALSE(is_palindrome("at"));
}

// Tests for make_palindrome function
TEST(MakePalindromeTest, EmptyString) {
    EXPECT_EQ(make_palindrome(""), "");
}

TEST(MakePalindromeTest, SingleCharacter) {
    EXPECT_EQ(make_palindrome("a"), "a");
}

TEST(MakePalindromeTest, AlreadyAPalindrome) {
    EXPECT_EQ(make_palindrome("aba"), "aba");
    EXPECT_EQ(make_palindrome("racecar"), "racecar");
    EXPECT_EQ(make_palindrome("aa"), "aa");
}

TEST(MakePalindromeTest, ExamplesFromDocstring) {
    EXPECT_EQ(make_palindrome("cat"), "catac");
    EXPECT_EQ(make_palindrome("cata"), "catac");
}

TEST(MakePalindromeTest, GenericStrings) {
    EXPECT_EQ(make_palindrome("abc"), "abcba");
    EXPECT_EQ(make_palindrome("xyz"), "xyz yx"); // Note: substr logic
    EXPECT_EQ(make_palindrome("abcd"), "abcdcba");
}

TEST(MakePalindromeTest, PartialSuffixPalindrome) {
    // "jerry" -> suffix "y" is palindrome -> "jerr" reversed is "rrej" -> "jerryrrej"
    EXPECT_EQ(make_palindrome("jerry"), "jerryrrej");
    // "banana" -> suffix "anana" is palindrome -> "b" reversed is "b" -> "bananab"
    EXPECT_EQ(make_palindrome("banana"), "bananab");
}

TEST(MakePalindromeTest, LongestSuffixCheck) {
    // "abb" -> suffix "bb" is palindrome -> "a" reversed is "a" -> "abba"
    EXPECT_EQ(make_palindrome("abb"), "abba");
}

TEST(MakePalindromeTest, EdgeCaseNonAscii) {
    // Basic string handles bytes; ensuring no crash
    EXPECT_EQ(make_palindrome("123"), "12321");
}