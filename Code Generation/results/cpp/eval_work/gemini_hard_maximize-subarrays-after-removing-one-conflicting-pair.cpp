// task_id: maximize-subarrays-after-removing-one-conflicting-pair
// difficulty: Hard

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
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        // Standardize pairs so a < b
        for (auto& pair : conflictingPairs) {
            if (pair[0] > pair[1]) swap(pair[0], pair[1]);
        }

        // For each right endpoint r, we need the largest left endpoints 
        // that form a conflict. We track the top two largest left endpoints.
        // firstMax[r] = largest l s.t. [l, r] is a conflict
        // secondMax[r] = second largest l s.t. [l, r] is a conflict
        // countFirst[r] = how many pairs have l == firstMax[r]
        // firstIdx[r] = the index of the pair if countFirst[r] == 1
        vector<int> firstMax(n + 1, 0);
        vector<int> secondMax(n + 1, 0);
        vector<int> countFirst(n + 1, 0);
        vector<int> firstIdx(n + 1, -1);

        int m = conflictingPairs.size();
        for (int i = 0; i < m; ++i) {
            int l = conflictingPairs[i][0];
            int r = conflictingPairs[i][1];
            if (l > firstMax[r]) {
                secondMax[r] = firstMax[r];
                firstMax[r] = l;
                countFirst[r] = 1;
                firstIdx[r] = i;
            } else if (l == firstMax[r]) {
                countFirst[r]++;
            } else if (l > secondMax[r]) {
                secondMax[r] = l;
            }
        }

        // Cumulative constraints: for a fixed right endpoint r, 
        // the subarray [L, r] is valid if L > max of all l's for all conflicts ending <= r.
        // Let f1[r] be the max left boundary for endpoint r with all pairs.
        // Let f2[r] be the max left boundary if we remove the 'best' pair for r.
        vector<int> f1(n + 1, 0);
        vector<int> f2(n + 1, 0);
        int curMax1 = 0, curMax2 = 0;

        for (int r = 1; r <= n; ++r) {
            curMax1 = max(curMax1, firstMax[r]);
            f1[r] = curMax1;
            
            // To calculate the impact of removing a specific pair, 
            // we track the contribution of the second-best constraints.
            curMax2 = max(curMax2, secondMax[r]);
            f2[r] = curMax2;
        }

        // Base total subarrays without removing anything
        long long baseTotal = 0;
        for (int r = 1; r <= n; ++r) {
            baseTotal += (r - f1[r]);
        }

        // gain[i] is the number of additional subarrays if pair i is removed.
        // A pair i = [l_i, r_i] affects subarrays ending at r where r >= r_i.
        // If we remove pair i, the new constraint for r becomes max(f2[r], max_{j != i} l_j).
        // This is complex to track directly, so we use a difference array approach
        // focusing on the ranges where pair i is the unique maximum.
        vector<long long> gain(m, 0);
        
        // Precompute the running maximums from the left excluding the unique contribution of specific pairs
        // Actually, we can just iterate through r and see if firstMax[r] is the bottleneck.
        int globalMax = 0;
        int secondaryGlobalMax = 0;
        
        // We need to know which pair is the "bottleneck" (the one determining f1[r])
        // If a pair i=[l, r_i] is the only one such that l == f1[r], removing it 
        // changes the boundary from f1[r] to the next best boundary.
        
        // Re-calculating the effective "current maximum" and which pair provides it.
        int currentM1 = 0; // Global max l seen so far
        int currentM2 = 0; // Second global max l seen so far
        int currentIdx = -1; // Index of the pair that provided currentM1
        
        for (int r = 1; r <= n; ++r) {
            // Update global maxes with pairs ending at r
            if (firstMax[r] > currentM1) {
                currentM2 = max(currentM1, secondMax[r]);
                currentM1 = firstMax[r];
                currentIdx = (countFirst[r] == 1) ? firstIdx[r] : -2; // -2 means multiple pairs share the max
            } else if (firstMax[r] == currentM1) {
                currentIdx = -2; 
                currentM2 = max(currentM2, secondMax[r]);
            } else if (firstMax[r] > currentM2) {
                currentM2 = firstMax[r];
            }

            // If there's a unique pair responsible for the current boundary
            if (currentIdx >= 0) {
                gain[currentIdx] += (currentM1 - currentM2);
            }
        }

        long long maxGain = 0;
        for (int i = 0; i < m; ++i) {
            maxGain = max(maxGain, gain[i]);
        }

        return baseTotal + maxGain;
    }
};

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.maxSubarrays(7, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}}) == 8LL));
    assert((sol.maxSubarrays(6, vector<vector<int>>{vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}}) == 12LL));
    assert((sol.maxSubarrays(6, vector<vector<int>>{vector<int>{1, 3}, vector<int>{3, 5}, vector<int>{2, 4}, vector<int>{4, 6}}) == 12LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}}) == 11LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 10}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}}) == 39LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 5}, vector<int>{2, 6}, vector<int>{3, 7}, vector<int>{4, 8}, vector<int>{5, 9}, vector<int>{6, 10}}) == 35LL));
    assert((sol.maxSubarrays(6, vector<vector<int>>{vector<int>{1, 2}, vector<int>{3, 4}, vector<int>{5, 6}}) == 12LL));
    assert((sol.maxSubarrays(5, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 5}, vector<int>{3, 5}}) == 12LL));
    assert((sol.maxSubarrays(4, vector<vector<int>>{vector<int>{2, 3}, vector<int>{1, 4}}) == 9LL));
    assert((sol.maxSubarrays(6, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}}) == 7LL));
    assert((sol.maxSubarrays(3, vector<vector<int>>{vector<int>{1, 2}, vector<int>{1, 3}, vector<int>{2, 3}}) == 4LL));
    assert((sol.maxSubarrays(3, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}}) == 4LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}, vector<int>{14, 15}, vector<int>{1, 15}}) == 16LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 5}, vector<int>{2, 6}, vector<int>{3, 7}, vector<int>{4, 8}, vector<int>{5, 9}, vector<int>{6, 10}, vector<int>{1, 6}, vector<int>{2, 7}, vector<int>{3, 8}, vector<int>{4, 9}}) == 35LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 10}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}, vector<int>{1, 6}, vector<int>{2, 7}, vector<int>{3, 8}, vector<int>{4, 9}, vector<int>{5, 10}}) == 37LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 5}, vector<int>{5, 9}, vector<int>{2, 6}, vector<int>{6, 10}, vector<int>{3, 7}, vector<int>{4, 8}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{1, 4}, vector<int>{2, 5}, vector<int>{3, 6}, vector<int>{4, 7}, vector<int>{5, 8}, vector<int>{6, 9}, vector<int>{7, 10}}) == 24LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}, vector<int>{14, 15}, vector<int>{15, 16}, vector<int>{16, 17}, vector<int>{17, 18}, vector<int>{18, 19}, vector<int>{19, 20}, vector<int>{1, 20}, vector<int>{2, 19}, vector<int>{3, 18}, vector<int>{4, 17}, vector<int>{5, 16}, vector<int>{6, 15}, vector<int>{7, 14}, vector<int>{8, 13}, vector<int>{9, 12}, vector<int>{10, 11}}) == 21LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 20}, vector<int>{2, 19}, vector<int>{3, 18}, vector<int>{4, 17}, vector<int>{5, 16}, vector<int>{6, 15}, vector<int>{7, 14}, vector<int>{8, 13}, vector<int>{9, 12}, vector<int>{10, 11}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{7, 9}, vector<int>{8, 10}, vector<int>{9, 11}, vector<int>{10, 12}}) == 75LL));
    assert((sol.maxSubarrays(9, vector<vector<int>>{vector<int>{1, 9}, vector<int>{2, 8}, vector<int>{3, 7}, vector<int>{4, 6}, vector<int>{5, 5}, vector<int>{1, 5}, vector<int>{2, 6}, vector<int>{3, 4}, vector<int>{7, 8}}) == 17LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}, vector<int>{14, 15}}) == 16LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 10}, vector<int>{10, 20}, vector<int>{1, 11}, vector<int>{11, 20}, vector<int>{1, 12}, vector<int>{12, 20}, vector<int>{1, 13}, vector<int>{13, 20}, vector<int>{1, 14}, vector<int>{14, 20}, vector<int>{1, 15}, vector<int>{15, 20}, vector<int>{1, 16}, vector<int>{16, 20}, vector<int>{1, 17}, vector<int>{17, 20}, vector<int>{1, 18}, vector<int>{18, 20}, vector<int>{1, 19}, vector<int>{19, 20}}) == 182LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{1, 10}}) == 11LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}, vector<int>{14, 15}, vector<int>{1, 15}}) == 16LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{7, 9}, vector<int>{8, 10}, vector<int>{9, 11}, vector<int>{10, 12}, vector<int>{11, 13}, vector<int>{12, 14}, vector<int>{13, 15}, vector<int>{1, 4}, vector<int>{2, 5}, vector<int>{3, 6}, vector<int>{4, 7}, vector<int>{5, 8}, vector<int>{6, 9}, vector<int>{7, 10}, vector<int>{8, 11}, vector<int>{9, 12}, vector<int>{10, 13}, vector<int>{11, 14}, vector<int>{12, 15}}) == 30LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 10}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}, vector<int>{6, 5}, vector<int>{7, 4}, vector<int>{8, 3}, vector<int>{9, 2}, vector<int>{10, 1}, vector<int>{11, 20}, vector<int>{12, 19}, vector<int>{13, 18}, vector<int>{14, 17}, vector<int>{15, 16}, vector<int>{16, 15}, vector<int>{17, 14}, vector<int>{18, 13}, vector<int>{19, 12}, vector<int>{20, 11}}) == 85LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 2}, vector<int>{3, 4}, vector<int>{5, 6}, vector<int>{7, 8}, vector<int>{9, 10}, vector<int>{11, 12}, vector<int>{13, 14}, vector<int>{15, 16}, vector<int>{17, 18}, vector<int>{19, 20}, vector<int>{1, 20}, vector<int>{2, 19}, vector<int>{3, 18}, vector<int>{4, 17}, vector<int>{5, 16}, vector<int>{6, 15}, vector<int>{7, 14}, vector<int>{8, 13}, vector<int>{9, 12}, vector<int>{10, 11}}) == 32LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 10}, vector<int>{10, 20}, vector<int>{1, 5}, vector<int>{5, 15}, vector<int>{1, 15}, vector<int>{15, 20}, vector<int>{1, 20}}) == 180LL));
    assert((sol.maxSubarrays(8, vector<vector<int>>{vector<int>{1, 2}, vector<int>{1, 3}, vector<int>{1, 4}, vector<int>{2, 3}, vector<int>{2, 4}, vector<int>{3, 4}, vector<int>{1, 5}, vector<int>{2, 5}, vector<int>{3, 5}, vector<int>{4, 5}, vector<int>{1, 6}, vector<int>{2, 6}, vector<int>{3, 6}, vector<int>{4, 6}, vector<int>{5, 6}, vector<int>{1, 7}, vector<int>{2, 7}, vector<int>{3, 7}, vector<int>{4, 7}, vector<int>{5, 7}, vector<int>{6, 7}, vector<int>{1, 8}, vector<int>{2, 8}, vector<int>{3, 8}, vector<int>{4, 8}, vector<int>{5, 8}, vector<int>{6, 8}, vector<int>{7, 8}}) == 9LL));
    assert((sol.maxSubarrays(50, vector<vector<int>>{vector<int>{1, 5}, vector<int>{5, 10}, vector<int>{10, 15}, vector<int>{15, 20}, vector<int>{20, 25}, vector<int>{25, 30}, vector<int>{30, 35}, vector<int>{35, 40}, vector<int>{40, 45}, vector<int>{45, 50}}) == 350LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 20}, vector<int>{2, 19}, vector<int>{3, 18}, vector<int>{4, 17}, vector<int>{5, 16}, vector<int>{6, 15}, vector<int>{7, 14}, vector<int>{8, 13}, vector<int>{9, 12}, vector<int>{10, 11}, vector<int>{1, 10}, vector<int>{2, 11}, vector<int>{3, 12}, vector<int>{4, 13}, vector<int>{5, 14}, vector<int>{6, 15}, vector<int>{7, 16}, vector<int>{8, 17}, vector<int>{9, 18}}) == 126LL));
    assert((sol.maxSubarrays(12, vector<vector<int>>{vector<int>{1, 6}, vector<int>{2, 7}, vector<int>{3, 8}, vector<int>{4, 9}, vector<int>{5, 10}, vector<int>{6, 11}, vector<int>{7, 12}}) == 51LL));
    assert((sol.maxSubarrays(25, vector<vector<int>>{vector<int>{1, 5}, vector<int>{2, 6}, vector<int>{3, 7}, vector<int>{4, 8}, vector<int>{5, 9}, vector<int>{6, 10}, vector<int>{7, 11}, vector<int>{8, 12}, vector<int>{9, 13}, vector<int>{10, 14}, vector<int>{11, 15}, vector<int>{12, 16}, vector<int>{13, 17}, vector<int>{14, 18}, vector<int>{15, 19}, vector<int>{16, 20}, vector<int>{17, 21}, vector<int>{18, 22}, vector<int>{19, 23}, vector<int>{20, 24}, vector<int>{21, 25}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{7, 9}, vector<int>{8, 10}, vector<int>{9, 11}, vector<int>{10, 12}, vector<int>{11, 13}, vector<int>{12, 14}, vector<int>{13, 15}, vector<int>{14, 16}, vector<int>{15, 17}, vector<int>{16, 18}, vector<int>{17, 19}, vector<int>{18, 20}, vector<int>{19, 21}, vector<int>{20, 22}, vector<int>{21, 23}, vector<int>{22, 24}, vector<int>{23, 25}}) == 50LL));
    assert((sol.maxSubarrays(12, vector<vector<int>>{vector<int>{1, 12}, vector<int>{2, 11}, vector<int>{3, 10}, vector<int>{4, 9}, vector<int>{5, 8}, vector<int>{6, 7}, vector<int>{1, 6}, vector<int>{2, 7}, vector<int>{3, 8}, vector<int>{4, 9}, vector<int>{5, 10}, vector<int>{6, 11}}) == 48LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 5}, vector<int>{2, 6}, vector<int>{3, 7}, vector<int>{4, 8}, vector<int>{5, 9}, vector<int>{6, 10}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{7, 9}, vector<int>{8, 10}}) == 20LL));
    assert((sol.maxSubarrays(50, vector<vector<int>>{vector<int>{1, 25}, vector<int>{2, 26}, vector<int>{3, 27}, vector<int>{4, 28}, vector<int>{5, 29}, vector<int>{6, 30}, vector<int>{7, 31}, vector<int>{8, 32}, vector<int>{9, 33}, vector<int>{10, 34}, vector<int>{11, 35}, vector<int>{12, 36}, vector<int>{13, 37}, vector<int>{14, 38}, vector<int>{15, 39}, vector<int>{16, 40}, vector<int>{17, 41}, vector<int>{18, 42}, vector<int>{19, 43}, vector<int>{20, 44}, vector<int>{21, 45}, vector<int>{22, 46}, vector<int>{23, 47}, vector<int>{24, 48}, vector<int>{25, 49}, vector<int>{26, 50}}) == 925LL));
    assert((sol.maxSubarrays(8, vector<vector<int>>{vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}, vector<int>{4, 5}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{1, 4}, vector<int>{2, 5}, vector<int>{3, 6}, vector<int>{4, 7}, vector<int>{5, 8}}) == 15LL));
    assert((sol.maxSubarrays(9, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}}) == 10LL));
    assert((sol.maxSubarrays(12, vector<vector<int>>{vector<int>{1, 4}, vector<int>{2, 5}, vector<int>{3, 6}, vector<int>{4, 7}, vector<int>{5, 8}, vector<int>{6, 9}, vector<int>{7, 10}, vector<int>{8, 11}, vector<int>{9, 12}}) == 34LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 2}, vector<int>{1, 3}, vector<int>{1, 4}, vector<int>{1, 5}, vector<int>{1, 6}, vector<int>{1, 7}, vector<int>{1, 8}, vector<int>{1, 9}, vector<int>{1, 10}, vector<int>{1, 11}, vector<int>{1, 12}, vector<int>{1, 13}, vector<int>{1, 14}, vector<int>{1, 15}}) == 107LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 20}, vector<int>{2, 19}, vector<int>{3, 18}, vector<int>{4, 17}, vector<int>{5, 16}, vector<int>{6, 15}, vector<int>{7, 14}, vector<int>{8, 13}, vector<int>{9, 12}, vector<int>{10, 11}}) == 129LL));
    assert((sol.maxSubarrays(100, vector<vector<int>>{vector<int>{1, 50}, vector<int>{50, 100}, vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}}) == 4244LL));
    assert((sol.maxSubarrays(8, vector<vector<int>>{vector<int>{1, 4}, vector<int>{2, 5}, vector<int>{3, 6}, vector<int>{4, 7}, vector<int>{5, 8}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}}) == 17LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 2}, vector<int>{1, 3}, vector<int>{1, 4}, vector<int>{1, 5}, vector<int>{1, 6}, vector<int>{1, 7}, vector<int>{1, 8}, vector<int>{1, 9}, vector<int>{1, 10}, vector<int>{2, 3}, vector<int>{2, 4}, vector<int>{2, 5}, vector<int>{2, 6}, vector<int>{2, 7}, vector<int>{2, 8}, vector<int>{2, 9}, vector<int>{2, 10}, vector<int>{3, 4}, vector<int>{3, 5}, vector<int>{3, 6}, vector<int>{3, 7}, vector<int>{3, 8}, vector<int>{3, 9}, vector<int>{3, 10}, vector<int>{4, 5}, vector<int>{4, 6}, vector<int>{4, 7}, vector<int>{4, 8}, vector<int>{4, 9}, vector<int>{4, 10}, vector<int>{5, 6}, vector<int>{5, 7}, vector<int>{5, 8}, vector<int>{5, 9}, vector<int>{5, 10}, vector<int>{6, 7}, vector<int>{6, 8}, vector<int>{6, 9}, vector<int>{6, 10}, vector<int>{7, 8}, vector<int>{7, 9}, vector<int>{7, 10}, vector<int>{8, 9}, vector<int>{8, 10}, vector<int>{9, 10}}) == 11LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{3, 13}, vector<int>{4, 12}, vector<int>{5, 11}, vector<int>{6, 10}, vector<int>{7, 9}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{5, 7}}) == 62LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 10}, vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}}) == 11LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{3, 13}, vector<int>{4, 12}, vector<int>{5, 11}, vector<int>{6, 10}, vector<int>{7, 9}, vector<int>{1, 8}, vector<int>{2, 9}, vector<int>{3, 10}, vector<int>{4, 11}, vector<int>{5, 12}, vector<int>{6, 13}, vector<int>{7, 14}}) == 79LL));
    assert((sol.maxSubarrays(8, vector<vector<int>>{vector<int>{1, 2}, vector<int>{1, 3}, vector<int>{1, 4}, vector<int>{1, 5}, vector<int>{1, 6}, vector<int>{1, 7}, vector<int>{1, 8}}) == 30LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 2}, vector<int>{3, 4}, vector<int>{5, 6}, vector<int>{7, 8}, vector<int>{9, 10}, vector<int>{11, 12}, vector<int>{13, 14}, vector<int>{15, 16}, vector<int>{17, 18}, vector<int>{19, 20}, vector<int>{1, 20}, vector<int>{2, 19}, vector<int>{3, 18}, vector<int>{4, 17}, vector<int>{5, 16}, vector<int>{6, 15}, vector<int>{7, 14}, vector<int>{8, 13}, vector<int>{9, 12}, vector<int>{10, 11}}) == 32LL));
    assert((sol.maxSubarrays(7, vector<vector<int>>{vector<int>{1, 2}, vector<int>{1, 3}, vector<int>{1, 4}, vector<int>{1, 5}, vector<int>{1, 6}, vector<int>{1, 7}}) == 23LL));
    assert((sol.maxSubarrays(18, vector<vector<int>>{vector<int>{1, 18}, vector<int>{2, 17}, vector<int>{3, 16}, vector<int>{4, 15}, vector<int>{5, 14}, vector<int>{6, 13}, vector<int>{7, 12}, vector<int>{8, 11}, vector<int>{9, 10}, vector<int>{1, 9}, vector<int>{2, 10}, vector<int>{3, 11}, vector<int>{4, 12}, vector<int>{5, 13}, vector<int>{6, 14}, vector<int>{7, 15}, vector<int>{8, 16}}) == 104LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 10}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{7, 9}}) == 21LL));
    assert((sol.maxSubarrays(12, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{1, 12}, vector<int>{1, 11}, vector<int>{1, 10}, vector<int>{1, 9}, vector<int>{1, 8}, vector<int>{1, 7}, vector<int>{1, 6}, vector<int>{1, 5}, vector<int>{1, 4}, vector<int>{1, 3}}) == 13LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{3, 13}, vector<int>{4, 12}, vector<int>{5, 11}, vector<int>{6, 10}, vector<int>{7, 9}}) == 84LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 5}, vector<int>{2, 6}, vector<int>{3, 7}, vector<int>{4, 8}, vector<int>{5, 9}, vector<int>{6, 10}, vector<int>{7, 11}, vector<int>{8, 12}, vector<int>{9, 13}, vector<int>{10, 14}, vector<int>{11, 15}}) == 55LL));
    assert((sol.maxSubarrays(25, vector<vector<int>>{vector<int>{1, 2}, vector<int>{3, 4}, vector<int>{5, 6}, vector<int>{7, 8}, vector<int>{9, 10}, vector<int>{11, 12}, vector<int>{13, 14}, vector<int>{15, 16}, vector<int>{17, 18}, vector<int>{19, 20}, vector<int>{21, 22}, vector<int>{23, 24}, vector<int>{24, 25}}) == 40LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 2}, vector<int>{3, 4}, vector<int>{5, 6}, vector<int>{7, 8}, vector<int>{9, 10}, vector<int>{11, 12}, vector<int>{13, 14}, vector<int>{15, 16}, vector<int>{17, 18}, vector<int>{19, 20}, vector<int>{1, 10}, vector<int>{2, 11}, vector<int>{3, 12}, vector<int>{4, 13}, vector<int>{5, 14}, vector<int>{6, 15}, vector<int>{7, 16}, vector<int>{8, 17}, vector<int>{9, 18}, vector<int>{10, 19}, vector<int>{1, 20}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}}) == 29LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 10}, vector<int>{2, 11}, vector<int>{3, 12}, vector<int>{4, 13}, vector<int>{5, 14}, vector<int>{6, 15}, vector<int>{7, 16}, vector<int>{8, 17}, vector<int>{9, 18}, vector<int>{10, 19}, vector<int>{11, 20}}) == 145LL));
    assert((sol.maxSubarrays(7, vector<vector<int>>{vector<int>{1, 7}, vector<int>{2, 6}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 7}}) == 18LL));
    assert((sol.maxSubarrays(11, vector<vector<int>>{vector<int>{1, 6}, vector<int>{2, 7}, vector<int>{3, 8}, vector<int>{4, 9}, vector<int>{5, 10}, vector<int>{6, 11}}) == 46LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{3, 13}, vector<int>{4, 12}, vector<int>{5, 11}, vector<int>{6, 10}, vector<int>{7, 9}, vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}}) == 18LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 3}, vector<int>{3, 5}, vector<int>{5, 7}, vector<int>{7, 9}, vector<int>{9, 11}, vector<int>{11, 13}, vector<int>{13, 15}, vector<int>{1, 4}, vector<int>{2, 5}, vector<int>{3, 6}, vector<int>{4, 7}, vector<int>{5, 8}, vector<int>{6, 9}, vector<int>{7, 10}, vector<int>{8, 11}, vector<int>{9, 12}, vector<int>{10, 13}, vector<int>{11, 14}, vector<int>{12, 15}, vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}, vector<int>{14, 15}}) == 16LL));
    assert((sol.maxSubarrays(15, vector<vector<int>>{vector<int>{1, 5}, vector<int>{5, 10}, vector<int>{10, 15}, vector<int>{3, 7}, vector<int>{7, 12}, vector<int>{2, 6}, vector<int>{6, 11}, vector<int>{4, 8}, vector<int>{8, 13}, vector<int>{1, 6}, vector<int>{6, 11}, vector<int>{2, 7}, vector<int>{7, 12}, vector<int>{3, 8}, vector<int>{8, 13}, vector<int>{4, 9}, vector<int>{9, 14}, vector<int>{5, 10}, vector<int>{10, 15}}) == 62LL));
    assert((sol.maxSubarrays(12, vector<vector<int>>{vector<int>{1, 6}, vector<int>{2, 7}, vector<int>{3, 8}, vector<int>{4, 9}, vector<int>{5, 10}, vector<int>{1, 7}, vector<int>{2, 8}, vector<int>{3, 9}, vector<int>{4, 10}, vector<int>{5, 11}, vector<int>{1, 8}, vector<int>{2, 9}, vector<int>{3, 10}, vector<int>{4, 11}, vector<int>{5, 12}}) == 54LL));
    assert((sol.maxSubarrays(30, vector<vector<int>>{vector<int>{1, 15}, vector<int>{2, 16}, vector<int>{3, 17}, vector<int>{4, 18}, vector<int>{5, 19}, vector<int>{6, 20}, vector<int>{7, 21}, vector<int>{8, 22}, vector<int>{9, 23}, vector<int>{10, 24}, vector<int>{11, 25}, vector<int>{12, 26}, vector<int>{13, 27}, vector<int>{14, 28}, vector<int>{15, 29}, vector<int>{16, 30}}) == 330LL));
    assert((sol.maxSubarrays(12, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{1, 12}, vector<int>{2, 11}, vector<int>{3, 10}, vector<int>{4, 9}, vector<int>{5, 8}, vector<int>{6, 7}, vector<int>{1, 7}, vector<int>{2, 8}, vector<int>{3, 9}, vector<int>{4, 10}, vector<int>{5, 11}, vector<int>{6, 12}}) == 13LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 10}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}, vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 10}}) == 24LL));
    assert((sol.maxSubarrays(30, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}, vector<int>{14, 15}, vector<int>{15, 16}, vector<int>{16, 17}, vector<int>{17, 18}, vector<int>{18, 19}, vector<int>{19, 20}, vector<int>{20, 21}, vector<int>{21, 22}, vector<int>{22, 23}, vector<int>{23, 24}, vector<int>{24, 25}, vector<int>{25, 26}, vector<int>{26, 27}, vector<int>{27, 28}, vector<int>{28, 29}, vector<int>{29, 30}, vector<int>{1, 3}, vector<int>{3, 5}, vector<int>{5, 7}, vector<int>{7, 9}, vector<int>{9, 11}, vector<int>{11, 13}, vector<int>{13, 15}, vector<int>{15, 17}, vector<int>{17, 19}, vector<int>{19, 21}, vector<int>{21, 23}, vector<int>{23, 25}, vector<int>{25, 27}, vector<int>{27, 29}}) == 31LL));
    assert((sol.maxSubarrays(9, vector<vector<int>>{vector<int>{1, 9}, vector<int>{2, 9}, vector<int>{3, 9}, vector<int>{4, 9}, vector<int>{5, 9}, vector<int>{6, 9}, vector<int>{7, 9}, vector<int>{8, 9}}) == 38LL));
    assert((sol.maxSubarrays(20, vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 11}, vector<int>{11, 12}, vector<int>{12, 13}, vector<int>{13, 14}, vector<int>{14, 15}, vector<int>{15, 16}, vector<int>{16, 17}, vector<int>{17, 18}, vector<int>{18, 19}, vector<int>{19, 20}}) == 21LL));
    assert((sol.maxSubarrays(75, vector<vector<int>>{vector<int>{1, 26}, vector<int>{2, 27}, vector<int>{3, 28}, vector<int>{4, 29}, vector<int>{5, 30}, vector<int>{6, 31}, vector<int>{7, 32}, vector<int>{8, 33}, vector<int>{9, 34}, vector<int>{10, 35}, vector<int>{11, 36}, vector<int>{12, 37}, vector<int>{13, 38}, vector<int>{14, 39}, vector<int>{15, 40}, vector<int>{16, 41}, vector<int>{17, 42}, vector<int>{18, 43}, vector<int>{19, 44}, vector<int>{20, 45}, vector<int>{21, 46}, vector<int>{22, 47}, vector<int>{23, 48}, vector<int>{24, 49}, vector<int>{25, 50}, vector<int>{26, 51}, vector<int>{27, 52}, vector<int>{28, 53}, vector<int>{29, 54}, vector<int>{30, 55}, vector<int>{31, 56}, vector<int>{32, 57}, vector<int>{33, 58}, vector<int>{34, 59}, vector<int>{35, 60}, vector<int>{36, 61}, vector<int>{37, 62}, vector<int>{38, 63}, vector<int>{39, 64}, vector<int>{40, 65}, vector<int>{41, 66}, vector<int>{42, 67}, vector<int>{43, 68}, vector<int>{44, 69}, vector<int>{45, 70}, vector<int>{46, 71}, vector<int>{47, 72}, vector<int>{48, 73}, vector<int>{49, 74}, vector<int>{50, 75}}) == 1576LL));
    assert((sol.maxSubarrays(10, vector<vector<int>>{vector<int>{1, 10}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{5, 7}, vector<int>{6, 8}}) == 25LL));
    assert((sol.maxSubarrays(12, vector<vector<int>>{vector<int>{1, 2}, vector<int>{3, 4}, vector<int>{5, 6}, vector<int>{7, 8}, vector<int>{9, 10}, vector<int>{11, 12}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 6}, vector<int>{5, 7}, vector<int>{6, 8}, vector<int>{7, 9}, vector<int>{8, 10}, vector<int>{9, 11}, vector<int>{10, 12}}) == 18LL));

    cout << "All tests passed for maximize-subarrays-after-removing-one-conflicting-pair" << endl;
    return 0;
}
