from typing import List

class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        
        def can_zero(k):
            # Use difference array to track max decrements possible at each index
            diff = [0] * (n + 1)
            for i in range(k):
                l, r, val = queries[i]
                diff[l] += val
                diff[r + 1] -= val
            
            curr = 0
            for i in range(n):
                curr += diff[i]
                if curr < nums[i]:
                    return False
            return True
        
        if can_zero(0):
            return 0
        
        lo, hi = 1, len(queries)
        if not can_zero(hi):
            return -1
        
        while lo < hi:
            mid = (lo + hi) // 2
            if can_zero(mid):
                hi = mid
            else:
                lo = mid + 1
        
        return lo