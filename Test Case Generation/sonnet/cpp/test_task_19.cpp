#include <gtest/gtest.h>
#include <string>
#include <map>
using namespace std;

string sort_numbers(string numbers);

TEST(SortNumbersTest, EmptyString) {
    EXPECT_EQ(sort_numbers(""), "");
}

TEST(SortNumbersTest, SingleWordZero) {
    EXPECT_EQ(sort_numbers("zero"), "zero");
}

TEST(SortNumbersTest, SingleWordOne) {
    EXPECT_EQ(sort_numbers("one"), "one");
}

TEST(SortNumbersTest, SingleWordTwo) {
    EXPECT_EQ(sort_numbers("two"), "two");
}

TEST(SortNumbersTest, SingleWordThree) {
    EXPECT_EQ(sort_numbers("three"), "three");
}

TEST(SortNumbersTest, SingleWordFour) {
    EXPECT_EQ(sort_numbers("four"), "four");
}

TEST(SortNumbersTest, SingleWordFive) {
    EXPECT_EQ(sort_numbers("five"), "five");
}

TEST(SortNumbersTest, SingleWordSix) {
    EXPECT_EQ(sort_numbers("six"), "six");
}

TEST(SortNumbersTest, SingleWordSeven) {
    EXPECT_EQ(sort_numbers("seven"), "seven");
}

TEST(SortNumbersTest, SingleWordEight) {
    EXPECT_EQ(sort_numbers("eight"), "eight");
}

TEST(SortNumbersTest, SingleWordNine) {
    EXPECT_EQ(sort_numbers("nine"), "nine");
}

TEST(SortNumbersTest, AlreadySortedTwoWords) {
    EXPECT_EQ(sort_numbers("one five"), "one five");
}

TEST(SortNumbersTest, ReverseSortedTwoWords) {
    EXPECT_EQ(sort_numbers("five one"), "one five");
}

TEST(SortNumbersTest, ExampleFromDocstring) {
    EXPECT_EQ(sort_numbers("three one five"), "one three five");
}

TEST(SortNumbersTest, AllNumbersAscending) {
    EXPECT_EQ(sort_numbers("zero one two three four five six seven eight nine"),
              "zero one two three four five six seven eight nine");
}

TEST(SortNumbersTest, AllNumbersDescending) {
    EXPECT_EQ(sort_numbers("nine eight seven six five four three two one zero"),
              "zero one two three four five six seven eight nine");
}

TEST(SortNumbersTest, DuplicateNumbers) {
    EXPECT_EQ(sort_numbers("three three one"), "one three three");
}

TEST(SortNumbersTest, AllSameNumber) {
    EXPECT_EQ(sort_numbers("five five five"), "five five five");
}

TEST(SortNumbersTest, DuplicatesOfMultipleNumbers) {
    EXPECT_EQ(sort_numbers("two two one one zero zero"), "zero zero one one two two");
}

TEST(SortNumbersTest, ManyDuplicatesOfZero) {
    EXPECT_EQ(sort_numbers("zero zero zero"), "zero zero zero");
}

TEST(SortNumbersTest, ManyDuplicatesOfNine) {
    EXPECT_EQ(sort_numbers("nine nine nine"), "nine nine nine");
}

TEST(SortNumbersTest, TwoElementsEqual) {
    EXPECT_EQ(sort_numbers("six six"), "six six");
}

TEST(SortNumbersTest, MixedWithZeroAndNine) {
    EXPECT_EQ(sort_numbers("nine zero"), "zero nine");
}

TEST(SortNumbersTest, LargerUnsortedSet) {
    EXPECT_EQ(sort_numbers("six two four eight zero"), "zero two four six eight");
}

TEST(SortNumbersTest, RepeatedAllNumbers) {
    EXPECT_EQ(sort_numbers("nine zero eight one seven two six three five four"),
              "zero one two three four five six seven eight nine");
}

TEST(SortNumbersTest, OnlyZeros) {
    EXPECT_EQ(sort_numbers("zero zero zero zero zero"), "zero zero zero zero zero");
}

TEST(SortNumbersTest, OnlyNines) {
    EXPECT_EQ(sort_numbers("nine nine nine nine"), "nine nine nine nine");
}

TEST(SortNumbersTest, TwoExtremes) {
    EXPECT_EQ(sort_numbers("nine zero nine zero"), "zero zero nine nine");
}

TEST(SortNumbersTest, SingleZero) {
    EXPECT_EQ(sort_numbers("zero"), "zero");
}

TEST(SortNumbersTest, SingleNine) {
    EXPECT_EQ(sort_numbers("nine"), "nine");
}

TEST(SortNumbersTest, NoTrailingSpace) {
    string result = sort_numbers("one two three");
    EXPECT_NE(result.back(), ' ');
}

TEST(SortNumbersTest, NoLeadingSpace) {
    string result = sort_numbers("one two three");
    EXPECT_NE(result.front(), ' ');
}

TEST(SortNumbersTest, ResultHasCorrectWordCount) {
    string result = sort_numbers("three one five");
    int spaces = 0;
    for (char c : result) if (c == ' ') spaces++;
    EXPECT_EQ(spaces, 2);
}

TEST(SortNumbersTest, SortFiveElements) {
    EXPECT_EQ(sort_numbers("five four three two one"), "one two three four five");
}

TEST(SortNumbersTest, SortWithMiddleElement) {
    EXPECT_EQ(sort_numbers("nine five zero"), "zero five nine");
}

TEST(SortNumbersTest, AllOddWords) {
    EXPECT_EQ(sort_numbers("nine seven five three one"), "one three five seven nine");
}

TEST(SortNumbersTest, AllEvenWords) {
    EXPECT_EQ(sort_numbers("eight six four two zero"), "zero two four six eight");
}

TEST(SortNumbersTest, MixedDuplicatesAndUniques) {
    EXPECT_EQ(sort_numbers("one two one three two one"), "one one one two two three");
}

TEST(SortNumbersTest, TenDifferentNumbersRandomOrder) {
    EXPECT_EQ(sort_numbers("four seven one nine zero six three eight two five"),
              "zero one two three four five six seven eight nine");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}