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

class Solution {
public:
    bool phonePrefix(vector<string> numbers) {
        // Sort strings lexicographically. 
        // If a string A is a prefix of string B, A will appear immediately before B 
        // or before some other strings that also share the prefix A.
        sort(numbers.begin(), numbers.end());

        for (int i = 0; i < (int)numbers.size() - 1; ++i) {
            const string& current = numbers[i];
            const string& next = numbers[i + 1];

            // Check if current is a prefix of next
            if (next.size() >= current.size()) {
                if (next.substr(0, current.size()) == current) {
                    return false;
                }
            }
        }

        return true;
    }
};