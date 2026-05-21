from typing import List
import heapq

class Solution:
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        n = len(nums1)
        # Sort indices by nums1 value
        order = sorted(range(n), key=lambda i: nums1[i])
        
        answer = [0] * n
        min_heap = []  # min-heap of nums2 values seen so far (with smaller nums1)
        heap_sum = 0
        
        i = 0
        while i < n:
            # Group indices with the same nums1 value
            j = i
            while j < n and nums1[order[j]] == nums1[order[i]]:
                j += 1
            
            # For all indices in this group, compute answer using current heap
            for idx in range(i, j):
                answer[order[idx]] = heap_sum
            
            # Now add nums2 values for this group into the heap
            for idx in range(i, j):
                val = nums2[order[idx]]
                heapq.heappush(min_heap, val)
                heap_sum += val
                if len(min_heap) > k:
                    heap_sum -= heapq.heappop(min_heap)
            
            i = j
        
        return answer