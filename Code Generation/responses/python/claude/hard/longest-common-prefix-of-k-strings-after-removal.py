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