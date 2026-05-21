#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

// Função a ser testada
vector<string> filter_by_substring(vector<string> strings, string substring) {
    vector<string> out;
    for (int i = 0; i < strings.size(); i++) {
        if (strings[i].find(substring) != strings[i].npos)
            out.push_back(strings[i]);
    }
    return out;
}

// Suite de Testes Unitários
class FilterBySubstringTest : public ::testing::Test {};

TEST_F(FilterBySubstringTest, EmptyInputVectorReturnsEmpty) {
    vector<string> input = {};
    vector<string> expected = {};
    EXPECT_EQ(filter_by_substring(input, "a"), expected);
}

TEST_F(FilterBySubstringTest, NoMatchesReturnsEmpty) {
    vector<string> input = {"abc", "def", "ghi"};
    vector<string> expected = {};
    EXPECT_EQ(filter_by_substring(input, "xyz"), expected);
}

TEST_F(FilterBySubstringTest, AllMatchReturnsFullVector) {
    vector<string> input = {"apple", "banana", "cherry"};
    vector<string> expected = {"apple", "banana", "cherry"};
    EXPECT_EQ(filter_by_substring(input, "a"), expected);
}

TEST_F(FilterBySubstringTest, PartialMatches) {
    vector<string> input = {"abc", "bacd", "cde", "vector"};
    vector<string> expected = {"abc", "bacd", "vector"};
    EXPECT_EQ(filter_by_substring(input, "a"), expected);
}

TEST_F(FilterBySubstringTest, EmptySubstringMatchesEverything) {
    vector<string> input = {"a", "b", "c"};
    vector<string> expected = {"a", "b", "c"};
    EXPECT_EQ(filter_by_substring(input, ""), expected);
}

TEST_F(FilterBySubstringTest, CaseSensitivity) {
    vector<string> input = {"Apple", "apple", "APPLE"};
    vector<string> expected = {"apple"};
    EXPECT_EQ(filter_by_substring(input, "ap"), expected);
}

TEST_F(FilterBySubstringTest, SubstringIsFullString) {
    vector<string> input = {"test", "testing", "tester"};
    vector<string> expected = {"test", "testing", "tester"};
    EXPECT_EQ(filter_by_substring(input, "test"), expected);
}

TEST_F(FilterBySubstringTest, SpecialCharactersAndSpaces) {
    vector<string> input = {"hello world", "c++20", "!@#$", " "};
    vector<string> expected = {"hello world", " "};
    EXPECT_EQ(filter_by_substring(input, " "), expected);
}

TEST_F(FilterBySubstringTest, LargeStrings) {
    string large(1000, 'z');
    vector<string> input = {large, "short", large + "suffix"};
    vector<string> expected = {large, large + "suffix"};
    EXPECT_EQ(filter_by_substring(input, "zzz"), expected);
}