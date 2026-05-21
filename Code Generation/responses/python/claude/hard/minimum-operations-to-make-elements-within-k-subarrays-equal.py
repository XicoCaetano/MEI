from typing import List
import sortedcontainers

class Solution:
    def minOperations(self, nums: List[int], x: int, k: int) -> int:
        n = len(nums)
        
        # Precompute cost of making subarray of size x starting at index i all equal
        # Optimal target is the median, cost = sum of |nums[j] - median|
        # Use sliding window with two heaps (or sorted structure)
        
        # Cost to make nums[i..i+x-1] all equal (to median)
        costs = []
        
        # Sliding window median and cost using two sorted lists
        lo = sortedcontainers.SortedList()  # max-heap (lower half)
        hi = sortedcontainers.SortedList()  # min-heap (upper half)
        lo_sum = 0
        hi_sum = 0
        
        def add(val):
            nonlocal lo_sum, hi_sum
            if lo and val <= lo[-1]:
                lo.add(val)
                lo_sum += val
            else:
                hi.add(val)
                hi_sum += val
            # Balance
            while len(lo) < len(hi):
                moved = hi[0]
                hi.remove(moved)
                hi_sum -= moved
                lo.add(moved)
                lo_sum += moved
            while len(lo) > len(hi) + 1:
                moved = lo[-1]
                lo.remove(moved)
                lo_sum -= moved
                hi.add(moved)
                hi_sum += moved
        
        def remove(val):
            nonlocal lo_sum, hi_sum
            if val in lo:
                lo.remove(val)
                lo_sum -= val
            else:
                hi.remove(val)
                hi_sum -= val
            # Rebalance
            while len(lo) < len(hi):
                moved = hi[0]
                hi.remove(moved)
                hi_sum -= moved
                lo.add(moved)
                lo_sum += moved
            while len(lo) > len(hi) + 1:
                moved = lo[-1]
                lo.remove(moved)
                lo_sum -= moved
                hi.add(moved)
                hi_sum += moved
        
        def get_cost():
            median = lo[-1]
            # Cost = median * len(lo) - lo_sum + hi_sum - median * len(hi)
            cost = median * len(lo) - lo_sum + hi_sum - median * len(hi)
            return cost
        
        # Initialize first window
        for j in range(x):
            add(nums[j])
        costs.append(get_cost())
        
        for i in range(1, n - x + 1):
            remove(nums[i - 1])
            add(nums[i + x - 1])
            costs.append(get_cost())
        
        # Now we have costs[i] = min ops to make subarray starting at i all equal
        # We need to pick k non-overlapping subarrays of size x to minimize total cost
        # DP: dp[j] = min cost to pick j subarrays from costs[0..current]
        
        # dp[j][i] = min cost using j subarrays, last one ends at or before i
        # Transition: dp[j][i] = min(dp[j][i-1], dp[j-1][i-x] + costs[i-x+1... wait
        
        # Let dp[j][i] = min cost to select j non-overlapping subarrays all within costs[0..i]
        # where costs[i] is subarray starting at i (covering indices i..i+x-1)
        # Two choices: don't use subarray starting at i: dp[j][i] = dp[j][i-1]
        # Use subarray starting at i: dp[j][i] = dp[j-1][i-x] + costs[i] (if i >= x, prev ends at i-x)
        
        m = len(costs)  # = n - x + 1
        INF = float('inf')
        
        # dp[j] array over positions
        prev = [INF] * m
        # j=1
        prev[0] = costs[0]
        for i in range(1, m):
            prev[i] = min(prev[i-1], costs[i])
        
        for j in range(2, k + 1):
            curr = [INF] * m
            # To use subarray starting at i, previous must end at i-x or before
            # i.e., previous subarray starts at <= i-x, so prev[i-x] gives best for j-1 subarrays
            for i in range(m):
                # Don't use subarray i
                if i > 0:
                    curr[i] = curr[i-1]
                # Use subarray i: need j-1 subarrays ending before position i (start <= i-x)
                if i >= x:
                    if prev[i-x] != INF:
                        curr[i] = min(curr[i], prev[i-x] + costs[i])
                elif j == 1:
                    curr[i] = min(curr[i] if i > 0 else INF, costs[i])
            prev = curr
        
        if k == 1:
            return min(costs)
        
        return prev[m-1]