// task_id: maximize-active-section-with-trade-ii
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


class SparseTable {
public:
    vector<vector<long long>> st;
    int m;
    SparseTable(const vector<pair<int,int>>& a) {
        int n = (int)a.size() - 1;
        m = 1;
        while ((1 << m) <= n) ++m;
        st.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i) {
            int l1 = a[i].first, r1 = a[i].second;
            int l2 = a[i+1].first, r2 = a[i+1].second;
            st[i][0] = (long long)(r1 - l1) + (r2 - l2);
        }
        for (int j = 1; j < m; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }
    long long query(int l, int r) {
        if (l >= r) return 0;
        int len = r - l;
        int k = 0;
        while ((1 << (k + 1)) <= len) ++k;
        return max(st[l][k], st[r - (1 << k)][k]);
    }
};


// === MODEL RESPONSE ===
#include <bits/stdc++.h>
using namespace std;

class SparseTable {
public:
    vector<vector<long long>> st;
    int m;
    SparseTable(const vector<pair<int,int>>& a) {
        int n = (int)a.size() - 1;
        if (n <= 0) { m = 1; return; }
        m = 1;
        while ((1 << m) <= n) ++m;
        st.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i) {
            int l1 = a[i].first, r1 = a[i].second;
            int l2 = a[i+1].first, r2 = a[i+1].second;
            st[i][0] = (long long)(r1 - l1) + (r2 - l2);
        }
        for (int j = 1; j < m; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }
    long long query(int l, int r) {
        if (l >= r) return 0;
        int len = r - l;
        int k = 0;
        while ((1 << (k + 1)) <= len) ++k;
        return max(st[l][k], st[r - (1 << k)][k]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>> queries) {
        int n = s.size();
        
        // Build runs: list of (start, end) for each run of same character
        // We'll work with the augmented string conceptually
        // For each query [l,r], augmented = '1' + s[l..r] + '1'
        
        // Precompute prefix sum of 1s
        vector<int> pre(n+1, 0);
        for (int i = 0; i < n; i++) pre[i+1] = pre[i] + (s[i]=='1');
        
        // Build runs of the original string
        // runs[i] = {start, end} (0-indexed, end exclusive) for consecutive same chars
        vector<pair<int,int>> runs; // (start, end) in original string indices
        vector<char> runChar;
        {
            int i = 0;
            while (i < n) {
                int j = i;
                while (j < n && s[j] == s[i]) j++;
                runs.push_back({i, j});
                runChar.push_back(s[i]);
                i = j;
            }
        }
        
        int R = runs.size();
        
        // For a query [l, r]:
        // Augmented string t = '1' + s[l..r] + '1'
        // We need runs of t. The augmented 1s at ends don't count toward answer.
        // 
        // The trade: pick a block of '1's surrounded by '0's -> convert to 0's,
        // then pick a block of '0's surrounded by '1's -> convert to 1's.
        // This means: we pick consecutive runs pattern: ...0-block, 1-block, 0-block...
        // and replace the middle 1-block + two 0-blocks with all 1's.
        // Net gain = size(left-0-block) + size(right-0-block) - size(middle-1-block)... 
        // Wait, let me re-read.
        //
        // Trade: convert a contiguous block of '1's surrounded by '0's to all '0's,
        //        then convert a contiguous block of '0's surrounded by '1's to all '1's.
        // 
        // After step 1: some 1-block becomes 0. Now it merges with neighbors.
        // After step 2: some 0-block (surrounded by 1's) becomes 1.
        //
        // The optimal strategy: We want to find adjacent runs pattern:
        // 0-run A, 1-run B, 0-run C (in augmented string)
        // Convert B to 0's: A+B+C become one big 0-block
        // Then convert A+B+C to 1's (it's now surrounded by 1's from neighbors)
        // Net change: gain (|A| + |B| + |C|) - lose |B| - ... 
        // Actually net active = original_ones - |B| + |A| + |B| + |C| = original_ones + |A| + |C|
        //
        // So the gain from a trade choosing zero-runs A (index i) and C (index i+2) 
        // with 1-run B (index i+1) in between is |A| + |C|.
        // We want to maximize |A| + |C| over all valid consecutive (0-run, 1-run, 0-run) triples
        // within the augmented string's runs.
        //
        // For the augmented string: prepend '1' and append '1'.
        // The runs of augmented string:
        //   - If s[l] == '1': first run merges with prepended '1'
        //   - If s[l] == '0': prepended '1' is separate run of length 1
        //   Similarly for end.
        
        // For each query we need the runs of the augmented substring.
        // Then find max (size of 0-run[i] + size of 0-run[i+2]) among all 0-runs at positions i, i+2
        // where i+1 is a 1-run (consecutive triple 0,1,0 in runs).
        
        // To handle queries efficiently, we need a way to:
        // 1. Find which original runs overlap with [l, r]
        // 2. Build augmented runs
        // 3. Query max pair of consecutive 0-runs (with 1-run between)
        
        // The sparse table from starter code seems to be for querying max over pairs of 
        // consecutive zero-blocks in the runs array.
        
        // Let's build the global runs and a sparse table over pairs of zero-runs.
        // For a query [l,r], we need to find the relevant runs within [l,r] augmented.
        
        // Strategy:
        // - Identify runs that are entirely within [l,r], and partial runs at boundaries.
        // - The augmented '1' at ends effectively extends/creates 1-runs at boundaries.
        
        // Let me think about the runs of the augmented string for query [l,r]:
        // t = '1' + s[l..r] + '1'
        // 
        // The runs of s[l..r]:
        //   Find the run index in `runs` that contains l (call it rl)
        //   Find the run index in `runs` that contains r (call it rr)
        //
        // For the augmented string:
        //   - Left: if s[l]=='1', merge with the '1' -> first run has length (runs[rl].second - l) + 1
        //           but since augmented 1 doesn't count, its length for our purposes is runs[rl].second - l
        //           if s[l]=='0', we have a '1' run of length 1 (augmented, doesn't count) then 0-run
        //   - Right: similar
        //
        // The zero-runs that matter are entirely within [l,r].
        // A zero-run at the boundary might be partial.
        
        // For the sparse table approach on pairs of zero-runs:
        // We need zero-runs in the augmented string. The augmented 1s at ends mean:
        //   - The first and last runs in augmented are always 1-runs (possibly length 1 from augment)
        //   - Zero-runs in the middle are the ones we care about
        
        // Let me index only the zero-runs in the original string.
        // zero_runs[k] = {start, end} of k-th zero-run
        // For a query [l,r], the zero-runs within are those zero-runs entirely or partially in [l,r].
        // 
        // The trade gains = max over consecutive zero-runs (z_k, z_{k+1}) in augmented string
        // = max of (effective_size(z_k) + effective_size(z_{k+1}))
        // where effective_size clips to [l,r].
        //
        // And for this to be valid, between z_k and z_{k+1} there must be a 1-run,
        // and the 1-run must be surrounded by zeros (which it is by definition since z_k and z_{k+1} surround it).
        // Also the 1-run must be surrounded by '0's in the augmented string - this is automatically true
        // since the zeros are on both sides.
        // BUT: the 1-run at position 0 of augmented (the prepended '1') and end don't count as 
        // surrounding zeros... Actually the condition is: the 1-block we convert must be surrounded by 0's.
        // In the augmented string t, the augmented '1's at position 0 and end are there to provide 
        // the surrounding for the 0-blocks.
        
        // Let me re-read the problem:
        // After augmentation t = '1' + s[l..r] + '1':
        // - Convert a 1-block surrounded by 0's to 0's
        // - Convert a 0-block surrounded by 1's to 1's
        // The augmented 1's provide the "surrounded" condition for the outermost 0-blocks.
        
        // So valid zero-blocks to convert (in step 2) are those surrounded by 1's in t.
        // Since t starts and ends with '1', any zero-block in t is surrounded by 1's 
        // (directly or through other characters... no wait, it needs to be directly adjacent to 1's).
        // A zero-block is surrounded by 1's means its left neighbor run is '1' and right neighbor run is '1'.
        // In t, the first and last characters are '1', so any zero-block in t has 1's on both sides
        // (because t starts/ends with 1, so the pattern is always 1...0...1 for any zero block).
        // YES: since t = 1...1, every maximal zero-block in t is flanked by 1's.
        
        // Step 1: pick a 1-block in t that's surrounded by 0's. Convert to 0's.
        // A 1-block surrounded by 0's: not the first or last run of t (since those are the augmented 1's
        // or merged with them). Actually any 1-block that has 0's on both sides.
        
        // So the trade: pick zero-block A, 1-block B, zero-block C (consecutive in t),
        // convert B->0: now A+B+C is one big zero-block, still surrounded by 1's,
        // convert A+B+C -> 1's.
        // Net gain in active sections = |A| + |C| (we gain A and C, B was already converted to 0 first).
        // Wait: original active = ones in s[l..r]. After trade:
        //   lose |B| ones (B->0), gain |A|+|B|+|C| ones (the merged block -> 1)
        //   net change = |A| + |C|
        // So answer = pre[r+1]-pre[l] + max(|A|+|C|) over all valid (A,1-block,C) triples in t.
        // If no valid triple, answer = pre[r+1]-pre[l].
        
        // Now, zero-blocks A and C in t must be within s[l..r] (the augmented 1's aren't real zero-blocks).
        // The zero-blocks of t that come from s[l..r] are exactly the zero-runs of s that intersect [l,r],
        // clipped to [l,r].
        
        // For two consecutive zero-runs (no other zero-run between them) in the clipped s[l..r] augmented,
        // they must have exactly one 1-run between them, and that 1-run must not be the augmented 1.
        // Since augmented 1's are at the very ends of t, the 1-block between A and C must come from s[l..r].
        
        // So: find all zero-runs in s that intersect [l,r], clip them, find consecutive pairs,
        // maximize sum of sizes.
        
        // Now for efficiency with 1e5 queries and 1e5 string length:
        // We need O(log n) per query.
        
        // Build array of zero-runs (globally). For a query [l,r]:
        // - Find leftmost zero-run intersecting [l,r]: call it index zl
        // - Find rightmost zero-run intersecting [l,r]: call it index zr
        // - The zero-runs fully inside [l,r]: from zl+1 to zr-1 (or zl to zr if fully inside)
        //   Actually zl might be partial (l is inside it), zr might be partial.
        // - We want max over consecutive pairs (z_k, z_{k+1}) for zl <= k < zr, k+1 <= zr
        //   where sizes are clipped.
        
        // The clipped sizes:
        //   z_k clipped size = min(zero_runs[k].second, r+1) - max(zero_runs[k].first, l)
        //   But only zero-runs that actually intersect [l,r].
        
        // For pairs entirely in the interior (zl < k and k+1 < zr):
        //   Both runs are fully inside [l,r], so their sizes are as-is.
        //   This is a range max query: max of (size(z_k) + size(z_{k+1})) for zl < k < zr, k < zr
        //   i.e., among fully interior consecutive zero-run pairs.
        
        // For boundary pairs:
        //   (zl, zl+1): left run might be clipped on the left, right run might be interior
        //   (zr-1, zr): left run might be interior, right run might be clipped on the right
        //   (zl, zr) if zl+1 == zr: both might be clipped
        
        // The sparse table can handle the interior range max.
        // Boundary cases are O(1) per query.
        
        // Let's implement this.
        
        // Collect zero-runs
        vector<pair<int,int>> zruns; // zero-runs (start, end) end exclusive
        for (int i = 0; i < R; i++) {
            if (runChar[i] == '0') {
                zruns.push_back(runs[i]);
            }
        }
        int ZR = zruns.size();
        
        // For each zero-run index k, precompute size
        vector<int> zsize(ZR);
        for (int k = 0; k < ZR; k++) zsize[k] = zruns[k].second - zruns[k].first;
        
        // Build sparse table for max(zsize[k] + zsize[k+1]) for consecutive zero-run pairs
        // But we need: between zero-run k and k+1, is there exactly one 1-run? Yes, by construction.
        // And that 1-run must be in s[l..r]... it is if both zero-runs intersect [l,r] (since 1-run is between them).
        // Actually if both z_k and z_{k+1} intersect [l,r], the 1-run between them is entirely in [l,r]
        // (since it's between z_k.first and z_{k+1}.second, and both intersect [l,r]... hmm not necessarily).
        // Actually z_k.second <= 1-run.start and 1-run.end <= z_{k+1}.first.
        // If z_k intersects [l,r] (z_k.first < r+1 and z_k.second > l) and 
        //    z_{k+1} intersects [l,r] (z_{k+1}.first < r+1 and z_{k+1}.second > l),
        // then the 1-run between them: its start = z_k.second, end = z_{k+1}.first.
        // For the 1-run to be in [l,r]: we need l <= z_k.second and z_{k+1}.first <= r... 
        // Hmm. Actually we need the 1-run to be surrounded by zeros in t. In t, it's surrounded by 
        // z_k (clipped) and z_{k+1} (clipped). As long as both clipped sizes > 0, the 1-run is surrounded.
        // So condition: clipped size of z_k > 0 AND clipped size of z_{k+1} > 0 AND 1-run is in [l,r].
        // The 1-run is in [l,r] iff z_k.second >= l and z_{k+1}.first <= r... 
        // Actually z_k.second (end of z_k = start of 1-run). Since z_k intersects [l,r], z_k.second > l.
        // And z_{k+1}.first = end of 1-run. Since z_{k+1} intersects [l,r], z_{k+1}.first < r+1, i.e., <= r.
        // So 1-run start = z_k.second (>= l since z_k intersects [l,r] means z_k.second > l... 
        // not quite: z_k.first < r+1 and z_k.second > l. So z_k.second > l means 1-run starts after l. Good.
        // z_{k+1}.first <= r means 1-run ends at or before r+1... z_{k+1}.first <= r means end <= r. Good.
        // So if both zero-runs intersect [l,r], the 1-run between them is within [l,r]. 
        
        // Build sparse table for consecutive zero-run pairs
        // st_val[k] = zsize[k] + zsize[k+1] for k in [0, ZR-2]
        // We want range max of st_val[k] for k in [zl, zr-1] but with potential boundary adjustments.
        
        // Actually we want:
        // For interior pairs: zl+1 <= k and k+1 <= zr-1, i.e., k in [zl+1, zr-2]
        //   (both zero-runs fully inside [l,r])
        // Hmm wait. A zero-run is fully inside [l,r] iff zruns[k].first >= l and zruns[k].second <= r+1... 
        // end exclusive so zruns[k].second-1 <= r, i.e., zruns[k].second <= r+1. Yes.
        
        // Let me define:
        // zl = first zero-run index intersecting [l,r]  (lower_bound on second > l, i.e., find first with .second > l)
        // zr = last zero-run index intersecting [l,r]   (find last with .first <= r)
        
        // For simplicity, let me build the sparse table for max(zsize[k]+zsize[k+1]) over range of k.
        
        // Precompute prefix max isn't enough since we need range max. Use sparse table.
        
        if (ZR == 0) {
            // No zero-runs, no trade possible
            vector<int> ans;
            for (auto& q : queries) {
                ans.push_back(pre[q[1]+1] - pre[q[0]]);
            }
            return ans;
        }
        
        // Build sparse table on consecutive pair sums
        int M = ZR - 1; // number of consecutive pairs
        int LOG = 1;
        while ((1 << LOG) <= M) LOG++;
        vector<vector<int>> spTable(max(M, 1), vector<int>(LOG, 0));
        if (M > 0) {
            for (int k = 0; k < M; k++) spTable[k][0] = zsize[k] + zsize[k+1];
            for (int j = 1; j < LOG; j++)
                for (int k = 0; k + (1<<j) <= M; k++)
                    spTable[k][j] = max(spTable[k][j-1], spTable[k+(1<<(j-1))][j-1]);
        }
        
        auto rangeMax = [&](int l2, int r2) -> int { // inclusive range [l2,r2] of pair indices
            if (l2 > r2) return -1;
            int len = r2 - l2 + 1;
            int k = __lg(len);
            return max(spTable[l2][k], spTable[r2-(1<<k)+1][k]);
        };
        
        // For zero-run index binary search
        // Find first zero-run with .second > l (i.e., intersects from left side)
        // Find last zero-run with .first <= r
        
        auto findZl = [&](int l) -> int {
            // first k with zruns[k].second > l
            int lo = 0, hi = ZR;
            while (lo < hi) {
                int mid = (lo+hi)/2;
                if (zruns[mid].second > l) hi = mid;
                else lo = mid+1;
            }
            return lo; // ZR if none
        };
        
        auto findZr = [&](int r) -> int {
            // last k with zruns[k].first <= r
            int lo = -1, hi = ZR-1;
            while (lo < hi) {
                int mid = (lo+hi+1)/2;
                if (zruns[mid].first <= r) lo = mid;
                else hi = mid-1;
            }
            return lo; // -1 if none
        };
        
        vector<int> ans;
        ans.reserve(queries.size());
        
        for (auto& q : queries) {
            int l = q[0], r = q[1];
            int ones = pre[r+1] - pre[l];
            
            int zl = findZl(l); // first zero-run intersecting [l,r]
            int zr_idx = findZr(r); // last zero-run intersecting [l,r]
            
            if (zl > zr_idx || zl == ZR) {
                // No zero-runs in [l,r]
                ans.push_back(ones);
                continue;
            }
            
            // Number of zero-runs intersecting [l,r]
            int cnt = zr_idx - zl + 1;
            if (cnt < 2) {
                // Only one zero-run, can't do the trade (need two zero-runs with a 1-run between)
                ans.push_back(ones);
                continue;
            }
            
            // We need to find max (clipped_size(z_a) + clipped_size(z_b)) for consecutive a,b in [zl, zr_idx]
            // clipped_size(k) = min(zruns[k].second, r+1) - max(zruns[k].first, l)
            
            // For fully interior zero-runs k: max(zruns[k].first, l) = zruns[k].first, min(zruns[k].second, r+1)=zruns[k].second
            // That's true when zruns[k].first >= l AND zruns[k].second <= r+1 (i.e., last char index <= r)
            // i.e., zruns[k].first >= l AND zruns[k].second-1 <= r
            
            // zl might be partial on left, zr_idx might be partial on right
            // Interior zero-runs: [zl+1, zr_idx-1] if cnt >= 3 (or just [zl, zr_idx] if all fully interior)
            
            // Actually: is zl partial? Only if zruns[zl].first < l (the run starts before l)
            // Is zr_idx partial? Only if zruns[zr_idx].second > r+1 (the run ends after r)
            
            bool zlPartial = (zruns[zl].first < l);
            bool zrPartial = (zruns[zr_idx].second > r+1);
            
            // Clipped sizes of boundary runs
            int clippedZl = min(zruns[zl].second, r+1) - max(zruns[zl].first, l);
            int clippedZr = min(zruns[zr_idx].second, r+1) - max(zruns[zr_idx].first, l);
            
            int bestGain = 0;
            
            // Consider all consecutive pairs (k, k+1) for k in [zl, zr_idx-1]
            // Pair (zl, zl+1): clippedZl + (clipped or full size of zl+1)
            // Pair (zr_idx-1, zr_idx): (full or clipped zr_idx-1) + clippedZr
            // Interior pairs (k, k+1) for k in [zl+1, zr_idx-2]: both full sizes -> sparse table
            
            if (cnt == 2) {
                // Only pair is (zl, zr_idx)
                bestGain = clippedZl + clippedZr;
            } else {
                // Multiple pairs
                // Boundary pair (zl, zl+1):
                int sizeZl1 = zsize[zl+1]; // fully interior if zl+1 < zr_idx or even if zl+1 == zr_idx but not partial
                // zl+1 < zr_idx means it's interior. If zl+1 == zr_idx, use clippedZr.
                // Wait, zl+1 could equal zr_idx only if cnt==2, handled above.
                // Here cnt>=3, so zl+1 <= zr_idx-1, so zl+1 is interior (fully inside [l,r])
                // Actually is zl+1 guaranteed fully inside? zruns[zl+1].first >= zruns[zl].second > l ✓
                // zruns[zl+1].second <= zruns[zr_idx].first <= r ✓ (since zr_idx > zl+1)
                // Wait zruns[zr_idx].first <= r (since it intersects [l,r]). And zruns[zl+1].second <= zruns[zl+2].first <= ... <= zruns[zr_idx].first <= r. ✓
                bestGain = max(bestGain, clippedZl + sizeZl1);
                
                // Boundary pair (zr_idx-1, zr_idx):
                int sizeZr1 = zsize[zr_idx-1]; // fully interior since zr_idx-1 >= zl+1
                bestGain = max(bestGain, sizeZr1 + clippedZr);
                
                // Interior pairs: k in [zl+1, zr_idx-2], query pairs [zl+1, zr_idx-2]
                if (zl+1 <= zr_idx-2) {
                    // pair indices: k in [zl+1, zr_idx-2] means pair (k, k+1) both in [zl+1, zr_idx-1]
                    // rangeMax on pair index range [zl+1, zr_idx-2]
                    int rm = rangeMax(zl+1, zr_idx-2);
                    if (rm > 0) bestGain = max(bestGain, rm);
                }
            }
            
            ans.push_back(ones + bestGain);
        }
        
        return ans;
    }
};

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.maxActiveSectionsAfterTrade("0100", vector<vector<int>>{vector<int>{0, 3}, vector<int>{0, 2}, vector<int>{1, 3}, vector<int>{2, 3}}) == vector<int>{4, 3, 1, 1}));
    assert((sol.maxActiveSectionsAfterTrade("01", vector<vector<int>>{vector<int>{0, 1}}) == vector<int>{1}));
    assert((sol.maxActiveSectionsAfterTrade("01010", vector<vector<int>>{vector<int>{0, 3}, vector<int>{1, 4}, vector<int>{1, 3}}) == vector<int>{4, 4, 2}));
    assert((sol.maxActiveSectionsAfterTrade("1000100", vector<vector<int>>{vector<int>{1, 5}, vector<int>{0, 6}, vector<int>{0, 4}}) == vector<int>{6, 7, 2}));
    assert((sol.maxActiveSectionsAfterTrade("111111111111111111111111111111111111111111111111", vector<vector<int>>{vector<int>{0, 39}, vector<int>{1, 38}, vector<int>{2, 37}, vector<int>{3, 36}, vector<int>{4, 35}, vector<int>{5, 34}, vector<int>{6, 33}, vector<int>{7, 32}, vector<int>{8, 31}, vector<int>{9, 30}}) == vector<int>{48, 48, 48, 48, 48, 48, 48, 48, 48, 48}));
    assert((sol.maxActiveSectionsAfterTrade("11111111111111111", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{17, 17, 17, 17, 17}));
    assert((sol.maxActiveSectionsAfterTrade("10000000010000000001000000001", vector<vector<int>>{vector<int>{0, 20}, vector<int>{5, 15}, vector<int>{10, 19}}) == vector<int>{21, 14, 4}));
    assert((sol.maxActiveSectionsAfterTrade("000000000000000000000000000000000000000000000000", vector<vector<int>>{vector<int>{0, 39}, vector<int>{1, 38}, vector<int>{2, 37}, vector<int>{3, 36}, vector<int>{4, 35}, vector<int>{5, 34}, vector<int>{6, 33}, vector<int>{7, 32}, vector<int>{8, 31}, vector<int>{9, 30}}) == vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert((sol.maxActiveSectionsAfterTrade("11001100110011001100110011", vector<vector<int>>{vector<int>{0, 20}, vector<int>{5, 15}, vector<int>{0, 9}, vector<int>{10, 19}, vector<int>{15, 25}}) == vector<int>{18, 18, 18, 18, 18}));
    assert((sol.maxActiveSectionsAfterTrade("111100001111000011110000", vector<vector<int>>{vector<int>{0, 23}, vector<int>{4, 19}, vector<int>{5, 18}, vector<int>{6, 17}, vector<int>{7, 16}, vector<int>{8, 15}, vector<int>{9, 14}, vector<int>{10, 13}, vector<int>{11, 12}}) == vector<int>{20, 20, 19, 18, 17, 12, 12, 12, 12}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001001001001001", vector<vector<int>>{vector<int>{0, 24}, vector<int>{2, 22}, vector<int>{3, 21}, vector<int>{4, 20}, vector<int>{5, 19}, vector<int>{6, 18}, vector<int>{7, 17}, vector<int>{8, 16}, vector<int>{9, 15}, vector<int>{10, 14}, vector<int>{11, 13}}) == vector<int>{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 11}));
    assert((sol.maxActiveSectionsAfterTrade("00101010101010101010", vector<vector<int>>{vector<int>{0, 9}, vector<int>{5, 15}, vector<int>{10, 19}}) == vector<int>{12, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("10101010101010101010101010", vector<vector<int>>{vector<int>{0, 25}, vector<int>{1, 24}, vector<int>{2, 23}, vector<int>{3, 22}, vector<int>{4, 21}}) == vector<int>{15, 15, 15, 15, 15}));
    assert((sol.maxActiveSectionsAfterTrade("101010101010101010101010101010101010101010101010101010101010", vector<vector<int>>{vector<int>{0, 59}, vector<int>{1, 58}, vector<int>{2, 57}, vector<int>{3, 56}, vector<int>{4, 55}, vector<int>{5, 54}, vector<int>{6, 53}, vector<int>{7, 52}, vector<int>{8, 51}, vector<int>{9, 50}}) == vector<int>{32, 32, 32, 32, 32, 32, 32, 32, 32, 32}));
    assert((sol.maxActiveSectionsAfterTrade("111000111000111", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{3, 11}, vector<int>{4, 10}}) == vector<int>{15, 15, 15, 15, 13}));
    assert((sol.maxActiveSectionsAfterTrade("000011110000111100001111", vector<vector<int>>{vector<int>{0, 23}, vector<int>{4, 19}, vector<int>{5, 18}, vector<int>{6, 17}, vector<int>{7, 16}, vector<int>{8, 15}, vector<int>{9, 14}, vector<int>{10, 13}, vector<int>{11, 12}}) == vector<int>{20, 20, 19, 18, 17, 12, 12, 12, 12}));
    assert((sol.maxActiveSectionsAfterTrade("111000111000", vector<vector<int>>{vector<int>{0, 11}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}}) == vector<int>{12, 6, 6, 6}));
    assert((sol.maxActiveSectionsAfterTrade("01010101010101010101010101010101", vector<vector<int>>{vector<int>{0, 15}, vector<int>{15, 30}, vector<int>{0, 29}}) == vector<int>{18, 18, 18}));
    assert((sol.maxActiveSectionsAfterTrade("10101010101010101010", vector<vector<int>>{vector<int>{0, 19}, vector<int>{1, 18}, vector<int>{2, 17}, vector<int>{3, 16}, vector<int>{4, 15}, vector<int>{5, 14}, vector<int>{6, 13}, vector<int>{7, 12}, vector<int>{8, 11}, vector<int>{9, 10}}) == vector<int>{12, 12, 12, 12, 12, 12, 12, 12, 12, 10}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001001001", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{5, 13}, vector<int>{3, 14}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("11110000111100001111", vector<vector<int>>{vector<int>{0, 9}, vector<int>{5, 15}, vector<int>{10, 19}}) == vector<int>{12, 19, 12}));
    assert((sol.maxActiveSectionsAfterTrade("1010101010", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}}) == vector<int>{7, 7, 7, 7}));
    assert((sol.maxActiveSectionsAfterTrade("0000011111000001111100000111110000011111", vector<vector<int>>{vector<int>{0, 9}, vector<int>{10, 19}, vector<int>{20, 29}, vector<int>{30, 39}, vector<int>{0, 39}}) == vector<int>{20, 20, 20, 20, 30}));
    assert((sol.maxActiveSectionsAfterTrade("1100001100011110001000000011001", vector<vector<int>>{vector<int>{5, 15}, vector<int>{2, 20}, vector<int>{0, 30}, vector<int>{10, 25}}) == vector<int>{16, 19, 22, 22}));
    assert((sol.maxActiveSectionsAfterTrade("00000100000100000", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{5, 10}, vector<int>{3, 8}}) == vector<int>{12, 11, 10, 2, 7}));
    assert((sol.maxActiveSectionsAfterTrade("00000000000000000", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.maxActiveSectionsAfterTrade("0101010101010101010", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{5, 13}, vector<int>{3, 14}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("000100010001000100010001000100010001000100010001000100010001", vector<vector<int>>{vector<int>{0, 59}, vector<int>{1, 58}, vector<int>{2, 57}, vector<int>{3, 56}, vector<int>{4, 55}, vector<int>{5, 54}, vector<int>{6, 53}, vector<int>{7, 52}, vector<int>{8, 51}, vector<int>{9, 50}}) == vector<int>{21, 21, 21, 21, 21, 21, 21, 21, 21, 21}));
    assert((sol.maxActiveSectionsAfterTrade("10101010101010101", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("0101010101", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}}) == vector<int>{7, 7, 7, 7}));
    assert((sol.maxActiveSectionsAfterTrade("01010101010101010101010101", vector<vector<int>>{vector<int>{0, 25}, vector<int>{1, 24}, vector<int>{2, 23}, vector<int>{3, 22}, vector<int>{4, 21}}) == vector<int>{15, 15, 15, 15, 15}));
    assert((sol.maxActiveSectionsAfterTrade("1100110011", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}, vector<int>{4, 5}}) == vector<int>{10, 10, 10, 8, 6}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}, vector<int>{4, 5}}) == vector<int>{8, 8, 7, 4, 4}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001001001", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{3, 15}, vector<int>{4, 14}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("0000000000", vector<vector<int>>{vector<int>{0, 9}, vector<int>{2, 7}, vector<int>{4, 6}}) == vector<int>{0, 0, 0}));
    assert((sol.maxActiveSectionsAfterTrade("1111111111", vector<vector<int>>{vector<int>{0, 9}, vector<int>{2, 7}, vector<int>{4, 6}}) == vector<int>{10, 10, 10}));
    assert((sol.maxActiveSectionsAfterTrade("110001100110001", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{5, 10}, vector<int>{3, 8}}) == vector<int>{12, 12, 12, 7, 11}));
    assert((sol.maxActiveSectionsAfterTrade("0000011111000001111100000", vector<vector<int>>{vector<int>{0, 24}, vector<int>{1, 23}, vector<int>{2, 22}, vector<int>{3, 21}, vector<int>{4, 20}, vector<int>{5, 19}, vector<int>{6, 18}, vector<int>{7, 17}, vector<int>{8, 16}, vector<int>{9, 15}}) == vector<int>{20, 19, 18, 17, 16, 10, 10, 10, 10, 10}));
    assert((sol.maxActiveSectionsAfterTrade("100100100100100", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{3, 11}, vector<int>{4, 10}, vector<int>{5, 9}}) == vector<int>{9, 9, 9, 9, 9, 8}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001", vector<vector<int>>{vector<int>{0, 12}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}}) == vector<int>{9, 9, 9, 8, 5}));
    assert((sol.maxActiveSectionsAfterTrade("1000000001", vector<vector<int>>{vector<int>{1, 8}, vector<int>{0, 9}, vector<int>{2, 7}, vector<int>{3, 6}}) == vector<int>{2, 2, 2, 2}));
    assert((sol.maxActiveSectionsAfterTrade("0000011110001110000", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{3, 15}, vector<int>{4, 14}, vector<int>{5, 13}}) == vector<int>{15, 14, 13, 12, 11, 7}));
    assert((sol.maxActiveSectionsAfterTrade("00110011001100110", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{12, 12, 12, 11, 12}));

    cout << "All tests passed for maximize-active-section-with-trade-ii" << endl;
    return 0;
}
