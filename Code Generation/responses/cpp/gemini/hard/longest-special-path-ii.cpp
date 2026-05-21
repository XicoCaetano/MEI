#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Solution {
    struct Edge {
        int to;
        int length;
    };

    long long maxLen = 0;
    int minNodes = 1;
    vector<vector<Edge>> adj;
    vector<int> pathNodes;
    vector<long long> prefixDist;
    unordered_map<int, vector<int>> lastSeenIdx;

    void dfs(int u, int p, long long currentDist, int currentDepth, const vector<int>& nums, int windowStart) {
        int val = nums[u];
        int prevIdx = -1;
        
        // Find the most recent occurrence of the current node's value in the current path
        if (lastSeenIdx.count(val) && !lastSeenIdx[val].empty()) {
            prevIdx = lastSeenIdx[val].back();
        }

        // The path must contain at most one duplicate. 
        // If 'val' already exists in the path, the new window must start AFTER that previous occurrence 
        // to ensure that 'val' is the only potential duplicate (occurring at 'prevIdx' and 'u').
        int originalWindowStart = windowStart;
        windowStart = max(windowStart, prevIdx + 1);

        // Calculate length from windowStart to current node u
        long long pathL = currentDist - prefixDist[windowStart];
        int nodesCount = currentDepth - windowStart + 1;

        if (pathL > maxLen) {
            maxLen = pathL;
            minNodes = nodesCount;
        } else if (pathL == maxLen) {
            minNodes = min(minNodes, nodesCount);
        }

        // Standard DFS bookkeeping
        pathNodes.push_back(u);
        prefixDist.push_back(currentDist);
        lastSeenIdx[val].push_back(currentDepth);

        for (auto& edge : adj[u]) {
            if (edge.to != p) {
                dfs(edge.to, u, currentDist + edge.length, currentDepth + 1, nums, windowStart);
            }
        }

        // Backtrack
        lastSeenIdx[val].pop_back();
        prefixDist.pop_back();
        pathNodes.pop_back();
    }

public:
    vector<int> longestSpecialPath(vector<vector<int>>& edges, vector<int>& nums) {
        int n = nums.size();
        adj.assign(n, vector<Edge>());
        for (const auto& e : edges) {
            adj[e[0]].push_back({e[1], e[2]});
            adj[e[1]].push_back({e[0], e[2]});
        }

        maxLen = 0;
        minNodes = 1e9;
        // If all paths have 0 length (all lengths 0), minNodes should be 1
        if (n > 0) minNodes = 1; 

        pathNodes.clear();
        prefixDist.clear();
        lastSeenIdx.clear();
        
        // Starting prefixDist at 0 for depth 0
        prefixDist.push_back(0);
        
        dfs(0, -1, 0, 0, nums, 0);

        return {(int)maxLen, minNodes};
    }
};