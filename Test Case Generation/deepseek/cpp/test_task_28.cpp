#include <gtest/gtest.h>
#include <vector>
#include <string>
#include "concatenate.h" // Assuming the function is declared here

using namespace std;

// Test fixture for concatenate function
class ConcatenateTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test empty vector
TEST_F(ConcatenateTest, EmptyVectorReturnsEmptyString) {
    vector<string> empty;
    EXPECT_EQ(concatenate(empty), "");
}

// Test vector with single string
TEST_F(ConcatenateTest, SingleStringReturnsSameString) {
    vector<string> single = {"hello"};
    EXPECT_EQ(concatenate(single), "hello");
}

// Test vector with multiple strings
TEST_F(ConcatenateTest, MultipleStringsConcatenated) {
    vector<string> multiple = {"a", "b", "c"};
    EXPECT_EQ(concatenate(multiple), "abc");
}

// Test vector with empty strings
TEST_F(ConcatenateTest, EmptyStringsInVector) {
    vector<string> withEmpty = {"", "test", ""};
    EXPECT_EQ(concatenate(withEmpty), "test");
}

// Test vector with long strings
TEST_F(ConcatenateTest, LongStrings) {
    vector<string> longStrings = {"This is a long string. ", "This is another long string."};
    EXPECT_EQ(concatenate(longStrings), "This is a long string. This is another long string.");
}

// Test vector with whitespace strings
TEST_F(ConcatenateTest, WhitespaceStrings) {
    vector<string> whitespace = {"   ", " \t ", "\n"};
    EXPECT_EQ(concatenate(whitespace), "    \t \n");
}

// Test vector with special characters
TEST_F(ConcatenateTest, SpecialCharacters) {
    vector<string> special = {"!@#$", "%^&*", "()_+"};
    EXPECT_EQ(concatenate(special), "!@#$%^&*()_+");
}

// Test vector with numeric string characters
TEST_F(ConcatenateTest, NumericStrings) {
    vector<string> numeric = {"123", "456", "789"};
    EXPECT_EQ(concatenate(numeric), "123456789");
}

// Test large number of strings
TEST_F(ConcatenateTest, ManyStrings) {
    vector<string> many;
    for (int i = 0; i < 1000; ++i) {
        many.push_back("x");
    }
    string expected(1000, 'x');
    EXPECT_EQ(concatenate(many), expected);
}

// Test vector with strings that contain null characters
TEST_F(ConcatenateTest, NullCharactersInStrings) {
    vector<string> withNull = {string("abc\0def", 7), string("ghi\0jkl", 7)};
    string expected = string("abc\0defghi\0jkl", 14);
    EXPECT_EQ(concatenate(withNull), expected);
}

// Test empty strings at different positions
TEST_F(ConcatenateTest, EmptyStringsAtBeginningMiddleEnd) {
    vector<string> emptyPositions = {"", "first", "", "second", ""};
    EXPECT_EQ(concatenate(emptyPositions), "firstsecond");
}

// Test vector with one very large string
TEST_F(ConcatenateTest, VeryLargeString) {
    string largeString(10000, 'A');
    vector<string> singleLarge = {largeString};
    EXPECT_EQ(concatenate(singleLarge), largeString);
}

// Test boundary case: size_t maximum? (practical limit - large vector)
TEST_F(ConcatenateTest, LargeVectorSize) {
    vector<string> largeVec;
    int numElements = 10000;
    for (int i = 0; i < numElements; ++i) {
        largeVec.push_back("x");
    }
    string expected(numElements, 'x');
    EXPECT_EQ(concatenate(largeVec), expected);
}