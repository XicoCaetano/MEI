#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution {
public:
    /**
     * Calculates how many times a number n must be divided by 4 to become 0.
     * This is equivalent to ceil(log4(n + 1)) for n > 0.
     * Specifically, it's the number of operations needed for a single element
     * if we had an infinite supply of other elements to pair it with.
     */
    long long getOperations(long long n) {
        if (n == 0) return 0;
        long long count = 0;
        while (n > 0) {
            n /= 4;
            count++;
        }
        return count;
    }

    /**
     * For a range [l, r], each number x needs k = getOperations(x) reductions.
     * Since one operation reduces TWO numbers, the total operations needed 
     * for the whole array is ceil((sum of operations for each element) / 2).
     */
    long long minOperations(vector<vector<long long>> queries) {
        long long totalResult = 0;

        for (const auto& query : queries) {
            long long l = query[0];
            long long r = query[1];
            long long totalOpsForRange = 0;

            // We need to sum getOperations(i) for i from l to r.
            // getOperations(i) is a step function that changes at powers of 4.
            // Transitions occur at 1, 4, 16, 64... (4^k)
            totalOpsForRange = sumOpsUpTo(r) - sumOpsUpTo(l - 1);
            
            // Each operation covers two reductions.
            totalResult += (totalOpsForRange + 1) / 2;
        }

        return totalResult;
    }

private:
    /**
     * Helper to calculate the prefix sum of getOperations(i) from 1 to n.
     * The value of getOperations(i) is k for 4^{k-1} <= i < 4^k.
     */
    long long sumOpsUpTo(long long n) {
        if (n <= 0) return 0;
        long long sum = 0;
        long long powerOf4 = 1; // 4^0
        long long k = 1;
        
        while (powerOf4 <= n) {
            long long nextPowerOf4 = powerOf4 * 4;
            long long upper = min(n, nextPowerOf4 - 1);
            long long count = upper - powerOf4 + 1;
            
            sum += count * k;
            
            // Check for overflow before multiplying
            if (n / 4 < powerOf4) break; 
            powerOf4 = nextPowerOf4;
            k++;
        }
        return sum;
    }
};