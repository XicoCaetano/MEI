# === IMPORTS GERAIS (do dataset) ===
import random
import functools
import collections
import string
import math
import datetime

from typing import *
from functools import *
from collections import *
from itertools import *
from heapq import *
from bisect import *
from string import *
from operator import *
from math import *

inf = float('inf')

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def list_node(values: list):
    if not values:
        return None
    head = ListNode(values[0])
    p = head
    for val in values[1:]:
        node = ListNode(val)
        p.next = node
        p = node
    return head

def is_same_list(p1, p2):
    if p1 is None and p2 is None:
        return True
    if not p1 or not p2:
        return False
    return p1.val == p2.val and is_same_list(p1.next, p2.next)

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def tree_node(values: list):
    if not values:
        return None
    root = TreeNode(values[0])
    i = 1
    queue = deque()
    queue.append(root)
    while queue:
        node = queue.popleft()
        if i < len(values) and values[i] is not None:
            node.left = TreeNode(values[i])
            queue.append(node.left)
        i += 1
        if i < len(values) and values[i] is not None:
            node.right = TreeNode(values[i])
            queue.append(node.right)
        i += 1
    return root

def is_same_tree(p, q):
    if not p and not q:
        return True
    elif not p or not q:
        return False
    elif p.val != q.val:
        return False
    else:
        return is_same_tree(p.left, q.left) and is_same_tree(p.right, q.right)


