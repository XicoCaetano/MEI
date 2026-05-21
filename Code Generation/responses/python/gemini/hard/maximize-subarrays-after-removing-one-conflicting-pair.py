from typing import List
from collections import defaultdict

class Solution:
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:
        adj = defaultdict(list)
        for a, b in conflictingPairs:
            u, v = min(a, b), max(a, b)
            adj[v].append(u)
            
        m1 = [0] * (n + 1)
        m2 = [0] * (n + 1)
        
        id1 = [-1] * (n + 1)
        
        cur_m1, cur_m2 = 0, 0
        pair_to_id = {}
        unique_pairs = []
        
        
        processed_pairs = []
        for v in range(1, n + 1):
            for u in adj[v]:
                pair_idx = len(processed_pairs)
                processed_pairs.append((u, v))
                
                if u > cur_m1:
                    cur_m2 = cur_m1
                    cur_m1 = u
                elif u > cur_m2:
                    cur_m2 = u
        
        f1 = [0] * (n + 1)
        f2 = [0] * (n + 1)
        id_of_f1 = [-1] * (n + 1)
        
        curr_f1, curr_f2 = 0, 0
        curr_id = -1
        

        constraints = [[] for _ in range(n + 1)]
        for i, (a, b) in enumerate(conflictingPairs):
            u, v = min(a, b), max(a, b)
            constraints[v].append((u, i))
            
        f1 = [0] * (n + 1)
        f2 = [0] * (n + 1)
        best_pair_idx = [-1] * (n + 1)
        
        cf1, cf2, cid = 0, 0, -1
        for i in range(1, n + 1):
            for u, idx in constraints[i]:
                if u > cf1:
                    cf2 = cf1
                    cf1 = u
                    cid = idx
                elif u == cf1:
                    cf2 = cf1 # Second max is also cf1
                    cid = -2 # Multiple pairs provide the same max, removing one won't help
                elif u > cf2:
                    cf2 = u
            f1[i] = cf1
            f2[i] = cf2
            best_pair_idx[i] = cid
            
        base_total = 0
        for i in range(1, n + 1):
            base_total += (i - f1[i])
            
        gain = [0] * len(conflictingPairs)
        
        for i in range(1, n + 1):
            idx = best_pair_idx[i]
            if idx >= 0:
                gain[idx] += (f1[i] - f2[i])
        
        return base_total + max(gain) if gain else base_total