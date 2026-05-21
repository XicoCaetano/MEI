#include <vector>
#include <unordered_set>
using namespace std;

class Solution {
    vector<int> parent;
    int find(int x) { return parent[x] == x ? x : parent[x] = find(parent[x]); }
    void unite(int a, int b) { parent[find(a)] = find(b); }
public:
    int numberOfComponents(vector<vector<int>> properties, int k) {
        int n = properties.size();
        parent.resize(n);
        iota(parent.begin(), parent.end(), 0);
        
        vector<unordered_set<int>> sets(n);
        for (int i = 0; i < n; i++)
            for (int v : properties[i]) sets[i].insert(v);
        
        for (int i = 0; i < n; i++)
            for (int j = i+1; j < n; j++) {
                int cnt = 0;
                for (int v : sets[i]) if (sets[j].count(v)) cnt++;
                if (cnt >= k) unite(i, j);
            }
        
        int components = 0;
        for (int i = 0; i < n; i++) if (find(i) == i) components++;
        return components;
    }
};