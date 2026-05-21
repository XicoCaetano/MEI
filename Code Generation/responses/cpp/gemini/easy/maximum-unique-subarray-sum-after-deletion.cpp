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
    int maxSum(vector<int> nums) {
        int n = nums.size();
        int max_sum = -200; // Initialize with a value lower than any possible single element sum

        // The problem allows deleting any number of elements and then picking a subarray.
        // This is equivalent to picking a SUBSEQUENCE of the original array,
        // and then treating that subsequence as a subarray.
        // However, a subarray of a subsequence is just another subsequence.
        // Therefore, the problem simplifies to finding a subsequence of 'nums'
        // where all elements are unique and the sum is maximized.

        // To maximize the sum of unique elements:
        // 1. We should only consider positive elements.
        // 2. We should pick the largest available instance of every unique positive integer.
        // 3. If there are no positive integers, we must pick exactly one element (the largest one)
        //    because we cannot leave the array empty.

        unordered_map<int, int> positive_elements;
        int max_val = INT_MIN;
        bool has_positive = false;

        for (int x : nums) {
            max_val = max(max_val, x);
            if (x > 0) {
                positive_elements[x] = x;
                has_positive = true;
            }
        }

        if (!has_positive) {
            // If there are no positive numbers, the best we can do is pick the largest
            // single element (which will be 0 or negative).
            return max_val;
        }

        int total_sum = 0;
        for (auto const& [val, count] : positive_elements) {
            total_sum += val;
        }

        return total_sum;
    }
};