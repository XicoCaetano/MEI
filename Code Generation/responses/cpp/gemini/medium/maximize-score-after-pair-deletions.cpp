#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
    int memo[2005][2005];
    
    int solve(int i, int j, int target, const vector<int>& nums) {
        if (i >= j) return 0;
        if (memo[i][j] != -1) return memo[i][j];
        
        int res = 0;
        
        // Option 1: Remove first two
        if (i + 1 <= j && nums[i] + nums[i+1] == target) {
            res = max(res, 1 + solve(i + 2, j, target, nums));
        }
        
        // Option 2: Remove last two
        if (j - 1 >= i && nums[j] + nums[j-1] == target) {
            res = max(res, 1 + solve(i, j - 2, target, nums));
        }
        
        // Option 3: Remove first and last
        if (i < j && nums[i] + nums[j] == target) {
            res = max(res, 1 + solve(i + 1, j - 1, target, nums));
        }
        
        return memo[i][j] = res;
    }

public:
    long long maxScore(vector<int> nums) {
        int n = nums.size();
        if (n < 2) return 0;

        // Based on the problem description "repeatedly perform... while array has more than two",
        // and the examples provided, it appears the user is asking for the maximum score 
        // from a SINGLE operation or the cumulative score of consistent operations.
        // However, the standard version of this problem (often seen in competitive programming)
        // requires all operations in a sequence to result in the SAME sum.
        
        // If the rules allow ANY sum at each step until n < 2:
        // The maximum score is simply the sum of the largest possible pairs.
        // But the examples show only ONE operation being performed because the remaining 
        // array size becomes 1 or 2, and the rule says "while more than 2 elements".
        
        // Re-evaluating Example 1: [2,4,1]. 3 elements. One operation makes it 1 element.
        // Possible: (2+4)=6, (4+1)=5, (2+1)=3. Max is 6.
        // Example 2: [5,-1,4,2]. 4 elements. One operation makes it 2 elements.
        // Process stops because 2 is not "more than 2". Max is 7.
        
        // Given the constraints and logic, this is a Dynamic Programming problem 
        // where we pick a target sum from the first possible operation and see how far we can go.
        
        auto get_max_for_target = [&](int target) {
            for (int i = 0; i <= n; i++) {
                for (int j = 0; j <= n; j++) {
                    memo[i][j] = -1;
                }
            }
            return solve(0, n - 1, target, nums);
        };

        // There are only 3 possible values for the first operation's sum
        int t1 = nums[0] + nums[1];
        int t2 = nums[n-2] + nums[n-1];
        int t3 = nums[0] + nums[n-1];
        
        // If the problem implies we want the sum of the values:
        // For N <= 2000, we use DP. For N up to 10^5, this logic only holds if we only 
        // perform ONE operation as the examples suggest.
        
        if (n > 2000) {
            // If N is large, the "while more than 2" and the examples suggest 
            // a single optimal pair if the sequence isn't forced to a target, 
            // or a greedy approach. Given the examples:
            return max({(long long)nums[0] + nums[1], 
                        (long long)nums[n-2] + nums[n-1], 
                        (long long)nums[0] + nums[n-1]});
        }

        // Standard DP approach for "Same Sum" variation
        long long ans = 0;
        ans = max(ans, (long long)get_max_for_target(t1));
        ans = max(ans, (long long)get_max_for_target(t2));
        ans = max(ans, (long long)get_max_for_target(t3));
        
        // If the problem meant "Total value" and not "Count of operations":
        // The logic above returns count. To return sum:
        return max({(long long)t1, (long long)t2, (long long)t3});
    }
};