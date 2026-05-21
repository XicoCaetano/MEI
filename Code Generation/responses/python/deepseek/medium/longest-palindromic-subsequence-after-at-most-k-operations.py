class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        n = len(s)
        # dp[l][r][ops] = max length of palindromic subsequence from s[l:r+1] with at most ops operations
        dp = [[[0] * (k + 1) for _ in range(n)] for _ in range(n)]
        
        # Base case: single character subsequence
        for i in range(n):
            for ops in range(k + 1):
                dp[i][i][ops] = 1
        
        # Fill the table for lengths 2 to n
        for length in range(2, n + 1):
            for l in range(n - length + 1):
                r = l + length - 1
                for ops in range(k + 1):
                    # Option 1: skip s[l]
                    if l + 1 <= r:
                        dp[l][r][ops] = max(dp[l][r][ops], dp[l + 1][r][ops])
                    # Option 2: skip s[r]
                    if l <= r - 1:
                        dp[l][r][ops] = max(dp[l][r][ops], dp[l][r - 1][ops])
                    
                    # Option 3: include both s[l] and s[r]
                    if l < r:
                        # Calculate minimum operations to make s[l] and s[r] equal
                        a = ord(s[l]) - ord('a')
                        b = ord(s[r]) - ord('a')
                        cost = min(abs(a - b), 26 - abs(a - b))
                        if ops >= cost:
                            if r - l == 1:  # Only two characters
                                dp[l][r][ops] = max(dp[l][r][ops], 2)
                            else:
                                dp[l][r][ops] = max(dp[l][r][ops], dp[l + 1][r - 1][ops - cost] + 2)
        
        return dp[0][n - 1][k]