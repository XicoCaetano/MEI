# === IMPORTS GERAIS (do dataset) ===
import heapq
import itertools
from sortedcontainers import SortedList
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
from collections import defaultdict

class TrieNode:
    def __init__(self):
        self.children = {}
        self.count = 0

class Trie:
    def __init__(self):
        self.root = TrieNode()
    
    def insert(self, word, delta=1):
        node = self.root
        node.count += delta
        for ch in word:
            if ch not in node.children:
                node.children[ch] = TrieNode()
            node = node.children[ch]
            node.count += delta
    
    def longest_prefix_with_k(self, k):
        node = self.root
        if node.count < k:
            return 0
        length = 0
        while True:
            next_node = None
            for ch, child in node.children.items():
                if child.count >= k:
                    next_node = child
                    break
            if next_node is None:
                break
            length += 1
            node = next_node
        return length

class Solution:
    def longestCommonPrefix(self, words: List[str], k: int) -> List[int]:
        n = len(words)
        
        trie = Trie()
        for word in words:
            trie.insert(word, 1)
        
        answer = []
        for i in range(n):
            trie.insert(words[i], -1)
            if n - 1 < k:
                answer.append(0)
            else:
                answer.append(trie.longest_prefix_with_k(k))
            trie.insert(words[i], 1)
        
        return answer

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(words = ['banana', 'band', 'bend', 'bendy'],k = 3) == [1, 1, 1, 1]
    assert candidate(words = ['abcd', 'abce', 'abcf', 'abcg'],k = 2) == [3, 3, 3, 3]
    assert candidate(words = ['apple', 'application', 'aptitude', 'appetite'],k = 3) == [2, 2, 3, 2]
    assert candidate(words = ['aaa', 'aa', 'a'],k = 2) == [1, 1, 2]
    assert candidate(words = ['aaaa', 'aaa', 'aa', 'a'],k = 2) == [2, 2, 3, 3]
    assert candidate(words = ['jump', 'run', 'run', 'jump', 'run'],k = 2) == [3, 4, 4, 3, 4]
    assert candidate(words = ['apple', 'application', 'appetite'],k = 2) == [3, 3, 4]
    assert candidate(words = ['abcdefg', 'abcde', 'abcd', 'abc', 'ab', 'a'],k = 4) == [2, 2, 2, 2, 3, 3]
    assert candidate(words = ['a', 'a', 'a', 'a', 'a'],k = 3) == [1, 1, 1, 1, 1]
    assert candidate(words = ['abc', 'abcd', 'ab', 'abcde'],k = 3) == [2, 2, 3, 2]
    assert candidate(words = ['dog', 'racer', 'car'],k = 2) == [0, 0, 0]
    assert candidate(words = ['hello', 'hell', 'he', 'h'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['abcd', 'abcde', 'ab', 'abc'],k = 3) == [2, 2, 3, 2]
    assert candidate(words = ['abc', 'abcd', 'abcde', 'abcdef'],k = 3) == [4, 3, 3, 3]
    assert candidate(words = ['cat', 'cater', 'category', 'catalog'],k = 2) == [4, 3, 3, 4]
    assert candidate(words = ['prefix', 'pre', 'preface', 'prefatory', 'presentation'],k = 3) == [3, 4, 3, 3, 4]
    assert candidate(words = ['banana', 'banan', 'ban', 'ba', 'b', 'bananaaa', 'bananas'],k = 3) == [5, 6, 6, 6, 6, 5, 5]
    assert candidate(words = ['abcdabcd', 'abcdabc', 'abcdab', 'abcd', 'abc', 'ab', 'a'],k = 4) == [3, 3, 3, 3, 4, 4, 4]
    assert candidate(words = ['programming', 'program', 'programmer', 'programmatic'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['interview', 'inter', 'internal', 'interpretation', 'internet'],k = 3) == [5, 5, 5, 5, 5]
    assert candidate(words = ['prefix', 'preface', 'preference', 'pre', 'predict', 'prevent', 'preach', 'prelude'],k = 4) == [3, 3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['hello', 'hell', 'he', 'helloworld', 'he'],k = 4) == [2, 2, 2, 2, 2]
    assert candidate(words = ['algorithm', 'algorithms', 'algo', 'al', 'algorith'],k = 3) == [4, 4, 8, 8, 4]
    assert candidate(words = ['sequence', 'sequential', 'succession', 'successive', 'succeed'],k = 4) == [1, 1, 1, 1, 1]
    assert candidate(words = ['optimization', 'optimize', 'optimal', 'optimum'],k = 3) == [5, 5, 5, 5]
    assert candidate(words = ['zebra', 'zebra', 'zebra', 'zebra', 'zebra'],k = 4) == [5, 5, 5, 5, 5]
    assert candidate(words = ['banana', 'bandana', 'band', 'bandwidth'],k = 3) == [4, 3, 3, 3]
    assert candidate(words = ['abcdefgh', 'abcde', 'abcd', 'abc', 'ab', 'a'],k = 3) == [3, 3, 3, 4, 4, 4]
    assert candidate(words = ['same', 'sam', 'sameple', 'sample', 'samp'],k = 3) == [3, 3, 3, 3, 3]
    assert candidate(words = ['prefix', 'pre', 'preface', 'preach', 'prelude'],k = 3) == [3, 3, 3, 3, 3]
    assert candidate(words = ['xxxxxxxxxx', 'xxxxxxxxx', 'xxxxxxxx', 'xxxxxxx', 'xxxxxx', 'xxxxx', 'xxxx', 'xxx', 'xx', 'x'],k = 5) == [5, 5, 5, 5, 5, 6, 6, 6, 6, 6]
    assert candidate(words = ['performance', 'perform', 'performanceanalysis', 'performant'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['programming', 'programmer', 'program', 'pro', 'pr', 'p'],k = 2) == [7, 7, 8, 8, 8, 8]
    assert candidate(words = ['abcabcabc', 'abcabc', 'abc', 'ab', 'a'],k = 2) == [3, 3, 6, 6, 6]
    assert candidate(words = ['test', 'testing', 'tested', 'tests', 'tempest'],k = 4) == [2, 2, 2, 2, 4]
    assert candidate(words = ['longest', 'longer', 'long', 'lon', 'lo', 'l'],k = 3) == [3, 3, 3, 4, 4, 4]
    assert candidate(words = ['abcdabcd', 'abcdabcde', 'abcdabc', 'abcdab', 'abcd'],k = 3) == [6, 6, 6, 7, 7]
    assert candidate(words = ['algorithm', 'algebra', 'algorithmic', 'algae'],k = 2) == [3, 9, 3, 9]
    assert candidate(words = ['mississippi', 'mississipp', 'mississip', 'mississi', 'mississ', 'missis', 'missi', 'miss', 'mis', 'mi', 'm'],k = 5) == [6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7]
    assert candidate(words = ['unique', 'unite', 'unity', 'unit', 'universe'],k = 3) == [4, 3, 3, 3, 4]
    assert candidate(words = ['abcdefghijklmnopqrstuvwxyz', 'abcdefghijklmnopqrstuvwxyz', 'abcdefghijklmnopqrstuvwxyz', 'abcdefghijklmnopqrstuvwxyz', 'abcdefghijklmnopqrstuvwxyz'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['abacaxi', 'abacax', 'abac', 'aba', 'ab'],k = 2) == [4, 4, 6, 6, 6]
    assert candidate(words = ['communication', 'communicate', 'communicator', 'communications'],k = 3) == [10, 10, 10, 10]
    assert candidate(words = ['common', 'commonly', 'commonsense', 'commonplace', 'commonwealth'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['prefix', 'pre', 'predefined', 'premier', 'pressure'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['banana', 'bandana', 'banter', 'bandage', 'banner', 'bandwidth'],k = 5) == [3, 3, 3, 3, 3, 3]
    assert candidate(words = ['sun', 'sunny', 'sunshine', 'sunset', 'sunken', 'sunflower', 'sunrise', 'sundial'],k = 3) == [3, 3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'],k = 2) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(words = ['test', 'testing', 'tested', 'testify', 'testament'],k = 4) == [4, 4, 4, 4, 4]
    assert candidate(words = ['abc', 'abcd', 'abcde', 'abcdef', 'abcdefg'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['prefix', 'prefixing', 'prefixation', 'prefix', 'pre'],k = 3) == [6, 6, 6, 6, 6]
    assert candidate(words = ['algorithm', 'algebra', 'algorithmic', 'algorithmically', 'algebraic'],k = 4) == [3, 3, 3, 3, 3]
    assert candidate(words = ['banana', 'bananas', 'bandana', 'bandanas', 'band'],k = 4) == [3, 3, 3, 3, 3]
    assert candidate(words = ['cat', 'cater', 'category', 'catalog', 'catalogue', 'catalogued', 'cataloging'],k = 6) == [3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['xylophone', 'xylography', 'xylophon', 'xylo', 'xy', 'x'],k = 3) == [4, 4, 4, 4, 4, 4]
    assert candidate(words = ['inter', 'interact', 'interactive', 'interface', 'interleave', 'interchange', 'interconnect', 'intercept', 'interdependent'],k = 7) == [5, 5, 5, 5, 5, 5, 5, 5, 5]
    assert candidate(words = ['cloud', 'cloudy', 'cloudstorage', 'cloudservices'],k = 3) == [5, 5, 5, 5]
    assert candidate(words = ['abacaxi', 'abacax', 'abaca', 'abac', 'aba', 'ab', 'a'],k = 4) == [3, 3, 3, 3, 4, 4, 4]
    assert candidate(words = ['abacaxi', 'banana', 'abacax', 'bacana', 'bacaxa'],k = 3) == [2, 0, 2, 0, 0]
    assert candidate(words = ['prefix', 'preface', 'prefect', 'prefer', 'prelude'],k = 4) == [3, 3, 3, 3, 4]
    assert candidate(words = ['algorithm', 'algebra', 'algorithmic', 'algal', 'algae', 'algorithmically', 'algorithmically'],k = 5) == [3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['aabbcc', 'aabb', 'aab', 'aa', 'a'],k = 3) == [2, 2, 2, 3, 3]
    assert candidate(words = ['banana', 'bandana', 'band', 'bandit', 'bandwidth'],k = 4) == [4, 3, 3, 3, 3]
    assert candidate(words = ['hello', 'hell', 'helo', 'hallo', 'heaven'],k = 3) == [2, 2, 2, 3, 3]
    assert candidate(words = ['intersection', 'inter', 'interact', 'interactive'],k = 2) == [8, 8, 5, 5]
    assert candidate(words = ['datastructure', 'data', 'database', 'dataanalysis'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['banana', 'bandana', 'band', 'bandanna', 'bang', 'ban', 'banner'],k = 3) == [4, 3, 3, 3, 4, 4, 4]
    assert candidate(words = ['hello', 'hell', 'helo', 'hella', 'hellomy', 'hellomyworld'],k = 4) == [4, 4, 4, 4, 4, 4]
    assert candidate(words = ['programming', 'program', 'pro', 'process', 'processor'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['programming', 'programmer', 'procrastinate', 'profession', 'process'],k = 4) == [3, 3, 3, 3, 3]
    assert candidate(words = ['elephant', 'elephante', 'elephant', 'elephant', 'eleph', 'ele', 'e'],k = 3) == [8, 8, 8, 8, 8, 8, 8]
    assert candidate(words = ['flower', 'flow', 'flight', 'flew', 'flour'],k = 2) == [3, 3, 4, 4, 4]
    assert candidate(words = ['elephant', 'elephant', 'elephant', 'elephant', 'elephant', 'elephant'],k = 5) == [8, 8, 8, 8, 8, 8]
    assert candidate(words = ['different', 'difficult', 'difficulty', 'differently', 'differ'],k = 4) == [4, 4, 4, 4, 4]
    assert candidate(words = ['programming', 'program', 'programmer', 'programm', 'programmi', 'programmin', 'programmin'],k = 4) == [8, 9, 9, 9, 8, 8, 8]
    assert candidate(words = ['abcdefg', 'abcdef', 'abcde', 'abcd', 'abc'],k = 2) == [5, 5, 6, 6, 6]
    assert candidate(words = ['test', 'testing', 'tested', 'testing', 'testify', 'testament'],k = 3) == [5, 4, 5, 4, 4, 5]
    assert candidate(words = ['abcdefghij', 'abcdefghi', 'abcdefgh', 'abcdefg', 'abcdef', 'abcde', 'abcd', 'abc', 'ab', 'a'],k = 5) == [5, 5, 5, 5, 5, 6, 6, 6, 6, 6]
    assert candidate(words = ['supercalifragilisticexpialidocious', 'super', 'supercalifragilistic', 'superex', 'supercalifragil'],k = 4) == [5, 5, 5, 5, 5]
    assert candidate(words = ['algorithm', 'algebra', 'algorithmic', 'alibi', 'alias'],k = 2) == [3, 9, 3, 9, 9]
    assert candidate(words = ['aabbcc', 'aabb', 'aabc', 'aab', 'aac', 'aa', 'ab', 'ac', 'a'],k = 3) == [3, 3, 3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['prefix', 'prefixes', 'prefixing', 'pref', 'pre'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['banana', 'band', 'ban', 'bandana', 'bandwidth'],k = 3) == [4, 3, 4, 3, 3]
    assert candidate(words = ['flower', 'flow', 'flight', 'flew', 'fly'],k = 4) == [2, 2, 2, 2, 2]
    assert candidate(words = ['abcd', 'abcde', 'ab', 'abc', 'a', 'abca', 'abcd'],k = 4) == [3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['repeated', 'repeat', 'repetition', 'repetitive', 'repel'],k = 3) == [4, 4, 4, 4, 4]
    assert candidate(words = ['flower', 'flow', 'flight', 'flock', 'flour', 'flat', 'flog'],k = 3) == [3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['prefix', 'pre', 'precondition', 'preference'],k = 3) == [3, 3, 3, 3]
    assert candidate(words = ['repeated', 'repeatedly', 'rep', 'repeat', 'repe'],k = 3) == [4, 4, 6, 4, 6]
    assert candidate(words = ['flower', 'flow', 'flight', 'flour', 'flourish', 'flourish', 'flourish'],k = 5) == [3, 3, 3, 3, 3, 3, 3]
    assert candidate(words = ['prefix', 'pre', 'predict', 'precondition', 'prevent', 'precedent'],k = 4) == [3, 3, 3, 3, 3, 3]
    assert candidate(words = ['xylophone', 'xenon', 'xylography', 'xylo', 'xylophoneography'],k = 2) == [4, 9, 9, 9, 4]
    assert candidate(words = ['small', 'smaller', 'smallest', 'smallests', 'smallestest'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['distinct', 'distinguish', 'distant', 'distortion', 'distract', 'distrust'],k = 4) == [4, 4, 4, 4, 4, 4]
    assert candidate(words = ['unique', 'uniqueness', 'un', 'uniq', 'uniquer'],k = 4) == [2, 2, 4, 2, 2]
    assert candidate(words = ['aaa', 'bbb', 'aaa', 'bbb', 'aaa', 'bbb'],k = 3) == [3, 3, 3, 3, 3, 3]
    assert candidate(words = ['test', 'testing', 'tested', 'testing', 'testify'],k = 2) == [7, 5, 7, 5, 7]
    assert candidate(words = ['programming', 'program', 'programmer', 'pro', 'programming'],k = 3) == [7, 8, 7, 8, 7]
    assert candidate(words = ['aaaaa', 'aaa', 'aa', 'a', 'abcd', 'abc', 'ab', 'a'],k = 3) == [2, 2, 2, 2, 2, 2, 2, 2]
    assert candidate(words = ['abcd', 'abcde', 'abcdef', 'abcdefg', 'abcdefgh', 'abcdefghi'],k = 5) == [5, 4, 4, 4, 4, 4]
    assert candidate(words = ['algorithm', 'algori', 'algor', 'algo', 'alg', 'al', 'a', 'algorithmic', 'algorith', 'algorithmically'],k = 6) == [4, 4, 4, 5, 5, 5, 5, 4, 4, 4]
    assert candidate(words = ['consistent', 'consistency', 'consist', 'cons', 'con', 'co', 'c'],k = 3) == [4, 4, 4, 7, 7, 7, 7]
    assert candidate(words = ['civic', 'civ', 'city', 'citizens', 'citizen', 'citize', 'citizi'],k = 5) == [3, 3, 2, 2, 2, 2, 2]
    assert candidate(words = ['aaaab', 'aaab', 'aab', 'ab', 'b'],k = 2) == [2, 2, 3, 3, 3]
    assert candidate(words = ['consistent', 'consistency', 'consist', 'cons', 'con'],k = 3) == [4, 4, 4, 7, 7]
    assert candidate(words = ['abacaxi', 'abacax', 'abac', 'aba', 'ab', 'a'],k = 5) == [1, 1, 1, 1, 1, 2]
    assert candidate(words = ['supercalifragilisticexpialidocious', 'super', 'supercal', 'supercali', 'superca'],k = 2) == [8, 9, 9, 8, 9]
    assert candidate(words = ['banana', 'bandana', 'band', 'ban', 'ba', 'b'],k = 3) == [3, 3, 3, 3, 3, 3]
    assert candidate(words = ['aabbcc', 'aabbc', 'aabb', 'aab', 'aa', 'a'],k = 4) == [2, 2, 2, 2, 3, 3]
    assert candidate(words = ['longest', 'longer', 'long', 'lo', 'l', 'longestword'],k = 4) == [2, 2, 2, 4, 4, 2]
    assert candidate(words = ['repetition', 'rep', 'repet', 'repetit', 'repetiti'],k = 3) == [5, 7, 7, 5, 5]
    assert candidate(words = ['test', 'testing', 'tested', 'tes'],k = 3) == [3, 3, 3, 4]
    assert candidate(words = ['prefix', 'pre', 'pref', 'prefer'],k = 3) == [3, 4, 3, 3]
    assert candidate(words = ['abcd', 'abce', 'abcf'],k = 2) == [3, 3, 3]
    assert candidate(words = ['abcd', 'abc', 'ab', 'a'],k = 3) == [1, 1, 1, 2]
    assert candidate(words = ['hello', 'hell', 'heaven', 'heavy'],k = 2) == [4, 4, 4, 4]
    assert candidate(words = ['abcd', 'abce', 'abcf', 'abcg'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['aaaaa', 'aaaab', 'aaabb', 'aabbb', 'abbbb'],k = 3) == [2, 2, 2, 3, 3]
    assert candidate(words = ['dog', 'racer', 'car'],k = 2) == [0, 0, 0]
    assert candidate(words = ['a', 'b', 'c', 'd', 'e'],k = 1) == [1, 1, 1, 1, 1]
    assert candidate(words = ['hello', 'world', 'help', 'hero'],k = 2) == [2, 3, 2, 3]
    assert candidate(words = ['interspecies', 'interstellar', 'interstate'],k = 2) == [7, 6, 6]
    assert candidate(words = ['one', 'once', 'on', 'oneone'],k = 2) == [2, 3, 3, 2]
    assert candidate(words = ['abcde', 'abcdf', 'abcda', 'abcdz'],k = 3) == [4, 4, 4, 4]
    assert candidate(words = ['aaaa', 'aaa', 'aa', 'a'],k = 3) == [1, 1, 1, 2]
    assert candidate(words = ['prefix', 'preface', 'prefer', 'preach'],k = 2) == [4, 4, 4, 4]
    assert candidate(words = ['abc', 'abcd', 'abcde', 'abcdef', 'abcdefg'],k = 4) == [4, 3, 3, 3, 3]
    assert candidate(words = ['abc', 'abcd', 'abcde', 'abcdef'],k = 2) == [5, 5, 4, 4]
    assert candidate(words = ['flower', 'flow', 'flight', 'flute'],k = 3) == [2, 2, 2, 2]
    assert candidate(words = ['flower', 'flow', 'flight', 'floor'],k = 2) == [3, 3, 4, 4]
    assert candidate(words = ['abcd', 'abce', 'abcf'],k = 2) == [3, 3, 3]
    assert candidate(words = ['flower', 'flow', 'flight'],k = 2) == [2, 2, 4]
    assert candidate(words = ['abc', 'abcd', 'abcde'],k = 3) == [0, 0, 0]
    assert candidate(words = ['hello', 'help', 'hold'],k = 2) == [1, 1, 3]
    assert candidate(words = ['abc', 'abcd', 'abcde', 'abcdef'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['test', 'taste', 'testing', 'temple'],k = 2) == [2, 4, 2, 4]
    assert candidate(words = ['apple', 'applet', 'application'],k = 3) == [0, 0, 0]
    assert candidate(words = ['a', 'a', 'a', 'a', 'a'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'],k = 4) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(words = ['aaa', 'aa', 'a'],k = 2) == [1, 1, 2]
    assert candidate(words = ['hello', 'hell', 'he', 'h'],k = 2) == [2, 2, 4, 4]
    assert candidate(words = ['flower', 'flow', 'flight', 'flour'],k = 3) == [2, 2, 3, 2]
    assert candidate(words = ['abc', 'abcd', 'abcde'],k = 3) == [0, 0, 0]
    assert candidate(words = ['prefix', 'preform', 'preference', 'prelude'],k = 3) == [3, 3, 3, 4]
    assert candidate(words = ['a', 'a', 'a', 'a', 'a'],k = 2) == [1, 1, 1, 1, 1]
    assert candidate(words = ['prefix', 'pre', 'pref', 'prefer', 'prefi'],k = 4) == [3, 4, 3, 3, 3]
    assert candidate(words = ['apple', 'application', 'apt', 'appetite'],k = 3) == [2, 2, 3, 2]
    assert candidate(words = ['prefix', 'pre', 'pref', 'prefer'],k = 2) == [4, 4, 4, 4]
    assert candidate(words = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'],k = 3) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(words = ['distinct', 'words', 'only', 'here'],k = 3) == [0, 0, 0, 0]
    assert candidate(words = ['abc', 'abc', 'abc', 'abc', 'abc'],k = 5) == [0, 0, 0, 0, 0]
    assert candidate(words = ['flower', 'flow', 'flight', 'flour'],k = 2) == [3, 3, 4, 4]
    assert candidate(words = ['aaaa', 'aaab', 'aaac', 'aabb'],k = 3) == [2, 2, 2, 3]
    assert candidate(words = ['abcde', 'abcdf', 'abcda', 'abcdb'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['abc', 'abcde', 'abcdf'],k = 3) == [0, 0, 0]
    assert candidate(words = ['flower', 'flow', 'flight', 'fluent'],k = 3) == [2, 2, 2, 2]
    assert candidate(words = ['a'],k = 1) == [0]
    assert candidate(words = ['abcd', 'abcde', 'abcdef', 'abcdefg', 'abcdefgh'],k = 2) == [7, 7, 7, 6, 6]
    assert candidate(words = ['aaaaa', 'aaaab', 'aaabb', 'aabbb', 'abbbb'],k = 4) == [1, 1, 1, 1, 2]
    assert candidate(words = ['same', 'same', 'same'],k = 2) == [4, 4, 4]
    assert candidate(words = ['aaaa', 'aa', 'aaa', 'a', 'aaaaa'],k = 2) == [3, 4, 4, 4, 3]
    assert candidate(words = ['aabb', 'aabc', 'aabd', 'aabe'],k = 3) == [3, 3, 3, 3]
    assert candidate(words = ['distinct', 'words', 'are', 'here'],k = 2) == [0, 0, 0, 0]
    assert candidate(words = ['abc', 'abcd', 'abce', 'abcdef'],k = 3) == [3, 3, 3, 3]
    assert candidate(words = ['prefix', 'pre', 'prepend', 'presume'],k = 3) == [3, 3, 3, 3]
    assert candidate(words = ['throne', 'throne', 'throne', 'throne'],k = 3) == [6, 6, 6, 6]
    assert candidate(words = ['prefix', 'prefix', 'prefix', 'prefix', 'prefix'],k = 4) == [6, 6, 6, 6, 6]
    assert candidate(words = ['abab', 'aba', ''],k = 2) == [0, 0, 3]
    assert candidate(words = ['test', 'testing', 'testcase', 'testing', 'testcases'],k = 3) == [4, 4, 4, 4, 4]
    assert candidate(words = ['apple', 'application', 'appetite', 'appreciate'],k = 3) == [3, 3, 3, 3]
    assert candidate(words = ['hello', 'hell', 'he', 'h'],k = 3) == [1, 1, 1, 2]
    assert candidate(words = ['abcd', 'abc', 'ab', 'a'],k = 2) == [2, 2, 3, 3]
    assert candidate(words = ['banana', 'bandana', 'ban', 'band', 'bandana'],k = 4) == [3, 3, 3, 3, 3]
    assert candidate(words = ['interspecies', 'interstellar', 'interstate'],k = 3) == [0, 0, 0]
    assert candidate(words = ['aaaa', 'aa', 'aaa', 'aaaaa'],k = 3) == [2, 3, 2, 2]
    assert candidate(words = ['apple', 'application', 'app', 'applet', 'apples'],k = 2) == [5, 5, 5, 5, 5]
    assert candidate(words = ['abcd', 'abce', 'abcf', 'abcg'],k = 3) == [3, 3, 3, 3]
    assert candidate(words = ['a', 'a', 'a', 'a'],k = 2) == [1, 1, 1, 1]
    assert candidate(words = ['hello', 'hell', 'he', 'helloworld'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['prefix', 'preface', 'presentation', 'preference', 'prestige'],k = 4) == [3, 3, 3, 3, 3]
    assert candidate(words = ['prefix', 'pre', 'predict', 'printing'],k = 2) == [3, 3, 3, 3]
    assert candidate(words = ['a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a', 'a'],k = 5) == [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]
    assert candidate(words = ['aaaa', 'aabb', 'aabc', 'aacc'],k = 3) == [2, 2, 2, 2]
    assert candidate(words = ['aaaa', 'bbbb', 'cccc', 'dddd'],k = 2) == [0, 0, 0, 0]
    assert candidate(words = ['apple', 'app', 'application', 'appetite'],k = 2) == [3, 4, 3, 4]
    assert candidate(words = ['jump', 'run', 'run', 'jump', 'run'],k = 2) == [3, 4, 4, 3, 4]
    assert candidate(words = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j'],k = 5) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(words = ['same', 'same', 'same', 'same'],k = 2) == [4, 4, 4, 4]
    assert candidate(words = ['abcdefg', 'abcdef', 'abcde', 'abcd'],k = 2) == [5, 5, 6, 6]
    assert candidate(words = ['prefix', 'preform', 'president', 'presentation'],k = 2) == [4, 4, 4, 4]
    assert candidate(words = ['aaaa', 'aaaa', 'aaaa', 'aaaa'],k = 4) == [0, 0, 0, 0]
    assert candidate(words = ['hello', 'he', 'hell', 'helper'],k = 2) == [3, 4, 3, 4]
    assert candidate(words = ['prefix', 'pre', 'pref', 'prefer', 'preference'],k = 4) == [3, 4, 3, 3, 3]
    assert candidate(words = ['prefix', 'pre', 'prepend', 'prevent'],k = 3) == [3, 3, 3, 3]
    assert candidate(words = ['same', 'same', 'same', 'same', 'same'],k = 4) == [4, 4, 4, 4, 4]
    assert candidate(words = ['hello', 'hell', 'heaven', 'heavy'],k = 3) == [2, 2, 2, 2]


# === INVOCATION ===
check(Solution().longestCommonPrefix)
print("All tests passed")
