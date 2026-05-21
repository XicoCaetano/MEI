#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long maxSum(vector<int>& nums, int k, int m) {
        int n = nums.size();
        
        // Prefix sums to calculate subarray sums in O(1)
        vector<long long> prefix_sum(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            prefix_sum[i + 1] = prefix_sum[i] + nums[i];
        }

        // dp[i][j] is the maximum sum using i subarrays from the first j elements.
        // We use a 1D DP or two rows to save space, but given N=2000, 
        // a 2D array or two rows of size N+1 is fine.
        const long long INF = 1e18;
        vector<long long> dp(n + 1, -INF);
        
        // Base case: 0 subarrays result in a sum of 0
        for (int j = 0; j <= n; ++j) {
            dp[j] = 0;
        }

        for (int i = 1; i <= k; ++i) {
            vector<long long> next_dp(n + 1, -INF);
            long long max_prev_dp = -INF;
            
            // To pick the i-th subarray ending at index j-1 (1-based index j),
            // the subarray must start at some index 'start' such that j - start >= m.
            // So start <= j - m.
            // We need to look at dp[start] (from previous i-1 subarrays) 
            // plus the sum of nums[start...j-1].
            
            for (int j = m * i; j <= n; ++j) {
                // Option 1: The i-th subarray ends exactly at j-1 and has length m.
                // We transition from the best solution of i-1 subarrays ending at or before j-m.
                // However, we can extend a previously started i-th subarray.
                
                // To optimize:
                // Let f[i][j] be max sum of i subarrays within first j elements.
                // f[i][j] = max(f[i][j-1], max_{p <= j-m} (f[i-1][p] + sum(p...j-1)))
                
                // Let's redefine:
                // dp[j] = max sum of i-1 subarrays using first j elements.
                // next_dp[j] = max sum of i subarrays using first j elements.
            }
            
            // Correct approach for i-th subarray:
            // best_prev captures the max of (dp[p] - prefix_sum[p]) for p <= j - m
            long long best_prev = -INF;
            for (int j = 1; j <= n; ++j) {
                // We can potentially start a new m-length subarray ending at j
                if (j >= m) {
                    best_prev = max(best_prev, dp[j - m] - prefix_sum[j - m]);
                }
                
                next_dp[j] = next_dp[j - 1]; // Case: i-th subarray ends before index j-1
                if (best_prev != -INF) {
                    next_dp[j] = max(next_dp[j], best_prev + prefix_sum[j]);
                }
            }
            dp = move(next_dp);
        }

        return dp[n];
    }
};