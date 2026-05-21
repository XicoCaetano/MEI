#include <gtest/gtest.h>
#include <string>
using namespace std;

string string_sequence(int n){
    string out="0";
    for (int i=1;i<=n;i++)
    out=out+" "+to_string(i);
    return out;
}

TEST(StringSequenceTest, ZeroReturnsJustZero) {
    EXPECT_EQ(string_sequence(0), "0");
}

TEST(StringSequenceTest, OneReturnZeroAndOne) {
    EXPECT_EQ(string_sequence(1), "0 1");
}

TEST(StringSequenceTest, FiveReturnsFullSequence) {
    EXPECT_EQ(string_sequence(5), "0 1 2 3 4 5");
}

TEST(StringSequenceTest, TwoReturnsCorrectSequence) {
    EXPECT_EQ(string_sequence(2), "0 1 2");
}

TEST(StringSequenceTest, TenReturnsCorrectSequence) {
    EXPECT_EQ(string_sequence(10), "0 1 2 3 4 5 6 7 8 9 10");
}

TEST(StringSequenceTest, LargeNumberReturnsCorrectSequence) {
    string result = string_sequence(100);
    EXPECT_EQ(result.substr(0, 1), "0");
    EXPECT_NE(result.find("99"), string::npos);
    EXPECT_NE(result.find("100"), string::npos);
}

TEST(StringSequenceTest, ResultStartsWithZero) {
    EXPECT_EQ(string_sequence(5).substr(0, 1), "0");
}

TEST(StringSequenceTest, ResultEndsWithN) {
    string result = string_sequence(7);
    EXPECT_EQ(result.substr(result.size() - 1), "7");
}

TEST(StringSequenceTest, SpaceDelimitedFormat) {
    string result = string_sequence(3);
    EXPECT_EQ(result, "0 1 2 3");
    size_t pos = 0;
    int count = 0;
    while ((pos = result.find(' ', pos)) != string::npos) {
        count++;
        pos++;
    }
    EXPECT_EQ(count, 3);
}

TEST(StringSequenceTest, NoLeadingOrTrailingSpaces) {
    string result = string_sequence(4);
    EXPECT_NE(result.front(), ' ');
    EXPECT_NE(result.back(), ' ');
}

TEST(StringSequenceTest, SingleDigitBoundary) {
    EXPECT_EQ(string_sequence(9), "0 1 2 3 4 5 6 7 8 9");
}

TEST(StringSequenceTest, MultiDigitTransition) {
    string result = string_sequence(10);
    EXPECT_NE(result.find("9 10"), string::npos);
}

TEST(StringSequenceTest, CorrectNumberOfTokens) {
    int n = 6;
    string result = string_sequence(n);
    int tokenCount = 0;
    size_t pos = 0;
    size_t found;
    while ((found = result.find(' ', pos)) != string::npos) {
        tokenCount++;
        pos = found + 1;
    }
    tokenCount++;
    EXPECT_EQ(tokenCount, n + 1);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}