from typing import List
import collections

class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        counts = collections.defaultdict(int)
        n = len(nums)
        
        for i in range(n - k + 1):
            window_unique = set(nums[i:i+k])
            for num in window_unique:
                counts[num] += 1
                
        ans = -1
        for num, count in counts.items():
            if count == 1:
                ans = max(ans, num)
                
        return ans