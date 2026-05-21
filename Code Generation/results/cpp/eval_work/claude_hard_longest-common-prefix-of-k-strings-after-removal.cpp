// task_id: longest-common-prefix-of-k-strings-after-removal
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


struct TrieNode {
    unordered_map<char, TrieNode*> children;
    int count = 0;
};

class Trie {
public:
    int k;
    TrieNode* root;
    unordered_map<int, int> prefixLengthsCount;
    set<int, greater<int>> prefixLengths;
    Trie(int k_) : k(k_), root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < (int)word.size(); ++i) {
            char c = word[i];
            int sz = i + 1;
            auto it = node->children.find(c);
            if (it == node->children.end()) {
                TrieNode* nn = new TrieNode();
                node->children[c] = nn;
                node = nn;
            } else {
                node = it->second;
            }
            node->count += 1;
            if (node->count >= k) {
                prefixLengthsCount[sz] += 1;
                if (prefixLengthsCount[sz] == 1) {
                    prefixLengths.insert(sz);
                }
            }
        }
    }

    void erase(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < (int)word.size(); ++i) {
            char c = word[i];
            int sz = i + 1;
            node = node->children[c];
            if (node->count == k) {
                prefixLengthsCount[sz] -= 1;
                if (prefixLengthsCount[sz] == 0) {
                    prefixLengths.erase(sz);
                }
            }
            node->count -= 1;
        }
    }

    int getLongestCommonPrefix() {
        if (prefixLengths.empty()) return 0;
        return *prefixLengths.begin();
    }
};


// === MODEL RESPONSE ===
#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    unordered_map<char, TrieNode*> children;
    int count = 0;
};

class Trie {
public:
    int k;
    TrieNode* root;
    unordered_map<int, int> prefixLengthsCount;
    set<int, greater<int>> prefixLengths;
    Trie(int k_) : k(k_), root(new TrieNode()) {}

    void insert(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < (int)word.size(); ++i) {
            char c = word[i];
            int sz = i + 1;
            auto it = node->children.find(c);
            if (it == node->children.end()) {
                TrieNode* nn = new TrieNode();
                node->children[c] = nn;
                node = nn;
            } else {
                node = it->second;
            }
            node->count += 1;
            if (node->count >= k) {
                prefixLengthsCount[sz] += 1;
                if (prefixLengthsCount[sz] == 1) {
                    prefixLengths.insert(sz);
                }
            }
        }
    }

    void erase(const string& word) {
        TrieNode* node = root;
        for (int i = 0; i < (int)word.size(); ++i) {
            char c = word[i];
            int sz = i + 1;
            node = node->children[c];
            if (node->count == k) {
                prefixLengthsCount[sz] -= 1;
                if (prefixLengthsCount[sz] == 0) {
                    prefixLengths.erase(sz);
                }
            }
            node->count -= 1;
        }
    }

    int getLongestCommonPrefix() {
        if (prefixLengths.empty()) return 0;
        return *prefixLengths.begin();
    }
};

