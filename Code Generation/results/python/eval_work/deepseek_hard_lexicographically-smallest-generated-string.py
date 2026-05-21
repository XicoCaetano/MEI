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
    def generateString(self, str1: str, str2: str) -> str:
        n = len(str1)
        m = len(str2)
        
        # Create constraints: for each position i, we need to ensure str2 matches or doesn't match
        # We'll build a graph where each node represents a position in the word (0 to n+m-2)
        # and we'll store constraints as equalities or inequalities between characters
        
        # First, handle the case when n == 1
        if n == 1:
            if str1[0] == 'T':
                return str2
            else:
                # Find smallest character not equal to str2[0] at position 0
                result = []
                # We need a string of length m, with word[0..m-1] != str2
                # Try to make it lexicographically smallest
                for i in range(m):
                    # At position i, try to put a character different from str2[i] if possible
                    # But we need to make the whole string as small as possible
                    # Actually simpler: try to find smallest string of length m that is not equal to str2
                    result.append('a')
                result_str = ''.join(result)
                if result_str == str2:
                    # If it equals str2, change last character to next smallest
                    result = list(result_str)
                    for j in range(m-1, -1, -1):
                        if result[j] < 'z':
                            result[j] = chr(ord(result[j]) + 1)
                            return ''.join(result)
                    return ''
                return result_str
        
        # For n > 1, we need to construct the string
        # The word length is L = n + m - 1
        L = n + m - 1
        word = [''] * L
        
        # First, handle all 'T' constraints
        # They force the string to have str2 at those positions
        forced_chars = [None] * L  # None means not forced, otherwise a character
        for i in range(n):
            if str1[i] == 'T':
                # word[i:i+m] must equal str2
                for j in range(m):
                    if forced_chars[i + j] is not None and forced_chars[i + j] != str2[j]:
                        return ""  # Conflict
                    forced_chars[i + j] = str2[j]
        
        # Now fill in forced characters
        for i in range(L):
            if forced_chars[i] is not None:
                word[i] = forced_chars[i]
        
        # Now handle 'F' constraints
        # For each 'F', we need word[i:i+m] != str2
        # This means there must be at least one position j in [0,m-1] where 
        # either word[i+j] is already set to a character different from str2[j],
        # or we can set it to a character different from str2[j]
        
        # For each position, we need to find the earliest character to put
        # to make the string lexicographically smallest
        
        # First pass: fill as many 'a's as possible
        for i in range(L):
            if word[i] == '':
                word[i] = 'a'
        
        # Now check all constraints and adjust if needed
        # For 'F', if the current word[i:i+m] == str2, we need to change
        # at least one character in that segment
        
        # We need to process positions from left to right to ensure lexicographically smallest
        for i in range(n):
            if str1[i] == 'F':
                # Check if word[i:i+m] == str2
                matches = True
                for j in range(m):
                    if word[i + j] != str2[j]:
                        matches = False
                        break
                
                if matches:
                    # Need to change at the rightmost position possible to get smallest lex order
                    # Try to increase the last character to next character
                    changed = False
                    for j in range(m-1, -1, -1):
                        pos = i + j
                        # Try to increase this character if possible
                        if word[pos] < 'z':
                            word[pos] = chr(ord(word[pos]) + 1)
                            changed = True
                            # Make all following positions 'a' again
                            for k in range(pos + 1, L):
                                word[k] = 'a'
                            break
                    if not changed:
                        return ""  # Cannot change any character
        
        # Second pass: check all constraints again
        # Also need to consider indirect conflicts: changing one position might
        # violate other constraints
        
        # We need to be more thorough: treat as a graph of constraints
        # Let's use backtracking for correctness since n<=10^4 is large but m<=500
        # Actually, we can solve greedily from left to right
        
        # Better approach: process from left to right, making decisions
        # Reset and try greedy with backtracking if needed
        return self.greedy_solve(str1, str2, n, m, L)
    
    def greedy_solve(self, str1: str, str2: str, n: int, m: int, L: int) -> str:
        word = [''] * L
        
        # First, handle forced characters from 'T'
        forced = [None] * L
        for i in range(n):
            if str1[i] == 'T':
                for j in range(m):
                    if forced[i+j] is not None and forced[i+j] != str2[j]:
                        return ""
                    forced[i+j] = str2[j]
        
        # Fill forced characters
        for i in range(L):
            if forced[i] is not None:
                word[i] = forced[i]
        
        # Now fill remaining positions with 'a'
        for i in range(L):
            if word[i] == '':
                word[i] = 'a'
        
        # We'll use a list of constraints for 'F' positions that currently match
        # and fix them from right to left
        
        # Process multiple times until stable
        changed = True
        while changed:
            changed = False
            # Process from left to right
            for i in range(n):
                if str1[i] == 'F':
                    # Check if this segment equals str2
                    matches = True
                    match_pos = -1
                    for j in range(m):
                        if word[i+j] != str2[j]:
                            matches = False
                            break
                    
                    if matches:
                        # Need to change at some position in [i, i+m-1]
                        # Choose the rightmost position that can be increased
                        for j in range(m-1, -1, -1):
                            pos = i + j
                            if word[pos] < 'z' and (forced[pos] is None or word[pos] != forced[pos]):
                                # This position is not forced to be something specific
                                # Increase it
                                word[pos] = chr(ord(word[pos]) + 1)
                                # Reset all positions to the right to 'a'
                                for k in range(pos + 1, L):
                                    if forced[k] is None:
                                        word[k] = 'a'
                                changed = True
                                break
                        if not changed:
                            return ""  # Cannot fix this constraint
        
        # Final check all constraints
        for i in range(n):
            segment = ''.join(word[i:i+m])
            if str1[i] == 'T':
                if segment != str2:
                    return ""
            else:  # 'F'
                if segment == str2:
                    return ""
        
        return ''.join(word)

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(str1 = "FF",str2 = "z") == "aa"
    assert candidate(str1 = "FT",str2 = "c") == "ac"
    assert candidate(str1 = "FT",str2 = "yz") == "ayz"
    assert candidate(str1 = "TTT",str2 = "aaa") == "aaaaa"
    assert candidate(str1 = "TTT",str2 = "xyz") == ""
    assert candidate(str1 = "TF",str2 = "ab") == "aba"
    assert candidate(str1 = "FFF",str2 = "a") == "bbb"
    assert candidate(str1 = "TFTF",str2 = "abc") == ""
    assert candidate(str1 = "TT",str2 = "a") == "aa"
    assert candidate(str1 = "F",str2 = "fgh") == "aaa"
    assert candidate(str1 = "FFF",str2 = "xyz") == "aaaaa"
    assert candidate(str1 = "TTFT",str2 = "ij") == ""
    assert candidate(str1 = "F",str2 = "a") == "b"
    assert candidate(str1 = "FT",str2 = "a") == "ba"
    assert candidate(str1 = "TF",str2 = "a") == "ab"
    assert candidate(str1 = "FTF",str2 = "aaa") == "baaab"
    assert candidate(str1 = "FFT",str2 = "aaa") == "abaaa"
    assert candidate(str1 = "FF",str2 = "aa") == "aba"
    assert candidate(str1 = "TF",str2 = "xy") == "xya"
    assert candidate(str1 = "T",str2 = "z") == "z"
    assert candidate(str1 = "T",str2 = "a") == "a"
    assert candidate(str1 = "TFT",str2 = "aaa") == ""
    assert candidate(str1 = "FT",str2 = "ab") == "aab"
    assert candidate(str1 = "TTT",str2 = "de") == ""
    assert candidate(str1 = "FFF",str2 = "aaa") == "aabaa"
    assert candidate(str1 = "TF",str2 = "b") == "ba"
    assert candidate(str1 = "TT",str2 = "ab") == ""
    assert candidate(str1 = "T",str2 = "de") == "de"
    assert candidate(str1 = "TFTF",str2 = "ab") == "ababa"
    assert candidate(str1 = "TF",str2 = "aa") == "aab"
    assert candidate(str1 = "FT",str2 = "aa") == "baa"
    assert candidate(str1 = "TFF",str2 = "aaa") == "aaaba"
    assert candidate(str1 = "FF",str2 = "xy") == "aaa"
    assert candidate(str1 = "F",str2 = "d") == "a"
    assert candidate(str1 = "TT",str2 = "aa") == "aaa"
    assert candidate(str1 = "F",str2 = "abc") == "aaa"
    assert candidate(str1 = "TT",str2 = "mn") == ""
    assert candidate(str1 = "T",str2 = "abc") == "abc"
    assert candidate(str1 = "TFFFTTFT",str2 = "dddd") == ""
    assert candidate(str1 = "TTT",str2 = "mnopqrstu") == ""
    assert candidate(str1 = "F",str2 = "z") == "a"
    assert candidate(str1 = "TTFFTFTFF",str2 = "generated") == ""
    assert candidate(str1 = "TFTFTFTFT",str2 = "xyz") == ""
    assert candidate(str1 = "TFTFTFT",str2 = "uv") == "uvuvuvuv"
    assert candidate(str1 = "FTFTFTFT",str2 = "mnop") == ""
    assert candidate(str1 = "FTFTFT",str2 = "qrstuvwx") == ""
    assert candidate(str1 = "FFFFFFFFFT",str2 = "xyz") == "aaaaaaaaaxyz"
    assert candidate(str1 = "TTTTTTTTTTTT",str2 = "qrstuvwx") == ""
    assert candidate(str1 = "FTFTFTFTFTFTFTFTFTFTFT",str2 = "abcdef") == ""
    assert candidate(str1 = "TFTFTF",str2 = "ijklmnop") == ""
    assert candidate(str1 = "TFTFTFTFTFT",str2 = "stuvwx") == ""
    assert candidate(str1 = "TFTFTFTFTFT",str2 = "xyz") == ""
    assert candidate(str1 = "TTTFTFTFT",str2 = "test") == ""
    assert candidate(str1 = "FFFFFFFFFFFFFFFF",str2 = "abc") == "aaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "TFTFTFTFTFT",str2 = "yz") == "yzyzyzyzyzyz"
    assert candidate(str1 = "FTTTFFTTTTFFFF",str2 = "sample") == ""
    assert candidate(str1 = "FTFT",str2 = "mnopq") == ""
    assert candidate(str1 = "TFTFTFTFTF",str2 = "test") == ""
    assert candidate(str1 = "TTFTFT",str2 = "zzz") == ""
    assert candidate(str1 = "TTTTFFF",str2 = "efgh") == ""
    assert candidate(str1 = "TTTFTFFTFF",str2 = "ghijkl") == ""
    assert candidate(str1 = "FTTFT",str2 = "xyzw") == ""
    assert candidate(str1 = "FFFFTTT",str2 = "ijkl") == ""
    assert candidate(str1 = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",str2 = "uvw") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "FFTTFFTF",str2 = "eeee") == ""
    assert candidate(str1 = "FFFF",str2 = "wxyz") == "aaaaaaa"
    assert candidate(str1 = "TFTFTFTFT",str2 = "xy") == "xyxyxyxyxy"
    assert candidate(str1 = "TFFFT",str2 = "abc") == "abcaabc"
    assert candidate(str1 = "TFTFT",str2 = "abcdefghi") == ""
    assert candidate(str1 = "TTFT",str2 = "abc") == ""
    assert candidate(str1 = "FFTFTFFT",str2 = "hhhh") == ""
    assert candidate(str1 = "TFTFTFTFTFTFTFTFTF",str2 = "complex") == ""
    assert candidate(str1 = "FTFTTFTF",str2 = "cccc") == ""
    assert candidate(str1 = "TFTFTFT",str2 = "mnop") == ""
    assert candidate(str1 = "FTFTFT",str2 = "mnop") == ""
    assert candidate(str1 = "TFTFTFTFTFT",str2 = "abcdefg") == ""
    assert candidate(str1 = "TTTTTTTTTTTT",str2 = "z") == "zzzzzzzzzzzz"
    assert candidate(str1 = "FFFFFFFFFFFF",str2 = "a") == "bbbbbbbbbbbb"
    assert candidate(str1 = "TTTFTTTT",str2 = "qrst") == ""
    assert candidate(str1 = "FFFFFFFFFT",str2 = "abcdef") == "aaaaaaaaaabcdef"
    assert candidate(str1 = "FTFTFT",str2 = "aaa") == ""
    assert candidate(str1 = "TTTTTTTTTT",str2 = "ghijkl") == ""
    assert candidate(str1 = "TTTTTTTTTT",str2 = "opqrst") == ""
    assert candidate(str1 = "FTFTFT",str2 = "xyz") == ""
    assert candidate(str1 = "TTFF",str2 = "qrstuvwx") == ""
    assert candidate(str1 = "TFTFT",str2 = "abc") == ""
    assert candidate(str1 = "TFTFTFTFTFTFT",str2 = "mnopqr") == ""
    assert candidate(str1 = "FF",str2 = "wx") == "aaa"
    assert candidate(str1 = "TTFTTFFFTTTFTFT",str2 = "qrstuvw") == ""
    assert candidate(str1 = "TTTFTTTFTTT",str2 = "mnopqrstuvw") == ""
    assert candidate(str1 = "FTFTFTFTFT",str2 = "xyz") == ""
    assert candidate(str1 = "FFFF",str2 = "ghijkl") == "aaaaaaaaa"
    assert candidate(str1 = "FFTFTT",str2 = "world") == ""
    assert candidate(str1 = "FTFTFTFTFT",str2 = "abc") == ""
    assert candidate(str1 = "TTFT",str2 = "uvw") == ""
    assert candidate(str1 = "TTFTFFTFTFFTFT",str2 = "example") == ""
    assert candidate(str1 = "FFFFFFFF",str2 = "abc") == "aaaaaaaaaa"
    assert candidate(str1 = "TFFT",str2 = "lmnopqrstu") == ""
    assert candidate(str1 = "FTFTFT",str2 = "def") == ""
    assert candidate(str1 = "FFFFFF",str2 = "abcd") == "aaaaaaaaa"
    assert candidate(str1 = "TFTFTFTFTFTFT",str2 = "abcdef") == ""
    assert candidate(str1 = "TFFT",str2 = "vwxyz") == ""
    assert candidate(str1 = "TTFTFTFTT",str2 = "world") == ""
    assert candidate(str1 = "TFFFFFFFF",str2 = "wxyz") == "wxyzaaaaaaaa"
    assert candidate(str1 = "TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT",str2 = "mnop") == ""
    assert candidate(str1 = "TFT",str2 = "abcdef") == ""
    assert candidate(str1 = "FTTFTFFT",str2 = "gggg") == ""
    assert candidate(str1 = "TFFTFT",str2 = "abcd") == ""
    assert candidate(str1 = "TTFTFTFFT",str2 = "lexicographically") == ""
    assert candidate(str1 = "FTFTFTFTT",str2 = "stuv") == ""
    assert candidate(str1 = "FFTFFT",str2 = "abc") == "aaabcabc"
    assert candidate(str1 = "TTTTTTT",str2 = "abcd") == ""
    assert candidate(str1 = "TF",str2 = "yz") == "yza"
    assert candidate(str1 = "TTFT",str2 = "jklmno") == ""
    assert candidate(str1 = "TFTFTFTFTFT",str2 = "mnopqrstuvw") == ""
    assert candidate(str1 = "TFTF",str2 = "mnop") == ""
    assert candidate(str1 = "TTTTTTTT",str2 = "a") == "aaaaaaaa"
    assert candidate(str1 = "TFTFTF",str2 = "mnopqr") == ""
    assert candidate(str1 = "TTT",str2 = "k") == "kkk"
    assert candidate(str1 = "TFFTFF",str2 = "bcb") == "bcbbcbaa"
    assert candidate(str1 = "TFTFTFTFTFTFTFTFTFT",str2 = "a") == "abababababababababa"
    assert candidate(str1 = "FTFTFTFTFT",str2 = "uvw") == ""
    assert candidate(str1 = "FTFTFT",str2 = "stuvwx") == ""
    assert candidate(str1 = "FFTT",str2 = "abcd") == ""
    assert candidate(str1 = "TTTTTTTTTTTTTTTTTT",str2 = "solution") == ""
    assert candidate(str1 = "FTFTFTFFT",str2 = "example") == ""
    assert candidate(str1 = "TFTFT",str2 = "efghij") == ""
    assert candidate(str1 = "TFTFTFT",str2 = "wxyz") == ""
    assert candidate(str1 = "TTTTTTTTT",str2 = "abcdefghi") == ""
    assert candidate(str1 = "FTF",str2 = "abcd") == "aabcda"
    assert candidate(str1 = "TFTFTFTFTFTFTF",str2 = "abcd") == ""
    assert candidate(str1 = "TFTFTFTFTF",str2 = "uvw") == ""
    assert candidate(str1 = "FTF",str2 = "zz") == "azza"
    assert candidate(str1 = "TFT",str2 = "efghijkl") == ""
    assert candidate(str1 = "TTTTTTTTTT",str2 = "yzab") == ""
    assert candidate(str1 = "TTTTTTTTF",str2 = "mnopqr") == ""
    assert candidate(str1 = "TFT",str2 = "def") == ""
    assert candidate(str1 = "TFTFTF",str2 = "xyz") == ""
    assert candidate(str1 = "TTTTTT",str2 = "aaa") == "aaaaaaaa"
    assert candidate(str1 = "FTFT",str2 = "pqrstu") == ""
    assert candidate(str1 = "FTFTFTFTFT",str2 = "mnopqrstuvwx") == ""
    assert candidate(str1 = "FFFFFFFF",str2 = "abcd") == "aaaaaaaaaaa"
    assert candidate(str1 = "TTFFTTFFTT",str2 = "abcdefgh") == ""
    assert candidate(str1 = "FTFTFTFTFTFTFTFTFTFTFTFTFTFTFTFT",str2 = "defghijklm") == ""
    assert candidate(str1 = "TFTFTF",str2 = "abcdefgh") == ""
    assert candidate(str1 = "TF",str2 = "zzz") == "zzza"
    assert candidate(str1 = "FTTFFTFF",str2 = "uvw") == ""
    assert candidate(str1 = "FFFFFFFFF",str2 = "aaaa") == "aaabaaabaaab"
    assert candidate(str1 = "TFTFT",str2 = "pqrstuvwx") == ""
    assert candidate(str1 = "TFTFTFTFTFTFTFTFTFT",str2 = "abcdefghijklmnopqrstuvwxyz") == ""
    assert candidate(str1 = "FFTTTFFFFTTFF",str2 = "abcdefghi") == ""
    assert candidate(str1 = "FTFTFTFT",str2 = "efghijkl") == ""
    assert candidate(str1 = "TTFFFFTT",str2 = "xyz") == ""
    assert candidate(str1 = "FT",str2 = "mnopqr") == "amnopqr"
    assert candidate(str1 = "FF",str2 = "abcdef") == "aaaaaaa"
    assert candidate(str1 = "TTT",str2 = "yz") == ""
    assert candidate(str1 = "TTTT",str2 = "aaa") == "aaaaaa"
    assert candidate(str1 = "FTFTFTFTFTFT",str2 = "yz") == "ayzyzyzyzyzyz"
    assert candidate(str1 = "TFFT",str2 = "rstuv") == ""
    assert candidate(str1 = "FFTFTFTFF",str2 = "mnop") == ""
    assert candidate(str1 = "TFT",str2 = "abcd") == ""
    assert candidate(str1 = "FFFFFFFFF",str2 = "abcde") == "aaaaaaaaaaaaa"
    assert candidate(str1 = "FFTFFT",str2 = "xyz") == "aaxyzxyz"
    assert candidate(str1 = "TFTFT",str2 = "abcde") == ""
    assert candidate(str1 = "FFFFFFFF",str2 = "abcdefgh") == "aaaaaaaaaaaaaaa"
    assert candidate(str1 = "TTTFFFF",str2 = "aaaa") == "aaaaaabaaa"
    assert candidate(str1 = "TFTFTF",str2 = "abc") == ""
    assert candidate(str1 = "FTFTFTFT",str2 = "a") == "babababa"
    assert candidate(str1 = "TTTTTTTTTTTTTTTT",str2 = "xyz") == ""
    assert candidate(str1 = "TFTFFT",str2 = "xyz") == ""
    assert candidate(str1 = "FFFFFFFFFT",str2 = "qrstuv") == "aaaaaaaaaqrstuv"
    assert candidate(str1 = "TTTTTTTT",str2 = "aaaa") == "aaaaaaaaaaa"
    assert candidate(str1 = "FFFFFFFFFFFFFFFF",str2 = "hijklmnop") == "aaaaaaaaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "TFTFFTFTFTFFT",str2 = "xyzxyz") == ""
    assert candidate(str1 = "TTTTTTTTT",str2 = "mnopqrst") == ""
    assert candidate(str1 = "FFFTTFFT",str2 = "qrstu") == ""
    assert candidate(str1 = "TTTTT",str2 = "ab") == ""
    assert candidate(str1 = "FFFF",str2 = "abcdefgh") == "aaaaaaaaaaa"
    assert candidate(str1 = "TFTFTFTFTFTFTFT",str2 = "abcdefg") == ""
    assert candidate(str1 = "FFFFFFFFFT",str2 = "cdefgh") == "aaaaaaaaacdefgh"
    assert candidate(str1 = "FFFFFFFFFF",str2 = "zyxwvut") == "aaaaaaaaaaaaaaaa"
    assert candidate(str1 = "TFFTFTF",str2 = "abcd") == ""
    assert candidate(str1 = "TTTTF",str2 = "mnop") == ""
    assert candidate(str1 = "FTFT",str2 = "abcdefghijk") == ""
    assert candidate(str1 = "TFTFTFTFT",str2 = "abcde") == ""
    assert candidate(str1 = "FFTT",str2 = "yz") == ""
    assert candidate(str1 = "TFFTTF",str2 = "abc") == ""
    assert candidate(str1 = "TTFFTTFFT",str2 = "solution") == ""
    assert candidate(str1 = "FFTTFF",str2 = "xyz") == ""
    assert candidate(str1 = "FTFTF",str2 = "qrst") == ""
    assert candidate(str1 = "FFTFTFTFT",str2 = "yz") == "aayzyzyzyz"
    assert candidate(str1 = "TTFFTT",str2 = "abc") == ""
    assert candidate(str1 = "FFFFFFFFFFFFFFFFFFFFFFFF",str2 = "mnopqrstuvwxyz") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "TTTTF",str2 = "abcde") == ""
    assert candidate(str1 = "FTFT",str2 = "zz") == ""
    assert candidate(str1 = "TFTFTFTFTFT",str2 = "abcdabcd") == ""
    assert candidate(str1 = "FTTFFTFTT",str2 = "possible") == ""
    assert candidate(str1 = "TFFFTF",str2 = "mnop") == "mnopmnopa"
    assert candidate(str1 = "FFTFFTTFT",str2 = "output") == ""
    assert candidate(str1 = "TTT",str2 = "qrstuv") == ""
    assert candidate(str1 = "TTF",str2 = "abcd") == ""
    assert candidate(str1 = "FFFFFFFFFFFF",str2 = "abcde") == "aaaaaaaaaaaaaaaa"
    assert candidate(str1 = "FFFFFFFFTT",str2 = "abcd") == ""
    assert candidate(str1 = "TTFF",str2 = "yz") == ""
    assert candidate(str1 = "FFFFFFFF",str2 = "zz") == "aaaaaaaaa"
    assert candidate(str1 = "FFFF",str2 = "xyz") == "aaaaaa"
    assert candidate(str1 = "TTFT",str2 = "yz") == ""
    assert candidate(str1 = "FFFF",str2 = "zzz") == "aaaaaa"
    assert candidate(str1 = "FFFFFF",str2 = "zzz") == "aaaaaaaa"
    assert candidate(str1 = "FFTFTFTFT",str2 = "complex") == ""
    assert candidate(str1 = "TT",str2 = "qrstuv") == ""
    assert candidate(str1 = "FFFFFFFF",str2 = "z") == "aaaaaaaa"
    assert candidate(str1 = "FTF",str2 = "mnop") == "amnopa"
    assert candidate(str1 = "FFTFFT",str2 = "qrst") == ""
    assert candidate(str1 = "TFT",str2 = "efghijklmno") == ""
    assert candidate(str1 = "FTFTFTFT",str2 = "pqrstuvwx") == ""
    assert candidate(str1 = "FFTFFTFFT",str2 = "string") == ""
    assert candidate(str1 = "FTFTFTFT",str2 = "ab") == "aabababab"
    assert candidate(str1 = "FFTFTF",str2 = "bcd") == ""
    assert candidate(str1 = "FTFTFTFT",str2 = "qrst") == ""
    assert candidate(str1 = "TFTFTF",str2 = "uvw") == ""
    assert candidate(str1 = "FTT",str2 = "efghijkl") == ""
    assert candidate(str1 = "TFTFTFTFTFTFTFTFT",str2 = "abc") == ""
    assert candidate(str1 = "TFFFFT",str2 = "def") == "defaadef"
    assert candidate(str1 = "TFTTFF",str2 = "hello") == ""
    assert candidate(str1 = "FFFFFFFFFFFFFFFF",str2 = "challenge") == "aaaaaaaaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "TFTFFTFF",str2 = "ffff") == ""
    assert candidate(str1 = "FTFTFT",str2 = "zzz") == ""
    assert candidate(str1 = "TTTTTTTT",str2 = "abcdefghijk") == ""
    assert candidate(str1 = "FTFTFTFTFTFT",str2 = "abcd") == ""
    assert candidate(str1 = "FFTFT",str2 = "wxyz") == ""
    assert candidate(str1 = "FTFTFFTTT",str2 = "smaller") == ""
    assert candidate(str1 = "FTFTFTFTFTFTFTFT",str2 = "mnopqr") == ""
    assert candidate(str1 = "TTTTTTTTTT",str2 = "mnop") == ""
    assert candidate(str1 = "TTTFTF",str2 = "abc") == ""
    assert candidate(str1 = "FTFTFTFTFT",str2 = "ab") == "aababababab"
    assert candidate(str1 = "TFTFTFTFTFT",str2 = "ijklmn") == ""
    assert candidate(str1 = "FFTTFFTT",str2 = "stuv") == ""
    assert candidate(str1 = "FTFTFTFTFT",str2 = "jklmnop") == ""
    assert candidate(str1 = "FTFTFFTTT",str2 = "input") == ""
    assert candidate(str1 = "FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF",str2 = "zzzzzzzzzz") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "FFFFFFFFFT",str2 = "mnopqr") == "aaaaaaaaamnopqr"
    assert candidate(str1 = "FFFFFFT",str2 = "bbbb") == "aaaaaabbbb"
    assert candidate(str1 = "FTTFFTFTF",str2 = "hello") == ""
    assert candidate(str1 = "FFTFTFT",str2 = "qrst") == ""
    assert candidate(str1 = "FFFFFFFF",str2 = "lmnop") == "aaaaaaaaaaaa"
    assert candidate(str1 = "FFFFFFFFFFFFFFFF",str2 = "zzzzzzzzzzzzzzzzzzzzzzzzzzzz") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "TFTFTFTFT",str2 = "stuv") == ""
    assert candidate(str1 = "FFTFFTFFT",str2 = "qrst") == ""
    assert candidate(str1 = "FFFFFFFF",str2 = "mnopqr") == "aaaaaaaaaaaaa"
    assert candidate(str1 = "TTFFFFTT",str2 = "uvwxy") == ""
    assert candidate(str1 = "FFFF",str2 = "vwxyz") == "aaaaaaaa"
    assert candidate(str1 = "TT",str2 = "abcdef") == ""
    assert candidate(str1 = "TTFFTTF",str2 = "mnop") == ""
    assert candidate(str1 = "FFFF",str2 = "abcdefghijklmno") == "aaaaaaaaaaaaaaaaaa"
    assert candidate(str1 = "TTFFTT",str2 = "mnop") == ""
    assert candidate(str1 = "TTT",str2 = "abc") == ""
    assert candidate(str1 = "TTTTTTTFT",str2 = "stuvwx") == ""
    assert candidate(str1 = "FFFFFFFFFT",str2 = "uvwxyz") == "aaaaaaaaauvwxyz"
    assert candidate(str1 = "TFTFTFTFTFTFT",str2 = "abcdabcd") == ""
    assert candidate(str1 = "FFTTF",str2 = "xyz") == ""
    assert candidate(str1 = "FFFFFFFFF",str2 = "a") == "bbbbbbbbb"
    assert candidate(str1 = "TFTFT",str2 = "ijkl") == ""
    assert candidate(str1 = "TFFTFT",str2 = "bca") == ""
    assert candidate(str1 = "FTFTFT",str2 = "ijklmnop") == ""
    assert candidate(str1 = "FFFFFT",str2 = "zyxwvut") == "aaaaazyxwvut"


# === INVOCATION ===
check(Solution().generateString)
print("All tests passed")
