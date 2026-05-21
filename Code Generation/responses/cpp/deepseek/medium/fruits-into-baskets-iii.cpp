#include <vector>
#include <algorithm>
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
        int n = fruits.size();
        SegmentTree st(n);
        
        // Initialize segment tree with basket capacities
        for (int i = 0; i < n; i++) {
            st.update(1, 0, n-1, i, baskets[i]);
        }
        
        int unplaced = 0;
        
        for (int i = 0; i < n; i++) {
            int fruit = fruits[i];
            
            // Find leftmost basket with capacity >= fruit using binary search on segment tree
            int left = 0, right = n - 1;
            int foundIndex = -1;
            
            while (left <= right) {
                int mid = (left + right) / 2;
                long long minCapacity = st.query(1, 0, n-1, left, mid);
                if (minCapacity >= fruit) {
                    foundIndex = mid;
                    right = mid - 1;
                } else {
                    left = mid + 1;
                }
            }
            
            if (foundIndex != -1) {
                // Remove this basket
                st.update(1, 0, n-1, foundIndex, SegmentTree::MN);
            } else {
                unplaced++;
            }
        }
        
        return unplaced;
    }
};