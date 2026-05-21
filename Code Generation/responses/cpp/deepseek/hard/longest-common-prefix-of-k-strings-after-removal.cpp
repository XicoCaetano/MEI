#include <vector>
#include <string>
#include <unordered_map>
#include <set>
#include <algorithm>

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
        vector<int> ans(n, 0);
        
        if (k > n) return ans;
        
        Trie trie(k);
        
        // Insert all words into the trie
        for (const string& word : words) {
            trie.insert(word);
        }
        
        // For each index, remove that word, get longest prefix, then re-insert
        for (int i = 0; i < n; ++i) {
            trie.erase(words[i]);
            ans[i] = trie.getLongestCommonPrefix();
            trie.insert(words[i]);
        }
        
        return ans;
    }
};