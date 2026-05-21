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
    def minimumCost(self, nums: List[int], cost: List[int], k: int) -> int:
        n = len(nums)
        prefix_nums = [0] * (n + 1)
        prefix_cost = [0] * (n + 1)
        
        for i in range(n):
            prefix_nums[i + 1] = prefix_nums[i] + nums[i]
            prefix_cost[i + 1] = prefix_cost[i] + cost[i]
        
        INF = 10**18
        dp = [INF] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            for j in range(i):
                total_nums = prefix_nums[i] - prefix_nums[j]
                segment_cost = prefix_cost[i] - prefix_cost[j]
                dp[i] = min(dp[i], dp[j] + (total_nums + k * (j // (j + 1))) * segment_cost)  # j//(j+1) = 0 for j=0, 1 for j>=1, but we need the number of subarrays before
        
        # Correct approach: We need the index of the subarray (starting from 1)
        # Let's recompute properly with the subarray count
        dp = [INF] * (n + 1)
        dp[0] = 0
        
        for i in range(1, n + 1):
            for j in range(i):
                total_nums = prefix_nums[i] - prefix_nums[j]
                segment_cost = prefix_cost[i] - prefix_cost[j]
                # Number of subarrays before = number of cuts made before i
                # This equals (j>0) ? 1 + (some count) : 0
                # Actually, we need the index i (1-based) of the current subarray
                # If we split at j, then the new subarray is subarray # (count of subarrays before) + 1
                # Let's track the number of subarrays separately
                pass
        
        # Better: dp[i][s] = min cost for first i elements ending with s subarrays
        dp = [[INF] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(n + 1):
            for s in range(n + 1):
                if i < n and dp[i][s] < INF:
                    for t in range(i + 1, n + 1):
                        total_nums = prefix_nums[t] - prefix_nums[i]
                        segment_cost = prefix_cost[t] - prefix_cost[i]
                        new_s = s + 1
                        dp[t][new_s] = min(dp[t][new_s], dp[i][s] + (total_nums + k * new_s) * segment_cost)
        
        min_cost = INF
        for s in range(1, n + 1):
            min_cost = min(min_cost, dp[n][s])
        
        return min_cost


# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [1],cost = [1],k = 1) == 2
    assert candidate(nums = [4, 8, 5, 1, 14, 2, 2, 12, 1],cost = [7, 2, 8, 4, 2, 2, 1, 1, 2],k = 7) == 985
    assert candidate(nums = [1, 2, 3, 4, 5],cost = [5, 4, 3, 2, 1],k = 2) == 130
    assert candidate(nums = [3, 1, 4],cost = [4, 6, 6],k = 1) == 110
    assert candidate(nums = [10, 20, 30],cost = [1, 2, 3],k = 5) == 315
    assert candidate(nums = [5, 5, 5, 5, 5],cost = [5, 5, 5, 5, 5],k = 10) == 825
    assert candidate(nums = [1, 2, 3, 4, 5],cost = [1, 1, 1, 1, 1],k = 2) == 59
    assert candidate(nums = [10, 10, 10],cost = [10, 10, 10],k = 5) == 900
    assert candidate(nums = [10, 10, 10],cost = [10, 10, 10],k = 10) == 1100
    assert candidate(nums = [5, 3, 8, 9, 2],cost = [2, 4, 3, 5, 1],k = 3) == 341
    assert candidate(nums = [1, 2, 3, 4, 5],cost = [5, 4, 3, 2, 1],k = 3) == 155
    assert candidate(nums = [10, 20, 30],cost = [100, 200, 300],k = 5) == 31500
    assert candidate(nums = [5, 5, 5, 5],cost = [1, 1, 1, 1],k = 2) == 69
    assert candidate(nums = [1, 2, 3],cost = [1, 1, 1],k = 1) == 16
    assert candidate(nums = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50],cost = [50, 45, 40, 35, 30, 25, 20, 15, 10, 5],k = 50) == 46700
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1],k = 50) == 18550
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5],cost = [4, 6, 6, 3, 2, 1, 5, 7, 8],k = 5) == 1289
    assert candidate(nums = [1, 2, 1, 2, 1, 2, 1, 2],cost = [1, 2, 1, 2, 1, 2, 1, 2],k = 4) == 177
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],cost = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 15) == 2285
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1],cost = [9, 8, 7, 6, 5, 4, 3, 2, 1],k = 10) == 798
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5) == 425
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],cost = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 50) == 1853000
    assert candidate(nums = [999, 998, 997, 996, 995],cost = [1000, 1000, 1000, 1000, 1000],k = 1000) == 25952000
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 1) == 17401
    assert candidate(nums = [9, 9, 9, 9, 9, 9, 9, 9, 9, 9],cost = [9, 9, 9, 9, 9, 9, 9, 9, 9, 9],k = 1) == 4950
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 1) == 1179
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],cost = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 5) == 1402
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6],cost = [6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6, 6],k = 1) == 6270
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9],cost = [9, 2, 6, 5, 3, 5, 8, 9, 7, 9, 3, 2],k = 7) == 2829
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9],k = 1) == 1901
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == 22055
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],cost = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 15) == 2285
    assert candidate(nums = [5, 10, 15, 20, 25],cost = [2, 4, 6, 8, 10],k = 5) == 1800
    assert candidate(nums = [999, 998, 997, 996, 995, 994, 993, 992, 991, 990],cost = [1000, 999, 998, 997, 996, 995, 994, 993, 992, 991],k = 1000) == 84261650
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],cost = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 5) == 5011
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],cost = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1],k = 7) == 3817
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5) == 2705
    assert candidate(nums = [100, 200, 300, 400, 500],cost = [10, 20, 30, 40, 50],k = 50) == 162500
    assert candidate(nums = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3],cost = [100, 100, 100, 100, 100, 100, 100, 100, 100, 100],k = 10) == 36700
    assert candidate(nums = [5, 5, 5, 5, 5],cost = [1, 2, 3, 4, 5],k = 10) == 525
    assert candidate(nums = [5, 5, 5, 5, 5, 5],cost = [10, 10, 10, 10, 10, 10],k = 5) == 1750
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 10) == 200
    assert candidate(nums = [10, 20, 30, 40, 50],cost = [1, 2, 3, 4, 5],k = 10) == 1800
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],cost = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 10) == 1740100
    assert candidate(nums = [9, 7, 5, 3, 1],cost = [9, 7, 5, 3, 1],k = 2) == 505
    assert candidate(nums = [500, 500, 500, 500, 500, 500, 500, 500, 500, 500],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 500) == 270500
    assert candidate(nums = [1000, 1, 1000, 1, 1000, 1, 1000, 1, 1000, 1],cost = [1, 1000, 1, 1000, 1, 1000, 1, 1000, 1, 1000],k = 1000) == 26043017
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == 434
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5) == 369
    assert candidate(nums = [5, 3, 8, 1, 9],cost = [2, 3, 4, 1, 5],k = 3) == 345
    assert candidate(nums = [5, 4, 3, 2, 1],cost = [5, 4, 3, 2, 1],k = 3) == 232
    assert candidate(nums = [5, 4, 3, 2, 1],cost = [10, 20, 30, 40, 50],k = 5) == 3000
    assert candidate(nums = [10, 20, 30, 40, 50],cost = [5, 4, 3, 2, 1],k = 5) == 875
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9],k = 3) == 2100
    assert candidate(nums = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3],cost = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3],k = 3) == 2655
    assert candidate(nums = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],cost = [20, 18, 16, 14, 12, 10, 8, 6, 4, 2],k = 100) == 18820
    assert candidate(nums = [10, 20, 30, 40, 50],cost = [5, 4, 3, 2, 1],k = 5) == 875
    assert candidate(nums = [1, 10, 1, 10, 1, 10, 1, 10, 1, 10],cost = [10, 1, 10, 1, 10, 1, 10, 1, 10, 1],k = 30) == 4052
    assert candidate(nums = [100, 100, 100, 100, 100, 100, 100],cost = [1, 1, 1, 1, 1, 1, 1],k = 100) == 4600
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 50) == 3690
    assert candidate(nums = [1, 10, 1, 10, 1, 10, 1, 10],cost = [10, 1, 10, 1, 10, 1, 10, 1],k = 2) == 1041
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 10) == 69200
    assert candidate(nums = [5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],cost = [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5],k = 25) == 25751
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],cost = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 5) == 2125
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5],cost = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110],k = 7) == 30420
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == 295
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],cost = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 10) == 3019
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],cost = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 7) == 5537
    assert candidate(nums = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 10) == 10152
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == 2255
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],cost = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],k = 7) == 8542
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],cost = [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 10) == 15636
    assert candidate(nums = [1, 3, 2, 4, 5, 6, 7, 8, 9],cost = [9, 8, 7, 6, 5, 4, 3, 2, 1],k = 15) == 1713
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3) == 3706
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5) == 425
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == 85
    assert candidate(nums = [2, 7, 1, 8, 2, 8, 1, 8, 2, 8],cost = [8, 2, 8, 4, 5, 9, 0, 4, 5, 2],k = 4) == 1485
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],cost = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 10) == 1868
    assert candidate(nums = [1, 3, 2, 4, 5, 6, 7, 8, 9, 10],cost = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3) == 22850
    assert candidate(nums = [5, 3, 8, 9, 2],cost = [2, 3, 1, 4, 5],k = 3) == 385
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 20) == 3821
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90],cost = [10, 10, 10, 10, 10, 10, 10, 10, 10],k = 5) == 18550
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1],k = 3) == 378
    assert candidate(nums = [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2],cost = [2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1],k = 2) == 673
    assert candidate(nums = [10, 20, 30, 40, 50, 60],cost = [60, 50, 40, 30, 20, 10],k = 3) == 14280
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1],cost = [1, 2, 3, 4, 5, 6, 7, 8, 9],k = 1) == 1901
    assert candidate(nums = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 15) == 1615
    assert candidate(nums = [500, 500, 500, 500, 500, 500, 500, 500, 500, 500],cost = [1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000, 1000],k = 500) == 42500000
    assert candidate(nums = [10, 20, 30, 40, 50],cost = [5, 4, 3, 2, 1],k = 10) == 1050
    assert candidate(nums = [7, 10, 4, 3, 20, 15],cost = [2, 3, 4, 5, 6, 7],k = 10) == 1483
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],cost = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10],k = 5) == 1440
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],cost = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],k = 2) == 7040
    assert candidate(nums = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == 3905
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],cost = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1],k = 7) == 3817
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],cost = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1],k = 1) == 2396
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90],cost = [9, 8, 7, 6, 5, 4, 3, 2, 1],k = 10) == 6420
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],cost = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11],k = 7) == 2107
    assert candidate(nums = [6, 2, 5, 8, 1, 4, 7, 3],cost = [4, 1, 3, 2, 5, 6, 1, 2],k = 2) == 626
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],cost = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 20) == 8312
    assert candidate(nums = [5, 10, 15, 20, 25, 30],cost = [2, 3, 5, 7, 11, 13],k = 20) == 4545
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10],cost = [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2],k = 5) == 1860
    assert candidate(nums = [2, 3, 5, 7, 11, 13, 17, 19],cost = [19, 17, 13, 11, 7, 5, 3, 2],k = 15) == 3355
    assert candidate(nums = [1, 2, 1, 2, 1, 2, 1, 2, 1, 2],cost = [2, 3, 2, 3, 2, 3, 2, 3, 2, 3],k = 2) == 341
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],cost = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 20) == 213400
    assert candidate(nums = [7, 1, 5, 3, 6, 4],cost = [10, 20, 30, 40, 50, 60],k = 5) == 6060
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],cost = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5) == 144
    assert candidate(nums = [10, 20, 30, 40, 50],cost = [1, 2, 3, 4, 5],k = 10) == 1800
    assert candidate(nums = [10, 20, 30, 40, 50],cost = [1, 2, 3, 4, 5],k = 5) == 1625


# === INVOCATION ===
check(Solution().minimumCost)
print("All tests passed")
