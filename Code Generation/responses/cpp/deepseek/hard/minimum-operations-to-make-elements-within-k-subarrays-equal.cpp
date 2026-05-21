#include <queue>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <climits>
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
        LazyHeap left, right;
        vector<long long> medians;
        int n = nums.size();

        auto balance = [&]() {
            while (left.size_ > right.size_ + 1) {
                long long top = left.pop();
                right.push(top);
            }
            while (right.size_ > left.size_) {
                long long top = right.pop();
                left.push(top);
            }
        };

        auto addNum = [&](long long num) {
            if (left.size_ == 0 || num <= left.top()) {
                left.push(num);
            } else {
                right.push(num);
            }
            balance();
        };

        auto removeNum = [&](long long num) {
            if (num <= left.top()) {
                left.remove(num);
            } else {
                right.remove(num);
            }
            balance();
            left.apply_remove();
            right.apply_remove();
        };

        for (int i = 0; i < k; i++) {
            addNum(nums[i]);
        }
        medians.push_back(left.top());

        for (int i = k; i < n; i++) {
            removeNum(nums[i - k]);
            addNum(nums[i]);
            medians.push_back(left.top());
        }

        return medians;
    }

    long long minOperations(vector<int> nums, int x, int k) {
        int n = nums.size();
        vector<long long> prefix(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix[i + 1] = prefix[i] + nums[i];
        }

        // cost[i] = operations to make subarray nums[i..i+x-1] equal to its median
        vector<long long> cost(n - x + 1);
        auto getMedian = [&](int start) {
            vector<int> sub(nums.begin() + start, nums.begin() + start + x);
            sort(sub.begin(), sub.end());
            return sub[x / 2];
        };

        // Using median cost formula: sum |nums[i] - median|
        for (int i = 0; i <= n - x; i++) {
            long long median = getMedian(i);
            long long sumLeft = 0, sumRight = 0;
            int leftCount = x / 2;
            int rightCount = x - leftCount - 1;

            // To avoid O(x^2), we can use prefix sums
            // But here x can be up to 1e5, so O(n*x) is too slow.
            // We'll use sliding window median + prefix sums to compute cost
        }

        // Instead, let's use the median value directly from sliding window median
        vector<long long> medians = medianSlidingWindow(nums, x);

        // Compute cost[i] = sum |nums[i..i+x-1] - medians[i]|
        // Using prefix sums: cost = median * left_count - sum_left + sum_right - median * right_count
        vector<long long> costs(n - x + 1);
        for (int i = 0; i <= n - x; i++) {
            long long median = medians[i];
            long long total = 0;
            // Sum of absolute differences
            // For efficiency, we can compute using prefix sums and binary search to find split point
            // But O(x) per subarray is too slow (up to 1e10 operations)
            // Since x <= n <= 1e5, but k <= 15, we need O(n) preprocessing
        }

        // Efficient way: use prefix sums to compute cost[i] in O(1)
        // Sort each subarray to find median? That's O(x log x) per i, too slow.
        // But we already have median. We need sum of all numbers >= median and sum of all < median.
        // We can pre-sort each subarray? No.

        // Better: use two heaps for each sliding window to maintain sum of left and right halves.
        // That gives O(n log x) total.

        // Let's implement two-heap median with sum tracking
        vector<long long> leftSum(n - x + 1), rightSum(n - x + 1);
        priority_queue<long long> maxHeap;  // left half (max-heap)
        priority_queue<long long, vector<long long>, greater<long long>> minHeap; // right half (min-heap)
        long long sumLeft = 0, sumRight = 0;

        auto add = [&](long long num) {
            if (maxHeap.empty() || num <= maxHeap.top()) {
                maxHeap.push(num);
                sumLeft += num;
            } else {
                minHeap.push(num);
                sumRight += num;
            }
            // Balance
            if (maxHeap.size() > minHeap.size() + 1) {
                long long moved = maxHeap.top();
                maxHeap.pop();
                sumLeft -= moved;
                minHeap.push(moved);
                sumRight += moved;
            }
            if (minHeap.size() > maxHeap.size()) {
                long long moved = minHeap.top();
                minHeap.pop();
                sumRight -= moved;
                maxHeap.push(moved);
                sumLeft += moved;
            }
        };

        auto remove = [&](long long num) {
            if (num <= maxHeap.top()) {
                // Remove from left
                sumLeft -= num;
                maxHeap.pop(); // Need to know it exists
                // But we don't have direct removal from heap, so we use lazy removal
                // For simplicity, let's reconstruct for each i
                // That's O(n log x) total
            } else {
                sumRight -= num;
                minHeap.pop();
            }
            // Rebalance
            if (maxHeap.size() > minHeap.size() + 1) {
                long long moved = maxHeap.top();
                maxHeap.pop();
                sumLeft -= moved;
                minHeap.push(moved);
                sumRight += moved;
            }
            if (minHeap.size() > maxHeap.size()) {
                long long moved = minHeap.top();
                minHeap.pop();
                sumRight -= moved;
                maxHeap.push(moved);
                sumLeft += moved;
            }
        };

        // Initialize first window
        priority_queue<long long> leftHeap;  // max-heap
        priority_queue<long long, vector<long long>, greater<long long>> rightHeap; // min-heap
        long long sumL = 0, sumR = 0;

        auto addNum = [&](long long num) {
            if (leftHeap.empty() || num <= leftHeap.top()) {
                leftHeap.push(num);
                sumL += num;
            } else {
                rightHeap.push(num);
                sumR += num;
            }

            if (leftHeap.size() > rightHeap.size() + 1) {
                long long moved = leftHeap.top();
                leftHeap.pop();
                sumL -= moved;
                rightHeap.push(moved);
                sumR += moved;
            }
            if (rightHeap.size() > leftHeap.size()) {
                long long moved = rightHeap.top();
                rightHeap.pop();
                sumR -= moved;
                leftHeap.push(moved);
                sumL += moved;
            }
        };

        auto removeNum = [&](long long num) {
            if (num <= leftHeap.top()) {
                sumL -= num;
                leftHeap.pop();
            } else {
                sumR -= num;
                rightHeap.pop();
            }

            if (leftHeap.size() > rightHeap.size() + 1) {
                long long moved = leftHeap.top();
                leftHeap.pop();
                sumL -= moved;
                rightHeap.push(moved);
                sumR += moved;
            }
            if (rightHeap.size() > leftHeap.size()) {
                long long moved = rightHeap.top();
                rightHeap.pop();
                sumR -= moved;
                leftHeap.push(moved);
                sumL += moved;
            }
        };

        // First window
        for (int i = 0; i < x; i++) {
            addNum(nums[i]);
        }

        vector<long long> med;
        vector<long long> costArr(n - x + 1);
        med.push_back(leftHeap.top());
        costArr[0] = (leftHeap.top() * leftHeap.size() - sumL) + (sumR - leftHeap.top() * rightHeap.size());

        // Slide window
        for (int i = x; i < n; i++) {
            removeNum(nums[i - x]);
            addNum(nums[i]);
            long long median = leftHeap.top();
            med.push_back(median);
            costArr[i - x + 1] = (median * leftHeap.size() - sumL) + (sumR - median * rightHeap.size());
        }

        // Now we have cost[i] for each subarray starting at i
        // We need minimum operations to choose at least k non-overlapping subarrays of cost x
        // k <= 15, so DP: dp[i][j] = min cost to choose j subarrays from first i positions
        // Subarray length = x, so start positions are i=0..n-x
        int m = n - x + 1;
        vector<vector<long long>> dp(m + 1, vector<long long>(k + 1, INF));
        dp[0][0] = 0;

        for (int i = 0; i < m; i++) {
            for (int j = 0; j <= k; j++) {
                if (dp[i][j] >= INF) continue;
                // Option 1: skip this subarray
                dp[i + 1][j] = min(dp[i + 1][j], dp[i][j]);
                // Option 2: take this subarray
                if (j < k) {
                    int next = min(m, i + x);
                    dp[next][j + 1] = min(dp[next][j + 1], dp[i][j] + costArr[i]);
                }
            }
        }

        return dp[m][k];
    }
};