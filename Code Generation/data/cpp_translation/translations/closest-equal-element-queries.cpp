// task_id: closest-equal-element-queries
// difficulty: Medium

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


class Solution {
public:
    vector<int> solveQueries(vector<int> nums, vector<int> queries) {
        int n = (int)nums.size();
        int m = n << 1;
        vector<int> d(m, m);
        unordered_map<int,int> left;
        for (int i = 0; i < m; ++i) {
            int x = nums[i % n];
            auto it = left.find(x);
            if (it != left.end()) d[i] = min(d[i], i - it->second);
            left[x] = i;
        }
        unordered_map<int,int> right;
        for (int i = m - 1; i >= 0; --i) {
            int x = nums[i % n];
            auto it = right.find(x);
            if (it != right.end()) d[i] = min(d[i], it->second - i);
            right[x] = i;
        }
        for (int i = 0; i < n; ++i) d[i] = min(d[i], d[i + n]);
        vector<int> ans;
        ans.reserve(queries.size());
        for (int q : queries) ans.push_back(d[q] >= n ? -1 : d[q]);
        return ans;
    }
};

int main() {
    Solution sol;

    assert((sol.solveQueries(vector<int>{1, 3, 1, 4, 1, 3, 2}, vector<int>{0, 3, 5}) == vector<int>{2, -1, 3}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4}, vector<int>{0, 1, 2, 3}) == vector<int>{-1, -1, -1, -1}));
    assert((sol.solveQueries(vector<int>{1000000, 1000000, 1000000}, vector<int>{0, 1, 2}) == vector<int>{1, 1, 1}));
    assert((sol.solveQueries(vector<int>{5, 1, 5, 2, 5, 3, 5, 4}, vector<int>{2, 4, 6, 0}) == vector<int>{2, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{10, 20, 30, 40, 50, 10, 20}, vector<int>{0, 1, 2, 3, 4, 5, 6}) == vector<int>{2, 2, -1, -1, -1, 2, 2}));
    assert((sol.solveQueries(vector<int>{6, 5, 4, 3, 2, 1}, vector<int>{0, 1, 2, 3, 4, 5}) == vector<int>{-1, -1, -1, -1, -1, -1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 9, 5}) == vector<int>{-1, -1, -1}));
    assert((sol.solveQueries(vector<int>{10, 10, 10, 10}, vector<int>{0, 1, 2, 3}) == vector<int>{1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{2, 1, 3, 1, 2}, vector<int>{0, 1, 2, 3, 4}) == vector<int>{1, 2, -1, 2, 1}));
    assert((sol.solveQueries(vector<int>{5, 1, 5, 1, 5, 1}, vector<int>{2, 4, 1, 3}) == vector<int>{2, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{5, 5, 5, 5, 5}, vector<int>{0, 1, 2, 3, 4}) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 2, 1}, vector<int>{0, 1, 2, 3, 4}) == vector<int>{1, 2, -1, 2, 1}));
    assert((sol.solveQueries(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 3, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == vector<int>{3, 2, 3, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 2}));
    assert((sol.solveQueries(vector<int>{7, 8, 9, 7, 10, 11, 12, 9, 13, 14, 7, 15, 16, 17, 8, 18}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == vector<int>{3, 3, 5, 3, -1, -1, -1, 5, -1, -1, 6, -1, -1, -1, 3, -1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9}, vector<int>{0, 9, 18, 27, 20}) == vector<int>{9, 9, 9, 9, 9}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50}, vector<int>{0, 5, 10}) == vector<int>{5, 5, 5}));
    assert((sol.solveQueries(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 1, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1000000, 2000000, 3000000, 4000000, 5000000, 1000000, 2000000, 3000000, 4000000, 5000000, 1000000, 2000000, 3000000, 4000000, 5000000}, vector<int>{0, 5, 10, 15, 20}) == vector<int>{5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4}, vector<int>{0, 5, 10}) == vector<int>{6, 6, 6}));
    assert((sol.solveQueries(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{10, 20, 10, 30, 10, 40, 10, 50, 10, 60}, vector<int>{0, 2, 4, 6, 8}) == vector<int>{2, 2, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{7, 8, 9, 7, 6, 7, 8, 9, 7, 6}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{2, 5, 5, 2, 5, 2, 5, 5, 2, 5}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 5, 10, 15, 20}) == vector<int>{10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{5, 6, 5, 6, 5, 6, 5, 6, 5, 6}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9}, vector<int>{0, 9, 10, 18}) == vector<int>{9, 9, 9, 9}));
    assert((sol.solveQueries(vector<int>{7, 8, 9, 7, 10, 8, 9, 7}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7}) == vector<int>{1, 4, 4, 3, -1, 4, 4, 1}));
    assert((sol.solveQueries(vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7}, vector<int>{0, 9, 18, 10, 19, 1, 11, 2, 12}) == vector<int>{3, 9, 3, 9, 3, 3, 9, 3, 9}));
    assert((sol.solveQueries(vector<int>{5, 6, 7, 8, 9, 5, 6, 7, 8, 9, 5, 6, 7, 8, 9}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3}, vector<int>{0, 3, 6, 9, 1, 4, 7, 10, 2, 5, 8, 11}) == vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}));
    assert((sol.solveQueries(vector<int>{100, 200, 100, 300, 100, 200, 100, 400, 100, 200}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{2, 2, 2, -1, 2, 4, 2, -1, 2, 2}));
    assert((sol.solveQueries(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{7, 7, 7, 7, 7, 7, 7}, vector<int>{0, 1, 2, 3, 4, 5, 6}) == vector<int>{1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13}) == vector<int>{5, 5, 5, 5, 5, -1, -1, -1, -1, 5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{1000000, 999999, 999998, 999997, 999996, 999995, 1000000, 999999, 999998, 999997}, vector<int>{0, 4, 8}) == vector<int>{4, -1, 4}));
    assert((sol.solveQueries(vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50, 10, 20, 30, 40, 50}, vector<int>{0, 5, 10, 15, 20}) == vector<int>{5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{5, 3, 5, 3, 5, 3, 5, 3, 5, 3}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9}, vector<int>{0, 5, 10, 15}) == vector<int>{9, 9, 9, 9}));
    assert((sol.solveQueries(vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 9, 10, 19, 5, 14}) == vector<int>{9, -1, 9, 9, 9, 9}));
    assert((sol.solveQueries(vector<int>{1, 2, 1, 3, 1, 4, 1, 5, 1, 6}, vector<int>{0, 2, 4, 6, 8}) == vector<int>{2, 2, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 100, 200, 300}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}) == vector<int>{3, 3, 3, -1, -1, -1, -1, -1, -1, 3, 3, 3}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 5, 10, 15, 20, 25, 30, 35, 39}) == vector<int>{10, 10, -1, -1, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 100}, vector<int>{0, 10, 5, 3, 8}) == vector<int>{1, 1, -1, -1, -1}));
    assert((sol.solveQueries(vector<int>{10, 20, 30, 10, 20, 30, 10, 20, 30, 10, 20, 30}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}) == vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}));
    assert((sol.solveQueries(vector<int>{1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1}, vector<int>{0, 2, 4, 6, 8, 10}) == vector<int>{1, 2, 2, 2, 2, 1}));
    assert((sol.solveQueries(vector<int>{4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 4, 8, 12, 16, 20}) == vector<int>{7, 7, 7, 7, 7, 7}));
    assert((sol.solveQueries(vector<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 1, 1, 1}, vector<int>{0, 4, 8, 12, 16}) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 10, 20, 30, 40, 50}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}) == vector<int>{5, 5, 5, 5, 5, -1, -1, -1, -1, -1, 5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 1, 2, 3, 4, 1, 2}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{2, 2, 4, 4, 4, 4, 4, 4, 2, 2}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5}, vector<int>{0, 5, 10, 15, 20, 1, 6, 11, 16, 21}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1}, vector<int>{0, 10, 20, 5, 15, 25}) == vector<int>{1, 10, 1, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{1, 1, 2, 2, 3, 3, 1, 1, 2, 2, 3, 3}, vector<int>{0, 2, 4, 6, 8, 10}) == vector<int>{1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{0, 10, 20, 30, 40, 50}) == vector<int>{20, 20, 20, 20, 20, 20}));
    assert((sol.solveQueries(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{2, 2, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 2, 2}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9}, vector<int>{0, 10, 15, 20}) == vector<int>{9, 9, 9, 9}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{0, 10, 20, 5, 15}) == vector<int>{9, 9, 9, 9, 9}));
    assert((sol.solveQueries(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{7, 8, 9, 7, 10, 11, 9, 12, 7}, vector<int>{0, 3, 6, 8}) == vector<int>{1, 3, 4, 1}));
    assert((sol.solveQueries(vector<int>{1000000, 999999, 999998, 999997, 999996, 1000000, 999999, 999998, 999997, 999996}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 1, 1}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{0, 5, 10, 15, 19}) == vector<int>{-1, -1, -1, -1, -1}));
    assert((sol.solveQueries(vector<int>{5, 3, 8, 3, 5, 8, 5, 3, 8, 3, 5, 8}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}) == vector<int>{2, 2, 3, 2, 2, 3, 2, 2, 3, 2, 2, 3}));
    assert((sol.solveQueries(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39}) == vector<int>{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{1, -1, -1, -1, -1, -1, -1, -1, -1, 1}));
    assert((sol.solveQueries(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{2, 3, 2, 2, 2, 3, 3, 2, 2, 2, 3}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == vector<int>{2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2}));
    assert((sol.solveQueries(vector<int>{7, 8, 9, 7, 10, 11, 7, 12, 7, 13, 7, 14}, vector<int>{0, 3, 6, 9, 12}) == vector<int>{2, 3, 2, -1, 2}));
    assert((sol.solveQueries(vector<int>{5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 1, 2, 3, 4, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.solveQueries(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == vector<int>{2, 2, -1, 2, 4, -1, -1, -1, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.solveQueries(vector<int>{1, 2, 1, 3, 1, 4, 1, 5, 1, 6}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{2, -1, 2, -1, 2, -1, 2, -1, 2, -1}));
    assert((sol.solveQueries(vector<int>{7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1, 7, 1}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.solveQueries(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}) == vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5}, vector<int>{0, 5, 10}) == vector<int>{5, 5, 5}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1, 2, 3, 4, 5}, vector<int>{0, 20, 21, 22, 23}) == vector<int>{5, 5, 5, 5, 5}));
    assert((sol.solveQueries(vector<int>{1, 2, 3, 4, 5, 1, 2, 3, 4, 5}, vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));

    cout << "All tests passed for closest-equal-element-queries" << endl;
    return 0;
}
