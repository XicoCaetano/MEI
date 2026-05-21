#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

vector<string> all_prefixes(string str){
    vector<string> out;
    string current="";
    for (int i=0;i<str.length();i++)
    {
        current=current+str[i];
        out.push_back(current);
    }
    return out;
}

TEST(AllPrefixesTest, EmptyString) {
    vector<string> result = all_prefixes("");
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0u);
}

TEST(AllPrefixesTest, SingleCharacter) {
    vector<string> result = all_prefixes("a");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], "a");
}

TEST(AllPrefixesTest, TwoCharacters) {
    vector<string> result = all_prefixes("ab");
    ASSERT_EQ(result.size(), 2u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "ab");
}

TEST(AllPrefixesTest, ThreeCharacters) {
    vector<string> result = all_prefixes("abc");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "ab");
    EXPECT_EQ(result[2], "abc");
}

TEST(AllPrefixesTest, SizeEqualsStringLength) {
    string input = "hello";
    vector<string> result = all_prefixes(input);
    EXPECT_EQ(result.size(), input.length());
}

TEST(AllPrefixesTest, PrefixesAreIncreasing) {
    vector<string> result = all_prefixes("hello");
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i].length(), i + 1);
    }
}

TEST(AllPrefixesTest, LastElementEqualsInput) {
    string input = "hello";
    vector<string> result = all_prefixes(input);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result.back(), input);
}

TEST(AllPrefixesTest, FirstElementIsSingleChar) {
    string input = "world";
    vector<string> result = all_prefixes(input);
    ASSERT_FALSE(result.empty());
    EXPECT_EQ(result[0], string(1, input[0]));
}

TEST(AllPrefixesTest, EachPrefixIsSubstringOfInput) {
    string input = "testing";
    vector<string> result = all_prefixes(input);
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], input.substr(0, i + 1));
    }
}

TEST(AllPrefixesTest, RepeatedCharacters) {
    vector<string> result = all_prefixes("aaa");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "aa");
    EXPECT_EQ(result[2], "aaa");
}

TEST(AllPrefixesTest, WithSpaces) {
    vector<string> result = all_prefixes("a b");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "a ");
    EXPECT_EQ(result[2], "a b");
}

TEST(AllPrefixesTest, WithSpecialCharacters) {
    vector<string> result = all_prefixes("!@#");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "!");
    EXPECT_EQ(result[1], "!@");
    EXPECT_EQ(result[2], "!@#");
}

TEST(AllPrefixesTest, WithDigits) {
    vector<string> result = all_prefixes("123");
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], "1");
    EXPECT_EQ(result[1], "12");
    EXPECT_EQ(result[2], "123");
}

TEST(AllPrefixesTest, LongerString) {
    string input = "abcdefghij";
    vector<string> result = all_prefixes(input);
    ASSERT_EQ(result.size(), 10u);
    for (size_t i = 0; i < result.size(); ++i) {
        EXPECT_EQ(result[i], input.substr(0, i + 1));
    }
}

TEST(AllPrefixesTest, ConsecutivePrefixsDifferByOneChar) {
    string input = "abcde";
    vector<string> result = all_prefixes(input);
    for (size_t i = 1; i < result.size(); ++i) {
        EXPECT_EQ(result[i].length(), result[i-1].length() + 1);
        EXPECT_EQ(result[i].substr(0, result[i-1].length()), result[i-1]);
    }
}

TEST(AllPrefixesTest, SingleSpace) {
    vector<string> result = all_prefixes(" ");
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], " ");
}

TEST(AllPrefixesTest, MixedAlphanumeric) {
    vector<string> result = all_prefixes("a1b2");
    ASSERT_EQ(result.size(), 4u);
    EXPECT_EQ(result[0], "a");
    EXPECT_EQ(result[1], "a1");
    EXPECT_EQ(result[2], "a1b");
    EXPECT_EQ(result[3], "a1b2");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}