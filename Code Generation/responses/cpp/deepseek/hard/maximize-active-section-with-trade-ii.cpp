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