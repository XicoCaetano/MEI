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
from functools import lru_cache

class Solution:
    def beautifulNumbers(self, l: int, r: int) -> int:
        def count_up_to(n):
            digits = list(map(int, str(n)))
            length = len(digits)
            
            # digit_product can be large but bounded: max 9^9 = 387420489
            # digit_sum bounded: max 9*9 = 81
            # We track (product, sum) but product can be huge
            # Instead track product mod lcm(1..81) and actual sum
            # lcm(1..81) - use this to check divisibility by any sum <= 81
            
            import math
            lcm_val = 1
            for i in range(1, 82):
                lcm_val = lcm_val * i // math.gcd(lcm_val, i)
            
            @lru_cache(maxsize=None)
            def dp(pos, prod_mod, digit_sum, tight, started):
                if pos == length:
                    if not started:
                        return 0
                    if digit_sum == 0:
                        return 0
                    # Check if prod_mod % digit_sum == 0
                    return 1 if prod_mod % digit_sum == 0 else 0
                
                limit = digits[pos] if tight else 9
                result = 0
                
                for d in range(0, limit + 1):
                    new_tight = tight and (d == limit)
                    if not started and d == 0:
                        result += dp(pos + 1, 1, 0, new_tight, False)
                    else:
                        new_prod = (prod_mod * d) % lcm_val
                        new_sum = digit_sum + d
                        result += dp(pos + 1, new_prod, new_sum, new_tight, True)
                
                return result
            
            ans = dp(0, 1, 0, True, False)
            dp.cache_clear()
            return ans
        
        return count_up_to(r) - count_up_to(l - 1)

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(l = 999,r = 999) == 1
    assert candidate(l = 1,r = 9) == 9
    assert candidate(l = 900,r = 1000) == 35
    assert candidate(l = 789,r = 890) == 35
    assert candidate(l = 500,r = 5000) == 1800
    assert candidate(l = 5,r = 50) == 13
    assert candidate(l = 100,r = 200) == 32
    assert candidate(l = 50,r = 100) == 9
    assert candidate(l = 10,r = 20) == 2
    assert candidate(l = 999,r = 1001) == 3
    assert candidate(l = 1,r = 999999999) == 670349658
    assert candidate(l = 990,r = 1000) == 3
    assert candidate(l = 100000000,r = 100000000) == 1
    assert candidate(l = 123,r = 456) == 110
    assert candidate(l = 1,r = 1) == 1
    assert candidate(l = 300,r = 500) == 70
    assert candidate(l = 99999,r = 100001) == 2
    assert candidate(l = 100,r = 150) == 19
    assert candidate(l = 1,r = 15) == 10
    assert candidate(l = 1000,r = 10000) == 3676
    assert candidate(l = 111,r = 222) == 33
    assert candidate(l = 1000,r = 1010) == 11
    assert candidate(l = 50,r = 55) == 1
    assert candidate(l = 100000,r = 200000) == 52892
    assert candidate(l = 100000,r = 150000) == 29004
    assert candidate(l = 999999,r = 1000001) == 2
    assert candidate(l = 123456,r = 654321) == 288118
    assert candidate(l = 1,r = 1000000) == 534358
    assert candidate(l = 333333,r = 444444) == 59841
    assert candidate(l = 90000000,r = 99999999) == 6259058
    assert candidate(l = 123456789,r = 2147483647) == 1428531442
    assert candidate(l = 7654321,r = 8765432) == 646518
    assert candidate(l = 1000000,r = 10000000) == 5311175
    assert candidate(l = 987654,r = 987664) == 3
    assert candidate(l = 10000000,r = 10001000) == 1001
    assert candidate(l = 10000000,r = 20000000) == 6285218
    assert candidate(l = 999999990,r = 999999999) == 2
    assert candidate(l = 999999,r = 999999) == 0
    assert candidate(l = 888888,r = 999999) == 57963
    assert candidate(l = 99999999,r = 100000000) == 1
    assert candidate(l = 5000,r = 75000) == 33900
    assert candidate(l = 1,r = 1000000000) == 670349659
    assert candidate(l = 777777,r = 888888) == 58602
    assert candidate(l = 987654321,r = 1000000000) == 7554239
    assert candidate(l = 999999,r = 9999999) == 5311174
    assert candidate(l = 500000,r = 510000) == 10001
    assert candidate(l = 987654321,r = 987654321) == 1
    assert candidate(l = 123456789,r = 234567890) == 73969442
    assert candidate(l = 2000000,r = 2010000) == 10001
    assert candidate(l = 100000,r = 1000000) == 486888
    assert candidate(l = 10000000,r = 10000000) == 1
    assert candidate(l = 555555555,r = 555555555) == 0
    assert candidate(l = 1000000,r = 1001000) == 1001
    assert candidate(l = 500000,r = 999999) == 270652
    assert candidate(l = 100000000,r = 300000000) == 134174863
    assert candidate(l = 1000000,r = 3000000) == 1175795
    assert candidate(l = 456789,r = 456789123) == 304015671
    assert candidate(l = 123456,r = 123567) == 46
    assert candidate(l = 56789,r = 567890) == 276722
    assert candidate(l = 88888888,r = 99999999) == 6902887
    assert candidate(l = 50000000,r = 60000000) == 6522427
    assert candidate(l = 500000000,r = 501000000) == 1000001
    assert candidate(l = 1234567,r = 12345678) == 6951395
    assert candidate(l = 12345,r = 67890) == 26696
    assert candidate(l = 98765432,r = 98765432) == 0
    assert candidate(l = 8000000,r = 8100000) == 100001
    assert candidate(l = 456789,r = 987654) == 286642
    assert candidate(l = 1234567,r = 8765432) == 4438756
    assert candidate(l = 555555,r = 666666) == 61137
    assert candidate(l = 5000000,r = 6000000) == 609303
    assert candidate(l = 50000,r = 55000) == 2738
    assert candidate(l = 1000000,r = 1010000) == 10001
    assert candidate(l = 800000,r = 900000) == 53367
    assert candidate(l = 500000000,r = 550000000) == 36195523
    assert candidate(l = 500000,r = 550000) == 30521
    assert candidate(l = 10000000,r = 100000000) == 57110376
    assert candidate(l = 111111,r = 222222) == 58091
    assert candidate(l = 100000000,r = 111111111) == 11111111
    assert candidate(l = 800000,r = 801000) == 1001
    assert candidate(l = 100000000,r = 200000000) == 66911398
    assert candidate(l = 500000,r = 600000) == 55997
    assert candidate(l = 999900,r = 1000100) == 124
    assert candidate(l = 123456789,r = 123456789) == 1
    assert candidate(l = 100000,r = 999999) == 486887
    assert candidate(l = 111111111,r = 222222222) == 73867777
    assert candidate(l = 8000000,r = 8999999) == 583871
    assert candidate(l = 987654,r = 987654) == 0
    assert candidate(l = 999000,r = 1001000) == 1335
    assert candidate(l = 123,r = 987654321) == 662795385
    assert candidate(l = 100000,r = 500000) == 216236
    assert candidate(l = 77777777,r = 88888888) == 6956761
    assert candidate(l = 5000000,r = 5010000) == 10001


# === INVOCATION ===
check(Solution().beautifulNumbers)
print("All tests passed")
