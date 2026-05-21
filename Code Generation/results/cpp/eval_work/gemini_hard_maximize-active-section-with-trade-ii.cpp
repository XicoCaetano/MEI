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


// === MODEL RESPONSE ===
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class SparseTable {
public:
    vector<vector<int>> st;
    int m;
    SparseTable(const vector<int>& a) {
        int n = a.size();
        if (n == 0) return;
        m = 0;
        while ((1 << m) <= n) ++m;
        st.assign(n, vector<int>(m, 0));
        for (int i = 0; i < n; ++i) {
            st[i][0] = a[i];
        }
        for (int j = 1; j < m; ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
            }
        }
    }
    int query(int l, int r) {
        if (l > r) return 0;
        int len = r - l + 1;
        int k = 31 - __builtin_clz(len);
        return max(st[l][k], st[r - (1 << k) + 1][k]);
    }
};

class Solution {
public:
    vector<int> maxActiveSectionsAfterTrade(string s, vector<vector<int>> queries) {
        int n = s.length();
        
        // Find contiguous blocks of 0s and 1s
        vector<pair<int, int>> zeros, ones;
        for (int i = 0; i < n; ) {
            int j = i;
            while (j < n && s[j] == s[i]) j++;
            if (s[i] == '0') zeros.push_back({i, j - 1});
            else ones.push_back({i, j - 1});
            i = j;
        }

        // Prefix sum for '1's to get current active count in range
        vector<int> pref(n + 1, 0);
        for (int i = 0; i < n; i++) pref[i + 1] = pref[i] + (s[i] == '1' ? 1 : 0);

        // A trade is possible if a block of 1s is surrounded by 0s in '1' + sub + '1'
        // This effectively means a '0' block is surrounded by '1' blocks.
        // We trade a '1' block (len L1) for a '0' block (len L0).
        // Gain = L0 - L1. Total = Total_ones + L0 - L1.
        // To maximize, we maximize (L0 - L1) where L1 is a block of 1s and L0 is an adjacent block of 0s.
        // More specifically, the rule is: convert 1-block to 0, then adjacent 0-block to 1.
        // This is equivalent to picking two adjacent blocks (one '1', one '0') and flipping both.
        
        // Let's identify pairs of adjacent (1-block, 0-block) or (0-block, 1-block).
        // In the augmented string '1' + sub + '1':
        // A block of 1s is "surrounded by 0s" only if it's an internal block of 1s 
        // in the original string that has 0s on both sides.
        
        vector<pair<int, int>> all_blocks; // Stores {start, end} and type implicitly by index
        vector<int> block_type; // 0 for '0', 1 for '1'
        int i = 0;
        while(i < n){
            int j = i;
            while(j < n && s[j] == s[i]) j++;
            all_blocks.push_back({i, j - 1});
            block_type.push_back(s[i] - '0');
            i = j;
        }

        int m = all_blocks.size();
        // potential_gain[i] = length of 0-block at i +/- length of 1-block at i+1 or i-1
        // We only care about internal 1-blocks (surrounded by 0s)
        // In the augmented '1' + sub + '1', even the first/last blocks of the substring
        // might become "surrounded" by the augmented '1's.
        
        vector<int> results;
        for (auto& q : queries) {
            int L = q[0], R = q[1];
            int current_ones = pref[R + 1] - pref[L];
            
            // Find blocks fully or partially contained in [L, R]
            int start_idx = lower_bound(all_blocks.begin(), all_blocks.end(), make_pair(L, -1)) - all_blocks.begin();
            if (start_idx > 0 && all_blocks[start_idx-1].second >= L) start_idx--;
            
            int end_idx = lower_bound(all_blocks.begin(), all_blocks.end(), make_pair(R, n + 1)) - all_blocks.begin() - 1;

            int max_gain = 0;
            // Iterate through blocks in the range to find valid trades
            for (int k = start_idx; k <= end_idx; k++) {
                if (block_type[k] == 1) {
                    int b_start = max(L, all_blocks[k].first);
                    int b_end = min(R, all_blocks[k].second);
                    int L1 = b_end - b_start + 1;

                    // Check if this 1-block is surrounded by 0s in '1' + sub + '1'
                    bool left_is_0 = false;
                    if (b_start > L) {
                        if (s[b_start - 1] == '0') left_is_0 = true;
                    } 
                    
                    bool right_is_0 = false;
                    if (b_end < R) {
                        if (s[b_end + 1] == '0') right_is_0 = true;
                    }

                    if (left_is_0 && right_is_0) {
                        // This 1-block is eligible to be converted to 0s.
                        // Then we flip a contiguous block of 0s surrounded by 1s to 1s.
                        // The best 0-block is the largest one adjacent to a 1 in '1'+sub+'1'.
                        
                        // Find max 0-block in [L, R] that is surrounded by 1s (including augmented)
                        for(int z = start_idx; z <= end_idx; z++) {
                            if (block_type[z] == 0) {
                                int z_start = max(L, all_blocks[z].first);
                                int z_end = min(R, all_blocks[z].second);
                                int L0 = z_end - z_start + 1;
                                
                                bool z_left_ok = (z_start == L || s[z_start-1] == '1');
                                bool z_right_ok = (z_end == R || s[z_end+1] == '1');
                                
                                if (z_left_ok && z_right_ok) {
                                    max_gain = max(max_gain, L0 - L1);
                                }
                            }
                        }
                    }
                }
            }
            results.push_back(current_ones + max_gain);
        }
        return results;
    }
};

// === TEST HARNESS ===
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
