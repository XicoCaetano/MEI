from typing import List
from itertools import permutations

class Solution:
    def totalNumbers(self, digits: List[int]) -> int:
        unique_numbers = set()
        
        for perm in permutations(digits, 3):
            if perm[0] != 0 and perm[2] % 2 == 0:
                num = perm[0] * 100 + perm[1] * 10 + perm[2]
                unique_numbers.add(num)
        
        return len(unique_numbers)