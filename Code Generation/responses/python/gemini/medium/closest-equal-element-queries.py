from typing import List
from collections import defaultdict
import bisect

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        # Map each value to a sorted list of indices where it appears
        val_to_indices = defaultdict(list)
        for i, val in enumerate(nums):
            val_to_indices[val].append(i)
            
        results = []
        for q_idx in queries:
            val = nums[q_idx]
            indices = val_to_indices[val]
            
            # If the element appears only once, there is no "other" index j
            if len(indices) <= 1:
                results.append(-1)
                continue
            
            # Find the position of q_idx in the sorted list of indices
            pos = bisect.bisect_left(indices, q_idx)
            
            # Potential neighbors in the sorted list (circularly)
            # Predecessor (left neighbor)
            left_neighbor = indices[(pos - 1) % len(indices)]
            # Successor (right neighbor)
            right_neighbor = indices[(pos + 1) % len(indices)]
            
            # Calculate circular distances
            # Distance = min(|i - j|, n - |i - j|)
            def get_circular_dist(i, j, n):
                linear_dist = abs(i - j)
                return min(linear_dist, n - linear_dist)
            
            dist_left = get_circular_dist(q_idx, left_neighbor, n)
            dist_right = get_circular_dist(q_idx, right_neighbor, n)
            
            results.append(min(dist_left, dist_right))
            
        return results