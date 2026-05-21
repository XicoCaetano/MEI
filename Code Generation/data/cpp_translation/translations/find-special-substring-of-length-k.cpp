// task_id: find-special-substring-of-length-k
// difficulty: Easy

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
    bool hasSpecialSubstring(string s, int k) {
        int n = (int)s.size();
        int l = 0;
        while (l < n) {
            int r = l;
            while (r < n && s[r] == s[l]) ++r;
            if (r - l == k) return true;
            l = r;
        }
        return false;
    }
};

int main() {
    Solution sol;

    assert((sol.hasSpecialSubstring("abc", 2) == false));
    assert((sol.hasSpecialSubstring("aabbccddeeff", 2) == true));
    assert((sol.hasSpecialSubstring("abcde", 1) == true));
    assert((sol.hasSpecialSubstring("zzzz", 4) == true));
    assert((sol.hasSpecialSubstring("xyzxyz", 1) == true));
    assert((sol.hasSpecialSubstring("abcdabcd", 2) == false));
    assert((sol.hasSpecialSubstring("aaaaa", 3) == false));
    assert((sol.hasSpecialSubstring("zzzzz", 5) == true));
    assert((sol.hasSpecialSubstring("aabbcc", 2) == true));
    assert((sol.hasSpecialSubstring("aaabaaa", 3) == true));
    assert((sol.hasSpecialSubstring("xyzxxxxxzyx", 6) == false));
    assert((sol.hasSpecialSubstring("aaabbbcccddd", 4) == false));
    assert((sol.hasSpecialSubstring("xyzxxxxxyzzzzzzzzz", 4) == false));
    assert((sol.hasSpecialSubstring("mmmmnmmmmm", 5) == true));
    assert((sol.hasSpecialSubstring("mnopqrrrrrstuvwxyz", 5) == true));
    assert((sol.hasSpecialSubstring("pppppqqqqqqppppp", 5) == true));
    assert((sol.hasSpecialSubstring("llllllllllllllllllll", 10) == false));
    assert((sol.hasSpecialSubstring("aabbbcccccddddd", 5) == true));
    assert((sol.hasSpecialSubstring("aabbccddeeffgghhhiii", 3) == true));
    assert((sol.hasSpecialSubstring("abababababababa", 3) == false));
    assert((sol.hasSpecialSubstring("aaaabbbbaaaa", 3) == false));
    assert((sol.hasSpecialSubstring("xyzxyzxyzxyzxyz", 3) == false));
    assert((sol.hasSpecialSubstring("abcdefghijjjjklmnop", 5) == false));
    assert((sol.hasSpecialSubstring("abcdefghijjjjjjklmnopqr", 6) == true));
    assert((sol.hasSpecialSubstring("aabbaaabbbaaa", 3) == true));
    assert((sol.hasSpecialSubstring("aabbccddeeffgghhiijjkk", 2) == true));
    assert((sol.hasSpecialSubstring("xyzzzzzyx", 4) == false));
    assert((sol.hasSpecialSubstring("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 40) == false));
    assert((sol.hasSpecialSubstring("mnopqrssssstuvw", 5) == true));
    assert((sol.hasSpecialSubstring("ppppqqqqrrrr", 4) == true));
    assert((sol.hasSpecialSubstring("aaaaabbbbbbcccccc", 5) == true));
    assert((sol.hasSpecialSubstring("abccccba", 4) == true));
    assert((sol.hasSpecialSubstring("abcdeeeefgh", 4) == true));
    assert((sol.hasSpecialSubstring("abcdefffgghijklmnoooppqrstuvwwxyz", 3) == true));
    assert((sol.hasSpecialSubstring("abcdeffghiiijjjjjklmnop", 5) == true));
    assert((sol.hasSpecialSubstring("qweeeeeeret", 5) == false));
    assert((sol.hasSpecialSubstring("abcdefffffghijkl", 5) == true));
    assert((sol.hasSpecialSubstring("abccbaabccba", 2) == true));
    assert((sol.hasSpecialSubstring("mnopqrstuvwxyzjjjjjjjjjjjjjjjjmnopqrstuvwxyz", 15) == false));
    assert((sol.hasSpecialSubstring("xyzzyzx", 2) == true));
    assert((sol.hasSpecialSubstring("zzzaaaazzz", 3) == true));
    assert((sol.hasSpecialSubstring("ababababab", 2) == false));
    assert((sol.hasSpecialSubstring("abcdefghijaaaaaaaaaaaabcdefghij", 12) == true));
    assert((sol.hasSpecialSubstring("abcccba", 3) == true));
    assert((sol.hasSpecialSubstring("tttttttttt", 10) == true));
    assert((sol.hasSpecialSubstring("ccccabcccc", 4) == true));
    assert((sol.hasSpecialSubstring("qqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqqq", 10) == false));
    assert((sol.hasSpecialSubstring("abcdefghijklmnopqrstuvwxyzzzzzzzzzzzzyxwvutsrqponmlkjihgfedcba", 11) == false));
    assert((sol.hasSpecialSubstring("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 50) == false));
    assert((sol.hasSpecialSubstring("aabbbaaacc", 3) == true));
    assert((sol.hasSpecialSubstring("abcdefghijaaaaaaaaaabcdefghij", 10) == true));
    assert((sol.hasSpecialSubstring("mnopqrstuuuuuuvwxyzz", 5) == false));
    assert((sol.hasSpecialSubstring("xxxyyyzzz", 3) == true));
    assert((sol.hasSpecialSubstring("mnonononononono", 7) == false));
    assert((sol.hasSpecialSubstring("abccccd", 4) == true));
    assert((sol.hasSpecialSubstring("abcdefghijjjjjjjjjklmnopqrstuvwxyz", 8) == false));
    assert((sol.hasSpecialSubstring("aaaaabaaaabaaa", 5) == true));
    assert((sol.hasSpecialSubstring("xxyyyyyyz", 5) == false));
    assert((sol.hasSpecialSubstring("zzzzzzzzzzz", 10) == false));
    assert((sol.hasSpecialSubstring("mnopqrrrpqmn", 3) == true));
    assert((sol.hasSpecialSubstring("aabaaaabaa", 4) == true));
    assert((sol.hasSpecialSubstring("aabbbaa", 3) == true));
    assert((sol.hasSpecialSubstring("aaabbbcccddd", 3) == true));
    assert((sol.hasSpecialSubstring("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 30) == false));
    assert((sol.hasSpecialSubstring("dddddeeeee", 5) == true));
    assert((sol.hasSpecialSubstring("xyzzzyxyzzzy", 4) == false));
    assert((sol.hasSpecialSubstring("abcdefghi", 1) == true));
    assert((sol.hasSpecialSubstring("mnopqrrrrrrstuv", 6) == true));
    assert((sol.hasSpecialSubstring("aaaaabbbbbcccccdddddeeeee", 5) == true));
    assert((sol.hasSpecialSubstring("aaaaaaaaaabbbbbbbbbb", 10) == true));
    assert((sol.hasSpecialSubstring("abababababababababab", 1) == true));
    assert((sol.hasSpecialSubstring("zzzzzzzzzzzzzzzzzzzz", 1) == false));
    assert((sol.hasSpecialSubstring("aaaaaabbbaaaaa", 3) == true));
    assert((sol.hasSpecialSubstring("xyxyxyxyxyxyxyxyxyxyxy", 3) == false));
    assert((sol.hasSpecialSubstring("abcdefghijkllllllmnop", 6) == true));
    assert((sol.hasSpecialSubstring("abcdeeeeefghijjjjkl", 4) == true));
    assert((sol.hasSpecialSubstring("xyzzzzzzxy", 6) == true));
    assert((sol.hasSpecialSubstring("aaaaaabaaaaaabaaa", 6) == true));
    assert((sol.hasSpecialSubstring("mnopqrstuvwxyzmnopqrstuvwxyzmnopqrstuvwxyz", 26) == false));
    assert((sol.hasSpecialSubstring("zzzzzzzzzzzzzzzzzzzz", 10) == false));
    assert((sol.hasSpecialSubstring("abcabcabc", 1) == true));
    assert((sol.hasSpecialSubstring("abcdefg", 1) == true));
    assert((sol.hasSpecialSubstring("abcabcabcabcabc", 1) == true));
    assert((sol.hasSpecialSubstring("mmmmmnnnnn", 5) == true));
    assert((sol.hasSpecialSubstring("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzzzzzzzzzzzzzzzz", 15) == false));
    assert((sol.hasSpecialSubstring("abcabcabcabcabcabc", 2) == false));
    assert((sol.hasSpecialSubstring("abcdabcdabcdabcdabcd", 4) == false));
    assert((sol.hasSpecialSubstring("aaaaaaaaaabbbbbbbbbc", 9) == true));
    assert((sol.hasSpecialSubstring("jjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjjj", 30) == false));
    assert((sol.hasSpecialSubstring("mnopqrstu", 4) == false));
    assert((sol.hasSpecialSubstring("xyzxyzzzzzzxyz", 5) == false));
    assert((sol.hasSpecialSubstring("qqqqqqqqqqqqqqqqqqqq", 10) == false));
    assert((sol.hasSpecialSubstring("abacadaeaf", 2) == false));
    assert((sol.hasSpecialSubstring("njjjjjjjjjjnj", 10) == true));
    assert((sol.hasSpecialSubstring("kjjjjjjjjjjjjjjjkl", 13) == false));
    assert((sol.hasSpecialSubstring("mmmmnnnnnnmmmm", 6) == true));
    assert((sol.hasSpecialSubstring("aabbccddeeeeffffgggghhhh", 4) == true));
    assert((sol.hasSpecialSubstring("abcdefghijjjjjjklmnop", 7) == false));
    assert((sol.hasSpecialSubstring("abccccccab", 6) == true));
    assert((sol.hasSpecialSubstring("aaaabbbbccccddddeeeeffff", 3) == false));
    assert((sol.hasSpecialSubstring("aabbbaaabbbaaabbbaaa", 4) == false));
    assert((sol.hasSpecialSubstring("xyzzyxzyxzyxzyxzyx", 2) == true));
    assert((sol.hasSpecialSubstring("pppppqqqqqppppp", 5) == true));
    assert((sol.hasSpecialSubstring("abcdefghijkllllllmnopqrstuv", 6) == true));
    assert((sol.hasSpecialSubstring("abcddeeeffggggghij", 4) == false));
    assert((sol.hasSpecialSubstring("zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz", 10) == false));
    assert((sol.hasSpecialSubstring("zzzzzaaaaazzzzz", 4) == false));
    assert((sol.hasSpecialSubstring("aabbccddeeffgghhiijjkkllmmnnooppqqrrssttuuvvwwxxyyzz", 2) == true));
    assert((sol.hasSpecialSubstring("aabbbcccddd", 3) == true));
    assert((sol.hasSpecialSubstring("ababababababababababababababababab", 3) == false));
    assert((sol.hasSpecialSubstring("zzzzzazzzzz", 5) == true));

    cout << "All tests passed for find-special-substring-of-length-k" << endl;
    return 0;
}
