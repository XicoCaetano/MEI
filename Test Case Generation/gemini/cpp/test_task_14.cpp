#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

// Função original para teste
vector<string> all_prefixes(string str) {
    vector<string> out;
    string current = "";
    for (int i = 0; i < str.length(); i++) {
        current = current + str[i];
        out.push_back(current);
    }
    return out;
}

// Suite de Testes Unitários
class AllPrefixesTest : public ::testing::Test {};

// Teste de caso padrão conforme exemplo fornecido
TEST_F(AllPrefixesTest, StandardInput) {
    string input = "abc";
    vector<string> expected = {"a", "ab", "abc"};
    EXPECT_EQ(all_prefixes(input), expected);
}

// Teste com string vazia (Edge Case: 0 iterações no loop)
TEST_F(AllPrefixesTest, EmptyString) {
    string input = "";
    vector<string> expected = {};
    EXPECT_EQ(all_prefixes(input), expected);
}

// Teste com um único caractere
TEST_F(AllPrefixesTest, SingleCharacter) {
    string input = "z";
    vector<string> expected = {"z"};
    EXPECT_EQ(all_prefixes(input), expected);
}

// Teste com caracteres especiais e espaços
TEST_F(AllPrefixesTest, SpecialCharactersAndSpaces) {
    string input = "a b!";
    vector<string> expected = {"a", "a ", "a b", "a b!"};
    EXPECT_EQ(all_prefixes(input), expected);
}

// Teste com caracteres repetidos
TEST_F(AllPrefixesTest, RepeatedCharacters) {
    string input = "aaa";
    vector<string> expected = {"a", "aa", "aaa"};
    EXPECT_EQ(all_prefixes(input), expected);
}

// Teste com string longa para verificar integridade do loop
TEST_F(AllPrefixesTest, LongString) {
    string input = "longstring";
    vector<string> result = all_prefixes(input);
    
    ASSERT_EQ(result.size(), input.length());
    EXPECT_EQ(result.front(), "l");
    EXPECT_EQ(result.back(), "longstring");
    EXPECT_EQ(result[4], "longs");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}