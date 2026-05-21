import collections

class Solution:
    def minOperations(self, nums: list[int], x: int, k: int) -> int:
        n = len(nums)
        costs = []
        for i in range(n - x + 1):
            window = sorted(nums[i:i+x])
            median = window[x // 2]
            cost = sum(abs(v - median) for v in window)
            costs.append(cost)
        
        m = len(costs)
        dp = [[float('inf')] * (m + 1) for _ in range(k + 1)]
        
        for j in range(m + 1):
            dp[0][j] = 0
            
        for i in range(1, k + 1):
            for j in range(m):
                dp[i][j+1] = min(dp[i][j+1], dp[i][j])
                
                prev_idx = j - x + 1
                prev_cost = 0
                if i > 1:
                    if prev_idx > 0:
                        prev_cost = dp[i-1][prev_idx]
                    else:
                        prev_cost = float('inf')
                
                if prev_cost != float('inf'):
                    dp[i][j+1] = min(dp[i][j+1], prev_cost + costs[j])
                    
        return int(dp[k][m])