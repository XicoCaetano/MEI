from functools import lru_cache

class Solution:
    def beautifulNumbers(self, l: int, r: int) -> int:
        def count_up_to(n):
            digits = list(map(int, str(n)))
            length = len(digits)
            
            # digit_product can be large but bounded: max 9^9 = 387420489
            # digit_sum bounded: max 9*9 = 81
            # We track (product, sum) but product can be huge
            # Instead track product mod lcm(1..81) and actual sum
            # lcm(1..81) - use this to check divisibility by any sum <= 81
            
            import math
            lcm_val = 1
            for i in range(1, 82):
                lcm_val = lcm_val * i // math.gcd(lcm_val, i)
            
            @lru_cache(maxsize=None)
            def dp(pos, prod_mod, digit_sum, tight, started):
                if pos == length:
                    if not started:
                        return 0
                    if digit_sum == 0:
                        return 0
                    # Check if prod_mod % digit_sum == 0
                    return 1 if prod_mod % digit_sum == 0 else 0
                
                limit = digits[pos] if tight else 9
                result = 0
                
                for d in range(0, limit + 1):
                    new_tight = tight and (d == limit)
                    if not started and d == 0:
                        result += dp(pos + 1, 1, 0, new_tight, False)
                    else:
                        new_prod = (prod_mod * d) % lcm_val
                        new_sum = digit_sum + d
                        result += dp(pos + 1, new_prod, new_sum, new_tight, True)
                
                return result
            
            ans = dp(0, 1, 0, True, False)
            dp.cache_clear()
            return ans
        
        return count_up_to(r) - count_up_to(l - 1)