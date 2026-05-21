#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "parse_nested_parens.h" // Assuming the function is declared here

using namespace std;

// Test fixture for parse_nested_parens function
class ParseNestedParensTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test empty string
TEST_F(ParseNestedParensTest, EmptyString) {
    vector<int> result = parse_nested_parens("");
    EXPECT_TRUE(result.empty());
}

// Test single group with no nesting
TEST_F(ParseNestedParensTest, SingleGroupNoNesting) {
    vector<int> result = parse_nested_parens("()");
    vector<int> expected = {1};
    EXPECT_EQ(result, expected);
}

// Test single group with nesting level 2
TEST_F(ParseNestedParensTest, SingleGroupNesting2) {
    vector<int> result = parse_nested_parens("(())");
    vector<int> expected = {2};
    EXPECT_EQ(result, expected);
}

// Test single group with nesting level 3
TEST_F(ParseNestedParensTest, SingleGroupNesting3) {
    vector<int> result = parse_nested_parens("((()))");
    vector<int> expected = {3};
    EXPECT_EQ(result, expected);
}

// Test single group with multiple parentheses but max nesting level 2
TEST_F(ParseNestedParensTest, SingleGroupMultiplePairsNesting2) {
    vector<int> result = parse_nested_parens("(()())");
    vector<int> expected = {2};
    EXPECT_EQ(result, expected);
}

// Test multiple groups from example
TEST_F(ParseNestedParensTest, MultipleGroupsExample) {
    vector<int> result = parse_nested_parens("(()()) ((())) () ((())()())");
    vector<int> expected = {2, 3, 1, 3};
    EXPECT_EQ(result, expected);
}

