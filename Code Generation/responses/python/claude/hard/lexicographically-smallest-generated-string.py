from typing import List

class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n = len(str1)
        m = len(str2)
        length = n + m - 1
        
        word = ['a'] * length
        locked = [False] * length
        
        # First pass: handle all 'T' positions
        for i in range(n):
            if str1[i] == 'T':
                for j in range(m):
                    idx = i + j
                    if locked[idx] and word[idx] != str2[j]:
                        return ""
                    word[idx] = str2[j]
                    locked[idx] = True
        
        # Second pass: handle 'F' positions
        for i in range(n):
            if str1[i] == 'F':
                # Check if current substring already differs from str2
                already_different = False
                for j in range(m):
                    idx = i + j
                    if word[idx] != str2[j]:
                        already_different = True
                        break
                
                if already_different:
                    continue
                
                # Need to make it different; find a non-locked position and change it
                changed = False
                for j in range(m - 1, -1, -1):
                    idx = i + j
                    if not locked[idx]:
                        # Change this position to make substring != str2
                        # Use lexicographically smallest: try 'a', else 'b'
                        if str2[j] == 'a':
                            word[idx] = 'b'
                        else:
                            word[idx] = 'a'
                        changed = True
                        break
                
                if not changed:
                    return ""
        
        return ''.join(word)