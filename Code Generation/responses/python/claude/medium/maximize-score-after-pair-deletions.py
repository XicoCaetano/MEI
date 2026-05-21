from typing import List

class Solution:
    def maxScore(self, nums: List[int]) -> int:
        # Key insight: each operation removes 2 adjacent elements from either end
        # of the current array. After all operations, we have at most 1 element left.
        # 
        # Notice: every element except possibly one gets removed. The element that
        # remains (if len is odd) must be at an even index from either end at some point.
        #
        # Better insight: we always remove pairs of adjacent elements (in circular sense).
        # The total sum minus the minimum element we can "skip" (if odd length).
        # 
        # Actually: we remove n//2 pairs. If n is even, all elements are removed.
        # If n is odd, exactly one element remains.
        # 
        # The operations always remove two elements that are adjacent in the CURRENT array.
        # This means we can always remove any two elements that are adjacent in the original
        # circular arrangement... let's think with DP.
        #
        # With operations: remove first two, last two, or first+last - these are exactly
        # the pairs that are adjacent on a circular array! So we're choosing n//2 non-
        # overlapping adjacent pairs on a circle (if even) or leaving one element out (odd).
        #
        # For even n: total sum (we must remove everything, score = sum of all)
        # For odd n: total sum - min element we must leave out
        # But which element can we leave out? Any element at an odd position in some valid
        # pairing... Actually for a circular arrangement we can leave out any element.
        
        n = len(nums)
        total = sum(nums)
        
        if n % 2 == 0:
            return total
        else:
            # We need to leave out exactly one element; to maximize score, leave out minimum
            # But can we always leave out ANY element? Yes - on a circle of odd length,
            # we can always pair up the remaining n-1 elements as adjacent pairs.
            return total - min(nums)