from typing import List

class Solution:
    def phonePrefix(self, numbers: List[str]) -> bool:
        # Sort the numbers lexicographically
        numbers.sort()
        
        # Check each adjacent pair for prefix relationship
        for i in range(len(numbers) - 1):
            if numbers[i + 1].startswith(numbers[i]):
                return False
        
        return True