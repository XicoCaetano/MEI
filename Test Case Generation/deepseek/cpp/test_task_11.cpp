#include <gtest/gtest.h>
#include <string>
#include "string_xor.h"

class StringXorTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(StringXorTest, BothStringsEqualLength) {
    EXPECT_EQ(string_xor("010", "110"), "100");
    EXPECT_EQ(string_xor("000", "000"), "000");
    EXPECT_EQ(string_xor("111", "111"), "000");
    EXPECT_EQ(string_xor("101", "010"), "111");
    EXPECT_EQ(string_xor("000", "111"), "111");
}

TEST_F(StringXorTest, FirstStringLonger) {
    EXPECT_EQ(string_xor("01010", "110"), "10010");
    EXPECT_EQ(string_xor("1111", "0"), "1111");
    EXPECT_EQ(string_xor("1000", "1"), "0001");
    EXPECT_EQ(string_xor("111000", "101"), "010101");
}

TEST_F(StringXorTest, SecondStringLonger) {
    EXPECT_EQ(string_xor("110", "01010"), "10010");
    EXPECT_EQ(string_xor("0", "1111"), "1111");
    EXPECT_EQ(string_xor("1", "1000"), "0001");
    EXPECT_EQ(string_xor("101", "111000"), "010101");
}

TEST_F(StringXorTest, EmptyStrings) {
    EXPECT_EQ(string_xor("", ""), "");
    EXPECT_EQ(string_xor("", "101"), "101");
    EXPECT_EQ(string_xor("101", ""), "101");
    EXPECT_EQ(string_xor("", "0"), "0");
    EXPECT_EQ(string_xor("0", ""), "0");
}

TEST_F(StringXorTest, SingleCharacter) {
    EXPECT_EQ(string_xor("0", "0"), "0");
    EXPECT_EQ(string_xor("1", "1"), "0");
    EXPECT_EQ(string_xor("0", "1"), "1");
    EXPECT_EQ(string_xor("1", "0"), "1");
}

TEST_F(StringXorTest, AllZeros) {
    EXPECT_EQ(string_xor("00000", "00000"), "00000");
    EXPECT_EQ(string_xor("000", "111"), "111");
    EXPECT_EQ(string_xor("0000", "1010"), "1010");
}

TEST_F(StringXorTest, AllOnes) {
    EXPECT_EQ(string_xor("11111", "11111"), "00000");
    EXPECT_EQ(string_xor("111", "000"), "111");
    EXPECT_EQ(string_xor("1111", "0101"), "1010");
}

TEST_F(StringXorTest, DifferentLengthsEdgeCases) {
    EXPECT_EQ(string_xor("1", "10"), "11");
    EXPECT_EQ(string_xor("10", "1"), "11");
    EXPECT_EQ(string_xor("0", "100"), "100");
    EXPECT_EQ(string_xor("100", "0"), "100");
    EXPECT_EQ(string_xor("11", "110"), "101");
    EXPECT_EQ(string_xor("110", "11"), "101");
}

TEST_F(StringXorTest, LongStrings) {
    std::string long_a(1000, '1');
    std::string long_b(1000, '0');
    std::string expected(1000, '1');
    EXPECT_EQ(string_xor(long_a, long_b), expected);
    
    std::string long_all_ones(1000, '1');
    std::string expected_all_zeros(1000, '0');
    EXPECT_EQ(string_xor(long_all_ones, long_all_ones), expected_all_zeros);
}

TEST_F(StringXorTest, AlternatingPatterns) {
    EXPECT_EQ(string_xor("101010", "010101"), "111111");
    EXPECT_EQ(string_xor("10101", "01010"), "11111");
    EXPECT_EQ(string_xor("110011", "001100"), "111111");
}

TEST_F(StringXorTest, FirstStringShorter) {
    EXPECT_EQ(string_xor("010", "11011"), "10011");
    EXPECT_EQ(string_xor("1", "101"), "001");
    EXPECT_EQ(string_xor("00", "111"), "111");
}

TEST_F(StringXorTest, SecondStringShorter) {
    EXPECT_EQ(string_xor("11011", "010"), "10011");
    EXPECT_EQ(string_xor("101", "1"), "001");
    EXPECT_EQ(string_xor("111", "00"), "111");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}