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
    def reverseDegree(self, s: str) -> int:
        return sum((26 - (ord(c) - ord('a'))) * (i + 1) for i, c in enumerate(s))

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(s = "zzzz") == 10
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz") == 15678
    assert candidate(s = "world") == 230
    assert candidate(s = "abcdefghijklmnopqrstuvwxyz") == 3276
    assert candidate(s = "z") == 1
    assert candidate(s = "degree") == 405
    assert candidate(s = "abc") == 148
    assert candidate(s = "reverse") == 403
    assert candidate(s = "aaa") == 156
    assert candidate(s = "zzz") == 6
    assert candidate(s = "zyxwvutsrqponmlkjihgfedcba") == 6201
    assert candidate(s = "a") == 26
    assert candidate(s = "zaza") == 160
    assert candidate(s = "hello") == 228
    assert candidate(s = "aaabbbccc") == 1107
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzzxywvutsrqponmlkjihgfedcba") == 18602
    assert candidate(s = "thisisaverylongstringthatweneedtocheck") == 11902
    assert candidate(s = "abcdefghijabcdefghijabcdefghijabcdefghij") == 17300
    assert candidate(s = "letsdothisoverandover") == 3275
    assert candidate(s = "repeatedcharactersss") == 3224
    assert candidate(s = "complex") == 362
    assert candidate(s = "abracadabra") == 1453
    assert candidate(s = "pythonprogramming") == 2314
    assert candidate(s = "uniquecharacters") == 2168
    assert candidate(s = "randomstringswithdifferentcharactersareincludedhere") == 22682
    assert candidate(s = "thisisareallylongstringwithvariouscharacters") == 14440
    assert candidate(s = "quickbrownfoxjumpsoverthelazydog") == 7059
    assert candidate(s = "python") == 250
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 1711
    assert candidate(s = "aquickbrownfoxjumpsoverthelazydog") == 7509
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 1485
    assert candidate(s = "abcdabcdabcd") == 1896
    assert candidate(s = "algorithms") == 724
    assert candidate(s = "exampletestcase") == 1940
    assert candidate(s = "reversealphabetcalculationsarefun") == 9042
    assert candidate(s = "thisisareallylongstringthatweneedtocalculatereversedegree") == 26964
    assert candidate(s = "qwertypoiasdfghjklzxcvbnm") == 4708
    assert candidate(s = "abacaxabacax") == 1576
    assert candidate(s = "loonyspoons") == 684
    assert candidate(s = "hellothere") == 880
    assert candidate(s = "thisisareallylongstringwithsomerepeatedcharacters") == 19494
    assert candidate(s = "pythonisfun") == 832
    assert candidate(s = "programmingisfun") == 1980
    assert candidate(s = "qwen") == 136
    assert candidate(s = "alibabacloud") == 1461
    assert candidate(s = "reversedegree") == 1634
    assert candidate(s = "mississippi") == 851
    assert candidate(s = "testcase") == 611
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz") == 12753
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba") == 18226
    assert candidate(s = "programming") == 1068
    assert candidate(s = "multiplewordstringexample") == 4768
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 1275
    assert candidate(s = "thequickbrownfoxjumpsoverthelazydog") == 8442
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzz") == 406


# === INVOCATION ===
check(Solution().reverseDegree)
print("All tests passed")
