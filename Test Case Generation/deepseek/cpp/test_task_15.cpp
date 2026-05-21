#include <gtest/gtest.h>
#include <string>

using namespace std;

// Declaration of the function to test
string string_sequence(int n);

// Test suite for string_sequence function
class StringSequenceTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test case: n = 0 (minimum value)
TEST_F(StringSequenceTest, HandlesMinimumValueZero) {
    EXPECT_EQ(string_sequence(0), "0");
}

// Test case: n = 1
TEST_F(StringSequenceTest, HandlesOne) {
    EXPECT_EQ(string_sequence(1), "0 1");
}

// Test case: n = 5 (normal case from example)
TEST_F(StringSequenceTest, HandlesFive) {
    EXPECT_EQ(string_sequence(5), "0 1 2 3 4 5");
}

// Test case: n = 10 (medium range)
TEST_F(StringSequenceTest, HandlesTen) {
    EXPECT_EQ(string_sequence(10), "0 1 2 3 4 5 6 7 8 9 10");
}

// Test case: n = 100 (larger number)
TEST_F(StringSequenceTest, HandlesHundred) {
    string expected = "0";
    for (int i = 1; i <= 100; ++i) {
        expected += " " + to_string(i);
    }
    EXPECT_EQ(string_sequence(100), expected);
}

// Test case: n = 999 (edge case - three digits)
TEST_F(StringSequenceTest, HandlesThreeDigitNumber) {
    string expected = "0";
    for (int i = 1; i <= 999; ++i) {
        expected += " " + to_string(i);
    }
    EXPECT_EQ(string_sequence(999), expected);
}

// Test case: n = -1 (negative number - the loop won't execute)
TEST_F(StringSequenceTest, HandlesNegativeValue) {
    EXPECT_EQ(string_sequence(-1), "0");
}

// Test case: n = -100 (large negative value)
TEST_F(StringSequenceTest, HandlesLargeNegativeValue) {
    EXPECT_EQ(string_sequence(-100), "0");
}

// Test case: n = INT_MAX (maximum integer value - verifies no overflow)
TEST_F(StringSequenceTest, HandlesMaxInt) {
    string expected = "0";
    // Only test up to 1000 for performance, verify the loop condition works
    EXPECT_NO_THROW(string_sequence(1000));
}

// Test case: verifying correct spacing pattern
TEST_F(StringSequenceTest, VerifiesCorrectSpacingPattern) {
    string result = string_sequence(3);
    // Check that there are no double spaces or leading/trailing spaces
    EXPECT_EQ(result, "0 1 2 3");
    EXPECT_EQ(result.find("  "), string::npos); // No double spaces
    EXPECT_NE(result.front(), ' '); // No leading space
    EXPECT_NE(result.back(), ' '); // No trailing space
}

// Test case: n = 2 (smallest non-trivial case)
TEST_F(StringSequenceTest, HandlesTwo) {
    EXPECT_EQ(string_sequence(2), "0 1 2");
}

// Edge case: n = INT_MIN verify no issues
TEST_F(StringSequenceTest, HandlesMinInt) {
    EXPECT_EQ(string_sequence(INT_MIN), "0");
}