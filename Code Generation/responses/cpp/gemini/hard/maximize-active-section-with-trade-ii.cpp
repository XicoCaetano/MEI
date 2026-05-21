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