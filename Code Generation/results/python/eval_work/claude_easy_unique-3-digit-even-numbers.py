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
from itertools import permutations

class Solution:
    def totalNumbers(self, digits: List[int]) -> int:
        seen = set()
        for perm in permutations(digits, 3):
            if perm[0] != 0 and perm[2] % 2 == 0:
                seen.add(perm[0] * 100 + perm[1] * 10 + perm[2])
        return len(seen)

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 0
    assert candidate(digits = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]) == 1
    assert candidate(digits = [6, 6, 6]) == 1
    assert candidate(digits = [1, 3, 5]) == 0
    assert candidate(digits = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) == 1
    assert candidate(digits = [1, 0, 2, 3, 5, 7, 9]) == 55
    assert candidate(digits = [9, 9, 9, 9, 9, 9, 9, 9, 9, 9]) == 0
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]) == 328
    assert candidate(digits = [0, 0, 0]) == 0
    assert candidate(digits = [2, 0, 0, 2]) == 3
    assert candidate(digits = [1, 2, 3]) == 2
    assert candidate(digits = [2, 2, 2, 2]) == 1
    assert candidate(digits = [2, 1, 3, 4, 2, 4, 2, 4, 2, 2]) == 28
    assert candidate(digits = [2, 2, 0, 0, 2, 2]) == 4
    assert candidate(digits = [0, 2, 2]) == 2
    assert candidate(digits = [0, 1, 3, 5, 7, 9]) == 20
    assert candidate(digits = [8, 6, 8, 6, 8, 6, 8, 6, 8, 6]) == 8
    assert candidate(digits = [2, 4, 6, 8, 0]) == 48
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 0]) == 1
    assert candidate(digits = [8, 0, 7, 4, 9, 3, 0, 3, 0, 9]) == 63
    assert candidate(digits = [1, 0, 1, 0, 1, 0]) == 2
    assert candidate(digits = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5]) == 48
    assert candidate(digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == 328
    assert candidate(digits = [1, 1, 2, 2, 3, 3]) == 8
    assert candidate(digits = [1, 2, 3, 4]) == 12
    assert candidate(digits = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]) == 328
    assert candidate(digits = [1, 0, 0, 2]) == 5
    assert candidate(digits = [0, 0, 2, 2, 4, 4, 6, 6, 8, 8]) == 96
    assert candidate(digits = [0, 0, 0, 0, 0, 0, 0, 0, 0, 3]) == 1
    assert candidate(digits = [0, 0, 0, 1, 1, 1, 2, 2, 2]) == 12
    assert candidate(digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0]) == 337
    assert candidate(digits = [0, 2, 4, 6, 8, 0, 2, 4, 6, 8, 0, 2, 4, 6]) == 99
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 2, 2, 2, 2]) == 4
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0]) == 446
    assert candidate(digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 0]) == 260
    assert candidate(digits = [9, 9, 9, 9, 9, 9, 9, 9, 9, 0]) == 1
    assert candidate(digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0]) == 337
    assert candidate(digits = [0, 1, 2, 2, 3, 4, 5]) == 63
    assert candidate(digits = [9, 9, 9, 9, 9, 9, 8, 8, 8, 8]) == 4
    assert candidate(digits = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4]) == 24
    assert candidate(digits = [1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 1]) == 0
    assert candidate(digits = [1, 2, 2, 3, 4, 4, 5, 6, 7, 8]) == 202
    assert candidate(digits = [0, 2, 4, 6, 8, 0, 2, 4, 6, 8, 0, 2]) == 97
    assert candidate(digits = [5, 5, 5, 5, 5, 5, 5, 5, 5, 0]) == 1
    assert candidate(digits = [0, 0, 0, 0, 1, 1, 1, 1, 2, 2]) == 11
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 0
    assert candidate(digits = [5, 5, 5, 5, 7, 7, 7, 7, 9, 9]) == 0
    assert candidate(digits = [0, 2, 4, 6, 8, 0, 2, 4, 6, 8]) == 96
    assert candidate(digits = [0, 1, 1, 2, 2, 3, 3, 4, 4, 5]) == 80
    assert candidate(digits = [1, 3, 5, 7, 9, 1, 3, 5, 7, 9]) == 0
    assert candidate(digits = [0, 0, 1, 1, 2, 2, 3, 3, 4, 4]) == 58
    assert candidate(digits = [1, 1, 1, 1, 2, 2, 2, 2, 3, 3]) == 9
    assert candidate(digits = [2, 4, 6, 8, 0, 1, 3, 5, 7, 9, 2]) == 349
    assert candidate(digits = [2, 4, 6, 8, 1, 3, 5, 7, 9, 0]) == 328
    assert candidate(digits = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) == 1
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9]) == 228
    assert candidate(digits = [1, 2, 3, 4, 5, 6]) == 60
    assert candidate(digits = [0, 0, 1, 1, 2, 2, 3, 3, 4, 4]) == 58
    assert candidate(digits = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4]) == 32
    assert candidate(digits = [8, 8, 8, 8, 8, 8, 8, 8, 8, 8]) == 1
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0]) == 337
    assert candidate(digits = [5, 5, 5, 5, 5, 5, 5, 5, 5, 9]) == 0
    assert candidate(digits = [9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9]) == 0
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0]) == 337
    assert candidate(digits = [2, 4, 6, 8, 0, 2, 4, 6, 8, 0]) == 96
    assert candidate(digits = [1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 1, 3]) == 0
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4]) == 380
    assert candidate(digits = [0, 2, 4, 6, 8, 2, 4, 6, 8, 0]) == 96
    assert candidate(digits = [7, 7, 7, 7, 7, 7, 7, 7, 7, 0]) == 1
    assert candidate(digits = [0, 0, 0, 0, 0, 0, 0, 0, 0, 2]) == 1
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9]) == 224
    assert candidate(digits = [2, 4, 6, 8, 0, 0, 0, 0, 0, 0]) == 52
    assert candidate(digits = [2, 4, 6, 8, 0, 1, 3, 5, 7, 9]) == 328
    assert candidate(digits = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 3]) == 0
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 2]) == 349
    assert candidate(digits = [7, 7, 7, 7, 7, 7, 7, 7, 7, 2]) == 1
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 2]) == 1
    assert candidate(digits = [2, 2, 2, 2, 2, 2, 2, 2, 2, 0]) == 3
    assert candidate(digits = [0, 0, 0, 0, 0, 1, 1, 1, 2, 2]) == 11
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0]) == 328
    assert candidate(digits = [1, 3, 5, 7, 9, 1, 3, 5, 7, 9]) == 0
    assert candidate(digits = [0, 2, 4, 6, 8, 1, 3, 5, 7, 9]) == 328
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 2]) == 1
    assert candidate(digits = [1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 9]) == 0
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 9]) == 228
    assert candidate(digits = [2, 2, 4, 4, 6, 6, 8, 8, 0, 0]) == 96
    assert candidate(digits = [0, 0, 0, 1, 1, 1, 2, 2, 2]) == 12
    assert candidate(digits = [7, 7, 7, 8, 8, 8, 9, 9, 9, 0]) == 21
    assert candidate(digits = [1, 3, 5, 7, 9, 0, 2, 4, 6, 8]) == 328
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1]) == 333
    assert candidate(digits = [0, 2, 4, 6, 8, 0, 2, 4, 6, 8]) == 96
    assert candidate(digits = [2, 4, 6, 8, 0, 2, 4, 6, 8, 0]) == 96
    assert candidate(digits = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5]) == 48
    assert candidate(digits = [9, 0, 1, 2, 3, 4, 5, 6, 7, 8]) == 328
    assert candidate(digits = [2, 4, 6, 8, 0, 0, 0, 1, 3, 5]) == 193
    assert candidate(digits = [2, 4, 6, 8, 0, 2, 4, 6, 8, 0, 2, 4]) == 98
    assert candidate(digits = [1, 0, 1, 0, 1, 0, 1, 0, 1, 0]) == 2
    assert candidate(digits = [1, 2, 2, 3, 3, 3, 4, 5, 6, 6]) == 87
    assert candidate(digits = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4]) == 24
    assert candidate(digits = [2, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 1
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2]) == 1
    assert candidate(digits = [1, 3, 5, 7, 9, 2, 4, 6, 8, 0]) == 328
    assert candidate(digits = [2, 2, 4, 4, 6, 6, 8, 8, 0, 0]) == 96
    assert candidate(digits = [1, 2, 2, 3, 3, 4, 4, 5, 5, 6]) == 90
    assert candidate(digits = [9, 9, 8, 8, 7, 7, 6, 6, 5, 5]) == 48
    assert candidate(digits = [1, 1, 1, 1, 2, 2, 2, 2, 3, 3]) == 9
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0]) == 337
    assert candidate(digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0]) == 337
    assert candidate(digits = [7, 7, 8, 8, 9, 9, 0, 0]) == 23
    assert candidate(digits = [0, 1, 2, 3, 4, 4, 5, 6, 7, 8]) == 271
    assert candidate(digits = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 0
    assert candidate(digits = [1, 1, 1, 1, 1, 1, 1, 1, 2, 2]) == 3
    assert candidate(digits = [9, 9, 9, 8, 8, 8, 7, 7, 7, 6, 6, 6]) == 32
    assert candidate(digits = [0, 0, 0, 0, 0, 0, 0, 0, 1, 3]) == 4
    assert candidate(digits = [1, 1, 1, 1, 1, 2, 2, 2, 2, 2]) == 4
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1]) == 228
    assert candidate(digits = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) == 1
    assert candidate(digits = [0, 0, 0, 0, 0, 0, 0, 0, 0, 1]) == 1
    assert candidate(digits = [0, 0, 0, 0, 0, 0, 0, 0, 0, 1]) == 1
    assert candidate(digits = [1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6]) == 102
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 3]) == 232
    assert candidate(digits = [2, 4, 6, 8, 2, 4, 6, 8, 0, 0]) == 96
    assert candidate(digits = [1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0]) == 337
    assert candidate(digits = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]) == 328
    assert candidate(digits = [0, 1, 1, 1, 2, 2, 2, 3, 3, 3]) == 21
    assert candidate(digits = [7, 8, 9, 0, 2, 4, 6, 8, 0, 2]) == 166
    assert candidate(digits = [0, 0, 2, 2, 4, 4, 6, 6, 8, 8]) == 96


# === INVOCATION ===
check(Solution().totalNumbers)
print("All tests passed")