# === MODEL RESPONSE ===
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

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(s = "0100",queries = [[0, 3], [0, 2], [1, 3], [2, 3]]) == [4, 3, 1, 1]
    assert candidate(s = "01",queries = [[0, 1]]) == [1]
    assert candidate(s = "01010",queries = [[0, 3], [1, 4], [1, 3]]) == [4, 4, 2]
    assert candidate(s = "1000100",queries = [[1, 5], [0, 6], [0, 4]]) == [6, 7, 2]
    assert candidate(s = "111111111111111111111111111111111111111111111111",queries = [[0, 39], [1, 38], [2, 37], [3, 36], [4, 35], [5, 34], [6, 33], [7, 32], [8, 31], [9, 30]]) == [48, 48, 48, 48, 48, 48, 48, 48, 48, 48]
    assert candidate(s = "11111111111111111",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [17, 17, 17, 17, 17]
    assert candidate(s = "10000000010000000001000000001",queries = [[0, 20], [5, 15], [10, 19]]) == [21, 14, 4]
    assert candidate(s = "000000000000000000000000000000000000000000000000",queries = [[0, 39], [1, 38], [2, 37], [3, 36], [4, 35], [5, 34], [6, 33], [7, 32], [8, 31], [9, 30]]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(s = "11001100110011001100110011",queries = [[0, 20], [5, 15], [0, 9], [10, 19], [15, 25]]) == [18, 18, 18, 18, 18]
    assert candidate(s = "111100001111000011110000",queries = [[0, 23], [4, 19], [5, 18], [6, 17], [7, 16], [8, 15], [9, 14], [10, 13], [11, 12]]) == [20, 20, 19, 18, 17, 12, 12, 12, 12]
    assert candidate(s = "1001001001001001001001001",queries = [[0, 24], [2, 22], [3, 21], [4, 20], [5, 19], [6, 18], [7, 17], [8, 16], [9, 15], [10, 14], [11, 13]]) == [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 11]
    assert candidate(s = "00101010101010101010",queries = [[0, 9], [5, 15], [10, 19]]) == [12, 11, 11]
    assert candidate(s = "10101010101010101010101010",queries = [[0, 25], [1, 24], [2, 23], [3, 22], [4, 21]]) == [15, 15, 15, 15, 15]
    assert candidate(s = "101010101010101010101010101010101010101010101010101010101010",queries = [[0, 59], [1, 58], [2, 57], [3, 56], [4, 55], [5, 54], [6, 53], [7, 52], [8, 51], [9, 50]]) == [32, 32, 32, 32, 32, 32, 32, 32, 32, 32]
    assert candidate(s = "111000111000111",queries = [[0, 14], [1, 13], [2, 12], [3, 11], [4, 10]]) == [15, 15, 15, 15, 13]
    assert candidate(s = "000011110000111100001111",queries = [[0, 23], [4, 19], [5, 18], [6, 17], [7, 16], [8, 15], [9, 14], [10, 13], [11, 12]]) == [20, 20, 19, 18, 17, 12, 12, 12, 12]
    assert candidate(s = "111000111000",queries = [[0, 11], [3, 8], [4, 7], [5, 6]]) == [12, 6, 6, 6]
    assert candidate(s = "01010101010101010101010101010101",queries = [[0, 15], [15, 30], [0, 29]]) == [18, 18, 18]
    assert candidate(s = "10101010101010101010",queries = [[0, 19], [1, 18], [2, 17], [3, 16], [4, 15], [5, 14], [6, 13], [7, 12], [8, 11], [9, 10]]) == [12, 12, 12, 12, 12, 12, 12, 12, 12, 10]
    assert candidate(s = "1001001001001001001",queries = [[0, 18], [1, 17], [2, 16], [5, 13], [3, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "11110000111100001111",queries = [[0, 9], [5, 15], [10, 19]]) == [12, 19, 12]
    assert candidate(s = "1010101010",queries = [[0, 9], [1, 8], [2, 7], [3, 6]]) == [7, 7, 7, 7]
    assert candidate(s = "0000011111000001111100000111110000011111",queries = [[0, 9], [10, 19], [20, 29], [30, 39], [0, 39]]) == [20, 20, 20, 20, 30]
    assert candidate(s = "1100001100011110001000000011001",queries = [[5, 15], [2, 20], [0, 30], [10, 25]]) == [16, 19, 22, 22]
    assert candidate(s = "00000100000100000",queries = [[0, 14], [1, 13], [2, 12], [5, 10], [3, 8]]) == [12, 11, 10, 2, 7]
    assert candidate(s = "00000000000000000",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [0, 0, 0, 0, 0]
    assert candidate(s = "0101010101010101010",queries = [[0, 18], [1, 17], [2, 16], [5, 13], [3, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "000100010001000100010001000100010001000100010001000100010001",queries = [[0, 59], [1, 58], [2, 57], [3, 56], [4, 55], [5, 54], [6, 53], [7, 52], [8, 51], [9, 50]]) == [21, 21, 21, 21, 21, 21, 21, 21, 21, 21]
    assert candidate(s = "10101010101010101",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "0101010101",queries = [[0, 9], [1, 8], [2, 7], [3, 6]]) == [7, 7, 7, 7]
    assert candidate(s = "01010101010101010101010101",queries = [[0, 25], [1, 24], [2, 23], [3, 22], [4, 21]]) == [15, 15, 15, 15, 15]
    assert candidate(s = "1100110011",queries = [[0, 9], [1, 8], [2, 7], [3, 6], [4, 5]]) == [10, 10, 10, 8, 6]
    assert candidate(s = "1001001001",queries = [[0, 9], [1, 8], [2, 7], [3, 6], [4, 5]]) == [8, 8, 7, 4, 4]
    assert candidate(s = "1001001001001001001",queries = [[0, 18], [1, 17], [2, 16], [3, 15], [4, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "0000000000",queries = [[0, 9], [2, 7], [4, 6]]) == [0, 0, 0]
    assert candidate(s = "1111111111",queries = [[0, 9], [2, 7], [4, 6]]) == [10, 10, 10]
    assert candidate(s = "110001100110001",queries = [[0, 14], [1, 13], [2, 12], [5, 10], [3, 8]]) == [12, 12, 12, 7, 11]
    assert candidate(s = "0000011111000001111100000",queries = [[0, 24], [1, 23], [2, 22], [3, 21], [4, 20], [5, 19], [6, 18], [7, 17], [8, 16], [9, 15]]) == [20, 19, 18, 17, 16, 10, 10, 10, 10, 10]
    assert candidate(s = "100100100100100",queries = [[0, 14], [1, 13], [2, 12], [3, 11], [4, 10], [5, 9]]) == [9, 9, 9, 9, 9, 8]
    assert candidate(s = "1001001001001",queries = [[0, 12], [2, 9], [3, 8], [4, 7], [5, 6]]) == [9, 9, 9, 8, 5]
    assert candidate(s = "1000000001",queries = [[1, 8], [0, 9], [2, 7], [3, 6]]) == [2, 2, 2, 2]
    assert candidate(s = "0000011110001110000",queries = [[0, 18], [1, 17], [2, 16], [3, 15], [4, 14], [5, 13]]) == [15, 14, 13, 12, 11, 7]
    assert candidate(s = "00110011001100110",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [12, 12, 12, 11, 12]


# === INVOCATION ===
check(Solution().maxActiveSectionsAfterTrade)
print("All tests passed")
