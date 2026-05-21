class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        """
        To solve this, we can observe that concatenating a substring of s and a substring of t 
        results in a combined string that is effectively a subsequence of the concatenated 
        string (s + t). However, the problem specifies substrings, which means we are looking 
        for the Longest Palindromic Subsequence (LPS) of (s + t) with one critical constraint: 
        the palindrome must contain at least one character from s and at least one character from t.
        """
        combined = s + t
        n = len(combined)
        m = len(s)
        
        # dp[i][j] will store the length of the longest palindromic subsequence in combined[i:j+1]
        dp = [[0] * n for _ in range(n)]
        max_len = 0
        
        # Initialize the DP table for single characters
        for i in range(n):
            dp[i][i] = 1
            
        # Fill the DP table
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if combined[i] == combined[j]:
                    dp[i][j] = dp[i + 1][j - 1] + 2
                    # If the matching characters come from different strings (one from s, one from t)
                    # then this is a valid candidate for our specific problem.
                    if i < m <= j:
                        max_len = max(max_len, dp[i][j])
                else:
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])
                    
        return max_len