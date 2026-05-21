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
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        
        pref = [0] * (n + 1)
        for i in range(n):
            pref[i + 1] = pref[i] + (1 if s[i] == '1' else 0)
            
        def get_ones(l, r):
            if l > r: return 0
            return pref[r + 1] - pref[l]

        segments = []
        if n > 0:
            curr_char = s[0]
            start = 0
            for i in range(1, n):
                if s[i] != curr_char:
                    segments.append((curr_char, start, i - 1))
                    curr_char = s[i]
                    start = i
            segments.append((curr_char, start, n - 1))
            
        m = len(segments)
        seg_idx = [0] * n
        for idx, (char, start, end) in enumerate(segments):
            for i in range(start, end + 1):
                seg_idx[i] = idx
    
        one_seg_lens = [] 
        zero_seg_lens = [] 
        
        results = []
        for l, r in queries:
            initial_ones = get_ones(l, r)
            
            idx_l = seg_idx[l]
            idx_r = seg_idx[r]
            
            q_segments = []
            if idx_l == idx_r:
                q_segments.append((s[l], r - l + 1))
            else:
                # First
                q_segments.append((s[l], segments[idx_l][2] - l + 1))
                # Middles
                for i in range(idx_l + 1, idx_r):
                    q_segments.append((segments[i][0], segments[i][2] - segments[i][1] + 1))
                # Last
                q_segments.append((s[r], r - segments[idx_r][1] + 1))
            
            max_zero = 0
            min_one = float('inf')
            
            # Find 0-blocks (all are candidates)
            for char, length in q_segments:
                if char == '0':
                    max_zero = max(max_zero, length)
    
            for i in range(1, len(q_segments) - 1):
                char, length = q_segments[i]
                if char == '1':
                    min_one = min(min_one, length)
            
            if min_one == float('inf') or max_zero == 0:
                results.append(initial_ones)
            else:
                results.append(initial_ones + max_zero - min_one)
                
        return results

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(s = "0100",queries = [[0, 3], [0, 2], [1, 3], [2, 3]]) == [4, 3, 1, 1]
    assert candidate(s = "01",queries = [[0, 1]]) == [1]
    assert candidate(s = "01010",queries = [[0, 3], [1, 4], [1, 3]]) == [4, 4, 2]
    assert candidate(s = "1000100",queries = [[1, 5], [0, 6], [0, 4]]) == [6, 7, 2]
    assert candidate(s = "111111111111111111111111111111111111111111111111",queries = [[0, 39], [1, 38], [2, 37], [3, 36], [4, 35], [5, 34], [6, 33], [7, 32], [8, 31], [9, 30]]) == [48, 48, 48, 48, 48, 48, 48, 48, 48, 48]
    assert candidate(s = "11111111111111111",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [17, 17, 17, 17, 17]
    assert candidate(s = "10000000010000000001000000001",queries = [[0, 20], [5, 15], [10, 19]]) == [21, 14, 4]
    assert candidate(s = "000000000000000000000000000000000000000000000000",queries = [[0, 39], [1, 38], [2, 37], [3, 36], [4, 35], [5, 34], [6, 33], [7, 32], [8, 31], [9, 30]]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(s = "11001100110011001100110011",queries = [[0, 20], [5, 15], [0, 9], [10, 19], [15, 25]]) == [18, 18, 18, 18, 18]
    assert candidate(s = "111100001111000011110000",queries = [[0, 23], [4, 19], [5, 18], [6, 17], [7, 16], [8, 15], [9, 14], [10, 13], [11, 12]]) == [20, 20, 19, 18, 17, 12, 12, 12, 12]
    assert candidate(s = "1001001001001001001001001",queries = [[0, 24], [2, 22], [3, 21], [4, 20], [5, 19], [6, 18], [7, 17], [8, 16], [9, 15], [10, 14], [11, 13]]) == [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 11]
    assert candidate(s = "00101010101010101010",queries = [[0, 9], [5, 15], [10, 19]]) == [12, 11, 11]
    assert candidate(s = "10101010101010101010101010",queries = [[0, 25], [1, 24], [2, 23], [3, 22], [4, 21]]) == [15, 15, 15, 15, 15]
    assert candidate(s = "101010101010101010101010101010101010101010101010101010101010",queries = [[0, 59], [1, 58], [2, 57], [3, 56], [4, 55], [5, 54], [6, 53], [7, 52], [8, 51], [9, 50]]) == [32, 32, 32, 32, 32, 32, 32, 32, 32, 32]
    assert candidate(s = "111000111000111",queries = [[0, 14], [1, 13], [2, 12], [3, 11], [4, 10]]) == [15, 15, 15, 15, 13]
    assert candidate(s = "000011110000111100001111",queries = [[0, 23], [4, 19], [5, 18], [6, 17], [7, 16], [8, 15], [9, 14], [10, 13], [11, 12]]) == [20, 20, 19, 18, 17, 12, 12, 12, 12]
    assert candidate(s = "111000111000",queries = [[0, 11], [3, 8], [4, 7], [5, 6]]) == [12, 6, 6, 6]
    assert candidate(s = "01010101010101010101010101010101",queries = [[0, 15], [15, 30], [0, 29]]) == [18, 18, 18]
    assert candidate(s = "10101010101010101010",queries = [[0, 19], [1, 18], [2, 17], [3, 16], [4, 15], [5, 14], [6, 13], [7, 12], [8, 11], [9, 10]]) == [12, 12, 12, 12, 12, 12, 12, 12, 12, 10]
    assert candidate(s = "1001001001001001001",queries = [[0, 18], [1, 17], [2, 16], [5, 13], [3, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "11110000111100001111",queries = [[0, 9], [5, 15], [10, 19]]) == [12, 19, 12]
    assert candidate(s = "1010101010",queries = [[0, 9], [1, 8], [2, 7], [3, 6]]) == [7, 7, 7, 7]
    assert candidate(s = "0000011111000001111100000111110000011111",queries = [[0, 9], [10, 19], [20, 29], [30, 39], [0, 39]]) == [20, 20, 20, 20, 30]
    assert candidate(s = "1100001100011110001000000011001",queries = [[5, 15], [2, 20], [0, 30], [10, 25]]) == [16, 19, 22, 22]
    assert candidate(s = "00000100000100000",queries = [[0, 14], [1, 13], [2, 12], [5, 10], [3, 8]]) == [12, 11, 10, 2, 7]
    assert candidate(s = "00000000000000000",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [0, 0, 0, 0, 0]
    assert candidate(s = "0101010101010101010",queries = [[0, 18], [1, 17], [2, 16], [5, 13], [3, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "000100010001000100010001000100010001000100010001000100010001",queries = [[0, 59], [1, 58], [2, 57], [3, 56], [4, 55], [5, 54], [6, 53], [7, 52], [8, 51], [9, 50]]) == [21, 21, 21, 21, 21, 21, 21, 21, 21, 21]
    assert candidate(s = "10101010101010101",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "0101010101",queries = [[0, 9], [1, 8], [2, 7], [3, 6]]) == [7, 7, 7, 7]
    assert candidate(s = "01010101010101010101010101",queries = [[0, 25], [1, 24], [2, 23], [3, 22], [4, 21]]) == [15, 15, 15, 15, 15]
    assert candidate(s = "1100110011",queries = [[0, 9], [1, 8], [2, 7], [3, 6], [4, 5]]) == [10, 10, 10, 8, 6]
    assert candidate(s = "1001001001",queries = [[0, 9], [1, 8], [2, 7], [3, 6], [4, 5]]) == [8, 8, 7, 4, 4]
    assert candidate(s = "1001001001001001001",queries = [[0, 18], [1, 17], [2, 16], [3, 15], [4, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "0000000000",queries = [[0, 9], [2, 7], [4, 6]]) == [0, 0, 0]
    assert candidate(s = "1111111111",queries = [[0, 9], [2, 7], [4, 6]]) == [10, 10, 10]
    assert candidate(s = "110001100110001",queries = [[0, 14], [1, 13], [2, 12], [5, 10], [3, 8]]) == [12, 12, 12, 7, 11]
    assert candidate(s = "0000011111000001111100000",queries = [[0, 24], [1, 23], [2, 22], [3, 21], [4, 20], [5, 19], [6, 18], [7, 17], [8, 16], [9, 15]]) == [20, 19, 18, 17, 16, 10, 10, 10, 10, 10]
    assert candidate(s = "100100100100100",queries = [[0, 14], [1, 13], [2, 12], [3, 11], [4, 10], [5, 9]]) == [9, 9, 9, 9, 9, 8]
    assert candidate(s = "1001001001001",queries = [[0, 12], [2, 9], [3, 8], [4, 7], [5, 6]]) == [9, 9, 9, 8, 5]
    assert candidate(s = "1000000001",queries = [[1, 8], [0, 9], [2, 7], [3, 6]]) == [2, 2, 2, 2]
    assert candidate(s = "0000011110001110000",queries = [[0, 18], [1, 17], [2, 16], [3, 15], [4, 14], [5, 13]]) == [15, 14, 13, 12, 11, 7]
    assert candidate(s = "00110011001100110",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [12, 12, 12, 11, 12]


# === INVOCATION ===
check(Solution().maxActiveSectionsAfterTrade)
print("All tests passed")
