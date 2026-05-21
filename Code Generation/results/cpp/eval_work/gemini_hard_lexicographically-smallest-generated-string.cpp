// task_id: lexicographically-smallest-generated-string
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.generateString("FF", "z") == "aa"));
    assert((sol.generateString("FT", "c") == "ac"));
    assert((sol.generateString("FT", "yz") == "ayz"));
    assert((sol.generateString("TTT", "aaa") == "aaaaa"));
    assert((sol.generateString("TTT", "xyz") == ""));
    assert((sol.generateString("TF", "ab") == "aba"));
    assert((sol.generateString("FFF", "a") == "bbb"));
    assert((sol.generateString("TFTF", "abc") == ""));
    assert((sol.generateString("TT", "a") == "aa"));
    assert((sol.generateString("F", "fgh") == "aaa"));
    assert((sol.generateString("FFF", "xyz") == "aaaaa"));
    assert((sol.generateString("TTFT", "ij") == ""));
    assert((sol.generateString("F", "a") == "b"));
    assert((sol.generateString("FT", "a") == "ba"));
    assert((sol.generateString("TF", "a") == "ab"));
    assert((sol.generateString("FTF", "aaa") == "baaab"));
    assert((sol.generateString("FFT", "aaa") == "abaaa"));
    assert((sol.generateString("FF", "aa") == "aba"));
    assert((sol.generateString("TF", "xy") == "xya"));
    assert((sol.generateString("T", "z") == "z"));
    assert((sol.generateString("T", "a") == "a"));
    assert((sol.generateString("TFT", "aaa") == ""));
    assert((sol.generateString("FT", "ab") == "aab"));
    assert((sol.generateString("TTT", "de") == ""));
    assert((sol.generateString("FFF", "aaa") == "aabaa"));
    assert((sol.generateString("TF", "b") == "ba"));
    assert((sol.generateString("TT", "ab") == ""));
    assert((sol.generateString("T", "de") == "de"));
    assert((sol.generateString("TFTF", "ab") == "ababa"));
    assert((sol.generateString("TF", "aa") == "aab"));
    assert((sol.generateString("FT", "aa") == "baa"));
    assert((sol.generateString("TFF", "aaa") == "aaaba"));
    assert((sol.generateString("FF", "xy") == "aaa"));
    assert((sol.generateString("F", "d") == "a"));
    assert((sol.generateString("TT", "aa") == "aaa"));
    assert((sol.generateString("F", "abc") == "aaa"));
    assert((sol.generateString("TT", "mn") == ""));
    assert((sol.generateString("T", "abc") == "abc"));
    assert((sol.generateString("TFFFTTFT", "dddd") == ""));
    assert((sol.generateString("TTT", "mnopqrstu") == ""));
    assert((sol.generateString("F", "z") == "a"));
    assert((sol.generateString("TTFFTFTFF", "generated") == ""));
    assert((sol.generateString("TFTFTFTFT", "xyz") == ""));
    assert((sol.generateString("TFTFTFT", "uv") == "uvuvuvuv"));
    assert((sol.generateString("FTFTFTFT", "mnop") == ""));
    assert((sol.generateString("FTFTFT", "qrstuvwx") == ""));
    assert((sol.generateString("FFFFFFFFFT", "xyz") == "aaaaaaaaaxyz"));
    assert((sol.generateString("TTTTTTTTTTTT", "qrstuvwx") == ""));
    assert((sol.generateString("FTFTFTFTFTFTFTFTFTFTFT", "abcdef") == ""));
    assert((sol.generateString("TFTFTF", "ijklmnop") == ""));
    assert((sol.generateString("TFTFTFTFTFT", "stuvwx") == ""));
    assert((sol.generateString("TFTFTFTFTFT", "xyz") == ""));
    assert((sol.generateString("TTTFTFTFT", "test") == ""));
    assert((sol.generateString("FFFFFFFFFFFFFFFF", "abc") == "aaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("TFTFTFTFTFT", "yz") == "yzyzyzyzyzyz"));
    assert((sol.generateString("FTTTFFTTTTFFFF", "sample") == ""));
    assert((sol.generateString("FTFT", "mnopq") == ""));
    assert((sol.generateString("TFTFTFTFTF", "test") == ""));
    assert((sol.generateString("TTFTFT", "zzz") == ""));
    assert((sol.generateString("TTTTFFF", "efgh") == ""));
    assert((sol.generateString("TTTFTFFTFF", "ghijkl") == ""));
    assert((sol.generateString("FTTFT", "xyzw") == ""));
    assert((sol.generateString("FFFFTTT", "ijkl") == ""));
    assert((sol.generateString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "uvw") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("FFTTFFTF", "eeee") == ""));
    assert((sol.generateString("FFFF", "wxyz") == "aaaaaaa"));
    assert((sol.generateString("TFTFTFTFT", "xy") == "xyxyxyxyxy"));
    assert((sol.generateString("TFFFT", "abc") == "abcaabc"));
    assert((sol.generateString("TFTFT", "abcdefghi") == ""));
    assert((sol.generateString("TTFT", "abc") == ""));
    assert((sol.generateString("FFTFTFFT", "hhhh") == ""));
    assert((sol.generateString("TFTFTFTFTFTFTFTFTF", "complex") == ""));
    assert((sol.generateString("FTFTTFTF", "cccc") == ""));
    assert((sol.generateString("TFTFTFT", "mnop") == ""));
    assert((sol.generateString("FTFTFT", "mnop") == ""));
    assert((sol.generateString("TFTFTFTFTFT", "abcdefg") == ""));
    assert((sol.generateString("TTTTTTTTTTTT", "z") == "zzzzzzzzzzzz"));
    assert((sol.generateString("FFFFFFFFFFFF", "a") == "bbbbbbbbbbbb"));
    assert((sol.generateString("TTTFTTTT", "qrst") == ""));
    assert((sol.generateString("FFFFFFFFFT", "abcdef") == "aaaaaaaaaabcdef"));
    assert((sol.generateString("FTFTFT", "aaa") == ""));
    assert((sol.generateString("TTTTTTTTTT", "ghijkl") == ""));
    assert((sol.generateString("TTTTTTTTTT", "opqrst") == ""));
    assert((sol.generateString("FTFTFT", "xyz") == ""));
    assert((sol.generateString("TTFF", "qrstuvwx") == ""));
    assert((sol.generateString("TFTFT", "abc") == ""));
    assert((sol.generateString("TFTFTFTFTFTFT", "mnopqr") == ""));
    assert((sol.generateString("FF", "wx") == "aaa"));
    assert((sol.generateString("TTFTTFFFTTTFTFT", "qrstuvw") == ""));
    assert((sol.generateString("TTTFTTTFTTT", "mnopqrstuvw") == ""));
    assert((sol.generateString("FTFTFTFTFT", "xyz") == ""));
    assert((sol.generateString("FFFF", "ghijkl") == "aaaaaaaaa"));
    assert((sol.generateString("FFTFTT", "world") == ""));
    assert((sol.generateString("FTFTFTFTFT", "abc") == ""));
    assert((sol.generateString("TTFT", "uvw") == ""));
    assert((sol.generateString("TTFTFFTFTFFTFT", "example") == ""));
    assert((sol.generateString("FFFFFFFF", "abc") == "aaaaaaaaaa"));
    assert((sol.generateString("TFFT", "lmnopqrstu") == ""));
    assert((sol.generateString("FTFTFT", "def") == ""));
    assert((sol.generateString("FFFFFF", "abcd") == "aaaaaaaaa"));
    assert((sol.generateString("TFTFTFTFTFTFT", "abcdef") == ""));
    assert((sol.generateString("TFFT", "vwxyz") == ""));
    assert((sol.generateString("TTFTFTFTT", "world") == ""));
    assert((sol.generateString("TFFFFFFFF", "wxyz") == "wxyzaaaaaaaa"));
    assert((sol.generateString("TTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTTT", "mnop") == ""));
    assert((sol.generateString("TFT", "abcdef") == ""));
    assert((sol.generateString("FTTFTFFT", "gggg") == ""));
    assert((sol.generateString("TFFTFT", "abcd") == ""));
    assert((sol.generateString("TTFTFTFFT", "lexicographically") == ""));
    assert((sol.generateString("FTFTFTFTT", "stuv") == ""));
    assert((sol.generateString("FFTFFT", "abc") == "aaabcabc"));
    assert((sol.generateString("TTTTTTT", "abcd") == ""));
    assert((sol.generateString("TF", "yz") == "yza"));
    assert((sol.generateString("TTFT", "jklmno") == ""));
    assert((sol.generateString("TFTFTFTFTFT", "mnopqrstuvw") == ""));
    assert((sol.generateString("TFTF", "mnop") == ""));
    assert((sol.generateString("TTTTTTTT", "a") == "aaaaaaaa"));
    assert((sol.generateString("TFTFTF", "mnopqr") == ""));
    assert((sol.generateString("TTT", "k") == "kkk"));
    assert((sol.generateString("TFFTFF", "bcb") == "bcbbcbaa"));
    assert((sol.generateString("TFTFTFTFTFTFTFTFTFT", "a") == "abababababababababa"));
    assert((sol.generateString("FTFTFTFTFT", "uvw") == ""));
    assert((sol.generateString("FTFTFT", "stuvwx") == ""));
    assert((sol.generateString("FFTT", "abcd") == ""));
    assert((sol.generateString("TTTTTTTTTTTTTTTTTT", "solution") == ""));
    assert((sol.generateString("FTFTFTFFT", "example") == ""));
    assert((sol.generateString("TFTFT", "efghij") == ""));
    assert((sol.generateString("TFTFTFT", "wxyz") == ""));
    assert((sol.generateString("TTTTTTTTT", "abcdefghi") == ""));
    assert((sol.generateString("FTF", "abcd") == "aabcda"));
    assert((sol.generateString("TFTFTFTFTFTFTF", "abcd") == ""));
    assert((sol.generateString("TFTFTFTFTF", "uvw") == ""));
    assert((sol.generateString("FTF", "zz") == "azza"));
    assert((sol.generateString("TFT", "efghijkl") == ""));
    assert((sol.generateString("TTTTTTTTTT", "yzab") == ""));
    assert((sol.generateString("TTTTTTTTF", "mnopqr") == ""));
    assert((sol.generateString("TFT", "def") == ""));
    assert((sol.generateString("TFTFTF", "xyz") == ""));
    assert((sol.generateString("TTTTTT", "aaa") == "aaaaaaaa"));
    assert((sol.generateString("FTFT", "pqrstu") == ""));
    assert((sol.generateString("FTFTFTFTFT", "mnopqrstuvwx") == ""));
    assert((sol.generateString("FFFFFFFF", "abcd") == "aaaaaaaaaaa"));
    assert((sol.generateString("TTFFTTFFTT", "abcdefgh") == ""));
    assert((sol.generateString("FTFTFTFTFTFTFTFTFTFTFTFTFTFTFTFT", "defghijklm") == ""));
    assert((sol.generateString("TFTFTF", "abcdefgh") == ""));
    assert((sol.generateString("TF", "zzz") == "zzza"));
    assert((sol.generateString("FTTFFTFF", "uvw") == ""));
    assert((sol.generateString("FFFFFFFFF", "aaaa") == "aaabaaabaaab"));
    assert((sol.generateString("TFTFT", "pqrstuvwx") == ""));
    assert((sol.generateString("TFTFTFTFTFTFTFTFTFT", "abcdefghijklmnopqrstuvwxyz") == ""));
    assert((sol.generateString("FFTTTFFFFTTFF", "abcdefghi") == ""));
    assert((sol.generateString("FTFTFTFT", "efghijkl") == ""));
    assert((sol.generateString("TTFFFFTT", "xyz") == ""));
    assert((sol.generateString("FT", "mnopqr") == "amnopqr"));
    assert((sol.generateString("FF", "abcdef") == "aaaaaaa"));
    assert((sol.generateString("TTT", "yz") == ""));
    assert((sol.generateString("TTTT", "aaa") == "aaaaaa"));
    assert((sol.generateString("FTFTFTFTFTFT", "yz") == "ayzyzyzyzyzyz"));
    assert((sol.generateString("TFFT", "rstuv") == ""));
    assert((sol.generateString("FFTFTFTFF", "mnop") == ""));
    assert((sol.generateString("TFT", "abcd") == ""));
    assert((sol.generateString("FFFFFFFFF", "abcde") == "aaaaaaaaaaaaa"));
    assert((sol.generateString("FFTFFT", "xyz") == "aaxyzxyz"));
    assert((sol.generateString("TFTFT", "abcde") == ""));
    assert((sol.generateString("FFFFFFFF", "abcdefgh") == "aaaaaaaaaaaaaaa"));
    assert((sol.generateString("TTTFFFF", "aaaa") == "aaaaaabaaa"));
    assert((sol.generateString("TFTFTF", "abc") == ""));
    assert((sol.generateString("FTFTFTFT", "a") == "babababa"));
    assert((sol.generateString("TTTTTTTTTTTTTTTT", "xyz") == ""));
    assert((sol.generateString("TFTFFT", "xyz") == ""));
    assert((sol.generateString("FFFFFFFFFT", "qrstuv") == "aaaaaaaaaqrstuv"));
    assert((sol.generateString("TTTTTTTT", "aaaa") == "aaaaaaaaaaa"));
    assert((sol.generateString("FFFFFFFFFFFFFFFF", "hijklmnop") == "aaaaaaaaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("TFTFFTFTFTFFT", "xyzxyz") == ""));
    assert((sol.generateString("TTTTTTTTT", "mnopqrst") == ""));
    assert((sol.generateString("FFFTTFFT", "qrstu") == ""));
    assert((sol.generateString("TTTTT", "ab") == ""));
    assert((sol.generateString("FFFF", "abcdefgh") == "aaaaaaaaaaa"));
    assert((sol.generateString("TFTFTFTFTFTFTFT", "abcdefg") == ""));
    assert((sol.generateString("FFFFFFFFFT", "cdefgh") == "aaaaaaaaacdefgh"));
    assert((sol.generateString("FFFFFFFFFF", "zyxwvut") == "aaaaaaaaaaaaaaaa"));
    assert((sol.generateString("TFFTFTF", "abcd") == ""));
    assert((sol.generateString("TTTTF", "mnop") == ""));
    assert((sol.generateString("FTFT", "abcdefghijk") == ""));
    assert((sol.generateString("TFTFTFTFT", "abcde") == ""));
    assert((sol.generateString("FFTT", "yz") == ""));
    assert((sol.generateString("TFFTTF", "abc") == ""));
    assert((sol.generateString("TTFFTTFFT", "solution") == ""));
    assert((sol.generateString("FFTTFF", "xyz") == ""));
    assert((sol.generateString("FTFTF", "qrst") == ""));
    assert((sol.generateString("FFTFTFTFT", "yz") == "aayzyzyzyz"));
    assert((sol.generateString("TTFFTT", "abc") == ""));
    assert((sol.generateString("FFFFFFFFFFFFFFFFFFFFFFFF", "mnopqrstuvwxyz") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("TTTTF", "abcde") == ""));
    assert((sol.generateString("FTFT", "zz") == ""));
    assert((sol.generateString("TFTFTFTFTFT", "abcdabcd") == ""));
    assert((sol.generateString("FTTFFTFTT", "possible") == ""));
    assert((sol.generateString("TFFFTF", "mnop") == "mnopmnopa"));
    assert((sol.generateString("FFTFFTTFT", "output") == ""));
    assert((sol.generateString("TTT", "qrstuv") == ""));
    assert((sol.generateString("TTF", "abcd") == ""));
    assert((sol.generateString("FFFFFFFFFFFF", "abcde") == "aaaaaaaaaaaaaaaa"));
    assert((sol.generateString("FFFFFFFFTT", "abcd") == ""));
    assert((sol.generateString("TTFF", "yz") == ""));
    assert((sol.generateString("FFFFFFFF", "zz") == "aaaaaaaaa"));
    assert((sol.generateString("FFFF", "xyz") == "aaaaaa"));
    assert((sol.generateString("TTFT", "yz") == ""));
    assert((sol.generateString("FFFF", "zzz") == "aaaaaa"));
    assert((sol.generateString("FFFFFF", "zzz") == "aaaaaaaa"));
    assert((sol.generateString("FFTFTFTFT", "complex") == ""));
    assert((sol.generateString("TT", "qrstuv") == ""));
    assert((sol.generateString("FFFFFFFF", "z") == "aaaaaaaa"));
    assert((sol.generateString("FTF", "mnop") == "amnopa"));
    assert((sol.generateString("FFTFFT", "qrst") == ""));
    assert((sol.generateString("TFT", "efghijklmno") == ""));
    assert((sol.generateString("FTFTFTFT", "pqrstuvwx") == ""));
    assert((sol.generateString("FFTFFTFFT", "string") == ""));
    assert((sol.generateString("FTFTFTFT", "ab") == "aabababab"));
    assert((sol.generateString("FFTFTF", "bcd") == ""));
    assert((sol.generateString("FTFTFTFT", "qrst") == ""));
    assert((sol.generateString("TFTFTF", "uvw") == ""));
    assert((sol.generateString("FTT", "efghijkl") == ""));
    assert((sol.generateString("TFTFTFTFTFTFTFTFT", "abc") == ""));
    assert((sol.generateString("TFFFFT", "def") == "defaadef"));
    assert((sol.generateString("TFTTFF", "hello") == ""));
    assert((sol.generateString("FFFFFFFFFFFFFFFF", "challenge") == "aaaaaaaaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("TFTFFTFF", "ffff") == ""));
    assert((sol.generateString("FTFTFT", "zzz") == ""));
    assert((sol.generateString("TTTTTTTT", "abcdefghijk") == ""));
    assert((sol.generateString("FTFTFTFTFTFT", "abcd") == ""));
    assert((sol.generateString("FFTFT", "wxyz") == ""));
    assert((sol.generateString("FTFTFFTTT", "smaller") == ""));
    assert((sol.generateString("FTFTFTFTFTFTFTFT", "mnopqr") == ""));
    assert((sol.generateString("TTTTTTTTTT", "mnop") == ""));
    assert((sol.generateString("TTTFTF", "abc") == ""));
    assert((sol.generateString("FTFTFTFTFT", "ab") == "aababababab"));
    assert((sol.generateString("TFTFTFTFTFT", "ijklmn") == ""));
    assert((sol.generateString("FFTTFFTT", "stuv") == ""));
    assert((sol.generateString("FTFTFTFTFT", "jklmnop") == ""));
    assert((sol.generateString("FTFTFFTTT", "input") == ""));
    assert((sol.generateString("FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF", "zzzzzzzzzz") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("FFFFFFFFFT", "mnopqr") == "aaaaaaaaamnopqr"));
    assert((sol.generateString("FFFFFFT", "bbbb") == "aaaaaabbbb"));
    assert((sol.generateString("FTTFFTFTF", "hello") == ""));
    assert((sol.generateString("FFTFTFT", "qrst") == ""));
    assert((sol.generateString("FFFFFFFF", "lmnop") == "aaaaaaaaaaaa"));
    assert((sol.generateString("FFFFFFFFFFFFFFFF", "zzzzzzzzzzzzzzzzzzzzzzzzzzzz") == "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("TFTFTFTFT", "stuv") == ""));
    assert((sol.generateString("FFTFFTFFT", "qrst") == ""));
    assert((sol.generateString("FFFFFFFF", "mnopqr") == "aaaaaaaaaaaaa"));
    assert((sol.generateString("TTFFFFTT", "uvwxy") == ""));
    assert((sol.generateString("FFFF", "vwxyz") == "aaaaaaaa"));
    assert((sol.generateString("TT", "abcdef") == ""));
    assert((sol.generateString("TTFFTTF", "mnop") == ""));
    assert((sol.generateString("FFFF", "abcdefghijklmno") == "aaaaaaaaaaaaaaaaaa"));
    assert((sol.generateString("TTFFTT", "mnop") == ""));
    assert((sol.generateString("TTT", "abc") == ""));
    assert((sol.generateString("TTTTTTTFT", "stuvwx") == ""));
    assert((sol.generateString("FFFFFFFFFT", "uvwxyz") == "aaaaaaaaauvwxyz"));
    assert((sol.generateString("TFTFTFTFTFTFT", "abcdabcd") == ""));
    assert((sol.generateString("FFTTF", "xyz") == ""));
    assert((sol.generateString("FFFFFFFFF", "a") == "bbbbbbbbb"));
    assert((sol.generateString("TFTFT", "ijkl") == ""));
    assert((sol.generateString("TFFTFT", "bca") == ""));
    assert((sol.generateString("FTFTFT", "ijklmnop") == ""));
    assert((sol.generateString("FFFFFT", "zyxwvut") == "aaaaazyxwvut"));

    cout << "All tests passed for lexicographically-smallest-generated-string" << endl;
    return 0;
}
