from typing import List

class Solution:
    def maxSum(self, nums: List[int], k: int, m: int) -> int:
        n = len(nums)
        
        # dp[i][j] = maximum sum using j subarrays considering first i elements
        # We need to handle the case where j subarrays are chosen, ending at position i or before
        # Let's use dp[i][j] = max sum using j subarrays from first i elements (i elements considered)
        # and we don't necessarily need to end at i
        
        # Initialize with -inf
        dp = [[float('-inf')] * (k + 1) for _ in range(n + 1)]
        
        # Base case: 0 subarrays, 0 sum
        for i in range(n + 1):
            dp[i][0] = 0
        
        # prefix sums for quick subarray sum calculation
        prefix_sums = [0] * (n + 1)
        for i in range(n):
            prefix_sums[i + 1] = prefix_sums[i] + nums[i]
        
        # For each position i (1-indexed), consider ending subarray at i
        for i in range(1, n + 1):
            # Option 1: skip current element
            for j in range(1, k + 1):
                dp[i][j] = max(dp[i][j], dp[i - 1][j])
            
            # Option 2: end a subarray at i
            # The subarray must have length >= m, so it can start at any position s where i - s + 1 >= m
            # That is s <= i - m + 1, and s >= 1
            if i >= m:
                # We need maximum of dp[s-1][j-1] + sum(nums[s-1:i]) for s from 1 to i - m + 1
                # sum(nums[s-1:i]) = prefix_sums[i] - prefix_sums[s-1]
                # So we need max over s: dp[s-1][j-1] - prefix_sums[s-1] + prefix_sums[i]
                
                # For each j, maintain the max of (dp[s-1][j-1] - prefix_sums[s-1]) for s <= i-m+1
                # Let's compute directly to avoid complexity
                for j in range(1, k + 1):
                    # Consider all possible start positions s for the subarray ending at i
                    # s ranges from 1 to i - m + 1
                    best = float('-inf')
                    for s in range(1, i - m + 2):
                        # s is 1-indexed, subarray nums[s-1:i] (0-indexed)
                        # We need s-1 elements before this subarray
                        # Number of subarrays used before = j-1
                        sum_sub = prefix_sums[i] - prefix_sums[s - 1]
                        if dp[s - 1][j - 1] != float('-inf'):
                            best = max(best, dp[s - 1][j - 1] + sum_sub)
                    if best != float('-inf'):
                        dp[i][j] = max(dp[i][j], best)
        
        # We want the maximum sum using exactly k subarrays from all n elements
        return dp[n][k]