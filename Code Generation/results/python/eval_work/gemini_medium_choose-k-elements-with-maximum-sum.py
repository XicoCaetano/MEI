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
import heapq

class Solution:
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        n = len(nums1)
        # Create a list of tuples (nums1 value, nums2 value, original index)
        # and sort by nums1 value to process them in increasing order.
        data = sorted([(nums1[i], nums2[i], i) for i in range(n)])
        
        results = [0] * n
        min_heap = []
        current_sum = 0
        
        # We need to track the pointer to the first element in the sorted list 
        # that has the same nums1 value as the current group.
        j = 0
        for i in range(n):
            # If the current nums1 value is greater than the previous processed one,
            # we can add all values that were smaller into our potential top-k pool.
            # This handles duplicate values in nums1 correctly.
            if i > 0 and data[i][0] > data[i-1][0]:
                while j < i:
                    val_to_add = data[j][1]
                    heapq.heappush(min_heap, val_to_add)
                    current_sum += val_to_add
                    
                    # Maintain only the top k largest elements in the heap
                    if len(min_heap) > k:
                        current_sum -= heapq.heappop(min_heap)
                    j += 1
            
            # The result for the original index is the current sum of the top k
            # values from elements strictly smaller than data[i][0].
            # If nums1 values are equal, the loop won't update current_sum, 
            # fulfilling the condition nums1[j] < nums1[i].
            original_idx = data[i][2]
            results[original_idx] = current_sum
            
        return results

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums1 = [10, 20, 30, 40, 50],nums2 = [50, 40, 30, 20, 10],k = 2) == [0, 50, 90, 90, 90]
    assert candidate(nums1 = [100000, 90000, 80000, 70000, 60000],nums2 = [1, 2, 3, 4, 5],k = 4) == [14, 12, 9, 5, 0]
    assert candidate(nums1 = [1, 1, 1, 1, 1],nums2 = [5, 5, 5, 5, 5],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(nums1 = [5, 4, 3, 2, 1],nums2 = [1, 2, 3, 4, 5],k = 2) == [9, 9, 9, 5, 0]
    assert candidate(nums1 = [5, 5, 5, 5, 5],nums2 = [1, 2, 3, 4, 5],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5],nums2 = [5, 4, 3, 2, 1],k = 3) == [0, 5, 9, 12, 12]
    assert candidate(nums1 = [10, 20, 30, 40, 50],nums2 = [1, 1, 1, 1, 1],k = 5) == [0, 1, 2, 3, 4]
    assert candidate(nums1 = [1, 3, 5, 7, 9],nums2 = [9, 7, 5, 3, 1],k = 3) == [0, 9, 16, 21, 21]
    assert candidate(nums1 = [4, 2, 1, 5, 3],nums2 = [10, 20, 30, 40, 50],k = 2) == [80, 30, 0, 80, 50]
    assert candidate(nums1 = [2, 2, 2, 2],nums2 = [3, 1, 2, 3],k = 1) == [0, 0, 0, 0]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3) == [0, 10, 30, 60, 90, 120, 150, 180, 210, 240]
    assert candidate(nums1 = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],nums2 = [5, 5, 4, 4, 3, 3, 2, 2, 1, 1],k = 3) == [0, 0, 10, 10, 14, 14, 14, 14, 14, 14]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 10) == [0, 1, 2, 3, 4, 5, 6, 7, 8, 9]
    assert candidate(nums1 = [100, 200, 300, 400, 500],nums2 = [5, 10, 15, 20, 25],k = 1) == [0, 5, 10, 15, 20]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],k = 10) == [0, 1, 4, 9, 16, 25, 36, 49, 64, 81]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5) == [0, 1, 3, 6, 10, 15, 20, 25, 30, 35]
    assert candidate(nums1 = [100000, 100000, 100000, 100000, 100000],nums2 = [50000, 60000, 70000, 80000, 90000],k = 3) == [0, 0, 0, 0, 0]
    assert candidate(nums1 = [5, 4, 3, 2, 1, 0, 6, 7, 8, 9],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3) == [150, 150, 150, 110, 60, 0, 150, 180, 210, 240]
    assert candidate(nums1 = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],k = 2) == [0, 100, 300, 500, 700, 900, 1100, 1300, 1500, 1700]
    assert candidate(nums1 = [1, 3, 2, 4, 5],nums2 = [5, 3, 8, 2, 7],k = 2) == [0, 13, 5, 13, 13]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50],nums2 = [50, 40, 30, 20, 10, 50, 40, 30, 20, 10],k = 4) == [0, 100, 180, 180, 180, 0, 100, 180, 180, 180]
    assert candidate(nums1 = [1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5) == [40, 40, 40, 40, 40, 34, 27, 19, 10, 0]
    assert candidate(nums1 = [100, 1, 200, 2, 300, 3, 400, 4, 500, 5],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 2) == [18, 0, 18, 2, 18, 6, 18, 10, 18, 14]
    assert candidate(nums1 = [10, 10, 10, 10, 10],nums2 = [1000, 1001, 1002, 1003, 1004],k = 3) == [0, 0, 0, 0, 0]
    assert candidate(nums1 = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 5) == [400, 400, 400, 400, 400, 340, 270, 190, 100, 0]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29],nums2 = [29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1],k = 7) == [0, 29, 56, 81, 104, 125, 144, 161, 161, 161, 161, 161, 161, 161, 161]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3) == [27, 27, 27, 27, 27, 27, 27, 19, 10, 0]
    assert candidate(nums1 = [50000, 40000, 30000, 20000, 10000, 60000, 70000, 80000, 90000, 100000],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 5) == [140, 120, 90, 50, 0, 150, 200, 250, 300, 350]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],k = 3) == [0, 100, 190, 270, 270, 270, 270, 270, 270, 270]
    assert candidate(nums1 = [1, 3, 2, 4, 5, 3, 4, 5, 6, 7],nums2 = [100, 200, 300, 400, 500, 100, 200, 300, 400, 500],k = 3) == [0, 400, 100, 600, 900, 400, 600, 900, 1200, 1300]
    assert candidate(nums1 = [1, 3, 2, 4, 6, 5, 8, 7, 10, 9],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 4) == [0, 40, 10, 60, 150, 100, 230, 180, 310, 260]
    assert candidate(nums1 = [500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000],nums2 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20],nums2 = [20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 5) == [0, 20, 39, 57, 74, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90, 90]
    assert candidate(nums1 = [10, 15, 20, 25, 30, 35, 40, 45, 50, 55],nums2 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],k = 2) == [0, 100, 300, 500, 700, 900, 1100, 1300, 1500, 1700]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [100, 200, 300, 400, 500],nums2 = [500, 400, 300, 200, 100],k = 3) == [0, 500, 900, 1200, 1200]
    assert candidate(nums1 = [5, 4, 3, 2, 1],nums2 = [100, 200, 300, 400, 500],k = 1) == [500, 500, 500, 500, 0]
    assert candidate(nums1 = [20, 20, 20, 20, 20, 20, 20, 20, 20, 20],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 5) == [0, 10, 30, 60, 100, 150, 200, 250, 300, 350]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],nums2 = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],k = 5) == [0, 100, 190, 270, 340, 400, 400, 400, 400, 400]
    assert candidate(nums1 = [5, 4, 3, 2, 1, 6, 7, 8, 9, 10],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 5) == [14, 12, 9, 5, 0, 15, 20, 25, 30, 35]
    assert candidate(nums1 = [1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 10) == [540, 520, 490, 450, 400, 340, 270, 190, 100, 0]
    assert candidate(nums1 = [5, 3, 8, 6, 2, 7, 4, 10, 9, 1],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 4) == [240, 150, 280, 240, 100, 260, 170, 320, 280, 0]
    assert candidate(nums1 = [5, 3, 8, 6, 2, 7, 4, 1, 9, 10],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3) == [200, 130, 210, 200, 80, 200, 150, 0, 210, 240]
    assert candidate(nums1 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],nums2 = [1000, 900, 800, 700, 600, 500, 400, 300, 200, 100],k = 3) == [0, 1000, 1900, 2700, 2700, 2700, 2700, 2700, 2700, 2700]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],k = 4) == [0, 100, 190, 270, 340, 340, 340, 340, 340, 340]
    assert candidate(nums1 = [5, 4, 3, 2, 1],nums2 = [10, 20, 30, 40, 50],k = 5) == [140, 120, 90, 50, 0]
    assert candidate(nums1 = [1, 1, 1, 1, 1],nums2 = [5, 4, 3, 2, 1],k = 2) == [0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],nums2 = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1],k = 5) == [0, 19, 36, 51, 64, 75, 75, 75, 75, 75]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5) == [0, 1, 2, 3, 4, 5, 5, 5, 5, 5]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [100000, 90000, 80000, 70000, 60000, 50000, 40000, 30000, 20000, 10000],k = 5) == [0, 100000, 190000, 270000, 340000, 400000, 400000, 400000, 400000, 400000]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 2) == [19, 19, 19, 19, 19, 19, 19, 19, 10, 0]
    assert candidate(nums1 = [1000000, 500000, 250000, 125000, 62500],nums2 = [62500, 125000, 250000, 500000, 1000000],k = 2) == [1500000, 1500000, 1500000, 1000000, 0]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 2) == [190, 190, 190, 190, 190, 190, 190, 190, 100, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 4) == [0, 10, 19, 27, 34, 34, 34, 34, 34, 34]
    assert candidate(nums1 = [1, 2, 2, 3, 4, 4, 5, 5, 5, 6],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 2) == [0, 10, 10, 50, 70, 70, 110, 110, 110, 170]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91],k = 5) == [0, 100, 199, 297, 394, 490, 490, 490, 490, 490]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 4) == [0, 1, 3, 6, 10, 14, 18, 22, 26, 30]
    assert candidate(nums1 = [1, 2, 3, 4, 5],nums2 = [5, 4, 3, 2, 1],k = 5) == [0, 5, 9, 12, 14]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],nums2 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 3) == [0, 1, 2, 3, 3, 3, 3, 3, 3, 3]
    assert candidate(nums1 = [5, 4, 3, 2, 1, 0],nums2 = [100, 200, 300, 400, 500, 600],k = 3) == [1500, 1500, 1500, 1100, 600, 0]
    assert candidate(nums1 = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3) == [27, 27, 27, 27, 27, 27, 27, 19, 10, 0]
    assert candidate(nums1 = [5, 4, 3, 2, 1],nums2 = [10, 20, 30, 40, 50],k = 2) == [90, 90, 90, 50, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 1) == [0, 10, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums1 = [1, 10, 2, 9, 3, 8, 4, 7, 5, 6],nums2 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 3) == [0, 25, 10, 24, 18, 24, 24, 24, 24, 24]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 10) == [0, 1, 3, 6, 10, 15, 21, 28, 36, 45]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [100000, 90000, 80000, 70000, 60000, 50000, 40000, 30000, 20000, 10000],k = 1) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [5, 3, 8, 6, 2, 7, 4, 10, 1],nums2 = [9, 1, 8, 7, 2, 6, 3, 10, 4],k = 3) == [9, 6, 22, 16, 4, 20, 7, 24, 0]
    assert candidate(nums1 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 3) == [0, 1, 3, 6, 9, 12, 15, 18, 21, 24]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 4) == [340, 340, 340, 340, 340, 340, 270, 190, 100, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 2) == [0, 10, 30, 50, 70, 90, 110, 130, 150, 170]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 1) == [10, 10, 10, 10, 10, 10, 10, 10, 10, 0]
    assert candidate(nums1 = [1, 1, 1, 1, 1],nums2 = [1, 2, 3, 4, 5],k = 1) == [0, 0, 0, 0, 0]
    assert candidate(nums1 = [1, 2, 2, 3, 3, 3, 4, 4, 5, 5],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 3) == [0, 10, 10, 60, 60, 60, 150, 150, 210, 210]
    assert candidate(nums1 = [1, 2, 3, 4, 5],nums2 = [5, 5, 5, 5, 5],k = 3) == [0, 5, 10, 15, 15]
    assert candidate(nums1 = [9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 3, 5, 7, 9, 11, 13, 15, 17],k = 4) == [56, 56, 56, 56, 56, 45, 32, 17, 0]
    assert candidate(nums1 = [5, 4, 3, 2, 1],nums2 = [1, 1, 1, 1, 1],k = 3) == [3, 3, 2, 1, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15],nums2 = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 3) == [0, 15, 29, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42]
    assert candidate(nums1 = [1, 3, 2, 5, 4, 7, 6, 9, 8, 10],nums2 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 4) == [0, 18, 10, 33, 27, 34, 34, 34, 34, 34]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991],k = 3) == [0, 1000000, 1999999, 2999997, 2999997, 2999997, 2999997, 2999997, 2999997, 2999997]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 10) == [54, 52, 49, 45, 40, 34, 27, 19, 10, 0]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],nums2 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 5) == [0, 1, 2, 3, 4, 5, 5, 5, 5, 5]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 10, 2, 20, 3, 30, 4, 40, 5, 50],k = 4) == [140, 140, 140, 125, 125, 99, 95, 55, 50, 0]
    assert candidate(nums1 = [2, 4, 6, 8, 10, 12, 14, 16, 18, 20],nums2 = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],k = 5) == [0, 1, 4, 9, 16, 25, 35, 45, 55, 65]
    assert candidate(nums1 = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],nums2 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],k = 1) == [0, 0, 10, 10, 10, 10, 10, 10, 10, 10]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 10) == [54, 52, 49, 45, 40, 34, 27, 19, 10, 0]
    assert candidate(nums1 = [5, 4, 3, 2, 1],nums2 = [500, 400, 300, 200, 100],k = 1) == [400, 300, 200, 100, 0]
    assert candidate(nums1 = [500000, 400000, 300000, 200000, 100000],nums2 = [50000, 40000, 30000, 20000, 10000],k = 2) == [70000, 50000, 30000, 10000, 0]
    assert candidate(nums1 = [100000, 90000, 80000, 70000, 60000, 50000, 40000, 30000, 20000, 10000],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 5) == [400, 400, 400, 400, 400, 340, 270, 190, 100, 0]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],nums2 = [90, 80, 70, 60, 50, 40, 30, 20, 10, 0],k = 5) == [0, 90, 170, 240, 300, 350, 350, 350, 350, 350]
    assert candidate(nums1 = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1],nums2 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],k = 1) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 0]
    assert candidate(nums1 = [500000, 400000, 300000, 200000, 100000],nums2 = [10, 20, 30, 40, 50],k = 5) == [140, 120, 90, 50, 0]
    assert candidate(nums1 = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],nums2 = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000],k = 4) == [0, 0, 300, 300, 1000, 1000, 1800, 1800, 2600, 2600]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],nums2 = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],k = 3) == [0, 100, 190, 270, 270, 270, 270, 270, 270, 270]
    assert candidate(nums1 = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],nums2 = [20, 18, 16, 14, 12, 10, 8, 6, 4, 2],k = 5) == [0, 20, 38, 54, 68, 80, 80, 80, 80, 80]
    assert candidate(nums1 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 5) == [0, 10, 30, 60, 100, 150, 200, 250, 300, 350]
    assert candidate(nums1 = [1, 1, 2, 2, 3, 3, 4, 4, 5, 5],nums2 = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10],k = 2) == [0, 0, 3, 3, 7, 7, 11, 11, 15, 15]
    assert candidate(nums1 = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums1 = [100, 50, 75, 25, 150, 125, 200, 175, 225, 15],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 4) == [190, 140, 160, 100, 230, 190, 290, 250, 310, 0]
    assert candidate(nums1 = [1, 2, 3, 4, 5, 1, 2, 3, 4, 5],nums2 = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50],k = 3) == [0, 20, 50, 80, 110, 0, 20, 50, 80, 110]
    assert candidate(nums1 = [1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991],nums2 = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100],k = 5) == [400, 400, 400, 400, 400, 340, 270, 190, 100, 0]
    assert candidate(nums1 = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19],nums2 = [19, 17, 15, 13, 11, 9, 7, 5, 3, 1],k = 2) == [0, 19, 36, 36, 36, 36, 36, 36, 36, 36]
    assert candidate(nums1 = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50],nums2 = [100, 90, 80, 70, 60, 50, 40, 30, 20, 10],k = 5) == [0, 100, 190, 270, 340, 400, 400, 400, 400, 400]
    assert candidate(nums1 = [5, 4, 3, 2, 1, 1, 2, 3, 4, 5],nums2 = [10, 20, 30, 40, 50, 10, 20, 30, 40, 50],k = 2) == [90, 90, 90, 60, 0, 0, 60, 90, 90, 90]


# === INVOCATION ===
check(Solution().findMaxSum)
print("All tests passed")
