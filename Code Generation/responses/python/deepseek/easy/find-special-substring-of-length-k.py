class Solution:
    def hasSpecialSubstring(self, s: str, k: int) -> bool:
        n = len(s)
        
        for i in range(n - k + 1):
            # Check if substring of length k starting at i has all same characters
            substring = s[i:i+k]
            if len(set(substring)) != 1:
                continue
            
            # Check character before substring
            if i > 0 and s[i-1] == s[i]:
                continue
            
            # Check character after substring
            if i + k < n and s[i+k] == s[i]:
                continue
            
            # All conditions satisfied
            return True
        
        return False