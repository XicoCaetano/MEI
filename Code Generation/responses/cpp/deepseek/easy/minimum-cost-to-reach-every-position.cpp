#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> minCosts(vector<int> cost) {
        int n = cost.size();
        vector<int> answer(n);
        
        int min_cost = cost[0];
        for (int i = 0; i < n; i++) {
            min_cost = min(min_cost, cost[i]);
            answer[i] = min_cost;
        }
        
        return answer;
    }
};