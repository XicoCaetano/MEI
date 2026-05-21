#include <gtest/gtest.h>
#include <string>
#include "sort_numbers.h"  // Assumes the function is declared here

class SortNumbersTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Basic functionality tests
TEST_F(SortNumbersTest, SortsThreeNumbers) {
    EXPECT_EQ(sort_numbers("three one five"), "one three five");
}

TEST_F(SortNumbersTest, SortsTwoNumbers) {
    EXPECT_EQ(sort_numbers("nine zero"), "zero nine");
}

TEST_F(SortNumbersTest, SortsAllNumbers) {
    EXPECT_EQ(sort_numbers("nine eight seven six five four three two one zero"), 
              "zero one two three four five six seven eight nine");
}

TEST_F(SortNumbersTest, SingleNumber) {
    EXPECT_EQ(sort_numbers("five"), "five");
}

TEST_F(SortNumbersTest, EmptyString) {
    EXPECT_EQ(sort_numbers(""), "");
}

TEST_F(SortNumbersTest, StringWithOnlySpaces) {
    EXPECT_EQ(sort_numbers("   "), "");
}

// Edge cases with duplicates
TEST_F(SortNumbersTest, DuplicateNumbers) {
    EXPECT_EQ(sort_numbers("one one one"), "one one one");
}

TEST_F(SortNumbersTest, MixedDuplicates) {
    EXPECT_EQ(sort_numbers("two two one one three three"), "one one two two three three");
}

TEST_F(SortNumbersTest, AllSameNumber) {
    EXPECT_EQ(sort_numbers("five five five five"), "five five five five");
}

// Edge cases with leading/trailing/multiple spaces
TEST_F(SortNumbersTest, LeadingSpaces) {
    EXPECT_EQ(sort_numbers("  one two three"), "one two three");
}

TEST_F(SortNumbersTest, TrailingSpaces) {
    EXPECT_EQ(sort_numbers("one two three  "), "one two three");
}

TEST_F(SortNumbersTest, MultipleSpacesBetweenNumbers) {
    EXPECT_EQ(sort_numbers("one   two    three"), "one two three");
}

TEST_F(SortNumbersTest, MixedSpacing) {
    EXPECT_EQ(sort_numbers("  one   two  three  "), "one two three");
}

// Edge cases with specific number orders
TEST_F(SortNumbersTest, AlreadySortedAscending) {
    EXPECT_EQ(sort_numbers("zero one two three four"), "zero one two three four");
}

TEST_F(SortNumbersTest, AlreadySortedDescending) {
    EXPECT_EQ(sort_numbers("nine eight seven six"), "six seven eight nine");
}

TEST_F(SortNumbersTest, RandomOrder) {
    EXPECT_EQ(sort_numbers("seven three nine one zero five"), "zero one three five seven nine");
}

// Edge cases with all numbers from zero to nine in various orders
TEST_F(SortNumbersTest, AllNumbersRandomOrder) {
    EXPECT_EQ(sort_numbers("five two eight one nine four seven three zero six"),
              "zero one two three four five six seven eight nine");
}

// Tests with single character input (should handle gracefully)
TEST_F(SortNumbersTest, InvalidSingleCharacter) {
    // Will produce empty string or crash? The function assumes valid input but test edge behavior
    // This tests that the function doesn't crash on invalid input
    EXPECT_NO_THROW(sort_numbers("x"));
}

TEST_F(SortNumbersTest, MixedValidAndInvalid) {
    EXPECT_NO_THROW(sort_numbers("one two invalid three"));
}

// Additional coverage tests for internal state
TEST_F(SortNumbersTest, VeryLongString) {
    std::string input;
    for (int i = 0; i < 100; i++) {
        input += "zero ";
    }
    input += "nine";
    std::string expected;
    for (int i = 0; i < 100; i++) {
        expected += "zero ";
    }
    expected += "nine";
    EXPECT_EQ(sort_numbers(input), expected);
}

// Test with number at the end without trailing space (covered by function logic)
TEST_F(SortNumbersTest, NoTrailingSpaceInInput) {
    EXPECT_EQ(sort_numbers("one two three"), "one two three");
}

// Test with leading and trailing spaces combined with multiple spaces
TEST_F(SortNumbersTest, ComplexSpacing) {
    EXPECT_EQ(sort_numbers("   one   two   three   "), "one two three");
}

// Boundary tests for each number
TEST_F(SortNumbersTest, EachNumberIndividually) {
    EXPECT_EQ(sort_numbers("zero"), "zero");
    EXPECT_EQ(sort_numbers("one"), "one");
    EXPECT_EQ(sort_numbers("two"), "two");
    EXPECT_EQ(sort_numbers("three"), "three");
    EXPECT_EQ(sort_numbers("four"), "four");
    EXPECT_EQ(sort_numbers("five"), "five");
    EXPECT_EQ(sort_numbers("six"), "six");
    EXPECT_EQ(sort_numbers("seven"), "seven");
    EXPECT_EQ(sort_numbers("eight"), "eight");
    EXPECT_EQ(sort_numbers("nine"), "nine");
}

// Stress test with many repeated numbers
TEST_F(SortNumbersTest, ManyRepeatedNumbers) {
    std::string input;
    std::string expected;
    for (int i = 0; i < 50; i++) {
        input += "nine eight ";
        expected += "eight eight nine nine ";
    }
    // Remove trailing space for comparison
    expected = expected.substr(0, expected.length() - 1);
    // Also need to sort the input - actually the expected should be properly sorted
    // Recompute expected properly
    expected = "";
    for (int i = 0; i < 50; i++) {
        expected += "eight eight nine nine ";
    }
    expected = expected.substr(0, expected.length() - 1);
    
    // Remove trailing space from input
    input = input.substr(0, input.length() - 1);
    EXPECT_EQ(sort_numbers(input), expected);
}

// Test with maximum possible numbers (10 of each)
TEST_F(SortNumbersTest, TenOfEachNumber) {
    std::string input;
    std::string expected;
    
    // Build input: ten of each number in random order
    for (int i = 0; i < 10; i++) {
        input += "nine eight seven six five four three two one zero ";
    }
    
    // Build expected: all numbers sorted
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j <= 9; j++) {
            switch(j) {
                case 0: expected += "zero "; break;
                case 1: expected += "one "; break;
                case 2: expected += "two "; break;
                case 3: expected += "three "; break;
                case 4: expected += "four "; break;
                case 5: expected += "five "; break;
                case 6: expected += "six "; break;
                case 7: expected += "seven "; break;
                case 8: expected += "eight "; break;
                case 9: expected += "nine "; break;
            }
        }
    }
    
    // Remove trailing space
    input = input.substr(0, input.length() - 1);
    expected = expected.substr(0, expected.length() - 1);
    
    EXPECT_EQ(sort_numbers(input), expected);
}

// Test with newline characters (should treat as part of token)
TEST_F(SortNumbersTest, NewlineCharacters) {
    EXPECT_EQ(sort_numbers("one\ntwo three"), "one three two");  // newline becomes part of token
}

// Test with tab characters (should treat as part of token)
TEST_F(SortNumbersTest, TabCharacters) {
    EXPECT_EQ(sort_numbers("one\ttwo three"), "one three two");  // tab becomes part of token
}

// Test with punctuation (should treat as part of token)
TEST_F(SortNumbersTest, PunctuationInTokens) {
    EXPECT_NO_THROW(sort_numbers("one, two three"));
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}