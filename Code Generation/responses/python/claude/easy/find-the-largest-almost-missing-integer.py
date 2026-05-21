from typing import List
from collections import defaultdict

class Solution:
    def largestInteger(self, nums: List[int], k: int) -> int:
        count = defaultdict(set)
        for i in range(len(nums) - k + 1):
            for x in set(nums[i:i+k]):
                count[x].add(i)
        return max((x for x, s in count.items() if len(s) == 1), default=-1)