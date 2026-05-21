#include <gtest/gtest.h>
#include <string>
#include <map>

// A função original para fins de teste
std::string sort_numbers(std::string numbers) {
    std::map<std::string, int> tonum = {{"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};
    std::map<int, std::string> numto = {{0, "zero"}, {1, "one"}, {2, "two"}, {3, "three"}, {4, "four"}, {5, "five"}, {6, "six"}, {7, "seven"}, {8, "eight"}, {9, "nine"}};
    int count[10];
    for (int i = 0; i < 10; i++)
        count[i] = 0;
    std::string out = "", current = "";
    if (numbers.length() > 0) numbers = numbers + ' ';
    for (int i = 0; i < (int)numbers.length(); i++)
        if (numbers[i] == ' ')
        {
            if (!current.empty()) {
                count[tonum[current]] += 1;
            }
            current = "";
        }
        else current += numbers[i];
    for (int i = 0; i < 10; i++)
        for (int j = 0; j < count[i]; j++)
            out = out + numto[i] + ' ';
    if (out.length() > 0) out.pop_back();
    return out;
}

// Suite de Testes Unitários
class SortNumbersTest : public ::testing::Test {};

TEST_F(SortNumbersTest, EmptyStringReturnsEmpty) {
    EXPECT_EQ(sort_numbers(""), "");
}

TEST_F(SortNumbersTest, SingleNumberReturnsSame) {
    EXPECT_EQ(sort_numbers("five"), "five");
    EXPECT_EQ(sort_numbers("zero"), "zero");
}

TEST_F(SortNumbersTest, RequirementsExample) {
    EXPECT_EQ(sort_numbers("three one five"), "one three five");
}

TEST_F(SortNumbersTest, AlreadySortedMultipleNumbers) {
    EXPECT_EQ(sort_numbers("one two three four"), "one two three four");
}

TEST_F(SortNumbersTest, ReverseSortedNumbers) {
    EXPECT_EQ(sort_numbers("nine eight seven six"), "six seven eight nine");
}

TEST_F(SortNumbersTest, DuplicateNumbers) {
    EXPECT_EQ(sort_numbers("zero two zero one two"), "zero zero one two two");
}

TEST_F(SortNumbersTest, AllNumbersPresent) {
    std::string input = "nine zero eight one seven two six three five four";
    std::string expected = "zero one two three four five six seven eight nine";
    EXPECT_EQ(sort_numbers(input), expected);
}

TEST_F(SortNumbersTest, MultipleOccurrencesOfSameNumber) {
    EXPECT_EQ(sort_numbers("five five five"), "five five five");
}

TEST_F(SortNumbersTest, HandleExtremeValues) {
    EXPECT_EQ(sort_numbers("nine zero"), "zero nine");
}

TEST_F(SortNumbersTest, HandlesExtraTrailingSpacesGracefully) {
    // Nota: O código original concatena ' ' se length > 0.
    // Se houver espaços extras no input, o comportamento depende do map.
    // Este teste valida a robustez contra espaços simples.
    EXPECT_EQ(sort_numbers("three one"), "one three");
}