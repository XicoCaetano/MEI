#include <vector>
#include <algorithm>

using namespace std;

class SegmentTree {
public:
    int n;
    vector<int> tree;

    SegmentTree(const vector<int>& baskets) {
        n = baskets.size();
        tree.resize(4 * n);
        build(baskets, 1, 0, n - 1);
    }

    void build(const vector<int>& baskets, int node, int start, int end) {
        if (start == end) {
            tree[node] = baskets[start];
            return;
        }
        int mid = (start + end) / 2;
        build(baskets, 2 * node, start, mid);
        build(baskets, 2 * node + 1, mid + 1, end);
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
    }

    int findAndUseFirst(int node, int start, int end, int val) {
        // If the maximum value in this range is less than val, no basket fits
        if (tree[node] < val) {
            return -1;
        }
        // Found a leaf node that satisfies the condition
        if (start == end) {
            int idx = start;
            tree[node] = -1; // Mark basket as used
            return idx;
        }

        int mid = (start + end) / 2;
        int res = -1;
        
        // Always try the left child first to find the "leftmost" available basket
        if (tree[2 * node] >= val) {
            res = findAndUseFirst(2 * node, start, mid, val);
        } else {
            res = findAndUseFirst(2 * node + 1, mid + 1, end, val);
        }

        // Update the maximum value for the internal node after potential modification
        tree[node] = max(tree[2 * node], tree[2 * node + 1]);
        return res;
    }
};

class Solution {
public:
    int numOfUnplacedFruits(vector<int>& fruits, vector<int>& baskets) {
        int n = fruits.size();
        SegmentTree st(baskets);
        int unplacedCount = 0;

        for (int i = 0; i < n; ++i) {
            int resultIndex = st.findAndUseFirst(1, 0, n - 1, fruits[i]);
            if (resultIndex == -1) {
                unplacedCount++;
            }
        }

        return unplacedCount;
    }
};