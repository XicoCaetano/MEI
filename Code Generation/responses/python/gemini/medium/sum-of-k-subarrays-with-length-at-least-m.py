from typing import List

class Solution:
    def maxSum(self, nums: List[int], k: int, m: int) -> int:
        n = len(nums)
        
        S = [0] * (n + 1)
        for i in range(n):
            S[i + 1] = S[i] + nums[i]
            
        prev_dp = [0] * (n + 1)
        
        for j in range(1, k + 1):
            new_dp = [float('-inf')] * (n + 1)
            max_val = float('-inf')
            
            for i in range(j * m, n + 1):
                p = i - m
                
                if prev_dp[p] != float('-inf'):
                    val = prev_dp[p] - S[p]
                    if val > max_val:
                        max_val = val
                        
                new_dp[i] = new_dp[i - 1]
                
                if max_val != float('-inf'):
                    current_sum = S[i] + max_val
                    if current_sum > new_dp[i]:
                        new_dp[i] = current_sum
                        
            prev_dp = new_dp
            
        return int(prev_dp[n])