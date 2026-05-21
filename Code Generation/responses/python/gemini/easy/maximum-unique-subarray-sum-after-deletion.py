from typing import List

class Solution:
    def maxSum(self, nums: List[int]) -> int:
        unique_nums = set(nums)
        positive_sum = sum(x for x in unique_nums if x > 0)
        
        if positive_sum > 0:
            return positive_sum
        
        return max(unique_nums)