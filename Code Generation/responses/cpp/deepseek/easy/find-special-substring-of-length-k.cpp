#include <string>
using namespace std;

class Solution {
public:
    bool hasSpecialSubstring(string s, int k) {
        int n = s.length();
        
        for (int i = 0; i <= n - k; i++) {
            // Check if substring of length k starting at i has all same characters
            bool allSame = true;
            for (int j = i + 1; j < i + k; j++) {
                if (s[j] != s[i]) {
                    allSame = false;
                    break;
                }
            }
            
            if (allSame) {
                // Check character before substring (if exists)
                bool beforeValid = (i == 0) || (s[i - 1] != s[i]);
                
                // Check character after substring (if exists)
                bool afterValid = (i + k == n) || (s[i + k] != s[i]);
                
                if (beforeValid && afterValid) {
                    return true;
                }
            }
        }
        
        return false;
    }
};