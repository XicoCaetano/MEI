#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxScore(vector<int> nums) {
        int n = nums.size();
        // prefix sum
        vector<long long> pre(n + 1, 0);
        for (int i = 0; i < n; i++)
            pre[i + 1] = pre[i] + nums[i];
        
        // dp[i][j] = max score from subarray nums[i..j]
        // We need to reduce to size <= 2, collecting scores along the way
        // Total sum is fixed; we want to maximize collected = total - remaining
        // Remaining is the last 1 or 2 elements (uncollected)
        // Actually: we collect until <= 2 elements remain, but we don't collect those.
        // So maximize collected = pre[n] - (remaining element(s) sum)
        // We want to minimize the remaining sum.
        
        // dp[i][j] = min sum of remaining when we've reduced nums[i..j] to <= 2 elements
        // If j - i + 1 <= 2: dp[i][j] = sum(i..j)
        // Else: dp[i][j] = min of:
        //   dp[i+2][j] (removed first two, their sum is added to score)
        //   dp[i][j-2] (removed last two)
        //   dp[i+1][j-1] (removed first and last)
        
        vector<vector<long long>> dp(n, vector<long long>(n, LLONG_MAX));
        
        for (int i = 0; i < n; i++) {
            dp[i][i] = nums[i];
            if (i + 1 < n)
                dp[i][i+1] = nums[i] + nums[i+1];
        }
        
        for (int len = 3; len <= n; len++) {
            for (int i = 0; i + len - 1 < n; i++) {
                int j = i + len - 1;
                long long best = LLONG_MAX;
                // remove first two: i+2 .. j
                if (i + 2 <= j)
                    best = min(best, dp[i+2][j]);
                else // i+2 > j means nothing left
                    best = min(best, 0LL);
                // remove last two: i .. j-2
                if (i <= j - 2)
                    best = min(best, dp[i][j-2]);
                else
                    best = min(best, 0LL);
                // remove first and last: i+1 .. j-1
                if (i + 1 <= j - 1)
                    best = min(best, dp[i+1][j-1]);
                else
                    best = min(best, 0LL);
                dp[i][j] = best;
            }
        }
        
        long long total = pre[n];
        return total - dp[0][n-1];
    }
};