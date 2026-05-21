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
    def minTime(self, skill: List[int], mana: List[int]) -> int:
        n = len(skill)
        m = len(mana)
        
        # List of start times for each wizard for each potion
        start_times = [[0] * m for _ in range(n)]
        
        # Time when each wizard finishes the previous potion
        finish_time = [0] * n
        
        # Process potions sequentially
        for j in range(m):
            # Start time for wizard 0 on potion j
            # Must be at least the previous finish time of wizard 0
            start_times[0][j] = finish_time[0]
            
            # Compute wizard by wizard
            for i in range(n):
                if i > 0:
                    # Wizard i can start when previous wizard finishes this potion
                    # OR when wizard i finishes previous potion (whichever is later)
                    start_times[i][j] = max(start_times[i-1][j] + skill[i-1] * mana[j], finish_time[i])
                
                # Update finish time for this wizard on this potion
                finish_time[i] = start_times[i][j] + skill[i] * mana[j]
        
        # Return total time (when last wizard finishes last potion)
        return finish_time[n-1]

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(skill = [10, 20, 30],mana = [1, 2, 3, 4, 5]) == 490
    assert candidate(skill = [3, 2, 1],mana = [6, 5, 4]) == 57
    assert candidate(skill = [1, 1, 1],mana = [1, 1, 1]) == 5
    assert candidate(skill = [1, 2, 3],mana = [4, 5, 6, 7]) == 78
    assert candidate(skill = [5000, 5000],mana = [1, 5000]) == 50005000
    assert candidate(skill = [1, 2, 3],mana = [4, 5, 6, 7, 8]) == 102
    assert candidate(skill = [1, 5, 2, 4],mana = [5, 1, 4, 2]) == 110
    assert candidate(skill = [10, 20, 30],mana = [1, 2, 3, 4, 5]) == 490
    assert candidate(skill = [1, 2, 3, 4],mana = [1, 2]) == 21
    assert candidate(skill = [5000, 5000, 5000],mana = [5000, 5000, 5000]) == 125000000
    assert candidate(skill = [3, 1, 4, 1, 5],mana = [9, 2, 6, 5, 3, 5]) == 275
    assert candidate(skill = [2, 3, 4, 5],mana = [1, 2, 3, 4, 5, 6, 7]) == 159
    assert candidate(skill = [1, 1, 2, 2, 3, 3],mana = [1, 2, 3, 4, 5, 6]) == 94
    assert candidate(skill = [10, 20, 30, 40, 50],mana = [5, 10, 15, 20, 25]) == 4750
    assert candidate(skill = [2, 3, 5, 7, 11, 13, 17, 19],mana = [23, 29, 31, 37, 41, 43, 47, 53, 59, 61]) == 9500
    assert candidate(skill = [2, 3, 5, 7, 11],mana = [13, 17, 19, 23, 29, 31, 37, 41]) == 2531
    assert candidate(skill = [100, 100, 100, 100, 100],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 9500
    assert candidate(skill = [5, 5, 5, 5, 5],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 475
    assert candidate(skill = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],mana = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 3375
    assert candidate(skill = [4999, 4998, 4997, 4996],mana = [5000, 4999, 4998, 4997, 4996]) == 199820050
    assert candidate(skill = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],mana = [10, 20, 30, 40, 50]) == 29500
    assert candidate(skill = [100, 200, 300, 400, 500],mana = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 295000
    assert candidate(skill = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29],mana = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29]) == 4585
    assert candidate(skill = [300, 200, 100, 400, 500],mana = [100, 200, 300, 400, 500]) == 1050000
    assert candidate(skill = [1, 2, 3, 4, 5, 6],mana = [6, 5, 4, 3, 2, 1]) == 216
    assert candidate(skill = [4, 3, 2, 1],mana = [100, 200, 300, 400, 500]) == 9000
    assert candidate(skill = [1000, 2000, 3000, 4000, 5000],mana = [1000, 2000, 3000, 4000, 5000]) == 95000000
    assert candidate(skill = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],mana = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]) == 2660
    assert candidate(skill = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],mana = [5000, 5000, 5000, 5000, 5000]) == 475000
    assert candidate(skill = [100, 200, 300, 400, 500, 600],mana = [600, 500, 400, 300, 200, 100]) == 2160000
    assert candidate(skill = [10, 20, 30, 40, 50],mana = [5, 10, 15, 20, 25, 30]) == 6250
    assert candidate(skill = [25, 50, 75, 100, 125, 150, 175, 200, 225, 250],mana = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]) == 1787500
    assert candidate(skill = [100, 200, 300],mana = [50, 25, 75, 100]) == 100000
    assert candidate(skill = [1, 2, 3, 4, 5],mana = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 2950
    assert candidate(skill = [5, 3, 8, 2, 4],mana = [15, 25, 10, 40, 5]) == 1395
    assert candidate(skill = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11]) == 1771
    assert candidate(skill = [29, 65, 12, 48, 77],mana = [31, 89, 17, 63, 54, 20, 41, 73]) == 54255
    assert candidate(skill = [1, 5, 10, 20, 50, 100, 200],mana = [1, 2, 3, 4, 5, 6, 7]) == 5786
    assert candidate(skill = [1500, 1500, 1500, 1500],mana = [2500, 2500, 2500, 2500, 2500]) == 30000000
    assert candidate(skill = [4000, 3000, 2000, 1000],mana = [1000, 2000, 3000, 4000, 5000]) == 90000000
    assert candidate(skill = [100, 200, 300, 400, 500],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 29500
    assert candidate(skill = [3, 6, 9, 12],mana = [10, 20, 30, 40, 50]) == 2100
    assert candidate(skill = [1, 1, 1, 1, 1],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 95
    assert candidate(skill = [1000, 2000, 3000],mana = [500, 1000, 1500, 2000, 2500]) == 24500000
    assert candidate(skill = [100, 150, 200, 250, 300],mana = [50, 100, 150, 200, 250, 300, 350]) == 505000
    assert candidate(skill = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],mana = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 7150
    assert candidate(skill = [7, 14, 21, 28],mana = [2, 4, 6, 8, 10, 12, 14, 16]) == 2156
    assert candidate(skill = [2, 4, 6, 8, 10, 12],mana = [1, 3, 5, 7, 9, 11, 13, 15]) == 908
    assert candidate(skill = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50],mana = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]) == 17875
    assert candidate(skill = [3000, 2500, 2000, 1500],mana = [1000, 1200, 1400, 1600, 1800]) == 31800000
    assert candidate(skill = [500, 1000, 1500, 2000],mana = [200, 400, 600, 800, 1000, 1200]) == 9400000
    assert candidate(skill = [100, 100, 100, 100, 100],mana = [100, 100, 100, 100, 100, 100, 100, 100, 100, 100]) == 140000
    assert candidate(skill = [2, 4, 6, 8, 10, 12],mana = [12, 10, 8, 6, 4, 2]) == 864
    assert candidate(skill = [100, 200, 150, 50, 250],mana = [50, 75, 100, 125, 150]) == 172500
    assert candidate(skill = [2, 4, 6, 8, 10],mana = [1, 3, 5, 7, 9]) == 330
    assert candidate(skill = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],mana = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]) == 35750
    assert candidate(skill = [4, 2, 6, 5, 1],mana = [9, 3, 7, 8, 2, 10]) == 465
    assert candidate(skill = [2, 4, 6, 8, 10],mana = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 120
    assert candidate(skill = [5000, 5000, 5000, 5000],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 425000
    assert candidate(skill = [1, 3, 2, 4, 5],mana = [2, 1, 3, 4, 5]) == 115
    assert candidate(skill = [5, 10, 15, 20, 25],mana = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 1500
    assert candidate(skill = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 715
    assert candidate(skill = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],mana = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]) == 71500
    assert candidate(skill = [100, 200, 150, 50],mana = [300, 250, 400, 100, 350]) == 440000
    assert candidate(skill = [50, 40, 30, 20, 10],mana = [25, 20, 15, 10, 5]) == 4750
    assert candidate(skill = [100, 200, 300, 400],mana = [10, 20, 30, 40, 50, 60]) == 94000
    assert candidate(skill = [7, 14, 21, 28, 35],mana = [35, 28, 21, 14, 7]) == 6125
    assert candidate(skill = [42, 15, 88, 34, 99, 56],mana = [72, 33, 19, 55, 48, 62, 28]) == 53845
    assert candidate(skill = [2500, 1000, 5000, 3000],mana = [5000, 2000, 1000, 3000, 4000]) == 115000000
    assert candidate(skill = [500, 1000, 1500, 2000],mana = [500, 1000, 1500, 2000, 2500]) == 17500000
    assert candidate(skill = [10, 20, 30, 40, 50],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 2950
    assert candidate(skill = [1, 2, 3, 4, 5],mana = [5, 10, 15, 20, 25]) == 475
    assert candidate(skill = [3, 7, 5, 2, 8],mana = [4, 6, 2, 9, 1]) == 377
    assert candidate(skill = [5, 3, 8, 6, 2],mana = [7, 1, 4, 2, 9, 5, 3]) == 469
    assert candidate(skill = [500, 1000, 1500, 2000],mana = [100, 200, 300, 400, 500, 600, 700, 800]) == 7700000
    assert candidate(skill = [1000, 2000, 3000, 4000, 5000],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 295000
    assert candidate(skill = [1000, 2000, 3000, 4000, 5000],mana = [1, 10, 100, 1000, 10000]) == 151111000
    assert candidate(skill = [10, 15, 20, 25, 30],mana = [35, 40, 45, 50, 55, 60, 65, 70]) == 15050
    assert candidate(skill = [100, 200, 300, 400],mana = [5, 10, 15, 20, 25, 30]) == 47000
    assert candidate(skill = [1000, 2000, 3000, 4000, 5000],mana = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150]) == 6200000
    assert candidate(skill = [300, 200, 100],mana = [5, 15, 25, 35, 45, 55]) == 70500
    assert candidate(skill = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],mana = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1]) == 3439
    assert candidate(skill = [2, 5, 7, 8],mana = [1, 3, 6, 9, 12]) == 341
    assert candidate(skill = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],mana = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 715000
    assert candidate(skill = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],mana = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 1000
    assert candidate(skill = [100, 200, 300, 400],mana = [50, 60, 70, 80, 90]) == 170000
    assert candidate(skill = [100, 200, 300, 400, 500],mana = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50]) == 147500
    assert candidate(skill = [300, 200, 100],mana = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 40500
    assert candidate(skill = [3, 7, 2, 8],mana = [6, 4, 9, 1, 5]) == 356
    assert candidate(skill = [1, 3, 2, 4],mana = [2, 3, 4, 5]) == 74
    assert candidate(skill = [1, 10, 100, 1000],mana = [1, 10, 100, 1000, 10000]) == 11111111
    assert candidate(skill = [5, 10, 15, 20, 25, 30],mana = [1, 3, 5, 7, 9]) == 1095
    assert candidate(skill = [1, 1, 1, 1, 1],mana = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 24
    assert candidate(skill = [500, 1000, 1500, 2000, 2500],mana = [250, 500, 750, 1000, 1250]) == 11875000
    assert candidate(skill = [3, 6, 9, 12, 15],mana = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]) == 1770
    assert candidate(skill = [5000, 4000, 3000, 2000, 1000],mana = [1000, 2000, 3000, 4000, 5000]) == 125000000
    assert candidate(skill = [1, 10, 100, 1000, 5000],mana = [1, 10, 100, 1000, 5000]) == 31111111
    assert candidate(skill = [4000, 3000, 2000, 1000, 500],mana = [500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000]) == 142500000
    assert candidate(skill = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],mana = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20]) == 2660
    assert candidate(skill = [3, 5, 7, 9],mana = [2, 4, 6, 8]) == 238
    assert candidate(skill = [5000, 1000, 2000, 3000, 4000],mana = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]) == 37500000
    assert candidate(skill = [1500, 1500, 1500, 1500],mana = [500, 1000, 1500, 2000, 2500, 3000]) == 29250000
    assert candidate(skill = [2, 3, 5, 7, 11],mana = [13, 17, 19, 23, 29, 31, 37]) == 2080


# === INVOCATION ===
check(Solution().minTime)
print("All tests passed")
