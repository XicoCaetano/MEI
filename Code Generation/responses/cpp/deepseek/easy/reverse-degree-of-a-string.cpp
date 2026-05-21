#include <string>
using namespace std;

class Solution {
public:
    int reverseDegree(string s) {
        int total = 0;
        int n = s.length();
        
        for (int i = 0; i < n; i++) {
            // Position in string (1-indexed)
            int stringIndex = i + 1;
            
            // Position in reversed alphabet: 'a' = 26, 'b' = 25, ..., 'z' = 1
            int reverseAlphabetIndex = 26 - (s[i] - 'a');
            
            total += stringIndex * reverseAlphabetIndex;
        }
        
        return total;
    }
};