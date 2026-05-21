#include <gtest/gtest.h>
#include <string>
#include "flip_case.h"  // Assume the function is declared here

using namespace std;

TEST(FlipCaseTest, EmptyString) {
    EXPECT_EQ(flip_case(""), "");
}

TEST(FlipCaseTest, AllLowercaseLetters) {
    EXPECT_EQ(flip_case("hello"), "HELLO");
    EXPECT_EQ(flip_case("world"), "WORLD");
    EXPECT_EQ(flip_case("abcdefghijklmnopqrstuvwxyz"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

TEST(FlipCaseTest, AllUppercaseLetters) {
    EXPECT_EQ(flip_case("HELLO"), "hello");
    EXPECT_EQ(flip_case("WORLD"), "world");
    EXPECT_EQ(flip_case("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "abcdefghijklmnopqrstuvwxyz");
}

TEST(FlipCaseTest, MixedCase) {
    EXPECT_EQ(flip_case("Hello"), "hELLO");
    EXPECT_EQ(flip_case("HeLlO"), "hElLo");
    EXPECT_EQ(flip_case("hElLo"), "HeLlO");
    EXPECT_EQ(flip_case("TeStInG"), "tEsTiNg");
}

TEST(FlipCaseTest, NonAlphabeticCharacters) {
    EXPECT_EQ(flip_case("12345"), "12345");
    EXPECT_EQ(flip_case("!@#$%^&*()"), "!@#$%^&*()");
    EXPECT_EQ(flip_case("Hello123"), "hELLO123");
    EXPECT_EQ(flip_case("123Hello456"), "123hELLO456");
}

TEST(FlipCaseTest, WhitespaceCharacters) {
    EXPECT_EQ(flip_case(" "), " ");
    EXPECT_EQ(flip_case("  "), "  ");
    EXPECT_EQ(flip_case("\t"), "\t");
    EXPECT_EQ(flip_case("\n"), "\n");
    EXPECT_EQ(flip_case("Hello World"), "hELLO wORLD");
    EXPECT_EQ(flip_case("  Hello  World  "), "  hELLO  wORLD  ");
}

TEST(FlipCaseTest, SpecialCharactersAndMixed) {
    EXPECT_EQ(flip_case("Hello, World!"), "hELLO, wORLD!");
    EXPECT_EQ(flip_case("C++ Programming"), "c++ pROGRAMMING");
    EXPECT_EQ(flip_case("[Hello] {World}"), "[hELLO] {wORLD}");
}

TEST(FlipCaseTest, SingleCharacter) {
    EXPECT_EQ(flip_case("a"), "A");
    EXPECT_EQ(flip_case("Z"), "z");
    EXPECT_EQ(flip_case("5"), "5");
    EXPECT_EQ(flip_case("@"), "@");
}

TEST(FlipCaseTest, LongString) {
    string input = "The Quick Brown Fox Jumps Over The Lazy Dog";
    string expected = "tHE qUICK bROWN fOX jUMPS oVER tHE lAZY dOG";
    EXPECT_EQ(flip_case(input), expected);
}

TEST(FlipCaseTest, NumbersAndLettersOnly) {
    EXPECT_EQ(flip_case("a1b2c3"), "A1B2C3");
    EXPECT_EQ(flip_case("A1B2C3"), "a1b2c3");
    EXPECT_EQ(flip_case("Aa1Bb2Cc3"), "aA1bB2cC3");
}

TEST(FlipCaseTest, StringWithUnderscoreAndHyphen) {
    EXPECT_EQ(flip_case("Hello_World"), "hELLO_wORLD");
    EXPECT_EQ(flip_case("flip-case"), "FLIP-CASE");
    EXPECT_EQ(flip_case("UPPER-lower"), "upper-LOWER");
}

TEST(FlipCaseTest, AlreadyFlippedString) {
    string original = "Hello";
    string flipped = flip_case(original);
    EXPECT_EQ(flip_case(flipped), original);
}