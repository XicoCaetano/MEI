#include <gtest/gtest.h>
#include <vector>
#include <string>

// Protótipo da função a testar
std::vector<int> parse_music(std::string music_string);

// Teste para garantir que uma string vazia retorna um vetor vazio
TEST(ParseMusicTest, HandlesEmptyInput) {
    std::string input = "";
    std::vector<int> expected = {};
    EXPECT_EQ(parse_music(input), expected);
}

// Teste do exemplo fornecido na documentação
TEST(ParseMusicTest, HandlesStandardInput) {
    std::string input = "o o| .| o| o| .| .| .| .| o o";
    std::vector<int> expected = {4, 2, 1, 2, 2, 1, 1, 1, 1, 4, 4};
    EXPECT_EQ(parse_music(input), expected);
}

// Teste individual para cada tipo de nota
TEST(ParseMusicTest, HandlesIndividualNotes) {
    EXPECT_EQ(parse_music("o"), std::vector<int>{4});
    EXPECT_EQ(parse_music("o|"), std::vector<int>{2});
    EXPECT_EQ(parse_music(".|"), std::vector<int>{1});
}

// Teste com múltiplas instâncias da mesma nota
TEST(ParseMusicTest, HandlesRepeatedNotes) {
    std::string input = "o o o";
    std::vector<int> expected = {4, 4, 4};
    EXPECT_EQ(parse_music(input), expected);
}

// Teste com espaços extras (conforme a lógica da função, espaços duplos resultam em 'current' vazio)
TEST(ParseMusicTest, HandlesExtraSpaces) {
    std::string input = "o  o|"; 
    std::vector<int> expected = {4, 2};
    EXPECT_EQ(parse_music(input), expected);
}

// Teste com caracteres inválidos ou formatos não reconhecidos (deve ignorar e não adicionar ao vetor)
TEST(ParseMusicTest, HandlesInvalidNotes) {
    std::string input = "o invalid .| x o|";
    std::vector<int> expected = {4, 1, 2};
    EXPECT_EQ(parse_music(input), expected);
}

// Teste de cobertura de fluxo: string com apenas espaços
TEST(ParseMusicTest, HandlesOnlySpaces) {
    std::string input = "   ";
    std::vector<int> expected = {};
    EXPECT_EQ(parse_music(input), expected);
}

// Teste para garantir que notas sem espaço no final são processadas (Branch Coverage do loop final)
TEST(ParseMusicTest, HandlesNoTrailingSpace) {
    std::string input = "o| .| o";
    std::vector<int> expected = {2, 1, 4};
    EXPECT_EQ(parse_music(input), expected);
}