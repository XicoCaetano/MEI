#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long getOperations(long long n) {
        if (n == 0) return 0;
        long long ops = 0;
        while (n > 0) {
            n /= 4;
            ops++;
        }
        return ops;
    }
    
    long long minOperations(vector<vector<long long>> queries) {
        long long total = 0;
        
        for (auto& q : queries) {
            long long l = q[0];
            long long r = q[1];
            // For range [l, r], we need to convert each number to 0
            // Each operation can reduce two numbers at once
            // The minimum operations = sum of individual operations required for each number, divided by 2, rounded up
            
            long long sum_ops = 0;
            for (long long i = l; i <= r; i++) {
                sum_ops += getOperations(i);
            }
            total += (sum_ops + 1) / 2; // ceiling of sum_ops/2
        }
        
        return total;
    }
};