from typing import List
import math

class Solution:
    def minOperations(self, queries: List[List[int]]) -> int:
        def ops_to_zero(n):
            # Number of times we need to divide n by 4 to reach 0
            count = 0
            while n > 0:
                n //= 4
                count += 1
            return count
        
        # For a range [l, r], we need total "reduction steps" across all numbers
        # Each operation handles 2 numbers simultaneously (one step each)
        # So ops = ceil(total_steps / 2)
        # 
        # Key insight: numbers in same "level" band need same number of steps
        # Level k: numbers in [4^(k-1), 4^k - 1] need exactly k steps
        # 
        # We can use prefix sums: for each query [l,r], sum up steps for all nums l..r
        # then ceil(total/2)
        #
        # To compute sum of steps for range [1..n] efficiently:
        # steps(x) = ceil(log4(x+1)) = number of times divide by 4 to reach 0
        
        def steps_sum_1_to_n(n):
            # Sum of ops_to_zero(x) for x in [1..n]
            # ops_to_zero(x) = k iff 4^(k-1) <= x <= 4^k - 1
            # Contribution of level k: count of numbers in [4^(k-1), min(n, 4^k-1)] * k
            if n <= 0:
                return 0
            total = 0
            k = 1
            lo = 1
            while lo <= n:
                hi = 4**k - 1
                count = min(n, hi) - lo + 1
                total += count * k
                k += 1
                lo = 4**(k-1)
            return total
        
        result = 0
        for l, r in queries:
            # Sum of steps for all numbers in [l, r]
            total_steps = steps_sum_1_to_n(r) - steps_sum_1_to_n(l - 1)
            # Each operation reduces 2 numbers by one step each
            result += math.ceil(total_steps / 2)
        
        return result