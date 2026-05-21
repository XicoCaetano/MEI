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


class Solution {
public:
    int calc(const string& s, const string& t) {
        int n = (int)s.size(), m = (int)t.size();
        // f[i+1][j] = length of common substring ending at s[i] starting at t[j]
        vector<vector<int>> f(n + 1, vector<int>(m + 1, 0));
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                if (s[i] == t[j]) {
                    f[i + 1][j] = f[i][j + 1] + 1;
                }
            }
        }
        vector<int> mx(n + 1, 0);
        for (int i = 0; i <= n; ++i) {
            int best = 0;
            for (int j = 0; j <= m; ++j) best = max(best, f[i][j]);
            mx[i] = best;
        }
        int ans = 0;
        for (int v : mx) ans = max(ans, v);
        ans *= 2;
        for (int i = 0; i < 2 * n - 1; ++i) {
            int l = i / 2;
            int r = (i + 1) / 2;
            while (l >= 0 && r < n && s[l] == s[r]) { --l; ++r; }
            if (l + 1 <= r - 1) {
                ans = max(ans, (r - l - 1) + mx[l + 1] * 2);
            }
        }
        return ans;
    }
    int longestPalindrome(string s, string t) {
        string sr(s.rbegin(), s.rend());
        string tr(t.rbegin(), t.rend());
        return max(calc(s, t), calc(tr, sr));
    }
};

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
