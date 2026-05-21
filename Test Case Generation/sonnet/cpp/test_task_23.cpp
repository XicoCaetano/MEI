#include <gtest/gtest.h>
#include <string>
using namespace std;

int strlen(string str);

TEST(StrlenTest, EmptyString) {
    EXPECT_EQ(strlen(""), 0);
}

TEST(StrlenTest, SingleCharacter) {
    EXPECT_EQ(strlen("a"), 1);
}

TEST(StrlenTest, MultipleCharacters) {
    EXPECT_EQ(strlen("abc"), 3);
}

TEST(StrlenTest, LongerString) {
    EXPECT_EQ(strlen("hello world"), 11);
}

TEST(StrlenTest, StringWithSpaces) {
    EXPECT_EQ(strlen("   "), 3);
}

TEST(StrlenTest, StringWithSpecialCharacters) {
    EXPECT_EQ(strlen("!@#$%"), 5);
}

TEST(StrlenTest, StringWithNumbers) {
    EXPECT_EQ(strlen("12345"), 5);
}

TEST(StrlenTest, StringWithNewline) {
    EXPECT_EQ(strlen("ab\ncd"), 5);
}

TEST(StrlenTest, StringWithTab) {
    EXPECT_EQ(strlen("ab\tcd"), 5);
}

TEST(StrlenTest, StringWithNullCharacterInMiddle) {
    string s("ab\0cd", 5);
    EXPECT_EQ(strlen(s), 5);
}

TEST(StrlenTest, StringWithUnicode) {
    EXPECT_EQ(strlen("abc123"), 6);
}

TEST(StrlenTest, StdStringObject) {
    std::string s = "hello";
    EXPECT_EQ(strlen(s), 5);
}

TEST(StrlenTest, LongString) {
    std::string s(1000, 'x');
    EXPECT_EQ(strlen(s), 1000);
}

TEST(StrlenTest, RepeatedCharacters) {
    EXPECT_EQ(strlen("aaaa"), 4);
}

TEST(StrlenTest, MixedContent) {
    EXPECT_EQ(strlen("aB3!z"), 5);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}