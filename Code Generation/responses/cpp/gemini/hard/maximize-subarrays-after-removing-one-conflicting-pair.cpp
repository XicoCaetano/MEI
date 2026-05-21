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