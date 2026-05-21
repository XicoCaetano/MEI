from typing import List
import itertools

class Solution:
    def totalNumbers(self, digits: List[int]) -> int:
        unique_evens = set()
        for p in itertools.permutations(digits, 3):
            if p[0] != 0 and p[2] % 2 == 0:
                num = p[0] * 100 + p[1] * 10 + p[2]
                unique_evens.add(num)
        return len(unique_evens)