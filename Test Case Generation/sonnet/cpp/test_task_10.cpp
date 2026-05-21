#include <gtest/gtest.h>
#include <string>
using namespace std;

bool is_palindrome(string str);
string make_palindrome(string str);

// ─── is_palindrome ───────────────────────────────────────────────────────────

TEST(IsPalindromeTest, EmptyString) {
    EXPECT_TRUE(is_palindrome(""));
}

TEST(IsPalindromeTest, SingleCharacter) {
    EXPECT_TRUE(is_palindrome("a"));
    EXPECT_TRUE(is_palindrome("z"));
}

TEST(IsPalindromeTest, TwoCharsSame) {
    EXPECT_TRUE(is_palindrome("aa"));
}

TEST(IsPalindromeTest, TwoCharsDifferent) {
    EXPECT_FALSE(is_palindrome("ab"));
}

TEST(IsPalindromeTest, OddLengthPalindrome) {
    EXPECT_TRUE(is_palindrome("aba"));
    EXPECT_TRUE(is_palindrome("racecar"));
    EXPECT_TRUE(is_palindrome("madam"));
}

TEST(IsPalindromeTest, EvenLengthPalindrome) {
    EXPECT_TRUE(is_palindrome("abba"));
    EXPECT_TRUE(is_palindrome("aabbaa"));
}

TEST(IsPalindromeTest, NotPalindrome) {
    EXPECT_FALSE(is_palindrome("cat"));
    EXPECT_FALSE(is_palindrome("hello"));
    EXPECT_FALSE(is_palindrome("abc"));
}

TEST(IsPalindromeTest, AllSameCharacters) {
    EXPECT_TRUE(is_palindrome("aaaa"));
    EXPECT_TRUE(is_palindrome("bbbbb"));
}

TEST(IsPalindromeTest, CaseSensitive) {
    EXPECT_FALSE(is_palindrome("Aba"));
    EXPECT_FALSE(is_palindrome("Racecar"));
}

TEST(IsPalindromeTest, WithSpaces) {
    EXPECT_TRUE(is_palindrome("a b a"));
    EXPECT_FALSE(is_palindrome("race car"));
}

TEST(IsPalindromeTest, WithNumbers) {
    EXPECT_TRUE(is_palindrome("12321"));
    EXPECT_FALSE(is_palindrome("12345"));
}

TEST(IsPalindromeTest, WithSpecialCharacters) {
    EXPECT_TRUE(is_palindrome("!@!"));
    EXPECT_FALSE(is_palindrome("!@#"));
}

// ─── make_palindrome ─────────────────────────────────────────────────────────

TEST(MakePalindromeTest, EmptyString) {
    EXPECT_EQ(make_palindrome(""), "");
}

TEST(MakePalindromeTest, SingleCharacter) {
    EXPECT_EQ(make_palindrome("a"), "a");
    EXPECT_EQ(make_palindrome("z"), "z");
}

TEST(MakePalindromeTest, AlreadyPalindrome_Odd) {
    EXPECT_EQ(make_palindrome("aba"), "aba");
    EXPECT_EQ(make_palindrome("racecar"), "racecar");
    EXPECT_EQ(make_palindrome("madam"), "madam");
}

TEST(MakePalindromeTest, AlreadyPalindrome_Even) {
    EXPECT_EQ(make_palindrome("abba"), "abba");
    EXPECT_EQ(make_palindrome("aa"), "aa");
}

TEST(MakePalindromeTest, SingleCharRepeated) {
    EXPECT_EQ(make_palindrome("aaa"), "aaa");
    EXPECT_EQ(make_palindrome("aaaa"), "aaaa");
}

TEST(MakePalindromeTest, CatExample) {
    // "cat" -> postfix "t" is palindrome -> prefix "ca" reversed = "ac" -> "catac"
    EXPECT_EQ(make_palindrome("cat"), "catac");
}

TEST(MakePalindromeTest, CataExample) {
    // "cata" -> postfix "ata" is palindrome -> prefix "c" reversed = "c" -> "catac"
    EXPECT_EQ(make_palindrome("cata"), "catac");
}

