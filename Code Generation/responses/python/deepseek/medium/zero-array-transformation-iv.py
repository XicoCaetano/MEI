from typing import List

class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        def can_make_zero(k: int) -> bool:
            diff = [0] * (len(nums) + 1)
            for i in range(k):
                l, r, val = queries[i]
                diff[l] += val
                diff[r + 1] -= val
            
            curr = 0
            for i in range(len(nums)):
                curr += diff[i]
                if curr < nums[i]:
                    return False
            return True
        
        low, high = 0, len(queries)
        # Binary search for the minimal k
        while low < high:
            mid = (low + high) // 2
            if can_make_zero(mid):
                high = mid
            else:
                low = mid + 1
        
        if low == len(queries) and not can_make_zero(low):
            return -1
        return low