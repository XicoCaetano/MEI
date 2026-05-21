#include <bits/stdc++.h>
using namespace std;

class LazyHeap {
public:
    priority_queue<long long, vector<long long>, greater<long long>> heap;
    unordered_map<long long, int> remove_cnt;
    int size_ = 0;
    long long sum_ = 0;

    void remove(long long x) {
        remove_cnt[x] += 1;
        size_ -= 1;
        sum_ -= x;
    }
    void apply_remove() {
        while (!heap.empty() && remove_cnt[heap.top()] > 0) {
            remove_cnt[heap.top()] -= 1;
            heap.pop();
        }
    }
    long long top() {
        apply_remove();
        return heap.top();
    }
    long long pop() {
        apply_remove();
        size_ -= 1;
        long long t = heap.top();
        sum_ -= t;
        heap.pop();
        return t;
    }
    void push(long long x) {
        if (remove_cnt[x] > 0) {
            remove_cnt[x] -= 1;
        } else {
            heap.push(x);
        }
        size_ += 1;
        sum_ += x;
    }
    long long pushpop(long long x) {
        apply_remove();
        if (heap.empty() || x <= heap.top()) return x;
        long long t = heap.top();
        sum_ += x - t;
        heap.pop();
        heap.push(x);
        return t;
    }
};

class Solution {
public:
    static constexpr long long INF = 4000000000000000000LL;

    // Cost to make all elements in nums[i..i+x-1] equal to their median
    // Returns sliding window median costs for each window of size x
    vector<long long> medianSlidingWindow(const vector<int>& nums, int x) {
        int n = nums.size();
        vector<long long> costs;
        
        // Use two heaps: max-heap for lower half, min-heap for upper half
        // lo: max-heap (negate values)
        // hi: min-heap
        priority_queue<long long> lo; // max heap
        priority_queue<long long, vector<long long>, greater<long long>> hi; // min heap
        
        unordered_map<long long, int> lo_del, hi_del;
        long long lo_sum = 0, hi_sum = 0;
        int lo_size = 0, hi_size = 0;
        
        auto lo_push = [&](long long v) {
            lo.push(v); lo_sum += v; lo_size++;
        };
        auto hi_push = [&](long long v) {
            hi.push(v); hi_sum += v; hi_size++;
        };
        auto lo_pop = [&]() -> long long {
            while (!lo.empty() && lo_del[lo.top()] > 0) {
                lo_del[lo.top()]--; lo.pop();
            }
            long long v = lo.top(); lo.pop();
            lo_sum -= v; lo_size--;
            return v;
        };
        auto hi_pop = [&]() -> long long {
            while (!hi.empty() && hi_del[hi.top()] > 0) {
                hi_del[hi.top()]--; hi.pop();
            }
            long long v = hi.top(); hi.pop();
            hi_sum -= v; hi_size--;
            return v;
        };
        auto lo_top = [&]() -> long long {
            while (!lo.empty() && lo_del[lo.top()] > 0) {
                lo_del[lo.top()]--; lo.pop();
            }
            return lo.top();
        };
        auto lo_lazy_remove = [&](long long v) {
            lo_del[v]++; lo_sum -= v; lo_size--;
        };
        auto hi_lazy_remove = [&](long long v) {
            hi_del[v]++; hi_sum -= v; hi_size--;
        };
        
        // lo has ceil(x/2) elements (median), hi has floor(x/2)
        int lo_target = (x + 1) / 2;
        
        for (int i = 0; i < n; i++) {
            long long v = nums[i];
            // Insert
            if (lo_size == 0 || v <= lo_top()) {
                lo_push(v);
            } else {
                hi_push(v);
            }
            
            // Rebalance
            while (lo_size > lo_target) {
                hi_push(lo_pop());
            }
            while (lo_size < lo_target) {
                lo_push(hi_pop());
            }
            
            if (i >= x - 1) {
                // Compute cost: median is lo_top()
                long long median = lo_top();
                // cost = median * lo_size - lo_sum + hi_sum - median * hi_size
                long long cost = median * lo_size - lo_sum + hi_sum - median * hi_size;
                costs.push_back(cost);
                
                // Remove element going out of window
                long long rem = nums[i - x + 1];
                if (rem <= lo_top()) {
                    lo_lazy_remove(rem);
                } else {
                    hi_lazy_remove(rem);
                }
                // Rebalance after removal
                while (lo_size > lo_target) {
                    hi_push(lo_pop());
                }
                while (lo_size < lo_target && hi_size > 0) {
                    lo_push(hi_pop());
                }
            }
        }
        
        return costs;
    }

    long long minOperations(vector<int> nums, int x, int k) {
        int n = nums.size();
        // cost[i] = minimum operations to make nums[i..i+x-1] all equal
        vector<long long> cost = medianSlidingWindow(nums, x);
        // m = number of possible windows
        int m = cost.size(); // m = n - x + 1
        
        // DP: dp[j][i] = min cost to place j non-overlapping subarrays
        // where the last one ends at position i (0-indexed in cost array, meaning window starts at i)
        // Window j starts at index i in nums, occupies [i, i+x-1]
        
        // dp[j][i] = min ops using j subarrays, last starting at i
        // Transition: dp[j][i] = cost[i] + min(dp[j-1][p]) for p <= i-x
        
        // We'll use 1D DP with prefix minimum
        // prev[i] = dp[j-1][i]
        // For j-th layer: dp[j][i] = cost[i] + min(prev[0..i-x])
        
        vector<long long> prev(m, INF);
        // j=1
        for (int i = 0; i < m; i++) {
            prev[i] = cost[i];
        }
        
        for (int j = 2; j <= k; j++) {
            vector<long long> curr(m, INF);
            // curr[i] = cost[i] + min(prev[0..i-x])
            long long min_prev = INF;
            for (int i = 0; i < m; i++) {
                // Can use prev[i-x] if i-x >= 0
                if (i - x >= 0 && prev[i - x] < min_prev) {
                    min_prev = prev[i - x];
                }
                if (min_prev < INF) {
                    curr[i] = cost[i] + min_prev;
                }
            }
            prev = curr;
        }
        
        long long ans = INF;
        for (int i = 0; i < m; i++) {
            ans = min(ans, prev[i]);
        }
        return ans;
    }
};