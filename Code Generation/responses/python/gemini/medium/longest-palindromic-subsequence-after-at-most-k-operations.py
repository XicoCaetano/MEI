import sys
from functools import cache

sys.setrecursionlimit(2000)

class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        @cache
        def dp(i: int, j: int, rem: int) -> int:
            if i > j:
                return 0
            if i == j:
                return 1
            
            res = dp(i + 1, j, rem)
            res2 = dp(i, j - 1, rem)
            if res2 > res:
                res = res2
            
            cost = abs(ord(s[i]) - ord(s[j]))
            cost = cost if cost <= 13 else 26 - cost
            
            if cost <= rem:
                res3 = 2 + dp(i + 1, j - 1, rem - cost)
                if res3 > res:
                    res = res3
                    
            return res

        return dp(0, len(s) - 1, k)