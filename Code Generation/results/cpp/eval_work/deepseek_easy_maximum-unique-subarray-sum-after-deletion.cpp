// task_id: maximum-unique-subarray-sum-after-deletion
// difficulty: Easy

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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.maxSum(vector<int>{-1, 2, -3, 4, -5}) == 6));
    assert((sol.maxSum(vector<int>{-10, 1, 20, -30, 40, -50, 60}) == 121));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1}) == 1));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1}) == 1));
    assert((sol.maxSum(vector<int>{100, -100, 50, -50, 25, -25}) == 175));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50}) == 150));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5}) == 5));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5}) == -1));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0}) == 0));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5}) == 15));
    assert((sol.maxSum(vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3}) == 6));
    assert((sol.maxSum(vector<int>{100, -100, 100, -100, 100}) == 100));
    assert((sol.maxSum(vector<int>{10, -2, 3, 4, -1, 2}) == 19));
    assert((sol.maxSum(vector<int>{1, 2, 2, 3, 4, 5, 5, 6}) == 21));
    assert((sol.maxSum(vector<int>{-1, 2, -3, 4, -5, 6}) == 12));
    assert((sol.maxSum(vector<int>{1, 2, 3, 2, 1}) == 6));
    assert((sol.maxSum(vector<int>{1, 2, -1, -2, 1, 0, -1}) == 3));
    assert((sol.maxSum(vector<int>{50, 50, 50, -50, 50, -50, 50}) == 50));
    assert((sol.maxSum(vector<int>{1, 1, 0, 1, 1}) == 1));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10}) == 55));
    assert((sol.maxSum(vector<int>{10, 20, 30, 10, 40, 50, 20, 60}) == 210));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == 55));
    assert((sol.maxSum(vector<int>{5, -5, 10, -10, 15, -15, 20, -20, 25, -25}) == 75));
    assert((sol.maxSum(vector<int>{-5, -1, -3, -4, -2, -3, -1, -2, -4}) == -1));
    assert((sol.maxSum(vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 210));
    assert((sol.maxSum(vector<int>{3, -1, 4, -1, 5, 9, -2, 6, 5, 3, 5, -9, 7, 9, -3, 2, 3, 8, 4, 6}) == 44));
    assert((sol.maxSum(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}) == 1));
    assert((sol.maxSum(vector<int>{99, -99, 49, -49, 24, -24, 12, -12, 6, -6, 3, -3, 1, -1, 0, 1, -1, 0}) == 194));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 1, 2, 3, 4, 5}) == 15));
    assert((sol.maxSum(vector<int>{5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5}) == 15));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == 0));
    assert((sol.maxSum(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == 45));
    assert((sol.maxSum(vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}) == 6));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == 55));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10}) == 55));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60}) == 210));
    assert((sol.maxSum(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5}) == 15));
    assert((sol.maxSum(vector<int>{10, 20, 10, 20, 10, 20, 10, 20, 10, 20}) == 30));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, -5, -4, -3, -2, -1}) == 15));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, -10, -20, -30, -40, -50, 60, 70, 80, 90, 100}) == 550));
    assert((sol.maxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == 55));
    assert((sol.maxSum(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, 19, -20}) == 100));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{-1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -2, -3, -4, -5, -6, -7, -8, -9, -10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 210));
    assert((sol.maxSum(vector<int>{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}) == 15));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5}) == 55));
    assert((sol.maxSum(vector<int>{3, 1, 2, 1, 3, 4, 5, 2, 6, 7, 8, 9, 1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 210));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 40, 30, 20, 10, 10, 20, 30, 40, 50, 40, 30, 20, 10}) == 150));
    assert((sol.maxSum(vector<int>{-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -10, 9, -8, 7, -6, 5, -4, 3, -2, 1}) == 55));
    assert((sol.maxSum(vector<int>{-5, -1, -3, -2, -4, -1, -2, -3, -5}) == -1));
    assert((sol.maxSum(vector<int>{5, -5, 10, -10, 15, -15, 20, -20, 25}) == 75));
    assert((sol.maxSum(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10}) == 55));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0}) == 0));
    assert((sol.maxSum(vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == 210));
    assert((sol.maxSum(vector<int>{0, 1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10, 0, 1, -1, 2, -2, 3, -3, 4, -4}) == 55));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 50, 40, 30, 20, 10, 10, 20, 30, 40, 50, 50, 40, 30, 20, 10}) == 150));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5}) == 210));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1}) == 55));
    assert((sol.maxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 210));
    assert((sol.maxSum(vector<int>{-99, 99, -98, 98, -97, 97, -96, 96, -95, 95, -94, 94, -93, 93, -92, 92, -91, 91, -90, 90}) == 945));
    assert((sol.maxSum(vector<int>{-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -11, 12, -13, 14, -15, 16, -17, 18, -19, 20}) == 110));
    assert((sol.maxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == 55));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == 5));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == -1));
    assert((sol.maxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 55));
    assert((sol.maxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{-1, 2, -3, 4, -5, 6, -7, 8, -9, 10, -1, 2, -3}) == 30));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 210));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}) == 465));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == 120));
    assert((sol.maxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 55));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == 5));
    assert((sol.maxSum(vector<int>{100, -90, 80, -70, 60, -50, 40, -30, 20, -10}) == 300));
    assert((sol.maxSum(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10}) == 55));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100}) == 550));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 2, 2, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8}) == 36));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 40, 30, 20, 10}) == 150));
    assert((sol.maxSum(vector<int>{50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50}) == 50));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == 45));
    assert((sol.maxSum(vector<int>{3, 1, 2, 3, 2, 4, 5, 1, 6, 5, 7, 8, 7, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{0, 0, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9}) == 45));
    assert((sol.maxSum(vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50}) == 150));
    assert((sol.maxSum(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}) == 30));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == 0));
    assert((sol.maxSum(vector<int>{-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6, -7, 7, -8, 8, -9, 9, -10, 10, -11, 11, -12, 12, -13, 13, -14, 14, -15, 15, -16, 16, -17, 17, -18, 18, -19, 19, -20, 20}) == 210));
    assert((sol.maxSum(vector<int>{10, 20, 30, 10, 40, 50, 20, 60, 70}) == 280));
    assert((sol.maxSum(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9, -10}) == 25));
    assert((sol.maxSum(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20}) == 210));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 210));
    assert((sol.maxSum(vector<int>{50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50}) == 50));
    assert((sol.maxSum(vector<int>{100, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50, 50, -50}) == 150));
    assert((sol.maxSum(vector<int>{10, 20, 30, -10, -20, -30, 40, 50, 60, -40, -50, -60, 70, 80, 90}) == 450));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == 0));
    assert((sol.maxSum(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == 0));
    assert((sol.maxSum(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0}) == 45));
    assert((sol.maxSum(vector<int>{-5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0, -5, 5, 0}) == 5));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0, -10, -20, -30, -40}) == 550));
    assert((sol.maxSum(vector<int>{0, -1, 2, -2, 1, -1, 3, -3, 4, -4, 5, -5, 6, -6}) == 21));
    assert((sol.maxSum(vector<int>{3, 1, 2, 1, 3, 4, 2, 5}) == 15));
    assert((sol.maxSum(vector<int>{1, 2, 3, 2, 4, 5, 6, 5, 7, 8, 9, 8, 10}) == 55));
    assert((sol.maxSum(vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10, 0, -10, -20, -30, -40, -50, -60, -70, -80, -90, -100}) == 550));
    assert((sol.maxSum(vector<int>{10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100}) == 1045));
    assert((sol.maxSum(vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}) == -1));
    assert((sol.maxSum(vector<int>{5, -1, 3, 5, -2, 3, 4, -1, 2, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4}) == 45));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 210));
    assert((sol.maxSum(vector<int>{10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60, 70, -70, 80, -80, 90, -90, 100, -100}) == 550));
    assert((sol.maxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 1));
    assert((sol.maxSum(vector<int>{10, 20, 10, 30, 40, 20, 50, 60, 30}) == 210));
    assert((sol.maxSum(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8, 8, 4, 1, 9, 7, 1, 6, 9, 3, 9, 9, 3, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5, 0, 2, 8}) == 45));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5}) == 55));
    assert((sol.maxSum(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{5, 3, -5, 2, 3, 3, 9, -2, 4, 5, 6, 7, 8, 9, 10}) == 54));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == -1));
    assert((sol.maxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 55));
    assert((sol.maxSum(vector<int>{1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 8, 8, 9, 10, 10, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20}) == 210));
    assert((sol.maxSum(vector<int>{-1, -2, -3, -4, -5, -1, -2}) == -1));
    assert((sol.maxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == 5));

    cout << "All tests passed for maximum-unique-subarray-sum-after-deletion" << endl;
    return 0;
}
