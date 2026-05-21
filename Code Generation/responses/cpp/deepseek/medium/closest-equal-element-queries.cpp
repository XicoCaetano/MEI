#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int> nums, vector<int> queries) {
        int n = nums.size();
        unordered_map<int, vector<int>> indices;
        
        // Group indices by value
        for (int i = 0; i < n; i++) {
            indices[nums[i]].push_back(i);
        }
        
        vector<int> result;
        
        for (int q : queries) {
            int val = nums[q];
            vector<int>& positions = indices[val];
            
            // If only one occurrence, answer is -1
            if (positions.size() <= 1) {
                result.push_back(-1);
                continue;
            }
            
            // Binary search to find position of q in positions
            auto it = lower_bound(positions.begin(), positions.end(), q);
            int idx = it - positions.begin();
            int m = positions.size();
            
            int minDist = INT_MAX;
            
            // Check left neighbor (circular)
            int leftIdx = (idx - 1 + m) % m;
            int distLeft = (q - positions[leftIdx] + n) % n;
            minDist = min(minDist, distLeft);
            
            // Check right neighbor (circular)
            int rightIdx = (idx + 1) % m;
            int distRight = (positions[rightIdx] - q + n) % n;
            minDist = min(minDist, distRight);
            
            result.push_back(minDist);
        }
        
        return result;
    }
};