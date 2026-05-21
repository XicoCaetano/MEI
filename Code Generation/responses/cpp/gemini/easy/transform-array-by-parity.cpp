#include <vector>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> transformArray(vector<int> nums) {
        for (int i = 0; i < nums.size(); ++i) {
            // Replace even numbers with 0, odd numbers with 1
            if (nums[i] % 2 == 0) {
                nums[i] = 0;
            } else {
                nums[i] = 1;
            }
        }
        
        // Sort the modified array in non-decreasing order
        sort(nums.begin(), nums.end());
        
        return nums;
    }
};