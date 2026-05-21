from typing import List
from collections import defaultdict

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        graph = [[] for _ in range(n)]
        for u, v, l in edges:
            graph[u].append((v, l))
            graph[v].append((u, l))
        
        ans_len = 0
        ans_nodes = 0
        
        # For each node, track paths from it downward
        def dfs(node, parent):
            nonlocal ans_len, ans_nodes
            
            # Store best paths with last value frequency
            # We'll store: (length, nodes_count, value_counts)
            # But due to constraints, we use a dict for frequencies
            best_paths = []  # list of (length, nodes, freq_dict)
            freq = defaultdict(int)
            freq[nums[node]] += 1
            
            # Start path at current node
            best_paths.append((0, 1, freq.copy()))
            
            for nei, l in graph[node]:
                if nei == parent:
                    continue
                
                # Get paths from child
                child_paths = dfs(nei, node)
                new_paths = []
                
                # Combine current node's path with child paths
                for path_len, path_nodes, path_freq in child_paths:
                    # Add current node to start of path
                    new_len = path_len + l
                    new_nodes = path_nodes + 1
                    
                    # Update frequency
                    val = nums[node]
                    new_freq = path_freq.copy()
                    new_freq[val] = new_freq.get(val, 0) + 1
                    
                    # Check if valid
                    bad = 0
                    for v in new_freq:
                        if new_freq[v] > 2:
                            bad = 2
                            break
                        if new_freq[v] == 2:
                            bad += 1
                            if bad > 1:
                                break
                    
                    if bad <= 1:  # Valid path
                        new_paths.append((new_len, new_nodes, new_freq))
                        # Update answer
                        if new_len > ans_len:
                            ans_len = new_len
                            ans_nodes = new_nodes
                        elif new_len == ans_len and new_nodes < ans_nodes:
                            ans_nodes = new_nodes
                
                # Also paths starting at current node
                cur_freq = defaultdict(int)
                cur_freq[nums[node]] = 1
                cur_len = 0
                cur_nodes = 1
                new_paths.append((cur_len, cur_nodes, cur_freq))
                
                # Update best_paths
                best_paths.extend(new_paths)
            
            # Keep only best paths per node (prune if needed)
            # Reduce to manageable size
            limited = []
            for p in best_paths:
                # Keep only paths that are best for some criteria
                limited.append(p)
                if len(limited) > 20:  # Heuristic limit
                    limited.sort(key=lambda x: (-x[0], x[1]))
                    limited = limited[:20]
            
            return limited
        
        # Start DFS from each node (tree, so any root works)
        # But we need all downward paths from all ancestors
        # We'll do DFS from each node, but that's O(n^2) - too slow
        # Alternative: do DFS from root and maintain state along path
        
        # Better approach: DFS with path tracking
        def dfs2(node, parent, path, freq, dup_count, total_len, total_nodes):
            nonlocal ans_len, ans_nodes
            
            # Current path from root to node
            # Update answer for all suffix starting at each ancestor?
            # We need to consider all ancestors, not just root
            
            # Add current node to path
            val = nums[node]
            new_freq = freq.copy()
            new_freq[val] = new_freq.get(val, 0) + 1
            new_dup = dup_count
            if new_freq[val] == 2:
                new_dup += 1
            
            # Check validity
            if new_dup <= 1:
                # Valid path from root to current node
                if total_len > ans_len:
                    ans_len = total_len
                    ans_nodes = total_nodes
                elif total_len == ans_len and total_nodes < ans_nodes:
                    ans_nodes = total_nodes
                
                # Also consider paths starting from lower ancestors
                # We need to check all prefixes
                prefix_len = 0
                prefix_nodes = 0
                for i, (l, val_i, freq_i) in enumerate(path):
                    prefix_len += l
                    prefix_nodes += 1
                    # Check if removing prefix makes valid
                    rem_freq = new_freq.copy()
                    rem_freq[val_i] -= 1
                    if rem_freq[val_i] == 0:
                        del rem_freq[val_i]
                    rem_dup = 0
                    for v in rem_freq:
                        if rem_freq[v] == 2:
                            rem_dup += 1
                    if rem_dup <= 1:
                        path_len = total_len - prefix_len
                        path_nodes = total_nodes - prefix_nodes
                        if path_len > ans_len:
                            ans_len = path_len
                            ans_nodes = path_nodes
                        elif path_len == ans_len and path_nodes < ans_nodes:
                            ans_nodes = path_nodes
                
                # Continue recursion
                for nei, l in graph[node]:
                    if nei != parent:
                        dfs2(nei, node, path + [(l, val, new_freq.copy())], new_freq, new_dup, total_len + l, total_nodes + 1)
        
        # Start from root 0
        dfs2(0, -1, [], defaultdict(int), 0, 0, 1)
        
        # If ans_len is still 0, handle case
        if ans_len == 0 and ans_nodes == 0:
            return [0, 0]
        
        return [ans_len, ans_nodes]
