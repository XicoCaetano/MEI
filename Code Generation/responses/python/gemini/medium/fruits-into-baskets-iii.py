from typing import List

class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        n = len(baskets)
        # We use a Segment Tree to store the maximum capacity available in ranges of baskets.
        # size is the smallest power of 2 >= n to simplify tree indexing.
        size = 1
        while size < n:
            size *= 2
            
        tree = [0] * (2 * size)
        
        # Initialize the leaves of the segment tree with basket capacities
        for i in range(n):
            tree[size + i] = baskets[i]
            
        # Build the segment tree (each node stores the max of its children)
        for i in range(size - 1, 0, -1):
            tree[i] = max(tree[2 * i], tree[2 * i + 1])
            
        unplaced_count = 0
        
        for fruit in fruits:
            # If the absolute maximum in the tree is less than the fruit quantity,
            # it cannot be placed in any available basket.
            if tree[1] < fruit:
                unplaced_count += 1
                continue
            
            # Find the leftmost basket with capacity >= fruit using the segment tree
            idx = 1
            while idx < size:
                # Check the left child first to ensure we pick the leftmost basket
                if tree[2 * idx] >= fruit:
                    idx = 2 * idx
                else:
                    idx = 2 * idx + 1
            
            # idx is now the leaf node index in the tree array. 
            # Convert tree index back to basket index:
            basket_idx = idx - size
            
            # Rule: Each basket can hold only one type of fruit. 
            # Mark the basket as used by setting its capacity to 0 in the tree.
            tree[idx] = 0
            
            # Update the tree moving upwards to reflect the used basket
            curr = idx // 2
            while curr >= 1:
                new_max = max(tree[2 * curr], tree[2 * curr + 1])
                if tree[curr] == new_max:
                    # Optimization: if the max doesn't change, we can stop early
                    break
                tree[curr] = new_max
                curr //= 2
                
        return unplaced_count