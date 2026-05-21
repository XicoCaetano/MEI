#include <vector>
#include <unordered_map>
#include <algorithm>
#include <cmath>
using namespace std;

class Solution {
public:
    vector<int> solveQueries(vector<int> nums, vector<int> queries) {
        int n = nums.size();
        unordered_map<int, vector<int>> indices;
        for (int i = 0; i < n; i++)
            indices[nums[i]].push_back(i);
        
        vector<int> answer;
        for (int q : queries) {
            int val = nums[q];
            auto& positions = indices[val];
            if (positions.size() == 1) { answer.push_back(-1); continue; }
            
            auto it = lower_bound(positions.begin(), positions.end(), q);
            int minDist = INT_MAX;
            
            // Check next position
            if (it != positions.end()) {
                int j = *it;
                if (j != q) {
                    int d = abs(j - q);
                    minDist = min(minDist, min(d, n - d));
                }
                auto nxt = next(it);
                if (nxt != positions.end()) {
                    int d = abs(*nxt - q);
                    minDist = min(minDist, min(d, n - d));
                }
            }
            // Check previous position
            if (it != positions.begin()) {
                auto prev_it = prev(it);
                int j = *prev_it;
                int d = abs(j - q);
                minDist = min(minDist, min(d, n - d));
                if (prev_it != positions.begin()) {
                    auto pp = prev(prev_it);
                    int d2 = abs(*pp - q);
                    minDist = min(minDist, min(d2, n - d2));
                }
            }
            // Check wrap-around: first and last in sorted positions
            {
                int first = positions.front();
                int last = positions.back();
                if (first != q) {
                    int d = abs(first - q);
                    minDist = min(minDist, min(d, n - d));
                }
                if (last != q) {
                    int d = abs(last - q);
                    minDist = min(minDist, min(d, n - d));
                }
            }
            
            answer.push_back(minDist == INT_MAX ? -1 : minDist);
        }
        return answer;
    }
};