from functools import lru_cache

class Solution:
    def beautifulNumbers(self, l: int, r: int) -> int:
        # Maximum possible sum of digits for r < 10^9 is 9 * 9 = 81
        # The product of digits can be represented by the powers of 2, 3, 5, 7.
        # Since we only care if product % sum == 0, we can track the remainder
        # for a fixed sum S.
        
        def count_beautiful(n: int) -> int:
            if n == 0:
                return 0
            s_n = str(n)
            length = len(s_n)
            
            total_count = 0
            
            # We iterate over every possible sum of digits S from 1 to 81
            for target_sum in range(1, 82):
                @lru_cache(None)
                def dp(idx, current_sum, current_rem, is_less, is_started):
                    if current_sum > target_sum:
                        return 0
                    
                    if idx == length:
                        return 1 if (current_sum == target_sum and current_rem == 0) else 0
                    
                    res = 0
                    upper = int(s_n[idx]) if not is_less else 9
                    
                    for digit in range(upper + 1):
                        new_is_less = is_less or (digit < upper)
                        new_is_started = is_started or (digit > 0)
                        
                        if not new_is_started:
                            # Leading zeros
                            res += dp(idx + 1, 0, 0, new_is_less, False)
                        else:
                            # Calculate new remainder: (prod * digit) % target_sum
                            # To handle digit 0: if any digit is 0, prod is 0, so rem is 0.
                            new_sum = current_sum + digit
                            if digit == 0:
                                new_rem = 0
                            else:
                                new_rem = (current_rem * digit) % target_sum
                            
                            res += dp(idx + 1, new_sum, new_rem, new_is_less, True)
                    return res
                
                # We need a fresh start for each target_sum, though leading zero logic 
                # can be tricky. A simpler way:
                # If target_sum is fixed, the product must be divisible by target_sum.
                # Initial product remainder for a non-zero start is 1 % target_sum.
                
                @lru_cache(None)
                def solve(idx, current_sum, current_rem, is_less, is_started):
                    if current_sum > target_sum:
                        return 0
                    if idx == length:
                        return 1 if (current_sum == target_sum and current_rem == 0) else 0
                    
                    limit = int(s_n[idx]) if not is_less else 9
                    res = 0
                    for d in range(limit + 1):
                        nxt_less = is_less or (d < limit)
                        if not is_started and d == 0:
                            res += solve(idx + 1, 0, 0, nxt_less, False)
                        else:
                            nxt_sum = current_sum + d
                            if nxt_sum > target_sum: continue
                            
                            if not is_started: # First non-zero digit
                                nxt_rem = d % target_sum
                            else:
                                nxt_rem = (current_rem * d) % target_sum
                            
                            res += solve(idx + 1, nxt_sum, nxt_rem, nxt_less, True)
                    return res

                total_count += solve(0, 0, 0, False, False)
                solve.cache_clear()
                
            return total_count

        return count_beautiful(r) - count_beautiful(l - 1)