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
import math

class Solution:
    def minOperations(self, queries: List[List[int]]) -> int:
        
        def get_total_steps(n: int) -> int:
            if n <= 0:
                return 0
            
            total = 0
            k = 1
            lower = 1
            while lower <= n:
                upper = min(n, (1 << (2 * k)) - 1)
                count = upper - lower + 1
                total += count * k
                lower = upper + 1
                k += 1
            return total

        ans = 0
        for l, r in queries:
            total_steps_in_range = get_total_steps(r) - get_total_steps(l - 1)
            ans += (total_steps_in_range + 1) // 2
            
        return ans

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(queries = [[1, 2], [2, 4]]) == 3
    assert candidate(queries = [[10, 20], [20, 30], [30, 40]]) == 48
    assert candidate(queries = [[1, 1000000000], [500000000, 1000000000]]) == 11071043045
    assert candidate(queries = [[1, 100], [100, 1000], [1000, 10000]]) == 32279
    assert candidate(queries = [[1, 10], [10, 20]]) == 23
    assert candidate(queries = [[5, 5], [10, 10], [15, 15]]) == 3
    assert candidate(queries = [[1, 1000000000], [1, 1000000000]]) == 14642086074
    assert candidate(queries = [[2, 6]]) == 4
    assert candidate(queries = [[1, 1000000000], [2, 999999999]]) == 14642086066
    assert candidate(queries = [[1, 3], [4, 6], [7, 9]]) == 8
    assert candidate(queries = [[1, 1000000], [500000, 1000000]]) == 7325248
    assert candidate(queries = [[5, 5], [10, 10]]) == 2
    assert candidate(queries = [[1, 10], [10, 20], [20, 30]]) == 40
    assert candidate(queries = [[1, 500000], [500001, 1000000], [1000001, 1500000], [1500001, 2000000]]) == 10300956
    assert candidate(queries = [[1, 10000], [20000, 30000], [40000, 50000], [60000, 70000], [80000, 90000]]) == 199523
    assert candidate(queries = [[100000000, 200000000], [200000000, 300000000], [300000000, 400000000], [400000000, 500000000], [500000000, 600000000], [600000000, 700000000], [700000000, 800000000], [800000000, 900000000], [900000000, 1000000000]]) == 6665782343
    assert candidate(queries = [[1, 10], [2, 20], [3, 30], [4, 40], [5, 50], [6, 60], [7, 70], [8, 80], [9, 90], [10, 100]]) == 751
    assert candidate(queries = [[1, 1000000], [1000001, 2000000], [2000001, 3000000]]) == 15800956
    assert candidate(queries = [[500000, 750000], [750001, 1000000], [1, 499999]]) == 4825243
    assert candidate(queries = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]]) == 16
    assert candidate(queries = [[10, 100], [200, 300], [400, 500], [600, 700], [800, 900]]) == 1136
    assert candidate(queries = [[1, 100], [101, 200], [201, 300], [301, 400], [401, 500], [501, 600], [601, 700], [701, 800], [801, 900], [901, 1000]]) == 2333
    assert candidate(queries = [[1, 500], [501, 1000], [1001, 1500], [1501, 2000], [2001, 2500], [2501, 3000]]) == 8321
    assert candidate(queries = [[1, 1000000000]]) == 7321043037
    assert candidate(queries = [[1, 1000], [1000, 2000], [2000, 3000], [3000, 4000], [4000, 5000], [5000, 6000], [6000, 7000], [7000, 8000], [8000, 9000], [9000, 10000]]) == 32305
    assert candidate(queries = [[1, 1000000000], [1, 500000000], [500000001, 1000000000]]) == 14642086074
    assert candidate(queries = [[1, 333333333], [333333334, 666666666], [666666667, 999999999]]) == 7321043031
    assert candidate(queries = [[1, 9], [2, 18], [3, 27], [4, 36], [5, 45], [6, 54], [7, 63], [8, 72], [9, 81], [10, 90]]) == 652
    assert candidate(queries = [[2, 3], [3, 5], [5, 7], [7, 9], [9, 11]]) == 13
    assert candidate(queries = [[1, 100], [2, 200], [3, 300], [4, 400], [5, 500], [6, 600], [7, 700], [8, 800], [9, 900], [10, 1000]]) == 12146
    assert candidate(queries = [[1, 1000], [1001, 2000], [2001, 3000], [3001, 4000], [4001, 5000], [5001, 6000], [6001, 7000], [7001, 8000], [8001, 9000], [9001, 10000]]) == 32274
    assert candidate(queries = [[500000000, 750000000], [750000001, 1000000000]]) == 3750000008
    assert candidate(queries = [[1, 2], [3, 4], [5, 6], [7, 8], [9, 10], [11, 12], [13, 14], [15, 16], [17, 18], [19, 20]]) == 22
    assert candidate(queries = [[1, 100000], [2, 200000], [3, 300000], [4, 400000], [5, 500000]]) == 6738351
    assert candidate(queries = [[1, 10000000], [10000001, 20000000], [20000001, 30000000], [30000001, 40000000]]) == 248815197
    assert candidate(queries = [[1, 3], [4, 7], [8, 11], [12, 15], [16, 19], [20, 23], [24, 27], [28, 31], [32, 35], [36, 39], [40, 43], [44, 47], [48, 51], [52, 55], [56, 59], [60, 63], [64, 67], [68, 71], [72, 75], [76, 79], [80, 83], [84, 87], [88, 91], [92, 95], [96, 99]]) == 158
    assert candidate(queries = [[1, 10], [20, 30], [30, 40], [40, 50], [50, 60], [60, 70], [70, 80], [80, 90], [90, 100]]) == 163
    assert candidate(queries = [[1, 1000000000]]) == 7321043037
    assert candidate(queries = [[1, 10], [2, 20], [3, 30], [4, 40], [5, 50], [6, 60], [7, 70], [8, 80], [9, 90], [10, 100]]) == 751
    assert candidate(queries = [[500000000, 500000010], [500000010, 500000020], [500000020, 500000030], [500000030, 500000040], [500000040, 500000050]]) == 415
    assert candidate(queries = [[1, 500000], [500001, 1000000], [1000001, 1500000], [1500001, 2000000], [2000001, 2500000], [2500001, 3000000], [3000001, 3500000], [3500001, 4000000], [4000001, 4500000], [4500001, 5000000]]) == 27203805
    assert candidate(queries = [[1, 31622], [31623, 63245], [63246, 94868], [94869, 126491], [126492, 158114]]) == 667829
    assert candidate(queries = [[1, 1000000000], [500000000, 1000000000]]) == 11071043045
    assert candidate(queries = [[1, 10], [1, 20], [1, 30], [1, 40], [1, 50], [1, 60], [1, 70], [1, 80], [1, 90], [1, 100]]) == 784
    assert candidate(queries = [[100, 200], [200, 300], [300, 400], [400, 500], [500, 600]]) == 1186
    assert candidate(queries = [[1, 10], [11, 20], [21, 30], [31, 40], [41, 50], [51, 60], [61, 70], [71, 80], [81, 90], [91, 100]]) == 161
    assert candidate(queries = [[1, 100], [200, 250], [350, 400], [550, 600], [750, 800], [950, 1000]]) == 774
    assert candidate(queries = [[1, 2], [4, 8], [16, 32], [32, 64], [64, 128], [128, 256], [256, 512], [512, 1024], [1024, 2048], [2048, 4096]]) == 11620
    assert candidate(queries = [[1, 9], [9, 81], [81, 729], [729, 6561]]) == 20243
    assert candidate(queries = [[1, 10], [2, 9], [3, 8], [4, 7], [5, 6]]) == 28
    assert candidate(queries = [[1, 100], [50, 150], [100, 200], [150, 250], [200, 300]]) == 984
    assert candidate(queries = [[1, 100000], [200000, 300000], [300000, 400000], [400000, 500000], [500000, 600000]]) == 2375262
    assert candidate(queries = [[1, 100], [101, 200], [201, 300], [301, 400], [401, 500]]) == 1083
    assert candidate(queries = [[1, 1], [2, 2], [3, 3], [4, 4], [5, 5], [6, 6], [7, 7], [8, 8], [9, 9], [10, 10]]) == 10
    assert candidate(queries = [[1, 3], [2, 5], [3, 7], [4, 9], [5, 11], [6, 13], [7, 15], [8, 17], [9, 19], [10, 21]]) == 79
    assert candidate(queries = [[1, 100], [50, 150], [100, 200], [150, 250], [200, 300], [250, 350], [300, 400], [350, 450], [400, 500], [450, 500]]) == 2121
    assert candidate(queries = [[1, 10000], [20000, 30000], [40000, 50000], [60000, 70000], [70000, 80000], [80000, 90000], [90000, 100000]]) == 289533
    assert candidate(queries = [[100000000, 200000000], [300000000, 400000000], [500000000, 600000000], [700000000, 800000000], [900000000, 1000000000]]) == 3700000039
    assert candidate(queries = [[1, 1], [2, 2], [3, 3], [4, 4], [5, 5], [6, 6], [7, 7], [8, 8], [9, 9], [10, 10]]) == 10
    assert candidate(queries = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10], [10, 11], [11, 12], [12, 13], [13, 14], [14, 15], [15, 16], [16, 17], [17, 18], [18, 19], [19, 20], [20, 21]]) == 44
    assert candidate(queries = [[10, 2000000], [2000000, 3000000], [3000000, 4000000], [4000000, 5000000], [5000000, 6000000]]) == 33203820
    assert candidate(queries = [[1, 1000000000], [1000000, 1000000000]]) == 14637260837
    assert candidate(queries = [[1, 1000], [1001, 2000], [2001, 3000], [3001, 4000], [4001, 5000]]) == 14774
    assert candidate(queries = [[1, 1000000000], [1, 1], [999999999, 1000000000]]) == 7321043053
    assert candidate(queries = [[1, 5], [6, 10], [11, 15], [16, 20], [21, 25], [26, 30], [31, 35], [36, 40], [41, 45], [46, 50]]) == 70
    assert candidate(queries = [[500000000, 500000010], [500000010, 500000020], [500000020, 500000030], [500000030, 500000040], [500000040, 500000050]]) == 415
    assert candidate(queries = [[1, 500000], [250000, 750000], [500000, 1000000], [750000, 1250000]]) == 9919899
    assert candidate(queries = [[500, 1000], [1500, 2000], [2500, 3000], [3500, 4000], [4500, 5000]]) == 7516
    assert candidate(queries = [[1, 100], [50, 150], [100, 200], [150, 250], [200, 300], [250, 350], [300, 400]]) == 1487
    assert candidate(queries = [[100, 200], [150, 250], [200, 300], [250, 350], [300, 400]]) == 1132
    assert candidate(queries = [[1, 2], [3, 5], [7, 10], [11, 15], [16, 20]]) == 21
    assert candidate(queries = [[1, 200], [50, 150], [100, 300], [250, 400]]) == 1355
    assert candidate(queries = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6], [6, 7], [7, 8], [8, 9], [9, 10]]) == 16
    assert candidate(queries = [[1, 2], [3, 6], [7, 10], [11, 14], [15, 18]]) == 19
    assert candidate(queries = [[1, 10], [2, 11], [3, 12], [4, 13], [5, 14], [6, 15], [7, 16], [8, 17], [9, 18], [10, 19]]) == 104
    assert candidate(queries = [[1, 100], [101, 200], [201, 300], [301, 400], [401, 500], [501, 600], [601, 700], [701, 800], [801, 900], [901, 1000]]) == 2333
    assert candidate(queries = [[1, 1000000], [1000001, 2000000], [2000001, 3000000], [3000001, 4000000], [4000001, 5000000]]) == 27203805
    assert candidate(queries = [[100, 1000], [200, 2000], [300, 3000], [400, 4000], [500, 5000]]) == 39064
    assert candidate(queries = [[100, 200], [200, 300], [300, 400], [400, 500], [500, 600], [600, 700], [700, 800], [800, 900], [900, 1000]]) == 2198
    assert candidate(queries = [[1, 2], [2, 3], [3, 4], [4, 5], [5, 6]]) == 8
    assert candidate(queries = [[1, 3], [2, 4], [3, 5], [4, 6], [5, 7], [6, 8], [7, 9], [8, 10], [9, 11], [10, 12]]) == 28
    assert candidate(queries = [[1, 9], [10, 18], [19, 27], [28, 36], [37, 45], [46, 54], [55, 63], [64, 72], [73, 81], [82, 90]]) == 143
    assert candidate(queries = [[1, 9], [10, 18], [19, 27], [28, 36], [37, 45], [46, 54], [55, 63], [64, 72], [73, 81], [82, 90], [91, 99]]) == 161
    assert candidate(queries = [[1, 1000000000], [500000000, 750000000]]) == 9196043045
    assert candidate(queries = [[1, 2000000000], [1000000000, 2000000000], [500000000, 1500000000], [1500000000, 2500000000]]) == 38960430326
    assert candidate(queries = [[1, 5], [2, 10], [3, 15], [4, 20], [5, 25], [6, 30], [7, 35], [8, 40], [9, 45], [10, 50]]) == 300
    assert candidate(queries = [[1000, 2000], [3000, 4000], [5000, 6000], [7000, 8000], [9000, 10000], [11000, 12000], [13000, 14000], [15000, 16000], [17000, 18000], [19000, 20000]]) == 35026
    assert candidate(queries = [[1, 1000], [501, 1500], [1001, 2000], [1501, 2500], [2001, 3000], [2501, 3500]]) == 17060
    assert candidate(queries = [[100000000, 150000000], [150000001, 200000000], [200000001, 250000000], [250000001, 300000000]]) == 1415782280
    assert candidate(queries = [[100, 200], [200, 300], [300, 400], [400, 500], [500, 600], [600, 700], [700, 800], [800, 900], [900, 1000]]) == 2198
    assert candidate(queries = [[1, 3], [4, 6], [7, 9], [10, 12], [13, 15], [16, 18], [19, 21]]) == 24
    assert candidate(queries = [[1, 2], [2, 4], [4, 8], [8, 16], [16, 32], [32, 64], [64, 128]]) == 224
    assert candidate(queries = [[1, 100], [101, 200], [201, 300], [301, 400], [401, 500]]) == 1083
    assert candidate(queries = [[1, 1000000], [2000000, 3000000], [3000000, 4000000], [4000000, 5000000], [5000000, 6000000], [6000000, 7000000], [7000000, 8000000], [8000000, 9000000], [9000000, 10000000]]) == 51728139


# === INVOCATION ===
check(Solution().minOperations)
print("All tests passed")
