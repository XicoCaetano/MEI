from typing import List
from collections import defaultdict

class Solution:
    def maxSubarrays(self, n: int, conflictingPairs: List[List[int]]) -> int:
        # For each right endpoint r, we want to know the minimum left endpoint
        # such that the subarray [l, r] is valid (no conflicting pair).
        # 
        # For a conflicting pair [a, b] with a < b, any subarray containing both
        # must have left <= a and right >= b. So for right = b, the constraint is
        # left > a (i.e., left >= a+1).
        #
        # For each position r, let limit[r] = max of all (min(a,b)) for pairs where max(a,b) = r
        # The valid subarrays ending at r have left in [limit[r]+1, r].
        # 
        # Base count (no removal): sum over r of (r - limit[r]) where limit is running max
        #
        # When we remove a pair [a, b] (a < b), it might increase the count for positions r >= b
        # where this pair was the "tightest" constraint.
        #
        # Strategy: compute base answer, then for each candidate removal, compute gain.

        # Normalize pairs so a < b
        pairs = [(min(a, b), max(a, b)) for a, b in conflictingPairs]
        
        # For each right endpoint, collect all left constraints
        constraints = defaultdict(list)
        for a, b in pairs:
            constraints[b].append(a)
        
        # Compute base answer and track limit at each position
        # limit[r] = the effective lower bound (max of all a's for pairs ending at r, running)
        
        # We need to track for each r: top1 and top2 constraints
        # top1 = highest constraint (most restrictive), top2 = second highest
        
        base_count = 0
        cur_limit = 0  # running max of constraints seen so far
        
        # For gain calculation: when we remove the pair that contributes cur_limit at some r,
        # the new limit becomes the second highest.
        # 
        # We need: for each r, what's the gain if we remove the tightest constraint at r?
        # gain at r = (new_limit_r - old_limit_r) propagated forward until overridden
        
        # Let's store limit per position and top2
        limits = [0] * (n + 1)  # limits[r] = effective limit at r (running max)
        top1 = [0] * (n + 1)    # top1 local constraint at r
        top2 = [0] * (n + 1)    # second local constraint at r
        
        cur = 0
        for r in range(1, n + 1):
            local = sorted(constraints[r], reverse=True)
            t1 = local[0] if len(local) > 0 else 0
            t2 = local[1] if len(local) > 1 else 0
            
            # cur is the running max before this position
            # new cur = max(cur, t1)
            prev_cur = cur
            cur = max(cur, t1)
            limits[r] = cur
            
            # top1[r]: the constraint that is "active" = cur
            # We need to know: if we remove the pair contributing cur, what's the new limit?
            # The new local top = t2, and the prev running = prev_cur
            # So new limit = max(prev_cur, t2)
            top1[r] = cur
            top2[r] = max(prev_cur, t2)
            
            base_count += r - cur
        
        # Now compute max gain from removing one pair
        # For each pair (a, b), removing it affects positions r = b
        # But the gain propagates: after r=b, subsequent positions may also benefit
        # if the limit was being held up by this pair.
        
        # We sweep from right to left to compute gains
        # gain[i] = if at position i we remove the binding constraint, gain = top1[i] - top2[i]
        # but this gain propagates to i+1, i+2, ... as long as limits[r] == top1[i]
        
        # For each pair (a, b), removing it gives gain at position b of (top1[b] - top2[b]) if a == top1[b]
        # Then this propagates rightward.
        
        # Propagate gains: go from n down to 1
        # extra[r] = extra subarrays gained if limit at r is reduced
        # If we remove pair (a, b) with a = limits[b], gain at b = limits[b] - top2[b]
        # For r > b: if limits[r] == limits[b] (unchanged), gain propagates
        # i.e., gain carries over as long as the running max didn't increase
        
        # Precompute: for each r, the "carry" gain if limit was reduced at r
        # carry[r] = gain that propagates from r to r+1 if limit[r] is the bottleneck
        
        # We sweep right to left
        carry = 0
        gain_if_removed = {}  # pair index -> total gain
        
        # Map from (a,b) to gain
        pair_to_gain = {}
        
        # Sweep from right to left
        carry = 0
        for r in range(n, 0, -1):
            # If someone removes the constraint at r (i.e., the pair that set limits[r] = top1[r])
            # the gain at r is (top1[r] - top2[r]) + carry_from_right (if top1[r] was propagated)
            if r < n and limits[r] == limits[r + 1]:
                # limit at r+1 was inherited from r, so gain propagates
                carry_here = carry
            else:
                carry_here = 0
            
            local_gain = (top1[r] - top2[r]) + carry_here
            
            # Which pair caused top1[r] at this position?
            # It's pairs with b = r and a = top1[r], but only if top1[r] > prev running max
            # Actually top1[r] = limits[r], contributed by some pair or inherited
            
            carry = local_gain if (top1[r] == limits[r]) else 0
            
            # Store gain for pairs ending at r where a == limits[r]
            for a in constraints[r]:
                if a == limits[r]:
                    # This pair is the binding one
                    pair_to_gain[(a, r)] = local_gain
                    break  # only one can be the binding one (the max)
        
        # Now find max gain over all pairs
        max_gain = 0
        for a, b in pairs:
            g = pair_to_gain.get((a, b), 0)
            max_gain = max(max_gain, g)
        
        # Also consider: pairs that are NOT the binding constraint at their position
        # Removing them gives 0 gain (they're not affecting the limit)
        # So max_gain already accounts for the best removal
        
        # Edge case: if no pair is binding anywhere, max_gain = 0, answer = base_count
        return base_count + max_gain