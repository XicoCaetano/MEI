#include <vector>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <set>

using namespace std;

class LazyHeap {
public:
    priority_queue<long long> max_heap; // left side
    priority_queue<long long, vector<long long>, greater<long long>> min_heap; // right side
    unordered_map<long long, int> left_rem, right_rem;
    int left_size = 0, right_size = 0;
    long long left_sum = 0, right_sum = 0;

    void normalize() {
        while (!max_heap.empty() && left_rem[max_heap.top()] > 0) {
            left_rem[max_heap.top()]--;
            max_heap.pop();
        }
        while (!min_heap.empty() && right_rem[min_heap.top()] > 0) {
            right_rem[min_heap.top()]--;
            min_heap.pop();
        }
    }

    void balance() {
        if (left_size > right_size + 1) {
            long long val = max_heap.top();
            max_heap.pop();
            if (left_rem[val] > 0) {
                left_rem[val]--;
                balance();
            } else {
                left_sum -= val; left_size--;
                min_heap.push(val);
                right_sum += val; right_size++;
            }
        } else if (right_size > left_size) {
            long long val = min_heap.top();
            min_heap.pop();
            if (right_rem[val] > 0) {
                right_rem[val]--;
                balance();
            } else {
                right_sum -= val; right_size--;
                max_heap.push(val);
                left_sum += val; left_size++;
            }
        }
        normalize();
    }

    void add(long long val) {
        if (left_size == 0 || val <= max_heap.top()) {
            max_heap.push(val);
            left_sum += val;
            left_size++;
        } else {
            min_heap.push(val);
            right_sum += val;
            right_size++;
        }
        balance();
    }

    void remove(long long val) {
        if (val <= max_heap.top()) {
            left_rem[val]++;
            left_sum -= val;
            left_size--;
        } else {
            right_rem[val]++;
            right_sum -= val;
            right_size--;
        }
        normalize();
        balance();
    }

    long long get_cost() {
        if (left_size == 0) return 0;
        long long median = max_heap.top();
        return (median * left_size - left_sum) + (right_sum - median * right_size);
    }
};

class Solution {
public:
    static constexpr long long INF = 4000000000000000000LL;

    long long minOperations(vector<int> nums, int x, int k) {
        int n = nums.size();
        // pre[i] is the minimum cost to have a block of size x ending at i-1
        vector<long long> cost(n - x + 1);
        LazyHeap lh;
        for (int i = 0; i < n; ++i) {
            lh.add(nums[i]);
            if (i >= x) lh.remove(nums[i - x]);
            if (i >= x - 1) cost[i - x + 1] = lh.get_cost();
        }

        // dp[i][j] = min cost to have i blocks using first j elements of cost array
        // Since blocks are size x, if we pick cost[j], the next block can start at j+x
        vector<vector<long long>> dp(k + 1, vector<long long>(n + 1, INF));
        fill(dp[0].begin(), dp[0].end(), 0);

        for (int i = 1; i <= k; ++i) {
            long long min_prev = INF;
            for (int j = 0; j <= (int)cost.size() - 1; ++j) {
                // To pick a block starting at j, we need results from dp[i-1] up to j-x
                if (j >= x) {
                    min_prev = min(min_prev, dp[i - 1][j - x + 1]);
                } else if (i == 1) {
                    min_prev = 0;
                }
                
                if (min_prev != INF) {
                    dp[i][j + 1] = min(dp[i][j], min_prev + cost[j]);
                } else {
                    dp[i][j + 1] = dp[i][j];
                }
            }
        }

        return dp[k][cost.size()];
    }
};