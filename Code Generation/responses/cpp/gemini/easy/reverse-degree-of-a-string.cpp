#include <string>

using namespace std;

class Solution {
public:
    /**
     * Calculates the reverse degree of a string s based on the 
     * character's reversed alphabet position and its 1-indexed string position.
     */
    int reverseDegree(string s) {
        int totalDegree = 0;
        
        for (int i = 0; i < s.length(); ++i) {
            // Index in string (1-indexed)
            int stringPosition = i + 1;
            
            // Index in reversed alphabet: 'a'=26, 'b'=25, ..., 'z'=1
            // Formula: 26 - (s[i] - 'a')
            int alphabetPosition = 26 - (s[i] - 'a');
            
            totalDegree += (alphabetPosition * stringPosition);
        }
        
        return totalDegree;
    }
};