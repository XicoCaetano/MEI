#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution {
public:
    string applySubstitutions(vector<vector<string>> replacements, string text) {
        unordered_map<string, string> mp;
        for (auto& r : replacements) mp[r[0]] = r[1];
        
        function<string(const string&)> resolve = [&](const string& s) -> string {
            string result;
            int i = 0;
            while (i < s.size()) {
                if (s[i] == '%') {
                    int j = s.find('%', i + 1);
                    string key = s.substr(i + 1, j - i - 1);
                    result += resolve(mp[key]);
                    i = j + 1;
                } else {
                    result += s[i++];
                }
            }
            return result;
        };
        
        return resolve(text);
    }
};