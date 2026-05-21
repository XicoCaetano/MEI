#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool phonePrefix(vector<string> numbers) {
        sort(numbers.begin(), numbers.end());
        for (int i = 0; i < (int)numbers.size() - 1; i++) {
            if (numbers[i+1].substr(0, numbers[i].size()) == numbers[i])
                return false;
        }
        return true;
    }
};