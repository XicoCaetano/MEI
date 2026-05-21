#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxSum(vector<int> nums, int k, int m) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++)
            prefix[i + 1] = prefix[i] + nums[i];
        
        // dp[j][i] = max sum using j subarrays from first i elements
        // Use rolling array: prev and curr
        const long long NEG_INF = LLONG_MIN / 2;
        
        vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, NEG_INF));
        for (int i = 0; i <= n; i++) dp[0][i] = 0;
        
        for (int j = 1; j <= k; j++) {
            // best[i] = max dp[j-1][t] for t <= i
            // We want: dp[j][i] = max over l in [m, i] of (dp[j-1][i-l] + prefix[i] - prefix[i-l])
            // = prefix[i] + max over t in [0, i-m] of (dp[j-1][t] - prefix[t])
            
            long long best = NEG_INF;
            for (int i = 0; i <= n; i++) {
                // At position i, we can end a subarray here
                // The subarray ends at index i (1-based), starts at i-l+1
                // We need i >= m*j (enough elements for j subarrays)
                
                // Update best with dp[j-1][i-m] - prefix[i-m] if valid
                if (i >= m) {
                    long long val = dp[j-1][i-m];
                    if (val != NEG_INF)
                        best = max(best, val - prefix[i-m]);
                }
                
                if (best != NEG_INF)
                    dp[j][i] = max(dp[j][i], prefix[i] + best);
            }
        }
        
        long long ans = NEG_INF;
        for (int i = 0; i <= n; i++)
            ans = max(ans, dp[k][i]);
        return ans;
    }
};