#include <string>
#include <vector>
#include <unordered_map>
#include <functional>
#include <regex>

using namespace std;

class Solution {
public:
    string applySubstitutions(vector<vector<string>> replacements, string text) {
        unordered_map<string, string> dict;
        for (const auto& pair : replacements) {
            dict[pair[0]] = pair[1];
        }
        
        function<string(string)> expand = [&](string s) -> string {
            regex pattern("%([A-Z])%");
            smatch match;
            string result = s;
            
            while (regex_search(result, match, pattern)) {
                string key = match[1].str();
                string replacement = dict[key];
                result = regex_replace(result, regex("%" + key + "%"), expand(replacement));
            }
            
            return result;
        };
        
        return expand(text);
    }
};