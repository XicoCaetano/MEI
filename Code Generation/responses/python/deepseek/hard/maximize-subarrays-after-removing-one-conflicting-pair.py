from typing import List
import sys

class Solution:
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:
        # For each position, track the nearest left and right conflicting pairs
        # We'll use an approach with segment tree to handle ranges
        
        # First, for each index i, we want to know the nearest left conflict end and right conflict start
        # But careful: we have multiple conflicting pairs
        
        # Convert conflicting pairs to a more manageable form
        conflicts = []
        for a, b in conflictingPairs:
            if a > b:
                a, b = b, a
            conflicts.append((a, b))
        
        # For each position, track which conflicts affect it
        # We'll compute for each position the closest left and right constraint
        
        # For each index, we want to know:
        # left_limit[i] = the smallest index such that subarray [j, i] is invalid for some conflict
        # but we need to be more precise
        
        # Alternative approach: For each conflict (l, r), it disallows subarrays that contain both
        # A subarray [i, j] contains both l and r iff i <= l and j >= r
        # So the number of valid subarrays = total - sum over conflicts of (overlap counts)
        # But with removal of one conflict, we want to maximize valid subarrays
        
        # Total subarrays = n*(n+1)//2
        total = n * (n + 1) // 2
        
        # For each conflict (l, r), the number of subarrays that contain both is: l * (n - r + 1)
        # Wait, careful: For subarray to contain both l and r, start must be <= l, end must be >= r
        # So count = l * (n - r + 1)
        # But we need to handle overlapping conflicts carefully
        
        # We want to find which conflict to remove to maximize valid subarrays
        # Invalid subarrays = union of subarrays that contain any conflict
        
        # Let's compute for each position, the earliest start that would make subarray invalid
        # We can do this with a sweep line
        
        # For each end position j, the earliest i such that [i, j] is valid is:
        # i = min(start where no conflict fully inside [i, j])
        # Actually, [i, j] is invalid if there exists conflict (l, r) with i <= l and r <= j
        
        # So for each j, let left_limit[j] = max(1, max(l+1 for conflicts with r <= j))
        # Then valid subarrays ending at j = j - left_limit[j] + 1
        
        # But we need to remove one conflict and see the improvement
        
        # Compute base without removing any conflict
        left_limit_original = [1] * (n + 1)
        # We'll process conflicts sorted by r
        for r in range(1, n + 1):
            # For current r, find all conflicts with that r
            left_limit_original[r] = left_limit_original[r-1]
            for l, r2 in conflicts:
                if r2 == r:
                    left_limit_original[r] = max(left_limit_original[r], l + 1)
        
        valid_count_original = 0
        for j in range(1, n + 1):
            valid_count_original += j - left_limit_original[j] + 1
        
        # Now we want to see which conflict to remove
        # Removing conflict (l0, r0) means for positions >= r0, left_boundary might decrease
        # For each conflict, compute how many new valid subarrays we gain if we remove it
        
        # For each end j, if we remove conflict (l0, r0), left_limit[j] might become lower if normally
        # it was limited by l0+1 when r0 <= j
        # Actually, original left_limit[j] = max(1, max(l+1 for conflicts with r <= j))
        # After removing (l0, r0), new left_limit[j] = max(1, max(l+1 for conflicts with r <= j and r != r0, or if r0 <= j and l0+1 was the max))
        
        # We'll compute for each position, what's the second best constraint
        best = [0] * (n + 1)
        second_best = [0] * (n + 1)
        source_best = [0] * (n + 1)  # which conflict gave the best
        
        for r in range(1, n + 1):
            # Start from previous
            best[r] = best[r-1]
            second_best[r] = second_best[r-1]
            source_best[r] = source_best[r-1]
            
            for l, r2 in conflicts:
                if r2 == r:
                    val = l + 1
                    if val > best[r]:
                        second_best[r] = best[r]
                        best[r] = val
                        source_best[r] = (l, r2)
                    elif val > second_best[r]:
                        second_best[r] = val
        
        # Now for each conflict, compute gain
        gain = [0] * len(conflicts)
        
        for k, (l0, r0) in enumerate(conflicts):
            # For each j >= r0, left_limit[j] was originally best[j]
            # If best[j] came from our conflict, after removal it becomes second_best[j]
            # Otherwise, no change
            total_gain = 0
            # We need to process continuous ranges
            j = r0
            while j <= n:
                # Find the segment where source_best[j] == (l0, r0)
                if source_best[j] == (l0, r0):
                    new_limit = second_best[j]
                else:
                    new_limit = best[j]
                # Original valid count at j: j - best[j] + 1
                # New valid count: j - new_limit + 1
                original_valid = j - best[j] + 1
                new_valid = j - new_limit + 1
                gain[k] += (new_valid - original_valid)
                j += 1
        
        # Max valid count = original - min(gain) ??? Wait, gain is positive when new_limit is smaller
        # Actually, valid subarrays after removal = original - (reduction in valid subarrays)
        # But gain = new_valid - original_valid, so new_total = original_total + sum(gain)
        # So best new_total = original_total + max(gain)
        
        # But careful: gain[removed] is the improvement when removing that conflict
        # We want to maximize total valid subarrays = original_total + max(gain)
        
        max_gain = max(gain) if gain else 0
        
        # Wait, original_total might already be computed, but we need to ensure we're using the correct original
        # Let's recompute with the method above
        left_limit = [1] * (n + 1)
        for r in range(1, n + 1):
            left_limit[r] = left_limit[r-1]
            for l, r2 in conflicts:
                if r2 == r:
                    left_limit[r] = max(left_limit[r], l + 1)
        
        total_valid = 0
        for j in range(1, n + 1):
            total_valid += j - left_limit[j] + 1
        
        result = total_valid + max_gain
        return result