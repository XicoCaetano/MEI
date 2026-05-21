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

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [1, 3, 1, 4, 1, 3, 2],queries = [0, 3, 5]) == [2, -1, 3]
    assert candidate(nums = [1, 2, 3, 4],queries = [0, 1, 2, 3]) == [-1, -1, -1, -1]
    assert candidate(nums = [1000000, 1000000, 1000000],queries = [0, 1, 2]) == [1, 1, 1]
    assert candidate(nums = [5, 1, 5, 2, 5, 3, 5, 4],queries = [2, 4, 6, 0]) == [2, 2, 2, 2]
    assert candidate(nums = [10, 20, 30, 40, 50, 10, 20],queries = [0, 1, 2, 3, 4, 5, 6]) == [2, 2, -1, -1, -1, 2, 2]
    assert candidate(nums = [6, 5, 4, 3, 2, 1],queries = [0, 1, 2, 3, 4, 5]) == [-1, -1, -1, -1, -1, -1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 9, 5]) == [-1, -1, -1]
    assert candidate(nums = [10, 10, 10, 10],queries = [0, 1, 2, 3]) == [1, 1, 1, 1]
    assert candidate(nums = [2, 1, 3, 1, 2],queries = [0, 1, 2, 3, 4]) == [1, 2, -1, 2, 1]
    assert candidate(nums = [5, 1, 5, 1, 5, 1],queries = [2, 4, 1, 3]) == [2, 2, 2, 2]
    assert candidate(nums = [5, 5, 5, 5, 5],queries = [0, 1, 2, 3, 4]) == [1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
    assert candidate(nums = [1, 2, 3, 2, 1],queries = [0, 1, 2, 3, 4]) == [1, 2, -1, 2, 1]
    assert candidate(nums = [7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 3, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == [3, 2, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2]
    assert candidate(nums = [7, 8, 9, 7, 10, 11, 12, 9, 13, 14, 7, 15, 16, 17, 8, 18],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == [3, 3, 5, 3, -1, -1, -1, 5, -1, -1, 6, -1, -1, -1, 3, -1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9],queries = [0, 9, 18, 27, 20]) == [9, 9, 9, 9, 9]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50],queries = [0, 5, 10]) == [5, 5, 5]
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1000000, 2000000, 3000000, 4000000, 5000000, 1000000, 2000000, 3000000, 4000000, 5000000, 1000000, 2000000, 3000000, 4000000, 5000000],queries = [0, 5, 10, 15, 20]) == [5, 5, 5, 5, 5]
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4],queries = [0, 5, 10]) == [6, 6, 6]
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [10, 20, 10, 30, 10, 40, 10, 50, 10, 60],queries = [0, 2, 4, 6, 8]) == [2, 2, 2, 2, 2]
    assert candidate(nums = [7, 8, 9, 7, 6, 7, 8, 9, 7, 6],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [2, 5, 5, 2, 5, 2, 5, 5, 2, 5]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 5, 10, 15, 20]) == [10, 10, 10, 10, 10]
    assert candidate(nums = [5, 6, 5, 6, 5, 6, 5, 6, 5, 6],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9],queries = [0, 9, 10, 18]) == [9, 9, 9, 9]
    assert candidate(nums = [7, 8, 9, 7, 10, 8, 9, 7],queries = [0, 1, 2, 3, 4, 5, 6, 7]) == [1, 4, 4, 3, -1, 4, 4, 1]
    assert candidate(nums = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]) == [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5]
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7],queries = [0, 9, 18, 10, 19, 1, 11, 2, 12]) == [3, 9, 3, 9, 3, 3, 9, 3, 9]
    assert candidate(nums = [5, 6, 7, 8, 9, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]) == [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5]
    assert candidate(nums = [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],queries = [0, 3, 6, 9, 1, 4, 7, 10, 2, 5, 8, 11]) == [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]
    assert candidate(nums = [100, 200, 100, 300, 100, 200, 100, 400, 100, 200],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [2, 2, 2, -1, 2, 4, 2, -1, 2, 2]
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [7, 7, 7, 7, 7, 7, 7],queries = [0, 1, 2, 3, 4, 5, 6]) == [1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13]) == [5, 5, 5, 5, 5, -1, -1, -1, -1, 5, 5, 5, 5, 5]
    assert candidate(nums = [1000000, 999999, 999998, 999997, 999996, 999995, 1000000, 999999, 999998, 999997],queries = [0, 4, 8]) == [4, -1, 4]
    assert candidate(nums = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50],queries = [0, 5, 10, 15, 20]) == [5, 5, 5, 5, 5]
    assert candidate(nums = [5, 3, 5, 3, 5, 3, 5, 3, 5, 3],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9],queries = [0, 5, 10, 15]) == [9, 9, 9, 9]
    assert candidate(nums = [2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 9, 10, 19, 5, 14]) == [9, -1, 9, 9, 9, 9]
    assert candidate(nums = [1, 2, 1, 3, 1, 4, 1, 5, 1, 6],queries = [0, 2, 4, 6, 8]) == [2, 2, 2, 2, 2]
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 100, 200, 300],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]) == [3, 3, 3, -1, -1, -1, -1, -1, -1, 3, 3, 3]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 5, 10, 15, 20, 25, 30, 35, 39]) == [10, 10, -1, -1, 10, 10, 10, 10, 10]
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 100],queries = [0, 10, 5, 3, 8]) == [1, 1, -1, -1, -1]
    assert candidate(nums = [10, 20, 30, 10, 20, 30, 10, 20, 30, 10, 20, 30],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]) == [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3]
    assert candidate(nums = [1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1],queries = [0, 2, 4, 6, 8, 10]) == [1, 2, 2, 2, 2, 1]
    assert candidate(nums = [4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10],queries = [0, 4, 8, 12, 16, 20]) == [7, 7, 7, 7, 7, 7]
    assert candidate(nums = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 1, 1, 1],queries = [0, 4, 8, 12, 16]) == [1, 1, 1, 1, 1]
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 10, 20, 30, 40, 50],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14]) == [5, 5, 5, 5, 5, -1, -1, -1, -1, -1, 5, 5, 5, 5, 5]
    assert candidate(nums = [1, 2, 3, 4, 1, 2, 3, 4, 1, 2],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [2, 2, 4, 4, 4, 4, 4, 4, 2, 2]
    assert candidate(nums = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5],queries = [0, 5, 10, 15, 20, 1, 6, 11, 16, 21]) == [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1],queries = [0, 10, 20, 5, 15, 25]) == [1, 10, 1, 10, 10, 10]
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 1, 1, 2, 2, 3, 3],queries = [0, 2, 4, 6, 8, 10]) == [1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],queries = [0, 10, 20, 30, 40, 50]) == [20, 20, 20, 20, 20, 20]
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9],queries = [0, 10, 15, 20]) == [9, 9, 9, 9]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1],queries = [0, 10, 20, 5, 15]) == [9, 9, 9, 9, 9]
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8]) == [1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [7, 8, 9, 7, 10, 11, 9, 12, 7],queries = [0, 3, 6, 8]) == [1, 3, 4, 1]
    assert candidate(nums = [1000000, 999999, 999998, 999997, 999996, 1000000, 999999, 999998, 999997, 999996],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 1, 1],queries = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],queries = [0, 5, 10, 15, 19]) == [-1, -1, -1, -1, -1]
    assert candidate(nums = [5, 3, 8, 3, 5, 8, 5, 3, 8, 3, 5, 8],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]) == [2, 2, 3, 2, 2, 3, 2, 2, 3, 2, 2, 3]
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39]) == [9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, -1, -1, -1, -1, -1, -1, -1, -1, 1]
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [2, 3, 2, 2, 2, 3, 3, 2, 2, 2, 3],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == [2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2]
    assert candidate(nums = [7, 8, 9, 7, 10, 11, 7, 12, 7, 13, 7, 14],queries = [0, 3, 6, 9, 12]) == [2, 3, 2, -1, 2]
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7]) == [1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]
    assert candidate(nums = [30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == [2, 2, -1, 2, 4, -1, -1, -1, 2, 2, 2]
    assert candidate(nums = [7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 1, 3, 1, 4, 1, 5, 1, 6],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [2, -1, 2, -1, 2, -1, 2, -1, 2, -1]
    assert candidate(nums = [7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19]) == [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
    assert candidate(nums = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5],queries = [0, 5, 10]) == [5, 5, 5]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5],queries = [0, 20, 21, 22, 23]) == [5, 5, 5, 5, 5]
    assert candidate(nums = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5],queries = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]


# === INVOCATION ===
check(Solution().solveQueries)
print("All tests passed")
