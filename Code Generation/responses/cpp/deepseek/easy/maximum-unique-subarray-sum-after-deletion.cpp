#include <vector>
#include <unordered_set>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    int maxSum(vector<int> nums) {
        int n = nums.size();
        int maxSum = INT_MIN;
        
        // Try all possible starting points of subarray
        for (int i = 0; i < n; i++) {
            unordered_set<int> seen;
            int currentSum = 0;
            
            // Extend the subarray from i to j
            for (int j = i; j < n; j++) {
                // If we encounter a duplicate, break this subarray
                if (seen.find(nums[j]) != seen.end()) {
                    break;
                }
                
                seen.insert(nums[j]);
                currentSum += nums[j];
                maxSum = max(maxSum, currentSum);
            }
        }
        
        return maxSum;
    }
};