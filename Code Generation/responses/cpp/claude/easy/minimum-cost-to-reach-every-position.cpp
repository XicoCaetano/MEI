#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> minCosts(vector<int> cost) {
        int n = cost.size();
        vector<int> answer(n);
        int minSoFar = cost[0];
        for (int i = 0; i < n; i++) {
            minSoFar = min(minSoFar, cost[i]);
            answer[i] = minSoFar;
        }
        return answer;
    }
};