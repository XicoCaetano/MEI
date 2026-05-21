#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
public:
    bool _match(const string& ans, int i, const string& s) {
        for (int j = 0; j < s.length(); ++j) {
            if (ans[i + j] != s[j]) return false;
        }
        return true;
    }

    int _lastModifiablePosition(int i, int m, const vector<bool>& modifiable) {
        for (int j = m - 1; j >= 0; --j) {
            if (modifiable[i + j]) return i + j;
        }
        return -1;
    }

    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        int len = n + m - 1;
        string ans(len, '\0');
        vector<bool> modifiable(len, true);

        // Step 1: Fill the string based on 'T' constraints
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; ++j) {
                    if (ans[i + j] != '\0' && ans[i + j] != str2[j]) {
                        return ""; // Contradiction between 'T' positions
                    }
                    ans[i + j] = str2[j];
                    modifiable[i + j] = false;
                }
            }
        }

        // Step 2: Fill remaining characters with 'a' to keep it lexicographically smallest
        for (int i = 0; i < len; ++i) {
            if (ans[i] == '\0') {
                ans[i] = 'a';
            }
        }

        // Step 3: Handle 'F' constraints greedily
        for (int i = 0; i < n; ++i) {
            if (str1[i] == 'F') {
                // If it currently matches str2, we must modify it
                while (_match(ans, i, str2)) {
                    int pos = _lastModifiablePosition(i, m, modifiable);
                    
                    if (pos == -1) return ""; // Cannot break the match

                    // Try to increment the character at the last modifiable position
                    if (ans[pos] < 'z') {
                        ans[pos]++;
                        // After changing a character, reset all following modifiable 
                        // characters to 'a' to maintain lexicographical minimality.
                        // However, we only care about positions within this window 
                        // or further right that were not fixed by a 'T'.
                        for (int k = pos + 1; k < len; ++k) {
                            if (modifiable[k]) ans[k] = 'a';
                        }
                    } else {
                        // This position is 'z' and modifiable? 
                        // This case is tricky, but logically we should try 
                        // a different position or fail. 
                        // With lowercase English, 'a' -> 'b' is usually enough.
                        return ""; 
                    }
                }
            }
        }

        // Final Verification: Changing a char for an 'F' might have violated a previous 'F'
        // Since we only ever increase characters and reset to 'a', we re-check all.
        for (int i = 0; i < n; ++i) {
            bool match = _match(ans, i, str2);
            if (str1[i] == 'T' && !match) return "";
            if (str1[i] == 'F' && match) return "";
        }

        return ans;
    }
};