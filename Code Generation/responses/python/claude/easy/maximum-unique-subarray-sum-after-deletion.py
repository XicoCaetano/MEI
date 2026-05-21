from typing import List

class Solution:
    def maxSum(self, nums: List[int]) -> int:
        # Keep only positive unique values (duplicates don't help)
        seen = set()
        total = 0
        for n in nums:
            if n > 0 and n not in seen:
                seen.add(n)
                total += n
        return total if total > 0 else max(nums)