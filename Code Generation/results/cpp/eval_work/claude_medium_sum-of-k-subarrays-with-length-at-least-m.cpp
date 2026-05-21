// task_id: sum-of-k-subarrays-with-length-at-least-m
// difficulty: Medium

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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.maxSum(vector<int>{1, 0, -1, 0, 1, -1, 0, 1}, 2, 2) == 2LL));
    assert((sol.maxSum(vector<int>{5, 4, 3, 2, 1}, 2, 2) == 15LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 2, 3) == 0LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3) == 45LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 4, 2) == 78LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0}, 1, 1) == 0LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0}, 2, 1) == 0LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50}, 2, 3) == -19999850LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5}, 1, 1) == 15LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 2) == 45LL));
    assert((sol.maxSum(vector<int>{-10, 3, -1, -2}, 4, 1) == -10LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5}, 2, 3) == 45LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9}, 3, 2) == -21LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5, 1) == 55LL));
    assert((sol.maxSum(vector<int>{1, 2, -1, 3, 3, 4}, 2, 2) == 13LL));
    assert((sol.maxSum(vector<int>{5, -1, 5, -1, 5, -1}, 2, 1) == 14LL));
    assert((sol.maxSum(vector<int>{-5, -4, -3, -2, -1}, 2, 1) == -3LL));
    assert((sol.maxSum(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 5, 3) == 150LL));
    assert((sol.maxSum(vector<int>{9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, 5, 3) == 199LL));
    assert((sol.maxSum(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29}, 5, 3) == 225LL));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30, 40}, 4, 3) == -19999940LL));
    assert((sol.maxSum(vector<int>{-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}, 5, 2) == 45LL));
    assert((sol.maxSum(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, 19, -20, 21, -22}, 6, 3) == 53LL));
    assert((sol.maxSum(vector<int>{1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000}, 5, 2) == 3000LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}, 5, 1) == 5LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20}, 3, 2) == -21LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 5, 3) == 210LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10, 1) == 20LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}, 6, 1) == 6LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, -4, -5, 6, -7, 8, 9, -10, 11, 12, 13, -14}, 5, 3) == -19999942LL));
    assert((sol.maxSum(vector<int>{-100, 0, 100, -200, 0, 200, -300, 0, 300, -400, 0, 400, -500, 0, 500, -600, 0, 600, -700, 0}, 5, 2) == 2000LL));
    assert((sol.maxSum(vector<int>{5, -2, 3, -4, 6, -1, 2, 8, -5, 7}, 3, 2) == 23LL));
    assert((sol.maxSum(vector<int>{-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110, -120, -130, -140, -150}, 5, 3) == -1200LL));
    assert((sol.maxSum(vector<int>{10, -5, 15, -10, 20, -15, 25, -20, 30, -25}, 5, 2) == 25LL));
    assert((sol.maxSum(vector<int>{100, 200, 300, 400, 500, -100, -200, -300, -400, -500, 600, 700, 800, 900, 1000}, 5, 2) == 5400LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 1) == 20LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 4, 3) == 210LL));
    assert((sol.maxSum(vector<int>{100, -200, 300, -400, 500, -600, 700, -800, 900, -1000}, 4, 2) == 500LL));
    assert((sol.maxSum(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200}, 7, 2) == 4100LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, 5, 3) == 465LL));
    assert((sol.maxSum(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, 5, 2) == 60LL));
    assert((sol.maxSum(vector<int>{100, -50, 200, -150, 300, -250, 400, -350, 500, -450}, 5, 2) == 250LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15}, 5, 3) == -120LL));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60, 70, -70, 80, -80, 90, -90, 100, -100}, 5, 2) == 300LL));
    assert((sol.maxSum(vector<int>{100, 200, -300, 400, 500, -600, 700, 800, -900, 1000}, 5, 2) == 1900LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, -40, 50, 60, -70, 80, 90, -100}, 4, 2) == 300LL));
    assert((sol.maxSum(vector<int>{1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0}, 5, 2) == 3LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, -5, 2, -5, 2, 3, 2, 1, -1, 2, 3, -4, 2}, 3, 2) == 73LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}, 3, 2) == 3LL));
    assert((sol.maxSum(vector<int>{10, -20, 30, -40, 50, -60, 70, -80, 90, -100, 110, -120}, 3, 2) == 180LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 2, 3) == -21LL));
    assert((sol.maxSum(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}, 5, 2) == 1060LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 3, 1) == -6LL));
    assert((sol.maxSum(vector<int>{5, -3, 2, 1, 4, -7, 3, 2, 1, 0}, 3, 2) == 15LL));
    assert((sol.maxSum(vector<int>{100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100}, 5, 2) == 500LL));
    assert((sol.maxSum(vector<int>{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, 5, 2) == 105LL));
    assert((sol.maxSum(vector<int>{5, 1, 5, 2, 3, 4, 2, 1, 3, 4, 5}, 3, 2) == 35LL));
    assert((sol.maxSum(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29}, 4, 2) == 225LL));
    assert((sol.maxSum(vector<int>{29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1}, 4, 2) == 225LL));
    assert((sol.maxSum(vector<int>{100, 200, -300, 400, 500, -600, 700, 800, -900, 1000}, 3, 2) == 2800LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 2) == 32LL));
    assert((sol.maxSum(vector<int>{-100, 100, -100, 100, -100, 100, -100, 100, -100, 100}, 5, 2) == 0LL));
    assert((sol.maxSum(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 3, 2) == 45LL));
    assert((sol.maxSum(vector<int>{1, 2, -1, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 5, 2) == 81LL));
    assert((sol.maxSum(vector<int>{5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1}, 5, 1) == 75LL));
    assert((sol.maxSum(vector<int>{0, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15}, 5, 3) == 20LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 2) == 20LL));
    assert((sol.maxSum(vector<int>{3, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, 4, 2) == 325LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 5, 3) == 210LL));
    assert((sol.maxSum(vector<int>{1000, -2000, 3000, -4000, 5000, -6000, 7000, -8000, 9000, -10000}, 2, 1) == 16000LL));
    assert((sol.maxSum(vector<int>{0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 5, 3) == 10LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200}, 5, 3) == 2100LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}, 5, 2) == 5LL));
    assert((sol.maxSum(vector<int>{100, 0, 100, 0, 100, 0, 100, 0, 100, 0}, 5, 2) == 500LL));
    assert((sol.maxSum(vector<int>{10, -5, -1, 0, 7, 10, 1, -2, 5, -6, 7, 8, -1, -3, -2}, 4, 1) == 48LL));
    assert((sol.maxSum(vector<int>{5, -2, 6, -3, 4, 3, -1, 2, 8, -7, 1, 3, 5}, 3, 2) == 34LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 3) == 20LL));
    assert((sol.maxSum(vector<int>{5, -2, 7, 1, -3, 9, -8, 6, 4, 2}, 3, 2) == 29LL));
    assert((sol.maxSum(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9, -10}, 3, 2) == 11LL));
    assert((sol.maxSum(vector<int>{100, 200, -300, 400, -500, 600, -700, 800, -900, 1000}, 4, 2) == 1400LL));
    assert((sol.maxSum(vector<int>{1, 2, -1, 2, -1, 1, -2, 1, -2, 1, -2, 1, -2, 1}, 4, 2) == 5LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, 4, 2) == 465LL));
    assert((sol.maxSum(vector<int>{0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1}, 5, 2) == 5LL));
    assert((sol.maxSum(vector<int>{10, -20, 30, -40, 50, -60, 70, -80, 90, -100, 110, -120, 130, -140, 150, -160, 170, -180, 190, -200}, 5, 3) == 500LL));
    assert((sol.maxSum(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10}, 6, 2) == 28LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150}, 5, 2) == 1200LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10, 3) == 38LL));
    assert((sol.maxSum(vector<int>{10, -5, 3, 8, -2, -4, 7, 10, -3, 6}, 3, 1) == 41LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150}, 5, 3) == 1200LL));
    assert((sol.maxSum(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 5, 1) == 250LL));
    assert((sol.maxSum(vector<int>{5, -5, 5, -5, 5, -5, 5, -5, 5, -5}, 5, 1) == 25LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 3, 2) == -21LL));
    assert((sol.maxSum(vector<int>{100, 200, 300, 400, 500}, 2, 3) == -19998500LL));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60}, 5, 1) == 200LL));
    assert((sol.maxSum(vector<int>{10, -5, 15, -20, 25, -30, 35, -40, 45, -50, 55, -60, 65}, 4, 3) == 95LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 5, 2) == 120LL));
    assert((sol.maxSum(vector<int>{5, -3, 10, 20, -25, 50, -100, 150, -200, 300}, 3, 2) == 307LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 5, 1) == -15LL));
    assert((sol.maxSum(vector<int>{100, -50, 200, -300, 400, -500, 600, -700, 800, -900, 1000}, 5, 2) == 650LL));
    assert((sol.maxSum(vector<int>{-5, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12}, 5, 2) == -50LL));
    assert((sol.maxSum(vector<int>{5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 4, 2) == 12LL));
    assert((sol.maxSum(vector<int>{2, 3, -1, -4, 5, 3, -5, 4, 3, -3, 2, -1, 1, 2, -3, 1}, 3, 2) == 21LL));
    assert((sol.maxSum(vector<int>{-1, 4, -2, 3, -2, 3, 4, -1, -2, 3, 4, 5}, 4, 1) == 26LL));
    assert((sol.maxSum(vector<int>{5, -3, 2, 7, -1, 4, -2, 8}, 3, 2) == 21LL));
    assert((sol.maxSum(vector<int>{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}, 2, 2) == 15LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, 5, 2) == 325LL));
    assert((sol.maxSum(vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1}, 4, 2) == 210LL));
    assert((sol.maxSum(vector<int>{5, 2, -3, 8, -10, 3, 4, 1, -1, 6}, 3, 2) == 25LL));
    assert((sol.maxSum(vector<int>{-5, -1, -8, -3, -4, -7, -9, -2, -6}, 3, 2) == -21LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 4, 3) == 80LL));
    assert((sol.maxSum(vector<int>{25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 5, 3) == 325LL));
    assert((sol.maxSum(vector<int>{-10, 3, -1, -2}, 4, 1) == -10LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 2, 1) == 50LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 1) == 20LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1}, 3, 2) == 1LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 2) == 55LL));
    assert((sol.maxSum(vector<int>{1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000}, 5, 2) == 0LL));
    assert((sol.maxSum(vector<int>{10000, -10000, 10000, -10000, 10000}, 2, 2) == 10000LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 5, 1) == -15LL));
    assert((sol.maxSum(vector<int>{-1000, -2000, -3000, -4000, -5000, -6000, -7000, -8000, -9000, -10000}, 4, 1) == -10000LL));
    assert((sol.maxSum(vector<int>{-5, -4, -3, -2, -1}, 2, 2) == -10LL));
    assert((sol.maxSum(vector<int>{-3, -2, -1, 0, 1, 2, 3}, 2, 1) == 6LL));
    assert((sol.maxSum(vector<int>{1, -1, 2, -2, 3, -3, 4, -4}, 2, 1) == 7LL));
    assert((sol.maxSum(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5}, 3, 2) == 8LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 1, 1) == 0LL));
    assert((sol.maxSum(vector<int>{10, -2, -3, 10, -2, -3, 10, -2, -3}, 3, 3) == 15LL));
    assert((sol.maxSum(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5}, 5, 1) == 15LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 5, 2) == 100LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 2) == 55LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5}, 1, 3) == 15LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3, 3) == 550LL));
    assert((sol.maxSum(vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 5, 1) == -5LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 2, 1) == 550LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 3, 3) == 50LL));
    assert((sol.maxSum(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, 3, 1) == 45LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 5, 1) == 50LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 3, 2) == 0LL));
    assert((sol.maxSum(vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 3, 3) == -9LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1}, 2, 1) == 2LL));
    assert((sol.maxSum(vector<int>{10000, 10000, 10000, 10000}, 2, 2) == 40000LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0}, 1, 1) == 0LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6}, 3, 1) == 21LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1}, 5, 2) == 0LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 1, 1) == 0LL));
    assert((sol.maxSum(vector<int>{100, -100, 200, -200, 300}, 2, 2) == 300LL));
    assert((sol.maxSum(vector<int>{10, 20, -30, 40, 50, -60, 70, 80, 90}, 3, 1) == 360LL));
    assert((sol.maxSum(vector<int>{100, -50, 100, -50, 100, -50, 100, -50, 100, -50}, 2, 2) == 350LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 2, 3) == 50LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 2, 2) == 50LL));
    assert((sol.maxSum(vector<int>{5, 1, 1, 5, 5, 1, 1, 5}, 3, 2) == 24LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 2, 2) == -10LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 1) == 10LL));
    assert((sol.maxSum(vector<int>{5, 6, 7, 8, 9, 10}, 2, 2) == 45LL));
    assert((sol.maxSum(vector<int>{100, -200, 300, -400, 500}, 2, 2) == 300LL));
    assert((sol.maxSum(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, 3, 2) == 5500LL));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30, 40, -40, 50, -50}, 3, 2) == 80LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 3, 2) == 50LL));
    assert((sol.maxSum(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9}, 3, 1) == 21LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 5, 2) == 120LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 2, 2) == 0LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 2, 2) == 10LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 2, 1) == 0LL));
    assert((sol.maxSum(vector<int>{100, -100, 100, -100, 100, -100, 100, -100, 100, -100}, 2, 3) == 200LL));
    assert((sol.maxSum(vector<int>{100, -100, 100, -100, 100, -100, 100, -100, 100, -100}, 3, 2) == 200LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 5, 2) == -55LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 5, 3) == 120LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5}, 2, 3) == 40LL));
    assert((sol.maxSum(vector<int>{5, 2, 3, 4, 5, 6}, 3, 1) == 25LL));
    assert((sol.maxSum(vector<int>{100, -100, 200, -200, 300, -300}, 3, 1) == 600LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50}, 1, 3) == 150LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 5, 2) == 210LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5}, 2, 1) == 15LL));
    assert((sol.maxSum(vector<int>{2, 1, -1, 2, -1, -2, 1}, 2, 1) == 5LL));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30, 40, -40}, 4, 1) == 100LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 2, 2) == -10LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0}, 2, 1) == 0LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1}, 2, 2) == 1LL));
    assert((sol.maxSum(vector<int>{10, -2, 3, -1, 4, -3, 6, -2, 5, -1, 8, -3, 7, -2, 9}, 3, 2) == 44LL));
    assert((sol.maxSum(vector<int>{5, -1, 5, -1, 5, -1, 5, -1}, 2, 2) == 18LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 2, 2) == 0LL));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0}, 2, 2) == 0LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1}, 5, 1) == 5LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5}, 2, 2) == 15LL));
    assert((sol.maxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 2, 3) == 55LL));
    assert((sol.maxSum(vector<int>{1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000}, 3, 3) == 55000LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5}, 2, 2) == -10LL));
    assert((sol.maxSum(vector<int>{1, 0, -1, 0, 1, -1, 0, 1, -1, 0}, 3, 1) == 3LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 3, 1) == 10LL));
    assert((sol.maxSum(vector<int>{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}, 3, 2) == 15LL));
    assert((sol.maxSum(vector<int>{100, 200, 300, 400, 500}, 1, 3) == 1500LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 1) == 55LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3, 3) == 550LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 3, 2) == 50LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5}, 3, 1) == 15LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 3, 2) == 10LL));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1}, 2, 1) == 2LL));
    assert((sol.maxSum(vector<int>{10, -5, -1, 7, 10, 5, -10, 10, 10, -5}, 2, 2) == 46LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 4, 3) == 12LL));
    assert((sol.maxSum(vector<int>{2, 4, 5, 6, 7, 8, 9}, 3, 2) == 41LL));
    assert((sol.maxSum(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9, -10}, 5, 1) == 25LL));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30}, 3, 2) == 0LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5}, 2, 2) == -10LL));
    assert((sol.maxSum(vector<int>{1000, -1000, 1000, -1000, 1000, -1000}, 3, 2) == 0LL));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 2) == 20LL));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9}, 2, 2) == -10LL));
    assert((sol.maxSum(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10}, 5, 2) == 30LL));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 2, 3) == 550LL));
    assert((sol.maxSum(vector<int>{1, 2, -1, 3, 3, 4}, 2, 2) == 13LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 2, 3) == 45LL));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5}, 3, 2) == 30LL));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 3) == 55LL));

    cout << "All tests passed for sum-of-k-subarrays-with-length-at-least-m" << endl;
    return 0;
}
