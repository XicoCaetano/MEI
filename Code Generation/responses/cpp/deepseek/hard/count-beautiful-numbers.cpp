#include <vector>
#include <string>
#include <functional>
#include <cstring>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long beautifulNumbers(int l, int r) {
        return count_le(r) - count_le(l - 1);
    }

    long long count_le(long long n) {
        if (n == 0) return 0;
        string s = to_string(n);
        int len = s.length();
        
        // product range: min product = 1 (digit 1), max product = 9^len
        int max_product = 1;
        for (int i = 0; i < len; i++) max_product *= 9;
        
        // sum range: min sum = 1 (digit 1), max sum = 9*len
        int max_sum = 9 * len;
        
        // DP: pos, sum, product, tight, started
        // product can be large, but we only care about divisibility
        // Use memoization with product reduced by gcd(product, sum) * product / sum?
        // Actually product % sum == 0 is equivalent to product/sum is integer
        // But product can be up to 9^9 ~ 387M, too large for DP array
        // Instead track product and sum, and check divisibility at end
        
        // We'll use direct DP with map memoization for product
        // But we can optimize: product % sum == 0 only depends on product mod sum
        // Actually we need product mod sum == 0, which is product % sum == 0
        // So we need to track product % sum, but sum changes, so need both
        
        // Use memoization with map
        // key: (pos, sum, product_mod_sum? no, product itself is large)
        // We'll use direct product with limits
        
        // Since digits <= 9, product grows exponentially, but state space manageable
        // Let's use DP with memo[10][9*10+1][product?] but product huge
        // Instead use vector of maps for product values
        // Or do digit DP that checks at leaf nodes
        
        vector<vector<unordered_map<int, long long>>> memo(len + 1, 
            vector<unordered_map<int, long long>>(max_sum + 1));
        
        function<long long(int, int, int, bool, bool)> dfs = [&](int pos, int sum, int prod, bool tight, bool started) -> long long {
            if (pos == len) {
                if (started && sum > 0 && prod % sum == 0) return 1;
                return 0;
            }
            if (!tight && started && memo[pos][sum].count(prod)) {
                return memo[pos][sum][prod];
            }
            int limit = tight ? s[pos] - '0' : 9;
            long long res = 0;
            for (int dig = 0; dig <= limit; dig++) {
                bool new_tight = tight && (dig == limit);
                if (!started && dig == 0) {
                    // not started yet
                    res += dfs(pos + 1, 0, 1, new_tight, false);
                } else {
                    int new_sum = sum + dig;
                    int new_prod = (started ? prod * dig : dig);
                    if (new_prod == 0) new_prod = 1; // 0 means product is 0
                    res += dfs(pos + 1, new_sum, new_prod, new_tight, true);
                }
            }
            if (!tight && started) {
                memo[pos][sum][prod] = res;
            }
            return res;
        };
        
        return dfs(0, 0, 1, true, false);
    }
};