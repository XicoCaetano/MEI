from typing import List
import math

class Solution:
    def minOperations(self, queries: List[List[int]]) -> int:
        
        def get_total_steps(n: int) -> int:
            if n <= 0:
                return 0
            
            total = 0
            k = 1
            lower = 1
            while lower <= n:
                upper = min(n, (1 << (2 * k)) - 1)
                count = upper - lower + 1
                total += count * k
                lower = upper + 1
                k += 1
            return total

        ans = 0
        for l, r in queries:
            total_steps_in_range = get_total_steps(r) - get_total_steps(l - 1)
            ans += (total_steps_in_range + 1) // 2
            
        return ans