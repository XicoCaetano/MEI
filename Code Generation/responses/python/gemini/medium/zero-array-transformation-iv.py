from typing import List

class Solution:
    def minZeroArray(self, nums: List[int], queries: List[List[int]]) -> int:
        n = len(nums)
        
        def check(k: int) -> bool:
            diff = [0] * (n + 1)
            for i in range(k):
                l, r, val = queries[i]
                diff[l] += val
                diff[r + 1] -= val
                
            capacity = 0
            for i in range(n):
                capacity += diff[i]
                if capacity < nums[i]:
                    return False
            return True

        left, right = 0, len(queries)
        ans = -1
        
        while left <= right:
            mid = (left + right) // 2
            if check(mid):
                ans = mid
                right = mid - 1
            else:
                left = mid + 1
                
        return ans