#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
    int dp[201][201][201];

    int getDist(char a, char b) {
        int x = a - 'a';
        int y = b - 'a';
        int diff = abs(x - y);
        return min(diff, 26 - diff);
    }

public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.length();
        // Initialize DP table with -1
        memset(dp, -1, sizeof(dp));
        return solve(0, n - 1, k, s);
    }

    int solve(int i, int j, int k, const string& s) {
        if (i > j) return 0;
        if (i == j) return 1;
        if (dp[i][j][k] != -1) return dp[i][j][k];

        // Option 1: Skip s[i]
        int res = solve(i + 1, j, k, s);
        
        // Option 2: Skip s[j]
        res = max(res, solve(i, j - 1, k, s));

        // Option 3: Match s[i] and s[j] by changing them to the same character
        // We want to find the minimum cost to make s[i] == s[j].
        // This is simply the circular distance between the two characters.
        int cost = getDist(s[i], s[j]);
        if (k >= cost) {
            res = max(res, 2 + solve(i + 1, j - 1, k - cost, s));
        }

        return dp[i][j][k] = res;
    }
};