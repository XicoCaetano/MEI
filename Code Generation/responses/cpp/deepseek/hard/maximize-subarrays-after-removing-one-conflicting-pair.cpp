#include <vector>
#include <algorithm>
#include <functional>
#include <set>
#include <map>
#include <climits>
using namespace std;

class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        vector<vector<int>> pos(n + 1);
        vector<int> L(n + 2, 0), R(n + 2, n + 1);
        
        for (auto& p : conflictingPairs) {
            int a = p[0], b = p[1];
            if (a > b) swap(a, b);
            pos[a].push_back(b);
        }
        
        vector<long long> total(n + 2, 0);
        long long res = 0;
        int maxL = 0;
        
        for (int i = 1; i <= n; ++i) {
            for (int b : pos[i]) {
                maxL = max(maxL, b);
            }
            long long cnt = (long long)(i - 1) * (n - i + 1);
            total[i] = cnt;
            res += total[i];
        }
        
        vector<int> firstOccur(n + 2, INT_MAX);
        vector<int> lastOccur(n + 2, 0);
        
        for (int i = 1; i <= n; ++i) {
            for (int b : pos[i]) {
                firstOccur[b] = min(firstOccur[b], i);
                lastOccur[b] = max(lastOccur[b], i);
            }
        }
        
        long long best = 0;
        
        for (int i = 0; i < conflictingPairs.size(); ++i) {
            int a = conflictingPairs[i][0], b = conflictingPairs[i][1];
            if (a > b) swap(a, b);
            long long val = 0;
            
            if (firstOccur[b] == a && lastOccur[b] == a) {
                int left = a;
                int right = b;
                int prev = 0;
                for (int j = a + 1; j < b; ++j) {
                    if (!pos[j].empty()) {
                        prev = j;
                    }
                }
                int nextOccur = INT_MAX;
                for (int j = b + 1; j <= n; ++j) {
                    if (!pos[j].empty()) {
                        nextOccur = j;
                        break;
                    }
                }
                val = (long long)(a - prev) * (nextOccur - b);
            }
            best = max(best, val);
        }
        
        return res + best;
    }
};