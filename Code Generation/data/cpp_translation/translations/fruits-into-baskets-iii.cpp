// task_id: fruits-into-baskets-iii
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


class SegmentTree {
public:
    static constexpr long long MN = 10000000000LL;
    int n;
    vector<long long> f;
    SegmentTree(int n_) : n(n_), f(4 * n_, MN) {}
    void update(int k, int l, int r, int i, long long x) {
        if (l == r) { f[k] = x; return; }
        int mid = (l + r) / 2;
        if (i <= mid) update(2*k, l, mid, i, x);
        else update(2*k+1, mid+1, r, i, x);
        f[k] = min(f[2*k], f[2*k+1]);
    }
    long long query(int k, int l, int r, int start, int end) {
        if (l == start && r == end) return f[k];
        int mid = (l + r) / 2;
        if (end <= mid) return query(2*k, l, mid, start, end);
        if (mid < start) return query(2*k+1, mid+1, r, start, end);
        long long lp = query(2*k, l, mid, start, mid);
        long long rp = query(2*k+1, mid+1, r, mid+1, end);
        return min(lp, rp);
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int> fruits, vector<int> baskets) {
        int n = (int)fruits.size();
        set<int> uniq(fruits.begin(), fruits.end());
        for (int x : baskets) uniq.insert(x);
        vector<int> arr(uniq.begin(), uniq.end());
        unordered_map<int,int> dt;
        for (int i = 0; i < (int)arr.size(); ++i) dt[arr[i]] = i;
        int sz = (int)arr.size();
        SegmentTree tree(sz);
        unordered_map<int, deque<int>> pos;
        for (int i = 0; i < n; ++i) {
            int num = baskets[i];
            if (pos.find(num) == pos.end()) {
                tree.update(1, 0, sz-1, dt[num], i);
            }
            pos[num].push_back(i);
        }
        int res = 0;
        for (int num : fruits) {
            long long j = tree.query(1, 0, sz-1, dt[num], sz-1);
            if (j == SegmentTree::MN) { ++res; continue; }
            int tmp = baskets[(int)j];
            pos[tmp].pop_front();
            if (!pos[tmp].empty()) {
                tree.update(1, 0, sz-1, dt[tmp], pos[tmp].front());
            } else {
                tree.update(1, 0, sz-1, dt[tmp], SegmentTree::MN);
            }
        }
        return res;
    }
};

