#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "parse_music.h" // Assume the function is declared here

using namespace std;

TEST(ParseMusicTest, EmptyStringReturnsEmptyVector) {
    vector<int> result = parse_music("");
    EXPECT_TRUE(result.empty());
}

TEST(ParseMusicTest, SingleWholeNote) {
    vector<int> result = parse_music("o");
    vector<int> expected = {4};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, SingleHalfNote) {
    vector<int> result = parse_music("o|");
    vector<int> expected = {2};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, SingleQuarterNote) {
    vector<int> result = parse_music(".|");
    vector<int> expected = {1};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, MultipleNotesWithSpaces) {
    vector<int> result = parse_music("o o| .|");
    vector<int> expected = {4, 2, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, ExampleFromProblem) {
    vector<int> result = parse_music("o o| .| o| o| .| .| .| .| o o");
    vector<int> expected = {4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, LeadingSpace) {
    vector<int> result = parse_music(" o o|");
    vector<int> expected = {4, 2};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, TrailingSpace) {
    vector<int> result = parse_music("o o| ");
    vector<int> expected = {4, 2};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, MultipleSpacesBetweenNotes) {
    vector<int> result = parse_music("o  o|   .|");
    vector<int> expected = {4, 2, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, AllNoteTypesRepeated) {
    vector<int> result = parse_music("o o o o| o| .| .|");
    vector<int> expected = {4, 4, 4, 2, 2, 1, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, SingleNoteWithNoTrailingSpace) {
    vector<int> result = parse_music("o|");
    vector<int> expected = {2};
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, WhitespaceOnlyString) {
    vector<int> result = parse_music("   ");
    EXPECT_TRUE(result.empty());
}

TEST(ParseMusicTest, NewlineInsteadOfSpace) {
    vector<int> result = parse_music("o\no|");
    // The function splits only on spaces, not newlines
    // This tests the actual behavior of the implementation
    vector<int> expected = {}; // "o\no|" becomes one token that doesn't match any pattern
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, TabInsteadOfSpace) {
    vector<int> result = parse_music("o\to|");
    vector<int> expected = {}; // Tab not recognized as delimiter
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, InvalidNoteIgnored) {
    vector<int> result = parse_music("o x o|");
    vector<int> expected = {4, 2}; // "x" doesn't match any pattern
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, VeryLongString) {
    string input;
    vector<int> expected;
    for (int i = 0; i < 1000; i++) {
        if (i % 3 == 0) {
            input += "o ";
            expected.push_back(4);
        } else if (i % 3 == 1) {
            input += "o| ";
            expected.push_back(2);
        } else {
            input += ".| ";
            expected.push_back(1);
        }
    }
    // Remove trailing space
    if (!input.empty()) input.pop_back();
    
    vector<int> result = parse_music(input);
    EXPECT_EQ(result, expected);
}

TEST(ParseMusicTest, MixedValidAndInvalidWithSpaces) {
    vector<int> result = parse_music("o invalid o| .| bad .|");
    vector<int> expected = {4, 2, 1, 1};
    EXPECT_EQ(result, expected);
}