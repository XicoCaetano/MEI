from typing import List

class Solution:
    def minimumCost(self, nums: List[int], cost: List[int], k: int) -> int:
        n = len(nums)
        prefix_nums = [0] * (n + 1)
        prefix_cost = [0] * (n + 1)
        
        for i in range(n):
            prefix_nums[i + 1] = prefix_nums[i] + nums[i]
            prefix_cost[i + 1] = prefix_cost[i] + cost[i]
        
        INF = 10**18
        dp = [INF] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            for j in range(i):
                total_nums = prefix_nums[i] - prefix_nums[j]
                segment_cost = prefix_cost[i] - prefix_cost[j]
                dp[i] = min(dp[i], dp[j] + (total_nums + k * (j // (j + 1))) * segment_cost)  # j//(j+1) = 0 for j=0, 1 for j>=1, but we need the number of subarrays before
        
        # Correct approach: We need the index of the subarray (starting from 1)
        # Let's recompute properly with the subarray count
        dp = [INF] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            for j in range(i):
                total_nums = prefix_nums[i] - prefix_nums[j]
                segment_cost = prefix_cost[i] - prefix_cost[j]
                # Number of subarrays before = number of cuts made before i
                # This equals (j>0) ? 1 + (some count) : 0
                # Actually, we need the index i (1-based) of the current subarray
                # If we split at j, then the new subarray is subarray # (count of subarrays before) + 1
                # Let's track the number of subarrays separately
                pass
        
        # Better: dp[i][s] = min cost for first i elements ending with s subarrays
        dp = [[INF] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(n + 1):
            for s in range(n + 1):
                if i < n and dp[i][s] < INF:
                    for t in range(i + 1, n + 1):
                        total_nums = prefix_nums[t] - prefix_nums[i]
                        segment_cost = prefix_cost[t] - prefix_cost[i]
                        new_s = s + 1
                        dp[t][new_s] = min(dp[t][new_s], dp[i][s] + (total_nums + k * new_s) * segment_cost)
        
        min_cost = INF
        for s in range(1, n + 1):
            min_cost = min(min_cost, dp[n][s])
        
        return min_cost
