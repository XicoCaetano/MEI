#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int totalNumbers(vector<int> digits) {
        unordered_set<int> resultSet;
        int n = digits.size();
        
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                for (int k = 0; k < n; ++k) {
                    if (i != j && i != k && j != k) {
                        int num = digits[i] * 100 + digits[j] * 10 + digits[k];
                        if (num >= 100 && num % 2 == 0) {
                            resultSet.insert(num);
                        }
                    }
                }
            }
        }
        
        return resultSet.size();
    }
};