#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "paren_groups.h"  // Assume a function está neste header

using namespace std;

TEST(SeparateParenGroupsTest, BasicExamples) {
    vector<string> result = separate_paren_groups("( ) (( )) (( )( ))");
    vector<string> expected = {"()", "(())", "(()())"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, SingleGroup) {
    vector<string> result = separate_paren_groups("(())");
    vector<string> expected = {"(())"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, MultipleAdjacentGroups) {
    vector<string> result = separate_paren_groups("()()()");
    vector<string> expected = {"()", "()", "()"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, NestedGroupsWithSpaces) {
    vector<string> result = separate_paren_groups("  (  )   ( ( ) )   ( ( ) ( ) )  ");
    vector<string> expected = {"()", "(())", "(()())"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, EmptyString) {
    vector<string> result = separate_paren_groups("");
    vector<string> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, OnlySpaces) {
    vector<string> result = separate_paren_groups("     ");
    vector<string> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, SinglePairWithSpaces) {
    vector<string> result = separate_paren_groups("  (    )  ");
    vector<string> expected = {"()"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, DeepNesting) {
    vector<string> result = separate_paren_groups("((((()))))");
    vector<string> expected = {"((((()))))"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, MultipleDifferentNestingLevels) {
    vector<string> result = separate_paren_groups("()(()) ((())) ()(())");
    vector<string> expected = {"()", "(())", "((()))", "()", "(())"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, ComplexWithSpacesAndTabs) {
    vector<string> result = separate_paren_groups("( )\t(( ))\n(( )( ))");
    vector<string> expected = {"()", "(())", "(()())"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, NoClosingParen) {
    vector<string> result = separate_paren_groups("((()");
    vector<string> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, NoOpeningParen) {
    vector<string> result = separate_paren_groups("()))");
    vector<string> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, UnmatchedInMiddle) {
    vector<string> result = separate_paren_groups("()(()(");
    vector<string> expected = {"()"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, ExtraClosingBeforeOpening) {
    vector<string> result = separate_paren_groups(")()");
    vector<string> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, SingleCharOnlyOpen) {
    vector<string> result = separate_paren_groups("(");
    vector<string> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, SingleCharOnlyClose) {
    vector<string> result = separate_paren_groups(")");
    vector<string> expected = {};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, MixedValidAndInvalid) {
    vector<string> result = separate_paren_groups("()(()))(()");
    vector<string> expected = {"()"};
    EXPECT_EQ(result, expected);
}

TEST(SeparateParenGroupsTest, VeryLongValidString) {
    string input(1000, '(');
    input.append(1000, ')');
    vector<string> result = separate_paren_groups(input);
    vector<string> expected = {input};
    EXPECT_EQ(result, expected);
}