#include <vector>
#include <set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int totalNumbers(vector<int> digits) {
        int n = digits.size();
        set<int> uniqueEvenNumbers;

        // Since the maximum size of digits is 10, O(N^3) is very efficient.
        // We use nested loops to pick three distinct indices i, j, k.
        for (int i = 0; i < n; ++i) {
            // First digit (hundreds place) cannot be zero.
            if (digits[i] == 0) continue;

            for (int j = 0; j < n; ++j) {
                if (j == i) continue;

                for (int k = 0; k < n; ++k) {
                    if (k == i || k == j) continue;

                    // Last digit (units place) must be even.
                    if (digits[k] % 2 == 0) {
                        int number = digits[i] * 100 + digits[j] * 10 + digits[k];
                        uniqueEvenNumbers.insert(number);
                    }
                }
            }
        }

        return uniqueEvenNumbers.size();
    }
};