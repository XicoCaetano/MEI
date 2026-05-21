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
    /**
     * Calculates the maximum number of containers that can be loaded onto an n x n deck.
     * Each container weighs 'w', and the total weight cannot exceed 'maxWeight'.
     */
    int maxContainers(int n, int w, int maxWeight) {
        // Total available cells on the n x n deck
        long long totalCells = (long long)n * n;
        
        // Maximum number of containers allowed by weight capacity
        // Note: Using long long for maxWeight to avoid overflow during calculation, 
        // though integer division handles the floor naturally.
        long long maxPossibleByWeight = (long long)maxWeight / w;
        
        // The actual number of containers is limited by both the physical space 
        // (totalCells) and the ship's weight capacity (maxPossibleByWeight).
        long long result = min(totalCells, maxPossibleByWeight);
        
        // Since n <= 1000 and maxWeight <= 10^9, the result fits in a standard int.
        return (int)result;
    }
};