#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

class Solution {
public:
    long long minimumCost(vector<int> nums, vector<int> cost, int k) {
        int n = nums.size();
        
        vector<long long> prefixSumNums(n + 1, 0);
        vector<long long> prefixSumCost(n + 1, 0);
        
        for (int i = 1; i <= n; i++) {
            prefixSumNums[i] = prefixSumNums[i - 1] + nums[i - 1];
            prefixSumCost[i] = prefixSumCost[i - 1] + cost[i - 1];
        }
        
        vector<long long> dp(n + 1, LLONG_MAX);
        dp[0] = 0;
        
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j < i; j++) {
                long long totalNums = prefixSumNums[i];
                long long costSum = prefixSumCost[i] - prefixSumCost[j];
                long long numSubarrays = j + 1;
                
                dp[i] = min(dp[i], dp[j] + (totalNums + k * numSubarrays) * costSum);
            }
        }
        
        return dp[n];
    }
};