// task_id: unique-3-digit-even-numbers
// difficulty: Easy

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>
#include <numeric>
#include <queue>
#include <stack>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>

using namespace std;



// === MODEL RESPONSE ===
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 0));
    assert((sol.totalNumbers(vector<int>{8, 8, 8, 8, 8, 8, 8, 8, 8, 8}) == 1));
    assert((sol.totalNumbers(vector<int>{6, 6, 6}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 3, 5}) == 0));
    assert((sol.totalNumbers(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 0, 2, 3, 5, 7, 9}) == 55));
    assert((sol.totalNumbers(vector<int>{9, 9, 9, 9, 9, 9, 9, 9, 9, 9}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}) == 328));
    assert((sol.totalNumbers(vector<int>{0, 0, 0}) == 0));
    assert((sol.totalNumbers(vector<int>{2, 0, 0, 2}) == 3));
    assert((sol.totalNumbers(vector<int>{1, 2, 3}) == 2));
    assert((sol.totalNumbers(vector<int>{2, 2, 2, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{2, 1, 3, 4, 2, 4, 2, 4, 2, 2}) == 28));
    assert((sol.totalNumbers(vector<int>{2, 2, 0, 0, 2, 2}) == 4));
    assert((sol.totalNumbers(vector<int>{0, 2, 2}) == 2));
    assert((sol.totalNumbers(vector<int>{0, 1, 3, 5, 7, 9}) == 20));
    assert((sol.totalNumbers(vector<int>{8, 6, 8, 6, 8, 6, 8, 6, 8, 6}) == 8));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0}) == 48));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 0}) == 1));
    assert((sol.totalNumbers(vector<int>{8, 0, 7, 4, 9, 3, 0, 3, 0, 9}) == 63));
    assert((sol.totalNumbers(vector<int>{1, 0, 1, 0, 1, 0}) == 2));
    assert((sol.totalNumbers(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}) == 48));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == 328));
    assert((sol.totalNumbers(vector<int>{1, 1, 2, 2, 3, 3}) == 8));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4}) == 12));
    assert((sol.totalNumbers(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}) == 328));
    assert((sol.totalNumbers(vector<int>{1, 0, 0, 2}) == 5));
    assert((sol.totalNumbers(vector<int>{0, 0, 2, 2, 4, 4, 6, 6, 8, 8}) == 96));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 3}) == 1));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 1, 1, 1, 2, 2, 2}) == 12));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0}) == 337));
    assert((sol.totalNumbers(vector<int>{0, 2, 4, 6, 8, 0, 2, 4, 6, 8, 0, 2, 4, 6}) == 99));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 2, 2, 2, 2}) == 4));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0}) == 446));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 0}) == 260));
    assert((sol.totalNumbers(vector<int>{9, 9, 9, 9, 9, 9, 9, 9, 9, 0}) == 1));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0}) == 337));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 2, 3, 4, 5}) == 63));
    assert((sol.totalNumbers(vector<int>{9, 9, 9, 9, 9, 9, 8, 8, 8, 8}) == 4));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4}) == 24));
    assert((sol.totalNumbers(vector<int>{1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 1}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 2, 2, 3, 4, 4, 5, 6, 7, 8}) == 202));
    assert((sol.totalNumbers(vector<int>{0, 2, 4, 6, 8, 0, 2, 4, 6, 8, 0, 2}) == 97));
    assert((sol.totalNumbers(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 0}) == 1));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 1, 1, 1, 1, 2, 2}) == 11));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 0));
    assert((sol.totalNumbers(vector<int>{5, 5, 5, 5, 7, 7, 7, 7, 9, 9}) == 0));
    assert((sol.totalNumbers(vector<int>{0, 2, 4, 6, 8, 0, 2, 4, 6, 8}) == 96));
    assert((sol.totalNumbers(vector<int>{0, 1, 1, 2, 2, 3, 3, 4, 4, 5}) == 80));
    assert((sol.totalNumbers(vector<int>{1, 3, 5, 7, 9, 1, 3, 5, 7, 9}) == 0));
    assert((sol.totalNumbers(vector<int>{0, 0, 1, 1, 2, 2, 3, 3, 4, 4}) == 58));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 2, 2, 2, 2, 3, 3}) == 9));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0, 1, 3, 5, 7, 9, 2}) == 349));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 1, 3, 5, 7, 9, 0}) == 328));
    assert((sol.totalNumbers(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 9, 9}) == 228));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6}) == 60));
    assert((sol.totalNumbers(vector<int>{0, 0, 1, 1, 2, 2, 3, 3, 4, 4}) == 58));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4}) == 32));
    assert((sol.totalNumbers(vector<int>{8, 8, 8, 8, 8, 8, 8, 8, 8, 8}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0}) == 337));
    assert((sol.totalNumbers(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 9}) == 0));
    assert((sol.totalNumbers(vector<int>{9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0}) == 337));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0, 2, 4, 6, 8, 0}) == 96));
    assert((sol.totalNumbers(vector<int>{1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 1, 3}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1, 2, 3, 4}) == 380));
    assert((sol.totalNumbers(vector<int>{0, 2, 4, 6, 8, 2, 4, 6, 8, 0}) == 96));
    assert((sol.totalNumbers(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 0}) == 1));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9}) == 224));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0, 0, 0, 0, 0, 0}) == 52));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0, 1, 3, 5, 7, 9}) == 328));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 3}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 2}) == 349));
    assert((sol.totalNumbers(vector<int>{7, 7, 7, 7, 7, 7, 7, 7, 7, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 0}) == 3));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 0, 1, 1, 1, 2, 2}) == 11));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0}) == 328));
    assert((sol.totalNumbers(vector<int>{1, 3, 5, 7, 9, 1, 3, 5, 7, 9}) == 0));
    assert((sol.totalNumbers(vector<int>{0, 2, 4, 6, 8, 1, 3, 5, 7, 9}) == 328));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 3, 5, 7, 9, 1, 3, 5, 7, 9, 9}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 9}) == 228));
    assert((sol.totalNumbers(vector<int>{2, 2, 4, 4, 6, 6, 8, 8, 0, 0}) == 96));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 1, 1, 1, 2, 2, 2}) == 12));
    assert((sol.totalNumbers(vector<int>{7, 7, 7, 8, 8, 8, 9, 9, 9, 0}) == 21));
    assert((sol.totalNumbers(vector<int>{1, 3, 5, 7, 9, 0, 2, 4, 6, 8}) == 328));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 1}) == 333));
    assert((sol.totalNumbers(vector<int>{0, 2, 4, 6, 8, 0, 2, 4, 6, 8}) == 96));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0, 2, 4, 6, 8, 0}) == 96));
    assert((sol.totalNumbers(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}) == 48));
    assert((sol.totalNumbers(vector<int>{9, 0, 1, 2, 3, 4, 5, 6, 7, 8}) == 328));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0, 0, 0, 1, 3, 5}) == 193));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 0, 2, 4, 6, 8, 0, 2, 4}) == 98));
    assert((sol.totalNumbers(vector<int>{1, 0, 1, 0, 1, 0, 1, 0, 1, 0}) == 2));
    assert((sol.totalNumbers(vector<int>{1, 2, 2, 3, 3, 3, 4, 5, 6, 6}) == 87));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 2, 2, 2, 3, 3, 3, 4}) == 24));
    assert((sol.totalNumbers(vector<int>{2, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 3, 5, 7, 9, 2, 4, 6, 8, 0}) == 328));
    assert((sol.totalNumbers(vector<int>{2, 2, 4, 4, 6, 6, 8, 8, 0, 0}) == 96));
    assert((sol.totalNumbers(vector<int>{1, 2, 2, 3, 3, 4, 4, 5, 5, 6}) == 90));
    assert((sol.totalNumbers(vector<int>{9, 9, 8, 8, 7, 7, 6, 6, 5, 5}) == 48));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 2, 2, 2, 2, 3, 3}) == 9));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0, 0}) == 337));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0}) == 337));
    assert((sol.totalNumbers(vector<int>{7, 7, 8, 8, 9, 9, 0, 0}) == 23));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 3, 4, 4, 5, 6, 7, 8}) == 271));
    assert((sol.totalNumbers(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == 0));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 2, 2}) == 3));
    assert((sol.totalNumbers(vector<int>{9, 9, 9, 8, 8, 8, 7, 7, 7, 6, 6, 6}) == 32));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 1, 3}) == 4));
    assert((sol.totalNumbers(vector<int>{1, 1, 1, 1, 1, 2, 2, 2, 2, 2}) == 4));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1}) == 228));
    assert((sol.totalNumbers(vector<int>{2, 2, 2, 2, 2, 2, 2, 2, 2, 2}) == 1));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}) == 1));
    assert((sol.totalNumbers(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 1}) == 1));
    assert((sol.totalNumbers(vector<int>{1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 6}) == 102));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 3}) == 232));
    assert((sol.totalNumbers(vector<int>{2, 4, 6, 8, 2, 4, 6, 8, 0, 0}) == 96));
    assert((sol.totalNumbers(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 0, 0}) == 337));
    assert((sol.totalNumbers(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9}) == 328));
    assert((sol.totalNumbers(vector<int>{0, 1, 1, 1, 2, 2, 2, 3, 3, 3}) == 21));
    assert((sol.totalNumbers(vector<int>{7, 8, 9, 0, 2, 4, 6, 8, 0, 2}) == 166));
    assert((sol.totalNumbers(vector<int>{0, 0, 2, 2, 4, 4, 6, 6, 8, 8}) == 96));

    cout << "All tests passed for unique-3-digit-even-numbers" << endl;
    return 0;
}
