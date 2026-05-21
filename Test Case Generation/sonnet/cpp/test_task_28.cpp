#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

string concatenate(vector<string> strings){
    string out="";
    for (int i=0;i<strings.size();i++)
        out=out+strings[i];
    return out;
}

TEST(ConcatenateTest, EmptyVector) {
    EXPECT_EQ(concatenate({}), "");
}

TEST(ConcatenateTest, SingleElement) {
    EXPECT_EQ(concatenate({"a"}), "a");
}

TEST(ConcatenateTest, MultipleElements) {
    EXPECT_EQ(concatenate({"a", "b", "c"}), "abc");
}

TEST(ConcatenateTest, SingleEmptyString) {
    EXPECT_EQ(concatenate({""}), "");
}

TEST(ConcatenateTest, MultipleEmptyStrings) {
    EXPECT_EQ(concatenate({"", "", ""}), "");
}

TEST(ConcatenateTest, MixedEmptyAndNonEmpty) {
    EXPECT_EQ(concatenate({"", "b", ""}), "b");
}

TEST(ConcatenateTest, LongerStrings) {
    EXPECT_EQ(concatenate({"hello", " ", "world"}), "hello world");
}

TEST(ConcatenateTest, SingleLongString) {
    EXPECT_EQ(concatenate({"abcdefghij"}), "abcdefghij");
}

TEST(ConcatenateTest, NumbersAsStrings) {
    EXPECT_EQ(concatenate({"1", "2", "3"}), "123");
}

TEST(ConcatenateTest, SpecialCharacters) {
    EXPECT_EQ(concatenate({"!", "@", "#"}), "!@#");
}

TEST(ConcatenateTest, WhitespaceStrings) {
    EXPECT_EQ(concatenate({" ", "\t", "\n"}), " \t\n");
}

TEST(ConcatenateTest, TwoElements) {
    EXPECT_EQ(concatenate({"foo", "bar"}), "foobar");
}

TEST(ConcatenateTest, MixedLengths) {
    EXPECT_EQ(concatenate({"a", "bb", "ccc", "dddd"}), "abbcccdddd");
}

TEST(ConcatenateTest, UnicodeCharacters) {
    EXPECT_EQ(concatenate({"こんにちは", " ", "世界"}), "こんにちは 世界");
}

TEST(ConcatenateTest, RepeatedElements) {
    EXPECT_EQ(concatenate({"ab", "ab", "ab"}), "ababab");
}

TEST(ConcatenateTest, LargeNumberOfElements) {
    vector<string> input(1000, "a");
    string expected(1000, 'a');
    EXPECT_EQ(concatenate(input), expected);
}

TEST(ConcatenateTest, MixedEmptyAndLongStrings) {
    EXPECT_EQ(concatenate({"", "hello", "", "world", ""}), "helloworld");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}