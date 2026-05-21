from typing import List

class Solution:
    def minimumCost(self, nums: List[int], cost: List[int], k: int) -> int:
        n = len(nums)
        prefix_nums = [0] * (n + 1)
        prefix_cost = [0] * (n + 1)
        
        for i in range(n):
            prefix_nums[i + 1] = prefix_nums[i] + nums[i]
            prefix_cost[i + 1] = prefix_cost[i] + cost[i]
        
        # dp[i] = min cost to partition nums[0..i-1]
        # When we place the j-th subarray as nums[l..r] (0-indexed: l to r=i-1),
        # cost = (prefix_nums[i] + k*j) * (prefix_cost[i] - prefix_cost[l])
        # 
        # dp[i] = min over l in [0..i-1] of:
        #   dp[l] + (prefix_nums[i] + k*j) * (prefix_cost[i] - prefix_cost[l])
        # where j is the subarray index (1-based)
        #
        # We don't know j directly, but we can track it via the number of subarrays used.
        # dp[i][j] = min cost using exactly j subarrays covering nums[0..i-1]
        # But j can be up to n, making this O(n^3).
        # 
        # With n<=1000, O(n^3) might be tight but let's try O(n^2) DP with j tracking.
        # Actually let's do dp[i][j] with memoization.
        
        INF = float('inf')
        # dp[i][j]: min cost partitioning nums[0..i-1] into exactly j subarrays
        # Transition: dp[i][j] = min over l in [j-1..i-1]:
        #   dp[l][j-1] + (prefix_nums[i] + k*j) * (prefix_cost[i] - prefix_cost[l])
        
        # Max subarrays = n, but we want minimum cost so fewer subarrays might be better
        # We need to try all possible j from 1 to n
        
        # O(n^3) with n=1000 -> 10^9 ops, too slow.
        # 
        # Key insight: for fixed j, the term (prefix_nums[i] + k*j) is constant w.r.t. l.
        # dp[i][j] = (prefix_nums[i] + k*j) * prefix_cost[i] 
        #            + min over l of (dp[l][j-1] - (prefix_nums[i]+k*j)*prefix_cost[l])
        # This looks like a linear function in prefix_nums[i]+k*j -> convex hull trick possible
        # but let's first try O(n^2) by noting we minimize over all partitions (any j).
        
        # Actually redefine: dp[i] = min cost over all ways to partition nums[0..i-1]
        # But we need j (subarray index) which depends on history.
        # 
        # Let's just do dp[i][j] with O(n^3) but optimized with early termination.
        # n=1000, might be ~10^8 with simple ops... let's try.
        
        dp = [[INF] * (n + 1) for _ in range(n + 1)]
        dp[0][0] = 0
        
        for i in range(1, n + 1):
            for j in range(1, i + 1):
                factor = prefix_nums[i] + k * j
                for l in range(j - 1, i):
                    if dp[l][j-1] == INF:
                        continue
                    val = dp[l][j-1] + factor * (prefix_cost[i] - prefix_cost[l])
                    if val < dp[i][j]:
                        dp[i][j] = val
        
        return min(dp[n][j] for j in range(1, n + 1))