#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

string longest(vector<string> strings){
    string out;
    for (int i=0;i<strings.size();i++)
    {
        if (strings[i].length()>out.length()) out=strings[i];
    }
    return out;
}

TEST(LongestTest, EmptyVector) {
    EXPECT_EQ(longest({}), "");
}

TEST(LongestTest, SingleElement) {
    EXPECT_EQ(longest({"a"}), "a");
}

TEST(LongestTest, SingleElementLongString) {
    EXPECT_EQ(longest({"hello"}), "hello");
}

TEST(LongestTest, AllSameLength_ReturnsFirst) {
    EXPECT_EQ(longest({"a", "b", "c"}), "a");
}

TEST(LongestTest, AllSameLength_TwoElements_ReturnsFirst) {
    EXPECT_EQ(longest({"bb", "cc"}), "bb");
}

TEST(LongestTest, IncreasingLength_ReturnsLast) {
    EXPECT_EQ(longest({"a", "bb", "ccc"}), "ccc");
}

TEST(LongestTest, DecreasingLength_ReturnsFirst) {
    EXPECT_EQ(longest({"ccc", "bb", "a"}), "ccc");
}

TEST(LongestTest, LongestInMiddle) {
    EXPECT_EQ(longest({"ab", "abcd", "xy"}), "abcd");
}

TEST(LongestTest, TwoStrings_FirstLonger) {
    EXPECT_EQ(longest({"hello", "hi"}), "hello");
}

TEST(LongestTest, TwoStrings_SecondLonger) {
    EXPECT_EQ(longest({"hi", "hello"}), "hello");
}

TEST(LongestTest, TwoStrings_SameLength_ReturnsFirst) {
    EXPECT_EQ(longest({"abc", "xyz"}), "abc");
}

TEST(LongestTest, EmptyStringInVector) {
    EXPECT_EQ(longest({"", "a"}), "a");
}

TEST(LongestTest, AllEmptyStrings) {
    EXPECT_EQ(longest({"", "", ""}), "");
}

TEST(LongestTest, EmptyStringAndNonEmpty_ReturnsNonEmpty) {
    EXPECT_EQ(longest({"", "hello", ""}), "hello");
}

TEST(LongestTest, LongStrings) {
    EXPECT_EQ(longest({"abcdefghij", "abcdefghijk", "abcdefghi"}), "abcdefghijk");
}

TEST(LongestTest, StringsWithSpaces) {
    EXPECT_EQ(longest({"hello world", "hi", "hey"}), "hello world");
}

TEST(LongestTest, StringsWithSpecialCharacters) {
    EXPECT_EQ(longest({"!@#", "!@#$%"}), "!@#$%");
}

TEST(LongestTest, NumericStrings) {
    EXPECT_EQ(longest({"123", "12345", "1"}), "12345");
}

TEST(LongestTest, TiedLength_MultipleElements_ReturnsFirst) {
    EXPECT_EQ(longest({"aa", "bb", "cc", "dd"}), "aa");
}

TEST(LongestTest, LongestIsLastOfTied) {
    EXPECT_EQ(longest({"a", "b", "cc", "dd"}), "cc");
}

TEST(LongestTest, MixedEmptyAndNonEmpty) {
    EXPECT_EQ(longest({"", "x", "", "yy", ""}), "yy");
}

TEST(LongestTest, SingleCharacterStrings_MultipleElements) {
    EXPECT_EQ(longest({"z", "a", "m"}), "z");
}

TEST(LongestTest, LargeVector) {
    vector<string> v(1000, "short");
    v.push_back("this_is_the_longest_string");
    EXPECT_EQ(longest(v), "this_is_the_longest_string");
}

TEST(LongestTest, LongestAtBeginningOfLargeVector) {
    vector<string> v(1000, "short");
    v.insert(v.begin(), "this_is_the_longest_string");
    EXPECT_EQ(longest(v), "this_is_the_longest_string");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}