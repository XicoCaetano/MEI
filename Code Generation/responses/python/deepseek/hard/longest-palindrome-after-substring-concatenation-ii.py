class Solution:
    def longestPalindrome(self, s: str, t: str) -> int:
        n, m = len(s), len(t)
        
        # Helper to find longest palindromic substring in a single string
        def longest_pal_substring(st):
            if not st:
                return 0
            L = len(st)
            # Expand around center approach
            max_len = 1
            for center in range(L):
                # Odd length
                l, r = center, center
                while l >= 0 and r < L and st[l] == st[r]:
                    max_len = max(max_len, r - l + 1)
                    l -= 1
                    r += 1
                # Even length
                l, r = center, center + 1
                while l >= 0 and r < L and st[l] == st[r]:
                    max_len = max(max_len, r - l + 1)
                    l -= 1
                    r += 1
            return max_len
        
        # Precompute longest palindromic substring for all prefixes of s and suffixes of t
        pal_s = [[False] * n for _ in range(n)]
        pal_t = [[False] * m for _ in range(m)]
        
        # Palindromes in s
        for i in range(n):
            pal_s[i][i] = True
        for i in range(n - 1):
            pal_s[i][i + 1] = (s[i] == s[i + 1])
        for length in range(3, n + 1):
            for i in range(n - length + 1):
                j = i + length - 1
                pal_s[i][j] = (s[i] == s[j] and pal_s[i + 1][j - 1])
        
        # Palindromes in t
        for i in range(m):
            pal_t[i][i] = True
        for i in range(m - 1):
            pal_t[i][i + 1] = (t[i] == t[i + 1])
        for length in range(3, m + 1):
            for i in range(m - length + 1):
                j = i + length - 1
                pal_t[i][j] = (t[i] == t[j] and pal_t[i + 1][j - 1])
        
        # Start with max palindrome from s or t alone
        ans = 1
        for i in range(n):
            for j in range(i, n):
                if pal_s[i][j]:
                    ans = max(ans, j - i + 1)
        for i in range(m):
            for j in range(i, m):
                if pal_t[i][j]:
                    ans = max(ans, j - i + 1)
        
        # Now consider concatenated palindromes
        # We'll check for each possible mid point where s part ends and t part begins
        # Let's try all ways to split into s_sub + t_sub that form a palindrome
        # We can think of trying to expand outwards from some center that spans the join
        
        # Precompute reverse of t for easier matching
        t_rev = t[::-1]
        
        # For each possible split between s and t
        # Consider all pairs (i, j) where i is index in s, j is index in t_rev
        # But more systematically: find longest chain where s[l:r] + t[a:b] is palindrome
        # This is equivalent to: we want s[l..r-1] + t[a..b-1] to be palindrome
        # The palindrome can be centered at the join, or entirely within one string
        
        # Better approach: try all possible centers that cross the boundary
        # For each possible split point, expand outwards checking s part and t part together
        
        # Let's try: for each i from 0 to n (end index in s, exclusive)
        # and for each j from m down to 0 (start index in t, inclusive)
        # we can expand outwards from this "middle point" where s[i-1] and t[j] are adjacent in palindrome
        
        # We'll generate all possible contiguous s_sub + t_sub strings by taking s[l..r] and t[a..b]
        # But we can check palindrome property without constructing the string
        # We'll check if s[l..r] + t[a..b] is palindrome by comparing from both ends
        
        # Let's try all possible lengths and positions
        # For each possible split between s and t (i where s part ends, and j where t part starts)
        # We'll expand outward checking that characters match
        
        # Initialize ans with already found palindromes
        # Now try combinations where we take parts from both strings
        
        # Generate all possible s_sub + t_sub strings by trying all start and end combinations
        # But O(n^2 * m^2) is too slow (10^12)
        
        # We need O(n*m) solution
        
        # Let's try: for each i from 0 to n (end index in s, exclusive)
        # and for each j from 0 to m-1 (start index in t, inclusive)
        # we check if we can form a palindrome by taking s[:i] and t[j:] matched from ends
        # Actually we want consecutive pieces
        
        # Let's try dynamic programming: dp[i][j] = length of longest palindrome starting with s[i] and ending at t[j] 
        # But that's tricky because palindrome can start and end in either string
        
        # Alternative: for each possible center (which could be between characters or at a character)
        # try to expand as far as possible, using s to the left and t to the right or vice versa
        
        # Let's try expanding outward from a point between s and t
        # Consider all ways to choose a substring from s (a..b) and from t (c..d)
        # Combined string is s[a:b+1] + t[c:d+1]
        # We want this to be palindrome
        
        # Try all possible pairs (i, j) where i is start in s, j is end in t
        # And expand outward matching characters
        # We'll consider building palindrome by expanding from the center outward
        
        # For each possible center point (between chars or at a char)
        # We'll try to expand using s for left part and t for right part
        
        # Precompute for s: longest palindrome starting at index i going leftwards
        # Precompute for t: longest palindrome ending at index j going rightwards
        # But we need both directions
        
        # Let's try an exhaustive but efficient approach:
        # For each i in range(n): for each j in range(m): try to match s[i] with t[j] as the outermost characters
        # Then expand inward
        
        # We can think of building palindrome by taking some prefix from s and some suffix from t
        
        for i in range(n):
            for j in range(m):
                if s[i] == t[j]:
                    # Try to expand from this outer pair
                    l, r = i, j
                    # This pair becomes part of a longer palindrome
                    # We'll try to match characters outward: s[l-1] with t[r+1], etc.
                    # But we need contiguous sections: either l moves left in s or moves right? Wait
                    # We want s[a..i] + t[j..b] to be palindrome
                    # So s[a..i] and t[j..b] must be symmetric
                    # That means if we match s[i] with t[j], then next we match s[i-1] with t[j+1] or s[i-1] with s[i-2]? No
                    # For concatenated string, the left part comes entirely from s, right part entirely from t
                    # So the palindrome structure is: s[left..i] + t[j..right] is palindrome
                    # This means: s[left..i] is the mirror of t[j..right]
                    # So we can expand outward from the pair (i, j) by matching s[i-k] with t[j+k]
                    # As long as we don't go out of bounds
                    k = 0
                    # First, try to match as many characters as possible outward
                    total_len = 0
                    # But we can also stop early if we find a mismatch
                    # Let's expand both directions
                    
                    # We'll try all possible extensions
                    # For each possible expansion length L
                    # Check if for all p in 0..L-1, s[i-p] == t[j+p] (if within bounds)
                    # Then this gives a palindrome of length 2*(L) (if we take full s[i-L+1..i] and t[j..j+L-1])
                    # Actually we need to also consider odd length palindromes centered at the join
                    
                    # Also need to consider palindromes where one side is longer than the other (has inner palindrome)
                    
        # This is getting complex. Let's use a simpler O(n*m*min(n,m)) approach:
        # For each i in range(n): for each j in range(m):
        #   Try to form palindrome using s[i:...] and t[...:j] concatenated
        
        # Generate all possible s_sub and t_sub
        # Check if s_sub + t_sub is palindrome
        
        # Store results in a set?
        
        # Let's just implement the O(n*m*min(n,m)) approach which is feasible since n,m<=1000
        # Actually O(n^2 * m^2) is too big, but O(n*m*min(n,m)) might be okay for 1000? 1000^3 = 10^9 too big
        # We need O(n*m)
        
        # Let's try dynamic programming: dp[i][j] = length of longest palindrome where s[i:] and t[:j] match
        # But that's not quite right
        
        # Let's use precomputed LCP (Longest Common Prefix) arrays
        # Precompute for all pairs (i,j) the length of longest common prefix of s[i:] and t_rev[j:]
        lcp_forward = [[0]*(m+1) for _ in range(n+1)]
        for i in range(n-1, -1, -1):
            for j in range(m-1, -1, -1):
                if s[i] == t[j]:
                    lcp_forward[i][j] = 1 + lcp_forward[i+1][j+1]
        
        # Now, for each possible center between s and t
        # Consider a palindrome where left part is from s, right part from t
        # Let's try all possible i where left part ends at i in s, and right part starts at j in t
        # The palindrome could be:
        # Option 1: Even length centered between s[i] and t[j] -> need s[i] == t[j] and then match outward
        # Option 2: Odd length centered at a character (either s[i] or t[j])
        
        # Try even length palindromes cross-boundary:
        for i in range(n):
            for j in range(m):
                if s[i] == t[j]:
                    # This pair is the center of an even-length palindrome
                    # Expand outward: s[i-k] should equal t[j+k] for k=1,2,...
                    # Use lcp_forward to get how many matches
                    matching = lcp_forward[i][j]  # This gives the number of pairs we can match
                    # Each pair gives 2 characters: s[i] and t[j] is one pair, then s[i-1] and t[j+1] is next, etc.
                    # So total length = 2 * matching
                    ans = max(ans, 2 * matching)
        
        # Try odd length palindromes centered at s[i]
        # That means the palindrome is s[i] in middle, then expand left in s and right in t
        for i in range(n):
            # Check if there exists t[j] to start expansion
            # Actually odd length centered at s[i] means s[i] is middle, then left part is s[i-1..a], right part is t[b..j]
            # But we need contiguous sections
            # The palindrome structure: s[i-k..i] + t[j..j+k-1] with condition s[i-k..i-1] reverses to t[j..j+k-1]
            # That is s[i-k..i-1] reversed equals t[j..j+k-1]
            # So we need lcp of s[i-1::-1] with t
            # Let's instead see: if we want odd palindrome centered at s[i], then the right part starts somewhere in t
            # Let's try all possible j indices in t
            # The palindrome is: s[i-k..i] (k characters left, s[i] in middle) + t[j..j+k-1] (k characters right)
            # That means s[i-k..i-1] reversed should equal t[j..j+k-1]
            # So s[i-k..i-1] should equal t_rev[j+k-1..j]
            # This is complicated
        
        # Let's try odd length palindromes centered in t similarly
        # For odd centered at s[i], we need matching prefix of s[len-i-1:len] with suffix of t
        # Alternative approach: try all possible lengths L and see if we can form palindrome
        
        # Finally, handle the case where palindrome is only from s or only from t (already did)
        
        return ans