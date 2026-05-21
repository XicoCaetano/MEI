#include <gtest/gtest.h>
#include <vector>
using namespace std;

vector<int> factorize(int n){
    vector<int> out={};
    for (int i=2;i*i<=n;i++)
        if (n%i==0)
        {
            n=n/i;
            out.push_back(i);
            i-=1;
        }
    out.push_back(n);
    return out;
}

TEST(FactorizeTest, SmallPrime2) {
    EXPECT_EQ(factorize(2), vector<int>({2}));
}

TEST(FactorizeTest, SmallPrime3) {
    EXPECT_EQ(factorize(3), vector<int>({3}));
}

TEST(FactorizeTest, SmallPrime5) {
    EXPECT_EQ(factorize(5), vector<int>({5}));
}

TEST(FactorizeTest, SmallPrime7) {
    EXPECT_EQ(factorize(7), vector<int>({7}));
}

TEST(FactorizeTest, SmallPrime11) {
    EXPECT_EQ(factorize(11), vector<int>({11}));
}

TEST(FactorizeTest, SmallPrime13) {
    EXPECT_EQ(factorize(13), vector<int>({13}));
}

TEST(FactorizeTest, PowerOf2_4) {
    EXPECT_EQ(factorize(4), (vector<int>{2, 2}));
}

TEST(FactorizeTest, PowerOf2_8) {
    EXPECT_EQ(factorize(8), (vector<int>{2, 2, 2}));
}

TEST(FactorizeTest, PowerOf2_16) {
    EXPECT_EQ(factorize(16), (vector<int>{2, 2, 2, 2}));
}

TEST(FactorizeTest, PowerOf2_32) {
    EXPECT_EQ(factorize(32), (vector<int>{2, 2, 2, 2, 2}));
}

TEST(FactorizeTest, PowerOf3_9) {
    EXPECT_EQ(factorize(9), (vector<int>{3, 3}));
}

TEST(FactorizeTest, PowerOf3_27) {
    EXPECT_EQ(factorize(27), (vector<int>{3, 3, 3}));
}

TEST(FactorizeTest, PerfectSquare25) {
    EXPECT_EQ(factorize(25), (vector<int>{5, 5}));
}

TEST(FactorizeTest, PerfectSquare49) {
    EXPECT_EQ(factorize(49), (vector<int>{7, 7}));
}

TEST(FactorizeTest, PerfectSquare121) {
    EXPECT_EQ(factorize(121), (vector<int>{11, 11}));
}

TEST(FactorizeTest, TwoDistinctPrimes_6) {
    EXPECT_EQ(factorize(6), (vector<int>{2, 3}));
}

TEST(FactorizeTest, TwoDistinctPrimes_10) {
    EXPECT_EQ(factorize(10), (vector<int>{2, 5}));
}

TEST(FactorizeTest, TwoDistinctPrimes_14) {
    EXPECT_EQ(factorize(14), (vector<int>{2, 7}));
}

TEST(FactorizeTest, TwoDistinctPrimes_15) {
    EXPECT_EQ(factorize(15), (vector<int>{3, 5}));
}

TEST(FactorizeTest, TwoDistinctPrimes_21) {
    EXPECT_EQ(factorize(21), (vector<int>{3, 7}));
}

TEST(FactorizeTest, TwoDistinctPrimes_35) {
    EXPECT_EQ(factorize(35), (vector<int>{5, 7}));
}

TEST(FactorizeTest, ThreeDistinctPrimes_30) {
    EXPECT_EQ(factorize(30), (vector<int>{2, 3, 5}));
}

TEST(FactorizeTest, ThreeDistinctPrimes_42) {
    EXPECT_EQ(factorize(42), (vector<int>{2, 3, 7}));
}

TEST(FactorizeTest, ThreeDistinctPrimes_70) {
    EXPECT_EQ(factorize(70), (vector<int>{2, 5, 7}));
}

TEST(FactorizeTest, ThreeDistinctPrimes_105) {
    EXPECT_EQ(factorize(105), (vector<int>{3, 5, 7}));
}

TEST(FactorizeTest, MixedFactors_12) {
    EXPECT_EQ(factorize(12), (vector<int>{2, 2, 3}));
}

TEST(FactorizeTest, MixedFactors_18) {
    EXPECT_EQ(factorize(18), (vector<int>{2, 3, 3}));
}

TEST(FactorizeTest, MixedFactors_20) {
    EXPECT_EQ(factorize(20), (vector<int>{2, 2, 5}));
}

TEST(FactorizeTest, MixedFactors_24) {
    EXPECT_EQ(factorize(24), (vector<int>{2, 2, 2, 3}));
}

TEST(FactorizeTest, MixedFactors_36) {
    EXPECT_EQ(factorize(36), (vector<int>{2, 2, 3, 3}));
}

TEST(FactorizeTest, MixedFactors_45) {
    EXPECT_EQ(factorize(45), (vector<int>{3, 3, 5}));
}

TEST(FactorizeTest, MixedFactors_48) {
    EXPECT_EQ(factorize(48), (vector<int>{2, 2, 2, 2, 3}));
}

TEST(FactorizeTest, MixedFactors_60) {
    EXPECT_EQ(factorize(60), (vector<int>{2, 2, 3, 5}));
}

TEST(FactorizeTest, MixedFactors_72) {
    EXPECT_EQ(factorize(72), (vector<int>{2, 2, 2, 3, 3}));
}

