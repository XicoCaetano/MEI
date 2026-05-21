#include <vector>
#include <unordered_set>
#include <queue>
#include <algorithm>

using namespace std;

class Solution {
public:
    int numberOfComponents(vector<vector<int>> properties, int k) {
        int n = properties.size();
        
        // Convert each row to a set for efficient intersection calculation
        vector<unordered_set<int>> sets(n);
        for (int i = 0; i < n; i++) {
            for (int val : properties[i]) {
                sets[i].insert(val);
            }
        }
        
        // Build adjacency list
        vector<vector<int>> adj(n);
        for (int i = 0; i < n; i++) {
            for (int j = i + 1; j < n; j++) {
                int common = 0;
                // Count number of common elements between sets[i] and sets[j]
                for (int val : sets[i]) {
                    if (sets[j].count(val)) {
                        common++;
                        if (common >= k) break;
                    }
                }
                if (common >= k) {
                    adj[i].push_back(j);
                    adj[j].push_back(i);
                }
            }
        }
        
        // Count connected components using BFS/DFS
        vector<bool> visited(n, false);
        int components = 0;
        
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                components++;
                // BFS
                queue<int> q;
                q.push(i);
                visited[i] = true;
                
                while (!q.empty()) {
                    int node = q.front();
                    q.pop();
                    
                    for (int neighbor : adj[node]) {
                        if (!visited[neighbor]) {
                            visited[neighbor] = true;
                            q.push(neighbor);
                        }
                    }
                }
            }
        }
        
        return components;
    }
};