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
class Solution:
    def maxContainers(self, n: int, w: int, maxWeight: int) -> int:
        total_cells = n * n
        max_by_weight = maxWeight // w
        return min(total_cells, max_by_weight)

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(n = 10,w = 5,maxWeight = 25) == 5
    assert candidate(n = 10,w = 1,maxWeight = 10) == 10
    assert candidate(n = 5,w = 2,maxWeight = 20) == 10
    assert candidate(n = 5,w = 10,maxWeight = 50) == 5
    assert candidate(n = 5,w = 10,maxWeight = 100) == 10
    assert candidate(n = 1000,w = 1000,maxWeight = 1000000000) == 1000000
    assert candidate(n = 2,w = 3,maxWeight = 15) == 4
    assert candidate(n = 7,w = 10,maxWeight = 50) == 5
    assert candidate(n = 1,w = 1,maxWeight = 1) == 1
    assert candidate(n = 7,w = 3,maxWeight = 60) == 20
    assert candidate(n = 4,w = 5,maxWeight = 10) == 2
    assert candidate(n = 7,w = 2,maxWeight = 50) == 25
    assert candidate(n = 3,w = 5,maxWeight = 20) == 4
    assert candidate(n = 1,w = 1,maxWeight = 1000) == 1
    assert candidate(n = 333,w = 334,maxWeight = 100000) == 299
    assert candidate(n = 150,w = 150,maxWeight = 22499) == 149
    assert candidate(n = 600,w = 50,maxWeight = 25000) == 500
    assert candidate(n = 800,w = 125,maxWeight = 10000000) == 80000
    assert candidate(n = 100,w = 50,maxWeight = 4500) == 90
    assert candidate(n = 100,w = 50,maxWeight = 4900) == 98
    assert candidate(n = 500,w = 200,maxWeight = 99999999) == 250000
    assert candidate(n = 250,w = 350,maxWeight = 875000) == 2500
    assert candidate(n = 200,w = 25,maxWeight = 4999) == 199
    assert candidate(n = 750,w = 100,maxWeight = 50000) == 500
    assert candidate(n = 100,w = 500,maxWeight = 45000) == 90
    assert candidate(n = 666,w = 166,maxWeight = 100000000) == 443556
    assert candidate(n = 400,w = 250,maxWeight = 1000000) == 4000
    assert candidate(n = 550,w = 800,maxWeight = 4400000) == 5500
    assert candidate(n = 400,w = 250,maxWeight = 100000) == 400
    assert candidate(n = 999,w = 500,maxWeight = 499500) == 999
    assert candidate(n = 100,w = 1001,maxWeight = 100100) == 100
    assert candidate(n = 750,w = 300,maxWeight = 675000) == 2250
    assert candidate(n = 600,w = 1200,maxWeight = 7200000) == 6000
    assert candidate(n = 333,w = 333,maxWeight = 333333333) == 110889
    assert candidate(n = 678,w = 9,maxWeight = 6000) == 666
    assert candidate(n = 250,w = 50,maxWeight = 12499) == 249
    assert candidate(n = 750,w = 200,maxWeight = 150000) == 750
    assert candidate(n = 5,w = 200,maxWeight = 999) == 4
    assert candidate(n = 999,w = 999,maxWeight = 998001) == 999
    assert candidate(n = 800,w = 500,maxWeight = 399999) == 799
    assert candidate(n = 600,w = 400,maxWeight = 250000) == 625
    assert candidate(n = 666,w = 150,maxWeight = 100000) == 666
    assert candidate(n = 250,w = 400,maxWeight = 100000) == 250
    assert candidate(n = 1000,w = 1,maxWeight = 500) == 500
    assert candidate(n = 5,w = 100,maxWeight = 200) == 2
    assert candidate(n = 250,w = 400,maxWeight = 1000000) == 2500
    assert candidate(n = 1000,w = 500,maxWeight = 500000) == 1000
    assert candidate(n = 400,w = 200,maxWeight = 79999) == 399
    assert candidate(n = 500,w = 200,maxWeight = 1000000) == 5000
    assert candidate(n = 400,w = 50,maxWeight = 99999) == 1999
    assert candidate(n = 200,w = 999,maxWeight = 200000) == 200
    assert candidate(n = 200,w = 15,maxWeight = 5000) == 333
    assert candidate(n = 300,w = 150,maxWeight = 50000) == 333
    assert candidate(n = 900,w = 300,maxWeight = 270000) == 900
    assert candidate(n = 500,w = 7,maxWeight = 350000) == 50000
    assert candidate(n = 500,w = 750,maxWeight = 300000) == 400
    assert candidate(n = 200,w = 1,maxWeight = 100) == 100
    assert candidate(n = 800,w = 10,maxWeight = 8000) == 800
    assert candidate(n = 900,w = 950,maxWeight = 855000000) == 810000
    assert candidate(n = 500,w = 50,maxWeight = 125000) == 2500
    assert candidate(n = 800,w = 50,maxWeight = 20000) == 400
    assert candidate(n = 750,w = 50,maxWeight = 180000) == 3600
    assert candidate(n = 666,w = 667,maxWeight = 500000) == 749
    assert candidate(n = 10,w = 10,maxWeight = 99) == 9
    assert candidate(n = 1000,w = 900,maxWeight = 900000) == 1000
    assert candidate(n = 5,w = 5000,maxWeight = 25000) == 5
    assert candidate(n = 250,w = 75,maxWeight = 20000) == 266
    assert candidate(n = 1000,w = 1000,maxWeight = 999999999) == 999999
    assert candidate(n = 999,w = 1,maxWeight = 999) == 999
    assert candidate(n = 250,w = 100,maxWeight = 24900) == 249
    assert candidate(n = 500,w = 250,maxWeight = 100000000) == 250000
    assert candidate(n = 999,w = 999,maxWeight = 999000000) == 998001
    assert candidate(n = 999,w = 1,maxWeight = 1000000000) == 998001
    assert candidate(n = 1000,w = 999,maxWeight = 998001) == 999
    assert candidate(n = 750,w = 150,maxWeight = 112500) == 750
    assert candidate(n = 500,w = 50,maxWeight = 100000) == 2000
    assert candidate(n = 800,w = 1000,maxWeight = 800000) == 800
    assert candidate(n = 333,w = 333,maxWeight = 33266667) == 99899
    assert candidate(n = 1,w = 1000000000,maxWeight = 1000000000) == 1
    assert candidate(n = 600,w = 60,maxWeight = 359999) == 5999
    assert candidate(n = 200,w = 300,maxWeight = 60000) == 200
    assert candidate(n = 123,w = 456,maxWeight = 67890123) == 15129
    assert candidate(n = 300,w = 100,maxWeight = 25000) == 250
    assert candidate(n = 200,w = 1000,maxWeight = 199000) == 199
    assert candidate(n = 750,w = 123,maxWeight = 1000000) == 8130
    assert candidate(n = 10,w = 999,maxWeight = 9990) == 10
    assert candidate(n = 500,w = 250,maxWeight = 125000) == 500
    assert candidate(n = 800,w = 100,maxWeight = 80000) == 800
    assert candidate(n = 300,w = 700,maxWeight = 2000000) == 2857
    assert candidate(n = 500,w = 2,maxWeight = 1000) == 500
    assert candidate(n = 300,w = 200,maxWeight = 60000) == 300
    assert candidate(n = 800,w = 10,maxWeight = 7900) == 790
    assert candidate(n = 500,w = 10,maxWeight = 4990) == 499
    assert candidate(n = 800,w = 150,maxWeight = 1200000) == 8000
    assert candidate(n = 800,w = 125,maxWeight = 100000) == 800
    assert candidate(n = 650,w = 100,maxWeight = 70000) == 700
    assert candidate(n = 750,w = 75,maxWeight = 450000) == 6000
    assert candidate(n = 50,w = 200,maxWeight = 19999) == 99
    assert candidate(n = 500,w = 750,maxWeight = 375000) == 500
    assert candidate(n = 400,w = 400,maxWeight = 599999) == 1499
    assert candidate(n = 10,w = 100,maxWeight = 1000) == 10
    assert candidate(n = 250,w = 333,maxWeight = 83250) == 250
    assert candidate(n = 50,w = 100,maxWeight = 4500) == 45
    assert candidate(n = 150,w = 25,maxWeight = 3749) == 149
    assert candidate(n = 900,w = 50,maxWeight = 45000) == 900
    assert candidate(n = 100,w = 10,maxWeight = 999) == 99
    assert candidate(n = 1000,w = 1,maxWeight = 999) == 999
    assert candidate(n = 750,w = 300,maxWeight = 500000000) == 562500
    assert candidate(n = 15,w = 15,maxWeight = 225) == 15
    assert candidate(n = 750,w = 20,maxWeight = 14500) == 725
    assert candidate(n = 500,w = 250,maxWeight = 500000) == 2000
    assert candidate(n = 1000,w = 10,maxWeight = 9999999) == 999999
    assert candidate(n = 100,w = 100,maxWeight = 5000) == 50
    assert candidate(n = 333,w = 250,maxWeight = 200000) == 800
    assert candidate(n = 900,w = 90,maxWeight = 729000) == 8100


# === INVOCATION ===
check(Solution().maxContainers)
print("All tests passed")
