class Solution:
    def hasSpecialSubstring(self, s: str, k: int) -> bool:
        i = 0
        while i < len(s):
            j = i
            while j < len(s) and s[j] == s[i]:
                j += 1
            if j - i == k:
                return True
            i = j
        return False