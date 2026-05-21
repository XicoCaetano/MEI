class Solution:
    def beautifulNumbers(self, l: int, r: int) -> int:
        from functools import lru_cache
        
        def count_up_to(n):
            if n == 0:
                return 0
            digits = list(map(int, str(n)))
            m = len(digits)
            
            # The maximum sum of digits for numbers up to 1e9 is 9*9 = 81
            # The maximum product of digits is also 9^9 = 387420489, but we cannot store all.
            # We'll store product and sum in the DP state.
            # Since product can be large, we'll use the fact that we only need to know
            # whether product % sum == 0. We can store product % sum in the state,
            # but sum changes dynamically. So we need to iterate over possible sums.
            
            # Precompute all possible sums (from 1 to 81)
            @lru_cache(None)
            def dp(pos, tight, sum_digits, prod_digits):
                if pos == m:
                    if sum_digits > 0:
                        return 1 if prod_digits % sum_digits == 0 else 0
                    return 0
                
                limit = digits[pos] if tight else 9
                total = 0
                for d in range(limit + 1):
                    if d == 0 and pos == 0:
                        # leading zero skip product/sum
                        new_sum = sum_digits
                        new_prod = prod_digits if prod_digits != 0 else 1
                    else:
                        new_sum = sum_digits + d
                        if prod_digits == 0:
                            new_prod = d
                        else:
                            new_prod = prod_digits * d
                    
                    total += dp(pos + 1, tight and d == limit, new_sum, new_prod)
                return total
            
            # But this DP will be too slow because product can be large.
            # We need a better approach: iterate over all possible sums of digits S (1 to 81)
            # and count numbers where sum of digits = S and product % S == 0.
            
            # We'll do digit DP with state (pos, tight, sum_mod, product_mod, sum_target)
            # But we also need to know if we are tracking sum to a target.
            # Alternative: iterate over target sum from 1 to 81 (max sum for 9 digits)
            # For each target sum, we do DP counting numbers where:
            #   sum_of_digits = target_sum, and product_of_digits % target_sum == 0
            # Then sum over all target sums.
            
            max_sum = 9 * m
            total_count = 0
            
            for target_sum in range(1, max_sum + 1):
                @lru_cache(None)
                def dp_target(pos, tight, current_sum, current_prod_mod):
                    if pos == m:
                        return 1 if (current_sum == target_sum and current_prod_mod == 0) else 0
                    
                    limit = digits[pos] if tight else 9
                    total = 0
                    for d in range(limit + 1):
                        new_tight = tight and d == limit
                        new_sum = current_sum + d
                        if new_sum > target_sum:
                            continue
                        if d == 0 and pos == 0:
                            new_prod_mod = 0 if current_prod_mod == 0 else 1
                        else:
                            if current_prod_mod == 0:
                                new_prod_mod = d % target_sum
                            else:
                                new_prod_mod = (current_prod_mod * d) % target_sum
                        total += dp_target(pos + 1, new_tight, new_sum, new_prod_mod)
                    return total
                
                total_count += dp_target(0, True, 0, 0)
                dp_target.cache_clear()
            
            return total_count
        
        return count_up_to(r) - count_up_to(l - 1)