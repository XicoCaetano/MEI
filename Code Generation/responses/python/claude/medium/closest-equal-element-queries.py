from typing import List
from collections import defaultdict

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        positions = defaultdict(list)
        for i, v in enumerate(nums):
            positions[v].append(i)
        
        def min_circular_dist(i, j):
            d = abs(i - j)
            return min(d, n - d)
        
        def nearest_dist(idx, pos_list):
            # Binary search for closest index in sorted pos_list
            import bisect
            pos = bisect.bisect_left(pos_list, idx)
            best = float('inf')
            # Check neighbors in the list
            for p in [pos - 1, pos, pos + 1]:
                if 0 <= p < len(pos_list) and pos_list[p] != idx:
                    best = min(best, min_circular_dist(idx, pos_list[p]))
            return best if best != float('inf') else -1
        
        result = []
        for q in queries:
            val = nums[q]
            pos_list = positions[val]
            if len(pos_list) == 1:
                result.append(-1)
            else:
                result.append(nearest_dist(q, pos_list))
        
        return result