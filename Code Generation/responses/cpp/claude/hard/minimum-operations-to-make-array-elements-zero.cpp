#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    // Sum of operations needed for each number from 1 to n
    // where ops(x) = number of times you divide x by 4 until 0
    long long getOperations(long long n) {
        if (n <= 0) return 0;
        long long total = 0;
        long long lo = 1;
        long long k = 1;
        // Numbers in [4^(k-1), 4^k - 1] each need k ops
        // 4^0=1..3, 4^1=4..15, 4^2=16..63, ...
        while (lo <= n) {
            // hi = lo * 4 - 1, but lo starts at 4^(k-1)
            // range size = 3 * 4^(k-1)
            long long hi = lo * 4 - 1;
            long long actualHi = min(hi, n);
            total += k * (actualHi - lo + 1);
            k++;
            lo = hi + 1;
        }
        return total;
    }
    
    long long minOperations(vector<vector<long long>> queries) {
        long long ans = 0;
        for (auto& q : queries) {
            long long l = q[0], r = q[1];
            long long totalSingleOps = getOperations(r) - getOperations(l - 1);
            ans += (totalSingleOps + 1) / 2;
        }
        return ans;
    }
};