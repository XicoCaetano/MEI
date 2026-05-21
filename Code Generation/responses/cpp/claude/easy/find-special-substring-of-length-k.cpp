#include <string>
using namespace std;

class Solution {
public:
    bool hasSpecialSubstring(string s, int k) {
        int n = s.size();
        int i = 0;
        while (i < n) {
            char c = s[i];
            int j = i;
            while (j < n && s[j] == c) j++;
            int len = j - i;
            if (len == k) return true;
            i = j;
        }
        return false;
    }
};