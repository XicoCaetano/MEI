#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution {
public:
    /**
     * Problem Analysis:
     * - You start at position n.
     * - To move to position i (where i < current_position), you pay cost[i].
     * - To move to position i (where i > current_position), it is free.
     * 
     * Logic:
     * To reach position i with minimum cost, you must have swapped with some 
     * person j where j <= i at some point. 
     * Once you are at position j, moving to any position i >= j is free.
     * Therefore, the minimum cost to reach position i is the minimum cost 
     * among all people at positions 0, 1, ..., i.
     */
    vector<int> minCosts(vector<int> cost) {
        int n = cost.size();
        vector<int> answer(n);
        
        if (n == 0) return answer;

        int currentMin = INT_MAX;
        for (int i = 0; i < n; ++i) {
            // The cost to reach position i is the minimum cost found in the 
            // range [0...i], because once you pay for a position j <= i, 
            // you can move to i for free.
            currentMin = min(currentMin, cost[i]);
            answer[i] = currentMin;
        }
        
        return answer;
    }
};