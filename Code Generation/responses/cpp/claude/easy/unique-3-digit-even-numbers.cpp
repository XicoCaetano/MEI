#include <vector>
#include <set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int totalNumbers(vector<int> digits) {
        set<int> result;
        sort(digits.begin(), digits.end());
        int n = digits.size();
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                for (int k = 0; k < n; k++) {
                    if (i == j || i == k || j == k) continue;
                    if (digits[i] == 0) continue;
                    if (digits[k] % 2 != 0) continue;
                    result.insert(digits[i]*100 + digits[j]*10 + digits[k]);
                }
        return result.size();
    }
};