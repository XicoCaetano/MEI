#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minimumCost(vector<int>& nums, vector<int>& cost, int k) {
        int n = nums.size();
        
        // Precompute prefix sums for nums and cost
        vector<long long> prefix_nums(n + 1, 0);
        vector<long long> prefix_cost(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_nums[i + 1] = prefix_nums[i] + nums[i];
            prefix_cost[i + 1] = prefix_cost[i] + cost[i];
        }

        // dp[i][j] represents the minimum cost to divide the first j elements 
        // into exactly i subarrays.
        // Given constraints (n <= 1000), O(n^3) or optimized O(n^2) is required.
        // We initialize with a large value.
        const long long INF = 1e18;
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, INF));
        
        dp[0][0] = 0;

        // Iterate through the number of subarrays
        for (int i = 1; i <= n; ++i) {
            // Iterate through the end position of the i-th subarray
            for (int j = i; j <= n; ++j) {
                // Iterate through the possible start positions of the i-th subarray
                // The i-th subarray is nums[p...j-1]
                for (int p = i - 1; p < j; ++p) {
                    if (dp[i - 1][p] == INF) continue;

                    // Cost calculation for the i-th subarray ending at j:
                    // (sum(nums[0...j-1]) + k * i) * sum(cost[p...j-1])
                    long long current_subarray_cost = (prefix_nums[j] + (long long)k * i) * (prefix_cost[j] - prefix_cost[p]);
                    
                    dp[i][j] = min(dp[i][j], dp[i - 1][p] + current_subarray_cost);
                }
            }
        }

        // The answer is the minimum value among dividing into any number of subarrays (1 to n)
        long long min_total_cost = INF;
        for (int i = 1; i <= n; ++i) {
            min_total_cost = min(min_total_cost, dp[i][n]);
        }

        return min_total_cost;
    }
};