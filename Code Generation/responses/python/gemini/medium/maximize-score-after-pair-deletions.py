from typing import List

class Solution:
    def maxScore(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2:
            return 0
        
        if n % 2 == 1:
            min_rem = min(nums)
        else:
            min_rem = min(nums[i] + nums[i+1] for i in range(n - 1))
            
        return sum(nums) - min_rem