// task_id: maximize-active-section-with-trade-ii
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


class SparseTable {
public:
    vector<vector<long long>> st;
    int m;
    SparseTable(const vector<pair<int,int>>& a) {
        int n = (int)a.size() - 1;
        m = 1;
        while ((1 << m) <= n) ++m;
        st.assign(n, vector<long long>(m, 0));
        for (int i = 0; i < n; ++i) {
            int l1 = a[i].first, r1 = a[i].second;
            int l2 = a[i+1].first, r2 = a[i+1].second;
            st[i][0] = (long long)(r1 - l1) + (r2 - l2);
        }
        for (int j = 1; j < m; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[i][j] = max(st[i][j-1], st[i + (1 << (j-1))][j-1]);
            }
        }
    }
    long long query(int l, int r) {
        if (l >= r) return 0;
        int len = r - l;
        int k = 0;
        while ((1 << (k + 1)) <= len) ++k;
        return max(st[l][k], st[r - (1 << k)][k]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>> queries) {
        int n = (int)s.size();
        long long total1 = 0;
        vector<pair<int,int>> a = {{-1, -1}};
        int start = 0;
        for (int i = 0; i < n; ++i) {
            if (i == n - 1 || s[i] != s[i + 1]) {
                if (s[i] == '1') {
                    total1 += i - start + 1;
                } else {
                    a.push_back({start, i + 1});
                }
                start = i + 1;
            }
        }
        a.push_back({n + 1, n + 1});

        auto merge_seg = [](long long x, long long y) -> long long {
            return (x > 0 && y > 0) ? (x + y) : 0;
        };
        SparseTable st(a);

        // For bisect_left on a by first: find first i in [0,size) with a[i].first >= ql.
        auto bisect_left_first = [&](int ql) {
            int lo = 0, hi = (int)a.size();
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (a[mid].first < ql) lo = mid + 1;
                else hi = mid;
            }
            return lo;
        };
        // For bisect_right on a by second: find first j with a[j].second > qr.
        auto bisect_right_second = [&](int qr) {
            int lo = 0, hi = (int)a.size();
            while (lo < hi) {
                int mid = (lo + hi) / 2;
                if (a[mid].second <= qr) lo = mid + 1;
                else hi = mid;
            }
            return lo;
        };

        vector<int> ans;
        ans.reserve(queries.size());
        for (auto& q : queries) {
            int ql = q[0], qr = q[1] + 1;
            int i = bisect_left_first(ql);
            int j = bisect_right_second(qr) - 1;
            long long mx = 0;
            if (i <= j) {
                long long c1 = st.query(i, j);
                long long c2 = merge_seg((long long)(a[i - 1].second - ql),
                                         (long long)(a[i].second - a[i].first));
                long long c3 = merge_seg((long long)(qr - a[j + 1].first),
                                         (long long)(a[j].second - a[j].first));
                mx = max({c1, c2, c3});
            } else if (i == j + 1) {
                mx = merge_seg((long long)(a[i - 1].second - ql),
                               (long long)(qr - a[j + 1].first));
            }
            ans.push_back((int)(total1 + mx));
        }
        return ans;
    }
};

