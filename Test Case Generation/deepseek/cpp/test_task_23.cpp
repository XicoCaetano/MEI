#include <gtest/gtest.h>
#include <string>
using namespace std;

extern int strlen(string str);

class StrlenTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(StrlenTest, EmptyString) {
    EXPECT_EQ(strlen(""), 0);
}

TEST_F(StrlenTest, SingleCharacter) {
    EXPECT_EQ(strlen("a"), 1);
    EXPECT_EQ(strlen("Z"), 1);
    EXPECT_EQ(strlen("1"), 1);
    EXPECT_EQ(strlen(" "), 1);
    EXPECT_EQ(strlen("\n"), 1);
    EXPECT_EQ(strlen("\t"), 1);
}

TEST_F(StrlenTest, MultipleCharacters) {
    EXPECT_EQ(strlen("abc"), 3);
    EXPECT_EQ(strlen("Hello World"), 11);
    EXPECT_EQ(strlen("12345"), 5);
    EXPECT_EQ(strlen("!@#$%"), 5);
}

TEST_F(StrlenTest, StringWithSpaces) {
    EXPECT_EQ(strlen("   "), 3);
    EXPECT_EQ(strlen("a b c"), 5);
    EXPECT_EQ(strlen(" leading"), 8);
    EXPECT_EQ(strlen("trailing "), 9);
    EXPECT_EQ(strlen(" multiple  spaces "), 18);
}

TEST_F(StrlenTest, StringWithSpecialCharacters) {
    EXPECT_EQ(strlen("\n\r\t"), 3);
    EXPECT_EQ(strlen("\\\"\'"), 3);
    EXPECT_EQ(strlen("\x00\x01\x02"), 3);
}

TEST_F(StrlenTest, LongString) {
    string longStr(10000, 'a');
    EXPECT_EQ(strlen(longStr), 10000);
    
    string veryLongStr(1000000, 'b');
    EXPECT_EQ(strlen(veryLongStr), 1000000);
}

TEST_F(StrlenTest, StringWithNullCharacters) {
    string strWithNull = "abc";
    strWithNull[1] = '\0';
    EXPECT_EQ(strlen(strWithNull), 3);
}

TEST_F(StrlenTest, UnicodeCharacters) {
    string utf8String = u8"こんにちは";
    EXPECT_EQ(strlen(utf8String), 15);
    
    string emojiString = u8"😀😁😂";
    EXPECT_EQ(strlen(emojiString), 12);
}

TEST_F(StrlenTest, NumericStrings) {
    EXPECT_EQ(strlen("0"), 1);
    EXPECT_EQ(strlen("1234567890"), 10);
    EXPECT_EQ(strlen("-9876543210"), 11);
    EXPECT_EQ(strlen("3.14159"), 7);
}

TEST_F(StrlenTest, AlphanumericStrings) {
    EXPECT_EQ(strlen("abc123"), 6);
    EXPECT_EQ(strlen("ABC456DEF"), 9);
    EXPECT_EQ(strlen("a1b2c3d4e5"), 10);
}

TEST_F(StrlenTest, MixedCaseStrings) {
    EXPECT_EQ(strlen("AbCdEfG"), 7);
    EXPECT_EQ(strlen("UPPERlower"), 10);
    EXPECT_EQ(strlen("MiXeDcAsE"), 10);
}