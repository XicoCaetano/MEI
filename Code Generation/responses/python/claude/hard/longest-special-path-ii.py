from typing import List
from collections import defaultdict

class Solution:
    def longestSpecialPath(self, edges: List[List[int]], nums: List[int]) -> List[int]:
        n = len(nums)
        graph = defaultdict(list)
        for u, v, w in edges:
            graph[u].append((v, w))
            graph[v].append((u, w))
        
        best_len = 0
        best_nodes = 1
        
        # prefix_dist[i] = distance from root to node at depth i in current path
        prefix_dist = [0] * (n + 1)
        # last two occurrences of each value in the current path (by depth index)
        last_occ = {}  # value -> list of depths where it appears
        
        def dfs(node, parent, depth, path_start_depth):
            nonlocal best_len, best_nodes
            
            val = nums[node]
            
            # Track occurrences of this value
            if val not in last_occ:
                last_occ[val] = []
            last_occ[val].append(depth)
            
            # The path can start at path_start_depth or later
            # If this value appears twice now, the second-to-last occurrence
            # forces the path start to be at least (second_last + 1)
            # If it appears more than twice, we need start > second_last occurrence
            
            occ_list = last_occ[val]
            if len(occ_list) >= 2:
                # second to last occurrence depth
                forced_start = occ_list[-2] + 1
                effective_start = max(path_start_depth, forced_start)
            else:
                effective_start = path_start_depth
            
            # Current path length = prefix_dist[depth+1] - prefix_dist[effective_start]
            cur_len = prefix_dist[depth + 1] - prefix_dist[effective_start]
            cur_nodes = depth - effective_start + 1
            
            if cur_len > best_len or (cur_len == best_len and cur_nodes < best_nodes):
                best_len = cur_len
                best_nodes = cur_nodes
            
            for child, w in graph[node]:
                if child != parent:
                    prefix_dist[depth + 2] = prefix_dist[depth + 1] + w
                    dfs(child, node, depth + 1, effective_start)
            
            # Remove this node's value occurrence
            last_occ[val].pop()
            if not last_occ[val]:
                del last_occ[val]
        
        prefix_dist[1] = 0  # root at depth 0, prefix_dist[1] = dist from root to root = 0
        dfs(0, -1, 0, 0)
        
        return [best_len, best_nodes]