int main() {
    Solution sol;

    assert((sol.numOfUnplacedFruits(vector<int>{5, 5, 5, 5, 5}, vector<int>{1, 2, 3, 4, 5}) == 4));
    assert((sol.numOfUnplacedFruits(vector<int>{4, 2, 5}, vector<int>{3, 5, 4}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 1}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000, 1000000000}, vector<int>{999999999, 1000000000}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000}, vector<int>{1000000000}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4}, vector<int>{4, 3, 2, 1}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4}, vector<int>{10, 10, 10, 10}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 9, 8, 7, 6}, vector<int>{6, 7, 8, 9, 10}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 5, 5, 5}, vector<int>{5, 5, 5, 5}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 10, 100, 1000}, vector<int>{1000, 100, 10, 1}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{7, 8, 9}, vector<int>{6, 7, 8}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 10, 10}, vector<int>{5, 5, 5}) == 3));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30}, vector<int>{5, 15, 25}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{3, 6, 1}, vector<int>{6, 4, 7}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{9, 7, 5, 3, 1}, vector<int>{1, 3, 5, 7, 9}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{5, 15, 25, 35, 45, 55, 65, 75, 85, 95}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 15, 25, 35, 45}, vector<int>{10, 20, 30, 40, 50}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 5, 5, 5, 5}, vector<int>{5, 5, 5, 5, 5}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 4));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{50, 40, 30, 20, 10}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{20, 30, 40, 50, 60}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000, 500000000, 250000000, 125000000, 62500000}, vector<int>{62500000, 125000000, 250000000, 500000000, 1000000000}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 1}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{1000, 900, 800, 700, 600, 500, 400, 300, 200, 100}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{25, 35, 15, 45, 55}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60}, vector<int>{15, 25, 35, 45, 55, 65}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 10}) == 9));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000, 999999999, 888888888, 777777777, 666666666}, vector<int>{999999999, 888888888, 777777777, 666666666, 555555555}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000}, vector<int>{999999999}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 4, 8, 16, 32, 64, 128, 256, 512}, vector<int>{1024, 512, 256, 128, 64, 32, 16, 8, 4, 2}) == 4));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 10));
    assert((sol.numOfUnplacedFruits(vector<int>{7, 3, 8, 2, 9, 5}, vector<int>{10, 5, 8, 4, 9, 6}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 5, 5, 5, 5}, vector<int>{1, 1, 1, 1, 10}) == 4));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 55, 60}, vector<int>{60, 55, 50, 45, 40, 35, 30, 25, 20, 15, 10, 5}) == 6));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 3, 5, 7, 9, 11, 13}, vector<int>{13, 11, 9, 7, 5, 3, 1}) == 3));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 10, 10, 10, 10, 10}, vector<int>{5, 5, 5, 5, 5, 5}) == 6));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 15, 25, 35, 45}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120}, vector<int>{120, 110, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10}) == 6));
    assert((sol.numOfUnplacedFruits(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{100, 200, 300, 400, 500}, vector<int>{500, 400, 300, 200, 100}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000}, vector<int>{10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 1}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}, vector<int>{50, 45, 40, 35, 30, 25, 20, 15, 10, 5}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{100, 99, 98, 97, 96, 95, 94, 93, 92, 91}, vector<int>{91, 92, 93, 94, 95, 96, 97, 98, 99, 100}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{50, 40, 30, 20, 10}, vector<int>{10, 20, 30, 40, 50}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{999999999, 999999998, 999999997, 999999996, 999999995}, vector<int>{1000000000, 1000000000, 1000000000, 1000000000, 1000000000}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 7, 3, 8, 2, 6}, vector<int>{4, 5, 7, 6, 8, 3}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7}, vector<int>{5, 5, 5, 5, 5, 10, 10, 10, 10, 10}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 2, 3, 3, 3, 4, 4, 4, 4}, vector<int>{2, 2, 3, 3, 3, 4, 4, 4, 4, 4}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{5, 4, 3, 2, 1, 5, 4, 3, 2, 1}) == 4));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 3, 8, 6, 2}, vector<int>{4, 7, 8, 5, 1}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 25, 15, 40, 30}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 1, 1, 1, 10}, vector<int>{10, 10, 10, 10, 1}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 10, 15, 20, 25}, vector<int>{5, 15, 25, 35, 45, 55}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{1, 1, 1, 1, 1}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 15, 25, 35, 45}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 9));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 7));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50, 60}, vector<int>{60, 50, 40, 30, 20, 10}) == 3));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 20, 30, 40, 50}, vector<int>{100, 100, 100, 100, 1}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{5, 5, 5, 5, 5}, vector<int>{3, 3, 3, 3, 3}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{500, 400, 300, 200, 100}, vector<int>{100, 200, 300, 400, 500}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 10));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 3, 5, 7, 9}, vector<int>{2, 4, 6, 8, 10}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{100, 200, 300, 400, 500}, vector<int>{150, 250, 350, 450, 550}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{20, 18, 16, 14, 12, 10, 8, 6, 4, 2}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{999999999, 999999998, 999999997, 999999996}, vector<int>{999999996, 999999997, 999999998, 999999999}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{2, 4, 6, 8, 10}, vector<int>{1, 3, 5, 7, 9}) == 1));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 9));
    assert((sol.numOfUnplacedFruits(vector<int>{9, 11, 13, 15, 17}, vector<int>{18, 19, 20, 21, 22}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 10, 10, 10, 10}, vector<int>{5, 5, 5, 5, 5}) == 5));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000, 1000000000, 1000000000}, vector<int>{999999999, 999999999, 999999999}) == 3));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 4, 8, 16, 32, 64, 128, 256, 512}, vector<int>{1, 2, 4, 8, 16, 32, 64, 128, 256, 1024}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 10}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{9, 8, 7, 6, 5}, vector<int>{10, 9, 8, 7, 6}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000, 1000000000, 1000000000}, vector<int>{999999999, 999999999, 1000000000}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 10));
    assert((sol.numOfUnplacedFruits(vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 9));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{2, 3, 1, 5, 4}, vector<int>{5, 3, 4, 2, 1}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{50, 50, 50, 50, 50}, vector<int>{40, 40, 60, 60, 60}) == 2));
    assert((sol.numOfUnplacedFruits(vector<int>{1, 3, 5, 7, 9, 11}, vector<int>{2, 4, 6, 8, 10, 12}) == 0));
    assert((sol.numOfUnplacedFruits(vector<int>{1000000000, 999999999, 888888888, 777777777, 666666666}, vector<int>{666666666, 777777777, 888888888, 999999999, 1000000000}) == 0));

    cout << "All tests passed for fruits-into-baskets-iii" << endl;
    return 0;
}
