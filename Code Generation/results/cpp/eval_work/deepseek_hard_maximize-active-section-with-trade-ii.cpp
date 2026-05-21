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
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>
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
        int n = s.length();
        
        // For each query, handle independently
        vector<int> result;
        result.reserve(queries.size());
        
        for (const auto& q : queries) {
            int l = q[0], r = q[1];
            
            // Build augmented string: '1' + s[l..r] + '1'
            string t = "1" + s.substr(l, r - l + 1) + "1";
            int m = t.length();
            
            // Count initial active sections (excluding the augmented '1's)
            int initialActive = 0;
            for (int i = 1; i < m - 1; ++i) {
                if (t[i] == '1') {
                    // Count contiguous block of '1's
                    int j = i;
                    while (j < m - 1 && t[j] == '1') ++j;
                    initialActive++;
                    i = j - 1;
                }
            }
            
            // Find maximal improvement from a trade
            int maxImprovement = 0;
            
            // Find positions of zeros and ones patterns
            vector<pair<int, int>> onesBlocks; // (start, end) indices in t
            vector<pair<int, int>> zerosBlocks;
            
            int i = 0;
            while (i < m) {
                if (t[i] == '1') {
                    int start = i;
                    while (i < m && t[i] == '1') ++i;
                    onesBlocks.emplace_back(start, i - 1);
                } else {
                    int start = i;
                    while (i < m && t[i] == '0') ++i;
                    zerosBlocks.emplace_back(start, i - 1);
                }
            }
            
            // A valid trade needs:
            // 1. A block of '1's surrounded by '0's (not including ends)
            // 2. A block of '0's surrounded by '1's (not including ends)
            // Finding best improvement: choose O = zeros block, I = ones block, and convert I->0 and O->1
            // Improvement = length(O) - length(I) + (if merging adjacent ones blocks when O filled)
            
            // Simplified: Look at patterns: 0...01...10...0 or 1...10...01...1
            // But with augmented '1's at ends, we can treat it as circular? No.
            
            // Better approach: For each zero block that is not at ends,
            // it can be filled to become all '1's, merging up to 2 adjacent one blocks.
            // The cost is converting any one block to zero (must be surrounded by zeros).
            
            // Find all one blocks that are not at ends (i.e., have zeros on both sides)
            // and all zero blocks that are not at ends.
            vector<pair<int, int>> candidateOnes;
            vector<pair<int, int>> candidateZeros;
            
            for (size_t j = 0; j < onesBlocks.size(); ++j) {
                int start = onesBlocks[j].first;
                int end = onesBlocks[j].second;
                // Check if not at ends and surrounded by zeros
                if (start > 0 && end < m - 1 && t[start-1] == '0' && t[end+1] == '0') {
                    candidateOnes.emplace_back(start, end);
                }
            }
            
            for (size_t j = 0; j < zerosBlocks.size(); ++j) {
                int start = zerosBlocks[j].first;
                int end = zerosBlocks[j].second;
                // Check if not at ends and surrounded by ones
                if (start > 0 && end < m - 1 && t[start-1] == '1' && t[end+1] == '1') {
                    candidateZeros.emplace_back(start, end);
                }
            }
            
            // For each candidate zero block, calculate gain if we fill it
            // and convert a one block to zero
            for (const auto& zeroBlock : candidateZeros) {
                int zeroStart = zeroBlock.first;
                int zeroEnd = zeroBlock.second;
                int zeroLen = zeroEnd - zeroStart + 1;
                
                // Find the one blocks adjacent to this zero block
                int leftOneStart = zeroStart - 1;
                while (leftOneStart >= 0 && t[leftOneStart] == '1') --leftOneStart;
                leftOneStart++;
                int leftOneEnd = zeroStart - 1;
                
                int rightOneStart = zeroEnd + 1;
                int rightOneEnd = rightOneStart;
                while (rightOneEnd < m && t[rightOneEnd] == '1') ++rightOneEnd;
                rightOneEnd--;
                
                // Gain from filling zero block: we get zeroLen new '1's, and we merge left and right one blocks
                int gain = zeroLen;
                // If we merge left and right one blocks, we reduce one block count
                // But we also need to convert a one block to zero
                
                // For each candidate one block, see if it's within this zero block's reach? No, separate.
                // Better: For each candidate one block we convert, we lose its length.
                for (const auto& oneBlock : candidateOnes) {
                    int oneStart = oneBlock.first;
                    int oneEnd = oneBlock.second;
                    int oneLen = oneEnd - oneStart + 1;
                    
                    // Convert this one block to zero
                    int improvement = gain - oneLen;
                    // Additionally, if this one block is adjacent to the zero block we filled,
                    // it might merge differently, but we already considered
                    
                    maxImprovement = max(maxImprovement, improvement);
                }
            }
            
            // Also consider: if we fill a zero block and it touches the ends (with our augmented ones)
            for (size_t j = 0; j < zerosBlocks.size(); ++j) {
                int start = zerosBlocks[j].first;
                int end = zerosBlocks[j].second;
                // Check if it's at an end with augmented '1'
                if (start == 0 || end == m-1) {
                    // Can't use because surrounded by 1's condition fails at ends? Wait augmented '1's are fake.
                    // Actually condition: zero block must be surrounded by 1's, augmented '1's are real 1's.
                    // So check:
                    if (start == 0) {
                        // Adjacent to left augmented 1, need right side to be 1
                        if (end + 1 < m && t[end+1] == '1') {
                            int zeroLen = end - start + 1;
                            // We can fill this zero block, gaining zeroLen
                            // But we must convert a one block to zero (must be surrounded by zeros)
                            // Find a candidate one block not at ends
                            for (const auto& oneBlock : candidateOnes) {
                                int oneLen = oneBlock.second - oneBlock.first + 1;
                                int improvement = zeroLen - oneLen;
                                maxImprovement = max(maxImprovement, improvement);
                            }
                        }
                    }
                    if (end == m-1) {
                        if (start - 1 >= 0 && t[start-1] == '1') {
                            int zeroLen = end - start + 1;
                            for (const auto& oneBlock : candidateOnes) {
                                int oneLen = oneBlock.second - oneBlock.first + 1;
                                int improvement = zeroLen - oneLen;
                                maxImprovement = max(maxImprovement, improvement);
                            }
                        }
                    }
                }
            }
            
            // Also consider: convert a one block to zero (must be surrounded by zeros)
            // and fill a zero block (must be surrounded by ones)
            // This is symmetric, we already considered both in loop above.
            
            // Edge case: if no valid trade possible
            if (maxImprovement <= 0) {
                result.push_back(initialActive);
            } else {
                result.push_back(initialActive + maxImprovement);
            }
        }
        
        return result;
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