int main() {
    Solution sol;

    assert((sol.maxActiveSectionsAfterTrade("0100", vector<vector<int>>{vector<int>{0, 3}, vector<int>{0, 2}, vector<int>{1, 3}, vector<int>{2, 3}}) == vector<int>{4, 3, 1, 1}));
    assert((sol.maxActiveSectionsAfterTrade("01", vector<vector<int>>{vector<int>{0, 1}}) == vector<int>{1}));
    assert((sol.maxActiveSectionsAfterTrade("01010", vector<vector<int>>{vector<int>{0, 3}, vector<int>{1, 4}, vector<int>{1, 3}}) == vector<int>{4, 4, 2}));
    assert((sol.maxActiveSectionsAfterTrade("1000100", vector<vector<int>>{vector<int>{1, 5}, vector<int>{0, 6}, vector<int>{0, 4}}) == vector<int>{6, 7, 2}));
    assert((sol.maxActiveSectionsAfterTrade("111111111111111111111111111111111111111111111111", vector<vector<int>>{vector<int>{0, 39}, vector<int>{1, 38}, vector<int>{2, 37}, vector<int>{3, 36}, vector<int>{4, 35}, vector<int>{5, 34}, vector<int>{6, 33}, vector<int>{7, 32}, vector<int>{8, 31}, vector<int>{9, 30}}) == vector<int>{48, 48, 48, 48, 48, 48, 48, 48, 48, 48}));
    assert((sol.maxActiveSectionsAfterTrade("11111111111111111", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{17, 17, 17, 17, 17}));
    assert((sol.maxActiveSectionsAfterTrade("10000000010000000001000000001", vector<vector<int>>{vector<int>{0, 20}, vector<int>{5, 15}, vector<int>{10, 19}}) == vector<int>{21, 14, 4}));
    assert((sol.maxActiveSectionsAfterTrade("000000000000000000000000000000000000000000000000", vector<vector<int>>{vector<int>{0, 39}, vector<int>{1, 38}, vector<int>{2, 37}, vector<int>{3, 36}, vector<int>{4, 35}, vector<int>{5, 34}, vector<int>{6, 33}, vector<int>{7, 32}, vector<int>{8, 31}, vector<int>{9, 30}}) == vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert((sol.maxActiveSectionsAfterTrade("11001100110011001100110011", vector<vector<int>>{vector<int>{0, 20}, vector<int>{5, 15}, vector<int>{0, 9}, vector<int>{10, 19}, vector<int>{15, 25}}) == vector<int>{18, 18, 18, 18, 18}));
    assert((sol.maxActiveSectionsAfterTrade("111100001111000011110000", vector<vector<int>>{vector<int>{0, 23}, vector<int>{4, 19}, vector<int>{5, 18}, vector<int>{6, 17}, vector<int>{7, 16}, vector<int>{8, 15}, vector<int>{9, 14}, vector<int>{10, 13}, vector<int>{11, 12}}) == vector<int>{20, 20, 19, 18, 17, 12, 12, 12, 12}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001001001001001", vector<vector<int>>{vector<int>{0, 24}, vector<int>{2, 22}, vector<int>{3, 21}, vector<int>{4, 20}, vector<int>{5, 19}, vector<int>{6, 18}, vector<int>{7, 17}, vector<int>{8, 16}, vector<int>{9, 15}, vector<int>{10, 14}, vector<int>{11, 13}}) == vector<int>{13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 11}));
    assert((sol.maxActiveSectionsAfterTrade("00101010101010101010", vector<vector<int>>{vector<int>{0, 9}, vector<int>{5, 15}, vector<int>{10, 19}}) == vector<int>{12, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("10101010101010101010101010", vector<vector<int>>{vector<int>{0, 25}, vector<int>{1, 24}, vector<int>{2, 23}, vector<int>{3, 22}, vector<int>{4, 21}}) == vector<int>{15, 15, 15, 15, 15}));
    assert((sol.maxActiveSectionsAfterTrade("101010101010101010101010101010101010101010101010101010101010", vector<vector<int>>{vector<int>{0, 59}, vector<int>{1, 58}, vector<int>{2, 57}, vector<int>{3, 56}, vector<int>{4, 55}, vector<int>{5, 54}, vector<int>{6, 53}, vector<int>{7, 52}, vector<int>{8, 51}, vector<int>{9, 50}}) == vector<int>{32, 32, 32, 32, 32, 32, 32, 32, 32, 32}));
    assert((sol.maxActiveSectionsAfterTrade("111000111000111", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{3, 11}, vector<int>{4, 10}}) == vector<int>{15, 15, 15, 15, 13}));
    assert((sol.maxActiveSectionsAfterTrade("000011110000111100001111", vector<vector<int>>{vector<int>{0, 23}, vector<int>{4, 19}, vector<int>{5, 18}, vector<int>{6, 17}, vector<int>{7, 16}, vector<int>{8, 15}, vector<int>{9, 14}, vector<int>{10, 13}, vector<int>{11, 12}}) == vector<int>{20, 20, 19, 18, 17, 12, 12, 12, 12}));
    assert((sol.maxActiveSectionsAfterTrade("111000111000", vector<vector<int>>{vector<int>{0, 11}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}}) == vector<int>{12, 6, 6, 6}));
    assert((sol.maxActiveSectionsAfterTrade("01010101010101010101010101010101", vector<vector<int>>{vector<int>{0, 15}, vector<int>{15, 30}, vector<int>{0, 29}}) == vector<int>{18, 18, 18}));
    assert((sol.maxActiveSectionsAfterTrade("10101010101010101010", vector<vector<int>>{vector<int>{0, 19}, vector<int>{1, 18}, vector<int>{2, 17}, vector<int>{3, 16}, vector<int>{4, 15}, vector<int>{5, 14}, vector<int>{6, 13}, vector<int>{7, 12}, vector<int>{8, 11}, vector<int>{9, 10}}) == vector<int>{12, 12, 12, 12, 12, 12, 12, 12, 12, 10}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001001001", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{5, 13}, vector<int>{3, 14}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("11110000111100001111", vector<vector<int>>{vector<int>{0, 9}, vector<int>{5, 15}, vector<int>{10, 19}}) == vector<int>{12, 19, 12}));
    assert((sol.maxActiveSectionsAfterTrade("1010101010", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}}) == vector<int>{7, 7, 7, 7}));
    assert((sol.maxActiveSectionsAfterTrade("0000011111000001111100000111110000011111", vector<vector<int>>{vector<int>{0, 9}, vector<int>{10, 19}, vector<int>{20, 29}, vector<int>{30, 39}, vector<int>{0, 39}}) == vector<int>{20, 20, 20, 20, 30}));
    assert((sol.maxActiveSectionsAfterTrade("1100001100011110001000000011001", vector<vector<int>>{vector<int>{5, 15}, vector<int>{2, 20}, vector<int>{0, 30}, vector<int>{10, 25}}) == vector<int>{16, 19, 22, 22}));
    assert((sol.maxActiveSectionsAfterTrade("00000100000100000", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{5, 10}, vector<int>{3, 8}}) == vector<int>{12, 11, 10, 2, 7}));
    assert((sol.maxActiveSectionsAfterTrade("00000000000000000", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.maxActiveSectionsAfterTrade("0101010101010101010", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{5, 13}, vector<int>{3, 14}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("000100010001000100010001000100010001000100010001000100010001", vector<vector<int>>{vector<int>{0, 59}, vector<int>{1, 58}, vector<int>{2, 57}, vector<int>{3, 56}, vector<int>{4, 55}, vector<int>{5, 54}, vector<int>{6, 53}, vector<int>{7, 52}, vector<int>{8, 51}, vector<int>{9, 50}}) == vector<int>{21, 21, 21, 21, 21, 21, 21, 21, 21, 21}));
    assert((sol.maxActiveSectionsAfterTrade("10101010101010101", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("0101010101", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}}) == vector<int>{7, 7, 7, 7}));
    assert((sol.maxActiveSectionsAfterTrade("01010101010101010101010101", vector<vector<int>>{vector<int>{0, 25}, vector<int>{1, 24}, vector<int>{2, 23}, vector<int>{3, 22}, vector<int>{4, 21}}) == vector<int>{15, 15, 15, 15, 15}));
    assert((sol.maxActiveSectionsAfterTrade("1100110011", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}, vector<int>{4, 5}}) == vector<int>{10, 10, 10, 8, 6}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001", vector<vector<int>>{vector<int>{0, 9}, vector<int>{1, 8}, vector<int>{2, 7}, vector<int>{3, 6}, vector<int>{4, 5}}) == vector<int>{8, 8, 7, 4, 4}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001001001", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{3, 15}, vector<int>{4, 14}}) == vector<int>{11, 11, 11, 11, 11}));
    assert((sol.maxActiveSectionsAfterTrade("0000000000", vector<vector<int>>{vector<int>{0, 9}, vector<int>{2, 7}, vector<int>{4, 6}}) == vector<int>{0, 0, 0}));
    assert((sol.maxActiveSectionsAfterTrade("1111111111", vector<vector<int>>{vector<int>{0, 9}, vector<int>{2, 7}, vector<int>{4, 6}}) == vector<int>{10, 10, 10}));
    assert((sol.maxActiveSectionsAfterTrade("110001100110001", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{5, 10}, vector<int>{3, 8}}) == vector<int>{12, 12, 12, 7, 11}));
    assert((sol.maxActiveSectionsAfterTrade("0000011111000001111100000", vector<vector<int>>{vector<int>{0, 24}, vector<int>{1, 23}, vector<int>{2, 22}, vector<int>{3, 21}, vector<int>{4, 20}, vector<int>{5, 19}, vector<int>{6, 18}, vector<int>{7, 17}, vector<int>{8, 16}, vector<int>{9, 15}}) == vector<int>{20, 19, 18, 17, 16, 10, 10, 10, 10, 10}));
    assert((sol.maxActiveSectionsAfterTrade("100100100100100", vector<vector<int>>{vector<int>{0, 14}, vector<int>{1, 13}, vector<int>{2, 12}, vector<int>{3, 11}, vector<int>{4, 10}, vector<int>{5, 9}}) == vector<int>{9, 9, 9, 9, 9, 8}));
    assert((sol.maxActiveSectionsAfterTrade("1001001001001", vector<vector<int>>{vector<int>{0, 12}, vector<int>{2, 9}, vector<int>{3, 8}, vector<int>{4, 7}, vector<int>{5, 6}}) == vector<int>{9, 9, 9, 8, 5}));
    assert((sol.maxActiveSectionsAfterTrade("1000000001", vector<vector<int>>{vector<int>{1, 8}, vector<int>{0, 9}, vector<int>{2, 7}, vector<int>{3, 6}}) == vector<int>{2, 2, 2, 2}));
    assert((sol.maxActiveSectionsAfterTrade("0000011110001110000", vector<vector<int>>{vector<int>{0, 18}, vector<int>{1, 17}, vector<int>{2, 16}, vector<int>{3, 15}, vector<int>{4, 14}, vector<int>{5, 13}}) == vector<int>{15, 14, 13, 12, 11, 7}));
    assert((sol.maxActiveSectionsAfterTrade("00110011001100110", vector<vector<int>>{vector<int>{0, 16}, vector<int>{1, 15}, vector<int>{2, 14}, vector<int>{5, 11}, vector<int>{3, 12}}) == vector<int>{12, 12, 12, 11, 12}));

    cout << "All tests passed for maximize-active-section-with-trade-ii" << endl;
    return 0;
}
