// task_id: properties-graph
// difficulty: Medium

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



// === MODEL RESPONSE ===
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4}, vector<int>{2, 3, 4, 5}, vector<int>{3, 4, 5, 6}, vector<int>{4, 5, 6, 7}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30}, vector<int>{30, 40, 50}, vector<int>{40, 50, 60}, vector<int>{50, 60, 70}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 1}}, 4) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1}, vector<int>{1, 1, 1}, vector<int>{1, 1, 1}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 1}}, 4) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1}, vector<int>{1, 1}}, 2) == 2));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{2, 3, 4}, vector<int>{3, 4, 5}, vector<int>{4, 5, 6}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{4, 5, 6}, vector<int>{7, 8, 9}, vector<int>{1, 4, 7}, vector<int>{2, 5, 8}, vector<int>{3, 6, 9}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30}, vector<int>{20, 30, 40}, vector<int>{30, 40, 50}, vector<int>{40, 50, 60}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{1, 1}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{7, 7}}, 1) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1}, vector<int>{2}, vector<int>{3}, vector<int>{4}, vector<int>{5}}, 1) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{3, 4}, vector<int>{5, 6}, vector<int>{7, 8}}, 0) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{2, 3, 4}, vector<int>{4, 3, 5}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30}, vector<int>{10, 20, 30}, vector<int>{10, 20, 30}, vector<int>{10, 20, 30}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{4, 5, 6}, vector<int>{7, 8, 9}}, 2) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{1, 11, 21, 31, 41, 51, 61, 71, 81, 91}}, 2) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11}}, 4) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, vector<int>{10, 11, 12, 13, 14, 15, 16, 17, 18, 19}}, 4) == 2));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{5, 5, 5}, vector<int>{5, 5, 5}, vector<int>{5, 5, 5}, vector<int>{5, 5, 5}, vector<int>{5, 5, 5}, vector<int>{5, 5, 5}}, 3) == 6));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, vector<int>{2, 3, 4, 5, 6}, vector<int>{6, 5, 4, 3, 2}, vector<int>{3, 4, 5, 6, 7}}, 4) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 11}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 12}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 2}, vector<int>{1, 1, 2, 2}, vector<int>{1, 2, 2, 2}}, 3) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}}, 10) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{1, 4, 7, 10, 13, 16, 19, 22, 25, 28}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{2, 3, 4}, vector<int>{4, 3, 5}, vector<int>{5, 6, 7}, vector<int>{7, 8, 9}}, 2) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6}, vector<int>{6, 7, 8, 9, 10, 11}, vector<int>{11, 12, 13, 14, 15, 16}, vector<int>{16, 17, 18, 19, 20, 21}}, 3) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 11}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 12}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 13}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30, 40, 50}, vector<int>{50, 40, 30, 20, 10}, vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, vector<int>{10, 15, 20, 25, 30}}, 2) == 2));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{5, 10, 15, 20}, vector<int>{10, 15, 20, 25}, vector<int>{15, 20, 25, 30}, vector<int>{20, 25, 30, 35}, vector<int>{25, 30, 35, 40}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{2, 2, 2, 2}, vector<int>{1, 1, 2, 2}, vector<int>{2, 2, 1, 1}, vector<int>{1, 2, 1, 2}, vector<int>{2, 1, 2, 1}}, 2) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1, 1}, vector<int>{2, 2, 2, 2, 2}, vector<int>{3, 3, 3, 3, 3}, vector<int>{1, 2, 3, 4, 5}, vector<int>{2, 3, 4, 5, 6}}, 3) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 1}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 1}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{1, 4}, vector<int>{2, 3}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}, vector<int>{10, 1}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 10, 100}, vector<int>{10, 100, 1000}, vector<int>{100, 1000, 10000}, vector<int>{1000, 10000, 100000}, vector<int>{100000, 1, 10}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5}, vector<int>{2, 3, 4, 5, 6}, vector<int>{3, 4, 5, 6, 7}, vector<int>{4, 5, 6, 7, 8}, vector<int>{5, 6, 7, 8, 9}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{2, 3, 4}, vector<int>{4, 5, 6}, vector<int>{6, 7, 8}, vector<int>{8, 9, 10}, vector<int>{10, 11, 12}}, 2) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30}, vector<int>{20, 30, 40}, vector<int>{30, 40, 50}, vector<int>{40, 50, 60}, vector<int>{50, 60, 70}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1}, vector<int>{1, 1, 2}, vector<int>{1, 2, 2}, vector<int>{2, 2, 2}, vector<int>{2, 2, 3}, vector<int>{2, 3, 3}, vector<int>{3, 3, 3}}, 2) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{21, 22, 23, 24, 25, 26, 27, 28, 29, 30}}, 1) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{1, 2, 2, 3, 3, 4, 4, 5, 5, 6}, vector<int>{1, 1, 2, 3, 3, 4, 4, 5, 6, 6}, vector<int>{1, 2, 2, 3, 3, 4, 4, 5, 6, 7}, vector<int>{1, 2, 2, 3, 3, 4, 4, 5, 6, 8}}, 4) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{4, 5, 6}, vector<int>{7, 8, 9}, vector<int>{1, 4, 7}, vector<int>{2, 5, 8}, vector<int>{3, 6, 9}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 6}, vector<int>{6, 7}, vector<int>{7, 8}, vector<int>{8, 9}, vector<int>{9, 10}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32}}, 15) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{21, 22, 23, 24, 25, 26, 27, 28, 29, 30}}, 5) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}}, 10) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30, 40, 50}, vector<int>{10, 20, 30, 60, 70}, vector<int>{10, 20, 50, 60, 70}, vector<int>{10, 50, 60, 70, 80}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{3, 3, 3, 4, 5, 6, 7, 8, 9, 10}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{2, 3, 4}, vector<int>{3, 4, 5}, vector<int>{4, 5, 6}, vector<int>{5, 6, 7}, vector<int>{6, 7, 8}, vector<int>{7, 8, 9}, vector<int>{8, 9, 10}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{2, 2, 2, 2}, vector<int>{3, 3, 3, 3}, vector<int>{1, 2, 3, 4}, vector<int>{4, 5, 6, 7}}, 2) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39}}, 6) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4}, vector<int>{5, 6, 7, 8}, vector<int>{9, 10, 11, 12}, vector<int>{13, 14, 15, 16}, vector<int>{1, 5, 9, 13}, vector<int>{2, 6, 10, 14}, vector<int>{3, 7, 11, 15}, vector<int>{4, 8, 12, 16}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27}}, 6) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{21, 22, 23, 24, 25, 26, 27, 28, 29, 30}, vector<int>{31, 32, 33, 34, 35, 36, 37, 38, 39, 40}}, 1) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 2, 2}, vector<int>{2, 2, 3, 3}, vector<int>{3, 3, 4, 4}, vector<int>{4, 4, 1, 1}}, 2) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 1}, vector<int>{1, 3}, vector<int>{3, 5}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5}, vector<int>{2, 3, 4, 5, 6}, vector<int>{3, 4, 5, 6, 7}, vector<int>{4, 5, 6, 7, 8}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 1}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 1, 2}, vector<int>{4, 5, 6, 7, 8, 9, 10, 1, 2, 3}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}, 5) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{1, 2, 3}, vector<int>{1, 2, 3}, vector<int>{1, 2, 3}, vector<int>{1, 2, 3}, vector<int>{1, 2, 3}, vector<int>{1, 2, 3}, vector<int>{1, 2, 3}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30}, vector<int>{10, 20, 40}, vector<int>{10, 30, 40}, vector<int>{20, 30, 40}, vector<int>{10, 20, 30, 40}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{3, 6, 9, 12, 15, 18, 21, 24, 27, 30}, vector<int>{4, 8, 12, 16, 20, 24, 28, 32, 36, 40}}, 4) == 2));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{2, 2, 2, 2}, vector<int>{3, 3, 3, 3}, vector<int>{1, 2, 3, 4}}, 2) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 1}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 2}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}, vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3}, vector<int>{4, 4, 4, 4, 4, 4, 4, 4, 4, 4}}, 5) == 4));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 2, 2}, vector<int>{2, 2, 3, 3}, vector<int>{3, 3, 4, 4}, vector<int>{4, 4, 5, 5}, vector<int>{5, 5, 6, 6}}, 2) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1, 1}, vector<int>{2, 2, 2, 2, 2}, vector<int>{3, 3, 3, 3, 3}, vector<int>{4, 4, 4, 4, 4}, vector<int>{5, 5, 5, 5, 5}}, 1) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}}, 8) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6}, vector<int>{2, 3, 4, 5, 6, 7}, vector<int>{3, 4, 5, 6, 7, 8}, vector<int>{4, 5, 6, 7, 8, 9}}, 4) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2}, vector<int>{2, 3}, vector<int>{3, 4}, vector<int>{4, 5}, vector<int>{5, 1}, vector<int>{1, 3}, vector<int>{2, 4}, vector<int>{3, 5}, vector<int>{4, 1}, vector<int>{5, 2}}, 1) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{10, 20, 30}, vector<int>{10, 20, 40}, vector<int>{10, 30, 50}, vector<int>{20, 30, 60}, vector<int>{30, 40, 50}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}}, 2) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 2, 3, 4, 4, 5}, vector<int>{2, 3, 3, 4, 4, 5, 5}, vector<int>{3, 4, 4, 5, 5, 6, 6}, vector<int>{4, 5, 5, 6, 6, 7, 7}, vector<int>{5, 6, 6, 7, 7, 8, 8}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6}, vector<int>{2, 3, 4, 5, 6, 7}, vector<int>{3, 4, 5, 6, 7, 8}, vector<int>{4, 5, 6, 7, 8, 9}, vector<int>{5, 6, 7, 8, 9, 10}}, 4) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5}, vector<int>{6, 7, 8, 9, 10}, vector<int>{1, 6, 2, 7, 3}, vector<int>{8, 4, 9, 5, 10}, vector<int>{11, 12, 13, 14, 15}}, 2) == 2));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 2}, vector<int>{1, 1, 2, 2}, vector<int>{1, 2, 2, 2}, vector<int>{2, 2, 2, 2}}, 3) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1, 1}, vector<int>{1, 1, 1, 2}, vector<int>{1, 1, 2, 2}, vector<int>{1, 2, 2, 2}, vector<int>{2, 2, 2, 2}}, 3) == 5));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5}, vector<int>{2, 3, 4, 5, 6}, vector<int>{3, 4, 5, 6, 7}, vector<int>{4, 5, 6, 7, 8}, vector<int>{5, 6, 7, 8, 9}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5}}, 3) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 11}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 11, 12}}, 4) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 6, 7, 8, 9}, vector<int>{9, 10, 11, 12, 13}, vector<int>{13, 14, 15, 16, 17}, vector<int>{17, 18, 19, 20, 21}, vector<int>{21, 22, 23, 24, 25}}, 2) == 6));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}}, 5) == 1));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3}, vector<int>{4, 5, 6}, vector<int>{7, 8, 9}, vector<int>{10, 11, 12}, vector<int>{13, 14, 15}, vector<int>{1, 4, 7}, vector<int>{2, 5, 8}, vector<int>{3, 6, 9}}, 1) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1, 1}, vector<int>{1, 1, 2}, vector<int>{1, 2, 2}, vector<int>{2, 2, 2}, vector<int>{2, 2, 1}}, 2) == 3));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 1}, vector<int>{2, 2}, vector<int>{3, 3}, vector<int>{4, 4}, vector<int>{5, 5}, vector<int>{6, 6}, vector<int>{7, 7}, vector<int>{8, 8}, vector<int>{9, 9}, vector<int>{10, 10}}, 1) == 10));
    assert((sol.numberOfComponents(vector<vector<int>>{vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{2, 3, 4, 5, 6, 7, 8, 9, 10, 1}, vector<int>{3, 4, 5, 6, 7, 8, 9, 10, 1, 2}}, 4) == 1));

    cout << "All tests passed for properties-graph" << endl;
    return 0;
}
