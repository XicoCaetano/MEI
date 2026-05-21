#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int largestInteger(vector<int> nums, int k) {
        int n = nums.size();
        unordered_map<int, int> freq;
        
        // Count frequency of each number in all subarrays of size k
        for (int i = 0; i <= n - k; i++) {
            unordered_map<int, bool> seen;
            for (int j = i; j < i + k; j++) {
                if (!seen[nums[j]]) {
                    freq[nums[j]]++;
                    seen[nums[j]] = true;
                }
            }
        }
        
        // Find the largest number that appears exactly once
        int ans = -1;
        for (auto& p : freq) {
            if (p.second == 1) {
                ans = max(ans, p.first);
            }
        }
        
        return ans;
    }
};