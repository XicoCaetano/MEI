#include <gtest/gtest.h>
#include <vector>

// Function declaration (assuming it's in the global namespace)
bool below_zero(std::vector<int> operations);

// Test suite for below_zero function
class BelowZeroTest : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Empty vector - never below zero
TEST_F(BelowZeroTest, EmptyVectorReturnsFalse) {
    std::vector<int> operations;
    EXPECT_FALSE(below_zero(operations));
}

// Test: Single positive deposit
TEST_F(BelowZeroTest, SinglePositiveDepositReturnsFalse) {
    std::vector<int> operations = {100};
    EXPECT_FALSE(below_zero(operations));
}

// Test: Single negative deposit (immediately below zero)
TEST_F(BelowZeroTest, SingleNegativeDepositReturnsTrue) {
    std::vector<int> operations = {-5};
    EXPECT_TRUE(below_zero(operations));
}

// Test: Single zero deposit
TEST_F(BelowZeroTest, SingleZeroDepositReturnsFalse) {
    std::vector<int> operations = {0};
    EXPECT_FALSE(below_zero(operations));
}

// Test: All positive deposits
TEST_F(BelowZeroTest, AllPositiveDepositsReturnsFalse) {
    std::vector<int> operations = {1, 2, 3, 4, 5};
    EXPECT_FALSE(below_zero(operations));
}

// Test: Balance never drops below zero
TEST_F(BelowZeroTest, BalanceNeverBelowZeroReturnsFalse) {
    std::vector<int> operations = {5, 3, -2, 4, -1};
    EXPECT_FALSE(below_zero(operations));
}

// Test: Balance drops below zero exactly at the negative operation
TEST_F(BelowZeroTest, BalanceDropsBelowZeroAtNegativeOperationReturnsTrue) {
    std::vector<int> operations = {5, 3, -9};
    EXPECT_TRUE(below_zero(operations));
}

// Test: Balance drops below zero after multiple operations
TEST_F(BelowZeroTest, BalanceDropsBelowZeroAfterMultipleOperationsReturnsTrue) {
    std::vector<int> operations = {1, 2, 3, -10};
    EXPECT_TRUE(below_zero(operations));
}

// Test: Balance drops below zero then recovers but should still return true
TEST_F(BelowZeroTest, BalanceDropsBelowZeroThenRecoversReturnsTrue) {
    std::vector<int> operations = {1, -5, 10};
    EXPECT_TRUE(below_zero(operations));
}

// Test: Balance drops below zero multiple times
TEST_F(BelowZeroTest, BalanceDropsBelowZeroMultipleTimesReturnsTrue) {
    std::vector<int> operations = {1, -2, 5, -10, 8};
    EXPECT_TRUE(below_zero(operations));
}

// Test: Balance exactly zero after operations
TEST_F(BelowZeroTest, BalanceExactlyZeroAfterOperationsReturnsFalse) {
    std::vector<int> operations = {3, -2, 5, -6};
    EXPECT_FALSE(below_zero(operations));
}

// Test: Balance exactly zero at intermediate point
TEST_F(BelowZeroTest, BalanceExactlyZeroAtIntermediatePointReturnsFalse) {
    std::vector<int> operations = {5, -5, 2};
    EXPECT_FALSE(below_zero(operations));
}

// Test: Large positive values
TEST_F(BelowZeroTest, LargePositiveValuesReturnsFalse) {
    std::vector<int> operations = {1000000, 2000000, -1500000, 500000};
    EXPECT_FALSE(below_zero(operations));
}

// Test: Large negative value causing immediate underflow
TEST_F(BelowZeroTest, LargeNegativeValueReturnsTrue) {
    std::vector<int> operations = {500000, -1000000};
    EXPECT_TRUE(below_zero(operations));
}

// Test: Operation sequence that dips to negative, returns to positive, dips again
TEST_F(BelowZeroTest, MultipleNegativeDipsReturnsTrue) {
    std::vector<int> operations = {2, -3, 5, -8, 10, -12};
    EXPECT_TRUE(below_zero(operations));
}

// Test: Maximum integer values (assuming no overflow concerns)
TEST_F(BelowZeroTest, MaximumIntegerValues) {
    std::vector<int> operations = {2147483647, -2147483647};
    EXPECT_FALSE(below_zero(operations));
}

// Test: Minimum integer negative value
TEST_F(BelowZeroTest, MinimumIntegerNegativeValue) {
    std::vector<int> operations = {0, -2147483648};
    // This will underflow because adding negative max to zero will go negative
    EXPECT_TRUE(below_zero(operations));
}