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
        n, m = len(s), len(t)
        
        # Helper to find longest palindromic substring in a single string
        def longest_pal_substring(st):
            if not st:
                return 0
            L = len(st)
            # Expand around center approach
            max_len = 1
            for center in range(L):
                # Odd length
                l, r = center, center
                while l >= 0 and r < L and st[l] == st[r]:
                    max_len = max(max_len, r - l + 1)
                    l -= 1
                    r += 1
                # Even length
                l, r = center, center + 1
                while l >= 0 and r < L and st[l] == st[r]:
                    max_len = max(max_len, r - l + 1)
                    l -= 1
                    r += 1
            return max_len
        
        # Precompute longest palindromic substring for all prefixes of s and suffixes of t
        pal_s = [[False] * n for _ in range(n)]
        pal_t = [[False] * m for _ in range(m)]
        
        # Palindromes in s
        for i in range(n):
            pal_s[i][i] = True
        for i in range(n - 1):
            pal_s[i][i + 1] = (s[i] == s[i + 1])
        for length in range(3, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                pal_s[i][j] = (s[i] == s[j] and pal_s[i + 1][j - 1])
        
        # Palindromes in t
        for i in range(m):
            pal_t[i][i] = True
        for i in range(m - 1):
            pal_t[i][i + 1] = (t[i] == t[i + 1])
        for length in range(3, m + 1):
            for i in range(m - length + 1):
                j = i + length - 1
                pal_t[i][j] = (t[i] == t[j] and pal_t[i + 1][j - 1])
        
        # Start with max palindrome from s or t alone
        ans = 1
        for i in range(n):
            for j in range(i, n):
                if pal_s[i][j]:
                    ans = max(ans, j - i + 1)
        for i in range(m):
            for j in range(i, m):
                if pal_t[i][j]:
                    ans = max(ans, j - i + 1)
        
        # Now consider concatenated palindromes
        # We'll check for each possible mid point where s part ends and t part begins
        # Let's try all ways to split into s_sub + t_sub that form a palindrome
        # We can think of trying to expand outwards from some center that spans the join
        
        # Precompute reverse of t for easier matching
        t_rev = t[::-1]
        
        # For each possible split between s and t
        # Consider all pairs (i, j) where i is index in s, j is index in t_rev
        # But more systematically: find longest chain where s[l:r] + t[a:b] is palindrome
        # This is equivalent to: we want s[l..r-1] + t[a..b-1] to be palindrome
        # The palindrome can be centered at the join, or entirely within one string
        
        # Better approach: try all possible centers that cross the boundary
        # For each possible split point, expand outwards checking s part and t part together
        
        # Let's try: for each i from 0 to n (end index in s, exclusive)
        # and for each j from m down to 0 (start index in t, inclusive)
        # we can expand outwards from this "middle point" where s[i-1] and t[j] are adjacent in palindrome
        
        # We'll generate all possible contiguous s_sub + t_sub strings by taking s[l..r] and t[a..b]
        # But we can check palindrome property without constructing the string
        # We'll check if s[l..r] + t[a..b] is palindrome by comparing from both ends
        
        # Let's try all possible lengths and positions
        # For each possible split between s and t (i where s part ends, and j where t part starts)
        # We'll expand outward checking that characters match
        
        # Initialize ans with already found palindromes
        # Now try combinations where we take parts from both strings
        
        # Generate all possible s_sub + t_sub strings by trying all start and end combinations
        # But O(n^2 * m^2) is too slow (10^12)
        
        # We need O(n*m) solution
        
        # Let's try: for each i from 0 to n (end index in s, exclusive)
        # and for each j from 0 to m-1 (start index in t, inclusive)
        # we check if we can form a palindrome by taking s[:i] and t[j:] matched from ends
        # Actually we want consecutive pieces
        
        # Let's try dynamic programming: dp[i][j] = length of longest palindrome starting with s[i] and ending at t[j] 
        # But that's tricky because palindrome can start and end in either string
        
        # Alternative: for each possible center (which could be between characters or at a character)
        # try to expand as far as possible, using s to the left and t to the right or vice versa
        
        # Let's try expanding outward from a point between s and t
        # Consider all ways to choose a substring from s (a..b) and from t (c..d)
        # Combined string is s[a:b+1] + t[c:d+1]
        # We want this to be palindrome
        
        # Try all possible pairs (i, j) where i is start in s, j is end in t
        # And expand outward matching characters
        # We'll consider building palindrome by expanding from the center outward
        
        # For each possible center point (between chars or at a char)
        # We'll try to expand using s for left part and t for right part
        
        # Precompute for s: longest palindrome starting at index i going leftwards
        # Precompute for t: longest palindrome ending at index j going rightwards
        # But we need both directions
        
        # Let's try an exhaustive but efficient approach:
        # For each i in range(n): for each j in range(m): try to match s[i] with t[j] as the outermost characters
        # Then expand inward
        
        # We can think of building palindrome by taking some prefix from s and some suffix from t
        
        for i in range(n):
            for j in range(m):
                if s[i] == t[j]:
                    # Try to expand from this outer pair
                    l, r = i, j
                    # This pair becomes part of a longer palindrome
                    # We'll try to match characters outward: s[l-1] with t[r+1], etc.
                    # But we need contiguous sections: either l moves left in s or moves right? Wait
                    # We want s[a..i] + t[j..b] to be palindrome
                    # So s[a..i] and t[j..b] must be symmetric
                    # That means if we match s[i] with t[j], then next we match s[i-1] with t[j+1] or s[i-1] with s[i-2]? No
                    # For concatenated string, the left part comes entirely from s, right part entirely from t
                    # So the palindrome structure is: s[left..i] + t[j..right] is palindrome
                    # This means: s[left..i] is the mirror of t[j..right]
                    # So we can expand outward from the pair (i, j) by matching s[i-k] with t[j+k]
                    # As long as we don't go out of bounds
                    k = 0
                    # First, try to match as many characters as possible outward
                    total_len = 0
                    # But we can also stop early if we find a mismatch
                    # Let's expand both directions
                    
                    # We'll try all possible extensions
                    # For each possible expansion length L
                    # Check if for all p in 0..L-1, s[i-p] == t[j+p] (if within bounds)
                    # Then this gives a palindrome of length 2*(L) (if we take full s[i-L+1..i] and t[j..j+L-1])
                    # Actually we need to also consider odd length palindromes centered at the join
                    
                    # Also need to consider palindromes where one side is longer than the other (has inner palindrome)
                    
        # This is getting complex. Let's use a simpler O(n*m*min(n,m)) approach:
        # For each i in range(n): for each j in range(m):
        #   Try to form palindrome using s[i:...] and t[...:j] concatenated
        
        # Generate all possible s_sub and t_sub
        # Check if s_sub + t_sub is palindrome
        
        # Store results in a set?
        
        # Let's just implement the O(n*m*min(n,m)) approach which is feasible since n,m<=1000
        # Actually O(n^2 * m^2) is too big, but O(n*m*min(n,m)) might be okay for 1000? 1000^3 = 10^9 too big
        # We need O(n*m)
        
        # Let's try dynamic programming: dp[i][j] = length of longest palindrome where s[i:] and t[:j] match
        # But that's not quite right
        
        # Let's use precomputed LCP (Longest Common Prefix) arrays
        # Precompute for all pairs (i,j) the length of longest common prefix of s[i:] and t_rev[j:]
        lcp_forward = [[0]*(m+1) for _ in range(n+1)]
        for i in range(n-1, -1, -1):
            for j in range(m-1, -1, -1):
                if s[i] == t[j]:
                    lcp_forward[i][j] = 1 + lcp_forward[i+1][j+1]
        
        # Now, for each possible center between s and t
        # Consider a palindrome where left part is from s, right part from t
        # Let's try all possible i where left part ends at i in s, and right part starts at j in t
        # The palindrome could be:
        # Option 1: Even length centered between s[i] and t[j] -> need s[i] == t[j] and then match outward
        # Option 2: Odd length centered at a character (either s[i] or t[j])
        
        # Try even length palindromes cross-boundary:
        for i in range(n):
            for j in range(m):
                if s[i] == t[j]:
                    # This pair is the center of an even-length palindrome
                    # Expand outward: s[i-k] should equal t[j+k] for k=1,2,...
                    # Use lcp_forward to get how many matches
                    matching = lcp_forward[i][j]  # This gives the number of pairs we can match
                    # Each pair gives 2 characters: s[i] and t[j] is one pair, then s[i-1] and t[j+1] is next, etc.
                    # So total length = 2 * matching
                    ans = max(ans, 2 * matching)
        
        # Try odd length palindromes centered at s[i]
        # That means the palindrome is s[i] in middle, then expand left in s and right in t
        for i in range(n):
            # Check if there exists t[j] to start expansion
            # Actually odd length centered at s[i] means s[i] is middle, then left part is s[i-1..a], right part is t[b..j]
            # But we need contiguous sections
            # The palindrome structure: s[i-k..i] + t[j..j+k-1] with condition s[i-k..i-1] reverses to t[j..j+k-1]
            # That is s[i-k..i-1] reversed equals t[j..j+k-1]
            # So we need lcp of s[i-1::-1] with t
            # Let's instead see: if we want odd palindrome centered at s[i], then the right part starts somewhere in t
            # Let's try all possible j indices in t
            # The palindrome is: s[i-k..i] (k characters left, s[i] in middle) + t[j..j+k-1] (k characters right)
            # That means s[i-k..i-1] reversed should equal t[j..j+k-1]
            # So s[i-k..i-1] should equal t_rev[j+k-1..j]
            # This is complicated
        
        # Let's try odd length palindromes centered in t similarly
        # For odd centered at s[i], we need matching prefix of s[len-i-1:len] with suffix of t
        # Alternative approach: try all possible lengths L and see if we can form palindrome
        
        # Finally, handle the case where palindrome is only from s or only from t (already did)
        
        return ans

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
