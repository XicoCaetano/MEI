// task_id: minimum-cost-to-reach-every-position
// difficulty: Easy

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


class Solution {
public:
    vector<int> minCosts(vector<int> cost) {
        for (size_t i = 1; i < cost.size(); ++i) {
            cost[i] = min(cost[i], cost[i-1]);
        }
        return cost;
    }
};

int main() {
    Solution sol;

    assert((sol.minCosts(vector<int>{1, 10, 1, 10, 1, 10, 1, 10, 1, 10}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{10, 20, 30, 40, 50}) == vector<int>{10, 10, 10, 10, 10}));
    assert((sol.minCosts(vector<int>{50, 25, 75, 100, 20, 30, 40, 60, 80, 90}) == vector<int>{50, 25, 25, 25, 20, 20, 20, 20, 20, 20}));
    assert((sol.minCosts(vector<int>{50, 20, 30, 10, 40}) == vector<int>{50, 20, 20, 10, 10}));
    assert((sol.minCosts(vector<int>{1, 2, 4, 6, 7}) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 100}) == vector<int>{1, 1}));
    assert((sol.minCosts(vector<int>{1}) == vector<int>{1}));
    assert((sol.minCosts(vector<int>{1, 1, 1, 1, 1}) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{100, 1}) == vector<int>{100, 1}));
    assert((sol.minCosts(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));
    assert((sol.minCosts(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}) == vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{5, 3, 4, 1, 3, 2}) == vector<int>{5, 3, 3, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{100, 100, 100, 100, 100, 100, 100, 100, 100, 100}) == vector<int>{100, 100, 100, 100, 100, 100, 100, 100, 100, 100}));
    assert((sol.minCosts(vector<int>{99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75}) == vector<int>{99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75}));
    assert((sol.minCosts(vector<int>{99, 1, 99, 1, 99, 1, 99, 1, 99, 1}) == vector<int>{99, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}) == vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7}));
    assert((sol.minCosts(vector<int>{10, 5, 15, 20, 25, 30, 35, 40, 45, 50}) == vector<int>{10, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.minCosts(vector<int>{7, 5, 3, 9, 6, 4, 8, 2, 10, 1}) == vector<int>{7, 5, 3, 3, 3, 3, 3, 2, 2, 1}));
    assert((sol.minCosts(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.minCosts(vector<int>{100, 99, 98, 97, 96, 95, 94}) == vector<int>{100, 99, 98, 97, 96, 95, 94}));
    assert((sol.minCosts(vector<int>{50, 25, 75, 100, 200, 150, 175, 125, 225, 275, 300, 250, 350, 400, 450}) == vector<int>{50, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25, 25}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 5, 9, 13, 17, 21, 25, 29, 33, 37, 41, 45, 49, 53, 57, 61, 65, 69, 73, 77, 81, 85, 89, 93, 97, 100, 97, 93, 89, 85, 81, 77, 73, 69, 65, 61, 57, 53, 49, 45, 41, 37, 33, 29, 25, 21, 17, 13, 9, 5, 1}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{50, 40, 30, 20, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{50, 40, 30, 20, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{3, 2, 1, 4, 5, 6, 7, 8, 9, 10}) == vector<int>{3, 2, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2, 3, 1, 2}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 10}) == vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 1}));
    assert((sol.minCosts(vector<int>{10, 2, 3, 4, 5, 6, 7, 8, 9, 1}) == vector<int>{10, 2, 2, 2, 2, 2, 2, 2, 2, 1}));
    assert((sol.minCosts(vector<int>{5, 2, 8, 6, 3, 1, 4}) == vector<int>{5, 2, 2, 2, 2, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 10, 2, 9, 3, 8, 4, 7, 5, 6}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{5, 3, 8, 2, 9, 4, 7, 1, 6}) == vector<int>{5, 3, 3, 2, 2, 2, 2, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 3, 2, 5, 4, 7, 6, 9, 8, 10}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{100, 1, 99, 2, 98, 3, 97, 4}) == vector<int>{100, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 4, 3, 2, 1}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}) == vector<int>{3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{10, 5, 10, 5, 10, 5, 10, 5, 10, 5}) == vector<int>{10, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.minCosts(vector<int>{1, 1, 2, 1, 2, 1, 3, 1, 2, 1, 3, 1, 4, 1, 2, 1, 3, 1, 4, 1, 5}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{100, 50, 25, 12, 6, 3, 1}) == vector<int>{100, 50, 25, 12, 6, 3, 1}));
    assert((sol.minCosts(vector<int>{100, 1, 10, 1, 100, 1, 10, 1, 100, 1}) == vector<int>{100, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{7, 6, 5, 4, 3, 2, 1, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 1, 2, 3, 4, 5, 6, 7}) == vector<int>{7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{5, 3, 4, 2, 6, 1}) == vector<int>{5, 3, 3, 2, 2, 1}));
    assert((sol.minCosts(vector<int>{5, 3, 8, 2, 7, 4}) == vector<int>{5, 3, 3, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{1, 10, 2, 9, 3, 8, 4, 7, 5, 6}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{15, 25, 5, 35, 45, 10, 50, 20, 60, 30}) == vector<int>{15, 15, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.minCosts(vector<int>{5, 8, 2, 10, 6, 3}) == vector<int>{5, 5, 2, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{3, 6, 9, 12, 15, 18, 21, 24, 27, 30, 33}) == vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}));
    assert((sol.minCosts(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{2, 3, 1, 5, 4, 7, 6, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 1, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50}) == vector<int>{2, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{7, 6, 5, 4, 3, 2, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}) == vector<int>{7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{10, 10, 10, 10, 1, 10, 10, 10, 10, 1}) == vector<int>{10, 10, 10, 10, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7}) == vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 7}));
    assert((sol.minCosts(vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));
    assert((sol.minCosts(vector<int>{5, 3, 4, 1, 3, 2, 8, 6, 7}) == vector<int>{5, 3, 3, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{5, 8, 2, 9, 4, 6, 1}) == vector<int>{5, 5, 2, 2, 2, 2, 1}));
    assert((sol.minCosts(vector<int>{10, 5, 20, 15, 25, 30, 35, 40, 45, 50}) == vector<int>{10, 5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.minCosts(vector<int>{10, 5, 3, 1, 7, 2, 6, 8, 4, 9}) == vector<int>{10, 5, 3, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 1, 100, 1, 1, 1, 100, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1, 1, 100, 1, 1}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{5, 8, 6, 3, 7, 2, 9, 4}) == vector<int>{5, 5, 5, 3, 3, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{3, 1, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1, 3, 2, 1}) == vector<int>{3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{2, 5, 1, 3, 7, 4, 6, 8, 10, 9}) == vector<int>{2, 2, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{30, 20, 10, 40, 50, 60, 70, 80, 90, 100}) == vector<int>{30, 20, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.minCosts(vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));
    assert((sol.minCosts(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}) == vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{10, 1, 10, 1, 10, 1, 10, 1, 10, 1}) == vector<int>{10, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{3, 5, 2, 7, 8, 6, 4, 9, 1, 10}) == vector<int>{3, 3, 2, 2, 2, 2, 2, 2, 1, 1}));
    assert((sol.minCosts(vector<int>{20, 20, 20, 20, 20, 1, 1, 1, 1, 1}) == vector<int>{20, 20, 20, 20, 20, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 100, 1, 100, 1, 100, 1, 100}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150}) == vector<int>{10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.minCosts(vector<int>{100, 10, 20, 30, 40, 50, 60, 70, 80, 90}) == vector<int>{100, 10, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.minCosts(vector<int>{3, 2, 3, 2, 3, 2, 3, 2, 3, 2, 3, 2}) == vector<int>{3, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}) == vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{1, 10, 1, 10, 1, 10, 1, 10, 1, 10, 1, 10, 1, 10, 1, 10}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{9, 1, 4, 3, 7, 2, 5, 8}) == vector<int>{9, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{50, 10, 20, 30, 40, 5, 15, 25, 35, 45}) == vector<int>{50, 10, 10, 10, 10, 5, 5, 5, 5, 5}));
    assert((sol.minCosts(vector<int>{1, 3, 2, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{5, 3, 4, 1, 3, 2, 8, 6, 7, 9}) == vector<int>{5, 3, 3, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{50, 40, 30, 20, 10, 5, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == vector<int>{50, 40, 30, 20, 10, 5, 3, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}) == vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3}));
    assert((sol.minCosts(vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}) == vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}));
    assert((sol.minCosts(vector<int>{50, 20, 50, 20, 50, 20, 50, 20, 50, 20, 50, 20, 50, 20, 50, 20, 50, 20, 50, 20}) == vector<int>{50, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20}));
    assert((sol.minCosts(vector<int>{3, 2, 1, 4, 7, 6, 5}) == vector<int>{3, 2, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{4, 1, 3, 2, 5, 8, 6, 7, 9, 10}) == vector<int>{4, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{50, 40, 30, 20, 10, 1, 2, 3, 4, 5}) == vector<int>{50, 40, 30, 20, 10, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31, 33, 35, 37, 39}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{5, 3, 8, 6, 2, 4, 7}) == vector<int>{5, 3, 3, 3, 2, 2, 2}));
    assert((sol.minCosts(vector<int>{1, 3, 5, 2, 4, 6, 3, 5, 7, 4, 6, 8, 5, 7, 9, 6, 8, 10, 7, 9}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}));
    assert((sol.minCosts(vector<int>{100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10}) == vector<int>{100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90, 89, 88, 87, 86, 85, 84, 83, 82, 81, 80, 79, 78, 77, 76, 75, 74, 73, 72, 71, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10}));
    assert((sol.minCosts(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{30, 10, 50, 20, 40, 60, 80, 70, 90}) == vector<int>{30, 10, 10, 10, 10, 10, 10, 10, 10}));
    assert((sol.minCosts(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}));
    assert((sol.minCosts(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1}) == vector<int>{29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1}));
    assert((sol.minCosts(vector<int>{20, 15, 10, 5, 1, 2, 3}) == vector<int>{20, 15, 10, 5, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{2, 2, 2, 1, 1, 1, 3, 3, 3, 3}) == vector<int>{2, 2, 2, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{1, 3, 2, 4, 1, 5, 2, 6, 3, 7, 4, 8, 5, 9, 6, 10, 7, 11, 8, 12}) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}) == vector<int>{3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.minCosts(vector<int>{7, 8, 9, 10, 2, 3, 4, 5, 6, 1}) == vector<int>{7, 7, 7, 7, 2, 2, 2, 2, 2, 1}));

    cout << "All tests passed for minimum-cost-to-reach-every-position" << endl;
    return 0;
}
