from typing import List

class Solution:
    def transformArray(self, nums: List[int]) -> List[int]:
        # Replace each even number with 0 and each odd number with 1
        transformed = [0 if num % 2 == 0 else 1 for num in nums]
        
        # Sort in non-decreasing order
        transformed.sort()
        
        return transformed