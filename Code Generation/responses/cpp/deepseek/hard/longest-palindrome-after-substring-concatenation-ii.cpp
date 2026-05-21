#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

class Solution {
public:
    int calc(const string& s, const string& t) {
        int n = s.length(), m = t.length();
        vector<vector<int>> dp_s(n, vector<int>(n, 0));
        vector<vector<int>> dp_t(m, vector<int>(m, 0));
        
        // dp_s[i][j] = length of longest palindrome in s[i..j]
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                if (len == 1) {
                    dp_s[i][j] = 1;
                } else if (len == 2) {
                    dp_s[i][j] = (s[i] == s[j]) ? 2 : 1;
                } else {
                    if (s[i] == s[j]) {
                        dp_s[i][j] = 2 + dp_s[i+1][j-1];
                    } else {
                        dp_s[i][j] = max(dp_s[i+1][j], dp_s[i][j-1]);
                    }
                }
            }
        }
        
        // dp_t[i][j] = length of longest palindrome in t[i..j]
        for (int len = 1; len <= m; len++) {
            for (int i = 0; i + len <= m; i++) {
                int j = i + len - 1;
                if (len == 1) {
                    dp_t[i][j] = 1;
                } else if (len == 2) {
                    dp_t[i][j] = (t[i] == t[j]) ? 2 : 1;
                } else {
                    if (t[i] == t[j]) {
                        dp_t[i][j] = 2 + dp_t[i+1][j-1];
                    } else {
                        dp_t[i][j] = max(dp_t[i+1][j], dp_t[i][j-1]);
                    }
                }
            }
        }
        
        int ans = 0;
        
        // Case 1: palindrome entirely in s
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                ans = max(ans, dp_s[i][j]);
            }
        }
        
        // Case 2: palindrome entirely in t
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {
                ans = max(ans, dp_t[i][j]);
            }
        }
        
        // Case 3: palindrome formed by concatenation
        // Try all pairs of substrings: s[i..j] + t[k..l]
        // We need to find the longest palindrome that can be formed
        
        // Precompute prefix and suffix palindromes
        vector<vector<bool>> is_pal_s(n, vector<bool>(n, false));
        vector<vector<bool>> is_pal_t(m, vector<bool>(m, false));
        
        // Mark palindromes in s
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                is_pal_s[i][j] = (dp_s[i][j] == j - i + 1);
            }
        }
        
        // Mark palindromes in t
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {
                is_pal_t[i][j] = (dp_t[i][j] == j - i + 1);
            }
        }
        
        // For each possible center or extended palindrome
        // Try to extend from s and t
        
        // Try all pairs of positions: one from s, one from t, and expand outward
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Check if s[i] == t[j], can start forming palindrome
                if (s[i] == t[j]) {
                    // Expand outward from this pair
                    int left_s = i, right_s = i;
                    int left_t = j, right_t = j;
                    int len = 2;
                    
                    // Expand while we can
                    while (left_s > 0 && right_t < m - 1 && s[left_s - 1] == t[right_t + 1]) {
                        left_s--;
                        right_t++;
                        len += 2;
                    }
                    ans = max(ans, len);
                    
                    // Now try to find longer palindromes by using palindromic substrings
                    // inside s and t
                    
                    // Try to prepend a palindrome from s before the left_s
                    if (left_s > 0) {
                        for (int k = 0; k < left_s; k++) {
                            if (is_pal_s[k][left_s - 1]) {
                                ans = max(ans, len + (left_s - k));
                            }
                        }
                    }
                    
                    // Try to append a palindrome from t after the right_t
                    if (right_t < m - 1) {
                        for (int k = right_t + 1; k < m; k++) {
                            if (is_pal_t[right_t + 1][k]) {
                                ans = max(ans, len + (k - right_t));
                            }
                        }
                    }
                }
            }
        }
        
        // Try all palindromic centers in the concatenated string
        // This is essentially looking for substrings that can be extended
        // with palindromes from either side
        
        // More exhaustive approach: try all pairs of substrings s[i..j] and t[k..l]
        // that together form a palindrome
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                string sub_s = s.substr(i, j - i + 1);
                for (int k = 0; k < m; k++) {
                    for (int l = k; l < m; l++) {
                        string sub_t = t.substr(k, l - k + 1);
                        string concat = sub_s + sub_t;
                        bool is_pal = true;
                        int left = 0, right = concat.length() - 1;
                        while (left < right) {
                            if (concat[left] != concat[right]) {
                                is_pal = false;
                                break;
                            }
                            left++;
                            right--;
                        }
                        if (is_pal) {
                            ans = max(ans, (int)concat.length());
                        }
                    }
                }
            }
        }
        
        return ans;
    }
    
    int longestPalindrome(string s, string t) {
        return calc(s, t);
    }
};