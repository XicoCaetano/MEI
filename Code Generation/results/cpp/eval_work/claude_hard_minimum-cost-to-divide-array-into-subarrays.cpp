// task_id: minimum-cost-to-divide-array-into-subarrays
// difficulty: Hard

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>
#include <numeric>
#include <queue>
#include <stack>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>

using namespace std;



// === MODEL RESPONSE ===
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.minimumCost(vector<int>{1}, vector<int>{1}, 1) == 2LL));
    assert((sol.minimumCost(vector<int>{4, 8, 5, 1, 14, 2, 2, 12, 1}, vector<int>{7, 2, 8, 4, 2, 2, 1, 1, 2}, 7) == 985LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, 2) == 130LL));
    assert((sol.minimumCost(vector<int>{3, 1, 4}, vector<int>{4, 6, 6}, 1) == 110LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30}, vector<int>{1, 2, 3}, 5) == 315LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5, 5}, vector<int>{5, 5, 5, 5, 5}, 10) == 825LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5}, vector<int>{1, 1, 1, 1, 1}, 2) == 59LL));
    assert((sol.minimumCost(vector<int>{10, 10, 10}, vector<int>{10, 10, 10}, 5) == 900LL));
    assert((sol.minimumCost(vector<int>{10, 10, 10}, vector<int>{10, 10, 10}, 10) == 1100LL));
    assert((sol.minimumCost(vector<int>{5, 3, 8, 9, 2}, vector<int>{2, 4, 3, 5, 1}, 3) == 341LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, 3) == 155LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30}, vector<int>{100, 200, 300}, 5) == 31500LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5}, vector<int>{1, 1, 1, 1}, 2) == 69LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3}, vector<int>{1, 1, 1}, 1) == 16LL));
    assert((sol.minimumCost(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}, vector<int>{50, 45, 40, 35, 30, 25, 20, 15, 10, 5}, 50) == 46700LL));
    assert((sol.minimumCost(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1}, 50) == 18550LL));
    assert((sol.minimumCost(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5}, vector<int>{4, 6, 6, 3, 2, 1, 5, 7, 8}, 5) == 1289LL));
    assert((sol.minimumCost(vector<int>{1, 2, 1, 2, 1, 2, 1, 2}, vector<int>{1, 2, 1, 2, 1, 2, 1, 2}, 4) == 177LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 15) == 2285LL));
    assert((sol.minimumCost(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, 10) == 798LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5) == 425LL));
    assert((sol.minimumCost(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 50) == 1853000LL));
    assert((sol.minimumCost(vector<int>{999, 998, 997, 996, 995}, vector<int>{1000, 1000, 1000, 1000, 1000}, 1000) == 25952000LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 1) == 17401LL));
    assert((sol.minimumCost(vector<int>{9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, vector<int>{9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, 1) == 4950LL));
    assert((sol.minimumCost(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 1) == 1179LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 5) == 1402LL));
    assert((sol.minimumCost(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6}, vector<int>{6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6}, 1) == 6270LL));
    assert((sol.minimumCost(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9}, vector<int>{9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2}, 7) == 2829LL));
    assert((sol.minimumCost(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 1) == 1901LL));
    assert((sol.minimumCost(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == 22055LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 15) == 2285LL));
    assert((sol.minimumCost(vector<int>{5, 10, 15, 20, 25}, vector<int>{2, 4, 6, 8, 10}, 5) == 1800LL));
    assert((sol.minimumCost(vector<int>{999, 998, 997, 996, 995, 994, 993, 992, 991, 990}, vector<int>{1000, 999, 998, 997, 996, 995, 994, 993, 992, 991}, 1000) == 84261650LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 5) == 5011LL));
    assert((sol.minimumCost(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}, 7) == 3817LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == 2705LL));
    assert((sol.minimumCost(vector<int>{100, 200, 300, 400, 500}, vector<int>{10, 20, 30, 40, 50}, 50) == 162500LL));
    assert((sol.minimumCost(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<int>{100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, 10) == 36700LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5, 5}, vector<int>{1, 2, 3, 4, 5}, 10) == 525LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5, 5, 5}, vector<int>{10, 10, 10, 10, 10, 10}, 5) == 1750LL));
    assert((sol.minimumCost(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10) == 200LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50}, vector<int>{1, 2, 3, 4, 5}, 10) == 1800LL));
    assert((sol.minimumCost(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 10) == 1740100LL));
    assert((sol.minimumCost(vector<int>{9, 7, 5, 3, 1}, vector<int>{9, 7, 5, 3, 1}, 2) == 505LL));
    assert((sol.minimumCost(vector<int>{500, 500, 500, 500, 500, 500, 500, 500, 500, 500}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 500) == 270500LL));
    assert((sol.minimumCost(vector<int>{1000, 1, 1000, 1, 1000, 1, 1000, 1, 1000, 1}, vector<int>{1, 1000, 1, 1000, 1, 1000, 1, 1000, 1, 1000}, 1000) == 26043017LL));
    assert((sol.minimumCost(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == 434LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5) == 369LL));
    assert((sol.minimumCost(vector<int>{5, 3, 8, 1, 9}, vector<int>{2, 3, 4, 1, 5}, 3) == 345LL));
    assert((sol.minimumCost(vector<int>{5, 4, 3, 2, 1}, vector<int>{5, 4, 3, 2, 1}, 3) == 232LL));
    assert((sol.minimumCost(vector<int>{5, 4, 3, 2, 1}, vector<int>{10, 20, 30, 40, 50}, 5) == 3000LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 4, 3, 2, 1}, 5) == 875LL));
    assert((sol.minimumCost(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 3) == 2100LL));
    assert((sol.minimumCost(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, 3) == 2655LL));
    assert((sol.minimumCost(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{20, 18, 16, 14, 12, 10, 8, 6, 4, 2}, 100) == 18820LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 4, 3, 2, 1}, 5) == 875LL));
    assert((sol.minimumCost(vector<int>{1, 10, 1, 10, 1, 10, 1, 10, 1, 10}, vector<int>{10, 1, 10, 1, 10, 1, 10, 1, 10, 1}, 30) == 4052LL));
    assert((sol.minimumCost(vector<int>{100, 100, 100, 100, 100, 100, 100}, vector<int>{1, 1, 1, 1, 1, 1, 1}, 100) == 4600LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 50) == 3690LL));
    assert((sol.minimumCost(vector<int>{1, 10, 1, 10, 1, 10, 1, 10}, vector<int>{10, 1, 10, 1, 10, 1, 10, 1}, 2) == 1041LL));
    assert((sol.minimumCost(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10) == 69200LL));
    assert((sol.minimumCost(vector<int>{5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5}, 25) == 25751LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 5) == 2125LL));
    assert((sol.minimumCost(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110}, 7) == 30420LL));
    assert((sol.minimumCost(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == 295LL));
    assert((sol.minimumCost(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10) == 3019LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 7) == 5537LL));
    assert((sol.minimumCost(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 10) == 10152LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == 2255LL));
    assert((sol.minimumCost(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, 7) == 8542LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10) == 15636LL));
    assert((sol.minimumCost(vector<int>{1, 3, 2, 4, 5, 6, 7, 8, 9}, vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, 15) == 1713LL));
    assert((sol.minimumCost(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3) == 3706LL));
    assert((sol.minimumCost(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5) == 425LL));
    assert((sol.minimumCost(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == 85LL));
    assert((sol.minimumCost(vector<int>{2, 7, 1, 8, 2, 8, 1, 8, 2, 8}, vector<int>{8, 2, 8, 4, 5, 9, 0, 4, 5, 2}, 4) == 1485LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 10) == 1868LL));
    assert((sol.minimumCost(vector<int>{1, 3, 2, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3) == 22850LL));
    assert((sol.minimumCost(vector<int>{5, 3, 8, 9, 2}, vector<int>{2, 3, 1, 4, 5}, 3) == 385LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 20) == 3821LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90}, vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10}, 5) == 18550LL));
    assert((sol.minimumCost(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1}, 3) == 378LL));
    assert((sol.minimumCost(vector<int>{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, vector<int>{2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1}, 2) == 673LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50, 60}, vector<int>{60, 50, 40, 30, 20, 10}, 3) == 14280LL));
    assert((sol.minimumCost(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 1) == 1901LL));
    assert((sol.minimumCost(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 15) == 1615LL));
    assert((sol.minimumCost(vector<int>{500, 500, 500, 500, 500, 500, 500, 500, 500, 500}, vector<int>{1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000}, 500) == 42500000LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 4, 3, 2, 1}, 10) == 1050LL));
    assert((sol.minimumCost(vector<int>{7, 10, 4, 3, 20, 15}, vector<int>{2, 3, 4, 5, 6, 7}, 10) == 1483LL));
    assert((sol.minimumCost(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 5) == 1440LL));
    assert((sol.minimumCost(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, 2) == 7040LL));
    assert((sol.minimumCost(vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == 3905LL));
    assert((sol.minimumCost(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}, 7) == 3817LL));
    assert((sol.minimumCost(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}, 1) == 2396LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90}, vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, 10) == 6420LL));
    assert((sol.minimumCost(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, 7) == 2107LL));
    assert((sol.minimumCost(vector<int>{6, 2, 5, 8, 1, 4, 7, 3}, vector<int>{4, 1, 3, 2, 5, 6, 1, 2}, 2) == 626LL));
    assert((sol.minimumCost(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 20) == 8312LL));
    assert((sol.minimumCost(vector<int>{5, 10, 15, 20, 25, 30}, vector<int>{2, 3, 5, 7, 11, 13}, 20) == 4545LL));
    assert((sol.minimumCost(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10}, vector<int>{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, 5) == 1860LL));
    assert((sol.minimumCost(vector<int>{2, 3, 5, 7, 11, 13, 17, 19}, vector<int>{19, 17, 13, 11, 7, 5, 3, 2}, 15) == 3355LL));
    assert((sol.minimumCost(vector<int>{1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, vector<int>{2, 3, 2, 3, 2, 3, 2, 3, 2, 3}, 2) == 341LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 20) == 213400LL));
    assert((sol.minimumCost(vector<int>{7, 1, 5, 3, 6, 4}, vector<int>{10, 20, 30, 40, 50, 60}, 5) == 6060LL));
    assert((sol.minimumCost(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5) == 144LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50}, vector<int>{1, 2, 3, 4, 5}, 10) == 1800LL));
    assert((sol.minimumCost(vector<int>{10, 20, 30, 40, 50}, vector<int>{1, 2, 3, 4, 5}, 5) == 1625LL));

    cout << "All tests passed for minimum-cost-to-divide-array-into-subarrays" << endl;
    return 0;
}
