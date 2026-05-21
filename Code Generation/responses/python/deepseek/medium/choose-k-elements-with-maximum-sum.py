from typing import List
import heapq

class Solution:
    def findMaxSum(self, nums1: List[int], nums2: List[int], k: int) -> List[int]:
        n = len(nums1)
        # Create an array of indices and sort by nums1 value
        indices = list(range(n))
        indices.sort(key=lambda i: nums1[i])
        
        ans = [0] * n
        
        # Min-heap to keep track of k largest nums2 values
        min_heap = []
        current_sum = 0
        # Store results in a dictionary to group by nums1 values
        results = {}
        
        i = 0
        while i < n:
            j = i
            # Find all indices with the same nums1 value
            while j < n and nums1[indices[j]] == nums1[indices[i]]:
                # All indices with current nums1 value have the same answer
                # which is the sum from previous smaller nums1 values
                results[indices[j]] = current_sum
                j += 1
            
            # Add all nums2 values from the current group to the heap
            # to prepare for the next group (strictly larger nums1 values)
            group_sum = 0
            for idx in range(i, j):
                val = nums2[indices[idx]]
                if len(min_heap) < k:
                    heapq.heappush(min_heap, val)
                    group_sum += val
                elif min_heap and min_heap[0] < val:
                    group_sum -= heapq.heappop(min_heap)
                    heapq.heappush(min_heap, val)
                    group_sum += val
            
            # Update current_sum with the sum from this group
            # (these values will be available for future groups with larger nums1)
            current_sum += group_sum
            
            i = j
        
        # Fill the answer array
        for i in range(n):
            ans[i] = results[i]
        
        return ans