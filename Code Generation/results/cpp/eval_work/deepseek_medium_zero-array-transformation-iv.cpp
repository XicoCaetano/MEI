// task_id: zero-array-transformation-iv
// difficulty: Medium

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>
#include <numeric>
#include <queue>
#include <stack>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>

using namespace std;



// === MODEL RESPONSE ===
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.minZeroArray(vector<int>{1, 2, 3, 2, 6}, vector<vector<int>>{vector<int>{0, 1, 1}, vector<int>{0, 2, 1}, vector<int>{1, 4, 2}, vector<int>{4, 4, 4}, vector<int>{3, 4, 1}, vector<int>{4, 4, 5}}) == 4));
    assert((sol.minZeroArray(vector<int>{2, 0, 2}, vector<vector<int>>{vector<int>{0, 2, 1}, vector<int>{0, 2, 1}, vector<int>{1, 1, 3}}) == 2));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 1, 1}, vector<int>{1, 2, 1}, vector<int>{2, 3, 2}, vector<int>{3, 4, 1}, vector<int>{4, 4, 1}}) == 4));
    assert((sol.minZeroArray(vector<int>{4, 3, 2, 1}, vector<vector<int>>{vector<int>{1, 3, 2}, vector<int>{0, 2, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 2}, vector<int>{0, 9, 3}, vector<int>{0, 9, 4}, vector<int>{0, 9, 5}, vector<int>{0, 9, 6}, vector<int>{0, 9, 7}, vector<int>{0, 9, 8}, vector<int>{0, 9, 9}, vector<int>{0, 9, 10}}) == 4));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{2, 4, 6, 8, 10, 8, 6, 4, 2, 0}, vector<vector<int>>{vector<int>{0, 4, 2}, vector<int>{1, 5, 3}, vector<int>{2, 6, 4}, vector<int>{3, 7, 5}, vector<int>{4, 8, 6}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{2, 6, 2}, vector<int>{1, 7, 3}, vector<int>{0, 9, 4}, vector<int>{3, 5, 5}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 1));
    assert((sol.minZeroArray(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<vector<int>>{vector<int>{0, 4, 10}, vector<int>{5, 9, 10}, vector<int>{0, 9, 5}}) == -1));
    assert((sol.minZeroArray(vector<int>{3, 6, 9, 12, 15}, vector<vector<int>>{vector<int>{0, 0, 3}, vector<int>{1, 1, 6}, vector<int>{2, 2, 9}, vector<int>{3, 3, 12}, vector<int>{4, 4, 15}}) == 5));
    assert((sol.minZeroArray(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<vector<int>>{vector<int>{0, 0, 1}, vector<int>{1, 1, 1}, vector<int>{2, 2, 1}, vector<int>{3, 3, 1}, vector<int>{4, 4, 1}, vector<int>{5, 5, 1}, vector<int>{6, 6, 1}, vector<int>{7, 7, 1}, vector<int>{8, 8, 1}, vector<int>{9, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 6, 7, 8, 9, 10, 11, 12, 13, 14}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 2}, vector<int>{2, 7, 3}, vector<int>{3, 6, 4}, vector<int>{4, 5, 5}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, vector<vector<int>>{vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}}) == 2));
    assert((sol.minZeroArray(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<vector<int>>{vector<int>{0, 2, 3}, vector<int>{3, 5, 3}, vector<int>{6, 8, 3}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 6));
    assert((sol.minZeroArray(vector<int>{8, 7, 6, 5, 4, 3, 2, 1, 0, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 4, 2}, vector<int>{5, 9, 2}, vector<int>{0, 9, 3}, vector<int>{0, 9, 4}}) == 5));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 0, 1}, vector<int>{1, 1, 1}, vector<int>{2, 2, 1}, vector<int>{3, 3, 1}, vector<int>{4, 4, 1}, vector<int>{5, 5, 1}, vector<int>{6, 6, 1}, vector<int>{7, 7, 1}, vector<int>{8, 8, 1}, vector<int>{9, 9, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, vector<vector<int>>{vector<int>{0, 4, 20}, vector<int>{5, 9, 20}, vector<int>{0, 9, 20}, vector<int>{0, 9, 20}, vector<int>{0, 9, 20}, vector<int>{0, 9, 20}, vector<int>{0, 9, 20}, vector<int>{0, 9, 20}, vector<int>{0, 9, 20}, vector<int>{0, 9, 20}}) == 6));
    assert((sol.minZeroArray(vector<int>{10, 20, 30, 40, 50}, vector<vector<int>>{vector<int>{0, 2, 5}, vector<int>{1, 3, 10}, vector<int>{2, 4, 15}, vector<int>{0, 4, 20}}) == -1));
    assert((sol.minZeroArray(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 4, 2}, vector<int>{5, 9, 3}, vector<int>{0, 2, 1}, vector<int>{7, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 0, 10}, vector<int>{1, 1, 10}, vector<int>{2, 2, 10}, vector<int>{3, 3, 10}, vector<int>{4, 4, 10}, vector<int>{5, 5, 10}, vector<int>{6, 6, 10}, vector<int>{7, 7, 10}, vector<int>{8, 8, 10}, vector<int>{9, 9, 10}}) == -1));
    assert((sol.minZeroArray(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 8, 2}, vector<int>{0, 7, 3}, vector<int>{0, 6, 4}, vector<int>{0, 5, 5}}) == 4));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 1));
    assert((sol.minZeroArray(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<vector<int>>{vector<int>{0, 4, 100}, vector<int>{5, 9, 200}, vector<int>{0, 9, 300}, vector<int>{0, 9, 100}, vector<int>{0, 9, 50}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 2}, vector<int>{0, 9, 3}, vector<int>{0, 9, 4}, vector<int>{0, 9, 5}, vector<int>{0, 9, 6}, vector<int>{0, 9, 7}, vector<int>{0, 9, 8}, vector<int>{0, 9, 9}, vector<int>{0, 9, 10}}) == 4));
    assert((sol.minZeroArray(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<vector<int>>{vector<int>{0, 0, 1}, vector<int>{1, 1, 3}, vector<int>{2, 2, 5}, vector<int>{3, 3, 7}, vector<int>{4, 4, 9}, vector<int>{5, 5, 11}, vector<int>{6, 6, 13}, vector<int>{7, 7, 15}, vector<int>{8, 8, 17}, vector<int>{9, 9, 19}}) == 10));
    assert((sol.minZeroArray(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<vector<int>>{vector<int>{0, 4, 5}, vector<int>{5, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}, vector<int>{0, 9, 5}}) == -1));
    assert((sol.minZeroArray(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 3));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 1));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 0, 1}, vector<int>{1, 1, 1}, vector<int>{2, 2, 1}, vector<int>{3, 3, 1}, vector<int>{4, 4, 1}, vector<int>{5, 5, 1}, vector<int>{6, 6, 1}, vector<int>{7, 7, 1}, vector<int>{8, 8, 1}, vector<int>{9, 9, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<vector<int>>{vector<int>{0, 1, 1}, vector<int>{2, 3, 2}, vector<int>{4, 5, 3}, vector<int>{6, 7, 4}, vector<int>{8, 9, 5}, vector<int>{0, 9, 1}, vector<int>{2, 7, 2}, vector<int>{1, 8, 3}, vector<int>{3, 6, 4}, vector<int>{4, 5, 5}}) == 5));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 4, 2}, vector<int>{5, 9, 3}, vector<int>{0, 2, 1}, vector<int>{7, 9, 1}, vector<int>{0, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<vector<int>>{vector<int>{0, 1, 2}, vector<int>{1, 2, 2}, vector<int>{2, 3, 2}, vector<int>{3, 4, 2}, vector<int>{4, 5, 2}, vector<int>{5, 6, 2}, vector<int>{6, 7, 2}, vector<int>{7, 8, 2}, vector<int>{8, 9, 2}, vector<int>{9, 9, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{1, 5, 1}, vector<int>{2, 6, 1}, vector<int>{3, 7, 1}, vector<int>{4, 8, 1}, vector<int>{5, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 6));
    assert((sol.minZeroArray(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<vector<int>>{vector<int>{0, 4, 5}, vector<int>{0, 4, 10}, vector<int>{0, 4, 15}, vector<int>{0, 4, 20}, vector<int>{0, 4, 25}, vector<int>{5, 9, 30}, vector<int>{5, 9, 35}, vector<int>{5, 9, 40}, vector<int>{5, 9, 45}, vector<int>{5, 9, 50}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}}) == -1));
    assert((sol.minZeroArray(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 3));
    assert((sol.minZeroArray(vector<int>{3, 6, 9, 12, 15, 18, 21, 24, 27, 30}, vector<vector<int>>{vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}, vector<int>{0, 9, 3}}) == 10));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 8, 1}, vector<int>{0, 7, 1}, vector<int>{0, 6, 1}, vector<int>{0, 5, 1}, vector<int>{0, 4, 1}, vector<int>{0, 3, 1}, vector<int>{0, 2, 1}, vector<int>{0, 1, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}, vector<int>{5, 4, 1}, vector<int>{6, 3, 1}, vector<int>{7, 2, 1}, vector<int>{8, 1, 1}, vector<int>{9, 0, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<vector<int>>{vector<int>{0, 4, 2}, vector<int>{0, 4, 2}, vector<int>{0, 4, 2}, vector<int>{5, 9, 2}, vector<int>{5, 9, 2}, vector<int>{5, 9, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}, vector<int>{5, 4, 1}, vector<int>{6, 3, 1}, vector<int>{7, 2, 1}, vector<int>{8, 1, 1}, vector<int>{9, 0, 1}}) == 1));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}, vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 5));
    assert((sol.minZeroArray(vector<int>{20, 20, 20, 20, 20, 20, 20, 20, 20, 20}, vector<vector<int>>{vector<int>{0, 9, 2}, vector<int>{1, 8, 2}, vector<int>{2, 7, 2}, vector<int>{3, 6, 2}, vector<int>{4, 5, 2}, vector<int>{5, 4, 2}, vector<int>{6, 3, 2}, vector<int>{7, 2, 2}, vector<int>{8, 1, 2}, vector<int>{9, 0, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 1, 2}, vector<int>{1, 2, 2}, vector<int>{2, 3, 2}, vector<int>{3, 4, 2}, vector<int>{4, 5, 2}, vector<int>{5, 6, 2}, vector<int>{6, 7, 2}, vector<int>{7, 8, 2}, vector<int>{8, 9, 2}, vector<int>{9, 9, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 20, 30, 40, 50}, vector<vector<int>>{vector<int>{0, 0, 10}, vector<int>{1, 1, 10}, vector<int>{2, 2, 10}, vector<int>{3, 3, 10}, vector<int>{4, 4, 10}, vector<int>{0, 4, 5}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 8, 1}, vector<int>{1, 8, 1}, vector<int>{1, 7, 1}, vector<int>{2, 7, 1}, vector<int>{2, 6, 1}, vector<int>{3, 6, 1}, vector<int>{3, 5, 1}, vector<int>{4, 5, 1}}) == 1));
    assert((sol.minZeroArray(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<vector<int>>{vector<int>{0, 9, 2}, vector<int>{1, 8, 2}, vector<int>{2, 7, 2}, vector<int>{3, 6, 2}, vector<int>{4, 5, 2}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 6));
    assert((sol.minZeroArray(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<vector<int>>{vector<int>{0, 2, 1}, vector<int>{3, 5, 1}, vector<int>{6, 8, 1}, vector<int>{0, 9, 3}}) == 4));
    assert((sol.minZeroArray(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<vector<int>>{vector<int>{0, 0, 9}, vector<int>{1, 1, 8}, vector<int>{2, 2, 7}, vector<int>{3, 3, 6}, vector<int>{4, 4, 5}, vector<int>{5, 5, 4}, vector<int>{6, 6, 3}, vector<int>{7, 7, 2}, vector<int>{8, 8, 1}, vector<int>{9, 9, 0}}) == 9));
    assert((sol.minZeroArray(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 3, 2}, vector<int>{1, 2, 1}, vector<int>{2, 5, 3}, vector<int>{0, 6, 1}, vector<int>{1, 4, 4}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 10}, vector<int>{1, 8, 8}, vector<int>{2, 7, 6}, vector<int>{3, 6, 4}, vector<int>{4, 5, 2}, vector<int>{0, 9, 10}, vector<int>{1, 8, 8}, vector<int>{2, 7, 6}, vector<int>{3, 6, 4}, vector<int>{4, 5, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}, vector<int>{5, 4, 1}, vector<int>{6, 3, 1}, vector<int>{7, 2, 1}, vector<int>{8, 1, 1}, vector<int>{9, 0, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{7, 7, 7, 7, 7, 7, 7}, vector<vector<int>>{vector<int>{0, 6, 1}, vector<int>{1, 5, 2}, vector<int>{2, 4, 3}, vector<int>{3, 3, 4}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{1, 5, 2}, vector<int>{2, 6, 3}, vector<int>{3, 7, 4}, vector<int>{4, 8, 5}, vector<int>{5, 9, 6}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 2, 3}, vector<int>{1, 3, 3}, vector<int>{2, 4, 3}, vector<int>{3, 5, 3}, vector<int>{4, 6, 3}, vector<int>{5, 7, 3}, vector<int>{6, 8, 3}, vector<int>{7, 9, 3}, vector<int>{8, 9, 3}, vector<int>{9, 9, 3}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 4, 2}, vector<int>{0, 4, 2}, vector<int>{0, 4, 2}, vector<int>{0, 4, 2}, vector<int>{0, 4, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 20, 30, 40, 50}, vector<vector<int>>{vector<int>{0, 4, 5}, vector<int>{1, 3, 10}, vector<int>{2, 2, 20}, vector<int>{3, 4, 15}}) == -1));
    assert((sol.minZeroArray(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<vector<int>>{vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}, vector<int>{0, 9, 100}}) == 10));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 8, 1}, vector<int>{0, 7, 1}, vector<int>{0, 6, 1}, vector<int>{0, 5, 1}, vector<int>{0, 4, 1}, vector<int>{0, 3, 1}, vector<int>{0, 2, 1}, vector<int>{0, 1, 1}, vector<int>{0, 0, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 2));
    assert((sol.minZeroArray(vector<int>{100, 100, 100, 100, 100}, vector<vector<int>>{vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}, vector<int>{0, 4, 10}}) == 10));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 1, 1}, vector<int>{1, 2, 1}, vector<int>{2, 3, 1}, vector<int>{3, 4, 1}, vector<int>{4, 5, 1}, vector<int>{5, 6, 1}, vector<int>{6, 7, 1}, vector<int>{7, 8, 1}, vector<int>{8, 9, 1}, vector<int>{9, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, vector<vector<int>>{vector<int>{0, 9, 3}, vector<int>{0, 9, 2}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 2}, vector<int>{2, 7, 3}, vector<int>{3, 6, 4}, vector<int>{4, 5, 5}, vector<int>{0, 4, 6}, vector<int>{5, 9, 7}}) == -1));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 4, 3, 2, 1, 0, 1, 2, 3, 4}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 4, 2}, vector<int>{5, 9, 3}, vector<int>{2, 7, 1}, vector<int>{3, 6, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{7, 7, 7, 7, 7, 7, 7}, vector<vector<int>>{vector<int>{0, 6, 1}, vector<int>{1, 5, 2}, vector<int>{2, 4, 3}, vector<int>{3, 6, 4}, vector<int>{0, 3, 5}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 8, 1}, vector<int>{0, 7, 1}, vector<int>{0, 6, 1}, vector<int>{0, 5, 1}, vector<int>{0, 4, 1}, vector<int>{0, 3, 1}, vector<int>{0, 2, 1}, vector<int>{0, 1, 1}, vector<int>{0, 0, 1}}) == 1));
    assert((sol.minZeroArray(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{1, 8, 1}, vector<int>{2, 7, 1}, vector<int>{3, 6, 1}, vector<int>{4, 5, 1}, vector<int>{5, 4, 1}, vector<int>{6, 3, 1}, vector<int>{7, 2, 1}, vector<int>{8, 1, 1}, vector<int>{9, 0, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{100, 0, 100, 0, 100}, vector<vector<int>>{vector<int>{0, 4, 50}, vector<int>{1, 3, 25}, vector<int>{0, 4, 25}, vector<int>{0, 4, 25}, vector<int>{0, 4, 1}}) == 4));
    assert((sol.minZeroArray(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<vector<int>>{vector<int>{0, 1, 2}, vector<int>{1, 2, 2}, vector<int>{2, 3, 2}, vector<int>{3, 4, 2}, vector<int>{4, 5, 2}, vector<int>{5, 6, 2}, vector<int>{6, 7, 2}, vector<int>{7, 8, 2}, vector<int>{8, 9, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 0));
    assert((sol.minZeroArray(vector<int>{5, 4, 3, 2, 1, 0, 1, 2, 3, 4}, vector<vector<int>>{vector<int>{0, 2, 1}, vector<int>{1, 3, 2}, vector<int>{2, 4, 3}, vector<int>{3, 5, 4}, vector<int>{4, 6, 5}, vector<int>{5, 7, 6}, vector<int>{6, 8, 7}, vector<int>{7, 9, 8}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{1, 3, 2}, vector<int>{2, 2, 3}, vector<int>{0, 4, 1}}) == -1));
    assert((sol.minZeroArray(vector<int>{6, 6, 6, 6, 6, 6, 6, 6, 6, 6}, vector<vector<int>>{vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 6));
    assert((sol.minZeroArray(vector<int>{15, 10, 5, 10, 15}, vector<vector<int>>{vector<int>{0, 4, 5}, vector<int>{1, 3, 3}, vector<int>{2, 2, 2}, vector<int>{0, 4, 4}}) == -1));
    assert((sol.minZeroArray(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<vector<int>>{vector<int>{0, 4, 2}, vector<int>{5, 9, 2}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 10));
    assert((sol.minZeroArray(vector<int>{3, 3, 3, 3, 3, 3}, vector<vector<int>>{vector<int>{0, 5, 1}, vector<int>{1, 4, 1}, vector<int>{2, 3, 1}, vector<int>{0, 2, 2}, vector<int>{3, 5, 2}}) == 5));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 4, 1}, vector<int>{5, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 4, 1}}) == 8));
    assert((sol.minZeroArray(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<vector<int>>{vector<int>{0, 9, 2}, vector<int>{1, 8, 2}, vector<int>{2, 7, 2}, vector<int>{3, 6, 2}, vector<int>{4, 5, 2}}) == -1));
    assert((sol.minZeroArray(vector<int>{20, 18, 16, 14, 12, 10, 8, 6, 4, 2}, vector<vector<int>>{vector<int>{0, 2, 3}, vector<int>{1, 3, 3}, vector<int>{2, 4, 3}, vector<int>{3, 5, 3}, vector<int>{4, 6, 3}, vector<int>{5, 7, 3}, vector<int>{6, 8, 3}, vector<int>{7, 9, 3}, vector<int>{8, 9, 3}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 4, 3, 2, 1}, vector<vector<int>>{vector<int>{0, 4, 1}, vector<int>{0, 3, 2}, vector<int>{1, 2, 3}, vector<int>{2, 4, 4}, vector<int>{3, 4, 5}}) == -1));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 0, 5}, vector<int>{1, 1, 5}, vector<int>{2, 2, 5}, vector<int>{3, 3, 5}, vector<int>{4, 4, 5}, vector<int>{0, 4, 5}}) == 5));
    assert((sol.minZeroArray(vector<int>{1, 3, 5, 7, 9, 7, 5, 3, 1}, vector<vector<int>>{vector<int>{0, 8, 1}, vector<int>{1, 7, 2}, vector<int>{2, 6, 3}, vector<int>{3, 5, 4}, vector<int>{4, 4, 5}, vector<int>{0, 8, 1}}) == 4));
    assert((sol.minZeroArray(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<vector<int>>{vector<int>{0, 9, 10}, vector<int>{1, 8, 20}, vector<int>{2, 7, 30}, vector<int>{3, 6, 40}, vector<int>{4, 5, 50}, vector<int>{0, 9, 10}}) == -1));
    assert((sol.minZeroArray(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<vector<int>>{vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}, vector<int>{0, 9, 2}}) == 10));
    assert((sol.minZeroArray(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<vector<int>>{vector<int>{0, 4, 2}, vector<int>{5, 9, 2}, vector<int>{2, 7, 2}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}, vector<int>{0, 9, 1}}) == 6));
    assert((sol.minZeroArray(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<vector<int>>{vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}, vector<int>{0, 9, 10}}) == -1));

    cout << "All tests passed for zero-array-transformation-iv" << endl;
    return 0;
}
