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

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(n = 7,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7]]) == 8
    assert candidate(n = 6,conflictingPairs = [[1, 3], [2, 4], [3, 5], [4, 6]]) == 12
    assert candidate(n = 6,conflictingPairs = [[1, 3], [3, 5], [2, 4], [4, 6]]) == 12
    assert candidate(n = 10,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]]) == 11
    assert candidate(n = 10,conflictingPairs = [[1, 10], [2, 9], [3, 8], [4, 7], [5, 6]]) == 39
    assert candidate(n = 10,conflictingPairs = [[1, 5], [2, 6], [3, 7], [4, 8], [5, 9], [6, 10]]) == 35
    assert candidate(n = 6,conflictingPairs = [[1, 2], [3, 4], [5, 6]]) == 12
    assert candidate(n = 5,conflictingPairs = [[1, 2], [2, 5], [3, 5]]) == 12
    assert candidate(n = 4,conflictingPairs = [[2, 3], [1, 4]]) == 9
    assert candidate(n = 6,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6]]) == 7
    assert candidate(n = 3,conflictingPairs = [[1, 2], [1, 3], [2, 3]]) == 4
    assert candidate(n = 3,conflictingPairs = [[1, 2], [2, 3]]) == 4
    assert candidate(n = 15,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15], [1, 15]]) == 16
    assert candidate(n = 10,conflictingPairs = [[1, 5], [2, 6], [3, 7], [4, 8], [5, 9], [6, 10], [1, 6], [2, 7], [3, 8], [4, 9]]) == 35
    assert candidate(n = 10,conflictingPairs = [[1, 10], [2, 9], [3, 8], [4, 7], [5, 6], [1, 6], [2, 7], [3, 8], [4, 9], [5, 10]]) == 37
    assert candidate(n = 10,conflictingPairs = [[1, 5], [5, 9], [2, 6], [6, 10], [3, 7], [4, 8], [1, 3], [2, 4], [5, 7], [6, 8], [1, 4], [2, 5], [3, 6], [4, 7], [5, 8], [6, 9], [7, 10]]) == 24
    assert candidate(n = 20,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15], [15, 16], [16, 17], [17, 18], [18, 19], [19, 20], [1, 20], [2, 19], [3, 18], [4, 17], [5, 16], [6, 15], [7, 14], [8, 13], [9, 12], [10, 11]]) == 21
    assert candidate(n = 20,conflictingPairs = [[1, 20], [2, 19], [3, 18], [4, 17], [5, 16], [6, 15], [7, 14], [8, 13], [9, 12], [10, 11], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [7, 9], [8, 10], [9, 11], [10, 12]]) == 75
    assert candidate(n = 9,conflictingPairs = [[1, 9], [2, 8], [3, 7], [4, 6], [5, 5], [1, 5], [2, 6], [3, 4], [7, 8]]) == 17
    assert candidate(n = 15,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15]]) == 16
    assert candidate(n = 20,conflictingPairs = [[1, 10], [10, 20], [1, 11], [11, 20], [1, 12], [12, 20], [1, 13], [13, 20], [1, 14], [14, 20], [1, 15], [15, 20], [1, 16], [16, 20], [1, 17], [17, 20], [1, 18], [18, 20], [1, 19], [19, 20]]) == 182
    assert candidate(n = 10,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [1, 10]]) == 11
    assert candidate(n = 15,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15], [1, 15]]) == 16
    assert candidate(n = 15,conflictingPairs = [[1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [7, 9], [8, 10], [9, 11], [10, 12], [11, 13], [12, 14], [13, 15], [1, 4], [2, 5], [3, 6], [4, 7], [5, 8], [6, 9], [7, 10], [8, 11], [9, 12], [10, 13], [11, 14], [12, 15]]) == 30
    assert candidate(n = 20,conflictingPairs = [[1, 10], [2, 9], [3, 8], [4, 7], [5, 6], [6, 5], [7, 4], [8, 3], [9, 2], [10, 1], [11, 20], [12, 19], [13, 18], [14, 17], [15, 16], [16, 15], [17, 14], [18, 13], [19, 12], [20, 11]]) == 85
    assert candidate(n = 20,conflictingPairs = [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10], [11, 12], [13, 14], [15, 16], [17, 18], [19, 20], [1, 20], [2, 19], [3, 18], [4, 17], [5, 16], [6, 15], [7, 14], [8, 13], [9, 12], [10, 11]]) == 32
    assert candidate(n = 20,conflictingPairs = [[1, 10], [10, 20], [1, 5], [5, 15], [1, 15], [15, 20], [1, 20]]) == 180
    assert candidate(n = 8,conflictingPairs = [[1, 2], [1, 3], [1, 4], [2, 3], [2, 4], [3, 4], [1, 5], [2, 5], [3, 5], [4, 5], [1, 6], [2, 6], [3, 6], [4, 6], [5, 6], [1, 7], [2, 7], [3, 7], [4, 7], [5, 7], [6, 7], [1, 8], [2, 8], [3, 8], [4, 8], [5, 8], [6, 8], [7, 8]]) == 9
    assert candidate(n = 50,conflictingPairs = [[1, 5], [5, 10], [10, 15], [15, 20], [20, 25], [25, 30], [30, 35], [35, 40], [40, 45], [45, 50]]) == 350
    assert candidate(n = 20,conflictingPairs = [[1, 20], [2, 19], [3, 18], [4, 17], [5, 16], [6, 15], [7, 14], [8, 13], [9, 12], [10, 11], [1, 10], [2, 11], [3, 12], [4, 13], [5, 14], [6, 15], [7, 16], [8, 17], [9, 18]]) == 126
    assert candidate(n = 12,conflictingPairs = [[1, 6], [2, 7], [3, 8], [4, 9], [5, 10], [6, 11], [7, 12]]) == 51
    assert candidate(n = 25,conflictingPairs = [[1, 5], [2, 6], [3, 7], [4, 8], [5, 9], [6, 10], [7, 11], [8, 12], [9, 13], [10, 14], [11, 15], [12, 16], [13, 17], [14, 18], [15, 19], [16, 20], [17, 21], [18, 22], [19, 23], [20, 24], [21, 25], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [7, 9], [8, 10], [9, 11], [10, 12], [11, 13], [12, 14], [13, 15], [14, 16], [15, 17], [16, 18], [17, 19], [18, 20], [19, 21], [20, 22], [21, 23], [22, 24], [23, 25]]) == 50
    assert candidate(n = 12,conflictingPairs = [[1, 12], [2, 11], [3, 10], [4, 9], [5, 8], [6, 7], [1, 6], [2, 7], [3, 8], [4, 9], [5, 10], [6, 11]]) == 48
    assert candidate(n = 10,conflictingPairs = [[1, 5], [2, 6], [3, 7], [4, 8], [5, 9], [6, 10], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [7, 9], [8, 10]]) == 20
    assert candidate(n = 50,conflictingPairs = [[1, 25], [2, 26], [3, 27], [4, 28], [5, 29], [6, 30], [7, 31], [8, 32], [9, 33], [10, 34], [11, 35], [12, 36], [13, 37], [14, 38], [15, 39], [16, 40], [17, 41], [18, 42], [19, 43], [20, 44], [21, 45], [22, 46], [23, 47], [24, 48], [25, 49], [26, 50]]) == 925
    assert candidate(n = 8,conflictingPairs = [[1, 8], [2, 7], [3, 6], [4, 5], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [1, 4], [2, 5], [3, 6], [4, 7], [5, 8]]) == 15
    assert candidate(n = 9,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9]]) == 10
    assert candidate(n = 12,conflictingPairs = [[1, 4], [2, 5], [3, 6], [4, 7], [5, 8], [6, 9], [7, 10], [8, 11], [9, 12]]) == 34
    assert candidate(n = 15,conflictingPairs = [[1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [1, 7], [1, 8], [1, 9], [1, 10], [1, 11], [1, 12], [1, 13], [1, 14], [1, 15]]) == 107
    assert candidate(n = 20,conflictingPairs = [[1, 20], [2, 19], [3, 18], [4, 17], [5, 16], [6, 15], [7, 14], [8, 13], [9, 12], [10, 11]]) == 129
    assert candidate(n = 100,conflictingPairs = [[1, 50], [50, 100], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]]) == 4244
    assert candidate(n = 8,conflictingPairs = [[1, 4], [2, 5], [3, 6], [4, 7], [5, 8], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7]]) == 17
    assert candidate(n = 10,conflictingPairs = [[1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [1, 7], [1, 8], [1, 9], [1, 10], [2, 3], [2, 4], [2, 5], [2, 6], [2, 7], [2, 8], [2, 9], [2, 10], [3, 4], [3, 5], [3, 6], [3, 7], [3, 8], [3, 9], [3, 10], [4, 5], [4, 6], [4, 7], [4, 8], [4, 9], [4, 10], [5, 6], [5, 7], [5, 8], [5, 9], [5, 10], [6, 7], [6, 8], [6, 9], [6, 10], [7, 8], [7, 9], [7, 10], [8, 9], [8, 10], [9, 10]]) == 11
    assert candidate(n = 15,conflictingPairs = [[1, 15], [2, 14], [3, 13], [4, 12], [5, 11], [6, 10], [7, 9], [1, 3], [2, 4], [5, 7]]) == 62
    assert candidate(n = 10,conflictingPairs = [[1, 10], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]]) == 11
    assert candidate(n = 15,conflictingPairs = [[1, 15], [2, 14], [3, 13], [4, 12], [5, 11], [6, 10], [7, 9], [1, 8], [2, 9], [3, 10], [4, 11], [5, 12], [6, 13], [7, 14]]) == 79
    assert candidate(n = 8,conflictingPairs = [[1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [1, 7], [1, 8]]) == 30
    assert candidate(n = 20,conflictingPairs = [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10], [11, 12], [13, 14], [15, 16], [17, 18], [19, 20], [1, 20], [2, 19], [3, 18], [4, 17], [5, 16], [6, 15], [7, 14], [8, 13], [9, 12], [10, 11]]) == 32
    assert candidate(n = 7,conflictingPairs = [[1, 2], [1, 3], [1, 4], [1, 5], [1, 6], [1, 7]]) == 23
    assert candidate(n = 18,conflictingPairs = [[1, 18], [2, 17], [3, 16], [4, 15], [5, 14], [6, 13], [7, 12], [8, 11], [9, 10], [1, 9], [2, 10], [3, 11], [4, 12], [5, 13], [6, 14], [7, 15], [8, 16]]) == 104
    assert candidate(n = 10,conflictingPairs = [[1, 10], [2, 9], [3, 8], [4, 7], [5, 6], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [7, 9]]) == 21
    assert candidate(n = 12,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [1, 12], [1, 11], [1, 10], [1, 9], [1, 8], [1, 7], [1, 6], [1, 5], [1, 4], [1, 3]]) == 13
    assert candidate(n = 15,conflictingPairs = [[1, 15], [2, 14], [3, 13], [4, 12], [5, 11], [6, 10], [7, 9]]) == 84
    assert candidate(n = 15,conflictingPairs = [[1, 5], [2, 6], [3, 7], [4, 8], [5, 9], [6, 10], [7, 11], [8, 12], [9, 13], [10, 14], [11, 15]]) == 55
    assert candidate(n = 25,conflictingPairs = [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10], [11, 12], [13, 14], [15, 16], [17, 18], [19, 20], [21, 22], [23, 24], [24, 25]]) == 40
    assert candidate(n = 20,conflictingPairs = [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10], [11, 12], [13, 14], [15, 16], [17, 18], [19, 20], [1, 10], [2, 11], [3, 12], [4, 13], [5, 14], [6, 15], [7, 16], [8, 17], [9, 18], [10, 19], [1, 20], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]]) == 29
    assert candidate(n = 20,conflictingPairs = [[1, 10], [2, 11], [3, 12], [4, 13], [5, 14], [6, 15], [7, 16], [8, 17], [9, 18], [10, 19], [11, 20]]) == 145
    assert candidate(n = 7,conflictingPairs = [[1, 7], [2, 6], [3, 5], [4, 6], [5, 7], [6, 7]]) == 18
    assert candidate(n = 11,conflictingPairs = [[1, 6], [2, 7], [3, 8], [4, 9], [5, 10], [6, 11]]) == 46
    assert candidate(n = 15,conflictingPairs = [[1, 15], [2, 14], [3, 13], [4, 12], [5, 11], [6, 10], [7, 9], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14]]) == 18
    assert candidate(n = 15,conflictingPairs = [[1, 3], [3, 5], [5, 7], [7, 9], [9, 11], [11, 13], [13, 15], [1, 4], [2, 5], [3, 6], [4, 7], [5, 8], [6, 9], [7, 10], [8, 11], [9, 12], [10, 13], [11, 14], [12, 15], [1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15]]) == 16
    assert candidate(n = 15,conflictingPairs = [[1, 5], [5, 10], [10, 15], [3, 7], [7, 12], [2, 6], [6, 11], [4, 8], [8, 13], [1, 6], [6, 11], [2, 7], [7, 12], [3, 8], [8, 13], [4, 9], [9, 14], [5, 10], [10, 15]]) == 62
    assert candidate(n = 12,conflictingPairs = [[1, 6], [2, 7], [3, 8], [4, 9], [5, 10], [1, 7], [2, 8], [3, 9], [4, 10], [5, 11], [1, 8], [2, 9], [3, 10], [4, 11], [5, 12]]) == 54
    assert candidate(n = 30,conflictingPairs = [[1, 15], [2, 16], [3, 17], [4, 18], [5, 19], [6, 20], [7, 21], [8, 22], [9, 23], [10, 24], [11, 25], [12, 26], [13, 27], [14, 28], [15, 29], [16, 30]]) == 330
    assert candidate(n = 12,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [1, 12], [2, 11], [3, 10], [4, 9], [5, 8], [6, 7], [1, 7], [2, 8], [3, 9], [4, 10], [5, 11], [6, 12]]) == 13
    assert candidate(n = 10,conflictingPairs = [[1, 10], [2, 9], [3, 8], [4, 7], [5, 6], [1, 2], [2, 3], [3, 4], [4, 5], [5, 10]]) == 24
    assert candidate(n = 30,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15], [15, 16], [16, 17], [17, 18], [18, 19], [19, 20], [20, 21], [21, 22], [22, 23], [23, 24], [24, 25], [25, 26], [26, 27], [27, 28], [28, 29], [29, 30], [1, 3], [3, 5], [5, 7], [7, 9], [9, 11], [11, 13], [13, 15], [15, 17], [17, 19], [19, 21], [21, 23], [23, 25], [25, 27], [27, 29]]) == 31
    assert candidate(n = 9,conflictingPairs = [[1, 9], [2, 9], [3, 9], [4, 9], [5, 9], [6, 9], [7, 9], [8, 9]]) == 38
    assert candidate(n = 20,conflictingPairs = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15], [15, 16], [16, 17], [17, 18], [18, 19], [19, 20]]) == 21
    assert candidate(n = 75,conflictingPairs = [[1, 26], [2, 27], [3, 28], [4, 29], [5, 30], [6, 31], [7, 32], [8, 33], [9, 34], [10, 35], [11, 36], [12, 37], [13, 38], [14, 39], [15, 40], [16, 41], [17, 42], [18, 43], [19, 44], [20, 45], [21, 46], [22, 47], [23, 48], [24, 49], [25, 50], [26, 51], [27, 52], [28, 53], [29, 54], [30, 55], [31, 56], [32, 57], [33, 58], [34, 59], [35, 60], [36, 61], [37, 62], [38, 63], [39, 64], [40, 65], [41, 66], [42, 67], [43, 68], [44, 69], [45, 70], [46, 71], [47, 72], [48, 73], [49, 74], [50, 75]]) == 1576
    assert candidate(n = 10,conflictingPairs = [[1, 10], [2, 9], [3, 8], [4, 7], [5, 6], [1, 3], [2, 4], [5, 7], [6, 8]]) == 25
    assert candidate(n = 12,conflictingPairs = [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10], [11, 12], [1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [7, 9], [8, 10], [9, 11], [10, 12]]) == 18


# === INVOCATION ===
check(Solution().maxSubarrays)
print("All tests passed")
