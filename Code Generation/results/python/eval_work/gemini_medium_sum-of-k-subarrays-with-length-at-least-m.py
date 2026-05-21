# === IMPORTS GERAIS (do dataset) ===
import heapq
import itertools
from sortedcontainers import SortedList
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
    def maxSum(self, nums: List[int], k: int, m: int) -> int:
        n = len(nums)
        
        S = [0] * (n + 1)
        for i in range(n):
            S[i + 1] = S[i] + nums[i]
            
        prev_dp = [0] * (n + 1)
        
        for j in range(1, k + 1):
            new_dp = [float('-inf')] * (n + 1)
            max_val = float('-inf')
            
            for i in range(j * m, n + 1):
                p = i - m
                
                if prev_dp[p] != float('-inf'):
                    val = prev_dp[p] - S[p]
                    if val > max_val:
                        max_val = val
                        
                new_dp[i] = new_dp[i - 1]
                
                if max_val != float('-inf'):
                    current_sum = S[i] + max_val
                    if current_sum > new_dp[i]:
                        new_dp[i] = current_sum
                        
            prev_dp = new_dp
            
        return int(prev_dp[n])

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [1, 0, -1, 0, 1, -1, 0, 1],k = 2,m = 2) == 2
    assert candidate(nums = [5, 4, 3, 2, 1],k = 2,m = 2) == 15
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],k = 2,m = 3) == 0
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9],k = 3,m = 3) == 45
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],k = 4,m = 2) == 78
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0],k = 1,m = 1) == 0
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0],k = 2,m = 1) == 0
    assert candidate(nums = [10, 20, 30, 40, 50],k = 2,m = 3) == -19999850
    assert candidate(nums = [1, 2, 3, 4, 5],k = 1,m = 1) == 15
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9],k = 3,m = 2) == 45
    assert candidate(nums = [-10, 3, -1, -2],k = 4,m = 1) == -10
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5],k = 2,m = 3) == 45
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9],k = 3,m = 2) == -21
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5,m = 1) == 55
    assert candidate(nums = [1, 2, -1, 3, 3, 4],k = 2,m = 2) == 13
    assert candidate(nums = [5, -1, 5, -1, 5, -1],k = 2,m = 1) == 14
    assert candidate(nums = [-5, -4, -3, -2, -1],k = 2,m = 1) == -3
    assert candidate(nums = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10],k = 5,m = 3) == 150
    assert candidate(nums = [9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19],k = 5,m = 3) == 199
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29],k = 5,m = 3) == 225
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40],k = 4,m = 3) == -19999940
    assert candidate(nums = [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9],k = 5,m = 2) == 45
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, 19, -20, 21, -22],k = 6,m = 3) == 53
    assert candidate(nums = [1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000],k = 5,m = 2) == 3000
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1],k = 5,m = 1) == 5
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20],k = 3,m = 2) == -21
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 5,m = 3) == 210
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 10,m = 1) == 20
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1],k = 6,m = 1) == 6
    assert candidate(nums = [1, 2, 3, -4, -5, 6, -7, 8, 9, -10, 11, 12, 13, -14],k = 5,m = 3) == -19999942
    assert candidate(nums = [-100, 0, 100, -200, 0, 200, -300, 0, 300, -400, 0, 400, -500, 0, 500, -600, 0, 600, -700, 0],k = 5,m = 2) == 2000
    assert candidate(nums = [5, -2, 3, -4, 6, -1, 2, 8, -5, 7],k = 3,m = 2) == 23
    assert candidate(nums = [-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110, -120, -130, -140, -150],k = 5,m = 3) == -1200
    assert candidate(nums = [10, -5, 15, -10, 20, -15, 25, -20, 30, -25],k = 5,m = 2) == 25
    assert candidate(nums = [100, 200, 300, 400, 500, -100, -200, -300, -400, -500, 600, 700, 800, 900, 1000],k = 5,m = 2) == 5400
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5,m = 1) == 20
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 4,m = 3) == 210
    assert candidate(nums = [100, -200, 300, -400, 500, -600, 700, -800, 900, -1000],k = 4,m = 2) == 500
    assert candidate(nums = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125, 130, 135, 140, 145, 150, 155, 160, 165, 170, 175, 180, 185, 190, 195, 200],k = 7,m = 2) == 4100
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30],k = 5,m = 3) == 465
    assert candidate(nums = [3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3],k = 5,m = 2) == 60
    assert candidate(nums = [100, -50, 200, -150, 300, -250, 400, -350, 500, -450],k = 5,m = 2) == 250
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15],k = 5,m = 3) == -120
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60, 70, -70, 80, -80, 90, -90, 100, -100],k = 5,m = 2) == 300
    assert candidate(nums = [100, 200, -300, 400, 500, -600, 700, 800, -900, 1000],k = 5,m = 2) == 1900
    assert candidate(nums = [10, 20, 30, -40, 50, 60, -70, 80, 90, -100],k = 4,m = 2) == 300
    assert candidate(nums = [1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0],k = 5,m = 2) == 3
    assert candidate(nums = [10, 20, 30, -5, 2, -5, 2, 3, 2, 1, -1, 2, 3, -4, 2],k = 3,m = 2) == 73
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1],k = 3,m = 2) == 3
    assert candidate(nums = [10, -20, 30, -40, 50, -60, 70, -80, 90, -100, 110, -120],k = 3,m = 2) == 180
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 2,m = 3) == -21
    assert candidate(nums = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97],k = 5,m = 2) == 1060
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 3,m = 1) == -6
    assert candidate(nums = [5, -3, 2, 1, 4, -7, 3, 2, 1, 0],k = 3,m = 2) == 15
    assert candidate(nums = [100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100, 100, -100],k = 5,m = 2) == 500
    assert candidate(nums = [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14],k = 5,m = 2) == 105
    assert candidate(nums = [5, 1, 5, 2, 3, 4, 2, 1, 3, 4, 5],k = 3,m = 2) == 35
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29],k = 4,m = 2) == 225
    assert candidate(nums = [29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1],k = 4,m = 2) == 225
    assert candidate(nums = [100, 200, -300, 400, 500, -600, 700, 800, -900, 1000],k = 3,m = 2) == 2800
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5,m = 2) == 32
    assert candidate(nums = [-100, 100, -100, 100, -100, 100, -100, 100, -100, 100],k = 5,m = 2) == 0
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 3,m = 2) == 45
    assert candidate(nums = [1, 2, -1, 3, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12],k = 5,m = 2) == 81
    assert candidate(nums = [5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1],k = 5,m = 1) == 75
    assert candidate(nums = [0, 1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15],k = 5,m = 3) == 20
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5,m = 2) == 20
    assert candidate(nums = [3, 2, 1, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25],k = 4,m = 2) == 325
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 5,m = 3) == 210
    assert candidate(nums = [1000, -2000, 3000, -4000, 5000, -6000, 7000, -8000, 9000, -10000],k = 2,m = 1) == 16000
    assert candidate(nums = [0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1],k = 5,m = 3) == 10
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200],k = 5,m = 3) == 2100
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1],k = 5,m = 2) == 5
    assert candidate(nums = [100, 0, 100, 0, 100, 0, 100, 0, 100, 0],k = 5,m = 2) == 500
    assert candidate(nums = [10, -5, -1, 0, 7, 10, 1, -2, 5, -6, 7, 8, -1, -3, -2],k = 4,m = 1) == 48
    assert candidate(nums = [5, -2, 6, -3, 4, 3, -1, 2, 8, -7, 1, 3, 5],k = 3,m = 2) == 34
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5,m = 3) == 20
    assert candidate(nums = [5, -2, 7, 1, -3, 9, -8, 6, 4, 2],k = 3,m = 2) == 29
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10],k = 3,m = 2) == 11
    assert candidate(nums = [100, 200, -300, 400, -500, 600, -700, 800, -900, 1000],k = 4,m = 2) == 1400
    assert candidate(nums = [1, 2, -1, 2, -1, 1, -2, 1, -2, 1, -2, 1, -2, 1],k = 4,m = 2) == 5
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30],k = 4,m = 2) == 465
    assert candidate(nums = [0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1, 0, -1, 0, 1],k = 5,m = 2) == 5
    assert candidate(nums = [10, -20, 30, -40, 50, -60, 70, -80, 90, -100, 110, -120, 130, -140, 150, -160, 170, -180, 190, -200],k = 5,m = 3) == 500
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10],k = 6,m = 2) == 28
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150],k = 5,m = 2) == 1200
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 10,m = 3) == 38
    assert candidate(nums = [10, -5, 3, 8, -2, -4, 7, 10, -3, 6],k = 3,m = 1) == 41
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150],k = 5,m = 3) == 1200
    assert candidate(nums = [10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10],k = 5,m = 1) == 250
    assert candidate(nums = [5, -5, 5, -5, 5, -5, 5, -5, 5, -5],k = 5,m = 1) == 25
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 3,m = 2) == -21
    assert candidate(nums = [100, 200, 300, 400, 500],k = 2,m = 3) == -19998500
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60],k = 5,m = 1) == 200
    assert candidate(nums = [10, -5, 15, -20, 25, -30, 35, -40, 45, -50, 55, -60, 65],k = 4,m = 3) == 95
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],k = 5,m = 2) == 120
    assert candidate(nums = [5, -3, 10, 20, -25, 50, -100, 150, -200, 300],k = 3,m = 2) == 307
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 5,m = 1) == -15
    assert candidate(nums = [100, -50, 200, -300, 400, -500, 600, -700, 800, -900, 1000],k = 5,m = 2) == 650
    assert candidate(nums = [-5, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12],k = 5,m = 2) == -50
    assert candidate(nums = [5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 4,m = 2) == 12
    assert candidate(nums = [2, 3, -1, -4, 5, 3, -5, 4, 3, -3, 2, -1, 1, 2, -3, 1],k = 3,m = 2) == 21
    assert candidate(nums = [-1, 4, -2, 3, -2, 3, 4, -1, -2, 3, 4, 5],k = 4,m = 1) == 26
    assert candidate(nums = [5, -3, 2, 7, -1, 4, -2, 8],k = 3,m = 2) == 21
    assert candidate(nums = [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5],k = 2,m = 2) == 15
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25],k = 5,m = 2) == 325
    assert candidate(nums = [2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1],k = 4,m = 2) == 210
    assert candidate(nums = [5, 2, -3, 8, -10, 3, 4, 1, -1, 6],k = 3,m = 2) == 25
    assert candidate(nums = [-5, -1, -8, -3, -4, -7, -9, -2, -6],k = 3,m = 2) == -21
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 4,m = 3) == 80
    assert candidate(nums = [25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 5,m = 3) == 325
    assert candidate(nums = [-10, 3, -1, -2],k = 4,m = 1) == -10
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 2,m = 1) == 50
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5,m = 1) == 20
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1],k = 3,m = 2) == 1
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3,m = 2) == 55
    assert candidate(nums = [1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000, 1000, -1000],k = 5,m = 2) == 0
    assert candidate(nums = [10000, -10000, 10000, -10000, 10000],k = 2,m = 2) == 10000
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 5,m = 1) == -15
    assert candidate(nums = [-1000, -2000, -3000, -4000, -5000, -6000, -7000, -8000, -9000, -10000],k = 4,m = 1) == -10000
    assert candidate(nums = [-5, -4, -3, -2, -1],k = 2,m = 2) == -10
    assert candidate(nums = [-3, -2, -1, 0, 1, 2, 3],k = 2,m = 1) == 6
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4],k = 2,m = 1) == 7
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5],k = 3,m = 2) == 8
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],k = 1,m = 1) == 0
    assert candidate(nums = [10, -2, -3, 10, -2, -3, 10, -2, -3],k = 3,m = 3) == 15
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5],k = 5,m = 1) == 15
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 5,m = 2) == 100
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3,m = 2) == 55
    assert candidate(nums = [1, 2, 3, 4, 5],k = 1,m = 3) == 15
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3,m = 3) == 550
    assert candidate(nums = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1],k = 5,m = 1) == -5
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 2,m = 1) == 550
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 3,m = 3) == 50
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1],k = 3,m = 1) == 45
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 5,m = 1) == 50
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0],k = 3,m = 2) == 0
    assert candidate(nums = [-1, -1, -1, -1, -1, -1, -1, -1, -1, -1],k = 3,m = 3) == -9
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1],k = 2,m = 1) == 2
    assert candidate(nums = [10000, 10000, 10000, 10000],k = 2,m = 2) == 40000
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0],k = 1,m = 1) == 0
    assert candidate(nums = [1, 2, 3, 4, 5, 6],k = 3,m = 1) == 21
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1],k = 5,m = 2) == 0
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],k = 1,m = 1) == 0
    assert candidate(nums = [100, -100, 200, -200, 300],k = 2,m = 2) == 300
    assert candidate(nums = [10, 20, -30, 40, 50, -60, 70, 80, 90],k = 3,m = 1) == 360
    assert candidate(nums = [100, -50, 100, -50, 100, -50, 100, -50, 100, -50],k = 2,m = 2) == 350
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 2,m = 3) == 50
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 2,m = 2) == 50
    assert candidate(nums = [5, 1, 1, 5, 5, 1, 1, 5],k = 3,m = 2) == 24
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 2,m = 2) == -10
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5,m = 1) == 10
    assert candidate(nums = [5, 6, 7, 8, 9, 10],k = 2,m = 2) == 45
    assert candidate(nums = [100, -200, 300, -400, 500],k = 2,m = 2) == 300
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],k = 3,m = 2) == 5500
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50, -50],k = 3,m = 2) == 80
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 3,m = 2) == 50
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9],k = 3,m = 1) == 21
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],k = 5,m = 2) == 120
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],k = 2,m = 2) == 0
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 2,m = 2) == 10
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],k = 2,m = 1) == 0
    assert candidate(nums = [100, -100, 100, -100, 100, -100, 100, -100, 100, -100],k = 2,m = 3) == 200
    assert candidate(nums = [100, -100, 100, -100, 100, -100, 100, -100, 100, -100],k = 3,m = 2) == 200
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 5,m = 2) == -55
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],k = 5,m = 3) == 120
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5],k = 2,m = 3) == 40
    assert candidate(nums = [5, 2, 3, 4, 5, 6],k = 3,m = 1) == 25
    assert candidate(nums = [100, -100, 200, -200, 300, -300],k = 3,m = 1) == 600
    assert candidate(nums = [10, 20, 30, 40, 50],k = 1,m = 3) == 150
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],k = 5,m = 2) == 210
    assert candidate(nums = [1, 2, 3, 4, 5],k = 2,m = 1) == 15
    assert candidate(nums = [2, 1, -1, 2, -1, -2, 1],k = 2,m = 1) == 5
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40],k = 4,m = 1) == 100
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10],k = 2,m = 2) == -10
    assert candidate(nums = [0, 0, 0, 0, 0, 0],k = 2,m = 1) == 0
    assert candidate(nums = [1, -1, 1, -1, 1, -1],k = 2,m = 2) == 1
    assert candidate(nums = [10, -2, 3, -1, 4, -3, 6, -2, 5, -1, 8, -3, 7, -2, 9],k = 3,m = 2) == 44
    assert candidate(nums = [5, -1, 5, -1, 5, -1, 5, -1],k = 2,m = 2) == 18
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0],k = 2,m = 2) == 0
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0],k = 2,m = 2) == 0
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1],k = 5,m = 1) == 5
    assert candidate(nums = [1, 2, 3, 4, 5],k = 2,m = 2) == 15
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 2,m = 3) == 55
    assert candidate(nums = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000],k = 3,m = 3) == 55000
    assert candidate(nums = [-1, -2, -3, -4, -5],k = 2,m = 2) == -10
    assert candidate(nums = [1, 0, -1, 0, 1, -1, 0, 1, -1, 0],k = 3,m = 1) == 3
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 3,m = 1) == 10
    assert candidate(nums = [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5],k = 3,m = 2) == 15
    assert candidate(nums = [100, 200, 300, 400, 500],k = 1,m = 3) == 1500
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3,m = 1) == 55
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3,m = 3) == 550
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],k = 3,m = 2) == 50
    assert candidate(nums = [1, 2, 3, 4, 5],k = 3,m = 1) == 15
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 3,m = 2) == 10
    assert candidate(nums = [1, -1, 1, -1, 1, -1],k = 2,m = 1) == 2
    assert candidate(nums = [10, -5, -1, 7, 10, 5, -10, 10, 10, -5],k = 2,m = 2) == 46
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 4,m = 3) == 12
    assert candidate(nums = [2, 4, 5, 6, 7, 8, 9],k = 3,m = 2) == 41
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10],k = 5,m = 1) == 25
    assert candidate(nums = [10, -10, 20, -20, 30, -30],k = 3,m = 2) == 0
    assert candidate(nums = [-1, -2, -3, -4, -5],k = 2,m = 2) == -10
    assert candidate(nums = [1000, -1000, 1000, -1000, 1000, -1000],k = 3,m = 2) == 0
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5,m = 2) == 20
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9],k = 2,m = 2) == -10
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10],k = 5,m = 2) == 30
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 2,m = 3) == 550
    assert candidate(nums = [1, 2, -1, 3, 3, 4],k = 2,m = 2) == 13
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9],k = 2,m = 3) == 45
    assert candidate(nums = [5, 5, 5, 5, 5, 5],k = 3,m = 2) == 30
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3,m = 3) == 55


# === INVOCATION ===
check(Solution().maxSum)
print("All tests passed")
