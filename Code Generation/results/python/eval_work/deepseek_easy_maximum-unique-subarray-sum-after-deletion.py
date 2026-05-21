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
    def maxSum(self, nums: List[int]) -> int:
        n = len(nums)
        max_sum = float('-inf')
        
        # Try every possible subarray
        for i in range(n):
            seen = set()
            current_sum = 0
            
            for j in range(i, n):
                if nums[j] in seen:
                    break
                seen.add(nums[j])
                current_sum += nums[j]
                max_sum = max(max_sum, current_sum)
        
        return max_sum

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [-1, 2, -3, 4, -5]) == 6
    assert candidate(nums = [-10, 1, 20, -30, 40, -50, 60]) == 121
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [1, -1, 1, -1, 1, -1]) == 1
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1]) == 1
    assert candidate(nums = [100, -100, 50, -50, 25, -25]) == 175
    assert candidate(nums = [10, 20, 30, 40, 50]) == 150
    assert candidate(nums = [5, 5, 5, 5, 5]) == 5
    assert candidate(nums = [-1, -2, -3, -4, -5]) == -1
    assert candidate(nums = [0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [1, 2, 3, 4, 5]) == 15
    assert candidate(nums = [1, 2, 3, 1, 2, 3, 1, 2, 3]) == 6
    assert candidate(nums = [100, -100, 100, -100, 100]) == 100
    assert candidate(nums = [10, -2, 3, 4, -1, 2]) == 19
    assert candidate(nums = [1, 2, 2, 3, 4, 5, 5, 6]) == 21
    assert candidate(nums = [-1, 2, -3, 4, -5, 6]) == 12
    assert candidate(nums = [1, 2, 3, 2, 1]) == 6
    assert candidate(nums = [1, 2, -1, -2, 1, 0, -1]) == 3
    assert candidate(nums = [50, 50, 50, -50, 50, -50, 50]) == 50
    assert candidate(nums = [1, 1, 0, 1, 1]) == 1
    assert candidate(nums = [1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10]) == 55
    assert candidate(nums = [10, 20, 30, 10, 40, 50, 20, 60]) == 210
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == 55
    assert candidate(nums = [5, -5, 10, -10, 15, -15, 20, -20, 25, -25]) == 75
    assert candidate(nums = [-5, -1, -3, -4, -2, -3, -1, -2, -4]) == -1
    assert candidate(nums = [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 210
    assert candidate(nums = [3, -1, 4, -1, 5, 9, -2, 6, 5, 3, 5, -9, 7, 9, -3, 2, 3, 8, 4, 6]) == 44
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1]) == 1
    assert candidate(nums = [99, -99, 49, -49, 24, -24, 12, -12, 6, -6, 3, -3, 1, -1, 0, 1, -1, 0]) == 194
    assert candidate(nums = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5]) == 15
    assert candidate(nums = [5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5]) == 15
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == 45
    assert candidate(nums = [1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3]) == 6
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == 55
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10]) == 55
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60]) == 210
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5]) == 15
    assert candidate(nums = [10, 20, 10, 20, 10, 20, 10, 20, 10, 20]) == 30
    assert candidate(nums = [1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1]) == 15
    assert candidate(nums = [10, 20, 30, 40, 50, -10, -20, -30, -40, -50, 60, 70, 80, 90, 100]) == 550
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == 55
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, 19, -20]) == 100
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -2, -3, -4, -5, -6, -7, -8, -9, -10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 210
    assert candidate(nums = [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5]) == 15
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5]) == 55
    assert candidate(nums = [3, 1, 2, 1, 3, 4, 5, 2, 6, 7, 8, 9, 1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 210
    assert candidate(nums = [10, 20, 30, 40, 50, 40, 30, 20, 10, 10, 20, 30, 40, 50, 40, 30, 20, 10]) == 150
    assert candidate(nums = [-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -10, 9, -8, 7, -6, 5, -4, 3, -2, 1]) == 55
    assert candidate(nums = [-5, -1, -3, -2, -4, -1, -2, -3, -5]) == -1
    assert candidate(nums = [5, -5, 10, -10, 15, -15, 20, -20, 25]) == 75
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10]) == 55
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == 210
    assert candidate(nums = [0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10, 0, 1, -1, 2, -2, 3, -3, 4, -4]) == 55
    assert candidate(nums = [10, 20, 30, 40, 50, 50, 40, 30, 20, 10, 10, 20, 30, 40, 50, 50, 40, 30, 20, 10]) == 150
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5]) == 210
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1]) == 55
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 210
    assert candidate(nums = [-99, 99, -98, 98, -97, 97, -96, 96, -95, 95, -94, 94, -93, 93, -92, 92, -91, 91, -90, 90]) == 945
    assert candidate(nums = [-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15, 16, -17, 18, -19, 20]) == 110
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == 55
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 5
    assert candidate(nums = [-1, -2, -3, -4, -5, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == -1
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 55
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -1, 2, -3]) == 30
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 210
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30]) == 465
    assert candidate(nums = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 120
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 55
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 5
    assert candidate(nums = [100, -90, 80, -70, 60, -50, 40, -30, 20, -10]) == 300
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10]) == 55
    assert candidate(nums = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 550
    assert candidate(nums = [1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8]) == 36
    assert candidate(nums = [10, 20, 30, 40, 50, 40, 30, 20, 10]) == 150
    assert candidate(nums = [50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50]) == 50
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == 45
    assert candidate(nums = [3, 1, 2, 3, 2, 4, 5, 1, 6, 5, 7, 8, 7, 9, 10]) == 55
    assert candidate(nums = [0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9]) == 45
    assert candidate(nums = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50]) == 150
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]) == 30
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6, -7, 7, -8, 8, -9, 9, -10, 10, -11, 11, -12, 12, -13, 13, -14, 14, -15, 15, -16, 16, -17, 17, -18, 18, -19, 19, -20, 20]) == 210
    assert candidate(nums = [10, 20, 30, 10, 40, 50, 20, 60, 70]) == 280
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10]) == 25
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20]) == 210
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 210
    assert candidate(nums = [50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50]) == 50
    assert candidate(nums = [100, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50]) == 150
    assert candidate(nums = [10, 20, 30, -10, -20, -30, 40, 50, 60, -40, -50, -60, 70, 80, 90]) == 450
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0]) == 45
    assert candidate(nums = [-5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0]) == 5
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0, -10, -20, -30, -40]) == 550
    assert candidate(nums = [0, -1, 2, -2, 1, -1, 3, -3, 4, -4, 5, -5, 6, -6]) == 21
    assert candidate(nums = [3, 1, 2, 1, 3, 4, 2, 5]) == 15
    assert candidate(nums = [1, 2, 3, 2, 4, 5, 6, 5, 7, 8, 9, 8, 10]) == 55
    assert candidate(nums = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0, -10, -20, -30, -40, -50, -60, -70, -80, -90, -100]) == 550
    assert candidate(nums = [10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]) == 1045
    assert candidate(nums = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1]) == -1
    assert candidate(nums = [5, -1, 3, 5, -2, 3, 4, -1, 2, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4]) == 45
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 210
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60, 70, -70, 80, -80, 90, -90, 100, -100]) == 550
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 1
    assert candidate(nums = [10, 20, 10, 30, 40, 20, 50, 60, 30]) == 210
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8]) == 45
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5]) == 55
    assert candidate(nums = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [5, 3, -5, 2, 3, 3, 9, -2, 4, 5, 6, 7, 8, 9, 10]) == 54
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == -1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 55
    assert candidate(nums = [1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 10, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20]) == 210
    assert candidate(nums = [-1, -2, -3, -4, -5, -1, -2]) == -1
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 5


# === INVOCATION ===
check(Solution().maxSum)
print("All tests passed")
