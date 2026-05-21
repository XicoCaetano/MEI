#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    int calc(const string& s, const string& t) {
        int n = s.size(), m = t.size();

        // Precompute palindrome tables for s and t
        vector<vector<bool>> ps(n, vector<bool>(n, false));
        vector<vector<bool>> pt(m, vector<bool>(m, false));
        for (int i = 0; i < n; i++) ps[i][i] = true;
        for (int i = 0; i < m; i++) pt[i][i] = true;
        for (int i = 0; i+1 < n; i++) if (s[i]==s[i+1]) ps[i][i+1] = true;
        for (int i = 0; i+1 < m; i++) if (t[i]==t[i+1]) pt[i][i+1] = true;
        for (int len = 3; len <= n; len++)
            for (int i = 0; i+len-1 < n; i++)
                ps[i][i+len-1] = (s[i]==s[i+len-1] && ps[i+1][i+len-2]);
        for (int len = 3; len <= m; len++)
            for (int i = 0; i+len-1 < m; i++)
                pt[i][i+len-1] = (t[i]==t[i+len-1] && pt[i+1][i+len-2]);

        // g[p] = longest palindrome in s[p..n-1]
        vector<int> g(n+1, 0);
        for (int p = n-1; p >= 0; p--) {
            g[p] = g[p+1];
            for (int j = p; j < n; j++)
                if (ps[p][j]) g[p] = max(g[p], j-p+1);
        }

        // f[q] = longest palindrome in t[0..q]
        vector<int> f(m, 0);
        for (int q = 0; q < m; q++) {
            f[q] = (q > 0 ? f[q-1] : 0);
            for (int i = 0; i <= q; i++)
                if (pt[i][q]) f[q] = max(f[q], q-i+1);
        }

        // Base: best pure-s or pure-t palindrome
        int res = max(g[0], f[m-1]);
        
        vector<vector<int>> ml(n, vector<int>(m, 0));
        for (int u = 0; u < n; u++) {
            for (int v = m-1; v >= 0; v--) {
                if (s[u] == t[v])
                    ml[u][v] = (u > 0 && v+1 < m ? ml[u-1][v+1] : 0) + 1;
                int k = ml[u][v];
                if (k > 0) {
                    res = max(res, 2*k + g[u+1]);
                    res = max(res, 2*k + (v > 0 ? f[v-1] : 0));
                }
            }
        }
        return res;
    }

    int longestPalindrome(string s, string t) {
        return calc(s, t);
    }
};