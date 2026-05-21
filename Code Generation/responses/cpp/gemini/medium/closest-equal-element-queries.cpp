#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>

using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int> nums, vector<int> queries) {
        int n = nums.size();
        unordered_map<int, vector<int>> positions;
        
        // Group all indices by their value
        for (int i = 0; i < n; ++i) {
            positions[nums[i]].push_back(i);
        }
        
        vector<int> answer;
        answer.reserve(queries.size());
        
        for (int q_idx : queries) {
            int val = nums[q_idx];
            const vector<int>& indices = positions[val];
            
            // If the element appears only once, there's no "other" index
            if (indices.size() <= 1) {
                answer.push_back(-1);
                continue;
            }
            
            // Find the position of q_idx within the sorted list of indices for this value
            auto it = lower_bound(indices.begin(), indices.end(), q_idx);
            int idx_in_pos = distance(indices.begin(), it);
            
            int min_dist = n; // Initialize with max possible distance
            
            // The nearest identical elements in a circular array are either:
            // 1. The immediate neighbor in the sorted indices list (linear distance)
            // 2. The wrapping neighbor (distance across the array boundary)
            
            // Check neighbor to the left (circularly)
            int left_idx = (idx_in_pos - 1 + indices.size()) % indices.size();
            int dist_left = abs(q_idx - indices[left_idx]);
            dist_left = min(dist_left, n - dist_left);
            min_dist = min(min_dist, dist_left);
            
            // Check neighbor to the right (circularly)
            int right_idx = (idx_in_pos + 1) % indices.size();
            int dist_right = abs(q_idx - indices[right_idx]);
            dist_right = min(dist_right, n - dist_right);
            min_dist = min(min_dist, dist_right);
            
            answer.push_back(min_dist);
        }
        
        return answer;
    }
};