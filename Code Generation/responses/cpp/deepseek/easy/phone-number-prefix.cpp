#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class Solution {
public:
    bool phonePrefix(vector<string> numbers) {
        // Sort the numbers lexicographically
        sort(numbers.begin(), numbers.end());
        
        // Check each adjacent pair
        for (int i = 0; i < numbers.size() - 1; i++) {
            // If the next number starts with the current number, current is a prefix
            if (numbers[i + 1].find(numbers[i]) == 0) {
                return false;
            }
        }
        
        return true;
    }
};