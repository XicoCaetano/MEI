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
import sortedcontainers

class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        # Use a sorted structure to efficiently find leftmost basket with capacity >= fruit quantity
        # We need leftmost, so we track (capacity, original_index) and find min index among valid
        
        # Segment tree approach: build over baskets array, query for leftmost index with value >= x
        n = len(baskets)
        
        # Segment tree storing max value in range, to quickly skip ranges
        # For leftmost basket >= fruit, we need to find leftmost position with baskets[pos] >= fruit
        
        size = 1
        while size < n:
            size <<= 1
        
        tree = [0] * (2 * size)
        
        # Build tree with max values
        for i in range(n):
            tree[size + i] = baskets[i]
        for i in range(size - 1, 0, -1):
            tree[i] = max(tree[2*i], tree[2*i+1])
        
        def query_leftmost(val):
            # Find leftmost index in [0, n) where baskets[index] >= val
            if tree[1] < val:
                return -1
            node = 1
            while node < size:
                if tree[2*node] >= val:
                    node = 2*node  # go left
                else:
                    node = 2*node + 1  # go right
            idx = node - size
            if idx < n and tree[node] >= val:
                return idx
            return -1
        
        def update(idx, val):
            pos = size + idx
            tree[pos] = val
            pos >>= 1
            while pos >= 1:
                tree[pos] = max(tree[2*pos], tree[2*pos+1])
                pos >>= 1
        
        unplaced = 0
        for fruit in fruits:
            idx = query_leftmost(fruit)
            if idx == -1:
                unplaced += 1
            else:
                update(idx, 0)  # mark basket as used
        
        return unplaced

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(fruits = [5, 5, 5, 5, 5],baskets = [1, 2, 3, 4, 5]) == 4
    assert candidate(fruits = [4, 2, 5],baskets = [3, 5, 4]) == 1
    assert candidate(fruits = [1, 1, 1, 1],baskets = [1, 1, 1, 1]) == 0
    assert candidate(fruits = [1000000000, 1000000000],baskets = [999999999, 1000000000]) == 1
    assert candidate(fruits = [1000000000],baskets = [1000000000]) == 0
    assert candidate(fruits = [1, 2, 3, 4],baskets = [4, 3, 2, 1]) == 2
    assert candidate(fruits = [1, 1, 1, 1, 1],baskets = [1, 1, 1, 1, 1]) == 0
    assert candidate(fruits = [1, 2, 3, 4],baskets = [10, 10, 10, 10]) == 0
    assert candidate(fruits = [10, 9, 8, 7, 6],baskets = [6, 7, 8, 9, 10]) == 0
    assert candidate(fruits = [5, 5, 5, 5],baskets = [5, 5, 5, 5]) == 0
    assert candidate(fruits = [1, 10, 100, 1000],baskets = [1000, 100, 10, 1]) == 2
    assert candidate(fruits = [7, 8, 9],baskets = [6, 7, 8]) == 1
    assert candidate(fruits = [10, 10, 10],baskets = [5, 5, 5]) == 3
    assert candidate(fruits = [1, 2, 3, 4, 5],baskets = [5, 4, 3, 2, 1]) == 2
    assert candidate(fruits = [10, 20, 30],baskets = [5, 15, 25]) == 1
    assert candidate(fruits = [3, 6, 1],baskets = [6, 4, 7]) == 0
    assert candidate(fruits = [9, 7, 5, 3, 1],baskets = [1, 3, 5, 7, 9]) == 0
    assert candidate(fruits = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],baskets = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95]) == 1
    assert candidate(fruits = [5, 15, 25, 35, 45],baskets = [10, 20, 30, 40, 50]) == 0
    assert candidate(fruits = [5, 5, 5, 5, 5],baskets = [5, 5, 5, 5, 5]) == 0
    assert candidate(fruits = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],baskets = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1]) == 5
    assert candidate(fruits = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],baskets = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 0
    assert candidate(fruits = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 4
    assert candidate(fruits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 0
    assert candidate(fruits = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],baskets = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1]) == 5
    assert candidate(fruits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],baskets = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 0
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [50, 40, 30, 20, 10]) == 2
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [20, 30, 40, 50, 60]) == 0
    assert candidate(fruits = [1000000000, 500000000, 250000000, 125000000, 62500000],baskets = [62500000, 125000000, 250000000, 500000000, 1000000000]) == 0
    assert candidate(fruits = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 0
    assert candidate(fruits = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],baskets = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5]) == 0
    assert candidate(fruits = [9, 8, 7, 6, 5, 4, 3, 2, 1, 1],baskets = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 0
    assert candidate(fruits = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],baskets = [1000, 900, 800, 700, 600, 500, 400, 300, 200, 100]) == 5
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [25, 35, 15, 45, 55]) == 1
    assert candidate(fruits = [10, 20, 30, 40, 50, 60],baskets = [15, 25, 35, 45, 55, 65]) == 0
    assert candidate(fruits = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],baskets = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10]) == 5
    assert candidate(fruits = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 0
    assert candidate(fruits = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3],baskets = [1, 1, 1, 1, 1, 1, 1, 1, 1, 10]) == 9
    assert candidate(fruits = [1000000000, 999999999, 888888888, 777777777, 666666666],baskets = [999999999, 888888888, 777777777, 666666666, 555555555]) == 1
    assert candidate(fruits = [1000000000],baskets = [999999999]) == 1
    assert candidate(fruits = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],baskets = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]) == 0
    assert candidate(fruits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],baskets = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 5
    assert candidate(fruits = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512],baskets = [1024, 512, 256, 128, 64, 32, 16, 8, 4, 2]) == 4
    assert candidate(fruits = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],baskets = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 10
    assert candidate(fruits = [7, 3, 8, 2, 9, 5],baskets = [10, 5, 8, 4, 9, 6]) == 0
    assert candidate(fruits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],baskets = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) == 0
    assert candidate(fruits = [5, 5, 5, 5, 5],baskets = [1, 1, 1, 1, 10]) == 4
    assert candidate(fruits = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60],baskets = [60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5]) == 6
    assert candidate(fruits = [1, 3, 5, 7, 9, 11, 13],baskets = [13, 11, 9, 7, 5, 3, 1]) == 3
    assert candidate(fruits = [10, 10, 10, 10, 10, 10],baskets = [5, 5, 5, 5, 5, 5]) == 6
    assert candidate(fruits = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],baskets = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]) == 0
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [5, 15, 25, 35, 45]) == 1
    assert candidate(fruits = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],baskets = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]) == 1
    assert candidate(fruits = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120],baskets = [120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10]) == 6
    assert candidate(fruits = [9, 8, 7, 6, 5, 4, 3, 2, 1],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9]) == 0
    assert candidate(fruits = [100, 200, 300, 400, 500],baskets = [500, 400, 300, 200, 100]) == 2
    assert candidate(fruits = [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000],baskets = [10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 1]) == 1
    assert candidate(fruits = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50],baskets = [50, 45, 40, 35, 30, 25, 20, 15, 10, 5]) == 5
    assert candidate(fruits = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91],baskets = [91, 92, 93, 94, 95, 96, 97, 98, 99, 100]) == 0
    assert candidate(fruits = [50, 40, 30, 20, 10],baskets = [10, 20, 30, 40, 50]) == 0
    assert candidate(fruits = [999999999, 999999998, 999999997, 999999996, 999999995],baskets = [1000000000, 1000000000, 1000000000, 1000000000, 1000000000]) == 0
    assert candidate(fruits = [5, 7, 3, 8, 2, 6],baskets = [4, 5, 7, 6, 8, 3]) == 1
    assert candidate(fruits = [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],baskets = [5, 5, 5, 5, 5, 10, 10, 10, 10, 10]) == 5
    assert candidate(fruits = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4],baskets = [2, 2, 3, 3, 3, 4, 4, 4, 4, 4]) == 0
    assert candidate(fruits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],baskets = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10]) == 0
    assert candidate(fruits = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],baskets = [5, 4, 3, 2, 1, 5, 4, 3, 2, 1]) == 4
    assert candidate(fruits = [5, 3, 8, 6, 2],baskets = [4, 7, 8, 5, 1]) == 1
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [5, 25, 15, 40, 30]) == 2
    assert candidate(fruits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],baskets = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]) == 0
    assert candidate(fruits = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],baskets = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 0
    assert candidate(fruits = [1, 1, 1, 1, 10],baskets = [10, 10, 10, 10, 1]) == 1
    assert candidate(fruits = [5, 10, 15, 20, 25],baskets = [5, 15, 25, 35, 45, 55]) == 0
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [1, 1, 1, 1, 1]) == 5
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [5, 15, 25, 35, 45]) == 1
    assert candidate(fruits = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 9
    assert candidate(fruits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],baskets = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 7
    assert candidate(fruits = [10, 20, 30, 40, 50, 60],baskets = [60, 50, 40, 30, 20, 10]) == 3
    assert candidate(fruits = [10, 20, 30, 40, 50],baskets = [100, 100, 100, 100, 1]) == 1
    assert candidate(fruits = [5, 5, 5, 5, 5],baskets = [3, 3, 3, 3, 3]) == 5
    assert candidate(fruits = [500, 400, 300, 200, 100],baskets = [100, 200, 300, 400, 500]) == 0
    assert candidate(fruits = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10],baskets = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 10
    assert candidate(fruits = [1, 3, 5, 7, 9],baskets = [2, 4, 6, 8, 10]) == 0
    assert candidate(fruits = [100, 200, 300, 400, 500],baskets = [150, 250, 350, 450, 550]) == 0
    assert candidate(fruits = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],baskets = [20, 18, 16, 14, 12, 10, 8, 6, 4, 2]) == 5
    assert candidate(fruits = [999999999, 999999998, 999999997, 999999996],baskets = [999999996, 999999997, 999999998, 999999999]) == 0
    assert candidate(fruits = [2, 4, 6, 8, 10],baskets = [1, 3, 5, 7, 9]) == 1
    assert candidate(fruits = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 9
    assert candidate(fruits = [9, 11, 13, 15, 17],baskets = [18, 19, 20, 21, 22]) == 0
    assert candidate(fruits = [10, 10, 10, 10, 10],baskets = [5, 5, 5, 5, 5]) == 5
    assert candidate(fruits = [1000000000, 1000000000, 1000000000],baskets = [999999999, 999999999, 999999999]) == 3
    assert candidate(fruits = [1, 2, 4, 8, 16, 32, 64, 128, 256, 512],baskets = [1, 2, 4, 8, 16, 32, 64, 128, 256, 1024]) == 0
    assert candidate(fruits = [9, 8, 7, 6, 5, 4, 3, 2, 1],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 10]) == 0
    assert candidate(fruits = [9, 8, 7, 6, 5],baskets = [10, 9, 8, 7, 6]) == 0
    assert candidate(fruits = [1000000000, 1000000000, 1000000000],baskets = [999999999, 999999999, 1000000000]) == 2
    assert candidate(fruits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],baskets = [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 10
    assert candidate(fruits = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10],baskets = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 9
    assert candidate(fruits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],baskets = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 0
    assert candidate(fruits = [2, 3, 1, 5, 4],baskets = [5, 3, 4, 2, 1]) == 2
    assert candidate(fruits = [50, 50, 50, 50, 50],baskets = [40, 40, 60, 60, 60]) == 2
    assert candidate(fruits = [1, 3, 5, 7, 9, 11],baskets = [2, 4, 6, 8, 10, 12]) == 0
    assert candidate(fruits = [1000000000, 999999999, 888888888, 777777777, 666666666],baskets = [666666666, 777777777, 888888888, 999999999, 1000000000]) == 0


# === INVOCATION ===
check(Solution().numOfUnplacedFruits)
print("All tests passed")
