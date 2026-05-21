#include <vector>
#include <string>
#include <unordered_map>
#include <set>

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
            if (node->count == k) {
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
    vector<int> longestCommonPrefix(vector<string>& words, int k) {
        int n = words.size();
        vector<int> answer(n, 0);
        
        // If removing one element leaves fewer than k elements, the result is 0.
        if (n - 1 < k) {
            return answer;
        }

        Trie trie(k);
        // Initially insert all words into the Trie
        for (const string& word : words) {
            trie.insert(word);
        }

        // For each index i, remove word[i], get the result, then re-insert word[i]
        for (int i = 0; i < n; ++i) {
            trie.erase(words[i]);
            answer[i] = trie.getLongestCommonPrefix();
            trie.insert(words[i]);
        }

        return answer;
    }
};