TEST(MakePalindromeTest, ResultIsPalindrome_Cat) {
    string result = make_palindrome("cat");
    EXPECT_TRUE(is_palindrome(result));
}

TEST(MakePalindromeTest, ResultIsPalindrome_Cata) {
    string result = make_palindrome("cata");
    EXPECT_TRUE(is_palindrome(result));
}

TEST(MakePalindromeTest, ResultIsPalindrome_Hello) {
    string result = make_palindrome("hello");
    EXPECT_TRUE(is_palindrome(result));
}

TEST(MakePalindromeTest, ResultIsPalindrome_Abcd) {
    string result = make_palindrome("abcd");
    EXPECT_TRUE(is_palindrome(result));
}

TEST(MakePalindromeTest, StartsWithInput) {
    string input = "cat";
    string result = make_palindrome(input);
    EXPECT_EQ(result.substr(0, input.size()), input);
}

TEST(MakePalindromeTest, TwoChars_Same) {
    // "aa" is already palindrome
    EXPECT_EQ(make_palindrome("aa"), "aa");
}

TEST(MakePalindromeTest, TwoChars_Different) {
    // "ab" -> postfix "b" palindrome -> prefix "a" reversed = "a" -> "aba"
    EXPECT_EQ(make_palindrome("ab"), "aba");
    EXPECT_TRUE(is_palindrome(make_palindrome("ab")));
}

TEST(MakePalindromeTest, StringWithPalindromeSuffix) {
    // "xyzyx" is palindrome already
    EXPECT_EQ(make_palindrome("xyzyx"), "xyzyx");
}

TEST(MakePalindromeTest, StringWithPalindromeSuffix_Partial) {
    // "aab" -> postfix "b" palindrome -> prefix "aa" reversed = "aa" -> "aabaa"
    EXPECT_EQ(make_palindrome("aab"), "aabaa");
    EXPECT_TRUE(is_palindrome(make_palindrome("aab")));
}

TEST(MakePalindromeTest, ResultStartsWithOriginalString) {
    vector<string> inputs = {"hello", "world", "test", "abcde", "xyz"};
    for (const auto& input : inputs) {
        string result = make_palindrome(input);
        EXPECT_EQ(result.substr(0, input.size()), input)
            << "Failed for input: " << input;
    }
}

TEST(MakePalindromeTest, ResultIsPalindromeForVariousInputs) {
    vector<string> inputs = {"a", "ab", "abc", "abcd", "abcde",
                             "hello", "world", "cat", "cata", "racecar"};
    for (const auto& input : inputs) {
        string result = make_palindrome(input);
        EXPECT_TRUE(is_palindrome(result))
            << "Result '" << result << "' is not palindrome for input: " << input;
    }
}

TEST(MakePalindromeTest, WithNumbers) {
    string result = make_palindrome("123");
    EXPECT_TRUE(is_palindrome(result));
    EXPECT_EQ(result.substr(0, 3), "123");
}

TEST(MakePalindromeTest, WithSpecialCharacters) {
    string result = make_palindrome("a!b");
    EXPECT_TRUE(is_palindrome(result));
}

TEST(MakePalindromeTest, PrefixPalindromeNotSuffix) {
    // "abacaba" is already a palindrome
    EXPECT_EQ(make_palindrome("abacaba"), "abacaba");
    EXPECT_TRUE(is_palindrome(make_palindrome("abacaba")));
}

TEST(MakePalindromeTest, LongerStringNoPalindromeSuffix) {
    // "abcde": postfix "e" is palindrome -> "abcd" reversed = "dcba" -> "abcdedcba"
    string result = make_palindrome("abcde");
    EXPECT_TRUE(is_palindrome(result));
    EXPECT_EQ(result.substr(0, 5), "abcde");
}

TEST(MakePalindromeTest, ShortestPalindromeProperty) {
    // make_palindrome("cat") must be "catac" not "catac..." longer
    EXPECT_EQ(make_palindrome("cat").size(), 5u);
    // make_palindrome("cata") must be "catac"
    EXPECT_EQ(make_palindrome("cata").size(), 5u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}