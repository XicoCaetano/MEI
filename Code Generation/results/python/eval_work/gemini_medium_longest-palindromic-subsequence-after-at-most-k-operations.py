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
import sys
from functools import cache

sys.setrecursionlimit(2000)

class Solution:
    def longestPalindromicSubsequence(self, s: str, k: int) -> int:
        @cache
        def dp(i: int, j: int, rem: int) -> int:
            if i > j:
                return 0
            if i == j:
                return 1
            
            res = dp(i + 1, j, rem)
            res2 = dp(i, j - 1, rem)
            if res2 > res:
                res = res2
            
            cost = abs(ord(s[i]) - ord(s[j]))
            cost = cost if cost <= 13 else 26 - cost
            
            if cost <= rem:
                res3 = 2 + dp(i + 1, j - 1, rem - cost)
                if res3 > res:
                    res = res3
                    
            return res

        return dp(0, len(s) - 1, k)

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(s = "zxy",k = 1) == 3
    assert candidate(s = "a",k = 5) == 1
    assert candidate(s = "abced",k = 2) == 3
    assert candidate(s = "abcdefghijklmnopqrstuvwxyz",k = 25) == 14
    assert candidate(s = "zzzzz",k = 1) == 5
    assert candidate(s = "abcdeedcba",k = 5) == 10
    assert candidate(s = "zzzzz",k = 10) == 5
    assert candidate(s = "abcba",k = 0) == 5
    assert candidate(s = "aaazzz",k = 4) == 6
    assert candidate(s = "abcdef",k = 3) == 3
    assert candidate(s = "adadd",k = 2) == 3
    assert candidate(s = "mamad",k = 3) == 3
    assert candidate(s = "zyxwvutsrqponmlkjihgfedcba",k = 200) == 26
    assert candidate(s = "xyz",k = 1) == 2
    assert candidate(s = "abba",k = 1) == 4
    assert candidate(s = "abcdedcba",k = 0) == 9
    assert candidate(s = "aabaa",k = 2) == 5
    assert candidate(s = "mnopqr",k = 10) == 6
    assert candidate(s = "a",k = 0) == 1
    assert candidate(s = "abcdefg",k = 3) == 3
    assert candidate(s = "abcdabcdabcd",k = 6) == 11
    assert candidate(s = "a",k = 1) == 1
    assert candidate(s = "abcdedcba",k = 5) == 9
    assert candidate(s = "zzzzzzzzzz",k = 0) == 10
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzz",k = 100) == 20
    assert candidate(s = "racecar",k = 10) == 7
    assert candidate(s = "zzyzxzyzxzyzxzyzxzyz",k = 30) == 20
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzz",k = 50) == 20
    assert candidate(s = "aaaabbbb",k = 5) == 8
    assert candidate(s = "abcabcabcabcabcabcabcabcabcabc",k = 25) == 30
    assert candidate(s = "aaaaabbbbbcccc",k = 5) == 10
    assert candidate(s = "aaaaabbbbbaaaa",k = 50) == 14
    assert candidate(s = "aaaaabbbbbaaaaa",k = 10) == 15
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba",k = 180) == 51
    assert candidate(s = "level",k = 5) == 5
    assert candidate(s = "racecar",k = 5) == 7
    assert candidate(s = "abcdefgabcdefgabcdefgabcdefg",k = 10) == 17
    assert candidate(s = "abcdedcba",k = 1) == 9
    assert candidate(s = "qwertyuioplkjhgfdsazxcvbnmqwertyuioplkjhgfdsazxcvb",k = 100) == 47
    assert candidate(s = "abxyzabcxyzabcxyz",k = 25) == 17
    assert candidate(s = "level",k = 1) == 5
    assert candidate(s = "abcba",k = 1) == 5
    assert candidate(s = "ababababababababababababababababababab",k = 75) == 38
    assert candidate(s = "abcdefgxyzzyxgfedcba",k = 15) == 20
    assert candidate(s = "refer",k = 0) == 5
    assert candidate(s = "aabbccddeeffggzzzyyxxwwvvuuttsrqponmlkjihgfedcba",k = 100) == 47
    assert candidate(s = "palindrome",k = 15) == 9
    assert candidate(s = "amanaplanacanalpanama",k = 100) == 21
    assert candidate(s = "qwertyuiopasdfghjklzxcvbnm",k = 50) == 23
    assert candidate(s = "aaaabbbbcccc",k = 15) == 12
    assert candidate(s = "mnonmonmomnonmonmonmomnonm",k = 15) == 26
    assert candidate(s = "mississippi",k = 7) == 10
    assert candidate(s = "banana",k = 10) == 5
    assert candidate(s = "aabacbebebe",k = 5) == 8
    assert candidate(s = "madamimadam",k = 10) == 11
    assert candidate(s = "abcdexyzabcdexyzabcdexyz",k = 50) == 24
    assert candidate(s = "mississippi",k = 10) == 10
    assert candidate(s = "deified",k = 4) == 7
    assert candidate(s = "abcdedcba",k = 2) == 9
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz",k = 50) == 28
    assert candidate(s = "abcdedcba",k = 3) == 9
    assert candidate(s = "mnopqrstuvwxyzyxwvutsrqponmlkjihgfedcbazyxwvutsrqponmlkjihgfedcba",k = 200) == 60
    assert candidate(s = "aabbccabcabcabcabcabc",k = 50) == 21
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 1) == 50
    assert candidate(s = "abcdeedcba",k = 0) == 10
    assert candidate(s = "abbaacddcabb",k = 4) == 11
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz",k = 200) == 52
    assert candidate(s = "zzzyzzyzzyzzyzzyzzyz",k = 200) == 20
    assert candidate(s = "mississippi",k = 5) == 9
    assert candidate(s = "level",k = 2) == 5
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 0) == 32
    assert candidate(s = "ababbabbbabaaa",k = 15) == 14
    assert candidate(s = "rotor",k = 15) == 5
    assert candidate(s = "noon",k = 1) == 4
    assert candidate(s = "noonhighnoon",k = 5) == 12
    assert candidate(s = "abcdbca",k = 2) == 7
    assert candidate(s = "abcdxyzabcdxyzabcdxyz",k = 30) == 21
    assert candidate(s = "banana",k = 3) == 5
    assert candidate(s = "qwertyuiopasdfghjklzxcvbnmnbvcxzlkjhgfdsapoiuytrewq",k = 50) == 51
    assert candidate(s = "abacbacbacbacbacbacbacbacbacbacbacbacbacbacbacbacb",k = 20) == 50
    assert candidate(s = "abacaba",k = 3) == 7
    assert candidate(s = "mamamamamamamamamamamamamamamamama",k = 50) == 33
    assert candidate(s = "racecar",k = 2) == 7
    assert candidate(s = "noon",k = 2) == 4
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba",k = 250) == 51
    assert candidate(s = "abcdefg",k = 6) == 5
    assert candidate(s = "zyzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 300) == 84
    assert candidate(s = "madam",k = 1) == 5
    assert candidate(s = "zyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyx",k = 100) == 57
    assert candidate(s = "zyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyx",k = 200) == 39
    assert candidate(s = "rotor",k = 0) == 5
    assert candidate(s = "abcdefgzyxwvutsrqponmlkjihgfedcba",k = 50) == 29
    assert candidate(s = "abcdefghzyxwvutsrqponmlkjihgfedcba",k = 150) == 34
    assert candidate(s = "qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm",k = 100) == 47
    assert candidate(s = "abcdefghizyxwvutsrqponmlkjihgfedcba",k = 100) == 35
    assert candidate(s = "deified",k = 2) == 7
    assert candidate(s = "aaaabbbbccccdddd",k = 10) == 13
    assert candidate(s = "madam",k = 2) == 5
    assert candidate(s = "rotor",k = 3) == 5
    assert candidate(s = "abcdefgihgfedcb",k = 15) == 15
    assert candidate(s = "abcdefghihgfedcba",k = 10) == 17
    assert candidate(s = "pqrstuvwxyzabcdefghijklmno",k = 50) == 20
    assert candidate(s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",k = 0) == 30
    assert candidate(s = "abcdefghijklmnopqrstuvwxyz",k = 10) == 9
    assert candidate(s = "abcdefghijklmnopqrstuvwxzy",k = 100) == 26
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzz",k = 10) == 20
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz",k = 150) == 49
    assert candidate(s = "abcabcabcabcabcabcabcabcabcabc",k = 100) == 30
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 5) == 52
    assert candidate(s = "reviled",k = 7) == 5
    assert candidate(s = "abccba",k = 0) == 6
    assert candidate(s = "zyxzyxzyxzyxzyxzyxzyx",k = 100) == 21
    assert candidate(s = "pneumonoultramicroscopicsilicovolcanoconiosis",k = 50) == 37
    assert candidate(s = "mnopqrstuvwxyz",k = 10) == 6
    assert candidate(s = "step on no pets",k = 10) == 15
    assert candidate(s = "zyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyx",k = 100) == 42
    assert candidate(s = "abababababababababababababababab",k = 50) == 32
    assert candidate(s = "abcdefghijklmnopqrstuvwxyz",k = 50) == 20
    assert candidate(s = "mississippi",k = 3) == 9
    assert candidate(s = "abacabadabacaba",k = 5) == 15
    assert candidate(s = "mnopqrstuvwxyzzyxwvutsrqponmlk",k = 80) == 30
    assert candidate(s = "abcdezyxwvutsrqponmlkjihgf",k = 50) == 20
    assert candidate(s = "abacabadabacaba",k = 10) == 15
    assert candidate(s = "abcabcabc",k = 4) == 8
    assert candidate(s = "abababababababababab",k = 10) == 20
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz",k = 100) == 40
    assert candidate(s = "abcabcabcabcabcabcabc",k = 20) == 21
    assert candidate(s = "qwertyuiopasdfghjklzxcvbnm",k = 25) == 18
    assert candidate(s = "aaaaabbbbb",k = 10) == 10
    assert candidate(s = "zabacabadabacaba",k = 10) == 15
    assert candidate(s = "abcdefedcbaabcdefedcbaabcdefedcba",k = 60) == 33
    assert candidate(s = "mnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba",k = 150) == 36
    assert candidate(s = "abcdxyzzyxcba",k = 10) == 13
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba",k = 100) == 51
    assert candidate(s = "kayak",k = 20) == 5
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz",k = 100) == 40
    assert candidate(s = "abcdzdcba",k = 3) == 9
    assert candidate(s = "aababaaa",k = 2) == 8
    assert candidate(s = "deed",k = 3) == 4
    assert candidate(s = "ababababababababababababababababababababababababababab",k = 100) == 54
    assert candidate(s = "abcdefghijkmlkjihgfedcba",k = 50) == 24
    assert candidate(s = "abcdeedcba",k = 3) == 10
    assert candidate(s = "abcdefg",k = 10) == 6
    assert candidate(s = "mnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba",k = 50) == 30
    assert candidate(s = "racecar",k = 0) == 7
    assert candidate(s = "zyxwvutsrqponmlkjihgfedcba",k = 150) == 26
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba",k = 50) == 51
    assert candidate(s = "abcdefghijabcdefghij",k = 15) == 13
    assert candidate(s = "abacabadabacabadabacaba",k = 20) == 23
    assert candidate(s = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa",k = 5) == 52
    assert candidate(s = "abcdabcdabcdabcd",k = 20) == 16
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz",k = 180) == 52
    assert candidate(s = "abcdefghijjihgfedcba",k = 5) == 20


# === INVOCATION ===
check(Solution().longestPalindromicSubsequence)
print("All tests passed")
