#include <gtest/gtest.h>
#include <vector>

using namespace std;

// Função original integrada para garantir a compilação nos testes
vector<int> intersperse(vector<int> numbers, int delimeter) { 
    vector<int> out = {};
    if (numbers.size() > 0) out.push_back(numbers[0]);
    for (int i = 1; i < (int)numbers.size(); i++) {
        out.push_back(delimeter);
        out.push_back(numbers[i]);
    }
    return out;
}

// Teste para vetor vazio (Edge Case: size == 0)
TEST(IntersperseTest, EmptyVector) {
    vector<int> input = {};
    vector<int> expected = {};
    EXPECT_EQ(intersperse(input, 4), expected);
}

// Teste para vetor com um único elemento (Edge Case: loop não deve executar)
TEST(IntersperseTest, SingleElement) {
    vector<int> input = {1};
    vector<int> expected = {1};
    EXPECT_EQ(intersperse(input, 4), expected);
}

// Teste para vetor com múltiplos elementos (Caminho feliz / Line coverage do loop)
TEST(IntersperseTest, MultipleElements) {
    vector<int> input = {1, 2, 3};
    vector<int> expected = {1, 4, 2, 4, 3};
    EXPECT_EQ(intersperse(input, 4), expected);
}

// Teste com o delimitador sendo zero ou negativo
TEST(IntersperseTest, ZeroAndNegativeDelimeter) {
    vector<int> input = {5, 5};
    vector<int> expected_zero = {5, 0, 5};
    vector<int> expected_neg = {5, -1, 5};
    
    EXPECT_EQ(intersperse(input, 0), expected_zero);
    EXPECT_EQ(intersperse(input, -1), expected_neg);
}

// Teste com elementos repetidos no input
TEST(IntersperseTest, RepeatedElements) {
    vector<int> input = {1, 1, 1};
    vector<int> expected = {1, 2, 1, 2, 1};
    EXPECT_EQ(intersperse(input, 2), expected);
}

// Teste de integridade de grandes valores
TEST(IntersperseTest, LargeValues) {
    vector<int> input = {2147483647, 2147483647};
    vector<int> expected = {2147483647, 100, 2147483647};
    EXPECT_EQ(intersperse(input, 100), expected);
}