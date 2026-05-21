#include <gtest/gtest.h>
#include <vector>
#include <string>
using namespace std;

vector<string> separate_paren_groups(string paren_string);

TEST(SeparateParenGroupsTest, ExampleFromDocstring) {
    vector<string> result = separate_paren_groups("( ) (( )) (( )( ))");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "()");
    EXPECT_EQ(result[1], "(())");
    EXPECT_EQ(result[2], "(()())");
}

TEST(SeparateParenGroupsTest, EmptyString) {
    vector<string> result = separate_paren_groups("");
    EXPECT_TRUE(result.empty());
}

TEST(SeparateParenGroupsTest, OnlySpaces) {
    vector<string> result = separate_paren_groups("     ");
    EXPECT_TRUE(result.empty());
}

TEST(SeparateParenGroupsTest, SingleSimpleGroup) {
    vector<string> result = separate_paren_groups("()");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "()");
}

TEST(SeparateParenGroupsTest, SingleGroupWithSpaces) {
    vector<string> result = separate_paren_groups("( )");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "()");
}

TEST(SeparateParenGroupsTest, TwoSimpleGroups) {
    vector<string> result = separate_paren_groups("()()");
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "()");
    EXPECT_EQ(result[1], "()");
}

TEST(SeparateParenGroupsTest, TwoSimpleGroupsWithSpaces) {
    vector<string> result = separate_paren_groups("() ()");
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "()");
    EXPECT_EQ(result[1], "()");
}

TEST(SeparateParenGroupsTest, NestedGroup) {
    vector<string> result = separate_paren_groups("(())");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "(())");
}

TEST(SeparateParenGroupsTest, DeeplyNestedGroup) {
    vector<string> result = separate_paren_groups("((()))");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "((()))");
}

TEST(SeparateParenGroupsTest, MultipleNestedGroups) {
    vector<string> result = separate_paren_groups("(()) (())");
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "(())");
    EXPECT_EQ(result[1], "(())");
}

TEST(SeparateParenGroupsTest, MixedNestingLevels) {
    vector<string> result = separate_paren_groups("() (()) ((()))");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "()");
    EXPECT_EQ(result[1], "(())");
    EXPECT_EQ(result[2], "((()))");
}

TEST(SeparateParenGroupsTest, GroupWithMultipleChildrenAtSameLevel) {
    vector<string> result = separate_paren_groups("(()())");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "(()())");
}

TEST(SeparateParenGroupsTest, ComplexMixedGroups) {
    vector<string> result = separate_paren_groups("(()()) (()) ()");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "(()())");
    EXPECT_EQ(result[1], "(())");
    EXPECT_EQ(result[2], "()");
}

TEST(SeparateParenGroupsTest, SpacesBetweenEveryCharacter) {
    vector<string> result = separate_paren_groups("( ( ) ( ) )");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "(()())");
}

TEST(SeparateParenGroupsTest, LeadingAndTrailingSpaces) {
    vector<string> result = separate_paren_groups("   ()   ");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "()");
}

TEST(SeparateParenGroupsTest, ManyTopLevelGroups) {
    vector<string> result = separate_paren_groups("()()()()()");
    ASSERT_EQ(result.size(), 5);
    for (int i = 0; i < 5; i++) {
        EXPECT_EQ(result[i], "()");
    }
}

TEST(SeparateParenGroupsTest, FourLevelsDeepNesting) {
    vector<string> result = separate_paren_groups("(((())))");
    ASSERT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], "(((())))");
}

TEST(SeparateParenGroupsTest, StringWithOnlyIgnoredCharacters) {
    vector<string> result = separate_paren_groups("abc 123");
    EXPECT_TRUE(result.empty());
}

TEST(SeparateParenGroupsTest, SpacesInsideAndOutsideGroups) {
    vector<string> result = separate_paren_groups(" ( ( ) ) ( ) ");
    ASSERT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], "(())");
    EXPECT_EQ(result[1], "()");
}

TEST(SeparateParenGroupsTest, ReturnTypeIsVector) {
    vector<string> result = separate_paren_groups("()");
    EXPECT_EQ(typeid(result), typeid(vector<string>));
}

TEST(SeparateParenGroupsTest, GroupsAreIndependent) {
    vector<string> result = separate_paren_groups("(()) ()");
    ASSERT_EQ(result.size(), 2);
    EXPECT_NE(result[0], result[1]);
    EXPECT_EQ(result[0], "(())");
    EXPECT_EQ(result[1], "()");
}

TEST(SeparateParenGroupsTest, AsymmetricNestingAcrossGroups) {
    vector<string> result = separate_paren_groups("((( ))) (( )) ( )");
    ASSERT_EQ(result.size(), 3);
    EXPECT_EQ(result[0], "((()))");
    EXPECT_EQ(result[1], "(())");
    EXPECT_EQ(result[2], "()");
}