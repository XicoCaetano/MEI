from typing import List

class Solution:
    def minimumCost(self, nums: List[int], cost: List[int], k: int) -> int:
        n = len(nums)
        

        p_nums = [0] * (n + 1)
        p_cost = [0] * (n + 1)
        for i in range(n):
            p_nums[i + 1] = p_nums[i] + nums[i]
            p_cost[i + 1] = p_cost[i] + cost[i]
        
        dp = [float('inf')] * (n + 1)
        dp[0] = 0
        
        ans = float('inf')
        
        for j in range(1, n + 1):
            next_dp = [float('inf')] * (n + 1)
            for i in range(j, n + 1):
                multiplier = p_nums[i] + k * j
                for p in range(j - 1, i):
                    current_val = dp[p] + multiplier * (p_cost[i] - p_cost[p])
                    if current_val < next_dp[i]:
                        next_dp[i] = current_val
            
            dp = next_dp
            ans = min(ans, dp[n])
            
        return ans