from typing import List

class Solution:
    def minCosts(self, cost: List[int]) -> List[int]:
        n = len(cost)
        answer = []
        min_so_far = float('inf')
        for i in range(n):
            min_so_far = min(min_so_far, cost[i])
            answer.append(min_so_far)
        return answer