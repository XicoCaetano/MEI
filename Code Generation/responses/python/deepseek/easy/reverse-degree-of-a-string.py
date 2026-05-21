class Solution:
    def reverseDegree(self, s: str) -> int:
        total = 0
        for i, char in enumerate(s, 1):
            reversed_alphabet_index = 26 - (ord(char) - ord('a'))
            total += reversed_alphabet_index * i
        return total