TEST(FactorizeTest, MixedFactors_100) {
    EXPECT_EQ(factorize(100), (vector<int>{2, 2, 5, 5}));
}

TEST(FactorizeTest, LargePrime_97) {
    EXPECT_EQ(factorize(97), (vector<int>{97}));
}

TEST(FactorizeTest, LargePrime_101) {
    EXPECT_EQ(factorize(101), (vector<int>{101}));
}

TEST(FactorizeTest, LargePrime_199) {
    EXPECT_EQ(factorize(199), (vector<int>{199}));
}

TEST(FactorizeTest, LargePrime_997) {
    EXPECT_EQ(factorize(997), (vector<int>{997}));
}

TEST(FactorizeTest, LargeComposite_1000) {
    EXPECT_EQ(factorize(1000), (vector<int>{2, 2, 2, 5, 5, 5}));
}

TEST(FactorizeTest, LargeComposite_1024) {
    EXPECT_EQ(factorize(1024), (vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
}

TEST(FactorizeTest, LargeComposite_2310) {
    // 2 * 3 * 5 * 7 * 11
    EXPECT_EQ(factorize(2310), (vector<int>{2, 3, 5, 7, 11}));
}

TEST(FactorizeTest, LargeComposite_9999) {
    // 3 * 3 * 11 * 101
    EXPECT_EQ(factorize(9999), (vector<int>{3, 3, 11, 101}));
}

TEST(FactorizeTest, LargeComposite_10000) {
    // 2^4 * 5^4
    EXPECT_EQ(factorize(10000), (vector<int>{2, 2, 2, 2, 5, 5, 5, 5}));
}

TEST(FactorizeTest, ProductEqualsInput_8) {
    vector<int> factors = factorize(8);
    int product = 1;
    for (int f : factors) product *= f;
    EXPECT_EQ(product, 8);
}

TEST(FactorizeTest, ProductEqualsInput_70) {
    vector<int> factors = factorize(70);
    int product = 1;
    for (int f : factors) product *= f;
    EXPECT_EQ(product, 70);
}

TEST(FactorizeTest, ProductEqualsInput_9999) {
    vector<int> factors = factorize(9999);
    int product = 1;
    for (int f : factors) product *= f;
    EXPECT_EQ(product, 9999);
}

TEST(FactorizeTest, ProductEqualsInput_LargePrime_997) {
    vector<int> factors = factorize(997);
    int product = 1;
    for (int f : factors) product *= f;
    EXPECT_EQ(product, 997);
}

TEST(FactorizeTest, OutputIsSorted_70) {
    vector<int> factors = factorize(70);
    vector<int> sorted_factors = factors;
    sort(sorted_factors.begin(), sorted_factors.end());
    EXPECT_EQ(factors, sorted_factors);
}

TEST(FactorizeTest, OutputIsSorted_2310) {
    vector<int> factors = factorize(2310);
    vector<int> sorted_factors = factors;
    sort(sorted_factors.begin(), sorted_factors.end());
    EXPECT_EQ(factors, sorted_factors);
}

TEST(FactorizeTest, OutputIsSorted_1000) {
    vector<int> factors = factorize(1000);
    vector<int> sorted_factors = factors;
    sort(sorted_factors.begin(), sorted_factors.end());
    EXPECT_EQ(factors, sorted_factors);
}

TEST(FactorizeTest, AllFactorsArePrime_60) {
    vector<int> factors = factorize(60);
    for (int f : factors) {
        if (f < 2) { FAIL() << f << " is not prime"; continue; }
        bool is_prime = true;
        for (int d = 2; d * d <= f; d++) {
            if (f % d == 0) { is_prime = false; break; }
        }
        EXPECT_TRUE(is_prime) << f << " is not prime";
    }
}

TEST(FactorizeTest, AllFactorsArePrime_2310) {
    vector<int> factors = factorize(2310);
    for (int f : factors) {
        if (f < 2) { FAIL() << f << " is not prime"; continue; }
        bool is_prime = true;
        for (int d = 2; d * d <= f; d++) {
            if (f % d == 0) { is_prime = false; break; }
        }
        EXPECT_TRUE(is_prime) << f << " is not prime";
    }
}

TEST(FactorizeTest, Composite_WithLargePrimeFactor_94) {
    // 94 = 2 * 47
    EXPECT_EQ(factorize(94), (vector<int>{2, 47}));
}

TEST(FactorizeTest, Composite_WithLargePrimeFactor_38) {
    // 38 = 2 * 19
    EXPECT_EQ(factorize(38), (vector<int>{2, 19}));
}

TEST(FactorizeTest, Composite_WithLargePrimeFactor_74) {
    // 74 = 2 * 37
    EXPECT_EQ(factorize(74), (vector<int>{2, 37}));
}

TEST(FactorizeTest, Composite_WithLargePrimeFactor_3xLarge) {
    // 3 * 97 = 291
    EXPECT_EQ(factorize(291), (vector<int>{3, 97}));
}

TEST(FactorizeTest, OutputSize_SinglePrime) {
    EXPECT_EQ(factorize(13).size(), 1u);
}

TEST(FactorizeTest, OutputSize_PowerOf2) {
    EXPECT_EQ(factorize(64).size(), 6u);
}

TEST(FactorizeTest, OutputSize_ThreeDistinct) {
    EXPECT_EQ(factorize(30).size(), 3u);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}