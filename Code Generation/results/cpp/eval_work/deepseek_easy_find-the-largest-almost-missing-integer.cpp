// task_id: find-the-largest-almost-missing-integer
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.largestInteger(vector<int>{2, 2, 3, 3, 4, 4, 5, 5}, 2) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10) == 10));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == 10));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5}, 2) == 5));
    assert((sol.largestInteger(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 3) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 2, 3, 3, 3, 4, 4, 4, 4}, 4) == 1));
    assert((sol.largestInteger(vector<int>{10, 20, 30, 40, 50}, 5) == 50));
    assert((sol.largestInteger(vector<int>{5, 5, 5, 5, 5}, 3) == -1));
    assert((sol.largestInteger(vector<int>{10, 20, 30, 40, 50}, 2) == 50));
    assert((sol.largestInteger(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 4) == 19));
    assert((sol.largestInteger(vector<int>{1, 3, 1, 3, 1, 3}, 3) == -1));
    assert((sol.largestInteger(vector<int>{42, 42, 42, 42, 42, 42, 42}, 7) == 42));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 2, 1, 2, 3, 2, 1}, 3) == -1));
    assert((sol.largestInteger(vector<int>{42}, 1) == 42));
    assert((sol.largestInteger(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 1) == 19));
    assert((sol.largestInteger(vector<int>{1, 1, 1, 1, 1}, 1) == -1));
    assert((sol.largestInteger(vector<int>{3, 9, 7, 2, 1, 7}, 4) == 3));
    assert((sol.largestInteger(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 10) == 19));
    assert((sol.largestInteger(vector<int>{3, 9, 2, 1, 7}, 3) == 7));
    assert((sol.largestInteger(vector<int>{1, 1, 2, 2, 3, 3}, 2) == -1));
    assert((sol.largestInteger(vector<int>{0, 0}, 1) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5}, 1) == 5));
    assert((sol.largestInteger(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, 2) == -1));
    assert((sol.largestInteger(vector<int>{5, 4, 3, 2, 1}, 3) == 5));
    assert((sol.largestInteger(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 4) == 15));
    assert((sol.largestInteger(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 4) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 7) == 20));
    assert((sol.largestInteger(vector<int>{4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, 10) == 25));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 19) == 20));
    assert((sol.largestInteger(vector<int>{7, 6, 5, 7, 5, 6, 7, 6, 5, 7, 5, 6, 7}, 7) == -1));
    assert((sol.largestInteger(vector<int>{15, 25, 35, 45, 55, 65, 75, 85, 95, 105}, 6) == 105));
    assert((sol.largestInteger(vector<int>{15, 25, 15, 30, 25, 30, 15, 25, 30, 15, 25, 30}, 5) == -1));
    assert((sol.largestInteger(vector<int>{10, 10, 10, 20, 20, 20, 30, 30, 30}, 2) == -1));
    assert((sol.largestInteger(vector<int>{7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10}, 3) == -1));
    assert((sol.largestInteger(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 15) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 5) == 12));
    assert((sol.largestInteger(vector<int>{8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 10, 10, 10, 10, 10}, 5) == -1));
    assert((sol.largestInteger(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90}, 4) == 90));
    assert((sol.largestInteger(vector<int>{50, 40, 30, 20, 10, 5, 15, 25, 35, 45, 55, 65, 75, 85, 95}, 7) == 95));
    assert((sol.largestInteger(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, 20) == -1));
    assert((sol.largestInteger(vector<int>{5, 3, 9, 3, 5, 9, 5, 3, 9}, 3) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}, 3) == -1));
    assert((sol.largestInteger(vector<int>{5, 5, 5, 5, 5, 5}, 3) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, 6) == 12));
    assert((sol.largestInteger(vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50}, 5) == -1));
    assert((sol.largestInteger(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4) == 10));
    assert((sol.largestInteger(vector<int>{15, 20, 25, 30, 35, 40, 45, 50, 55}, 4) == 55));
    assert((sol.largestInteger(vector<int>{42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42, 42}, 21) == 42));
    assert((sol.largestInteger(vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 5) == 15));
    assert((sol.largestInteger(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 10) == 100));
    assert((sol.largestInteger(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, 1) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5}, 15) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 2, 1, 3, 3, 1, 2, 1, 2, 3}, 3) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 5) == 15));
    assert((sol.largestInteger(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9}, 4) == -1));
    assert((sol.largestInteger(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10}, 4) == -1));
    assert((sol.largestInteger(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 3) == -1));
    assert((sol.largestInteger(vector<int>{5, 4, 3, 2, 1, 5, 4, 3, 2, 1}, 5) == -1));
    assert((sol.largestInteger(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15}, 15) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, 7) == 15));
    assert((sol.largestInteger(vector<int>{5, 2, 5, 3, 5, 2, 5, 3, 5, 2, 5}, 3) == -1));
    assert((sol.largestInteger(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 20) == 7));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 5) == 20));
    assert((sol.largestInteger(vector<int>{42, 24, 42, 24, 42, 24, 42, 24}, 5) == -1));
    assert((sol.largestInteger(vector<int>{8, 6, 4, 2, 0, 2, 4, 6, 8, 10, 12, 14}, 5) == 14));
    assert((sol.largestInteger(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3, 3, 8, 3, 2, 7, 9, 5}, 10) == -1));
    assert((sol.largestInteger(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 3) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, 4) == 1));
    assert((sol.largestInteger(vector<int>{7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6}, 7) == 7));
    assert((sol.largestInteger(vector<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}, 3) == -1));
    assert((sol.largestInteger(vector<int>{10, 20, 10, 30, 10, 20, 30, 10, 20, 30, 10, 20, 30}, 5) == -1));
    assert((sol.largestInteger(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9}, 5) == -1));
    assert((sol.largestInteger(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97}, 10) == 97));
    assert((sol.largestInteger(vector<int>{8, 6, 4, 2, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31}, 3) == 31));
    assert((sol.largestInteger(vector<int>{5, 3, 5, 2, 5, 3, 5}, 3) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5}, 3) == 5));
    assert((sol.largestInteger(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, 5) == -1));
    assert((sol.largestInteger(vector<int>{50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 25) == 50));
    assert((sol.largestInteger(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 2) == -1));
    assert((sol.largestInteger(vector<int>{23, 45, 67, 89, 23, 45, 67, 89, 23, 45, 67, 89, 23, 45, 67, 89}, 8) == -1));
    assert((sol.largestInteger(vector<int>{29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, 10) == 29));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4) == 10));
    assert((sol.largestInteger(vector<int>{5, 4, 3, 2, 1, 5, 4, 3, 2, 1}, 5) == -1));
    assert((sol.largestInteger(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6}, 2) == -1));
    assert((sol.largestInteger(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}, 4) == 31));
    assert((sol.largestInteger(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, 15) == 30));
    assert((sol.largestInteger(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 5) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 2) == 20));
    assert((sol.largestInteger(vector<int>{5, 15, 25, 35, 45, 55, 65, 75}, 4) == 75));
    assert((sol.largestInteger(vector<int>{50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 25) == 50));
    assert((sol.largestInteger(vector<int>{10, 20, 10, 30, 20, 40, 30, 50, 40, 60}, 4) == 60));
    assert((sol.largestInteger(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90}, 5) == 90));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50}, 50) == 50));
    assert((sol.largestInteger(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 8, 8, 8, 8, 8, 8, 8, 8, 8}, 9) == -1));
    assert((sol.largestInteger(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 6) == 10));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == 10));
    assert((sol.largestInteger(vector<int>{5, 15, 25, 35, 45, 55, 65}, 3) == 65));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, 12) == 25));
    assert((sol.largestInteger(vector<int>{42, 42, 42, 42, 42, 42, 41, 41, 41, 41, 40, 40, 40, 39, 39}, 3) == -1));
    assert((sol.largestInteger(vector<int>{45, 45, 45, 45, 45, 45, 45}, 3) == -1));
    assert((sol.largestInteger(vector<int>{5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 5, 4, 3, 2, 1}, 6) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 20) == 20));
    assert((sol.largestInteger(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, 5) == 29));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 10) == 20));
    assert((sol.largestInteger(vector<int>{5, 8, 5, 9, 8, 9, 10, 8, 10, 9}, 4) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 10) == 20));
    assert((sol.largestInteger(vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 5) == 20));
    assert((sol.largestInteger(vector<int>{42, 42, 42, 42, 42, 42, 42, 42, 42, 42}, 10) == 42));
    assert((sol.largestInteger(vector<int>{1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, 10) == -1));
    assert((sol.largestInteger(vector<int>{1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10}, 2) == 1));
    assert((sol.largestInteger(vector<int>{10, 10, 20, 20, 30, 30, 40, 40, 50, 50}, 3) == -1));
    assert((sol.largestInteger(vector<int>{34, 23, 12, 45, 67, 89, 10, 20, 30, 40, 50, 60, 70, 80, 90}, 6) == 90));
    assert((sol.largestInteger(vector<int>{15, 20, 15, 20, 15, 20, 15, 20, 15, 20}, 4) == -1));
    assert((sol.largestInteger(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 9, 7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3}, 7) == -1));
    assert((sol.largestInteger(vector<int>{3, 6, 3, 9, 6, 9, 12, 6, 12, 9, 12, 9, 3, 6, 9, 3, 6, 9}, 6) == -1));
    assert((sol.largestInteger(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12, 12, 13, 13, 14, 14, 15, 15, 16, 16, 17, 17, 18, 18, 19, 19, 20, 20}, 5) == -1));
    assert((sol.largestInteger(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, 6) == 20));
    assert((sol.largestInteger(vector<int>{7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10, 11, 11, 11}, 3) == -1));
    assert((sol.largestInteger(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 10) == -1));

    cout << "All tests passed for find-the-largest-almost-missing-integer" << endl;
    return 0;
}
