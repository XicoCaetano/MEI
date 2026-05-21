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
    bool hasSpecialSubstring(string s, int k) {
        int n = s.length();
        
        for (int i = 0; i <= n - k; ++i) {
            char target = s[i];
            bool all_same = true;
            
            // Check if all characters in the substring are the same
            for (int j = i; j < i + k; ++j) {
                if (s[j] != target) {
                    all_same = false;
                    break;
                }
            }
            
            if (all_same) {
                // Check character before the substring
                bool left_ok = (i == 0 || s[i - 1] != target);
                // Check character after the substring
                bool right_ok = (i + k == n || s[i + k] != target);
                
                if (left_ok && right_ok) {
                    return true;
                }
            }
        }
        
        return false;
    }
};