#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.length();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        
        function<int(int, int, int)> solve = [&](int i, int j, int rem) -> int {
            if (i > j) return 0;
            if (i == j) return 1;
            if (dp[i][j][rem] != -1) return dp[i][j][rem];
            
            int res = max(solve(i + 1, j, rem), solve(i, j - 1, rem));
            
            int diff = abs(s[i] - s[j]);
            int cost = min(diff, 26 - diff);
            
            if (rem >= cost) {
                res = max(res, 2 + solve(i + 1, j - 1, rem - cost));
            }
            
            return dp[i][j][rem] = res;
        };
        
        return solve(0, n - 1, k);
    }
};