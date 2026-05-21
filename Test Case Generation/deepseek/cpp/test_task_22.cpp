#include <gtest/gtest.h>
#include <vector>
#include <list>
#include <string>
#include <boost/any.hpp>
#include "filter_integers.h" // Assume a função está neste header

using namespace std;

class FilterIntegersTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Teste básico com mistura de tipos
TEST_F(FilterIntegersTest, MixedTypesReturnsOnlyIntegers) {
    list_any values;
    values.push_back(string("a"));
    values.push_back(3.14);
    values.push_back(5);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {5};
    EXPECT_EQ(result, expected);
}

// Teste com múltiplos inteiros e outros tipos
TEST_F(FilterIntegersTest, MultipleIntegersWithOthers) {
    list_any values;
    values.push_back(1);
    values.push_back(2);
    values.push_back(3);
    values.push_back(string("abc"));
    values.push_back(list_any()); // lista vazia
    values.push_back(list_any()); // outra lista vazia
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {1, 2, 3};
    EXPECT_EQ(result, expected);
}

// Teste com lista vazia
TEST_F(FilterIntegersTest, EmptyListReturnsEmptyVector) {
    list_any values;
    
    vector<int> result = filter_integers(values);
    
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result.size(), 0);
}

// Teste com apenas inteiros
TEST_F(FilterIntegersTest, OnlyIntegersReturnsAll) {
    list_any values;
    values.push_back(10);
    values.push_back(20);
    values.push_back(30);
    values.push_back(40);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {10, 20, 30, 40};
    EXPECT_EQ(result, expected);
}

// Teste com apenas não-inteiros
TEST_F(FilterIntegersTest, OnlyNonIntegersReturnsEmpty) {
    list_any values;
    values.push_back(string("hello"));
    values.push_back(3.14159);
    values.push_back(2.71828);
    values.push_back(list_any());
    values.push_back(true);
    
    vector<int> result = filter_integers(values);
    
    EXPECT_TRUE(result.empty());
}

// Teste com tipos variados incluindo booleanos e caracteres
TEST_F(FilterIntegersTest, VariousTypesIncludingBoolAndChar) {
    list_any values;
    values.push_back(42);
    values.push_back(true); // bool pode ser convertido para int, mas typeid(bool) != typeid(int)
    values.push_back('c');  // char também é diferente de int
    values.push_back(100);
    values.push_back(3.14f);
    values.push_back(200);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {42, 100, 200};
    EXPECT_EQ(result, expected);
}

// Teste com inteiros negativos
TEST_F(FilterIntegersTest, NegativeIntegers) {
    list_any values;
    values.push_back(-5);
    values.push_back(0);
    values.push_back(15);
    values.push_back(-42);
    values.push_back(string("test"));
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {-5, 0, 15, -42};
    EXPECT_EQ(result, expected);
}

// Teste com inteiros grandes
TEST_F(FilterIntegersTest, LargeIntegers) {
    list_any values;
    values.push_back(2147483647);  // INT_MAX
    values.push_back(-2147483648); // INT_MIN
    values.push_back(1000000);
    values.push_back(-999999);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {2147483647, -2147483648, 1000000, -999999};
    EXPECT_EQ(result, expected);
}

// Teste com tipos aninhados e estruturas complexas
TEST_F(FilterIntegersTest, ComplexNestedTypes) {
    list_any values;
    list_any nested_list;
    nested_list.push_back(1);
    nested_list.push_back(2);
    
    values.push_back(nested_list);
    values.push_back(100);
    values.push_back(list_any());
    values.push_back(200);
    values.push_back(string("nested"));
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {100, 200};
    EXPECT_EQ(result, expected);
}

// Teste com ordem preservada
TEST_F(FilterIntegersTest, OrderIsPreserved) {
    list_any values;
    values.push_back(5);
    values.push_back(string("skip"));
    values.push_back(3);
    values.push_back(8.5);
    values.push_back(1);
    values.push_back(7);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {5, 3, 1, 7};
    EXPECT_EQ(result, expected);
}

// Teste com inteiros duplicados
TEST_F(FilterIntegersTest, DuplicateIntegers) {
    list_any values;
    values.push_back(42);
    values.push_back(string("test"));
    values.push_back(42);
    values.push_back(3.14);
    values.push_back(42);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {42, 42, 42};
    EXPECT_EQ(result, expected);
}

// Teste com um único inteiro
TEST_F(FilterIntegersTest, SingleInteger) {
    list_any values;
    values.push_back(123);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {123};
    EXPECT_EQ(result, expected);
}

// Teste com um único não-inteiro
TEST_F(FilterIntegersTest, SingleNonInteger) {
    list_any values;
    values.push_back(string("only string"));
    
    vector<int> result = filter_integers(values);
    
    EXPECT_TRUE(result.empty());
}

// Teste com tipos ponteiro (não devem ser incluídos)
TEST_F(FilterIntegersTest, PointerTypesNotIncluded) {
    list_any values;
    int x = 42;
    values.push_back(&x);
    values.push_back(100);
    values.push_back(nullptr);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {100};
    EXPECT_EQ(result, expected);
}

// Teste com valores extremos
TEST_F(FilterIntegersTest, BoundaryValues) {
    list_any values;
    values.push_back(0);
    values.push_back(1);
    values.push_back(-1);
    values.push_back(INT_MAX);
    values.push_back(INT_MIN);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {0, 1, -1, INT_MAX, INT_MIN};
    EXPECT_EQ(result, expected);
}

// Teste com mistura de todos os tipos possíveis
TEST_F(FilterIntegersTest, ComprehensiveTypeMix) {
    list_any values;
    values.push_back(10);
    values.push_back(20.5);
    values.push_back(string("text"));
    values.push_back(30);
    values.push_back(list_any());
    values.push_back(40.0);
    values.push_back(true);
    values.push_back('A');
    values.push_back(nullptr);
    values.push_back(50);
    values.push_back(60.75f);
    
    vector<int> result = filter_integers(values);
    
    vector<int> expected = {10, 30, 50};
    EXPECT_EQ(result, expected);
}

// Teste com lista grande
TEST_F(FilterIntegersTest, LargeListPerformance) {
    list_any values;
    vector<int> expected;
    
    for (int i = 0; i < 1000; ++i) {
        if (i % 2 == 0) {
            values.push_back(i);
            expected.push_back(i);
        } else {
            values.push_back(static_cast<double>(i));
        }
    }
    
    vector<int> result = filter_integers(values);
    
    EXPECT_EQ(result, expected);
    EXPECT_EQ(result.size(), 500);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}