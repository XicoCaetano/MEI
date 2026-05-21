#include <gtest/gtest.h>
#include <string>
using namespace std;

string flip_case(string str){
    string out="";
    for (int i=0;i<str.length();i++)
    {
        char w=str[i];
        if (w>=97 and w<=122) {w-=32;}
        else
            if (w>=65 and w<=90){ w+=32;}
        out=out+w;
    }
    return out;
}

TEST(FlipCaseTest, EmptyString) {
    EXPECT_EQ(flip_case(""), "");
}

TEST(FlipCaseTest, SingleLowercase) {
    EXPECT_EQ(flip_case("a"), "A");
    EXPECT_EQ(flip_case("z"), "Z");
    EXPECT_EQ(flip_case("m"), "M");
}

TEST(FlipCaseTest, SingleUppercase) {
    EXPECT_EQ(flip_case("A"), "a");
    EXPECT_EQ(flip_case("Z"), "z");
    EXPECT_EQ(flip_case("M"), "m");
}

TEST(FlipCaseTest, MixedCase) {
    EXPECT_EQ(flip_case("Hello"), "hELLO");
    EXPECT_EQ(flip_case("hELLO"), "Hello");
    EXPECT_EQ(flip_case("HeLLo"), "hEllO");
}

TEST(FlipCaseTest, AllLowercase) {
    EXPECT_EQ(flip_case("hello"), "HELLO");
    EXPECT_EQ(flip_case("world"), "WORLD");
    EXPECT_EQ(flip_case("abcdefghijklmnopqrstuvwxyz"), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

TEST(FlipCaseTest, AllUppercase) {
    EXPECT_EQ(flip_case("HELLO"), "hello");
    EXPECT_EQ(flip_case("WORLD"), "world");
    EXPECT_EQ(flip_case("ABCDEFGHIJKLMNOPQRSTUVWXYZ"), "abcdefghijklmnopqrstuvwxyz");
}

TEST(FlipCaseTest, BoundaryLowercaseCharacters) {
    EXPECT_EQ(flip_case("a"), "A");
    EXPECT_EQ(flip_case("z"), "Z");
}

TEST(FlipCaseTest, BoundaryUppercaseCharacters) {
    EXPECT_EQ(flip_case("A"), "a");
    EXPECT_EQ(flip_case("Z"), "z");
}

TEST(FlipCaseTest, NonAlphabeticCharacters) {
    EXPECT_EQ(flip_case("123"), "123");
    EXPECT_EQ(flip_case("!@#$%^&*()"), "!@#$%^&*()");
    EXPECT_EQ(flip_case(" "), " ");
    EXPECT_EQ(flip_case("\t\n"), "\t\n");
    EXPECT_EQ(flip_case(",./<>?;':\"[]{}\\|`~"), ",./<>?;':\"[]{}\\|`~");
}

TEST(FlipCaseTest, MixedAlphaAndNonAlpha) {
    EXPECT_EQ(flip_case("Hello, World!"), "hELLO, wORLD!");
    EXPECT_EQ(flip_case("abc123"), "ABC123");
    EXPECT_EQ(flip_case("ABC123"), "abc123");
    EXPECT_EQ(flip_case("a1B2c3"), "A1b2C3");
    EXPECT_EQ(flip_case("Test 123!"), "tEST 123!");
}

TEST(FlipCaseTest, StringWithSpaces) {
    EXPECT_EQ(flip_case("Hello World"), "hELLO wORLD");
    EXPECT_EQ(flip_case("   "), "   ");
    EXPECT_EQ(flip_case("a b c"), "A B C");
}

TEST(FlipCaseTest, LongString) {
    string lower(100, 'a');
    string upper(100, 'A');
    EXPECT_EQ(flip_case(lower), upper);
    EXPECT_EQ(flip_case(upper), lower);
}

TEST(FlipCaseTest, RepeatedApplication) {
    string original = "Hello, World!";
    EXPECT_EQ(flip_case(flip_case(original)), original);
}

TEST(FlipCaseTest, CharactersJustOutsideAlphaRange) {
    string just_below_upper = "";
    just_below_upper += (char)64;
    EXPECT_EQ(flip_case(just_below_upper), just_below_upper);

    string just_above_upper = "";
    just_above_upper += (char)91;
    EXPECT_EQ(flip_case(just_above_upper), just_above_upper);

    string just_below_lower = "";
    just_below_lower += (char)96;
    EXPECT_EQ(flip_case(just_below_lower), just_below_lower);

    string just_above_lower = "";
    just_above_lower += (char)123;
    EXPECT_EQ(flip_case(just_above_lower), just_above_lower);
}

TEST(FlipCaseTest, SingleNonAlpha) {
    EXPECT_EQ(flip_case("1"), "1");
    EXPECT_EQ(flip_case("!"), "!");
    EXPECT_EQ(flip_case(" "), " ");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}