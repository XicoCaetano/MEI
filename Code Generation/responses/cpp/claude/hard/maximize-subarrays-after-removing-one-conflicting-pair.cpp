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