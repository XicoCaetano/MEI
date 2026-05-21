#include <vector>
#include <unordered_set>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    struct DSU {
        vector<int> parent;
        int components;
        DSU(int n) {
            parent.resize(n);
            iota(parent.begin(), parent.end(), 0);
            components = n;
        }
        int find(int i) {
            if (parent[i] == i) return i;
            return parent[i] = find(parent[i]);
        }
        void unite(int i, int j) {
            int root_i = find(i);
            int root_j = find(j);
            if (root_i != root_j) {
                parent[root_i] = root_j;
                components--;
            }
        }
    };

    int intersect(const vector<int>& a, const vector<int>& b) {
        unordered_set<int> set_a(a.begin(), a.end());
        unordered_set<int> set_b(b.begin(), b.end());
        int common = 0;
        for (int val : set_a) {
            if (set_b.count(val)) {
                common++;
            }
        }
        return common;
    }

    int numberOfComponents(vector<vector<int>> properties, int k) {
        int n = properties.size();
        DSU dsu(n);

        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                if (intersect(properties[i], properties[j]) >= k) {
                    dsu.unite(i, j);
                }
            }
        }

        return dsu.components;
    }
};