#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <boost/any.hpp>
#include <list>

typedef std::list<boost::any> list_any;
using namespace std;

// Function prototype
vector<int> filter_integers(list_any values);

class FilterIntegersTest : public ::testing::Test {};

// Test case for the first example provided in docstring
TEST_F(FilterIntegersTest, HandlesMixedTypesWithFloatsAndStrings) {
    list_any input = { string("a"), 3.14, 5 };
    vector<int> expected = { 5 };
    EXPECT_EQ(filter_integers(input), expected);
}

// Test case for the second example provided in docstring
TEST_F(FilterIntegersTest, HandlesMixedTypesWithEmptyContainers) {
    list_any input = { 1, 2, 3, string("abc"), list_any{}, list_any{} };
    vector<int> expected = { 1, 2, 3 };
    EXPECT_EQ(filter_integers(input), expected);
}

// Edge case: Empty input list
TEST_F(FilterIntegersTest, HandlesEmptyList) {
    list_any input;
    vector<int> expected;
    EXPECT_TRUE(filter_integers(input).empty());
}

// Edge case: List with no integers
TEST_F(FilterIntegersTest, ReturnsEmptyVectorWhenNoIntegersPresent) {
    list_any input = { string("hello"), 2.718, false, 'c' };
    vector<int> expected;
    EXPECT_EQ(filter_integers(input), expected);
}

// Edge case: List with only integers
TEST_F(FilterIntegersTest, HandlesOnlyIntegers) {
    list_any input = { -1, 0, 42, 1000 };
    vector<int> expected = { -1, 0, 42, 1000 };
    EXPECT_EQ(filter_integers(input), expected);
}

// Edge case: Large integers and boundaries
TEST_F(FilterIntegersTest, HandlesIntegerBoundaries) {
    list_any input = { numeric_limits<int>::min(), numeric_limits<int>::max() };
    vector<int> expected = { numeric_limits<int>::min(), numeric_limits<int>::max() };
    EXPECT_EQ(filter_integers(input), expected);
}

// Testing specifically against similar types that are NOT int (long, short, etc.)
TEST_F(FilterIntegersTest, DoesNotMatchNonIntNumericTypes) {
    list_any input = { 10L, (short)5, 20.0f, 30.0 };
    vector<int> expected;
    EXPECT_EQ(filter_integers(input), expected);
}

// Verifying loop logic with multiple occurrences
TEST_F(FilterIntegersTest, HandlesDuplicatesAndOrdering) {
    list_any input = { 7, 7, string("test"), 8, 7 };
    vector<int> expected = { 7, 7, 8, 7 };
    EXPECT_EQ(filter_integers(input), expected);
}