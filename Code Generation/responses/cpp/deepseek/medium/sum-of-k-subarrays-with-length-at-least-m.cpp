#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    long long maxSum(vector<int> nums, int k, int m) {
        int n = nums.size();
        
        // Prefix sums for quick subarray sum calculation
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }
        
        // DP array: dp[i][j] = max sum using j subarrays from first i elements
        vector<vector<long long>> dp(n + 1, vector<long long>(k + 1, LLONG_MIN / 2));
        dp[0][0] = 0;
        
        // For tracking the best previous value when we take subarrays of length at least m
        vector<vector<long long>> bestPrev(n + 1, vector<long long>(k + 1, LLONG_MIN / 2));
        
        // Initialize bestPrev[i][0] for using 0 subarrays
        for (int i = 0; i <= n; i++) {
            bestPrev[i][0] = 0;
        }
        
        // Fill DP table
        for (int i = 1; i <= n; i++) {
            // Not using element i as part of a new subarray
            for (int j = 0; j <= k; j++) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j]);
                bestPrev[i][j] = max(bestPrev[i - 1][j], dp[i - m][j] - prefix[i - m]);
            }
            
            // Using element i as end of a new subarray
            for (int j = 1; j <= k; j++) {
                if (i >= m) {
                    // We can start a subarray ending at i (1-indexed) or i-1 (0-indexed)
                    // Start the subarray at some position pos, where pos >= 1 (1-indexed), pos <= i-m+1
                    // dp[i][j] = max(dp[pos-1][j-1] + sum(pos..i))
                    // sum(pos..i) = prefix[i] - prefix[pos-1]
                    // So dp[pos-1][j-1] - prefix[pos-1] + prefix[i]
                    
                    // Use bestPrev to store max of (dp[pos-1][j-1] - prefix[pos-1]) for valid starts
                    if (bestPrev[i - m + 1][j - 1] != LLONG_MIN / 2) {
                        dp[i][j] = max(dp[i][j], bestPrev[i - m + 1][j - 1] + prefix[i]);
                    }
                }
            }
            
            // Update bestPrev for future steps
            for (int j = 0; j <= k; j++) {
                bestPrev[i][j] = max(bestPrev[i - 1][j], dp[i][j] - prefix[i]);
            }
        }
        
        return dp[n][k];
    }
};