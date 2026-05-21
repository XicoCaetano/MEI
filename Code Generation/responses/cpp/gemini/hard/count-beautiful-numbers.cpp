#include <iostream>
#include <vector>
#include <string>
#include <cstring>

using namespace std;

class Solution {
    // memo[index][tight_constraint][current_sum][current_product_rem][has_zero]
    // Max sum for 9 digits is 9 * 9 = 81.
    // However, product % sum depends on the target sum.
    // We iterate through all possible target sums (1 to 81).
    long long memo[12][2][82][82];
    string num_str;
    int target_sum;

    long long dp(int idx, bool tight, int sum, int prod_rem) {
        if (sum > target_sum) return 0;
        if (idx == num_str.size()) {
            return (sum == target_sum && prod_rem == 0) ? 1 : 0;
        }
        if (memo[idx][tight][sum][prod_rem] != -1) {
            return memo[idx][tight][sum][prod_rem];
        }

        long long count = 0;
        int limit = tight ? (num_str[idx] - '0') : 9;

        for (int d = 0; d <= limit; ++d) {
            int next_sum = sum + d;
            // If any digit is 0, the product becomes 0. 0 % target_sum is always 0.
            // We pass a special state for prod_rem if a 0 is encountered.
            // Since we only care if the final product is divisible by target_sum,
            // we can represent the "zero product" state as prod_rem = 0.
            int next_prod_rem;
            if (d == 0) {
                next_prod_rem = 0;
            } else {
                next_prod_rem = (prod_rem * d) % target_sum;
            }

            count += dp(idx + 1, tight && (d == limit), next_sum, next_prod_rem);
        }

        return memo[idx][tight][sum][prod_rem] = count;
    }

    long long solve_for_sum(long long n, int s) {
        num_str = to_string(n);
        target_sum = s;
        memset(memo, -1, sizeof(memo));
        // prod_rem starts at 1 because it's a multiplicative identity.
        // If a number starts with 0s (leading zeros), they shouldn't force 
        // the product to 0. However, the problem says "positive integer".
        // A simple way is to handle numbers digit by digit. 
        // To avoid leading zero issues with product, we use a separate DP or 
        // simply ensure we start multiplying only after the first non-zero digit.
        
        // Revised DP:
        return dp_with_zero_check(0, true, 0, 1, true);
    }

    long long memo2[12][2][82][82][2];
    long long dp_with_zero_check(int idx, bool tight, int sum, int prod_rem, bool leading_zeros) {
        if (sum > target_sum) return 0;
        if (idx == num_str.size()) {
            return (sum == target_sum && prod_rem == 0) ? 1 : 0;
        }
        if (memo2[idx][tight][sum][prod_rem][leading_zeros] != -1) {
            return memo2[idx][tight][sum][prod_rem][leading_zeros];
        }

        long long count = 0;
        int limit = tight ? (num_str[idx] - '0') : 9;

        for (int d = 0; d <= limit; ++d) {
            int next_sum = sum + d;
            int next_prod_rem;
            bool next_leading_zeros = leading_zeros && (d == 0);

            if (next_leading_zeros) {
                // Still in leading zeros, product doesn't change
                next_prod_rem = 1; 
            } else {
                if (d == 0) next_prod_rem = 0;
                else next_prod_rem = (prod_rem * d) % target_sum;
            }

            count += dp_with_zero_check(idx + 1, tight && (d == limit), next_sum, next_prod_rem, next_leading_zeros);
        }
        return memo2[idx][tight][sum][prod_rem][leading_zeros] = count;
    }

public:
    long long count_le(long long n) {
        if (n <= 0) return 0;
        long long total = 0;
        num_str = to_string(n);
        // Max possible sum for 10^9 - 1 is 9*9 = 81.
        for (int s = 1; s <= 81; ++s) {
            target_sum = s;
            memset(memo2, -1, sizeof(memo2));
            total += dp_with_zero_check(0, true, 0, 1, true);
        }
        return total;
    }

    long long beautifulNumbers(int l, int r) {
        return count_le(r) - count_le(l - 1);
    }
};