class Solution {
public:
    vector<int> longestCommonPrefix(vector<string> words, int k) {
        int n = words.size();
        vector<int> answer(n, 0);
        
        if (n - 1 < k) return answer;
        
        Trie trie(k);
        for (const string& w : words) trie.insert(w);
        
        for (int i = 0; i < n; i++) {
            trie.erase(words[i]);
            answer[i] = trie.getLongestCommonPrefix();
            trie.insert(words[i]);
        }
        
        return answer;
    }
};

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.longestCommonPrefix(vector<string>{"banana", "band", "bend", "bendy"}, 3) == vector<int>{1, 1, 1, 1}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abce", "abcf", "abcg"}, 2) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"apple", "application", "aptitude", "appetite"}, 3) == vector<int>{2, 2, 3, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"aaa", "aa", "a"}, 2) == vector<int>{1, 1, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "aaa", "aa", "a"}, 2) == vector<int>{2, 2, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"jump", "run", "run", "jump", "run"}, 2) == vector<int>{3, 4, 4, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"apple", "application", "appetite"}, 2) == vector<int>{3, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdefg", "abcde", "abcd", "abc", "ab", "a"}, 4) == vector<int>{2, 2, 2, 2, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "a", "a", "a", "a"}, 3) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "ab", "abcde"}, 3) == vector<int>{2, 2, 3, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"dog", "racer", "car"}, 2) == vector<int>{0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "he", "h"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abcde", "ab", "abc"}, 3) == vector<int>{2, 2, 3, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abcde", "abcdef"}, 3) == vector<int>{4, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"cat", "cater", "category", "catalog"}, 2) == vector<int>{4, 3, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "preface", "prefatory", "presentation"}, 3) == vector<int>{3, 4, 3, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "banan", "ban", "ba", "b", "bananaaa", "bananas"}, 3) == vector<int>{5, 6, 6, 6, 6, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdabcd", "abcdabc", "abcdab", "abcd", "abc", "ab", "a"}, 4) == vector<int>{3, 3, 3, 3, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"programming", "program", "programmer", "programmatic"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"interview", "inter", "internal", "interpretation", "internet"}, 3) == vector<int>{5, 5, 5, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "preface", "preference", "pre", "predict", "prevent", "preach", "prelude"}, 4) == vector<int>{3, 3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "he", "helloworld", "he"}, 4) == vector<int>{2, 2, 2, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"algorithm", "algorithms", "algo", "al", "algorith"}, 3) == vector<int>{4, 4, 8, 8, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"sequence", "sequential", "succession", "successive", "succeed"}, 4) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.longestCommonPrefix(vector<string>{"optimization", "optimize", "optimal", "optimum"}, 3) == vector<int>{5, 5, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"zebra", "zebra", "zebra", "zebra", "zebra"}, 4) == vector<int>{5, 5, 5, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "bandana", "band", "bandwidth"}, 3) == vector<int>{4, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdefgh", "abcde", "abcd", "abc", "ab", "a"}, 3) == vector<int>{3, 3, 3, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"same", "sam", "sameple", "sample", "samp"}, 3) == vector<int>{3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "preface", "preach", "prelude"}, 3) == vector<int>{3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"xxxxxxxxxx", "xxxxxxxxx", "xxxxxxxx", "xxxxxxx", "xxxxxx", "xxxxx", "xxxx", "xxx", "xx", "x"}, 5) == vector<int>{5, 5, 5, 5, 5, 6, 6, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"performance", "perform", "performanceanalysis", "performant"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"programming", "programmer", "program", "pro", "pr", "p"}, 2) == vector<int>{7, 7, 8, 8, 8, 8}));
    assert((sol.longestCommonPrefix(vector<string>{"abcabcabc", "abcabc", "abc", "ab", "a"}, 2) == vector<int>{3, 3, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"test", "testing", "tested", "tests", "tempest"}, 4) == vector<int>{2, 2, 2, 2, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"longest", "longer", "long", "lon", "lo", "l"}, 3) == vector<int>{3, 3, 3, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdabcd", "abcdabcde", "abcdabc", "abcdab", "abcd"}, 3) == vector<int>{6, 6, 6, 7, 7}));
    assert((sol.longestCommonPrefix(vector<string>{"algorithm", "algebra", "algorithmic", "algae"}, 2) == vector<int>{3, 9, 3, 9}));
    assert((sol.longestCommonPrefix(vector<string>{"mississippi", "mississipp", "mississip", "mississi", "mississ", "missis", "missi", "miss", "mis", "mi", "m"}, 5) == vector<int>{6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7}));
    assert((sol.longestCommonPrefix(vector<string>{"unique", "unite", "unity", "unit", "universe"}, 3) == vector<int>{4, 3, 3, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz", "abcdefghijklmnopqrstuvwxyz"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"abacaxi", "abacax", "abac", "aba", "ab"}, 2) == vector<int>{4, 4, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"communication", "communicate", "communicator", "communications"}, 3) == vector<int>{10, 10, 10, 10}));
    assert((sol.longestCommonPrefix(vector<string>{"common", "commonly", "commonsense", "commonplace", "commonwealth"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "predefined", "premier", "pressure"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "bandana", "banter", "bandage", "banner", "bandwidth"}, 5) == vector<int>{3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"sun", "sunny", "sunshine", "sunset", "sunken", "sunflower", "sunrise", "sundial"}, 3) == vector<int>{3, 3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"}, 2) == vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"test", "testing", "tested", "testify", "testament"}, 4) == vector<int>{4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abcde", "abcdef", "abcdefg"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "prefixing", "prefixation", "prefix", "pre"}, 3) == vector<int>{6, 6, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"algorithm", "algebra", "algorithmic", "algorithmically", "algebraic"}, 4) == vector<int>{3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "bananas", "bandana", "bandanas", "band"}, 4) == vector<int>{3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"cat", "cater", "category", "catalog", "catalogue", "catalogued", "cataloging"}, 6) == vector<int>{3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"xylophone", "xylography", "xylophon", "xylo", "xy", "x"}, 3) == vector<int>{4, 4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"inter", "interact", "interactive", "interface", "interleave", "interchange", "interconnect", "intercept", "interdependent"}, 7) == vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"cloud", "cloudy", "cloudstorage", "cloudservices"}, 3) == vector<int>{5, 5, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"abacaxi", "abacax", "abaca", "abac", "aba", "ab", "a"}, 4) == vector<int>{3, 3, 3, 3, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abacaxi", "banana", "abacax", "bacana", "bacaxa"}, 3) == vector<int>{2, 0, 2, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "preface", "prefect", "prefer", "prelude"}, 4) == vector<int>{3, 3, 3, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"algorithm", "algebra", "algorithmic", "algal", "algae", "algorithmically", "algorithmically"}, 5) == vector<int>{3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"aabbcc", "aabb", "aab", "aa", "a"}, 3) == vector<int>{2, 2, 2, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "bandana", "band", "bandit", "bandwidth"}, 4) == vector<int>{4, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "helo", "hallo", "heaven"}, 3) == vector<int>{2, 2, 2, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"intersection", "inter", "interact", "interactive"}, 2) == vector<int>{8, 8, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"datastructure", "data", "database", "dataanalysis"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "bandana", "band", "bandanna", "bang", "ban", "banner"}, 3) == vector<int>{4, 3, 3, 3, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "helo", "hella", "hellomy", "hellomyworld"}, 4) == vector<int>{4, 4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"programming", "program", "pro", "process", "processor"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"programming", "programmer", "procrastinate", "profession", "process"}, 4) == vector<int>{3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"elephant", "elephante", "elephant", "elephant", "eleph", "ele", "e"}, 3) == vector<int>{8, 8, 8, 8, 8, 8, 8}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "flew", "flour"}, 2) == vector<int>{3, 3, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"elephant", "elephant", "elephant", "elephant", "elephant", "elephant"}, 5) == vector<int>{8, 8, 8, 8, 8, 8}));
    assert((sol.longestCommonPrefix(vector<string>{"different", "difficult", "difficulty", "differently", "differ"}, 4) == vector<int>{4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"programming", "program", "programmer", "programm", "programmi", "programmin", "programmin"}, 4) == vector<int>{8, 9, 9, 9, 8, 8, 8}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdefg", "abcdef", "abcde", "abcd", "abc"}, 2) == vector<int>{5, 5, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"test", "testing", "tested", "testing", "testify", "testament"}, 3) == vector<int>{5, 4, 5, 4, 4, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdefghij", "abcdefghi", "abcdefgh", "abcdefg", "abcdef", "abcde", "abcd", "abc", "ab", "a"}, 5) == vector<int>{5, 5, 5, 5, 5, 6, 6, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"supercalifragilisticexpialidocious", "super", "supercalifragilistic", "superex", "supercalifragil"}, 4) == vector<int>{5, 5, 5, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"algorithm", "algebra", "algorithmic", "alibi", "alias"}, 2) == vector<int>{3, 9, 3, 9, 9}));
    assert((sol.longestCommonPrefix(vector<string>{"aabbcc", "aabb", "aabc", "aab", "aac", "aa", "ab", "ac", "a"}, 3) == vector<int>{3, 3, 3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "prefixes", "prefixing", "pref", "pre"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "band", "ban", "bandana", "bandwidth"}, 3) == vector<int>{4, 3, 4, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "flew", "fly"}, 4) == vector<int>{2, 2, 2, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abcde", "ab", "abc", "a", "abca", "abcd"}, 4) == vector<int>{3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"repeated", "repeat", "repetition", "repetitive", "repel"}, 3) == vector<int>{4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "flock", "flour", "flat", "flog"}, 3) == vector<int>{3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "precondition", "preference"}, 3) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"repeated", "repeatedly", "rep", "repeat", "repe"}, 3) == vector<int>{4, 4, 6, 4, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "flour", "flourish", "flourish", "flourish"}, 5) == vector<int>{3, 3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "predict", "precondition", "prevent", "precedent"}, 4) == vector<int>{3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"xylophone", "xenon", "xylography", "xylo", "xylophoneography"}, 2) == vector<int>{4, 9, 9, 9, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"small", "smaller", "smallest", "smallests", "smallestest"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"distinct", "distinguish", "distant", "distortion", "distract", "distrust"}, 4) == vector<int>{4, 4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"unique", "uniqueness", "un", "uniq", "uniquer"}, 4) == vector<int>{2, 2, 4, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"aaa", "bbb", "aaa", "bbb", "aaa", "bbb"}, 3) == vector<int>{3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"test", "testing", "tested", "testing", "testify"}, 2) == vector<int>{7, 5, 7, 5, 7}));
    assert((sol.longestCommonPrefix(vector<string>{"programming", "program", "programmer", "pro", "programming"}, 3) == vector<int>{7, 8, 7, 8, 7}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaaa", "aaa", "aa", "a", "abcd", "abc", "ab", "a"}, 3) == vector<int>{2, 2, 2, 2, 2, 2, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abcde", "abcdef", "abcdefg", "abcdefgh", "abcdefghi"}, 5) == vector<int>{5, 4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"algorithm", "algori", "algor", "algo", "alg", "al", "a", "algorithmic", "algorith", "algorithmically"}, 6) == vector<int>{4, 4, 4, 5, 5, 5, 5, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"consistent", "consistency", "consist", "cons", "con", "co", "c"}, 3) == vector<int>{4, 4, 4, 7, 7, 7, 7}));
    assert((sol.longestCommonPrefix(vector<string>{"civic", "civ", "city", "citizens", "citizen", "citize", "citizi"}, 5) == vector<int>{3, 3, 2, 2, 2, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaab", "aaab", "aab", "ab", "b"}, 2) == vector<int>{2, 2, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"consistent", "consistency", "consist", "cons", "con"}, 3) == vector<int>{4, 4, 4, 7, 7}));
    assert((sol.longestCommonPrefix(vector<string>{"abacaxi", "abacax", "abac", "aba", "ab", "a"}, 5) == vector<int>{1, 1, 1, 1, 1, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"supercalifragilisticexpialidocious", "super", "supercal", "supercali", "superca"}, 2) == vector<int>{8, 9, 9, 8, 9}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "bandana", "band", "ban", "ba", "b"}, 3) == vector<int>{3, 3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"aabbcc", "aabbc", "aabb", "aab", "aa", "a"}, 4) == vector<int>{2, 2, 2, 2, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"longest", "longer", "long", "lo", "l", "longestword"}, 4) == vector<int>{2, 2, 2, 4, 4, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"repetition", "rep", "repet", "repetit", "repetiti"}, 3) == vector<int>{5, 7, 7, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"test", "testing", "tested", "tes"}, 3) == vector<int>{3, 3, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "pref", "prefer"}, 3) == vector<int>{3, 4, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abce", "abcf"}, 2) == vector<int>{3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abc", "ab", "a"}, 3) == vector<int>{1, 1, 1, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "heaven", "heavy"}, 2) == vector<int>{4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abce", "abcf", "abcg"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaaa", "aaaab", "aaabb", "aabbb", "abbbb"}, 3) == vector<int>{2, 2, 2, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"dog", "racer", "car"}, 2) == vector<int>{0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "b", "c", "d", "e"}, 1) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "world", "help", "hero"}, 2) == vector<int>{2, 3, 2, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"interspecies", "interstellar", "interstate"}, 2) == vector<int>{7, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"one", "once", "on", "oneone"}, 2) == vector<int>{2, 3, 3, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"abcde", "abcdf", "abcda", "abcdz"}, 3) == vector<int>{4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "aaa", "aa", "a"}, 3) == vector<int>{1, 1, 1, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "preface", "prefer", "preach"}, 2) == vector<int>{4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abcde", "abcdef", "abcdefg"}, 4) == vector<int>{4, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abcde", "abcdef"}, 2) == vector<int>{5, 5, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "flute"}, 3) == vector<int>{2, 2, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "floor"}, 2) == vector<int>{3, 3, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abce", "abcf"}, 2) == vector<int>{3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight"}, 2) == vector<int>{2, 2, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abcde"}, 3) == vector<int>{0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "help", "hold"}, 2) == vector<int>{1, 1, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abcde", "abcdef"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"test", "taste", "testing", "temple"}, 2) == vector<int>{2, 4, 2, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"apple", "applet", "application"}, 3) == vector<int>{0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "a", "a", "a", "a"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"}, 4) == vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"aaa", "aa", "a"}, 2) == vector<int>{1, 1, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "he", "h"}, 2) == vector<int>{2, 2, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "flour"}, 3) == vector<int>{2, 2, 3, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abcde"}, 3) == vector<int>{0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "preform", "preference", "prelude"}, 3) == vector<int>{3, 3, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "a", "a", "a", "a"}, 2) == vector<int>{1, 1, 1, 1, 1}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "pref", "prefer", "prefi"}, 4) == vector<int>{3, 4, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"apple", "application", "apt", "appetite"}, 3) == vector<int>{2, 2, 3, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "pref", "prefer"}, 2) == vector<int>{4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"}, 3) == vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"distinct", "words", "only", "here"}, 3) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abc", "abc", "abc", "abc"}, 5) == vector<int>{0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "flour"}, 2) == vector<int>{3, 3, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "aaab", "aaac", "aabb"}, 3) == vector<int>{2, 2, 2, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"abcde", "abcdf", "abcda", "abcdb"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcde", "abcdf"}, 3) == vector<int>{0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"flower", "flow", "flight", "fluent"}, 3) == vector<int>{2, 2, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"a"}, 1) == vector<int>{0}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abcde", "abcdef", "abcdefg", "abcdefgh"}, 2) == vector<int>{7, 7, 7, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaaa", "aaaab", "aaabb", "aabbb", "abbbb"}, 4) == vector<int>{1, 1, 1, 1, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"same", "same", "same"}, 2) == vector<int>{4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "aa", "aaa", "a", "aaaaa"}, 2) == vector<int>{3, 4, 4, 4, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"aabb", "aabc", "aabd", "aabe"}, 3) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"distinct", "words", "are", "here"}, 2) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"abc", "abcd", "abce", "abcdef"}, 3) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "prepend", "presume"}, 3) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"throne", "throne", "throne", "throne"}, 3) == vector<int>{6, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "prefix", "prefix", "prefix", "prefix"}, 4) == vector<int>{6, 6, 6, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"abab", "aba", ""}, 2) == vector<int>{0, 0, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"test", "testing", "testcase", "testing", "testcases"}, 3) == vector<int>{4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"apple", "application", "appetite", "appreciate"}, 3) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "he", "h"}, 3) == vector<int>{1, 1, 1, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abc", "ab", "a"}, 2) == vector<int>{2, 2, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"banana", "bandana", "ban", "band", "bandana"}, 4) == vector<int>{3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"interspecies", "interstellar", "interstate"}, 3) == vector<int>{0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "aa", "aaa", "aaaaa"}, 3) == vector<int>{2, 3, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"apple", "application", "app", "applet", "apples"}, 2) == vector<int>{5, 5, 5, 5, 5}));
    assert((sol.longestCommonPrefix(vector<string>{"abcd", "abce", "abcf", "abcg"}, 3) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "a", "a", "a"}, 2) == vector<int>{1, 1, 1, 1}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "he", "helloworld"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "preface", "presentation", "preference", "prestige"}, 4) == vector<int>{3, 3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "predict", "printing"}, 2) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "a", "a", "a", "a", "a", "a", "a", "a", "a"}, 5) == vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "aabb", "aabc", "aacc"}, 3) == vector<int>{2, 2, 2, 2}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "bbbb", "cccc", "dddd"}, 2) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"apple", "app", "application", "appetite"}, 2) == vector<int>{3, 4, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"jump", "run", "run", "jump", "run"}, 2) == vector<int>{3, 4, 4, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"a", "b", "c", "d", "e", "f", "g", "h", "i", "j"}, 5) == vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"same", "same", "same", "same"}, 2) == vector<int>{4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"abcdefg", "abcdef", "abcde", "abcd"}, 2) == vector<int>{5, 5, 6, 6}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "preform", "president", "presentation"}, 2) == vector<int>{4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"aaaa", "aaaa", "aaaa", "aaaa"}, 4) == vector<int>{0, 0, 0, 0}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "he", "hell", "helper"}, 2) == vector<int>{3, 4, 3, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "pref", "prefer", "preference"}, 4) == vector<int>{3, 4, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"prefix", "pre", "prepend", "prevent"}, 3) == vector<int>{3, 3, 3, 3}));
    assert((sol.longestCommonPrefix(vector<string>{"same", "same", "same", "same", "same"}, 4) == vector<int>{4, 4, 4, 4, 4}));
    assert((sol.longestCommonPrefix(vector<string>{"hello", "hell", "heaven", "heavy"}, 3) == vector<int>{2, 2, 2, 2}));

    cout << "All tests passed for longest-common-prefix-of-k-strings-after-removal" << endl;
    return 0;
}
