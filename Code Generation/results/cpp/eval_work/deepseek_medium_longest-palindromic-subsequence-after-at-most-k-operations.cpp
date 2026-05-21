// task_id: longest-palindromic-subsequence-after-at-most-k-operations
// difficulty: Medium

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
#include <vector>
#include <string>
#include <algorithm>
#include <cstring>
using namespace std;

class Solution {
public:
    int longestPalindromicSubsequence(string s, int k) {
        int n = s.length();
        vector<vector<vector<int>>> dp(n, vector<vector<int>>(n, vector<int>(k + 1, -1)));
        
        function<int(int, int, int)> solve = [&](int i, int j, int rem) -> int {
            if (i > j) return 0;
            if (i == j) return 1;
            if (dp[i][j][rem] != -1) return dp[i][j][rem];
            
            int res = max(solve(i + 1, j, rem), solve(i, j - 1, rem));
            
            int diff = abs(s[i] - s[j]);
            int cost = min(diff, 26 - diff);
            
            if (rem >= cost) {
                res = max(res, 2 + solve(i + 1, j - 1, rem - cost));
            }
            
            return dp[i][j][rem] = res;
        };
        
        return solve(0, n - 1, k);
    }
};

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.longestPalindromicSubsequence("zxy", 1) == 3));
    assert((sol.longestPalindromicSubsequence("a", 5) == 1));
    assert((sol.longestPalindromicSubsequence("abced", 2) == 3));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyz", 25) == 14));
    assert((sol.longestPalindromicSubsequence("zzzzz", 1) == 5));
    assert((sol.longestPalindromicSubsequence("abcdeedcba", 5) == 10));
    assert((sol.longestPalindromicSubsequence("zzzzz", 10) == 5));
    assert((sol.longestPalindromicSubsequence("abcba", 0) == 5));
    assert((sol.longestPalindromicSubsequence("aaazzz", 4) == 6));
    assert((sol.longestPalindromicSubsequence("abcdef", 3) == 3));
    assert((sol.longestPalindromicSubsequence("adadd", 2) == 3));
    assert((sol.longestPalindromicSubsequence("mamad", 3) == 3));
    assert((sol.longestPalindromicSubsequence("zyxwvutsrqponmlkjihgfedcba", 200) == 26));
    assert((sol.longestPalindromicSubsequence("xyz", 1) == 2));
    assert((sol.longestPalindromicSubsequence("abba", 1) == 4));
    assert((sol.longestPalindromicSubsequence("abcdedcba", 0) == 9));
    assert((sol.longestPalindromicSubsequence("aabaa", 2) == 5));
    assert((sol.longestPalindromicSubsequence("mnopqr", 10) == 6));
    assert((sol.longestPalindromicSubsequence("a", 0) == 1));
    assert((sol.longestPalindromicSubsequence("abcdefg", 3) == 3));
    assert((sol.longestPalindromicSubsequence("abcdabcdabcd", 6) == 11));
    assert((sol.longestPalindromicSubsequence("a", 1) == 1));
    assert((sol.longestPalindromicSubsequence("abcdedcba", 5) == 9));
    assert((sol.longestPalindromicSubsequence("zzzzzzzzzz", 0) == 10));
    assert((sol.longestPalindromicSubsequence("zzzzzzzzzzzzzzzzzzzz", 100) == 20));
    assert((sol.longestPalindromicSubsequence("racecar", 10) == 7));
    assert((sol.longestPalindromicSubsequence("zzyzxzyzxzyzxzyzxzyz", 30) == 20));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyzz", 50) == 20));
    assert((sol.longestPalindromicSubsequence("aaaabbbb", 5) == 8));
    assert((sol.longestPalindromicSubsequence("abcabcabcabcabcabcabcabcabcabc", 25) == 30));
    assert((sol.longestPalindromicSubsequence("aaaaabbbbbcccc", 5) == 10));
    assert((sol.longestPalindromicSubsequence("aaaaabbbbbaaaa", 50) == 14));
    assert((sol.longestPalindromicSubsequence("aaaaabbbbbaaaaa", 10) == 15));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba", 180) == 51));
    assert((sol.longestPalindromicSubsequence("level", 5) == 5));
    assert((sol.longestPalindromicSubsequence("racecar", 5) == 7));
    assert((sol.longestPalindromicSubsequence("abcdefgabcdefgabcdefgabcdefg", 10) == 17));
    assert((sol.longestPalindromicSubsequence("abcdedcba", 1) == 9));
    assert((sol.longestPalindromicSubsequence("qwertyuioplkjhgfdsazxcvbnmqwertyuioplkjhgfdsazxcvb", 100) == 47));
    assert((sol.longestPalindromicSubsequence("abxyzabcxyzabcxyz", 25) == 17));
    assert((sol.longestPalindromicSubsequence("level", 1) == 5));
    assert((sol.longestPalindromicSubsequence("abcba", 1) == 5));
    assert((sol.longestPalindromicSubsequence("ababababababababababababababababababab", 75) == 38));
    assert((sol.longestPalindromicSubsequence("abcdefgxyzzyxgfedcba", 15) == 20));
    assert((sol.longestPalindromicSubsequence("refer", 0) == 5));
    assert((sol.longestPalindromicSubsequence("aabbccddeeffggzzzyyxxwwvvuuttsrqponmlkjihgfedcba", 100) == 47));
    assert((sol.longestPalindromicSubsequence("palindrome", 15) == 9));
    assert((sol.longestPalindromicSubsequence("amanaplanacanalpanama", 100) == 21));
    assert((sol.longestPalindromicSubsequence("qwertyuiopasdfghjklzxcvbnm", 50) == 23));
    assert((sol.longestPalindromicSubsequence("aaaabbbbcccc", 15) == 12));
    assert((sol.longestPalindromicSubsequence("mnonmonmomnonmonmonmomnonm", 15) == 26));
    assert((sol.longestPalindromicSubsequence("mississippi", 7) == 10));
    assert((sol.longestPalindromicSubsequence("banana", 10) == 5));
    assert((sol.longestPalindromicSubsequence("aabacbebebe", 5) == 8));
    assert((sol.longestPalindromicSubsequence("madamimadam", 10) == 11));
    assert((sol.longestPalindromicSubsequence("abcdexyzabcdexyzabcdexyz", 50) == 24));
    assert((sol.longestPalindromicSubsequence("mississippi", 10) == 10));
    assert((sol.longestPalindromicSubsequence("deified", 4) == 7));
    assert((sol.longestPalindromicSubsequence("abcdedcba", 2) == 9));
    assert((sol.longestPalindromicSubsequence("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz", 50) == 28));
    assert((sol.longestPalindromicSubsequence("abcdedcba", 3) == 9));
    assert((sol.longestPalindromicSubsequence("mnopqrstuvwxyzyxwvutsrqponmlkjihgfedcbazyxwvutsrqponmlkjihgfedcba", 200) == 60));
    assert((sol.longestPalindromicSubsequence("aabbccabcabcabcabcabc", 50) == 21));
    assert((sol.longestPalindromicSubsequence("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 1) == 50));
    assert((sol.longestPalindromicSubsequence("abcdeedcba", 0) == 10));
    assert((sol.longestPalindromicSubsequence("abbaacddcabb", 4) == 11));
    assert((sol.longestPalindromicSubsequence("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz", 200) == 52));
    assert((sol.longestPalindromicSubsequence("zzzyzzyzzyzzyzzyzzyz", 200) == 20));
    assert((sol.longestPalindromicSubsequence("mississippi", 5) == 9));
    assert((sol.longestPalindromicSubsequence("level", 2) == 5));
    assert((sol.longestPalindromicSubsequence("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 0) == 32));
    assert((sol.longestPalindromicSubsequence("ababbabbbabaaa", 15) == 14));
    assert((sol.longestPalindromicSubsequence("rotor", 15) == 5));
    assert((sol.longestPalindromicSubsequence("noon", 1) == 4));
    assert((sol.longestPalindromicSubsequence("noonhighnoon", 5) == 12));
    assert((sol.longestPalindromicSubsequence("abcdbca", 2) == 7));
    assert((sol.longestPalindromicSubsequence("abcdxyzabcdxyzabcdxyz", 30) == 21));
    assert((sol.longestPalindromicSubsequence("banana", 3) == 5));
    assert((sol.longestPalindromicSubsequence("qwertyuiopasdfghjklzxcvbnmnbvcxzlkjhgfdsapoiuytrewq", 50) == 51));
    assert((sol.longestPalindromicSubsequence("abacbacbacbacbacbacbacbacbacbacbacbacbacbacbacbacb", 20) == 50));
    assert((sol.longestPalindromicSubsequence("abacaba", 3) == 7));
    assert((sol.longestPalindromicSubsequence("mamamamamamamamamamamamamamamamama", 50) == 33));
    assert((sol.longestPalindromicSubsequence("racecar", 2) == 7));
    assert((sol.longestPalindromicSubsequence("noon", 2) == 4));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba", 250) == 51));
    assert((sol.longestPalindromicSubsequence("abcdefg", 6) == 5));
    assert((sol.longestPalindromicSubsequence("zyzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 300) == 84));
    assert((sol.longestPalindromicSubsequence("madam", 1) == 5));
    assert((sol.longestPalindromicSubsequence("zyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyx", 100) == 57));
    assert((sol.longestPalindromicSubsequence("zyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyx", 200) == 39));
    assert((sol.longestPalindromicSubsequence("rotor", 0) == 5));
    assert((sol.longestPalindromicSubsequence("abcdefgzyxwvutsrqponmlkjihgfedcba", 50) == 29));
    assert((sol.longestPalindromicSubsequence("abcdefghzyxwvutsrqponmlkjihgfedcba", 150) == 34));
    assert((sol.longestPalindromicSubsequence("qwertyuiopasdfghjklzxcvbnmqwertyuiopasdfghjklzxcvbnm", 100) == 47));
    assert((sol.longestPalindromicSubsequence("abcdefghizyxwvutsrqponmlkjihgfedcba", 100) == 35));
    assert((sol.longestPalindromicSubsequence("deified", 2) == 7));
    assert((sol.longestPalindromicSubsequence("aaaabbbbccccdddd", 10) == 13));
    assert((sol.longestPalindromicSubsequence("madam", 2) == 5));
    assert((sol.longestPalindromicSubsequence("rotor", 3) == 5));
    assert((sol.longestPalindromicSubsequence("abcdefgihgfedcb", 15) == 15));
    assert((sol.longestPalindromicSubsequence("abcdefghihgfedcba", 10) == 17));
    assert((sol.longestPalindromicSubsequence("pqrstuvwxyzabcdefghijklmno", 50) == 20));
    assert((sol.longestPalindromicSubsequence("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 0) == 30));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyz", 10) == 9));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxzy", 100) == 26));
    assert((sol.longestPalindromicSubsequence("zzzzzzzzzzzzzzzzzzzz", 10) == 20));
    assert((sol.longestPalindromicSubsequence("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz", 150) == 49));
    assert((sol.longestPalindromicSubsequence("abcabcabcabcabcabcabcabcabcabc", 100) == 30));
    assert((sol.longestPalindromicSubsequence("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 5) == 52));
    assert((sol.longestPalindromicSubsequence("reviled", 7) == 5));
    assert((sol.longestPalindromicSubsequence("abccba", 0) == 6));
    assert((sol.longestPalindromicSubsequence("zyxzyxzyxzyxzyxzyxzyx", 100) == 21));
    assert((sol.longestPalindromicSubsequence("pneumonoultramicroscopicsilicovolcanoconiosis", 50) == 37));
    assert((sol.longestPalindromicSubsequence("mnopqrstuvwxyz", 10) == 6));
    assert((sol.longestPalindromicSubsequence("step on no pets", 10) == 15));
    assert((sol.longestPalindromicSubsequence("zyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyxzyx", 100) == 42));
    assert((sol.longestPalindromicSubsequence("abababababababababababababababab", 50) == 32));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyz", 50) == 20));
    assert((sol.longestPalindromicSubsequence("mississippi", 3) == 9));
    assert((sol.longestPalindromicSubsequence("abacabadabacaba", 5) == 15));
    assert((sol.longestPalindromicSubsequence("mnopqrstuvwxyzzyxwvutsrqponmlk", 80) == 30));
    assert((sol.longestPalindromicSubsequence("abcdezyxwvutsrqponmlkjihgf", 50) == 20));
    assert((sol.longestPalindromicSubsequence("abacabadabacaba", 10) == 15));
    assert((sol.longestPalindromicSubsequence("abcabcabc", 4) == 8));
    assert((sol.longestPalindromicSubsequence("abababababababababab", 10) == 20));
    assert((sol.longestPalindromicSubsequence("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz", 100) == 40));
    assert((sol.longestPalindromicSubsequence("abcabcabcabcabcabcabc", 20) == 21));
    assert((sol.longestPalindromicSubsequence("qwertyuiopasdfghjklzxcvbnm", 25) == 18));
    assert((sol.longestPalindromicSubsequence("aaaaabbbbb", 10) == 10));
    assert((sol.longestPalindromicSubsequence("zabacabadabacaba", 10) == 15));
    assert((sol.longestPalindromicSubsequence("abcdefedcbaabcdefedcbaabcdefedcba", 60) == 33));
    assert((sol.longestPalindromicSubsequence("mnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba", 150) == 36));
    assert((sol.longestPalindromicSubsequence("abcdxyzzyxcba", 10) == 13));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba", 100) == 51));
    assert((sol.longestPalindromicSubsequence("kayak", 20) == 5));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyz", 100) == 40));
    assert((sol.longestPalindromicSubsequence("abcdzdcba", 3) == 9));
    assert((sol.longestPalindromicSubsequence("aababaaa", 2) == 8));
    assert((sol.longestPalindromicSubsequence("deed", 3) == 4));
    assert((sol.longestPalindromicSubsequence("ababababababababababababababababababababababababababab", 100) == 54));
    assert((sol.longestPalindromicSubsequence("abcdefghijkmlkjihgfedcba", 50) == 24));
    assert((sol.longestPalindromicSubsequence("abcdeedcba", 3) == 10));
    assert((sol.longestPalindromicSubsequence("abcdefg", 10) == 6));
    assert((sol.longestPalindromicSubsequence("mnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba", 50) == 30));
    assert((sol.longestPalindromicSubsequence("racecar", 0) == 7));
    assert((sol.longestPalindromicSubsequence("zyxwvutsrqponmlkjihgfedcba", 150) == 26));
    assert((sol.longestPalindromicSubsequence("abcdefghijklmnopqrstuvwxyzyxwvutsrqponmlkjihgfedcba", 50) == 51));
    assert((sol.longestPalindromicSubsequence("abcdefghijabcdefghij", 15) == 13));
    assert((sol.longestPalindromicSubsequence("abacabadabacabadabacaba", 20) == 23));
    assert((sol.longestPalindromicSubsequence("aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa", 5) == 52));
    assert((sol.longestPalindromicSubsequence("abcdabcdabcdabcd", 20) == 16));
    assert((sol.longestPalindromicSubsequence("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz", 180) == 52));
    assert((sol.longestPalindromicSubsequence("abcdefghijjihgfedcba", 5) == 20));

    cout << "All tests passed for longest-palindromic-subsequence-after-at-most-k-operations" << endl;
    return 0;
}
