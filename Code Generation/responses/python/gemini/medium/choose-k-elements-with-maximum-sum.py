from typing import List
import heapq

class Solution:
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        n = len(nums1)
        # Create a list of tuples (nums1 value, nums2 value, original index)
        # and sort by nums1 value to process them in increasing order.
        data = sorted([(nums1[i], nums2[i], i) for i in range(n)])
        
        results = [0] * n
        min_heap = []
        current_sum = 0
        
        # We need to track the pointer to the first element in the sorted list 
        # that has the same nums1 value as the current group.
        j = 0
        for i in range(n):
            # If the current nums1 value is greater than the previous processed one,
            # we can add all values that were smaller into our potential top-k pool.
            # This handles duplicate values in nums1 correctly.
            if i > 0 and data[i][0] > data[i-1][0]:
                while j < i:
                    val_to_add = data[j][1]
                    heapq.heappush(min_heap, val_to_add)
                    current_sum += val_to_add
                    
                    # Maintain only the top k largest elements in the heap
                    if len(min_heap) > k:
                        current_sum -= heapq.heappop(min_heap)
                    j += 1
            
            # The result for the original index is the current sum of the top k
            # values from elements strictly smaller than data[i][0].
            # If nums1 values are equal, the loop won't update current_sum, 
            # fulfilling the condition nums1[j] < nums1[i].
            original_idx = data[i][2]
            results[original_idx] = current_sum
            
        return results