#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.size();
        // dp[i][j][c] = longest palindromic subsequence of s[i..j] where both ends are character c
        // We want the longest palindromic subsequence where total cost <= k
        
        // Alternative: dp[i][j] = max length palindromic subsequence in s[i..j] using at most k ops
        // But k needs to be part of state too... k<=200, n<=200
        
        // dp[i][j][ops] = longest palindromic subseq in s[i..j] using at most 'ops' operations
        // n=200, k=200 => 200*200*201 states, too much memory? 200*200*201 = ~8M, feasible
        
        // Actually let's think differently:
        // dp[i][j] with memoization, tracking remaining k
        // dp[i][j][k] = longest palindromic subsequence of s[i..j] with at most k ops
        
        // cost to make char a and char b equal (min ops on circular alphabet of 26)
        auto cost = [](char a, char b) {
            int d = abs(a - b);
            return min(d, 26 - d);
        };
        
        // dp[i][j][rem] = longest pal subseq in s[i..j] with rem ops remaining
        // Transitions:
        // 1. Skip s[i] or s[j]: dp[i+1][j][rem], dp[i][j-1][rem]
        // 2. Match s[i] and s[j]: need cost(s[i],s[j]) ops, if <= rem:
        //    if i==j: 1
        //    else: 2 + dp[i+1][j-1][rem - cost(s[i],s[j])]
        
        // n=200, k=200 => 200*200*201 ~ 8M entries, each int => ~32MB, should be ok
        
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k+1, -1)));
        
        function<int(int,int,int)> solve = [&](int i, int j, int rem) -> int {
            if (i > j) return 0;
            if (i == j) return 1; // single char, always palindrome of length 1
            if (dp[i][j][rem] != -1) return dp[i][j][rem];
            
            int res = max(solve(i+1, j, rem), solve(i, j-1, rem));
            
            int c = cost(s[i], s[j]);
            if (c <= rem) {
                int inner = (i+1 <= j-1) ? solve(i+1, j-1, rem - c) : 0;
                res = max(res, 2 + inner);
            }
            
            dp[i][j][rem] = res;
            return res;
        };
        
        return solve(0, n-1, k);
    }
};