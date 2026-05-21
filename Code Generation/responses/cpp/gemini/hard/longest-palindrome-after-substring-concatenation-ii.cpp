#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    int longestPalindrome(string s, string t) {
        string combined = s + t;
        int n = combined.length();
        int n1 = s.length();
        int n2 = t.length();
        
        // dp[i][j] stores the length of the longest palindromic subsequence 
        // in combined[i...j]
        vector<vector<int>> dp(n, vector<int>(n, 0));
        int ans = 0;

        for (int i = n - 1; i >= 0; i--) {
            dp[i][i] = 1;
            for (int j = i + 1; j < n; j++) {
                if (combined[i] == combined[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                    
                    // We only update the global max if the palindrome uses at least 
                    // one character from s and at least one character from t.
                    // This happens if i < n1 (index in s) and j >= n1 (index in t).
                    if (i < n1 && j >= n1) {
                        ans = max(ans, dp[i][j]);
                    }
                } else {
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1]);
                }
            }
        }
        
        return ans;
    }

    // Keeping signature as per starter code, though logic is combined above
    int calc(const string& s, const string& t) {
        return longestPalindrome(s, t);
    }
};