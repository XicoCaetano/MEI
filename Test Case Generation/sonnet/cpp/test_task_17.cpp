#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

vector<int> parse_music(string music_string);

TEST(ParseMusicTest, EmptyString) {
    EXPECT_EQ(parse_music(""), vector<int>({}));
}

TEST(ParseMusicTest, SingleWholeNote) {
    EXPECT_EQ(parse_music("o"), vector<int>({4}));
}

TEST(ParseMusicTest, SingleHalfNote) {
    EXPECT_EQ(parse_music("o|"), vector<int>({2}));
}

TEST(ParseMusicTest, SingleQuarterNote) {
    EXPECT_EQ(parse_music(".|"), vector<int>({1}));
}

TEST(ParseMusicTest, ExampleFromDocstring) {
    vector<int> expected = {4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4};
    EXPECT_EQ(parse_music("o o| .| o| o| .| .| .| .| o o"), expected);
}

TEST(ParseMusicTest, MultipleWholeNotes) {
    EXPECT_EQ(parse_music("o o o"), vector<int>({4, 4, 4}));
}

TEST(ParseMusicTest, MultipleHalfNotes) {
    EXPECT_EQ(parse_music("o| o| o|"), vector<int>({2, 2, 2}));
}

TEST(ParseMusicTest, MultipleQuarterNotes) {
    EXPECT_EQ(parse_music(".| .| .|"), vector<int>({1, 1, 1}));
}

TEST(ParseMusicTest, WholeAndHalfNotes) {
    EXPECT_EQ(parse_music("o o|"), vector<int>({4, 2}));
}

TEST(ParseMusicTest, HalfAndQuarterNotes) {
    EXPECT_EQ(parse_music("o| .|"), vector<int>({2, 1}));
}

TEST(ParseMusicTest, WholeAndQuarterNotes) {
    EXPECT_EQ(parse_music("o .|"), vector<int>({4, 1}));
}

TEST(ParseMusicTest, UnknownTokenIgnored) {
    EXPECT_EQ(parse_music("x"), vector<int>({}));
}

TEST(ParseMusicTest, MixedValidAndInvalidTokens) {
    EXPECT_EQ(parse_music("o x o|"), vector<int>({4, 2}));
}

TEST(ParseMusicTest, OnlySpaces) {
    EXPECT_EQ(parse_music("   "), vector<int>({}));
}

TEST(ParseMusicTest, MultipleSpacesBetweenNotes) {
    EXPECT_EQ(parse_music("o  o|"), vector<int>({4, 2}));
}

TEST(ParseMusicTest, LeadingSpace) {
    EXPECT_EQ(parse_music(" o"), vector<int>({4}));
}

TEST(ParseMusicTest, TrailingSpace) {
    EXPECT_EQ(parse_music("o "), vector<int>({4}));
}

TEST(ParseMusicTest, LeadingAndTrailingSpaces) {
    EXPECT_EQ(parse_music(" o| "), vector<int>({2}));
}

TEST(ParseMusicTest, LongSequence) {
    vector<int> expected = {4, 2, 1, 1, 2, 4, 1, 2};
    EXPECT_EQ(parse_music("o o| .| .| o| o .| o|"), expected);
}

TEST(ParseMusicTest, AllNoteTypes) {
    vector<int> expected = {4, 2, 1};
    EXPECT_EQ(parse_music("o o| .|"), expected);
}

TEST(ParseMusicTest, RepeatedQuarterNotes) {
    vector<int> expected = {1, 1, 1, 1};
    EXPECT_EQ(parse_music(".| .| .| .|"), expected);
}

TEST(ParseMusicTest, SingleDotNotANote) {
    EXPECT_EQ(parse_music("."), vector<int>({}));
}

TEST(ParseMusicTest, SinglePipeNotANote) {
    EXPECT_EQ(parse_music("|"), vector<int>({}));
}

TEST(ParseMusicTest, DotWithoutPipeIgnored) {
    EXPECT_EQ(parse_music(". o"), vector<int>({4}));
}

TEST(ParseMusicTest, OWithoutPipeIsWholeNote) {
    EXPECT_EQ(parse_music("o o|"), vector<int>({4, 2}));
}

TEST(ParseMusicTest, TwoCharacterInvalidToken) {
    EXPECT_EQ(parse_music(".. o"), vector<int>({4}));
}

TEST(ParseMusicTest, EmptyAfterSplit) {
    EXPECT_EQ(parse_music("o| o .| o o| .|"), vector<int>({2, 4, 1, 4, 2, 1}));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}