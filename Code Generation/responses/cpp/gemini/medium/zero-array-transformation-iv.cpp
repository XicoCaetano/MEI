#include <vector>
#include <numeric>

using namespace std;

class Solution {
public:
    /**
     * Checks if the first k queries can transform nums into a Zero Array.
     * We use a difference array (prefix sums) to calculate the total reduction 
     * available at each index efficiently in O(n) time.
     */
    bool check(int k, const vector<int>& nums, const vector<vector<int>>& queries) {
        int n = nums.size();
        if (k == 0) {
            for (int x : nums) if (x > 0) return false;
            return true;
        }

        // diff[i] stores the net change at index i relative to i-1
        vector<long long> diff(n + 1, 0);
        for (int i = 0; i < k; ++i) {
            int l = queries[i][0];
            int r = queries[i][1];
            int val = queries[i][2];
            diff[l] += val;
            if (r + 1 < n) {
                diff[r + 1] -= val;
            }
        }

        long long current_reduction = 0;
        for (int i = 0; i < n; ++i) {
            current_reduction += diff[i];
            // If the total reduction possible at index i is less than the initial value,
            // the first k queries are insufficient.
            if (current_reduction < (long long)nums[i]) {
                return false;
            }
        }
        return true;
    }

    int minZeroArray(vector<int> nums, vector<vector<int>> queries) {
        int n = nums.size();
        int q = queries.size();

        // Binary search for the minimum k in the range [0, q]
        int low = 0, high = q;
        int ans = -1;

        while (low <= high) {
            int mid = low + (high - low) / 2;
            if (check(mid, nums, queries)) {
                ans = mid;
                high = mid - 1; // Try to find a smaller k
            } else {
                low = mid + 1; // Need more queries
            }
        }

        return ans;
    }
};