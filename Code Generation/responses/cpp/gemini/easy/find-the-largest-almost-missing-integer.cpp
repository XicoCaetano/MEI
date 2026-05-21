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

class Solution {
public:
    int largestInteger(vector<int> nums, int k) {
        int n = nums.size();
        unordered_map<int, int> subarray_count;
        
        // Iterate through every possible subarray of size k
        for (int i = 0; i <= n - k; ++i) {
            // Identify unique elements in the current subarray
            unordered_set<int> unique_in_subarray;
            for (int j = i; j < i + k; ++j) {
                unique_in_subarray.insert(nums[j]);
            }
            
            // Increment the count of how many subarrays each element appears in
            for (int val : unique_in_subarray) {
                subarray_count[val]++;
            }
        }
        
        int result = -1;
        // Find the largest integer that appeared in exactly one subarray
        for (auto const& [val, count] : subarray_count) {
            if (count == 1) {
                if (val > result) {
                    result = val;
                }
            }
        }
        
        return result;
    }
};