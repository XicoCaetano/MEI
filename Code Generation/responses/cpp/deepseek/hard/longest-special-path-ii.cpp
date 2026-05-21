#include <vector>
#include <unordered_map>
#include <algorithm>
#include <functional>
using namespace std;

class Solution {
public:
    vector<int> longestSpecialPath(vector<vector<int>> edges, vector<int> nums) {
        int n = nums.size();
        vector<vector<pair<int, int>>> graph(n);
        for (auto& e : edges) {
            int u = e[0], v = e[1], w = e[2];
            graph[u].emplace_back(v, w);
            graph[v].emplace_back(u, w);
        }
        
        int maxLen = 0, minNodes = 0;
        unordered_map<int, int> lastPos;
        lastPos[nums[0]] = 0;
        
        vector<int> prefixLen = {0};
        vector<int> prefixNodes = {1};
        
        function<void(int, int, int, int, int)> dfs = [&](int node, int parent, int startIdx, int lenSoFar, int nodesSoFar) {
            // Check max special path ending at current node
            int conflictIdx = max(startIdx, lastPos[nums[node]] + 1);
            int currentLen = lenSoFar - (conflictIdx > 0 ? prefixLen[conflictIdx - 1] : 0);
            int currentNodes = nodesSoFar - (conflictIdx > 0 ? prefixNodes[conflictIdx - 1] : 0);
            
            if (currentLen > maxLen) {
                maxLen = currentLen;
                minNodes = currentNodes;
            } else if (currentLen == maxLen && currentNodes < minNodes) {
                minNodes = currentNodes;
            }
            
            int oldPos = lastPos[nums[node]];
            lastPos[nums[node]] = nodesSoFar;
            
            for (auto& [nei, w] : graph[node]) {
                if (nei == parent) continue;
                prefixLen.push_back(lenSoFar + w);
                prefixNodes.push_back(nodesSoFar + 1);
                dfs(nei, node, conflictIdx, lenSoFar + w, nodesSoFar + 1);
                prefixLen.pop_back();
                prefixNodes.pop_back();
            }
            
            lastPos[nums[node]] = oldPos;
        };
        
        dfs(0, -1, 0, 0, 1);
        
        return {maxLen, minNodes};
    }
};