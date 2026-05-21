#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int maxSum(vector<int> nums) {
        // Key insight: we can delete any elements, so we can keep any subset.
        // We need a contiguous subarray with unique elements after deletions.
        // Since we can delete freely, we can pick any subset of distinct values
        // and arrange them contiguously. So just sum all positive occurrences
        // of each unique value (take each unique value at most once, only if positive).
        
        unordered_map<int, int> seen;
        for (int x : nums) seen[x]++;
        
        int result = INT_MIN;
        // We must select at least one element (subarray can't be empty based on problem)
        // Actually problem says "without making it empty" for deletions, subarray selected after
        // So we pick the best single unique value or combination
        
        // Since we can delete duplicates and negatives, optimal is:
        // take each unique value that's positive, sum them up
        // but we must pick at least one element
        
        int sum = 0;
        int maxSingle = INT_MIN;
        for (auto& [val, cnt] : seen) {
            maxSingle = max(maxSingle, val);
            if (val > 0) sum += val;
        }
        
        if (sum == 0) return maxSingle; // all non-positive, pick the largest
        return sum;
    }
};