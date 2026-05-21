#include <vector>
#include <climits>
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
    // Find leftmost index in [start, end] with value >= minVal
    int findLeftmost(int k, int l, int r, int start, int end, long long minVal) {
        if (f[k] < minVal) return -1;
        if (l == r) return l;
        int mid = (l + r) / 2;
        int res = -1;
        if (start <= mid) {
            res = findLeftmost(2*k, l, mid, start, min(end, mid), minVal);
        }
        if (res == -1 && end > mid) {
            res = findLeftmost(2*k+1, mid+1, r, max(start, mid+1), end, minVal);
        }
        return res;
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int> fruits, vector<int> baskets) {
        int n = fruits.size();
        SegmentTree st(n);
        for (int i = 0; i < n; i++) {
            st.update(1, 0, n-1, i, baskets[i]);
        }
        int unplaced = 0;
        for (int i = 0; i < n; i++) {
            int idx = st.findLeftmost(1, 0, n-1, 0, n-1, (long long)fruits[i]);
            if (idx == -1) {
                unplaced++;
            } else {
                st.update(1, 0, n-1, idx, 0);
            }
        }
        return unplaced;
    }
};