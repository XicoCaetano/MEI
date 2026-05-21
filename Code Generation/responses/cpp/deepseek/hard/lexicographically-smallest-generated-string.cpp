#include <string>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    string generateString(string str1, string str2) {
        int n = str1.length();
        int m = str2.length();
        int len = n + m - 1;
        
        // modifiable[i] = true if position i can be freely chosen
        vector<bool> modifiable(len, true);
        
        // First pass: enforce T constraints
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                // Check if we can place str2 starting at position i
                for (int j = 0; j < m; j++) {
                    modifiable[i + j] = false;
                }
            }
        }
        
        // Second pass: check F constraints and potentially fix positions
        vector<char> ans(len, ' ');
        
        // Try to build the smallest possible string
        for (int i = 0; i < len; i++) {
            if (ans[i] == ' ') {
                ans[i] = 'a';
            }
        }
        
        // Enforce T constraints
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    ans[i + j] = str2[j];
                }
            }
        }
        
        // Check for conflicts in T positions
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] != str2[j]) {
                        return "";
                    }
                }
            }
        }
        
        // Handle F constraints: ensure no unwanted matches
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'F') {
                // Check if current ans would match str2 at position i
                bool wouldMatch = true;
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] != str2[j]) {
                        wouldMatch = false;
                        break;
                    }
                }
                
                if (wouldMatch) {
                    // Need to modify at least one position to break the match
                    // Find the rightmost modifiable position in this window
                    int modIndex = -1;
                    for (int j = m - 1; j >= 0; j--) {
                        if (modifiable[i + j] && ans[i + j] == str2[j]) {
                            modIndex = i + j;
                            break;
                        }
                    }
                    
                    if (modIndex == -1) {
                        return "";
                    }
                    
                    // Change this position to the next character
                    if (ans[modIndex] < 'z') {
                        ans[modIndex]++;
                        // After incrementing, try to make the rest minimal
                        for (int k = modIndex + 1; k < len; k++) {
                            if (modifiable[k]) {
                                ans[k] = 'a';
                            }
                        }
                    } else {
                        return "";
                    }
                    
                    // Re-check this F constraint from beginning
                    i--;
                }
            }
        }
        
        // Final verification
        for (int i = 0; i < n; i++) {
            if (str1[i] == 'T') {
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] != str2[j]) {
                        return "";
                    }
                }
            } else { // 'F'
                bool matches = true;
                for (int j = 0; j < m; j++) {
                    if (ans[i + j] != str2[j]) {
                        matches = false;
                        break;
                    }
                }
                if (matches) {
                    return "";
                }
            }
        }
        
        string result(ans.begin(), ans.end());
        return result;
    }
};