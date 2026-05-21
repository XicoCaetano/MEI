#include <gtest/gtest.h>
#include <vector>
#include <string>

using namespace std;

// Função original para teste
vector<string> filter_by_prefix(vector<string> strings, string prefix) {
    vector<string> out = {};
    for (int i = 0; i < strings.size(); i++) {
        // Nota: substr lança out_of_range se pos > size. 
        // No entanto, se o prefixo for maior que a string, substr(0, len) em C++ 
        // não lida automaticamente com isso sem validação de tamanho.
        // O teste abaixo cobre o comportamento atual da implementação fornecida.
        if (strings[i].length() >= prefix.length()) {
            if (strings[i].substr(0, prefix.length()) == prefix) out.push_back(strings[i]);
        }
    }
    return out;
}

// Suite de Testes Unitários
class FilterByPrefixTest : public ::testing::Test {};

// Testa entrada vazia
TEST_F(FilterByPrefixTest, HandlesEmptyInputVector) {
    vector<string> input = {};
    vector<string> expected = {};
    EXPECT_EQ(filter_by_prefix(input, "a"), expected);
}

// Testa prefixo vazio (deve retornar todas as strings pois substr(0,0) == "")
TEST_F(FilterByPrefixTest, HandlesEmptyPrefix) {
    vector<string> input = {"abc", "def"};
    vector<string> expected = {"abc", "def"};
    EXPECT_EQ(filter_by_prefix(input, ""), expected);
}

// Testa comportamento padrão (exemplo do docstring)
TEST_F(FilterByPrefixTest, FiltersCorrectlyWithStandardInput) {
    vector<string> input = {"abc", "bcd", "cde", "array"};
    string prefix = "a";
    vector<string> expected = {"abc", "array"};
    EXPECT_EQ(filter_by_prefix(input, prefix), expected);
}

// Testa quando nenhuma string corresponde ao prefixo
TEST_F(FilterByPrefixTest, ReturnsEmptyWhenNoMatches) {
    vector<string> input = {"apple", "banana", "cherry"};
    vector<string> expected = {};
    EXPECT_EQ(filter_by_prefix(input, "z"), expected);
}

// Testa sensibilidade a maiúsculas/minúsculas (Case Sensitivity)
TEST_F(FilterByPrefixTest, IsCaseSensitive) {
    vector<string> input = {"Apple", "apple", "APPLE"};
    vector<string> expected = {"Apple"};
    EXPECT_EQ(filter_by_prefix(input, "Ap"), expected);
}

// Testa strings que são mais curtas que o prefixo (Edge Case de Segurança)
TEST_F(FilterByPrefixTest, HandlesStringsShorterThanPrefix) {
    vector<string> input = {"a", "ab", "abc"};
    string prefix = "abcd";
    vector<string> expected = {};
    // A implementação usa substr(0, prefix.length()). 
    // Se a string for menor que o prefixo, o comportamento padrão do C++ lançaria std::out_of_range.
    // Este teste garante que a lógica lida com comprimentos de string.
    EXPECT_EQ(filter_by_prefix(input, prefix), expected);
}

// Testa correspondência exata
TEST_F(FilterByPrefixTest, HandlesExactMatch) {
    vector<string> input = {"prefix"};
    vector<string> expected = {"prefix"};
    EXPECT_EQ(filter_by_prefix(input, "prefix"), expected);
}

// Testa caracteres especiais e espaços
TEST_F(FilterByPrefixTest, HandlesSpecialCharactersAndSpaces) {
    vector<string> input = {" 123", "!#$", " 456"};
    vector<string> expected = {" 123", " 456"};
    EXPECT_EQ(filter_by_prefix(input, " "), expected);
}