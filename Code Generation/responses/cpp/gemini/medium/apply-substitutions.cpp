#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution {
public:
    /**
     * Resolves a key by recursively replacing any placeholders within its mapped value.
     * Since there are no cyclic dependencies, this process will eventually terminate.
     */
    string resolve(const string& key, unordered_map<string, string>& mapping, unordered_map<string, string>& memo) {
        if (memo.count(key)) {
            return memo[key];
        }

        string rawValue = mapping[key];
        string result = "";
        
        for (int i = 0; i < rawValue.length(); ++i) {
            if (rawValue[i] == '%') {
                // Find the closing '%'
                size_t nextPos = rawValue.find('%', i + 1);
                string innerKey = rawValue.substr(i + 1, nextPos - i - 1);
                result += resolve(innerKey, mapping, memo);
                i = nextPos; // Move index to the closing '%'
            } else {
                result += rawValue[i];
            }
        }

        return memo[key] = result;
    }

    string applySubstitutions(vector<vector<string>> replacements, string text) {
        unordered_map<string, string> mapping;
        unordered_map<string, string> memo;

        for (const auto& pair : replacements) {
            mapping[pair[0]] = pair[1];
        }

        string finalResult = "";
        for (int i = 0; i < text.length(); ++i) {
            if (text[i] == '%') {
                size_t nextPos = text.find('%', i + 1);
                string key = text.substr(i + 1, nextPos - i - 1);
                finalResult += resolve(key, mapping, memo);
                i = nextPos;
            } else {
                finalResult += text[i];
            }
        }

        return finalResult;
    }
};