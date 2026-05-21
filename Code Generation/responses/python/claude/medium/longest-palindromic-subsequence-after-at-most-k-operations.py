from functools import lru_cache

class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        n = len(s)
        
        def char_dist(a, b):
            d = abs(ord(a) - ord(b))
            return min(d, 26 - d)
        
        @lru_cache(maxsize=None)
        def dp(i, j, rem):
            if i > j:
                return 0
            if i == j:
                return 1
            
            d = char_dist(s[i], s[j])
            
            if d <= rem:
                return 2 + dp(i + 1, j - 1, rem - d)
            
            return max(dp(i + 1, j, rem), dp(i, j - 1, rem))
        
        return dp(0, n - 1, k)