from typing import List

class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        
        # Parse the string into runs of (char, start, end) inclusive
        runs = []
        i = 0
        while i < n:
            j = i
            while j < n and s[j] == s[i]:
                j += 1
            runs.append((s[i], i, j - 1))
            i = j
        
        # For each run index, store its info
        # We need to handle queries on substring s[l..r] augmented with '1' on both ends
        # 
        # The trade: pick a block of 1s surrounded by 0s, turn it to 0s,
        # then pick a block of 0s surrounded by 1s, turn it to 1s.
        # Net effect: we gain (zeros_block_size) - (ones_block_size) ones.
        # 
        # After augmentation t = '1' + s[l..r] + '1':
        # A valid trade requires pattern: ...1 [0+] [1+] [0+] 1...
        # where the middle [1+] is surrounded by zeros, and those zeros are surrounded by 1s.
        # We turn [1+] to 0s and then the combined [0+][0+] block to 1s.
        # Gain = (left_zeros + ones + right_zeros) - ones = left_zeros + right_zeros
        #
        # So for consecutive runs in the augmented string of pattern 0-block, 1-block, 0-block
        # (where surrounding context provides the required 1s), the gain = len(left_0) + len(right_0).
        #
        # We want to maximize: base_ones + max_gain
        # 
        # Strategy: precompute prefix sums for runs, then for each query binary search for
        # relevant runs and use sparse table / segment tree for range max of gains.
        
        # Build run index arrays
        run_char = [r[0] for r in runs]
        run_start = [r[1] for r in runs]
        run_end = [r[2] for r in runs]
        run_len = [r[2] - r[1] + 1 for r in runs]
        
        # prefix sum of 1s count by position (for base count)
        prefix_ones = [0] * (n + 1)
        for i in range(n):
            prefix_ones[i+1] = prefix_ones[i] + (1 if s[i] == '1' else 0)
        
        def ones_in_range(l, r):
            return prefix_ones[r+1] - prefix_ones[l]
        
        import bisect
        
        # For each run i that is '1' and has run i-1 and i+1 being '0',
        # the gain from trading this 1-block = run_len[i-1] + run_len[i+1] - run_len[i]
        # Wait: gain = left_zeros + right_zeros (we lose the ones block, gain left+right zeros converted to ones)
        # Actually net change in ones = (left_zeros + ones + right_zeros) - ones = left_zeros + right_zeros
        # But we need those zeros to be within the query range.
        
        # For a query [l, r], augmented string is '1' + s[l..r] + '1'
        # In terms of original runs within [l,r]:
        # The first and last runs might be partial. The augmented '1's serve as boundary.
        
        # Let's think of "gain entries": for each triple of consecutive runs (0-run, 1-run, 0-run)
        # in the original string, if this triple is fully contained in [l,r],
        # gain = left_0_len_clipped + right_0_len_clipped
        # But clipping happens at query boundaries.
        
        # This is complex. Let me think differently.
        # 
        # For augmented string, runs are: [1] + runs_within[l,r] + [1]
        # We need to find consecutive triple (0,1,0) in this augmented run list.
        # For full internal runs (not touching l or r boundary), gain = full lengths.
        # For boundary runs, their effective length is clipped.
        #
        # Key insight: the gain for a trade on runs (i-1, i, i+1) where run i is '1':
        # effective_left_zeros = min(run_end[i-1], r) - max(run_start[i-1], l) + 1
        #   (but run i-1 must be '0', and it must be adjacent with a '1' to its left,
        #    which is either another run or the augmented '1')
        # effective_right_zeros = similarly
        #
        # Actually the gain = effective_left_zeros + effective_right_zeros
        # (we're converting left_zeros + ones_block + right_zeros all to ones, net gain = left+right zeros)
        
        # Let me enumerate all valid (i-1, i, i+1) triples where run_char[i]='1'
        # and run_char[i-1]='0' and run_char[i+1]='0' (or boundary augmented '1')
        # 
        # For a query [l, r]:
        # - runs that overlap with [l,r]
        # - find the first and last run indices overlapping
        # - For each "middle" 1-run at position i in runs list, check if triple fits
        
        # Given constraints 1e5 x 1e5, we need O(n log n + q log n).
        
        # Approach: 
        # For each valid trade triple (runs j, j+1, j+2) where run_char[j+1]='1',
        # run_char[j]='0', run_char[j+2]='0':
        #   This trade is "usable" in query [l,r] if the 1-run and its surrounding context
        #   fall within [l,r] considering augmented boundaries.
        #
        # The gain for query [l,r] using this triple:
        #   left_gain = min(run_end[j], r) - max(run_start[j], l) + 1
        #   right_gain = min(run_end[j+2], r) - max(run_start[j+2], l) + 1
        #   total_gain = left_gain + right_gain
        #
        # This is valid only if the 1-block (run j+1) is entirely in [l,r]:
        #   run_start[j+1] >= l and run_end[j+1] <= r
        # AND there's a '1' to the left of the left-zero block within augmented string:
        #   either run_start[j] > l (so augmented '1' is to the left), 
        #   OR j > 0 and run_char[j-1]='1' and run_start[j] <= run_end[j] (there's a '1' run to left)
        #   -- but since run_char[j]='0', the run to its left in original is '1' if j>0
        #   -- and within query, if run_start[j] >= l then that '1' context comes from augmented
        #   -- if run_start[j] < l then the portion of run j in [l,r] starts at l, 
        #      and to its left is the augmented '1'. So always valid as long as 1-block is in [l,r].
        # Similarly for right side.
        #
        # So: gain(j, l, r) = clipped_len(j, l, r) + clipped_len(j+2, l, r)
        # where clipped_len(k, l, r) = min(run_end[k], r) - max(run_start[k], l) + 1
        #
        # We want max gain over all valid j where run_start[j+1] >= l and run_end[j+1] <= r.
        
        # For fixed l, r:
        # gain = (min(run_end[j],r) - max(run_start[j],l) + 1) + (min(run_end[j+2],r) - max(run_start[j+2],l) + 1)
        #
        # When j's run is entirely within [l,r] (run_start[j] >= l):
        #   left part = run_len[j]
        # When j's run starts before l:
        #   left part = run_end[j] - l + 1
        #
        # Similarly for j+2.
        #
        # For runs entirely inside [l,r], gain = run_len[j] + run_len[j+2] (constant per triple)
        # The only "boundary" effects are for the first and last zero-runs in the query.
        
        # Let me build for each valid triple index (centered at run index i, 1-indexed in runs):
        # triple_gain[i] = run_len[i-1] + run_len[i+1]  (for runs i-1, i, i+1)
        # This is the gain when both zero runs are fully inside query.
        
        # For a query [l, r]:
        # 1. Find all triples (i-1, i, i+1) where run_start[i] >= l and run_end[i] <= r
        # 2. For most of them, gain = run_len[i-1] + run_len[i+1]
        # 3. For the leftmost valid triple, left zero run might be clipped
        # 4. For the rightmost valid triple, right zero run might be clipped
        
        # Build sparse table on triple_gain for range max queries.
        
        # First, identify all valid triples
        # A triple centered at run index i is valid if:
        #   run_char[i] == '1', run_char[i-1] == '0', run_char[i+1] == '0'
        # (i ranges from 1 to len(runs)-2)
        
        # For a query [l, r]:
        # runs that have 1-block fully inside: run_start[i] >= l and run_end[i] <= r
        # Use binary search on run_start and run_end arrays.
        
        # Let's store valid triple centers
        valid_centers = []  # run indices i where triple (i-1,i,i+1) is valid
        for i in range(1, len(runs)-1):
            if run_char[i] == '1' and run_char[i-1] == '0' and run_char[i+1] == '0':
                valid_centers.append(i)
        
        if not valid_centers:
            # No valid trades possible anywhere
            return [ones_in_range(l, r) for l, r in queries]
        
        vc = valid_centers
        vc_start = [run_start[i] for i in vc]  # start of 1-block
        vc_end = [run_end[i] for i in vc]       # end of 1-block
        vc_gain = [run_len[i-1] + run_len[i+1] for i in vc]  # full gain
        
        # Sparse table for range max of vc_gain
        import math
        m = len(vc)
        LOG = max(1, m.bit_length())
        sparse = [[0]*m for _ in range(LOG)]
        sparse[0] = vc_gain[:]
        for k in range(1, LOG):
            for j in range(m - (1<<k) + 1):
                sparse[k][j] = max(sparse[k-1][j], sparse[k-1][j + (1<<(k-1))])
        
        def range_max(l_idx, r_idx):
            if l_idx > r_idx:
                return -1
            k = (r_idx - l_idx + 1).bit_length() - 1
            return max(sparse[k][l_idx], sparse[k][r_idx - (1<<k) + 1])
        
        results = []
        for l, r in queries:
            base = ones_in_range(l, r)
            
            # Find valid centers where 1-block is fully in [l, r]
            # vc_start[idx] >= l and vc_end[idx] <= r
            lo = bisect.bisect_left(vc_start, l)
            hi = bisect.bisect_right(vc_end, r) - 1
            # But we need both conditions simultaneously
            # Since valid centers alternate (0,1,0 pattern), vc_start is sorted
            # and for each, vc_end[i] > vc_start[i], vc_end is also sorted
            # Find range where vc_start >= l: indices [lo, m-1]
            # Find range where vc_end <= r: indices [0, hi]
            # Intersection: [lo, hi]
            
            if lo > hi:
                results.append(base)
                continue
            
            # Check boundary effects:
            # For the leftmost valid center in [lo, hi]:
            #   its left zero run (run index vc[lo]-1) might be partially outside [l,r]
            #   but since vc_start[lo] >= l, the 1-block starts at or after l
            #   the left zero run ends at run_end[vc[lo]-1] = run_start[vc[lo]] - 1
            #   and starts at run_start[vc[lo]-1]
            #   clipped left gain = run_start[vc[lo]] - 1 - max(run_start[vc[lo]-1], l) + 1
            #                     = run_start[vc[lo]] - max(run_start[vc[lo]-1], l)
            # Similarly for rightmost.
            
            # Get max gain from "interior" triples (no clipping needed if both zero runs fully inside)
            # A triple's left zero run is fully inside if run_start[i-1] >= l
            # A triple's right zero run is fully inside if run_end[i+1] <= r
            
            # For simplicity, compute:
            # max_gain = max over [lo, hi] of adjusted gain
            # 
            # For center idx in vc (position pos in vc array):
            #   left_z_start = run_start[vc[pos]-1]
            #   left_z_end = run_end[vc[pos]-1] = run_start[vc[pos]] - 1
            #   right_z_start = run_start[vc[pos]+1] = run_end[vc[pos]] + 1  
            #   right_z_end = run_end[vc[pos]+1]
            #
            #   adjusted_left = run_start[vc[pos]] - max(left_z_start, l)  
            #   adjusted_right = min(right_z_end, r) - run_end[vc[pos]]
            #   adjusted_gain = adjusted_left + adjusted_right

            # The adjustment only matters for leftmost (left side clipping) and 
            # rightmost (right side clipping) triples.
            # For interior ones, gain = vc_gain[pos].
            
            # Get interior range max
            best = range_max(lo, hi)
            
            # Check leftmost with potential left clipping
            pos = lo
            i = vc[pos]
            left_z_start = run_start[i-1]
            adj_left = run_start[i] - max(left_z_start, l)
            right_z_end = run_end[i+1]
            adj_right = min(right_z_end, r) - run_end[i]
            best = max(best, adj_left + adj_right)
            
            # Check rightmost with potential right clipping
            pos = hi
            i = vc[pos]
            left_z_start = run_start[i-1]
            adj_left = run_start[i] - max(left_z_start, l)
            right_z_end = run_end[i+1]
            adj_right = min(right_z_end, r) - run_end[i]
            best = max(best, adj_left + adj_right)
            
            results.append(base + best)
        
        return results