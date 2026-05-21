#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxStudentsOnBench(vector<vector<int>> students) {
        unordered_map<int, unordered_set<int>> bench;
        for (auto& s : students)
            bench[s[1]].insert(s[0]);
        int res = 0;
        for (auto& [b, st] : bench)
            res = max(res, (int)st.size());
        return res;
    }
};