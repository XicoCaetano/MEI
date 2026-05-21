from typing import List
from collections import defaultdict

class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        n = len(nums)
        freq = defaultdict(int)
        
        # Count frequency of each integer in all subarrays of size k
        for i in range(n - k + 1):
            subarray = nums[i:i + k]
            seen = set(subarray)  # Avoid counting duplicates in the same subarray
            for num in seen:
                freq[num] += 1
        
        # Find the largest integer that appears exactly once across all subarrays
        result = -1
        for num, count in freq.items():
            if count == 1:
                result = max(result, num)
        
        return result