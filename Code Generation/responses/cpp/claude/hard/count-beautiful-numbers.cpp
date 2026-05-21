#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Digit DP: count beautiful numbers in [1, n]
    // State: pos, tight, prod, sum
    // prod can be large but we only need prod % sum, however sum varies...
    // Instead, track sum (max 9*9=81) and prod % lcm(1..81)
    // lcm(1..81) is huge. Alternative: track prod up to some limit.
    // 
    // Key insight: sum of digits <= 9*9 = 81, product of digits <= 9^9
    // We need product % sum == 0. 
    // Track sum directly (<=81) and product mod LCM(1..81).
    // LCM(1..81) = LCM of all numbers 1..81
    // That's too large. 
    //
    // Better: since sum <= 81, we only need product mod lcm(1..81).
    // But lcm(1..81) ~ 10^35. Not feasible.
    //
    // Alternative approach: track (sum, product mod P) where P = lcm(1..81)
    // is too large. 
    //
    // Since product <= 9^9 < 10^9 and sum <= 81, and we need prod % sum == 0,
    // we can track product directly but cap it. If product > 81*81=6561 and 
    // we know it's divisible appropriately... not straightforward.
    //
    // Actually product of up to 9 digits each 1-9: max = 9^9 = 387,420,489
    // We can't store full product in DP state.
    // 
    // Key: we need prod % sum == 0. Sum <= 81. 
    // Track (sum, prod % 2520) where 2520 = lcm(1..10) -- but sum can be up to 81.
    // lcm(1..81): we need divisibility by any number up to 81.
    // lcm(1..81) is astronomically large.
    //
    // Practical approach: since n < 10^9 (9 digits), brute force with memoization
    // on (pos, tight, sum, prod_mod_M) where M = lcm of primes up to 81.
    // M = 2^6 * 3^4 * 5^2 * 7^2 * 11 * 13 * 17 * 19 * 23 * 29 * 31 * 37 * 41 
    //     * 43 * 47 * 53 * 59 * 61 * 67 * 71 * 73 * 79 = way too large
    //
    // Simpler: just track (sum, product) but product mod lcm(1..81).
    // Since this is infeasible, use a different state compression:
    // Note sum <= 81, product's relevant part for divisibility by sum:
    // Track product mod (lcm of all possible sums) = lcm(1..81).
    // 
    // Feasible alternative: since digits are 0-9 and at most 9 digits,
    // track product directly with early termination. Product has at most
    // 9^9 ~ 4*10^8 values which is too many states.
    //
    // Practical solution: memoize on (pos, tight, sum, prod) but limit
    // prod to only what matters. Since sum<=81, store prod % lcm but
    // use the fact that once prod >= some threshold and sum divides it...
    // 
    // Actually cleanest: digit DP with state (pos, tight, sum, prod)
    // where prod is stored mod LCM(1..81). We compute this LCM.
    
    long long M; // lcm(1..81) mod something -- we'll use 720720 = lcm(1..12)*... 
    // lcm(1..36) = 144403552893600 -- still large
    // 
    // Final practical approach: since r < 10^9, just iterate. 
    // But r can be 10^9, so ~10^9 iterations is too slow.
    //
    // Digit DP with state: (pos, tight, sum, prod_mod_2520)
    // 2520 = lcm(1..10). But sum can be up to 81, so we need divisibility by up to 81.
    // Use M = lcm(1..81). Let's compute it properly and see.
    // Actually for competitive programming, M = 720720 = lcm(1..12) works if all sums<=12,
    // but sums can be up to 81.
    // 
    // We'll compute lcm(1..81) and use __int128 or just use the actual value mod something.
    // 
    // Simplest correct solution: memoize on (pos, tight, sum, prod) where
    // prod is capped/tracked as prod mod LCM. We compute LCM(1..81).
    
    map<tuple<int,bool,int,long long>, long long> memo;
    string digits;
    long long LCM;
    
    long long gcd(long long a, long long b) { return b ? gcd(b, a%b) : a; }
    long long lcm(long long a, long long b) { return a / gcd(a,b) * b; }
    
    long long dp(int pos, bool tight, int sum, long long prod) {
        if (pos == (int)digits.size()) {
            if (sum == 0) return 0; // shouldn't happen for positive numbers but handle
            return (prod % sum == 0) ? 1 : 0;
        }
        
        auto key = make_tuple(pos, tight, sum, prod);
        auto it = memo.find(key);
        if (it != memo.end()) return it->second;
        
        int limit = tight ? (digits[pos] - '0') : 9;
        long long res = 0;
        
        for (int d = 0; d <= limit; d++) {
            bool new_tight = tight && (d == limit);
            int new_sum = sum + d;
            long long new_prod = (d == 0) ? 0 : (prod == 0 && pos == 0 ? d : (prod == 0 ? 0 : prod * d % LCM));
            // Handle leading zeros: if prod==0 and d==0, it's a leading zero
            // Actually we need to track whether we've started the number
            // Let's re-think with a "started" flag embedded differently
            // For now: prod=0 means either leading zeros or actual zero digit
            if (prod == -1) { // leading zero state
                if (d == 0) {
                    res += dp(pos+1, new_tight, 0, -1);
                } else {
                    res += dp(pos+1, new_tight, d, d);
                }
            } else {
                new_prod = (d == 0) ? 0 : (prod * d % LCM);
                res += dp(pos+1, new_tight, new_sum, new_prod);
            }
        }
        
        memo[key] = res;
        return res;
    }
    
    long long count_le(long long n) {
        memo.clear();
        digits = to_string(n);
        return dp2(0, true, 0, -1LL); // -1 = leading zero marker
    }
    
    // Rewrite cleanly with leading zero flag
    map<tuple<int,bool,int,long long,bool>, long long> memo2;
    
    long long dp2(int pos, bool tight, int sum, long long prod, bool started) {
        if (pos == (int)digits.size()) {
            if (!started) return 0;
            if (sum == 0) return 0;
            return (prod % sum == 0) ? 1 : 0;
        }
        
        auto key = make_tuple(pos, tight, sum, prod, started);
        auto it = memo2.find(key);
        if (it != memo2.end()) return it->second;
        
        int limit = tight ? (digits[pos] - '0') : 9;
        long long res = 0;
        
        for (int d = 0; d <= limit; d++) {
            bool new_tight = tight && (d == limit);
            if (!started && d == 0) {
                res += dp2(pos+1, new_tight, 0, 1, false);
            } else {
                int new_sum = sum + d;
                long long new_prod = started ? (prod * d % LCM) : d;
                if (d == 0) new_prod = 0;
                res += dp2(pos+1, new_tight, new_sum, new_prod, true);
            }
        }
        
        return memo2[key] = res;
    }

    long long beautifulNumbers(int l, int r) {
        // Compute LCM(1..81)
        LCM = 1;
        for (int i = 2; i <= 81; i++) LCM = lcm(LCM, (long long)i);
        
        memo2.clear();
        digits = to_string(r);
        long long ans_r = dp2(0, true, 0, 1, false);
        
        memo2.clear();
        digits = to_string(l - 1);
        long long ans_l = dp2(0, true, 0, 1, false);
        
        return ans_r - ans_l;
    }
};