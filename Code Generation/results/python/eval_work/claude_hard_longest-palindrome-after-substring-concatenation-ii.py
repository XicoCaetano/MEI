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
        def longest_palindromic_substring(text):
            n = len(text)
            best = {}
            # DP table: dp[i][j] = True if text[i..j] is palindrome
            dp = [[False] * n for _ in range(n)]
            for i in range(n):
                dp[i][i] = True
            for length in range(2, n + 1):
                for i in range(n - length + 1):
                    j = i + length - 1
                    if length == 2:
                        dp[i][j] = (text[i] == text[j])
                    else:
                        dp[i][j] = (text[i] == text[j] and dp[i+1][j-1])
            return dp

        def lcs_length(a, b):
            # Returns DP table where lcs[i][j] = LCS length of a[:i] and b[:j]
            m, n = len(a), len(b)
            dp = [[0] * (n + 1) for _ in range(m + 1)]
            for i in range(1, m + 1):
                for j in range(1, n + 1):
                    if a[i-1] == b[j-1]:
                        dp[i][j] = dp[i-1][j-1] + 1
                    else:
                        dp[i][j] = max(dp[i-1][j], dp[i][j-1])
            return dp

        # We pick substring s[i..j] and t[p..q], concatenate to form s[i..j]+t[p..q]
        # This needs to be a palindrome.
        # 
        # Key insight: s_sub + t_sub is palindrome means it equals its reverse = rev(t_sub) + rev(s_sub)
        # 
        # Strategy: 
        # 1. Try all palindromic substrings of s alone, palindromic substrings of t alone
        # 2. For combined: s_sub + t_sub is palindrome
        #    The combined string of length L is palindrome if combined[k] == combined[L-1-k]
        #
        # Better approach using the structure:
        # If s[i..i+k-1] concatenated with t[j..j+m-1] is a palindrome,
        # consider matching from outside in.
        #
        # Efficient approach: 
        # For each prefix of s and suffix of t that form matching pairs from outside,
        # plus check if the middle part is a palindrome.
        
        n, m = len(s), len(t)
        t_rev = t[::-1]
        
        # dp_s[i][j] = True if s[i..j] is palindrome
        dp_s = longest_palindromic_substring(s)
        # dp_t[i][j] = True if t[i..j] is palindrome  
        dp_t = longest_palindromic_substring(t)
        
        best = 1  # At minimum, single character palindrome exists
        
        # Check pure palindromes in s or t
        for i in range(n):
            for j in range(i, n):
                if dp_s[i][j]:
                    best = max(best, j - i + 1)
        for i in range(m):
            for j in range(i, m):
                if dp_t[i][j]:
                    best = max(best, j - i + 1)
        
        # For combined s[0..i] + t[j..m-1] type structures:
        # We want to find max length where we take a prefix of s and suffix of t
        # such that the concatenation is a palindrome.
        # 
        # Approach: fix how many chars from s prefix match t suffix (from outside in),
        # then check if the remaining middle is a palindrome.
        
        # Use LCS on s and reversed t to find matching prefixes/suffixes
        # lcs_dp[i][j] = length of longest common prefix of s[:i] and t_rev[:j]
        # Actually we need: longest k such that s[0..k-1] == t[m-k..m-1] (reversed)
        
        # For each possible "outer shell" length k (s[0..k-1] matches rev of t[m-k..m-1]):
        # i.e., s[:k] == t[m-k:][::-1]
        # Then the middle can be any palindrome from s[k..n-1] or t[0..m-k-1]
        
        # Precompute: for each i in s, j in t_rev, longest common extension
        # lcp[i][j] = length of longest common prefix of s[i:] and t_rev[j:]
        lcp = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(m - 1, -1, -1):
                if s[i] == t_rev[j]:
                    lcp[i][j] = lcp[i+1][j+1] + 1
                else:
                    lcp[i][j] = 0
        
        # Best palindrome in s[k:] 
        best_s_suffix = [0] * (n + 1)  # best_s_suffix[k] = longest palindrome in s[k:]
        for k in range(n - 1, -1, -1):
            best_s_suffix[k] = best_s_suffix[k+1]
            for j in range(k, n):
                if dp_s[k][j]:
                    best_s_suffix[k] = max(best_s_suffix[k], j - k + 1)
        
        # Best palindrome in t[:q] (t[0..q-1])
        best_t_prefix = [0] * (m + 1)  # best_t_prefix[q] = longest palindrome in t[:q]
        for q in range(1, m + 1):
            best_t_prefix[q] = best_t_prefix[q-1]
            for i in range(q):
                if dp_t[i][q-1]:
                    best_t_prefix[q] = max(best_t_prefix[q], q - i)
        
        # Now try all possible outer shell lengths
        # The outer shell: s[0..k-1] matches reverse of t[m-k..m-1]
        # i.e., s[si] == t_rev[m-1-(m-k)+...] = t_rev[k-1-si+...] hmm let me re-think
        
        # s[0..k-1] concatenated with t[m-k..m-1]: this is palindrome if s[0..k-1] == rev(t[m-k..m-1])
        # rev(t[m-k..m-1]) = t_rev[0..k-1]
        # So we need s[0..k-1] == t_rev[0..k-1], i.e., lcp[0][0] >= k
        
        max_outer = lcp[0][0]  # maximum k where s[:k] == t_rev[:k]
        
        for k in range(0, min(max_outer, n, m) + 1):
            # outer shell of size k on each side: contributes 2*k to length
            # middle from s[k:] best palindrome OR middle from t[:m-k] best palindrome
            mid = max(best_s_suffix[k], best_t_prefix[m - k])
            best = max(best, 2 * k + mid)
        
        return best

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
