#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    int minZeroArray(vector<int> nums, vector<vector<int>> queries) {
        int n = nums.size();
        int m = queries.size();
        
        // Check if it's already zero
        bool allZero = true;
        for (int num : nums) {
            if (num != 0) {
                allZero = false;
                break;
            }
        }
        if (allZero) return 0;
        
        // Binary search on k
        int left = 1, right = m, ans = -1;
        
        while (left <= right) {
            int mid = left + (right - left) / 2;
            
            // Check if first mid queries can make array zero
            vector<int> diff(n + 1, 0);
            
            // Apply the first mid queries
            for (int i = 0; i < mid; i++) {
                int l = queries[i][0];
                int r = queries[i][1];
                int val = queries[i][2];
                diff[l] += val;
                diff[r + 1] -= val;
            }
            
            // Compute prefix sum to get actual decrements
            vector<int> decrement(n, 0);
            int prefix = 0;
            for (int i = 0; i < n; i++) {
                prefix += diff[i];
                decrement[i] = prefix;
            }
            
            // Check if nums can be made zero
            bool possible = true;
            for (int i = 0; i < n; i++) {
                if (nums[i] > decrement[i]) {
                    possible = false;
                    break;
                }
            }
            
            if (possible) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }
        
        return ans;
    }
};