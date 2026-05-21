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
    def transformArray(self, nums: List[int]) -> List[int]:
        # Replace each even number with 0 and each odd number with 1
        transformed = [0 if num % 2 == 0 else 1 for num in nums]
        
        # Sort in non-decreasing order
        transformed.sort()
        
        return transformed

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [111, 222, 333, 444, 555, 666, 777, 888, 999]) == [0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [4, 3, 2, 1]) == [0, 0, 1, 1]
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [2, 4, 6, 8, 10]) == [0, 0, 0, 0, 0]
    assert candidate(nums = [1, 3, 5, 7, 9]) == [1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 5, 1, 4, 2]) == [0, 0, 1, 1, 1]
    assert candidate(nums = [1000, 999, 998, 997, 996]) == [0, 0, 0, 1, 1]
    assert candidate(nums = [5, 5, 5, 5, 5]) == [1, 1, 1, 1, 1]
    assert candidate(nums = [999, 1000, 1001]) == [0, 1, 1]
    assert candidate(nums = [999, 888, 777, 666, 555]) == [0, 0, 1, 1, 1]
    assert candidate(nums = [8, 6, 4, 2]) == [0, 0, 0, 0]
    assert candidate(nums = [10, 21, 32, 43, 54]) == [0, 0, 0, 1, 1]
    assert candidate(nums = [100, 200, 300, 400, 500]) == [0, 0, 0, 0, 0]
    assert candidate(nums = [11, 22, 33, 44, 55, 66, 77, 88, 99, 100]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [50, 25, 75, 100, 125, 150, 175, 200]) == [0, 0, 0, 0, 1, 1, 1, 1]
    assert candidate(nums = [999, 888, 777, 666, 555, 444, 333, 222, 111]) == [0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [7, 11, 13, 17, 19]) == [1, 1, 1, 1, 1]
    assert candidate(nums = [10, 15, 20, 25, 30]) == [0, 0, 0, 1, 1]
    assert candidate(nums = [1000, 999, 1, 2, 998, 3, 997, 4, 996, 5]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [1001, 1003, 1005, 1007, 1009, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [333, 222, 555, 444, 777, 666, 999, 888, 111, 10]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [101, 2, 203, 4, 305, 6, 407, 8, 509, 10, 611, 12, 713, 14, 815]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [2, 3, 2, 3, 2, 3, 2, 3, 2, 3]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [7, 14, 21, 28, 35, 42, 49, 56, 63, 70]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90]) == [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [123, 456, 789, 1011, 1213, 1415, 1617, 1818]) == [0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 150, 200, 250, 300, 350, 400, 450, 500, 550]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums = [300, 299, 298, 297, 296, 295, 294, 293, 292, 291, 290, 289, 288, 287, 286, 285, 284, 283, 282, 281]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1111, 2222, 3333, 4444, 5555, 6666, 7777, 8888, 9999, 10000]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [111, 222, 333, 444, 555, 666, 777, 888, 999, 1000]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16]) == [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1, 3, 5, 7, 9]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [999, 500, 301, 702, 101, 604, 805, 206, 407, 1]) == [0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47]) == [0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [23, 42, 61, 82, 103, 124, 145, 166, 187, 208, 229, 250, 271, 292, 313, 334, 355, 376, 397, 418]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [231, 232, 233, 234, 235, 236, 237, 238, 239, 240]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3]) == [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [112, 111, 110, 99, 88, 77, 66, 55, 44, 33, 22, 11]) == [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 100, 2, 99, 3, 98, 4, 97, 5, 96, 6, 95, 7, 94, 8, 93]) == [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [550, 549, 548, 547, 546, 545, 544, 543, 542, 541]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [1010, 1009, 1008, 1007, 1006, 1005, 1004, 1003, 1002, 1001]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [999, 1000, 998, 1001, 997, 1002, 996, 1003, 995, 1004]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [999, 888, 777, 666, 555, 444, 333, 222, 111, 1]) == [0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 1, 3, 2, 4, 3, 5, 4, 6, 5, 7, 6, 8, 7, 9, 8, 10]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [11, 22, 33, 44, 55, 66, 77, 88, 99, 100]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [11, 22, 33, 44, 55, 66, 77, 88, 99, 110, 111, 112]) == [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [111, 222, 333, 444, 555, 666, 777, 888, 999]) == [0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [1000, 999, 998, 997, 996, 995, 994, 993, 992, 991, 990, 989, 988, 987, 986, 985, 984, 983, 982, 981]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [23, 42, 55, 60, 71, 88, 99, 100]) == [0, 0, 0, 0, 1, 1, 1, 1]
    assert candidate(nums = [100, 99, 98, 97, 96, 95, 94, 93, 92, 91]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [5, 15, 25, 35, 45, 55, 65, 75, 85, 95]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1000, 500, 250, 125, 62, 31, 15, 7, 3, 1, 0, 2, 4, 8, 16]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 2, 300, 4, 500, 6, 700, 8, 900, 10, 101, 202, 303, 404, 505]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1]
    assert candidate(nums = [1000, 999, 998, 997, 996, 995, 994, 993, 992, 991]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 200, 300, 400, 500, 501, 601, 701, 801, 901]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510]) == [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [50, 49, 48, 47, 46, 45, 44, 43, 42, 41]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300]) == [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [500, 501, 502, 503, 504, 505, 506, 507, 508, 509, 510, 511, 512, 513, 514]) == [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33, 36, 39, 42, 45]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [59, 42, 68, 13, 99, 22, 71, 35, 58, 89, 66, 42]) == [0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 200, 300, 400, 500, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [33, 66, 99, 132, 165, 198, 231, 264, 297, 330, 363, 396, 429, 462, 495]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 15, 14, 13, 12, 11, 20, 19, 18, 17, 16]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [21, 42, 63, 84, 105, 126]) == [0, 0, 0, 1, 1, 1]
    assert candidate(nums = [37, 42, 19, 78, 55, 84, 21, 91, 60, 100, 101]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [82, 73, 64, 55, 46, 37, 28, 19, 10, 11, 20, 29, 38, 47, 56, 65, 74, 83, 92]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [256, 512, 768, 1024, 128, 384, 640, 896, 1536, 1792]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [999, 888, 777, 666, 555, 444, 333, 222, 111, 100, 99, 88, 77, 66, 55, 44, 33, 22, 11, 0]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [999, 998, 997, 996, 995, 994, 993, 992, 991, 990]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [999, 888, 777, 666, 555, 444, 333, 222, 111, 0]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [7, 14, 21, 28, 35, 42, 49, 56, 63, 70, 77, 84, 91, 98]) == [0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [999, 888, 777, 666, 555, 444, 333, 222, 111]) == [0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [13, 27, 42, 55, 68, 81, 94, 107, 120, 133]) == [0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1234, 5678, 91011, 121314, 151617, 181920, 212223]) == [0, 0, 0, 0, 1, 1, 1]
    assert candidate(nums = [999, 1000, 501, 502, 251, 252, 125, 126, 63, 64]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9]) == [0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(nums = [9, 7, 5, 3, 1, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115]) == [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [500, 499, 498, 497, 496, 495, 494, 493, 492, 491, 490, 489, 488, 487, 486, 485, 484, 483, 482, 481]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [123, 456, 789, 101, 202, 303, 404, 505, 606, 707]) == [0, 0, 0, 0, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1, 3, 5, 7, 9, 2, 4, 6, 8, 10, 11, 13, 15, 17, 19, 12, 14, 16, 18, 20]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [1000, 999, 998, 997, 996, 995, 994, 993, 992, 991, 990, 989, 988, 987, 986]) == [0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(nums = [101, 202, 303, 404, 505, 606, 707, 808, 909]) == [0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [101, 202, 303, 404, 505, 606, 707, 808, 909, 1010]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1]
    assert candidate(nums = [8, 15, 17, 22, 31, 46, 59, 68, 77, 84, 93]) == [0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1]


# === INVOCATION ===
check(Solution().transformArray)
print("All tests passed")
