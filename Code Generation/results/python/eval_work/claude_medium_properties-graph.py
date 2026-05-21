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
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        sets = [set(p) for p in properties]
        parent = list(range(n))

        def find(x):
            while parent[x] != x:
                parent[x] = parent[parent[x]]
                x = parent[x]
            return x

        def union(x, y):
            parent[find(x)] = find(y)

        for i in range(n):
            for j in range(i + 1, n):
                if len(sets[i] & sets[j]) >= k:
                    union(i, j)

        return len({find(i) for i in range(n)})

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(properties = [[1, 2, 3, 4], [2, 3, 4, 5], [3, 4, 5, 6], [4, 5, 6, 7]],k = 3) == 1
    assert candidate(properties = [[10, 20, 30], [30, 40, 50], [40, 50, 60], [50, 60, 70]],k = 1) == 1
    assert candidate(properties = [[1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1]],k = 4) == 4
    assert candidate(properties = [[1, 1, 1], [1, 1, 1], [1, 1, 1]],k = 1) == 1
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6]],k = 1) == 1
    assert candidate(properties = [[1, 1, 1, 1], [1, 1, 1, 1], [1, 1, 1, 1]],k = 4) == 3
    assert candidate(properties = [[1, 1], [1, 1]],k = 2) == 2
    assert candidate(properties = [[1, 2, 3], [2, 3, 4], [3, 4, 5], [4, 5, 6]],k = 2) == 1
    assert candidate(properties = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [1, 4, 7], [2, 5, 8], [3, 6, 9]],k = 1) == 1
    assert candidate(properties = [[10, 20, 30], [20, 30, 40], [30, 40, 50], [40, 50, 60]],k = 2) == 1
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 5]],k = 1) == 1
    assert candidate(properties = [[1, 2], [1, 1], [3, 4], [4, 5], [5, 6], [7, 7]],k = 1) == 3
    assert candidate(properties = [[1], [2], [3], [4], [5]],k = 1) == 5
    assert candidate(properties = [[1, 2], [3, 4], [5, 6], [7, 8]],k = 0) == 1
    assert candidate(properties = [[1, 2, 3], [2, 3, 4], [4, 3, 5]],k = 2) == 1
    assert candidate(properties = [[10, 20, 30], [10, 20, 30], [10, 20, 30], [10, 20, 30]],k = 2) == 1
    assert candidate(properties = [[1, 2, 3], [4, 5, 6], [7, 8, 9]],k = 2) == 3
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [1, 11, 21, 31, 41, 51, 61, 71, 81, 91]],k = 2) == 3
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9], [2, 3, 4, 5, 6, 7, 8, 9, 10], [3, 4, 5, 6, 7, 8, 9, 10, 11]],k = 4) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12], [10, 11, 12, 13, 14, 15, 16, 17, 18, 19]],k = 4) == 2
    assert candidate(properties = [[5, 5, 5], [5, 5, 5], [5, 5, 5], [5, 5, 5], [5, 5, 5], [5, 5, 5]],k = 3) == 6
    assert candidate(properties = [[1, 2, 3, 4, 5], [5, 4, 3, 2, 1], [2, 3, 4, 5, 6], [6, 5, 4, 3, 2], [3, 4, 5, 6, 7]],k = 4) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 11], [1, 2, 3, 4, 5, 6, 7, 8, 9, 12]],k = 5) == 1
    assert candidate(properties = [[1, 1, 1, 1], [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2]],k = 3) == 4
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21]],k = 10) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 3, 5, 7, 9, 11, 13, 15, 17, 19], [2, 4, 6, 8, 10, 12, 14, 16, 18, 20], [1, 4, 7, 10, 13, 16, 19, 22, 25, 28]],k = 3) == 1
    assert candidate(properties = [[1, 2, 3], [2, 3, 4], [4, 3, 5], [5, 6, 7], [7, 8, 9]],k = 2) == 3
    assert candidate(properties = [[1, 2, 3, 4, 5, 6], [6, 7, 8, 9, 10, 11], [11, 12, 13, 14, 15, 16], [16, 17, 18, 19, 20, 21]],k = 3) == 4
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 11], [1, 2, 3, 4, 5, 6, 7, 8, 9, 12], [1, 2, 3, 4, 5, 6, 7, 8, 9, 13]],k = 5) == 1
    assert candidate(properties = [[10, 20, 30, 40, 50], [50, 40, 30, 20, 10], [1, 2, 3, 4, 5], [5, 4, 3, 2, 1], [10, 15, 20, 25, 30]],k = 2) == 2
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]],k = 5) == 1
    assert candidate(properties = [[5, 10, 15, 20], [10, 15, 20, 25], [15, 20, 25, 30], [20, 25, 30, 35], [25, 30, 35, 40]],k = 3) == 1
    assert candidate(properties = [[1, 1, 1, 1], [2, 2, 2, 2], [1, 1, 2, 2], [2, 2, 1, 1], [1, 2, 1, 2], [2, 1, 2, 1]],k = 2) == 3
    assert candidate(properties = [[1, 1, 1, 1, 1], [2, 2, 2, 2, 2], [3, 3, 3, 3, 3], [1, 2, 3, 4, 5], [2, 3, 4, 5, 6]],k = 3) == 4
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 1]],k = 1) == 1
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 1], [1, 3], [2, 4], [1, 4], [2, 3]],k = 1) == 1
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 1]],k = 1) == 1
    assert candidate(properties = [[1, 10, 100], [10, 100, 1000], [100, 1000, 10000], [1000, 10000, 100000], [100000, 1, 10]],k = 2) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7], [4, 5, 6, 7, 8], [5, 6, 7, 8, 9]],k = 3) == 1
    assert candidate(properties = [[1, 2, 3], [2, 3, 4], [4, 5, 6], [6, 7, 8], [8, 9, 10], [10, 11, 12]],k = 2) == 5
    assert candidate(properties = [[10, 20, 30], [20, 30, 40], [30, 40, 50], [40, 50, 60], [50, 60, 70]],k = 2) == 1
    assert candidate(properties = [[1, 1, 1], [1, 1, 2], [1, 2, 2], [2, 2, 2], [2, 2, 3], [2, 3, 3], [3, 3, 3]],k = 2) == 5
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [21, 22, 23, 24, 25, 26, 27, 28, 29, 30]],k = 1) == 3
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12]],k = 5) == 1
    assert candidate(properties = [[1, 1, 2, 2, 3, 3, 4, 4, 5, 5], [1, 2, 2, 3, 3, 4, 4, 5, 5, 6], [1, 1, 2, 3, 3, 4, 4, 5, 6, 6], [1, 2, 2, 3, 3, 4, 4, 5, 6, 7], [1, 2, 2, 3, 3, 4, 4, 5, 6, 8]],k = 4) == 1
    assert candidate(properties = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [1, 4, 7], [2, 5, 8], [3, 6, 9]],k = 1) == 1
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]],k = 1) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32]],k = 15) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [21, 22, 23, 24, 25, 26, 27, 28, 29, 30]],k = 5) == 3
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]],k = 10) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]],k = 5) == 1
    assert candidate(properties = [[10, 20, 30, 40, 50], [10, 20, 30, 60, 70], [10, 20, 50, 60, 70], [10, 50, 60, 70, 80]],k = 2) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [2, 2, 3, 4, 5, 6, 7, 8, 9, 10], [3, 3, 3, 4, 5, 6, 7, 8, 9, 10]],k = 3) == 1
    assert candidate(properties = [[1, 2, 3], [2, 3, 4], [3, 4, 5], [4, 5, 6], [5, 6, 7], [6, 7, 8], [7, 8, 9], [8, 9, 10]],k = 2) == 1
    assert candidate(properties = [[1, 1, 1, 1], [2, 2, 2, 2], [3, 3, 3, 3], [1, 2, 3, 4], [4, 5, 6, 7]],k = 2) == 5
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39]],k = 6) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]],k = 5) == 1
    assert candidate(properties = [[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16], [1, 5, 9, 13], [2, 6, 10, 14], [3, 7, 11, 15], [4, 8, 12, 16]],k = 1) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27]],k = 6) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [21, 22, 23, 24, 25, 26, 27, 28, 29, 30], [31, 32, 33, 34, 35, 36, 37, 38, 39, 40]],k = 1) == 4
    assert candidate(properties = [[1, 1, 2, 2], [2, 2, 3, 3], [3, 3, 4, 4], [4, 4, 1, 1]],k = 2) == 4
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 1], [1, 3], [3, 5]],k = 1) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7], [4, 5, 6, 7, 8]],k = 3) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [2, 3, 4, 5, 6, 7, 8, 9, 10, 1], [3, 4, 5, 6, 7, 8, 9, 10, 1, 2], [4, 5, 6, 7, 8, 9, 10, 1, 2, 3]],k = 3) == 1
    assert candidate(properties = [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]],k = 5) == 4
    assert candidate(properties = [[1, 2, 3], [1, 2, 3], [1, 2, 3], [1, 2, 3], [1, 2, 3], [1, 2, 3], [1, 2, 3], [1, 2, 3]],k = 3) == 1
    assert candidate(properties = [[10, 20, 30], [10, 20, 40], [10, 30, 40], [20, 30, 40], [10, 20, 30, 40]],k = 2) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [2, 4, 6, 8, 10, 12, 14, 16, 18, 20], [3, 6, 9, 12, 15, 18, 21, 24, 27, 30], [4, 8, 12, 16, 20, 24, 28, 32, 36, 40]],k = 4) == 2
    assert candidate(properties = [[1, 1, 1, 1], [2, 2, 2, 2], [3, 3, 3, 3], [1, 2, 3, 4]],k = 2) == 4
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 2]],k = 5) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16], [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29]],k = 5) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17]],k = 5) == 1
    assert candidate(properties = [[1, 1, 1, 1, 1, 1, 1, 1, 1, 1], [2, 2, 2, 2, 2, 2, 2, 2, 2, 2], [3, 3, 3, 3, 3, 3, 3, 3, 3, 3], [4, 4, 4, 4, 4, 4, 4, 4, 4, 4]],k = 5) == 4
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22]],k = 5) == 1
    assert candidate(properties = [[1, 1, 2, 2], [2, 2, 3, 3], [3, 3, 4, 4], [4, 4, 5, 5], [5, 5, 6, 6]],k = 2) == 5
    assert candidate(properties = [[1, 1, 1, 1, 1], [2, 2, 2, 2, 2], [3, 3, 3, 3, 3], [4, 4, 4, 4, 4], [5, 5, 5, 5, 5]],k = 1) == 5
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]],k = 8) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6], [2, 3, 4, 5, 6, 7], [3, 4, 5, 6, 7, 8], [4, 5, 6, 7, 8, 9]],k = 4) == 1
    assert candidate(properties = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 1], [1, 3], [2, 4], [3, 5], [4, 1], [5, 2]],k = 1) == 1
    assert candidate(properties = [[10, 20, 30], [10, 20, 40], [10, 30, 50], [20, 30, 60], [30, 40, 50]],k = 2) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [1, 3, 5, 7, 9, 11, 13, 15, 17, 19], [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]],k = 2) == 1
    assert candidate(properties = [[1, 2, 2, 3, 4, 4, 5], [2, 3, 3, 4, 4, 5, 5], [3, 4, 4, 5, 5, 6, 6], [4, 5, 5, 6, 6, 7, 7], [5, 6, 6, 7, 7, 8, 8]],k = 3) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6], [2, 3, 4, 5, 6, 7], [3, 4, 5, 6, 7, 8], [4, 5, 6, 7, 8, 9], [5, 6, 7, 8, 9, 10]],k = 4) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5], [6, 7, 8, 9, 10], [1, 6, 2, 7, 3], [8, 4, 9, 5, 10], [11, 12, 13, 14, 15]],k = 2) == 2
    assert candidate(properties = [[1, 1, 1, 1], [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2], [2, 2, 2, 2]],k = 3) == 5
    assert candidate(properties = [[1, 1, 1, 1], [1, 1, 1, 2], [1, 1, 2, 2], [1, 2, 2, 2], [2, 2, 2, 2]],k = 3) == 5
    assert candidate(properties = [[1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7], [4, 5, 6, 7, 8], [5, 6, 7, 8, 9]],k = 3) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5], [5, 4, 3, 2, 1], [1, 2, 3, 4, 5], [5, 4, 3, 2, 1], [1, 2, 3, 4, 5]],k = 3) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [2, 3, 4, 5, 6, 7, 8, 9, 10, 11], [3, 4, 5, 6, 7, 8, 9, 10, 11, 12]],k = 4) == 1
    assert candidate(properties = [[1, 2, 3, 4, 5], [5, 6, 7, 8, 9], [9, 10, 11, 12, 13], [13, 14, 15, 16, 17], [17, 18, 19, 20, 21], [21, 22, 23, 24, 25]],k = 2) == 6
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [10, 9, 8, 7, 6, 5, 4, 3, 2, 1], [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]],k = 5) == 1
    assert candidate(properties = [[1, 2, 3], [4, 5, 6], [7, 8, 9], [10, 11, 12], [13, 14, 15], [1, 4, 7], [2, 5, 8], [3, 6, 9]],k = 1) == 3
    assert candidate(properties = [[1, 1, 1], [1, 1, 2], [1, 2, 2], [2, 2, 2], [2, 2, 1]],k = 2) == 3
    assert candidate(properties = [[1, 1], [2, 2], [3, 3], [4, 4], [5, 5], [6, 6], [7, 7], [8, 8], [9, 9], [10, 10]],k = 1) == 10
    assert candidate(properties = [[1, 2, 3, 4, 5, 6, 7, 8, 9, 10], [2, 3, 4, 5, 6, 7, 8, 9, 10, 1], [3, 4, 5, 6, 7, 8, 9, 10, 1, 2]],k = 4) == 1


# === INVOCATION ===
check(Solution().numberOfComponents)
print("All tests passed")
