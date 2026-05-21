class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        def longest_palindromic_substring(text):
            n = len(text)
            best = {}
            # DP table: dp[i][j] = True if text[i..j] is palindrome
            dp = [[False] * n for _ in range(n)]
            for i in range(n):
                dp[i][i] = True
            for length in range(2, n + 1):
                for i in range(n - length + 1):
                    j = i + length - 1
                    if length == 2:
                        dp[i][j] = (text[i] == text[j])
                    else:
                        dp[i][j] = (text[i] == text[j] and dp[i+1][j-1])
            return dp

        def lcs_length(a, b):
            # Returns DP table where lcs[i][j] = LCS length of a[:i] and b[:j]
            m, n = len(a), len(b)
            dp = [[0] * (n + 1) for _ in range(m + 1)]
            for i in range(1, m + 1):
                for j in range(1, n + 1):
                    if a[i-1] == b[j-1]:
                        dp[i][j] = dp[i-1][j-1] + 1
                    else:
                        dp[i][j] = max(dp[i-1][j], dp[i][j-1])
            return dp

        # We pick substring s[i..j] and t[p..q], concatenate to form s[i..j]+t[p..q]
        # This needs to be a palindrome.
        # 
        # Key insight: s_sub + t_sub is palindrome means it equals its reverse = rev(t_sub) + rev(s_sub)
        # 
        # Strategy: 
        # 1. Try all palindromic substrings of s alone, palindromic substrings of t alone
        # 2. For combined: s_sub + t_sub is palindrome
        #    The combined string of length L is palindrome if combined[k] == combined[L-1-k]
        #
        # Better approach using the structure:
        # If s[i..i+k-1] concatenated with t[j..j+m-1] is a palindrome,
        # consider matching from outside in.
        #
        # Efficient approach: 
        # For each prefix of s and suffix of t that form matching pairs from outside,
        # plus check if the middle part is a palindrome.
        
        n, m = len(s), len(t)
        t_rev = t[::-1]
        
        # dp_s[i][j] = True if s[i..j] is palindrome
        dp_s = longest_palindromic_substring(s)
        # dp_t[i][j] = True if t[i..j] is palindrome  
        dp_t = longest_palindromic_substring(t)
        
        best = 1  # At minimum, single character palindrome exists
        
        # Check pure palindromes in s or t
        for i in range(n):
            for j in range(i, n):
                if dp_s[i][j]:
                    best = max(best, j - i + 1)
        for i in range(m):
            for j in range(i, m):
                if dp_t[i][j]:
                    best = max(best, j - i + 1)
        
        # For combined s[0..i] + t[j..m-1] type structures:
        # We want to find max length where we take a prefix of s and suffix of t
        # such that the concatenation is a palindrome.
        # 
        # Approach: fix how many chars from s prefix match t suffix (from outside in),
        # then check if the remaining middle is a palindrome.
        
        # Use LCS on s and reversed t to find matching prefixes/suffixes
        # lcs_dp[i][j] = length of longest common prefix of s[:i] and t_rev[:j]
        # Actually we need: longest k such that s[0..k-1] == t[m-k..m-1] (reversed)
        
        # For each possible "outer shell" length k (s[0..k-1] matches rev of t[m-k..m-1]):
        # i.e., s[:k] == t[m-k:][::-1]
        # Then the middle can be any palindrome from s[k..n-1] or t[0..m-k-1]
        
        # Precompute: for each i in s, j in t_rev, longest common extension
        # lcp[i][j] = length of longest common prefix of s[i:] and t_rev[j:]
        lcp = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            for j in range(m - 1, -1, -1):
                if s[i] == t_rev[j]:
                    lcp[i][j] = lcp[i+1][j+1] + 1
                else:
                    lcp[i][j] = 0
        
        # Best palindrome in s[k:] 
        best_s_suffix = [0] * (n + 1)  # best_s_suffix[k] = longest palindrome in s[k:]
        for k in range(n - 1, -1, -1):
            best_s_suffix[k] = best_s_suffix[k+1]
            for j in range(k, n):
                if dp_s[k][j]:
                    best_s_suffix[k] = max(best_s_suffix[k], j - k + 1)
        
        # Best palindrome in t[:q] (t[0..q-1])
        best_t_prefix = [0] * (m + 1)  # best_t_prefix[q] = longest palindrome in t[:q]
        for q in range(1, m + 1):
            best_t_prefix[q] = best_t_prefix[q-1]
            for i in range(q):
                if dp_t[i][q-1]:
                    best_t_prefix[q] = max(best_t_prefix[q], q - i)
        
        # Now try all possible outer shell lengths
        # The outer shell: s[0..k-1] matches reverse of t[m-k..m-1]
        # i.e., s[si] == t_rev[m-1-(m-k)+...] = t_rev[k-1-si+...] hmm let me re-think
        
        # s[0..k-1] concatenated with t[m-k..m-1]: this is palindrome if s[0..k-1] == rev(t[m-k..m-1])
        # rev(t[m-k..m-1]) = t_rev[0..k-1]
        # So we need s[0..k-1] == t_rev[0..k-1], i.e., lcp[0][0] >= k
        
        max_outer = lcp[0][0]  # maximum k where s[:k] == t_rev[:k]
        
        for k in range(0, min(max_outer, n, m) + 1):
            # outer shell of size k on each side: contributes 2*k to length
            # middle from s[k:] best palindrome OR middle from t[:m-k] best palindrome
            mid = max(best_s_suffix[k], best_t_prefix[m - k])
            best = max(best, 2 * k + mid)
        
        return best