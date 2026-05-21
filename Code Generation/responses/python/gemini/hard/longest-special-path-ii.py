from collections import defaultdict
import sys

# Increase recursion depth for deep trees
sys.setrecursionlimit(200000)

class Solution:
    def longestSpecialPath(self, edges: list[list[int]], nums: list[int]) -> list[int]:
        n = len(nums)
        adj = defaultdict(list)
        for u, v, w in edges:
            adj[u].append((v, w))
            adj[v].append((u, w))
            
        # last_pos stores the last index in the current path where a value appeared
        last_pos = defaultdict(lambda: -1)
        # current_path_prefix_sums stores the distance from root to the i-th node in current path
        prefix_sums = [0]
        # node_depths stores the depth (number of nodes) from root to i-th node in current path
        node_depths = [0]
        
        self.max_len = -1
        self.min_nodes = float('inf')
        
        # path_values_idx tracks the indices in the current recursion stack (path)
        # where specific values are located
        path_indices = []

        def dfs(u, p, current_dist, current_depth, top_invalid_idx):
            val = nums[u]
            
            # The "illegal" boundary is the furthest down index that causes a duplicate.
            # If nums[u] appeared before at index 'prev_idx' in the path, 
            # the path must start after 'prev_idx' to keep it "special" (at most one duplicate).
            # Specifically, if we allow at most one duplicate, the start node must be 
            # at an index > the second-to-last occurrence. 
            # However, the problem says "all node values are distinct, except for at most one value 
            # that may appear twice." This means in the path from ancestor to descendant, 
            # only ONE value can have a count of 2, others must be 1.
            # Actually, the simpler interpretation for a downward path: 
            # If we encounter a value already in our current path, the path "start" 
            # must be moved below the *previous* occurrence of that value to keep the 
            # sub-path valid for the *next* potential duplicate.
            # Wait, the rule is: only one value can repeat. 
            # If we maintain a sliding window [L, R] on the path where all values are distinct, 
            # and we encounter a duplicate of nums[R], moving L to last_pos[nums[R]] + 1 
            # makes the segment [L, R] distinct again. 
            
            prev_idx = last_pos[val]
            # Update the top boundary of our valid window
            new_top = max(top_invalid_idx, prev_idx + 1)
            
            # Calculate length and node count from the valid top to current node
            path_len = current_dist - prefix_sums[new_top]
            num_nodes = (current_depth + 1) - node_depths[new_top]
            
            if path_len > self.max_len:
                self.max_len = path_len
                self.min_nodes = num_nodes
            elif path_len == self.max_len:
                if num_nodes < self.min_nodes:
                    self.min_nodes = num_nodes
            
            # Record current node's info for children
            old_idx = last_pos[val]
            last_pos[val] = len(path_indices)
            path_indices.append(u)
            prefix_sums.append(current_dist)
            node_depths.append(current_depth + 1)
            
            for v, w in adj[u]:
                if v != p:
                    dfs(v, u, current_dist + w, current_depth + 1, new_top)
            
            # Backtrack
            path_indices.pop()
            prefix_sums.pop()
            node_depths.pop()
            last_pos[val] = old_idx

        dfs(0, -1, 0, 0, 0)
        return [self.max_len, self.min_nodes]