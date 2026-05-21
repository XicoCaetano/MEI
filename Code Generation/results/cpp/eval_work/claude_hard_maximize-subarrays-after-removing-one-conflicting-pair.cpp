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
#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>> conflictingPairs) {
        // For each right endpoint r, we need to find the minimum left endpoint
        // such that subarray [l, r] is valid (no conflicting pair both in it).
        // 
        // For a conflicting pair (a, b) with a < b, when right endpoint = b,
        // the left endpoint must be > a to avoid including both.
        // So for each r, limit[r] = max over all pairs (a,b) with b<=r of (a+1... wait)
        // 
        // More precisely: for right endpoint r, the minimum allowed left is:
        // minLeft[r] = max(minLeft[r-1], for each pair (a,b) with max(a,b)=r: min(a,b)+1)
        // 
        // Base count without removing anything: sum over r of (r - minLeft[r] + 1 - (minLeft[r]-1))
        // = sum over r of (r - minLeft[r] + 1) where minLeft starts at 1
        // Wait: number of valid subarrays ending at r = r - minLeft[r] + 1
        
        // When we remove one pair, we might increase minLeft for certain r values.
        // 
        // Strategy:
        // 1. Compute minLeft[r] for all r (the minimum left boundary for subarrays ending at r)
        // 2. Base answer = sum(r - minLeft[r] + 1) for r=1..n
        // 3. For each pair removed, compute the gain
        
        // For each right endpoint r, track which pair(s) are "active" (achieving the max).
        // When we remove a pair, the gain for endpoint r is: new_minLeft[r] - minLeft[r] (decrease in minLeft = more subarrays)
        
        // Let's group pairs by their max element.
        // For each r, compute:
        //   - top1: the highest lower bound contributed by pairs ending at r or before
        //   - which pair caused top1
        //   - top2: second highest lower bound
        
        // minLeft[r] = max(minLeft[r-1], contributions from pairs with max=r)
        // The "controlling" pair at r is the one that set minLeft[r].
        
        // For each pair p, removing p gives gain = sum over all r where p is the sole controller
        // of (second_best[r] - best[r]) ... but this needs careful tracking.
        
        // Let's implement:
        // - For each position r from 1 to n, maintain current minLeft
        // - Track for each pair, total gain if removed
        
        vector<vector<pair<int,int>>> pairsAt(n + 1); // pairsAt[max(a,b)] = {min(a,b), pair_index}
        int m = conflictingPairs.size();
        for (int i = 0; i < m; i++) {
            int a = conflictingPairs[i][0], b = conflictingPairs[i][1];
            if (a > b) swap(a, b);
            // pair (a, b): when right endpoint >= b, left must be > a
            pairsAt[b].push_back({a, i});
        }
        
        // For each r, minLeft[r] = max(minLeft[r-1], max of (a+1) for pairs with max=r... 
        // Actually lower bound for left = a+1? No.
        // If pair is (a,b) with a<b, subarray [l,r] contains both iff l<=a and r>=b.
        // So for r>=b, we need l > a, i.e., l >= a+1.
        // So constraint: minLeft >= a+1 when r >= b.
        
        // We need to track: for each r, what is minLeft[r], and which pair index is responsible,
        // and what would minLeft[r] be if that pair were removed (second best).
        
        vector<long long> gain(m, 0); // gain[i] = extra subarrays if pair i is removed
        
        long long baseCount = 0;
        int curMin = 1; // current minLeft
        // We also need: best pair index causing curMin, and second best value
        // But minLeft can be set by accumulated max over all r' <= r.
        // 
        // Let's track: 
        //   curMin = current minLeft (accumulated)
        //   bestPairIdx = which pair last set curMin (-1 if none / initial)
        //   secondMin = what curMin would be if bestPairIdx were removed
        //   secondPairIdx = which pair set secondMin
        
        // This is tricky because multiple pairs accumulate. Let me think differently.
        // 
        // At each r, new constraints come in. The new minLeft = max(prevMinLeft, new constraints).
        // If the new constraint from pair i (value = a_i + 1) > prevMinLeft, then pair i is now controlling.
        // If two new constraints tie, we need both tracked.
        
        // Let's maintain:
        // lim1 = current minLeft (best = highest lower bound so far)
        // lim2 = second highest lower bound (if lim1 pair removed)
        // idx1 = pair index responsible for lim1 (-1 if from initial/multiple)
        // 
        // When we remove pair idx1, minLeft becomes lim2 for all r >= current r (until overridden)
        
        // gain[idx1] += (lim1 - lim2) * 1 for each r where idx1 is controlling
        // But gain accumulates over all r from when idx1 became controlling until it's overridden.
        
        // Let me simulate:
        int lim1 = 1, lim2 = 1; // lim1 >= lim2
        int idx1 = -1; // pair that set lim1 (-1 means no single pair, or initial)
        
        for (int r = 1; r <= n; r++) {
            // Process new pairs ending at r
            for (auto [a, pidx] : pairsAt[r]) {
                int newLim = a + 1;
                if (newLim > lim1) {
                    lim2 = lim1;
                    lim1 = newLim;
                    idx1 = pidx;
                } else if (newLim > lim2) {
                    lim2 = newLim;
                    // idx1 stays the same
                } else if (newLim == lim1 && pidx != idx1) {
                    // tie: if we remove idx1, lim1 stays because newLim == lim1
                    // so effectively lim2 = lim1
                    lim2 = lim1;
                    // idx1: now removing either one doesn't help, set idx1 = -1 to indicate
                    idx1 = -1;
                }
            }
            
            baseCount += (r - lim1 + 1);
            
            // If idx1 != -1, removing idx1 would give lim2 instead of lim1 for this r
            // gain = lim1 - lim2
            if (idx1 != -1) {
                gain[idx1] += (lim1 - lim2);
            }
        }
        
        long long maxGain = *max_element(gain.begin(), gain.end());
        return baseCount + maxGain;
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
