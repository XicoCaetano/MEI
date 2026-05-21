from typing import List
import sortedcontainers

class Solution:
    def numOfUnplacedFruits(self, fruits: List[int], baskets: List[int]) -> int:
        # Use a sorted structure to efficiently find leftmost basket with capacity >= fruit quantity
        # We need leftmost, so we track (capacity, original_index) and find min index among valid
        
        # Segment tree approach: build over baskets array, query for leftmost index with value >= x
        n = len(baskets)
        
        # Segment tree storing max value in range, to quickly skip ranges
        # For leftmost basket >= fruit, we need to find leftmost position with baskets[pos] >= fruit
        
        size = 1
        while size < n:
            size <<= 1
        
        tree = [0] * (2 * size)
        
        # Build tree with max values
        for i in range(n):
            tree[size + i] = baskets[i]
        for i in range(size - 1, 0, -1):
            tree[i] = max(tree[2*i], tree[2*i+1])
        
        def query_leftmost(val):
            # Find leftmost index in [0, n) where baskets[index] >= val
            if tree[1] < val:
                return -1
            node = 1
            while node < size:
                if tree[2*node] >= val:
                    node = 2*node  # go left
                else:
                    node = 2*node + 1  # go right
            idx = node - size
            if idx < n and tree[node] >= val:
                return idx
            return -1
        
        def update(idx, val):
            pos = size + idx
            tree[pos] = val
            pos >>= 1
            while pos >= 1:
                tree[pos] = max(tree[2*pos], tree[2*pos+1])
                pos >>= 1
        
        unplaced = 0
        for fruit in fruits:
            idx = query_leftmost(fruit)
            if idx == -1:
                unplaced += 1
            else:
                update(idx, 0)  # mark basket as used
        
        return unplaced