#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minimumCost(vector<int> nums, vector<int> cost, int k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        vector<long long> costPrefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
            costPrefix[i + 1] = costPrefix[i] + cost[i];
        }
        
        // dp[i] = min cost to partition nums[0..i-1]
        // For subarray nums[l..r] as the i-th subarray:
        // cost = (prefix[r+1] + k*i) * (costPrefix[r+1] - costPrefix[l])
        // Note: prefix[r+1] is sum of nums[0..r], k*i depends on subarray index
        
        // dp[r+1] = min over all l <= r of:
        //   dp[l] + (prefix[r+1] + k * subarray_index) * (costPrefix[r+1] - costPrefix[l])
        // But subarray_index depends on how many subarrays came before.
        
        // Let's redefine: dp[i][j] = min cost partitioning first i elements into j subarrays
        // This could be O(n^3) which is fine for n=1000? Actually O(n^2 * n) might be too slow.
        // n=1000, so O(n^2) DP needed.
        
        // Key insight: the i-th subarray cost uses k*i. We can rewrite:
        // total cost = sum over subarrays j of (prefix[r_j+1] + k*j) * costSum_j
        // = sum (prefix[r_j+1] * costSum_j) + k * sum(j * costSum_j)
        
        // Let's try O(n^2) DP where dp[i] = min cost for first i elements, tracking number of subarrays implicitly.
        // dp[i] = min over j < i: dp[j] + (prefix[i] + k * cnt) * (costPrefix[i] - costPrefix[j])
        // where cnt is the subarray index. This requires knowing cnt.
        
        // Use dp[i][cnt] but cnt can be up to n, giving O(n^2) states and O(n) transitions = O(n^3).
        // n=1000 -> 10^9, too slow.
        
        // Alternative: dp[i] = min cost partitioning nums[0..i-1], and we also track number of subarrays used.
        // Actually let dp[i] = min cost for nums[0..i-1]. When we extend with subarray [i..r]:
        // We need the subarray index. Let's use dp2[i][m] where m = number of subarrays.
        // Transitions: dp2[r][m] = min over l: dp2[l][m-1] + (prefix[r] + k*m)*(costPrefix[r]-costPrefix[l])
        // O(n^2) states, O(n) transitions = O(n^3). For n=1000 this is 10^9.
        
        // Given constraints n<=1000, O(n^3) might be acceptable if operations are simple.
        // Let's try it.
        
        const long long INF = 1e18;
        // dp[m][i] = min cost to partition first i elements into m subarrays
        vector<vector<long long>> dp(n + 1, vector<long long>(n + 1, INF));
        dp[0][0] = 0;
        
        for (int m = 1; m <= n; m++) {
            for (int r = m; r <= n; r++) {
                // last subarray is [l..r-1], 1-indexed as m-th
                for (int l = m - 1; l < r; l++) {
                    if (dp[m-1][l] == INF) continue;
                    long long val = dp[m-1][l] + (prefix[r] + (long long)k * m) * (costPrefix[r] - costPrefix[l]);
                    dp[m][r] = min(dp[m][r], val);
                }
            }
        }
        
        long long ans = INF;
        for (int m = 1; m <= n; m++) {
            ans = min(ans, dp[m][n]);
        }
        return ans;
    }
};