// Test groups separated by multiple spaces
TEST_F(ParseNestedParensTest, MultipleSpacesBetweenGroups) {
    vector<int> result = parse_nested_parens("()   (())    ((()))");
    vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

// Test leading and trailing spaces
TEST_F(ParseNestedParensTest, LeadingAndTrailingSpaces) {
    vector<int> result = parse_nested_parens("  (())  ()  ");
    vector<int> expected = {2, 1};
    EXPECT_EQ(result, expected);
}

// Test complex nesting patterns
TEST_F(ParseNestedParensTest, ComplexNesting) {
    vector<int> result = parse_nested_parens("((()())) (()(()))");
    vector<int> expected = {3, 3};
    EXPECT_EQ(result, expected);
}

// Test single group with maximum nesting at beginning
TEST_F(ParseNestedParensTest, MaxNestingAtBeginning) {
    vector<int> result = parse_nested_parens("((()))()");
    vector<int> expected = {3, 1};
    EXPECT_EQ(result, expected);
}

// Test single group with maximum nesting in middle
TEST_F(ParseNestedParensTest, MaxNestingInMiddle) {
    vector<int> result = parse_nested_parens("(()(()))");
    vector<int> expected = {3};
    EXPECT_EQ(result, expected);
}

// Test groups with varying levels
TEST_F(ParseNestedParensTest, VaryingLevels) {
    vector<int> result = parse_nested_parens("() ((())) (()) ()");
    vector<int> expected = {1, 3, 2, 1};
    EXPECT_EQ(result, expected);
}

// Test deep nesting
TEST_F(ParseNestedParensTest, DeepNesting) {
    vector<int> result = parse_nested_parens("((((()))))");
    vector<int> expected = {5};
    EXPECT_EQ(result, expected);
}

// Test unbalanced parentheses - edge case (assuming valid input as per spec)
// Note: The function assumes valid input, but testing gracefully handles it
TEST_F(ParseNestedParensTest, UnbalancedParenthesesExtraOpen) {
    // The function will still return a result based on its logic
    // Groups are only pushed when level returns to 0
    vector<int> result = parse_nested_parens("(()");
    // Since level never returns to 0, no groups are pushed
    EXPECT_TRUE(result.empty());
}

TEST_F(ParseNestedParensTest, UnbalancedParenthesesExtraClose) {
    // Starting with close parenthesis causes level to go negative
    // But we still process until a group completes or end of string
    vector<int> result = parse_nested_parens("())");
    // Level starts at 0, sees ')', becomes -1, then sees '(' etc.
    // The first group ends when level returns to -1? Actually level becomes -2 etc.
    // For "())", sequence: ')'(level=-1), ')'(level=-2), never reaches 0 from positive
    // So no groups pushed
    EXPECT_TRUE(result.empty());
}

// Test single character (no parentheses)
TEST_F(ParseNestedParensTest, NoParentheses) {
    vector<int> result = parse_nested_parens("abc");
    EXPECT_TRUE(result.empty());
}

// Test spaces only
TEST_F(ParseNestedParensTest, SpacesOnly) {
    vector<int> result = parse_nested_parens("     ");
    EXPECT_TRUE(result.empty());
}

// Test groups with no spaces between them (invalid per spec but testing code behavior)
TEST_F(ParseNestedParensTest, NoSpacesBetweenGroups) {
    vector<int> result = parse_nested_parens("()()()");
    vector<int> expected = {1, 1, 1};
    EXPECT_EQ(result, expected);
}

// Test empty group (impossible with valid parentheses, but for completeness)
TEST_F(ParseNestedParensTest, EmptyParenthesesGroup) {
    vector<int> result = parse_nested_parens("()");
    vector<int> expected = {1};
    EXPECT_EQ(result, expected);
}

// Test large number of groups
TEST_F(ParseNestedParensTest, ManyGroups) {
    string input;
    for (int i = 0; i < 100; i++) {
        input += "() ";
    }
    input.pop_back(); // Remove trailing space
    
    vector<int> result = parse_nested_parens(input);
    EXPECT_EQ(result.size(), 100);
    for (int level : result) {
        EXPECT_EQ(level, 1);
    }
}

// Test mixed complexity
TEST_F(ParseNestedParensTest, MixedComplexity) {
    vector<int> result = parse_nested_parens("((())) (()()) ((())()) (((())))");
    vector<int> expected = {3, 2, 3, 4};
    EXPECT_EQ(result, expected);
}

// Test string with tabs instead of spaces
TEST_F(ParseNestedParensTest, TabsAsSeparators) {
    // The function only checks spaces, so tabs won't separate groups
    // This tests the actual behavior
    vector<int> result = parse_nested_parens("()\t(())");
    // Since '\t' is not space, everything is treated as one group
    vector<int> expected = {2}; // "()(())" has max nesting 2
    EXPECT_EQ(result, expected);
}

// Test random spaces
TEST_F(ParseNestedParensTest, RandomSpaces) {
    vector<int> result = parse_nested_parens("  (())   ()   ((()))  ");
    vector<int> expected = {2, 1, 3};
    EXPECT_EQ(result, expected);
}

// Test with newlines and spaces (assuming input doesn't have newlines per spec)
TEST_F(ParseNestedParensTest, NewlinesAndSpaces) {
    // Newlines are not spaces, so they'd be part of the group
    vector<int> result = parse_nested_parens("()\n()");
    // Treated as single group "()\n()" which is invalid parentheses
    // So no groups completed if newline doesn't close properly
    // The function only looks for '(', ')', and spaces
    // Newline will be ignored as it's not recognized
    // Actually, the code processes each char, ignoring those not '(' or ')'
    // So "()\n()" becomes two groups because '\n' is not space? Wait, the code only checks for spaces specifically
    // '\n' is not space, so the whole string is one continuous stream: '(',')', '\n', '(', ')'
    // Since '\n' is not '(' or ')', it's just skipped. So we have "( ) ( )" -> "()()" which forms two groups
    // Let me trace: 
    // char[0]='(', level=1,max=1
    // char[1]=')', level=0 -> push(1)
    // char[2]='\n', no change
    // char[3]='(', level=1,max=1
    // char[4]=')', level=0 -> push(1)
    // Result: {1,1}
    vector<int> expected = {1, 1};
    EXPECT_EQ(result, expected);
}
