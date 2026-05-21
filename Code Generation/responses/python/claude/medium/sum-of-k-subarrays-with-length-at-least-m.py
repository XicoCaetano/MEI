from typing import List

class Solution:
    def maxSum(self, nums: List[int], k: int, m: int) -> int:
        n = len(nums)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + nums[i]
        
        def subarray_sum(l, r):  # inclusive
            return prefix[r + 1] - prefix[l]
        
        # dp[j][i] = max sum using j subarrays from nums[0..i-1]
        # We use i as "first i elements considered"
        NEG_INF = float('-inf')
        
        # dp[j][i]: max sum picking j non-overlapping subarrays each of length >= m
        # from nums[0..i-1]
        # Transition: either we don't use nums[i-1] in any new subarray ending at i,
        # or we pick a subarray ending at index i-1 with length l >= m
        
        # dp[j][i] = max(dp[j][i-1], max over l>=m of (dp[j-1][i-l] + sum(i-l..i-1)))
        
        dp = [[NEG_INF] * (n + 1) for _ in range(k + 1)]
        dp[0][0] = 0
        for i in range(1, n + 1):
            dp[0][i] = 0
        
        for j in range(1, k + 1):
            # For each i, we need max over l in [m, i-...] of dp[j-1][i-l] + prefix[i] - prefix[i-l]
            # = prefix[i] + max over l>=m of (dp[j-1][i-l] - prefix[i-l])
            # Let t = i - l, so t ranges from 0 to i-m
            # = prefix[i] + max over t in [0, i-m] of (dp[j-1][t] - prefix[t])
            
            best = NEG_INF  # max of dp[j-1][t] - prefix[t] for t in [0, i-m]
            
            for i in range(1, n + 1):
                # Update best with t = i - m (when we've moved far enough)
                t = i - m
                if t >= 0 and dp[j-1][t] != NEG_INF:
                    best = max(best, dp[j-1][t] - prefix[t])
                
                # Option 1: don't end a subarray at position i
                dp[j][i] = dp[j][i-1]
                
                # Option 2: end a subarray at position i (1-indexed, so at nums[i-1])
                if best != NEG_INF:
                    dp[j][i] = max(dp[j][i], prefix[i] + best)
        
        return dp[k][n]