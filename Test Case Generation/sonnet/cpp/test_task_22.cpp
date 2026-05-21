#include <gtest/gtest.h>
#include <boost/any.hpp>
#include <list>
#include <vector>
#include <string>

typedef std::list<boost::any> list_any;

std::vector<int> filter_integers(list_any values);

// Basic functionality
TEST(FilterIntegersTest, SingleInteger) {
    list_any input = {5};
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 5);
}

TEST(FilterIntegersTest, MultipleIntegers) {
    list_any input = {1, 2, 3};
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

TEST(FilterIntegersTest, MixedWithString) {
    list_any input;
    input.push_back(std::string("a"));
    input.push_back(3.14);
    input.push_back(5);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 5);
}

TEST(FilterIntegersTest, MixedIntegersAndStrings) {
    list_any input;
    input.push_back(1);
    input.push_back(2);
    input.push_back(3);
    input.push_back(std::string("abc"));
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 2);
    EXPECT_EQ(result[2], 3);
}

// Edge cases: empty input
TEST(FilterIntegersTest, EmptyList) {
    list_any input;
    std::vector<int> result = filter_integers(input);
    EXPECT_TRUE(result.empty());
}

// Edge cases: no integers
TEST(FilterIntegersTest, NoIntegers_OnlyStrings) {
    list_any input;
    input.push_back(std::string("hello"));
    input.push_back(std::string("world"));
    std::vector<int> result = filter_integers(input);
    EXPECT_TRUE(result.empty());
}

TEST(FilterIntegersTest, NoIntegers_OnlyDoubles) {
    list_any input = {1.1, 2.2, 3.3};
    std::vector<int> result = filter_integers(input);
    EXPECT_TRUE(result.empty());
}

TEST(FilterIntegersTest, NoIntegers_OnlyFloats) {
    list_any input;
    input.push_back(1.0f);
    input.push_back(2.5f);
    std::vector<int> result = filter_integers(input);
    EXPECT_TRUE(result.empty());
}

// Type discrimination: doubles that look like integers must not be included
TEST(FilterIntegersTest, DoubleNotInt) {
    list_any input;
    input.push_back(1.0);   // double, not int
    input.push_back(2);     // int
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 2);
}

// Type discrimination: float not included
TEST(FilterIntegersTest, FloatNotInt) {
    list_any input;
    input.push_back(3.0f);
    input.push_back(7);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 7);
}

// Type discrimination: long/short/char not included
TEST(FilterIntegersTest, LongNotInt) {
    list_any input;
    input.push_back(100L);
    input.push_back(42);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 42);
}

TEST(FilterIntegersTest, ShortNotInt) {
    list_any input;
    input.push_back((short)10);
    input.push_back(99);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 99);
}

TEST(FilterIntegersTest, CharNotInt) {
    list_any input;
    input.push_back('A');
    input.push_back(3);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 3);
}

TEST(FilterIntegersTest, UnsignedIntNotInt) {
    list_any input;
    input.push_back((unsigned int)5u);
    input.push_back(10);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 10);
}

// Edge cases: negative integers
TEST(FilterIntegersTest, NegativeIntegers) {
    list_any input = {-1, -100, -9999};
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], -1);
    EXPECT_EQ(result[1], -100);
    EXPECT_EQ(result[2], -9999);
}

// Edge cases: zero
TEST(FilterIntegersTest, ZeroIsInteger) {
    list_any input = {0};
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 0);
}

// Edge cases: boundary values
TEST(FilterIntegersTest, MaxInt) {
    list_any input;
    input.push_back(std::numeric_limits<int>::max());
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], std::numeric_limits<int>::max());
}

TEST(FilterIntegersTest, MinInt) {
    list_any input;
    input.push_back(std::numeric_limits<int>::min());
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], std::numeric_limits<int>::min());
}

// Order preservation
TEST(FilterIntegersTest, OrderPreserved) {
    list_any input;
    input.push_back(std::string("x"));
    input.push_back(10);
    input.push_back(3.14);
    input.push_back(20);
    input.push_back(std::string("y"));
    input.push_back(30);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 3u);
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 20);
    EXPECT_EQ(result[2], 30);
}

// Large list
TEST(FilterIntegersTest, LargeListMixed) {
    list_any input;
    for (int i = 0; i < 1000; ++i) {
        input.push_back(i);
        input.push_back(std::string("str"));
        input.push_back(3.14);
    }
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1000u);
    for (int i = 0; i < 1000; ++i) {
        EXPECT_EQ(result[i], i);
    }
}

// Boolean: in C++ bool is not int (typeid differs)
TEST(FilterIntegersTest, BoolNotInt) {
    list_any input;
    input.push_back(true);
    input.push_back(false);
    input.push_back(1);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 1);
}

// List inside list_any (nested)
TEST(FilterIntegersTest, NestedListNotInt) {
    list_any inner;
    inner.push_back(1);
    list_any input;
    input.push_back(inner);
    input.push_back(5);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 5);
}

// Only one integer among many non-integers
TEST(FilterIntegersTest, OneIntegerAmongMany) {
    list_any input;
    input.push_back(std::string("foo"));
    input.push_back(9.99);
    input.push_back(42);
    input.push_back(std::string("bar"));
    input.push_back(1.0f);
    std::vector<int> result = filter_integers(input);
    ASSERT_EQ(result.size(), 1u);
    EXPECT_EQ(result[0], 42);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}