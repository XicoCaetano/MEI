// task_id: minimum-operations-to-make-elements-within-k-subarrays-equal
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


// === MODEL RESPONSE ===
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.minOperations(vector<int>{1000000, -1000000, 1000000, -1000000, 1000000}, 2, 2) == 4000000LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10, 1) == 0LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 2, 5) == 0LL));
    assert((sol.minOperations(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 5, 2) == 0LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 2) == 0LL));
    assert((sol.minOperations(vector<int>{9, -2, -2, -2, 1, 5}, 2, 2) == 3LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 4) == 0LL));
    assert((sol.minOperations(vector<int>{1, 2, 1, 2, 1, 2, 1, 2, 1, 2}, 2, 5) == 5LL));
    assert((sol.minOperations(vector<int>{5, -2, 1, 3, 7, 3, 6, 4, -1}, 3, 2) == 8LL));
    assert((sol.minOperations(vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 4, 2) == 0LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, 3, 3) == 6LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3, 3) == 6LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 1) == 0LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 2, 3) == 3LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5, 1) == 6LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9, 10, 10, 10}, 3, 9) == 0LL));
    assert((sol.minOperations(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75}, 5, 3) == 90LL));
    assert((sol.minOperations(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500}, 5, 3) == 1800LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, 3, 10) == 20LL));
    assert((sol.minOperations(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150}, 5, 3) == 180LL));
    assert((sol.minOperations(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 10, 2) == 0LL));
    assert((sol.minOperations(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 4, 7) == 4000000000000000000LL));
    assert((sol.minOperations(vector<int>{1000000, 999999, 1000001, 1000000, 999999, 1000001, 1000000, 999999, 1000001, 1000000}, 2, 5) == 6LL));
    assert((sol.minOperations(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 5, 4) == 0LL));
    assert((sol.minOperations(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25}, 5, 2) == 24LL));
    assert((sol.minOperations(vector<int>{-1, -1, -1, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5}, 3, 4) == 0LL));
    assert((sol.minOperations(vector<int>{-10, -20, -30, -40, -50, -60, -70, -80, -90, -100}, 5, 2) == 120LL));
    assert((sol.minOperations(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15}, 4, 4) == 4000000000000000000LL));
    assert((sol.minOperations(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29}, 3, 5) == 20LL));
    assert((sol.minOperations(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130}, 4, 3) == 120LL));
    assert((sol.minOperations(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31}, 5, 3) == 36LL));
    assert((sol.minOperations(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10}, 5, 4) == 24LL));
    assert((sol.minOperations(vector<int>{100, 50, 100, 50, 100, 50, 100, 50, 100, 50, 100, 50, 100, 50}, 3, 4) == 200LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, 5, 5) == 30LL));
    assert((sol.minOperations(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250}, 5, 5) == 300LL));
    assert((sol.minOperations(vector<int>{1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2, 1, 1, 2, 2}, 2, 10) == 0LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5, 3) == 0LL));
    assert((sol.minOperations(vector<int>{100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115}, 5, 3) == 18LL));
    assert((sol.minOperations(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, 10, 2) == 0LL));
    assert((sol.minOperations(vector<int>{1, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1}, 2, 10) == 8LL));
    assert((sol.minOperations(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, 5, 4) == 0LL));
    assert((sol.minOperations(vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}, 4, 5) == 0LL));
    assert((sol.minOperations(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 5, 10) == 0LL));
    assert((sol.minOperations(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000}, 6, 3) == 2700LL));
    assert((sol.minOperations(vector<int>{10, 15, 10, 20, 25, 20, 30, 35, 30, 40, 45, 40, 50, 55, 50}, 3, 5) == 25LL));
    assert((sol.minOperations(vector<int>{1000000, -1000000, 1000000, -1000000, 1000000, -1000000, 1000000, -1000000}, 4, 2) == 8000000LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10, 3) == 0LL));
    assert((sol.minOperations(vector<int>{7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26}, 5, 4) == 24LL));
    assert((sol.minOperations(vector<int>{10, 15, 10, 20, 25, 30, 35, 40, 45, 50, 55, 60, 65, 70, 75, 80, 85, 90, 95, 100, 105, 110, 115, 120, 125}, 7, 3) == 175LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, 5, 6) == 36LL));
    assert((sol.minOperations(vector<int>{-1, -1, -1, -1, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 7, 7, 7, 7, 8, 8, 8, 8, 9, 9, 9, 9, 10, 10, 10, 10}, 4, 5) == 0LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10, 2) == 0LL));
    assert((sol.minOperations(vector<int>{5, 5, 5, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3}, 3, 4) == 0LL));
    assert((sol.minOperations(vector<int>{10, 15, 10, 15, 10, 15, 10, 15, 10, 15}, 5, 2) == 20LL));
    assert((sol.minOperations(vector<int>{10, 10, 10, 20, 20, 20, 30, 30, 30, 40, 40, 40, 50, 50, 50}, 3, 5) == 0LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 4, 3, 2, 1, 2, 3, 4, 5, 4, 3, 2, 1, 2, 3, 4}, 4, 3) == 6LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, 5, 5) == 30LL));
    assert((sol.minOperations(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150}, 5, 3) == 180LL));
    assert((sol.minOperations(vector<int>{1, 100, 2, 99, 3, 98, 4, 97, 5, 96, 6, 95, 7, 94, 8, 93, 9, 92, 10, 91, 11, 90, 12, 89}, 4, 6) == 1056LL));
    assert((sol.minOperations(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000}, 5, 4) == 2400LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, 5, 4) == 24LL));
    assert((sol.minOperations(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, 5, 5) == 30LL));
    assert((sol.minOperations(vector<int>{-1, -1, -1, 0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9}, 3, 10) == 0LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100}, 10, 10) == 250LL));
    assert((sol.minOperations(vector<int>{100, -100, 200, -200, 300, -300, 400, -400, 500, -500, 600, -600, 700, -700, 800, -800}, 4, 4) == 7200LL));
    assert((sol.minOperations(vector<int>{-50, -50, -50, -50, -50, 50, 50, 50, 50, 50, -50, -50, -50, -50, -50, 50, 50, 50, 50, 50}, 5, 4) == 0LL));
    assert((sol.minOperations(vector<int>{100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, 10, 2) == 0LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50}, 10, 5) == 125LL));
    assert((sol.minOperations(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20}, 4, 5) == 20LL));
    assert((sol.minOperations(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, 5, 10) == 0LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50}, 7, 5) == 60LL));
    assert((sol.minOperations(vector<int>{5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19}, 5, 5) == 30LL));
    assert((sol.minOperations(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 3, 8) == 0LL));
    assert((sol.minOperations(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10}, 4, 5) == 10LL));
    assert((sol.minOperations(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60}, 6, 10) == 90LL));
    assert((sol.minOperations(vector<int>{5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14}, 4, 5) == 20LL));
    assert((sol.minOperations(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, 4, 5) == 20LL));
    assert((sol.minOperations(vector<int>{1000000, -1000000, 0, 1000000, -1000000, 0, 1000000, -1000000, 0, 1000000, -1000000, 0}, 4, 3) == 8000000LL));
    assert((sol.minOperations(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 10, 2) == 0LL));
    assert((sol.minOperations(vector<int>{-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5}, 5, 2) == 12LL));

    cout << "All tests passed for minimum-operations-to-make-elements-within-k-subarrays-equal" << endl;
    return 0;
}
