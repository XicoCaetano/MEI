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

class Solution {
public:
    static constexpr long long INF = 4000000000000000000LL;

    vector<long long> medianSlidingWindow(const vector<int>& nums, int k) {
        int n = (int)nums.size();
        vector<long long> ans(n - k + 1, 0);
        LazyHeap left, right;
        for (int i = 0; i < n; ++i) {
            long long x = nums[i];
            if (left.size_ == right.size_) {
                left.push(-right.pushpop(x));
            } else {
                right.push(-left.pushpop(-x));
            }
            int l = i + 1 - k;
            if (l < 0) continue;
            long long v = -left.top();
            long long s1 = v * left.size_ + left.sum_;
            long long s2 = right.sum_ - v * right.size_;
            ans[l] = s1 + s2;
            long long xx = nums[l];
            if (xx <= -left.top()) {
                left.remove(-xx);
                if (left.size_ < right.size_) {
                    left.push(-right.pop());
                }
            } else {
                right.remove(xx);
                if (left.size_ > right.size_ + 1) {
                    right.push(-left.pop());
                }
            }
        }
        return ans;
    }

    long long minOperations(vector<int> nums, int x, int k) {
        int n = (int)nums.size();
        vector<long long> dis = medianSlidingWindow(nums, x);
        vector<vector<long long>> f(k + 1, vector<long long>(n + 1, 0));
        for (int i = 1; i <= k; ++i) {
            f[i][i * x - 1] = INF;
            for (int j = i * x; j <= n - (k - i) * x; ++j) {
                long long left_opt = f[i][j - 1];
                long long alt = f[i - 1][j - x] + dis[j - x];
                f[i][j] = min(left_opt, alt);
            }
        }
        return f[k][n];
    }
};

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
