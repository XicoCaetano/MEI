#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> transformArray(vector<int> nums) {
        for (auto& n : nums) n = n % 2;
        sort(nums.begin(), nums.end());
        return nums;
    }
};