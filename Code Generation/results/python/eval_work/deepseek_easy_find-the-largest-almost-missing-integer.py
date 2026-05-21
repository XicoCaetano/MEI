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
    def largestInteger(self, nums: List[int], k: int) -> int:
        n = len(nums)
        freq = defaultdict(int)
        
        # Count frequency of each integer in all subarrays of size k
        for i in range(n - k + 1):
            subarray = nums[i:i + k]
            seen = set(subarray)  # Avoid counting duplicates in the same subarray
            for num in seen:
                freq[num] += 1
        
        # Find the largest integer that appears exactly once across all subarrays
        result = -1
        for num, count in freq.items():
            if count == 1:
                result = max(result, num)
        
        return result

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [2, 2, 3, 3, 4, 4, 5, 5],k = 2) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 10) == 10
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5) == 10
    assert candidate(nums = [1, 2, 3, 4, 5],k = 2) == 5
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 3) == -1
    assert candidate(nums = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4],k = 4) == 1
    assert candidate(nums = [10, 20, 30, 40, 50],k = 5) == 50
    assert candidate(nums = [5, 5, 5, 5, 5],k = 3) == -1
    assert candidate(nums = [10, 20, 30, 40, 50],k = 2) == 50
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],k = 4) == 19
    assert candidate(nums = [1, 3, 1, 3, 1, 3],k = 3) == -1
    assert candidate(nums = [42, 42, 42, 42, 42, 42, 42],k = 7) == 42
    assert candidate(nums = [1, 2, 3, 2, 1, 2, 3, 2, 1],k = 3) == -1
    assert candidate(nums = [42],k = 1) == 42
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],k = 1) == 19
    assert candidate(nums = [1, 1, 1, 1, 1],k = 1) == -1
    assert candidate(nums = [3, 9, 7, 2, 1, 7],k = 4) == 3
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],k = 10) == 19
    assert candidate(nums = [3, 9, 2, 1, 7],k = 3) == 7
    assert candidate(nums = [1, 1, 2, 2, 3, 3],k = 2) == -1
    assert candidate(nums = [0, 0],k = 1) == -1
    assert candidate(nums = [1, 2, 3, 4, 5],k = 1) == 5
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],k = 2) == -1
    assert candidate(nums = [5, 4, 3, 2, 1],k = 3) == 5
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 10) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],k = 4) == 15
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 4) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 7) == 20
    assert candidate(nums = [4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25],k = 10) == 25
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 19) == 20
    assert candidate(nums = [7, 6, 5, 7, 5, 6, 7, 6, 5, 7, 5, 6, 7],k = 7) == -1
    assert candidate(nums = [15, 25, 35, 45, 55, 65, 75, 85, 95, 105],k = 6) == 105
    assert candidate(nums = [15, 25, 15, 30, 25, 30, 15, 25, 30, 15, 25, 30],k = 5) == -1
    assert candidate(nums = [10, 10, 10, 20, 20, 20, 30, 30, 30],k = 2) == -1
    assert candidate(nums = [7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10],k = 3) == -1
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 15) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],k = 5) == 12
    assert candidate(nums = [8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10],k = 5) == -1
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90],k = 4) == 90
    assert candidate(nums = [50, 40, 30, 20, 10, 5, 15, 25, 35, 45, 55, 65, 75, 85, 95],k = 7) == 95
    assert candidate(nums = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3],k = 20) == -1
    assert candidate(nums = [5, 3, 9, 3, 5, 9, 5, 3, 9],k = 3) == -1
    assert candidate(nums = [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3],k = 3) == -1
    assert candidate(nums = [5, 5, 5, 5, 5, 5],k = 3) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],k = 6) == 12
    assert candidate(nums = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50],k = 5) == -1
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 4) == 10
    assert candidate(nums = [15, 20, 25, 30, 35, 40, 45, 50, 55],k = 4) == 55
    assert candidate(nums = [42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42],k = 21) == 42
    assert candidate(nums = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 5) == 15
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 10) == 100
    assert candidate(nums = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3],k = 1) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5],k = 15) == -1
    assert candidate(nums = [1, 2, 2, 1, 3, 3, 1, 2, 1, 2, 3],k = 3) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],k = 5) == 15
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9],k = 4) == -1
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10],k = 4) == -1
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 3) == -1
    assert candidate(nums = [5, 4, 3, 2, 1, 5, 4, 3, 2, 1],k = 5) == -1
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15],k = 15) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],k = 7) == 15
    assert candidate(nums = [5, 2, 5, 3, 5, 2, 5, 3, 5, 2, 5],k = 3) == -1
    assert candidate(nums = [7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7],k = 20) == 7
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 5) == 20
    assert candidate(nums = [42, 24, 42, 24, 42, 24, 42, 24],k = 5) == -1
    assert candidate(nums = [8, 6, 4, 2, 0, 2, 4, 6, 8, 10, 12, 14],k = 5) == 14
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5],k = 10) == -1
    assert candidate(nums = [7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7],k = 3) == -1
    assert candidate(nums = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9],k = 4) == 1
    assert candidate(nums = [7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6],k = 7) == 7
    assert candidate(nums = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4],k = 3) == -1
    assert candidate(nums = [10, 20, 10, 30, 10, 20, 30, 10, 20, 30, 10, 20, 30],k = 5) == -1
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9],k = 5) == -1
    assert candidate(nums = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97],k = 10) == 97
    assert candidate(nums = [8, 6, 4, 2, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31],k = 3) == 31
    assert candidate(nums = [5, 3, 5, 2, 5, 3, 5],k = 3) == -1
    assert candidate(nums = [1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5],k = 3) == 5
    assert candidate(nums = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2],k = 5) == -1
    assert candidate(nums = [50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0],k = 25) == 50
    assert candidate(nums = [7, 7, 7, 7, 7, 7, 7, 7, 7, 7],k = 2) == -1
    assert candidate(nums = [23, 45, 67, 89, 23, 45, 67, 89, 23, 45, 67, 89, 23, 45, 67, 89],k = 8) == -1
    assert candidate(nums = [29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0],k = 10) == 29
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 4) == 10
    assert candidate(nums = [5, 4, 3, 2, 1, 5, 4, 3, 2, 1],k = 5) == -1
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6],k = 2) == -1
    assert candidate(nums = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31],k = 4) == 31
    assert candidate(nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30],k = 15) == 30
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 5) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 2) == 20
    assert candidate(nums = [5, 15, 25, 35, 45, 55, 65, 75],k = 4) == 75
    assert candidate(nums = [50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 25) == 50
    assert candidate(nums = [10, 20, 10, 30, 20, 40, 30, 50, 40, 60],k = 4) == 60
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90],k = 5) == 90
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50],k = 50) == 50
    assert candidate(nums = [7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8],k = 9) == -1
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 6) == 10
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5) == 10
    assert candidate(nums = [5, 15, 25, 35, 45, 55, 65],k = 3) == 65
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25],k = 12) == 25
    assert candidate(nums = [42, 42, 42, 42, 42, 42, 41, 41, 41, 41, 40, 40, 40, 39, 39],k = 3) == -1
    assert candidate(nums = [45, 45, 45, 45, 45, 45, 45],k = 3) == -1
    assert candidate(nums = [5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1],k = 6) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 20) == 20
    assert candidate(nums = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29],k = 5) == 29
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 10) == 20
    assert candidate(nums = [5, 8, 5, 9, 8, 9, 10, 8, 10, 9],k = 4) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 10) == 20
    assert candidate(nums = [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 5) == 20
    assert candidate(nums = [42, 42, 42, 42, 42, 42, 42, 42, 42, 42],k = 10) == 42
    assert candidate(nums = [1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2],k = 10) == -1
    assert candidate(nums = [1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10],k = 2) == 1
    assert candidate(nums = [10, 10, 20, 20, 30, 30, 40, 40, 50, 50],k = 3) == -1
    assert candidate(nums = [34, 23, 12, 45, 67, 89, 10, 20, 30, 40, 50, 60, 70, 80, 90],k = 6) == 90
    assert candidate(nums = [15, 20, 15, 20, 15, 20, 15, 20, 15, 20],k = 4) == -1
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3],k = 7) == -1
    assert candidate(nums = [3, 6, 3, 9, 6, 9, 12, 6, 12, 9, 12, 9, 3, 6, 9, 3, 6, 9],k = 6) == -1
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20],k = 5) == -1
    assert candidate(nums = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],k = 6) == 20
    assert candidate(nums = [7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11],k = 3) == -1
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 10) == -1


# === INVOCATION ===
check(Solution().largestInteger)
print("All tests passed")
