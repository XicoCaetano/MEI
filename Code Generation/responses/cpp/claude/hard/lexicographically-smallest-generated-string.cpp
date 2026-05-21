#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool _match(const string& ans, int i, const string& s) {
        for (int j = 0; j < (int)s.size(); j++) {
            if (ans[i + j] != s[j]) return false;
        }
        return true;
    }

    int _lastModifiablePosition(int i, int m, const vector<bool>& modifiable) {
        for (int j = m - 1; j >= 0; j--) {
            if (modifiable[i + j]) return i + j;
        }
        return -1;
    }

    string generateString(string str1, string str2) {
        int n = str1.size(), m = str2.size();
        int len = n + m - 1;
        string ans(len, 'a');
        vector<bool> modifiable(len, true);

        // First pass: place str2 at all 'T' positions
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    if (modifiable[i + j] && ans[i + j] != str2[j]) {
                        ans[i + j] = str2[j];
                    } else if (!modifiable[i + j] && ans[i + j] != str2[j]) {
                        return "";
                    }
                }
                // Mark these positions as fixed
                for (int j = 0; j < m; j++) {
                    modifiable[i + j] = false;
                    ans[i + j] = str2[j];
                }
            }
        }

        // Second pass: ensure 'F' positions don't match str2
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {
                if (_match(ans, i, str2)) {
                    // Need to make it not match - find last modifiable position in range
                    int pos = _lastModifiablePosition(i, m, modifiable);
                    if (pos == -1) return "";
                    // Change ans[pos] to something != str2[pos - i]
                    // To keep lexicographically smallest, use 'a' if str2[pos-i] != 'a', else 'b'
                    char needed = (str2[pos - i] != 'a') ? 'a' : 'b';
                    ans[pos] = needed;
                    modifiable[pos] = false;
                }
            }
        }

        // Final verification
        for (int i = 0; i < n; i++) {
            bool matches = _match(ans, i, str2);
            if (str1[i] == 'T' && !matches) return "";
            if (str1[i] == 'F' && matches) return "";
        }

        return ans;
    }
};