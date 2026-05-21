#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution {
public:
    int largestInteger(vector<int> nums, int k) {
        int n = nums.size();
        unordered_map<int, int> count;
        
        for (int i = 0; i <= n - k; i++) {
            unordered_map<int, bool> seen;
            for (int j = i; j < i + k; j++) {
                if (!seen[nums[j]]) {
                    count[nums[j]]++;
                    seen[nums[j]] = true;
                }
            }
        }
        
        int ans = -1;
        for (auto& [val, cnt] : count) {
            if (cnt == 1) ans = max(ans, val);
        }
        return ans;
    }
};