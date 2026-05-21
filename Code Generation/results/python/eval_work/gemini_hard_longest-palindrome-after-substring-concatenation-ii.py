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
    def longestPalindrome(self, s: str, t: str) -> int:
        """
        To solve this, we can observe that concatenating a substring of s and a substring of t 
        results in a combined string that is effectively a subsequence of the concatenated 
        string (s + t). However, the problem specifies substrings, which means we are looking 
        for the Longest Palindromic Subsequence (LPS) of (s + t) with one critical constraint: 
        the palindrome must contain at least one character from s and at least one character from t.
        """
        combined = s + t
        n = len(combined)
        m = len(s)
        
        # dp[i][j] will store the length of the longest palindromic subsequence in combined[i:j+1]
        dp = [[0] * n for _ in range(n)]
        max_len = 0
        
        # Initialize the DP table for single characters
        for i in range(n):
            dp[i][i] = 1
            
        # Fill the DP table
        for length in range(2, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                if combined[i] == combined[j]:
                    dp[i][j] = dp[i + 1][j - 1] + 2
                    # If the matching characters come from different strings (one from s, one from t)
                    # then this is a valid candidate for our specific problem.
                    if i < m <= j:
                        max_len = max(max_len, dp[i][j])
                else:
                    dp[i][j] = max(dp[i + 1][j], dp[i][j - 1])
                    
        return max_len

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(s = "b",t = "aaaa") == 4
    assert candidate(s = "hello",t = "world") == 3
    assert candidate(s = "aaaa",t = "bbbb") == 4
    assert candidate(s = "abcde",t = "ecdba") == 5
    assert candidate(s = "noon",t = "moon") == 7
    assert candidate(s = "race",t = "care") == 7
    assert candidate(s = "a",t = "a") == 2
    assert candidate(s = "abcd",t = "dcba") == 8
    assert candidate(s = "xyz",t = "zyx") == 6
    assert candidate(s = "abc",t = "def") == 1
    assert candidate(s = "referrefer",t = "referref") == 16
    assert candidate(s = "abccba",t = "abcba") == 7
    assert candidate(s = "abcabc",t = "cbacba") == 12
    assert candidate(s = "mnopqr",t = "rqpomn") == 8
    assert candidate(s = "rotorrotor",t = "rotorrot") == 16
    assert candidate(s = "madam",t = "madammadam") == 15
    assert candidate(s = "aabbaabb",t = "bbaa") == 10
    assert candidate(s = "aaaaabbbbb",t = "bbbbbbaaaa") == 19
    assert candidate(s = "abccba",t = "bccbab") == 11
    assert candidate(s = "aabbcc",t = "ccbbaa") == 12
    assert candidate(s = "abcdef",t = "fedabc") == 6
    assert candidate(s = "xyxyxy",t = "yxyxyx") == 12
    assert candidate(s = "aba",t = "bab") == 5
    assert candidate(s = "abcdefg",t = "gfedcba") == 14
    assert candidate(s = "tatactatta",t = "tatattac") == 11
    assert candidate(s = "madam",t = "madam") == 10
    assert candidate(s = "aabaa",t = "bbabb") == 6
    assert candidate(s = "abcdef",t = "fedcbaghi") == 12
    assert candidate(s = "palindrome",t = "emordnilap") == 20
    assert candidate(s = "xyzaaayzx",t = "zyxxzyxzy") == 9
    assert candidate(s = "abcabcabc",t = "cbacbacba") == 18
    assert candidate(s = "pqr",t = "rqp") == 6
    assert candidate(s = "abcdcba",t = "abcdcba") == 14
    assert candidate(s = "deified",t = "deified") == 14
    assert candidate(s = "abracadabra",t = "abraccadabr") == 8
    assert candidate(s = "longestpalindrome",t = "emordnilapgnol") == 20
    assert candidate(s = "abcdefghijk",t = "kjihgfedcba") == 22
    assert candidate(s = "abacax",t = "xacaba") == 12
    assert candidate(s = "pqrstu",t = "utsrqponmlkjihgfedcba") == 12
    assert candidate(s = "abcdef",t = "gfedcbaa") == 13
    assert candidate(s = "civiccivic",t = "iviciciv") == 11
    assert candidate(s = "aabbccdd",t = "ddeeccbbaa") == 14
    assert candidate(s = "abcxyzdef",t = "fedxyzcba") == 7
    assert candidate(s = "civic",t = "civiccivic") == 15
    assert candidate(s = "banana",t = "nanaba") == 11
    assert candidate(s = "abacdfgdcaba",t = "abacdfgdcaba") == 11
    assert candidate(s = "tattarrattat",t = "tattarrattat") == 24
    assert candidate(s = "level",t = "levvel") == 7
    assert candidate(s = "xxyyyzzz",t = "zzzyyyxx") == 16
    assert candidate(s = "rotorrotor",t = "rotor") == 15
    assert candidate(s = "rotor",t = "rotator") == 7
    assert candidate(s = "abacaxbaca",t = "xacabacaba") == 13
    assert candidate(s = "mnopqrstu",t = "utsrqponmlkjihgfedcbazyxwvut") == 18
    assert candidate(s = "aabbccddeeffgg",t = "ggffeeeeddccbbaa") == 22
    assert candidate(s = "xyzyx",t = "yzyxxy") == 9
    assert candidate(s = "aaaaaa",t = "bbbbbb") == 6
    assert candidate(s = "abcdefg",t = "hijklmn") == 1
    assert candidate(s = "abcdef",t = "fedcbag") == 12
    assert candidate(s = "level",t = "leveleveleveleveleveleveleveleveleveleveleveleveleve") == 55
    assert candidate(s = "abcdabcd",t = "dcbaabcd") == 9
    assert candidate(s = "abcdeedcba",t = "fghijklkjihgf") == 13
    assert candidate(s = "aaaabb",t = "aabbaa") == 10
    assert candidate(s = "civic",t = "civic") == 10
    assert candidate(s = "level",t = "levevl") == 8
    assert candidate(s = "racecar",t = "madam") == 7
    assert candidate(s = "deifieddeified",t = "deifiededeif") == 21
    assert candidate(s = "noonhighnoon",t = "deifiedlevel") == 7
    assert candidate(s = "abracadabra",t = "aracabradab") == 7
    assert candidate(s = "level",t = "deified") == 7
    assert candidate(s = "mirror",t = "rimmom") == 9
    assert candidate(s = "abcdedcba",t = "zyxwxyzyx") == 9
    assert candidate(s = "pneumonoultramicroscopicsilicovolcanoconiosis",t = "osivicnoclovosicrepimicroscopultramaounep") == 11
    assert candidate(s = "xyzzyx",t = "abczyzyxcba") == 7
    assert candidate(s = "abcxyzyxcba",t = "xyzzyx") == 11
    assert candidate(s = "abcabcabc",t = "abcabcabc") == 3
    assert candidate(s = "mississippi",t = "ppissimms") == 13
    assert candidate(s = "abacaxaba",t = "abacaxaba") == 7
    assert candidate(s = "hello",t = "olleh") == 10
    assert candidate(s = "noonhighnoon",t = "noonlownoon") == 9
    assert candidate(s = "abaccadda",t = "addacca") == 14
    assert candidate(s = "refer",t = "repaper") == 7
    assert candidate(s = "mississippi",t = "ippississimm") == 22
    assert candidate(s = "abacaba",t = "bdcabdc") == 9
    assert candidate(s = "mississippi",t = "noon") == 7
    assert candidate(s = "noon",t = "noonnoonnoonnoon") == 20
    assert candidate(s = "abracadabra",t = "abacabadabrac") == 11
    assert candidate(s = "abcd",t = "abcdabcd") == 3
    assert candidate(s = "abc",t = "mnopqr") == 1
    assert candidate(s = "abccba",t = "xyzyx") == 6
    assert candidate(s = "zzzzzz",t = "zzzzzz") == 12
    assert candidate(s = "amanaplanacanalpanama",t = "amanaP lanac a nalp a namA") == 21
    assert candidate(s = "noonnoon",t = "moonmoon") == 8
    assert candidate(s = "noonhighnoon",t = "noon") == 9
    assert candidate(s = "xyzz",t = "zzxy") == 4
    assert candidate(s = "racecar",t = "civic") == 7
    assert candidate(s = "mnopqr",t = "rqponm") == 12
    assert candidate(s = "levellevellevel",t = "levevlevevlevevl") == 18
    assert candidate(s = "mammam",t = "mammam") == 12
    assert candidate(s = "kayak",t = "yakayk") == 7
    assert candidate(s = "radar",t = "radar") == 10
    assert candidate(s = "neveroddoreven",t = "levelmadamrotor") == 14
    assert candidate(s = "madam",t = "refer") == 5
    assert candidate(s = "hello",t = "ollehworld") == 10
    assert candidate(s = "xyzuvw",t = "vwxyz") == 3
    assert candidate(s = "zzzzzzzzzz",t = "zzzzzzzzzz") == 20
    assert candidate(s = "zzzzz",t = "zzzz") == 9
    assert candidate(s = "banana",t = "ananab") == 12
    assert candidate(s = "abacabadabacaba",t = "abacabadabacaba") == 30
    assert candidate(s = "rotor",t = "rotorrotorrotor") == 20
    assert candidate(s = "aabbccddeeff",t = "ffeeddccbbaa") == 24
    assert candidate(s = "abracadabra",t = "arbadacarba") == 22
    assert candidate(s = "aaaabbbb",t = "bbbbcccc") == 8
    assert candidate(s = "abacdfgdcaba",t = "abacdgfdcaba") == 24
    assert candidate(s = "repaper",t = "repaper") == 14
    assert candidate(s = "aabbccddeeffgg",t = "ggffeeddcbaabbccddeeffgg") == 18
    assert candidate(s = "racecar",t = "carrear") == 7
    assert candidate(s = "abcabcabcabc",t = "cbacbacbacba") == 24
    assert candidate(s = "racecar",t = "racecar") == 14
    assert candidate(s = "aabbccdd",t = "dccbbaaa") == 15
    assert candidate(s = "abcdefgfedcba",t = "ghijklimno") == 13
    assert candidate(s = "aabbccddeeaabbccddeeaabb",t = "ddeeaabbccddeeaabb") == 6
    assert candidate(s = "rotor",t = "rotor") == 10


# === INVOCATION ===
check(Solution().longestPalindrome)
print("All tests passed")
