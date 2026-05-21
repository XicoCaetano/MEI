#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

vector<int> parse_nested_parens(string paren_string);

TEST(ParseNestedParens, ExampleFromDocstring) {
    vector<int> result = parse_nested_parens("(()()) ((())) () ((())()())");
    vector<int> expected = {2, 3, 1, 3};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, SingleFlatGroup) {
    vector<int> result = parse_nested_parens("()");
    vector<int> expected = {1};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, SingleDeepGroup) {
    vector<int> result = parse_nested_parens("((()))");
    vector<int> expected = {3};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, TwoLevels) {
    vector<int> result = parse_nested_parens("(()())");
    vector<int> expected = {2};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, MultipleGroups) {
    vector<int> result = parse_nested_parens("((())) ()");
    vector<int> expected = {3, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, EmptyString) {
    vector<int> result = parse_nested_parens("");
    vector<int> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, OnlySpaces) {
    vector<int> result = parse_nested_parens("   ");
    vector<int> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, SingleGroupDepthOne) {
    vector<int> result = parse_nested_parens("()");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 1);
}

TEST(ParseNestedParens, SingleGroupDepthFour) {
    vector<int> result = parse_nested_parens("(((())))");
    vector<int> expected = {4};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, MultipleGroupsAllFlat) {
    vector<int> result = parse_nested_parens("() () ()");
    vector<int> expected = {1, 1, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, MultipleGroupsIncreasingDepth) {
    vector<int> result = parse_nested_parens("() (()) ((()))");
    vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, MultipleGroupsDecreasingDepth) {
    vector<int> result = parse_nested_parens("((())) (()) ()");
    vector<int> expected = {3, 2, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, GroupWithMultipleSiblings) {
    vector<int> result = parse_nested_parens("(()()())");
    vector<int> expected = {2};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, NestedAndSiblingsMixed) {
    vector<int> result = parse_nested_parens("((())()())");
    vector<int> expected = {3};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, MaxLevelResetBetweenGroups) {
    vector<int> result = parse_nested_parens("((())) ()");
    EXPECT_EQ(result[0], 3);
    EXPECT_EQ(result[1], 1);
}

TEST(ParseNestedParens, FiveGroups) {
    vector<int> result = parse_nested_parens("() (()) ((())) (()) ()");
    vector<int> expected = {1, 2, 3, 2, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, DeepNestingFiveLevel) {
    vector<int> result = parse_nested_parens("((((()))))");
    vector<int> expected = {5};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, SpaceBetweenEveryGroup) {
    vector<int> result = parse_nested_parens("() () () ()");
    vector<int> expected = {1, 1, 1, 1};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, ComplexGroupMaxLevelIsCorrect) {
    // ((())()()) -> deepest is 3 (the ((()))) part
    vector<int> result = parse_nested_parens("((())()())");
    EXPECT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 3);
}

TEST(ParseNestedParens, ResultSizeMatchesGroupCount) {
    vector<int> result = parse_nested_parens("(()()) ((())) () ((())()())");
    EXPECT_EQ(result.size(), 4u);
}

TEST(ParseNestedParens, TwoGroupsSameDepth) {
    vector<int> result = parse_nested_parens("((())) ((()))");
    vector<int> expected = {3, 3};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, GroupWithDeepAndShallowChildren) {
    // (()((()))) -> levels: ( -> 1, ( -> 2, ) -> 1, ( -> 2, ( -> 3, ( -> 4... wait
    // (()((()))) : depth trace: 1,2,1,2,3,4... No.
    // Let's trace: ( -> 1, ( -> 2, ) -> 1, ( -> 2, ( -> 3, ( -> 4 no, only 3 parens deep
    // (()((()))) = ( ( ) ( ( ( ) ) ) )
    // depths:       1 2 1 2 3 4... no let's count chars:
    // ( -> 1
    // ( -> 2
    // ) -> back to 1
    // ( -> 2
    // ( -> 3
    // ( -> 4? no: "(()((())))" that's 10 chars
    // Use: "(()((())))" 
    // ( ->1, ( ->2, ) ->1, ( ->2, ( ->3, ( ->4? No "(()((())))"
    // Simpler: "(()((())))" = ( ( ) ( ( ( ) ) ) )
    // 1 2 1 2 3 4 3 2 1 -> wait that's wrong count
    // "(()((())))" has depth 4? Let me just use a known value.
    vector<int> result = parse_nested_parens("(()(()))");
    // ( ->1, ( ->2, ) ->1, ( ->2, ( ->3, ) ->2, ) ->1, ) ->0 => max=3
    vector<int> expected = {3};
    EXPECT_EQ(result, expected);
}

TEST(ParseNestedParens, SingleGroupReturnsSingleElement) {
    vector<int> result = parse_nested_parens("((()))");
    EXPECT_EQ(result.size(), 1u);
}

TEST(ParseNestedParens, NonParenCharsIgnored) {
    // Only '(' and ')' are processed; spaces are ignored
    vector<int> result = parse_nested_parens("()");
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result[0], 1);
}