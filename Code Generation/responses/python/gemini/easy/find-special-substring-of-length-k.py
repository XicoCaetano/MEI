class Solution:
    def hasSpecialSubstring(self, s: str, k: int) -> bool:
        if not s:
            return False
            
        count = 1
        for i in range(1, len(s)):
            if s[i] == s[i - 1]:
                count += 1
            else:
                if count == k:
                    return True
                count = 1
                
        return count == k