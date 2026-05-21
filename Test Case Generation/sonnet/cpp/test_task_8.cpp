#include <gtest/gtest.h>
#include <vector>
using namespace std;

vector<int> sum_product(vector<int> numbers){
    int sum=0,product=1;
    for (int i=0;i<numbers.size();i++)
    {
        sum+=numbers[i];
        product*=numbers[i];
    }
    return {sum,product};
}

TEST(SumProductTest, EmptyVector) {
    vector<int> result = sum_product({});
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
}

TEST(SumProductTest, SingleElement) {
    vector<int> result = sum_product({5});
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 5);
}

TEST(SumProductTest, SingleElementOne) {
    vector<int> result = sum_product({1});
    EXPECT_EQ(result[0], 1);
    EXPECT_EQ(result[1], 1);
}

TEST(SumProductTest, SingleElementZero) {
    vector<int> result = sum_product({0});
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
}

TEST(SumProductTest, MultiplePositiveIntegers) {
    vector<int> result = sum_product({1, 2, 3, 4});
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 24);
}

TEST(SumProductTest, NegativeIntegers) {
    vector<int> result = sum_product({-1, -2, -3});
    EXPECT_EQ(result[0], -6);
    EXPECT_EQ(result[1], -6);
}

TEST(SumProductTest, MixedPositiveAndNegative) {
    vector<int> result = sum_product({-1, 2, -3, 4});
    EXPECT_EQ(result[0], 2);
    EXPECT_EQ(result[1], 24);
}

TEST(SumProductTest, ContainsZero) {
    vector<int> result = sum_product({1, 2, 0, 4});
    EXPECT_EQ(result[0], 7);
    EXPECT_EQ(result[1], 0);
}

TEST(SumProductTest, AllZeros) {
    vector<int> result = sum_product({0, 0, 0});
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 0);
}

TEST(SumProductTest, TwoElements) {
    vector<int> result = sum_product({3, 7});
    EXPECT_EQ(result[0], 10);
    EXPECT_EQ(result[1], 21);
}

TEST(SumProductTest, ResultSizeIsAlwaysTwo) {
    vector<int> result = sum_product({});
    EXPECT_EQ(result.size(), 2);

    result = sum_product({1, 2, 3});
    EXPECT_EQ(result.size(), 2);
}

TEST(SumProductTest, LargeValues) {
    vector<int> result = sum_product({100, 200, 300});
    EXPECT_EQ(result[0], 600);
    EXPECT_EQ(result[1], 6000000);
}

TEST(SumProductTest, AllOnes) {
    vector<int> result = sum_product({1, 1, 1, 1, 1});
    EXPECT_EQ(result[0], 5);
    EXPECT_EQ(result[1], 1);
}

TEST(SumProductTest, EvenNumberOfNegatives) {
    vector<int> result = sum_product({-2, -3});
    EXPECT_EQ(result[0], -5);
    EXPECT_EQ(result[1], 6);
}

TEST(SumProductTest, OddNumberOfNegatives) {
    vector<int> result = sum_product({-2, -3, -4});
    EXPECT_EQ(result[0], -9);
    EXPECT_EQ(result[1], -24);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}