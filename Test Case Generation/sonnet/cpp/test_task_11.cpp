#include <gtest/gtest.h>
#include <string>
using namespace std;

string string_xor(string a, string b) {
    string output = "";
    for (int i = 0; (i < a.length() and i < b.length()); i++) {
        if (i < a.length() and i < b.length()) {
            if (a[i] == b[i]) {
                output += '0';
            } else output += '1';
        } else {
            if (i >= a.length()) {
                output += b[i];
            } else output += a[i];
        }
    }
    return output;
}

TEST(StringXorTest, BasicExample) {
    EXPECT_EQ(string_xor("010", "110"), "100");
}

TEST(StringXorTest, AllZeros) {
    EXPECT_EQ(string_xor("000", "000"), "000");
}

TEST(StringXorTest, AllOnes) {
    EXPECT_EQ(string_xor("111", "111"), "000");
}

TEST(StringXorTest, AllDifferent) {
    EXPECT_EQ(string_xor("000", "111"), "111");
}

TEST(StringXorTest, AllDifferentReversed) {
    EXPECT_EQ(string_xor("111", "000"), "111");
}

TEST(StringXorTest, SingleBitZeroZero) {
    EXPECT_EQ(string_xor("0", "0"), "0");
}

TEST(StringXorTest, SingleBitOneOne) {
    EXPECT_EQ(string_xor("1", "1"), "0");
}

TEST(StringXorTest, SingleBitZeroOne) {
    EXPECT_EQ(string_xor("0", "1"), "1");
}

TEST(StringXorTest, SingleBitOneZero) {
    EXPECT_EQ(string_xor("1", "0"), "1");
}

TEST(StringXorTest, EmptyStrings) {
    EXPECT_EQ(string_xor("", ""), "");
}

TEST(StringXorTest, LongerStringA) {
    EXPECT_EQ(string_xor("11010", "110"), "001");
}

TEST(StringXorTest, LongerStringB) {
    EXPECT_EQ(string_xor("110", "11010"), "001");
}

TEST(StringXorTest, MixedPattern) {
    EXPECT_EQ(string_xor("10101", "01010"), "11111");
}

TEST(StringXorTest, MixedPatternReversed) {
    EXPECT_EQ(string_xor("01010", "10101"), "11111");
}

TEST(StringXorTest, IdenticalStrings) {
    EXPECT_EQ(string_xor("10110101", "10110101"), "00000000");
}

TEST(StringXorTest, LengthOneVsEmpty) {
    EXPECT_EQ(string_xor("1", ""), "");
}

TEST(StringXorTest, EmptyVsLengthOne) {
    EXPECT_EQ(string_xor("", "1"), "");
}

TEST(StringXorTest, LongerBinaryStrings) {
    EXPECT_EQ(string_xor("11001100", "10101010"), "01100110");
}

TEST(StringXorTest, OutputLengthEqualsMinLength_Alonger) {
    string result = string_xor("111111", "000");
    EXPECT_EQ(result.length(), (size_t)3);
    EXPECT_EQ(result, "111");
}

TEST(StringXorTest, OutputLengthEqualsMinLength_Blonger) {
    string result = string_xor("000", "111111");
    EXPECT_EQ(result.length(), (size_t)3);
    EXPECT_EQ(result, "111");
}

TEST(StringXorTest, OutputLengthEqualsSameLength) {
    string result = string_xor("101", "010");
    EXPECT_EQ(result.length(), (size_t)3);
    EXPECT_EQ(result, "111");
}

TEST(StringXorTest, OnlyZerosAndOnes_ComplexMix) {
    EXPECT_EQ(string_xor("110100", "011011"), "101111");
}

TEST(StringXorTest, SingleOneVsMultiple) {
    EXPECT_EQ(string_xor("1", "101"), "0");
}

TEST(StringXorTest, SingleZeroVsMultiple) {
    EXPECT_EQ(string_xor("0", "101"), "1");
}

TEST(StringXorTest, MultipleVsSingleOne) {
    EXPECT_EQ(string_xor("101", "1"), "0");
}

TEST(StringXorTest, MultipleVsSingleZero) {
    EXPECT_EQ(string_xor("101", "0"), "1");
}

TEST(StringXorTest, EightBitXor) {
    EXPECT_EQ(string_xor("11111111", "00000000"), "11111111");
}

TEST(StringXorTest, EightBitXorAllSame) {
    EXPECT_EQ(string_xor("10101010", "10101010"), "00000000");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}