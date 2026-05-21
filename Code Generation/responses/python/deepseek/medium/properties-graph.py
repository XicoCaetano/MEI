from typing import List

class Solution:
    def numberOfComponents(self, properties: List[List[int]], k: int) -> int:
        n = len(properties)
        
        # Convert each property list to a set for efficient intersection
        property_sets = [set(row) for row in properties]
        
        # Build adjacency list
        adj = [[] for _ in range(n)]
        
        for i in range(n):
            for j in range(i + 1, n):
                # Compute intersection size
                intersect_count = len(property_sets[i] & property_sets[j])
                if intersect_count >= k:
                    adj[i].append(j)
                    adj[j].append(i)
        
        # Find connected components using BFS/DFS
        visited = [False] * n
        
        def dfs(node):
            stack = [node]
            visited[node] = True
            while stack:
                curr = stack.pop()
                for neighbor in adj[curr]:
                    if not visited[neighbor]:
                        visited[neighbor] = True
                        stack.append(neighbor)
        
        components = 0
        for i in range(n):
            if not visited[i]:
                components += 1
                dfs(i)
        
        return components