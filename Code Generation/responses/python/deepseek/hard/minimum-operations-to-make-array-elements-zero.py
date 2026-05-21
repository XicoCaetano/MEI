from typing import List

class Solution:
    def minOperations(self, queries: List[List[int]]) -> int:
        def count_ops_for_interval(l, r):
            # Count total operations needed for numbers from l to r
            total_ops = 0
            pow4 = 1
            # We need to consider groups: numbers requiring k operations
            # Number x requires k operations if 4^(k-1) <= x < 4^k
            # Actually, more precisely: number lies in [4^(k-1), 4^k) needs k operations
            # Because:
            # - Numbers in [1, 4): need 1 operation (can be reduced to 0 in one step)
            # - Numbers in [4, 16): need 2 operations
            # - Numbers in [16, 64): need 3 operations, etc.
            
            # For a given k, how many numbers in [l, r] fall into [4^(k-1), 4^k)?
            # Special case: for k=1, lower bound is 1, not 4^0=1
            k = 1
            while True:
                start = pow4
                if k == 1:
                    start = 1
                else:
                    start = pow4
                
                end = pow4 * 4  # Not including end
                
                if start > r:
                    break
                
                # Count numbers in [max(l, start), min(r, end-1)]
                cnt_start = max(l, start)
                cnt_end = min(r, end - 1)
                
                if cnt_start <= cnt_end:
                    total_ops += k * (cnt_end - cnt_start + 1)
                
                pow4 *= 4
                k += 1
            
            # Each operation reduces two numbers, so number of operations is ceiling(total/2)
            return (total_ops + 1) // 2
        
        total = 0
        for l, r in queries:
            total += count_ops_for_interval(l, r)
        return total
