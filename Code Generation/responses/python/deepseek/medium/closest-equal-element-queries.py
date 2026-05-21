from typing import List
from collections import defaultdict
import bisect

class Solution:
    def solveQueries(self, nums: List[int], queries: List[int]) -> List[int]:
        n = len(nums)
        
        # Group indices by their values
        value_to_indices = defaultdict(list)
        for i, val in enumerate(nums):
            value_to_indices[val].append(i)
        
        # For each value, create a list of indices and store for quick lookup
        # We'll also duplicate the list to handle circular distances easily
        for val in value_to_indices:
            indices = value_to_indices[val]
            # If there's only one occurrence, we can handle it directly
            if len(indices) == 1:
                value_to_indices[val] = indices
            else:
                # Duplicate the list to handle wrap-around
                duplicated = indices + [idx + n for idx in indices]
                value_to_indices[val] = duplicated
        
        result = []
        
        for q_idx in queries:
            val = nums[q_idx]
            indices = value_to_indices[val]
            
            if len(indices) <= 1:
                # Only one occurrence (original length before duplication)
                original_len = len(indices)
                if original_len < 2:
                    result.append(-1)
                else:
                    # Actually this case shouldn't happen if we duplicated correctly
                    # But to be safe, we'll handle it
                    result.append(-1)
                continue
            
            # Find the position in the duplicated list
            # We need to find the two closest occurrences (one before, one after)
            # Since indices is duplicated for circular handling
            
            # Find the index of q_idx in the original part of the duplicated list
            # But we need to find it in the duplicated version
            # The indices list for values with multiple occurrences is duplicated
            # We know that q_idx is in the original first half of the duplicated list
            # because original indices are all < n
            
            # We can binary search for q_idx in the duplicated list
            pos = bisect.bisect_left(indices, q_idx)
            
            # Get previous and next indices (next is at pos+1, previous is at pos-1)
            # Since it's duplicated, previous and next will give correct distances
            prev_idx = indices[pos - 1] if pos > 0 else indices[-1] - n
            next_idx = indices[pos + 1] if pos + 1 < len(indices) else indices[0] + n
            
            # Calculate distances (circular)
            # For previous: since indices are sorted and may be in different parts
            # If prev_idx > q_idx (meaning it's from the duplicated part), subtract n
            if prev_idx > q_idx:
                prev_idx -= n
            dist_prev = abs(q_idx - prev_idx)
            
            # For next: if next_idx is from duplicated part, subtract n for actual distance
            if next_idx >= n:
                next_dist = next_idx - n - q_idx
            else:
                next_dist = next_idx - q_idx
            if next_dist < 0:
                next_dist += n
            
            min_dist = min(dist_prev, next_dist)
            result.append(min_dist)
        
        return result