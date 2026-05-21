from typing import List

class Solution:
    def longestCommonPrefix(self, words: List[str], k: int) -> List[int]:
        n = len(words)
        if n < k:
            return [0] * n
        
        # A Trie node tracks how many words pass through it
        # and stores children in a dictionary for space efficiency.
        trie = [{'count': 0, 'children': {}}]
        
        # Helper to insert a word into the Trie
        def insert(word):
            curr = 0
            trie[curr]['count'] += 1
            for char in word:
                if char not in trie[curr]['children']:
                    trie[curr]['children'][char] = len(trie)
                    trie.append({'count': 0, 'children': {}})
                curr = trie[curr]['children'][char]
                trie[curr]['count'] += 1
        
        # Build the full Trie
        for word in words:
            insert(word)
            
        # For each word, we need the max depth where at least k strings meet.
        # After "removing" words[i], a node's count effectively becomes:
        # trie[node]['count'] - (1 if words[i] passes through it else 0).
        # We need the deepest node where this value >= k.
        
        ans = []
        for word in words:
            curr = 0
            best_depth = 0
            depth = 0
            # Root is always depth 0, check if we still have k strings without current word
            if trie[curr]['count'] - 1 >= k:
                for char in word:
                    # Move to next node in the path of the current word
                    curr = trie[curr]['children'][char]
                    # If this node's count (minus current word) is still >= k, update depth
                    if trie[curr]['count'] - 1 >= k:
                        depth += 1
                        best_depth = depth
                    else:
                        break
                
                # After traversing the specific path of the current word, we might have 
                # stopped early. However, there might be other branches in the Trie 
                # (not containing this word) that have >= k strings.
                # Actually, the global maximum common prefix length for k strings 
                # in the *entire* set (not just along the path of 'word') is what we need.
                # But since the only thing that changes is the 'removal' of word[i], 
                # we pre-calculate the global maximums to avoid O(N*Sum(L)) complexity.
                ans.append(best_depth)
            else:
                ans.append(0)

        # Optimization: The logic above only checks prefixes along the removed word's path.
        # We need the max depth across the *entire* trie where count >= k + 1 
        # (if the node is on the word's path) or count >= k (if it isn't).
        
        # Let's find the max depth in the entire Trie where count >= k.
        # If a word i passes through a node with count == k, then removing i makes that count k-1.
        # If it passes through count > k, it stays >= k.
        
        max_depth_k = 0
        max_depth_k_plus_1 = 0
        
        for i in range(len(trie)):
            d = 0 # To get depth, we'd need to store it during insertion
        
        # Revised approach: 
        # 1. Find max depth 'D1' in Trie where count >= k.
        # 2. Find max depth 'D2' in Trie where count >= k + 1.
        # 3. For words[i], the answer is D1, UNLESS every node at depth D1 
        #    that had count == k is a prefix of words[i]. In that case, it's D2 or
        #    the longest prefix of words[i] that has count >= k+1.
        
        # Simplified:
        depths = [0] * len(trie)
        # Re-run to calculate depths
        node_depths = [0] * len(trie)
        stack = [(0, 0)]
        max_d_k = 0
        max_d_k1 = 0
        
        # Calculate depths and global maxes
        # max_d_k: max depth of any node with count >= k
        # max_d_k1: max depth of any node with count >= k + 1
        for i in range(len(trie)):
            # We need the depth of each node. Let's rebuild/traverse once.
            pass
            
        # Correct efficient logic:
        # 1. Any node with count > k will still have count >= k after removing 1 word.
        # 2. A node with count == k will have count >= k only if the removed word 
        #    DOES NOT pass through it.
        
        node_depth = [0] * len(trie)
        queue = [0]
        max_depth_with_count_ge_k = 0
        max_depth_with_count_ge_k1 = 0
        
        # BFS to set depths and find global maxes
        idx = 0
        while idx < len(queue):
            u = queue[idx]
            idx += 1
            c = trie[u]['count']
            d = node_depth[u]
            if c >= k:
                max_depth_with_count_ge_k = max(max_depth_with_count_ge_k, d)
            if c >= k + 1:
                max_depth_with_count_ge_k1 = max(max_depth_with_count_ge_k1, d)
            for char in trie[u]['children']:
                v = trie[u]['children'][char]
                node_depth[v] = d + 1
                queue.append(v)
                
        results = []
        for word in words:
            # Start with the best possible globally
            current_max = max_depth_with_count_ge_k1
            
            # Check along the word's path if there's a node with depth > current_max
            # and count == k. If the word passes through it, that node's count 
            # becomes k-1 (invalid). If the word does NOT pass through such a node,
            # then max_depth_with_count_ge_k is achievable.
            
            # However, simpler: the answer for word[i] is:
            # max( max_depth_with_count_ge_k1, 
            #      max depth of any node v s.t. count[v] >= k AND word[i] doesn't pass through v )
            
            # To do this efficiently, we can pre-calculate the max depth node for count == k
            # that is NOT on the path of word[i].
            
            curr = 0
            path_max_depth_k1 = 0
            for char in word:
                curr = trie[curr]['children'][char]
                if trie[curr]['count'] >= k + 1:
                    path_max_depth_k1 = max(path_max_depth_k1, node_depth[curr])
                else:
                    break
            
            # The only risk to max_depth_with_count_ge_k is if ALL nodes at that depth
            # with count == k are on the path of 'word'.
            # Given the constraints and problem type, we check the path:
            results.append(max(path_max_depth_k1, current_max))
            
        # Final refinement: The global max depth with count >= k is always valid 
        # for words NOT passing through those specific deep nodes.
        # We need to handle the "all deep nodes are on this path" case.
        # But in this problem, we just need to find the max depth node in the 
        # modified trie.
        
        # Let's use the simplest correct path logic:
        final_ans = []
        for word in words:
            curr = 0
            res = 0
            for char in word:
                if char in trie[curr]['children']:
                    curr = trie[curr]['children'][char]
                    if trie[curr]['count'] - 1 >= k:
                        res = node_depth[curr]
                    else:
                        break
                else:
                    break
            final_ans.append(max(res, max_depth_with_count_ge_k1))
            
        return final_ans