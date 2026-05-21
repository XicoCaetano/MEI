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
    def maxScore(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2:
            return 0
        
        if n % 2 == 1:
            min_rem = min(nums)
        else:
            min_rem = min(nums[i] + nums[i+1] for i in range(n - 1))
            
        return sum(nums) - min_rem

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 8
    assert candidate(nums = [5, -1, 4, 2]) == 7
    assert candidate(nums = [10000, -10000, 10000, -10000, 10000]) == 20000
    assert candidate(nums = [1, 2, 3]) == 5
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 52
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 52
    assert candidate(nums = [1]) == 0
    assert candidate(nums = [-5, 5, -5, 5, -5, 5]) == 0
    assert candidate(nums = [1, 2]) == 0
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50]) == 90
    assert candidate(nums = [5, 1, 5, 1, 5, 1, 5, 1, 5, 1]) == 24
    assert candidate(nums = [2, 4, 1]) == 6
    assert candidate(nums = [-1, -2, -3, -4, -5]) == -10
    assert candidate(nums = [-5, -4, -3, -2, -1]) == -10
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1]) == 0
    assert candidate(nums = [10000, -10000, 10000, -10000, 10000]) == 20000
    assert candidate(nums = [1, 2, 3, 4, 5]) == 14
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 8
    assert candidate(nums = [10, -10, 20, -20, 30]) == 50
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [100, -50, 200, -300, 400, -500, 600, -700, 800, -900]) == -250
    assert candidate(nums = [1, 2]) == 0
    assert candidate(nums = [0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [1, -1, 2, -2, 3, -3]) == 0
    assert candidate(nums = [1, 2, 3]) == 5
    assert candidate(nums = [29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1]) == 224
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31]) == 252
    assert candidate(nums = [100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110]) == 1055
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]) == 11900
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60, 70, -70, 80, -80, 90, -90, 100, -100]) == 0
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20]) == -171
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]) == 5200
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 900, 800, 700, 600, 500, 400, 300, 200, 100]) == 9900
    assert candidate(nums = [0, 1, 0, -1, 0, 2, 0, -2, 0, 3, 0, -3, 0, 4, 0, -4, 0, 5, 0, -5]) == 5
    assert candidate(nums = [1000, -1000, 500, -500, 250, -250, 125, -125, 62, -62]) == 500
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29]) == 224
    assert candidate(nums = [5, -5, 5, -5, 5, -5, 5, -5, 5, -5]) == 0
    assert candidate(nums = [100, -100, 200, -200, 300, -300, 400, -400, 500, -500]) == 0
    assert candidate(nums = [100, 100, -50, -50, 200, -300, 400, -500, 600, -700]) == -100
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, 19, -20]) == -9
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000]) == 20700
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130]) == 900
    assert candidate(nums = [99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110]) == 1055
    assert candidate(nums = [-1, -3, -5, -7, -9, -11, -13, -15, -17, -19]) == -64
    assert candidate(nums = [3, 1, -2, 5, 7, -10, 15]) == 29
    assert candidate(nums = [-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110, -120, -130]) == -780
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 28
    assert candidate(nums = [1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000]) == 5000005
    assert candidate(nums = [1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10]) == 65
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10]) == 990
    assert candidate(nums = [10, -20, 30, -40, 50, -60, 70]) == 100
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]) == 324
    assert candidate(nums = [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 1, 2, 3, 4, 5]) == 1111111125
    assert candidate(nums = [-10, 100, -20, 200, -30, 300, -40, 400]) == 820
    assert candidate(nums = [5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5]) == 30
    assert candidate(nums = [1000, -1000, 2000, -2000, 3000, -3000, 4000, -4000, 5000, -5000]) == 0
    assert candidate(nums = [5, 1, 3, 7, 9, 2, 6, 4, 8, 10, 12, 14]) == 77
    assert candidate(nums = [5, 3, 8, 1, 9, 4, 7, 6, 2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 202
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 52
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10]) == 0
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]) == 96
    assert candidate(nums = [-1, -3, -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29]) == -196
    assert candidate(nums = [-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110]) == -550
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1]) == 2
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 119
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, -500, -400, -300, -200, -100]) == 4500
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 52
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10]) == -4
    assert candidate(nums = [-1, 2, -3, 4, -5, 6]) == 4
    assert candidate(nums = [10000, -10000, 10000, -10000, 10000, -10000]) == 0
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100]) == 6500
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]) == 43
    assert candidate(nums = [1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14]) == 119
    assert candidate(nums = [-100, -200, 300, 400, -500, 600]) == 800
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120]) == 750
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 207
    assert candidate(nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 119
    assert candidate(nums = [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1]) == -36
    assert candidate(nums = [1000, -999, 888, -777, 666, -555, 444, -333, 222, -111]) == 556
    assert candidate(nums = [10, -20, 30, -40, 50, -60, 70, -80, 90, -100]) == -40
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13]) == 48
    assert candidate(nums = [3, 1, 2, 4, 5, 6]) == 18
    assert candidate(nums = [-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6, -7, 7, -8, 8, -9, 9, -10, 10]) == 1
    assert candidate(nums = [5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5]) == 5
    assert candidate(nums = [-1, 2, -3, 4, -5, 6, -7, 8, -9, 10]) == 6
    assert candidate(nums = [5, 3, 8, 2, 4, 7, 1, 6, 9, 0]) == 39
    assert candidate(nums = [-100, -101, -102, -103, -104, -105, -106, -107, -108, -109, -110]) == -1045
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == -36
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5]) == 0
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 520
    assert candidate(nums = [5, -1, 4, 2, 3, 6, -2, 8, -3, 7]) == 26
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 18
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1]) == 0
    assert candidate(nums = [-1000, 2000, -3000, 4000, -5000, 6000, -7000, 8000, -9000, 10000]) == 6000
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]) == 44
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 70
    assert candidate(nums = [1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]) == 231
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1]) == 0
    assert candidate(nums = [100, -50, 25, -10, 15, 20, -30]) == 120
    assert candidate(nums = [0, 10000, -10000, 10000, -10000, 0, 10000, -10000, 10000, -10000]) == 10000
    assert candidate(nums = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]) == 52000


# === INVOCATION ===
check(Solution().maxScore)
print("All tests passed")
