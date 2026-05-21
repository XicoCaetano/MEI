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
    def hasSpecialSubstring(self, s: str, k: int) -> bool:
        n = len(s)
        
        for i in range(n - k + 1):
            # Check if substring of length k starting at i has all same characters
            substring = s[i:i+k]
            if len(set(substring)) != 1:
                continue
            
            # Check character before substring
            if i > 0 and s[i-1] == s[i]:
                continue
            
            # Check character after substring
            if i + k < n and s[i+k] == s[i]:
                continue
            
            # All conditions satisfied
            return True
        
        return False

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(s = "abc",k = 2) == False
    assert candidate(s = "aabbccddeeff",k = 2) == True
    assert candidate(s = "abcde",k = 1) == True
    assert candidate(s = "zzzz",k = 4) == True
    assert candidate(s = "xyzxyz",k = 1) == True
    assert candidate(s = "abcdabcd",k = 2) == False
    assert candidate(s = "aaaaa",k = 3) == False
    assert candidate(s = "zzzzz",k = 5) == True
    assert candidate(s = "aabbcc",k = 2) == True
    assert candidate(s = "aaabaaa",k = 3) == True
    assert candidate(s = "xyzxxxxxzyx",k = 6) == False
    assert candidate(s = "aaabbbcccddd",k = 4) == False
    assert candidate(s = "xyzxxxxxyzzzzzzzzz",k = 4) == False
    assert candidate(s = "mmmmnmmmmm",k = 5) == True
    assert candidate(s = "mnopqrrrrrstuvwxyz",k = 5) == True
    assert candidate(s = "pppppqqqqqqppppp",k = 5) == True
    assert candidate(s = "llllllllllllllllllll",k = 10) == False
    assert candidate(s = "aabbbcccccddddd",k = 5) == True
    assert candidate(s = "aabbccddeeffgghhhiii",k = 3) == True
    assert candidate(s = "abababababababa",k = 3) == False
    assert candidate(s = "aaaabbbbaaaa",k = 3) == False
    assert candidate(s = "xyzxyzxyzxyzxyz",k = 3) == False
    assert candidate(s = "abcdefghijjjjklmnop",k = 5) == False
    assert candidate(s = "abcdefghijjjjjjklmnopqr",k = 6) == True
    assert candidate(s = "aabbaaabbbaaa",k = 3) == True
    assert candidate(s = "aabbccddeeffgghhiijjkk",k = 2) == True
    assert candidate(s = "xyzzzzzyx",k = 4) == False
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 40) == False
    assert candidate(s = "mnopqrssssstuvw",k = 5) == True
    assert candidate(s = "ppppqqqqrrrr",k = 4) == True
    assert candidate(s = "aaaaabbbbbbcccccc",k = 5) == True
    assert candidate(s = "abccccba",k = 4) == True
    assert candidate(s = "abcdeeeefgh",k = 4) == True
    assert candidate(s = "abcdefffgghijklmnoooppqrstuvwwxyz",k = 3) == True
    assert candidate(s = "abcdeffghiiijjjjjklmnop",k = 5) == True
    assert candidate(s = "qweeeeeeret",k = 5) == False
    assert candidate(s = "abcdefffffghijkl",k = 5) == True
    assert candidate(s = "abccbaabccba",k = 2) == True
    assert candidate(s = "mnopqrstuvwxyzjjjjjjjjjjjjjjjjmnopqrstuvwxyz",k = 15) == False
    assert candidate(s = "xyzzyzx",k = 2) == True
    assert candidate(s = "zzzaaaazzz",k = 3) == True
    assert candidate(s = "ababababab",k = 2) == False
    assert candidate(s = "abcdefghijaaaaaaaaaaaabcdefghij",k = 12) == True
    assert candidate(s = "abcccba",k = 3) == True
    assert candidate(s = "tttttttttt",k = 10) == True
    assert candidate(s = "ccccabcccc",k = 4) == True
    assert candidate(s = "qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq",k = 10) == False
    assert candidate(s = "abcdefghijklmnopqrstuvwxyzzzzzzzzzzzzyxwvutsrqponmlkjihgfedcba",k = 11) == False
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 50) == False
    assert candidate(s = "aabbbaaacc",k = 3) == True
    assert candidate(s = "abcdefghijaaaaaaaaaabcdefghij",k = 10) == True
    assert candidate(s = "mnopqrstuuuuuuvwxyzz",k = 5) == False
    assert candidate(s = "xxxyyyzzz",k = 3) == True
    assert candidate(s = "mnonononononono",k = 7) == False
    assert candidate(s = "abccccd",k = 4) == True
    assert candidate(s = "abcdefghijjjjjjjjjklmnopqrstuvwxyz",k = 8) == False
    assert candidate(s = "aaaaabaaaabaaa",k = 5) == True
    assert candidate(s = "xxyyyyyyz",k = 5) == False
    assert candidate(s = "zzzzzzzzzzz",k = 10) == False
    assert candidate(s = "mnopqrrrpqmn",k = 3) == True
    assert candidate(s = "aabaaaabaa",k = 4) == True
    assert candidate(s = "aabbbaa",k = 3) == True
    assert candidate(s = "aaabbbcccddd",k = 3) == True
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 30) == False
    assert candidate(s = "dddddeeeee",k = 5) == True
    assert candidate(s = "xyzzzyxyzzzy",k = 4) == False
    assert candidate(s = "abcdefghi",k = 1) == True
    assert candidate(s = "mnopqrrrrrrstuv",k = 6) == True
    assert candidate(s = "aaaaabbbbbcccccdddddeeeee",k = 5) == True
    assert candidate(s = "aaaaaaaaaabbbbbbbbbb",k = 10) == True
    assert candidate(s = "abababababababababab",k = 1) == True
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzz",k = 1) == False
    assert candidate(s = "aaaaaabbbaaaaa",k = 3) == True
    assert candidate(s = "xyxyxyxyxyxyxyxyxyxyxy",k = 3) == False
    assert candidate(s = "abcdefghijkllllllmnop",k = 6) == True
    assert candidate(s = "abcdeeeeefghijjjjkl",k = 4) == True
    assert candidate(s = "xyzzzzzzxy",k = 6) == True
    assert candidate(s = "aaaaaabaaaaaabaaa",k = 6) == True
    assert candidate(s = "mnopqrstuvwxyzmnopqrstuvwxyzmnopqrstuvwxyz",k = 26) == False
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzz",k = 10) == False
    assert candidate(s = "abcabcabc",k = 1) == True
    assert candidate(s = "abcdefg",k = 1) == True
    assert candidate(s = "abcabcabcabcabc",k = 1) == True
    assert candidate(s = "mmmmmnnnnn",k = 5) == True
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzzzzzzzzzzzzzzzz",k = 15) == False
    assert candidate(s = "abcabcabcabcabcabc",k = 2) == False
    assert candidate(s = "abcdabcdabcdabcdabcd",k = 4) == False
    assert candidate(s = "aaaaaaaaaabbbbbbbbbc",k = 9) == True
    assert candidate(s = "jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj",k = 30) == False
    assert candidate(s = "mnopqrstu",k = 4) == False
    assert candidate(s = "xyzxyzzzzzzxyz",k = 5) == False
    assert candidate(s = "qqqqqqqqqqqqqqqqqqqq",k = 10) == False
    assert candidate(s = "abacadaeaf",k = 2) == False
    assert candidate(s = "njjjjjjjjjjnj",k = 10) == True
    assert candidate(s = "kjjjjjjjjjjjjjjjkl",k = 13) == False
    assert candidate(s = "mmmmnnnnnnmmmm",k = 6) == True
    assert candidate(s = "aabbccddeeeeffffgggghhhh",k = 4) == True
    assert candidate(s = "abcdefghijjjjjjklmnop",k = 7) == False
    assert candidate(s = "abccccccab",k = 6) == True
    assert candidate(s = "aaaabbbbccccddddeeeeffff",k = 3) == False
    assert candidate(s = "aabbbaaabbbaaabbbaaa",k = 4) == False
    assert candidate(s = "xyzzyxzyxzyxzyxzyx",k = 2) == True
    assert candidate(s = "pppppqqqqqppppp",k = 5) == True
    assert candidate(s = "abcdefghijkllllllmnopqrstuv",k = 6) == True
    assert candidate(s = "abcddeeeffggggghij",k = 4) == False
    assert candidate(s = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz",k = 10) == False
    assert candidate(s = "zzzzzaaaaazzzzz",k = 4) == False
    assert candidate(s = "aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz",k = 2) == True
    assert candidate(s = "aabbbcccddd",k = 3) == True
    assert candidate(s = "ababababababababababababababababab",k = 3) == False
    assert candidate(s = "zzzzzazzzzz",k = 5) == True


# === INVOCATION ===
check(Solution().hasSpecialSubstring)
print("All tests passed")
