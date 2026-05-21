#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>> edges, vector<int> nums) {
        int n = nums.size();
        vector<vector<pair<int,int>>> adj(n);
        for (auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }
        
        int bestLen = 0, bestNodes = 1;
        
        // For each value, maintain stack of path-positions (depths) where it appears
        unordered_map<int, vector<int>> occs;
        // s_set: multiset of second-to-last occurrences (for values with 2+ occurrences in current path)
        multiset<int> s_set;
        // h_set: multiset of (third-to-last occurrence + 1) for values with 3+ occurrences
        //        L_hard = max(h_set), ensures no value appears 3+ times in [L_hard, depth]
        multiset<int> h_set;
        // distStack[i] = cumulative distance from root to node at depth i
        vector<long long> distStack = {0LL};
        
        function<void(int,int,int)> dfs = [&](int u, int par, int depth) {
            int val = nums[u];
            auto& ov = occs[val];
            int k = (int)ov.size(); // size BEFORE pushing current depth
            
            // --- Update s_set (second-to-last of val) BEFORE pushing ---
            // After push, new second-to-last = ov[k-1] (if k>=1), or none if k==0
            if (k == 1) {
                // Now val has 2 occs: insert its second-to-last = ov[0]
                s_set.insert(ov[0]);
            } else if (k >= 2) {
                // Was ov[k-2], becomes ov[k-1]
                s_set.erase(s_set.find(ov[k-2]));
                s_set.insert(ov[k-1]);
            }
            
            // --- Update h_set (third-to-last+1 of val) BEFORE pushing ---
            // After push, third-to-last exists iff k+1 >= 3, i.e., k >= 2
            if (k == 2) {
                // New third-to-last = ov[0]
                h_set.insert(ov[0] + 1);
            } else if (k >= 3) {
                // Was ov[k-3], becomes ov[k-2]
                h_set.erase(h_set.find(ov[k-3] + 1));
                h_set.insert(ov[k-2] + 1);
            }
            
            ov.push_back(depth);
            
            // --- Compute valid window left boundary ---
            // L_hard: ensures no value appears 3+ times in [L_hard, depth]
            int L_hard = h_set.empty() ? 0 : *h_set.rbegin();
            // L_soft: ensures at most one value appears 2+ times in [L_soft, depth]
            // = second-max(s_set) + 1 if |s_set| >= 2, else 0
            int L_soft = ((int)s_set.size() >= 2) ? (*prev(s_set.end(), 2) + 1) : 0;
            int L = max(L_hard, L_soft);
            
            long long pathLen = distStack.back() - distStack[L];
            int nodes = depth - L + 1;
            
            if (pathLen > bestLen || (pathLen == bestLen && nodes < bestNodes)) {
                bestLen = (int)pathLen;
                bestNodes = nodes;
            }
            
            // Recurse into children
            for (auto [v, w] : adj[u]) {
                if (v != par) {
                    distStack.push_back(distStack.back() + w);
                    dfs(v, u, depth + 1);
                    distStack.pop_back();
                }
            }
            
            // --- Undo: pop depth from ov and reverse s_set/h_set updates ---
            ov.pop_back();
            // k is still the size before we pushed (same value)
            
            // Undo s_set
            if (k == 1) {
                s_set.erase(s_set.find(ov[0]));
            } else if (k >= 2) {
                s_set.erase(s_set.find(ov[k-1]));
                s_set.insert(ov[k-2]);
            }
            
            // Undo h_set
            if (k == 2) {
                h_set.erase(h_set.find(ov[0] + 1));
            } else if (k >= 3) {
                h_set.erase(h_set.find(ov[k-2] + 1));
                h_set.insert(ov[k-3] + 1);
            }
        };
        
        dfs(0, -1, 0);
        
        return {bestLen, bestNodes};
    }
};