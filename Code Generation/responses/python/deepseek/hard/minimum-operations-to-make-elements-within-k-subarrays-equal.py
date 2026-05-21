from typing import List
import heapq

class Solution:
    def minOperations(self, nums: List[int], x: int, k: int) -> int:
        n = len(nums)
        
        # Precompute cost to make each subarray of length x have all equal elements
        cost = []
        for i in range(n - x + 1):
            # We need to make nums[i:i+x] all equal to median
            window = sorted(nums[i:i+x])
            median = window[x//2]
            c = sum(abs(num - median) for num in window)
            cost.append(c)
        
        # DP: dp[i][j] = min operations to choose j disjoint subarrays from first i segments
        # where i segments from 0 to i-1 are processed, and we have taken j subarrays
        dp = [[float('inf')] * (k + 1) for _ in range(len(cost) + 2)]
        dp[0][0] = 0
        
        # For each segment position
        for i in range(len(cost)):
            # Copy previous row for skipping
            for j in range(k + 1):
                dp[i+1][j] = min(dp[i+1][j], dp[i][j])
            
            # Take segment i if possible
            for j in range(k):
                if dp[i][j] != float('inf'):
                    next_idx = i + x  # because segments must be non-overlapping (length x)
                    if next_idx <= len(cost):
                        dp[next_idx][j+1] = min(dp[next_idx][j+1], dp[i][j] + cost[i])
        
        return dp[len(cost)][k]