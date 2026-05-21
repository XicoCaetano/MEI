// task_id: longest-palindrome-after-substring-concatenation-ii
// difficulty: Hard

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>
#include <numeric>
#include <queue>
#include <stack>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>

using namespace std;



// === MODEL RESPONSE ===
#include <string>
#include <vector>
#include <algorithm>
#include <functional>
#include <cstring>

using namespace std;

class Solution {
public:
    int calc(const string& s, const string& t) {
        int n = s.length(), m = t.length();
        vector<vector<int>> dp_s(n, vector<int>(n, 0));
        vector<vector<int>> dp_t(m, vector<int>(m, 0));
        
        // dp_s[i][j] = length of longest palindrome in s[i..j]
        for (int len = 1; len <= n; len++) {
            for (int i = 0; i + len <= n; i++) {
                int j = i + len - 1;
                if (len == 1) {
                    dp_s[i][j] = 1;
                } else if (len == 2) {
                    dp_s[i][j] = (s[i] == s[j]) ? 2 : 1;
                } else {
                    if (s[i] == s[j]) {
                        dp_s[i][j] = 2 + dp_s[i+1][j-1];
                    } else {
                        dp_s[i][j] = max(dp_s[i+1][j], dp_s[i][j-1]);
                    }
                }
            }
        }
        
        // dp_t[i][j] = length of longest palindrome in t[i..j]
        for (int len = 1; len <= m; len++) {
            for (int i = 0; i + len <= m; i++) {
                int j = i + len - 1;
                if (len == 1) {
                    dp_t[i][j] = 1;
                } else if (len == 2) {
                    dp_t[i][j] = (t[i] == t[j]) ? 2 : 1;
                } else {
                    if (t[i] == t[j]) {
                        dp_t[i][j] = 2 + dp_t[i+1][j-1];
                    } else {
                        dp_t[i][j] = max(dp_t[i+1][j], dp_t[i][j-1]);
                    }
                }
            }
        }
        
        int ans = 0;
        
        // Case 1: palindrome entirely in s
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                ans = max(ans, dp_s[i][j]);
            }
        }
        
        // Case 2: palindrome entirely in t
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {
                ans = max(ans, dp_t[i][j]);
            }
        }
        
        // Case 3: palindrome formed by concatenation
        // Try all pairs of substrings: s[i..j] + t[k..l]
        // We need to find the longest palindrome that can be formed
        
        // Precompute prefix and suffix palindromes
        vector<vector<bool>> is_pal_s(n, vector<bool>(n, false));
        vector<vector<bool>> is_pal_t(m, vector<bool>(m, false));
        
        // Mark palindromes in s
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                is_pal_s[i][j] = (dp_s[i][j] == j - i + 1);
            }
        }
        
        // Mark palindromes in t
        for (int i = 0; i < m; i++) {
            for (int j = i; j < m; j++) {
                is_pal_t[i][j] = (dp_t[i][j] == j - i + 1);
            }
        }
        
        // For each possible center or extended palindrome
        // Try to extend from s and t
        
        // Try all pairs of positions: one from s, one from t, and expand outward
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                // Check if s[i] == t[j], can start forming palindrome
                if (s[i] == t[j]) {
                    // Expand outward from this pair
                    int left_s = i, right_s = i;
                    int left_t = j, right_t = j;
                    int len = 2;
                    
                    // Expand while we can
                    while (left_s > 0 && right_t < m - 1 && s[left_s - 1] == t[right_t + 1]) {
                        left_s--;
                        right_t++;
                        len += 2;
                    }
                    ans = max(ans, len);
                    
                    // Now try to find longer palindromes by using palindromic substrings
                    // inside s and t
                    
                    // Try to prepend a palindrome from s before the left_s
                    if (left_s > 0) {
                        for (int k = 0; k < left_s; k++) {
                            if (is_pal_s[k][left_s - 1]) {
                                ans = max(ans, len + (left_s - k));
                            }
                        }
                    }
                    
                    // Try to append a palindrome from t after the right_t
                    if (right_t < m - 1) {
                        for (int k = right_t + 1; k < m; k++) {
                            if (is_pal_t[right_t + 1][k]) {
                                ans = max(ans, len + (k - right_t));
                            }
                        }
                    }
                }
            }
        }
        
        // Try all palindromic centers in the concatenated string
        // This is essentially looking for substrings that can be extended
        // with palindromes from either side
        
        // More exhaustive approach: try all pairs of substrings s[i..j] and t[k..l]
        // that together form a palindrome
        for (int i = 0; i < n; i++) {
            for (int j = i; j < n; j++) {
                string sub_s = s.substr(i, j - i + 1);
                for (int k = 0; k < m; k++) {
                    for (int l = k; l < m; l++) {
                        string sub_t = t.substr(k, l - k + 1);
                        string concat = sub_s + sub_t;
                        bool is_pal = true;
                        int left = 0, right = concat.length() - 1;
                        while (left < right) {
                            if (concat[left] != concat[right]) {
                                is_pal = false;
                                break;
                            }
                            left++;
                            right--;
                        }
                        if (is_pal) {
                            ans = max(ans, (int)concat.length());
                        }
                    }
                }
            }
        }
        
        return ans;
    }
    
    int longestPalindrome(string s, string t) {
        return calc(s, t);
    }
};

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.longestPalindrome("b", "aaaa") == 4));
    assert((sol.longestPalindrome("hello", "world") == 3));
    assert((sol.longestPalindrome("aaaa", "bbbb") == 4));
    assert((sol.longestPalindrome("abcde", "ecdba") == 5));
    assert((sol.longestPalindrome("noon", "moon") == 7));
    assert((sol.longestPalindrome("race", "care") == 7));
    assert((sol.longestPalindrome("a", "a") == 2));
    assert((sol.longestPalindrome("abcd", "dcba") == 8));
    assert((sol.longestPalindrome("xyz", "zyx") == 6));
    assert((sol.longestPalindrome("abc", "def") == 1));
    assert((sol.longestPalindrome("referrefer", "referref") == 16));
    assert((sol.longestPalindrome("abccba", "abcba") == 7));
    assert((sol.longestPalindrome("abcabc", "cbacba") == 12));
    assert((sol.longestPalindrome("mnopqr", "rqpomn") == 8));
    assert((sol.longestPalindrome("rotorrotor", "rotorrot") == 16));
    assert((sol.longestPalindrome("madam", "madammadam") == 15));
    assert((sol.longestPalindrome("aabbaabb", "bbaa") == 10));
    assert((sol.longestPalindrome("aaaaabbbbb", "bbbbbbaaaa") == 19));
    assert((sol.longestPalindrome("abccba", "bccbab") == 11));
    assert((sol.longestPalindrome("aabbcc", "ccbbaa") == 12));
    assert((sol.longestPalindrome("abcdef", "fedabc") == 6));
    assert((sol.longestPalindrome("xyxyxy", "yxyxyx") == 12));
    assert((sol.longestPalindrome("aba", "bab") == 5));
    assert((sol.longestPalindrome("abcdefg", "gfedcba") == 14));
    assert((sol.longestPalindrome("tatactatta", "tatattac") == 11));
    assert((sol.longestPalindrome("madam", "madam") == 10));
    assert((sol.longestPalindrome("aabaa", "bbabb") == 6));
    assert((sol.longestPalindrome("abcdef", "fedcbaghi") == 12));
    assert((sol.longestPalindrome("palindrome", "emordnilap") == 20));
    assert((sol.longestPalindrome("xyzaaayzx", "zyxxzyxzy") == 9));
    assert((sol.longestPalindrome("abcabcabc", "cbacbacba") == 18));
    assert((sol.longestPalindrome("pqr", "rqp") == 6));
    assert((sol.longestPalindrome("abcdcba", "abcdcba") == 14));
    assert((sol.longestPalindrome("deified", "deified") == 14));
    assert((sol.longestPalindrome("abracadabra", "abraccadabr") == 8));
    assert((sol.longestPalindrome("longestpalindrome", "emordnilapgnol") == 20));
    assert((sol.longestPalindrome("abcdefghijk", "kjihgfedcba") == 22));
    assert((sol.longestPalindrome("abacax", "xacaba") == 12));
    assert((sol.longestPalindrome("pqrstu", "utsrqponmlkjihgfedcba") == 12));
    assert((sol.longestPalindrome("abcdef", "gfedcbaa") == 13));
    assert((sol.longestPalindrome("civiccivic", "iviciciv") == 11));
    assert((sol.longestPalindrome("aabbccdd", "ddeeccbbaa") == 14));
    assert((sol.longestPalindrome("abcxyzdef", "fedxyzcba") == 7));
    assert((sol.longestPalindrome("civic", "civiccivic") == 15));
    assert((sol.longestPalindrome("banana", "nanaba") == 11));
    assert((sol.longestPalindrome("abacdfgdcaba", "abacdfgdcaba") == 11));
    assert((sol.longestPalindrome("tattarrattat", "tattarrattat") == 24));
    assert((sol.longestPalindrome("level", "levvel") == 7));
    assert((sol.longestPalindrome("xxyyyzzz", "zzzyyyxx") == 16));
    assert((sol.longestPalindrome("rotorrotor", "rotor") == 15));
    assert((sol.longestPalindrome("rotor", "rotator") == 7));
    assert((sol.longestPalindrome("abacaxbaca", "xacabacaba") == 13));
    assert((sol.longestPalindrome("mnopqrstu", "utsrqponmlkjihgfedcbazyxwvut") == 18));
    assert((sol.longestPalindrome("aabbccddeeffgg", "ggffeeeeddccbbaa") == 22));
    assert((sol.longestPalindrome("xyzyx", "yzyxxy") == 9));
    assert((sol.longestPalindrome("aaaaaa", "bbbbbb") == 6));
    assert((sol.longestPalindrome("abcdefg", "hijklmn") == 1));
    assert((sol.longestPalindrome("abcdef", "fedcbag") == 12));
    assert((sol.longestPalindrome("level", "leveleveleveleveleveleveleveleveleveleveleveleveleve") == 55));
    assert((sol.longestPalindrome("abcdabcd", "dcbaabcd") == 9));
    assert((sol.longestPalindrome("abcdeedcba", "fghijklkjihgf") == 13));
    assert((sol.longestPalindrome("aaaabb", "aabbaa") == 10));
    assert((sol.longestPalindrome("civic", "civic") == 10));
    assert((sol.longestPalindrome("level", "levevl") == 8));
    assert((sol.longestPalindrome("racecar", "madam") == 7));
    assert((sol.longestPalindrome("deifieddeified", "deifiededeif") == 21));
    assert((sol.longestPalindrome("noonhighnoon", "deifiedlevel") == 7));
    assert((sol.longestPalindrome("abracadabra", "aracabradab") == 7));
    assert((sol.longestPalindrome("level", "deified") == 7));
    assert((sol.longestPalindrome("mirror", "rimmom") == 9));
    assert((sol.longestPalindrome("abcdedcba", "zyxwxyzyx") == 9));
    assert((sol.longestPalindrome("pneumonoultramicroscopicsilicovolcanoconiosis", "osivicnoclovosicrepimicroscopultramaounep") == 11));
    assert((sol.longestPalindrome("xyzzyx", "abczyzyxcba") == 7));
    assert((sol.longestPalindrome("abcxyzyxcba", "xyzzyx") == 11));
    assert((sol.longestPalindrome("abcabcabc", "abcabcabc") == 3));
    assert((sol.longestPalindrome("mississippi", "ppissimms") == 13));
    assert((sol.longestPalindrome("abacaxaba", "abacaxaba") == 7));
    assert((sol.longestPalindrome("hello", "olleh") == 10));
    assert((sol.longestPalindrome("noonhighnoon", "noonlownoon") == 9));
    assert((sol.longestPalindrome("abaccadda", "addacca") == 14));
    assert((sol.longestPalindrome("refer", "repaper") == 7));
    assert((sol.longestPalindrome("mississippi", "ippississimm") == 22));
    assert((sol.longestPalindrome("abacaba", "bdcabdc") == 9));
    assert((sol.longestPalindrome("mississippi", "noon") == 7));
    assert((sol.longestPalindrome("noon", "noonnoonnoonnoon") == 20));
    assert((sol.longestPalindrome("abracadabra", "abacabadabrac") == 11));
    assert((sol.longestPalindrome("abcd", "abcdabcd") == 3));
    assert((sol.longestPalindrome("abc", "mnopqr") == 1));
    assert((sol.longestPalindrome("abccba", "xyzyx") == 6));
    assert((sol.longestPalindrome("zzzzzz", "zzzzzz") == 12));
    assert((sol.longestPalindrome("amanaplanacanalpanama", "amanaP lanac a nalp a namA") == 21));
    assert((sol.longestPalindrome("noonnoon", "moonmoon") == 8));
    assert((sol.longestPalindrome("noonhighnoon", "noon") == 9));
    assert((sol.longestPalindrome("xyzz", "zzxy") == 4));
    assert((sol.longestPalindrome("racecar", "civic") == 7));
    assert((sol.longestPalindrome("mnopqr", "rqponm") == 12));
    assert((sol.longestPalindrome("levellevellevel", "levevlevevlevevl") == 18));
    assert((sol.longestPalindrome("mammam", "mammam") == 12));
    assert((sol.longestPalindrome("kayak", "yakayk") == 7));
    assert((sol.longestPalindrome("radar", "radar") == 10));
    assert((sol.longestPalindrome("neveroddoreven", "levelmadamrotor") == 14));
    assert((sol.longestPalindrome("madam", "refer") == 5));
    assert((sol.longestPalindrome("hello", "ollehworld") == 10));
    assert((sol.longestPalindrome("xyzuvw", "vwxyz") == 3));
    assert((sol.longestPalindrome("zzzzzzzzzz", "zzzzzzzzzz") == 20));
    assert((sol.longestPalindrome("zzzzz", "zzzz") == 9));
    assert((sol.longestPalindrome("banana", "ananab") == 12));
    assert((sol.longestPalindrome("abacabadabacaba", "abacabadabacaba") == 30));
    assert((sol.longestPalindrome("rotor", "rotorrotorrotor") == 20));
    assert((sol.longestPalindrome("aabbccddeeff", "ffeeddccbbaa") == 24));
    assert((sol.longestPalindrome("abracadabra", "arbadacarba") == 22));
    assert((sol.longestPalindrome("aaaabbbb", "bbbbcccc") == 8));
    assert((sol.longestPalindrome("abacdfgdcaba", "abacdgfdcaba") == 24));
    assert((sol.longestPalindrome("repaper", "repaper") == 14));
    assert((sol.longestPalindrome("aabbccddeeffgg", "ggffeeddcbaabbccddeeffgg") == 18));
    assert((sol.longestPalindrome("racecar", "carrear") == 7));
    assert((sol.longestPalindrome("abcabcabcabc", "cbacbacbacba") == 24));
    assert((sol.longestPalindrome("racecar", "racecar") == 14));
    assert((sol.longestPalindrome("aabbccdd", "dccbbaaa") == 15));
    assert((sol.longestPalindrome("abcdefgfedcba", "ghijklimno") == 13));
    assert((sol.longestPalindrome("aabbccddeeaabbccddeeaabb", "ddeeaabbccddeeaabb") == 6));
    assert((sol.longestPalindrome("rotor", "rotor") == 10));

    cout << "All tests passed for longest-palindrome-after-substring-concatenation-ii" << endl;
    return 0;
}
