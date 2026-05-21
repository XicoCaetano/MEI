#include <vector>
#include <numeric>
using namespace std;

class Solution {
public:
    int minZeroArray(vector<int> nums, vector<vector<int>> queries) {
        int n = nums.size();
        int q = queries.size();
        
        auto canZero = [&](int k) -> bool {
            vector<long long> diff(n + 1, 0);
            for (int i = 0; i < k; i++) {
                int l = queries[i][0], r = queries[i][1], val = queries[i][2];
                diff[l] += val;
                diff[r + 1] -= val;
            }
            long long cur = 0;
            for (int i = 0; i < n; i++) {
                cur += diff[i];
                if (cur < nums[i]) return false;
            }
            return true;
        };
        
        if (canZero(0)) return 0;
        
        int lo = 1, hi = q, ans = -1;
        while (lo <= hi) {
            int mid = (lo + hi) / 2;
            if (canZero(mid)) {
                ans = mid;
                hi = mid - 1;
            } else {
                lo = mid + 1;
            }
        }
        return ans;
    }
};