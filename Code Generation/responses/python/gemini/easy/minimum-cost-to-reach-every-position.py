from typing import List

class Solution:
    def minCosts(self, cost: List[int]) -> List[int]:
        ans = []
        current_min = float('inf')
        for c in cost:
            if c < current_min:
                current_min = c
            ans.append(current_min)
        return ans