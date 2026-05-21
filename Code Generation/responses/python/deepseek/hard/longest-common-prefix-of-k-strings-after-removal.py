from typing import List
from collections import Counter

class Solution:
    def longestCommonPrefix(self, words: List[str], k: int) -> List[int]:
        n = len(words)
        if k > n:
            return [0] * n
        
        # For each word, consider each possible prefix length
        # We'll count occurrences of each prefix
        
        # First, find all possible prefixes and their frequencies
        # But we need to handle removal of one element
        
        # Better approach: For each index, we want longest prefix that appears in at least k other words
        # We can do binary search on prefix length for each query
        # But to optimize, we can use prefix count with proper handling
        
        # Let's consider all possible prefixes of all words
        # But constraints: total length of all words is 1e5, so total number of prefixes is at most 1e5
        
        # We'll store prefix counts in a trie-like structure
        # For each word, we can check which prefixes appear in at least k other words
        
        # However, we need to handle removal of one word efficiently
        
        # Approach 2: For each word, we can try all its prefixes and check if
        # after removing this word, there are at least k occurrences of that prefix
        
        result = []
        
        for i in range(n):
            # Remove word[i]
            # Check all prefixes of remaining words
            # But this would be O(n * L) which is too slow
            
            # We need a smarter way
            pass
        
        # Better approach:
        # Preprocess: For each possible prefix, store list of indices containing it
        # Then for each index i, we can find longest prefix that appears in at least k indices excluding i
        
        # Step 1: Get all possible prefixes
        prefixes = {}
        # prefix -> list of indices
        for idx, word in enumerate(words):
            for l in range(1, len(word) + 1):
                prefix = word[:l]
                if prefix not in prefixes:
                    prefixes[prefix] = []
                prefixes[prefix].append(idx)
        
        # Now for each index i, we need longest prefix where count excluding i >= k
        result = [0] * n
        
        # For each prefix, mark which indices get this prefix
        for prefix, indices in prefixes.items():
            cnt = len(indices)
            if cnt >= k:
                # Some indices might benefit
                # If cnt >= k+1, all indices not in indices get length from this prefix
                # If cnt == k, only indices not in indices get length from this prefix
                # Actually, we need to check for each index i:
                # If cnt - (1 if i in indices else 0) >= k
                # Then answer[i] can be at least len(prefix)
                
                # Since prefixes are processed in increasing length, 
                # we need to take maximum over all prefixes
                if cnt - 1 >= k:
                    # All indices can get length from this prefix
                    # Actually, if cnt > k, then for all indices, cnt - (1 if i in indices else 0) >= k
                    # If cnt == k+1, then for indices not in indices: cnt >= k, for indices in indices: cnt-1 = k >= k
                    # So all indices get it
                    for j in range(n):
                        result[j] = max(result[j], len(prefix))
                else:
                    # cnt == k
                    # Then only indices not in indices get it (since removing i from indices would leave k-1)
                    for j in range(n):
                        if j not in indices:  # This is O(n) per prefix, too slow
                            result[j] = max(result[j], len(prefix))
        
        # Optimize the O(n * #prefixes) case
        # We need a more efficient way
        
        # Let's rethink: For each index i, we need longest prefix that appears in at least k other words
        # So if we want to process efficiently, we can binary search on prefix length for each i
        # But that still might be O(n * L * log L) which is 1e9
        
        # Let's try the reverse: For each length L, find which indices can achieve prefix length L
        # Then propagate
        
        # We need to handle the "removing one element" condition
        
        return result

# Implementation using prefix frequency globally and per index
# Let's build a frequency map for prefixes at each length

class Solution:
    def longestCommonPrefix(self, words: List[str], k: int) -> List[int]:
        n = len(words)
        if k > n:
            return [0] * n
        
        # We'll try each possible prefix length from longest to shortest
        # For each length L, we want to know for each index if there are >= k distinct indices
        # (other than i) sharing that prefix of length L
        
        # Get all prefixes of all words
        prefix_counts = {}
        for idx, word in enumerate(words):
            for l in range(1, len(word) + 1):
                prefix = word[:l]
                if prefix not in prefix_counts:
                    prefix_counts[prefix] = []
                prefix_counts[prefix].append(idx)
        
        # For each prefix, we have list of indices
        # We'll sort prefixes by length to process longest first
        prefixes_by_length = {}
        for prefix, indices in prefix_counts.items():
            l = len(prefix)
            if l not in prefixes_by_length:
                prefixes_by_length[l] = []
            prefixes_by_length[l].append((prefix, indices))
        
        result = [0] * n
        
        # Process lengths from longest to shortest
        for l in range(max(len(w) for w in words), 0, -1):
            if l in prefixes_by_length:
                # For each prefix of length l
                for prefix, indices in prefixes_by_length[l]:
                    cnt = len(indices)
                    if cnt >= k:
                        # All indices not in indices can get this length
                        # But we need to update result for those indices
                        # Also, if cnt > k, all indices can get it
                        if cnt > k:
                            # All n indices get this length if they don't already have longer
                            for i in range(n):
                                if result[i] == 0:
                                    result[i] = l
                        else:
                            # cnt == k
                            # Only indices NOT in indices get it
                            # Create a set of indices for faster lookup
                            indices_set = set(indices)
                            for i in range(n):
                                if result[i] == 0 and i not in indices_set:
                                    result[i] = l
                    break  # Once we process one prefix of this length, we can break
                    # Actually we need to check all prefixes of this length
                    # But since we process longest first, we want maximum possible
                    # So for a given i, if we find any prefix of length l that works, we set result[i] = l
                    # So we can process all prefixes of length l before moving to shorter lengths
        
        return result