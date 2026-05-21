from typing import List

class Solution:
    def phonePrefix(self, numbers: List[str]) -> bool:
        numbers.sort()
        for i in range(len(numbers) - 1):
            if numbers[i + 1].startswith(numbers[i]):
                return False
        return True