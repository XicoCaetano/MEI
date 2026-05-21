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
from collections import defaultdict

class Solution:
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:
        # For each right endpoint r, we want to know the minimum left endpoint
        # such that the subarray [l, r] is valid (no conflicting pair).
        # 
        # For a conflicting pair [a, b] with a < b, any subarray containing both
        # must have left <= a and right >= b. So for right = b, the constraint is
        # left > a (i.e., left >= a+1).
        #
        # For each position r, let limit[r] = max of all (min(a,b)) for pairs where max(a,b) = r
        # The valid subarrays ending at r have left in [limit[r]+1, r].
        # 
        # Base count (no removal): sum over r of (r - limit[r]) where limit is running max
        #
        # When we remove a pair [a, b] (a < b), it might increase the count for positions r >= b
        # where this pair was the "tightest" constraint.
        #
        # Strategy: compute base answer, then for each candidate removal, compute gain.

        # Normalize pairs so a < b
        pairs = [(min(a, b), max(a, b)) for a, b in conflictingPairs]
        
        # For each right endpoint, collect all left constraints
        constraints = defaultdict(list)
        for a, b in pairs:
            constraints[b].append(a)
        
        # Compute base answer and track limit at each position
        # limit[r] = the effective lower bound (max of all a's for pairs ending at r, running)
        
        # We need to track for each r: top1 and top2 constraints
        # top1 = highest constraint (most restrictive), top2 = second highest
        
        base_count = 0
        cur_limit = 0  # running max of constraints seen so far
        
        # For gain calculation: when we remove the pair that contributes cur_limit at some r,
        # the new limit becomes the second highest.
        # 
        # We need: for each r, what's the gain if we remove the tightest constraint at r?
        # gain at r = (new_limit_r - old_limit_r) propagated forward until overridden
        
        # Let's store limit per position and top2
        limits = [0] * (n + 1)  # limits[r] = effective limit at r (running max)
        top1 = [0] * (n + 1)    # top1 local constraint at r
        top2 = [0] * (n + 1)    # second local constraint at r
        
        cur = 0
        for r in range(1, n + 1):
            local = sorted(constraints[r], reverse=True)
            t1 = local[0] if len(local) > 0 else 0
            t2 = local[1] if len(local) > 1 else 0
            
            # cur is the running max before this position
            # new cur = max(cur, t1)
            prev_cur = cur
            cur = max(cur, t1)
            limits[r] = cur
            
            # top1[r]: the constraint that is "active" = cur
            # We need to know: if we remove the pair contributing cur, what's the new limit?
            # The new local top = t2, and the prev running = prev_cur
            # So new limit = max(prev_cur, t2)
            top1[r] = cur
            top2[r] = max(prev_cur, t2)
            
            base_count += r - cur
        
        # Now compute max gain from removing one pair
        # For each pair (a, b), removing it affects positions r = b
        # But the gain propagates: after r=b, subsequent positions may also benefit
        # if the limit was being held up by this pair.
        
        # We sweep from right to left to compute gains
        # gain[i] = if at position i we remove the binding constraint, gain = top1[i] - top2[i]
        # but this gain propagates to i+1, i+2, ... as long as limits[r] == top1[i]
        
        # For each pair (a, b), removing it gives gain at position b of (top1[b] - top2[b]) if a == top1[b]
        # Then this propagates rightward.
        
        # Propagate gains: go from n down to 1
        # extra[r] = extra subarrays gained if limit at r is reduced
        # If we remove pair (a, b) with a = limits[b], gain at b = limits[b] - top2[b]
        # For r > b: if limits[r] == limits[b] (unchanged), gain propagates
        # i.e., gain carries over as long as the running max didn't increase
        
        # Precompute: for each r, the "carry" gain if limit was reduced at r
        # carry[r] = gain that propagates from r to r+1 if limit[r] is the bottleneck
        
        # We sweep right to left
        carry = 0
        gain_if_removed = {}  # pair index -> total gain
        
        # Map from (a,b) to gain
        pair_to_gain = {}
        
        # Sweep from right to left
        carry = 0
        for r in range(n, 0, -1):
            # If someone removes the constraint at r (i.e., the pair that set limits[r] = top1[r])
            # the gain at r is (top1[r] - top2[r]) + carry_from_right (if top1[r] was propagated)
            if r < n and limits[r] == limits[r + 1]:
                # limit at r+1 was inherited from r, so gain propagates
                carry_here = carry
            else:
                carry_here = 0
            
            local_gain = (top1[r] - top2[r]) + carry_here
            
            # Which pair caused top1[r] at this position?
            # It's pairs with b = r and a = top1[r], but only if top1[r] > prev running max
            # Actually top1[r] = limits[r], contributed by some pair or inherited
            
            carry = local_gain if (top1[r] == limits[r]) else 0
            
            # Store gain for pairs ending at r where a == limits[r]
            for a in constraints[r]:
                if a == limits[r]:
                    # This pair is the binding one
                    pair_to_gain[(a, r)] = local_gain
                    break  # only one can be the binding one (the max)
        
        # Now find max gain over all pairs
        max_gain = 0
        for a, b in pairs:
            g = pair_to_gain.get((a, b), 0)
            max_gain = max(max_gain, g)
        
        # Also consider: pairs that are NOT the binding constraint at their position
        # Removing them gives 0 gain (they're not affecting the limit)
        # So max_gain already accounts for the best removal
        
        # Edge case: if no pair is binding anywhere, max_gain = 0, answer = base_count
        return base_count + max_gain

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
