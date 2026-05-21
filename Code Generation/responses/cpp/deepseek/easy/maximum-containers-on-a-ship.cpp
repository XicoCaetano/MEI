#include <algorithm>
using namespace std;

class Solution {
public:
    int maxContainers(int n, int w, int maxWeight) {
        int maxCells = n * n;
        int maxByWeight = maxWeight / w;
        return min(maxCells, maxByWeight);
    }
};