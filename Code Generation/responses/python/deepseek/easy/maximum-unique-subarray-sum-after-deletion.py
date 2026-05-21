from typing import List

class Solution:
    def maxSum(self, nums: List[int]) -> int:
        n = len(nums)
        max_sum = float('-inf')
        
        # Try every possible subarray
        for i in range(n):
            seen = set()
            current_sum = 0
            
            for j in range(i, n):
                if nums[j] in seen:
                    break
                seen.add(nums[j])
                current_sum += nums[j]
                max_sum = max(max_sum, current_sum)
        
        return max_sum