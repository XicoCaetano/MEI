# === IMPORTS GERAIS (do dataset) ===
import random
import functools
import collections
import string
import math
import datetime

from typing import *
from functools import *
from collections import *
from itertools import *
from heapq import *
from bisect import *
from string import *
from operator import *
from math import *

inf = float('inf')

class ListNode:
    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

def list_node(values: list):
    if not values:
        return None
    head = ListNode(values[0])
    p = head
    for val in values[1:]:
        node = ListNode(val)
        p.next = node
        p = node
    return head

def is_same_list(p1, p2):
    if p1 is None and p2 is None:
        return True
    if not p1 or not p2:
        return False
    return p1.val == p2.val and is_same_list(p1.next, p2.next)

class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right

def tree_node(values: list):
    if not values:
        return None
    root = TreeNode(values[0])
    i = 1
    queue = deque()
    queue.append(root)
    while queue:
        node = queue.popleft()
        if i < len(values) and values[i] is not None:
            node.left = TreeNode(values[i])
            queue.append(node.left)
        i += 1
        if i < len(values) and values[i] is not None:
            node.right = TreeNode(values[i])
            queue.append(node.right)
        i += 1
    return root

def is_same_tree(p, q):
    if not p and not q:
        return True
    elif not p or not q:
        return False
    elif p.val != q.val:
        return False
    else:
        return is_same_tree(p.left, q.left) and is_same_tree(p.right, q.right)


# === MODEL RESPONSE ===
from typing import List

class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        
        # Precompute prefix sums for active sections (1's)
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i + 1] = prefix[i] + (1 if s[i] == '1' else 0)
        
        # Precompute blocks of consecutive 1's and 0's
        blocks = []
        i = 0
        while i < n:
            j = i
            while j < n and s[j] == s[i]:
                j += 1
            blocks.append((s[i], j - i))
            i = j
        
        m = len(blocks)
        
        # For each block of 0's, find the number of 1's around it if it's between two 1-blocks
        # This is used to compute the gain from converting that 0-block to 1's
        # The gain is (number of 1's in surrounding blocks) + (number of 1's in the 0-block after conversion)
        # But since we convert the 0-block to 1's, the gain is the sum of the two surrounding 1-blocks
        # plus the length of the 0-block (since it becomes active) minus the original 1's in those surrounding blocks
        # However, we need to consider that we also turn the selected 1-block to 0's.
        # The net change: +len(selected_0_block) + len(left_1_block) + len(right_1_block) - len(selected_1_block)
        # But careful: we select a 1-block surrounded by 0's to turn to 0's, then turn a 0-block to 1's.
        # The optimal is to take the largest net gain.

        # Prepare prefix sums of block lengths and values for faster query
        # But queries are on substrings, so we need to handle partial blocks at the ends of the substring
        # The augmented string adds '1' at both ends, so we need to consider that in the substring context
        
        # To answer queries efficiently, we need to know for any substring the best possible net gain.
        # For substring s[l..r], augmented: '1' + s[l..r] + '1'
        # We need the best block of 1's surrounded by 0's within this augmented substring, and the best block of 0's surrounded by 1's.
        # Then the net gain = (sum of surrounding 1's around the chosen 0-block) + (length of chosen 0-block) - (length of chosen 1-block)
        
        # Let's precompute arrays for positions of 1's and 0's to find these blocks quickly? But queries are many.
        # We need O(log n) or O(1) per query.
        
        # Precompute for each position the nearest block start/end
        
        # We'll use a different approach: For any substring, the maximum active sections after trade = original active sections + net gain, where net gain is the maximum over all pairs (i1, i2) of (len(0_block_i2) + len(left_1_around_i2) + len(right_1_around_i2) - len(1_block_i1)) where i1 and i2 are within the substring and i1 is a 1-block surrounded by 0's, i2 is a 0-block surrounded by 1's.
        # But i1 and i2 can be any blocks, not necessarily in order? Actually they must be the same block? No, they are independent choices. The trade: convert a 1-block (surrounded by 0's) to 0's, and convert a 0-block (surrounded by 1's) to 1's. These can be different blocks.
        
        # Observation: The net gain depends only on the chosen 0-block and the chosen 1-block:
        # Let a = len(0_block) + len(left_1_around_it) + len(right_1_around_it)
        # Let b = len(1_block)
        # Gain = a - b
        # We want to maximize a - b, with the chosen 0-block and 1-block both in the augmented substring.
        # So we need the max a over 0-blocks in the substring, and min b over 1-blocks in the substring? No, not independent because they must be chosen such that the trade is valid: the 1-block must have 0's on both sides, and the 0-block must have 1's on both sides. In the augmented substring, the 1's at ends are in the subnet.
        
        # Let's consider the augmented string t = '1' + s[l..r] + '1'
        # We want to find:
        # max_{i1 = indices of 1-blocks in between 0's in t} ( (len(0_left_of_i1) + len(0_right_of_i1) + len(1_block_i1) )? Not right.
        
        # Actually, the net gain = (len(0_block_selected) + sum of surrounding 1's) - len(1_block_selected)
        # But sum of surrounding 1's = before conversion, we had those 1's in adjacent blocks, after conversion we still have them, plus the new 0_block becomes 1's. So we add len(0_block).
        # And we lose len(1_block) because we convert it to 0's.
        # So net = len(0_block) + sum(surrounding_1's) - len(1_block)
        
        # In t, the candidate 0-blocks for conversion are those with 1's on both sides.
        # Candidate 1-blocks for turning to 0's are those with 0's on both sides.
        
        # We can precompute for each position p in s, the length of the block it's in, and the left/right neighbor types and lengths.
        # But queries are substrings, so we need to find candidate blocks within that substring.
        
        # Let's precompute arrays:
        # block_id[pos] = which block this position belongs to
        # block_len[pos] = length of that block
        # left_neighbor_len[pos] = length of left neighbor block if it's between 0's, etc.
        
        # Better: Since n ≤ 1e5, m ≤ 1e5, we can precompute for each block its properties and then for each query, find the relevant blocks and compute max gain.
        # But queries can be 1e5, so O(1) per query needed.
        
        # Another approach: Precompute prefix sums of block lengths and use them to quickly compute number of 1's in any substring, and also to find nearest blocks.
        
        # We'll use a map to store for each block index its start, end, length, char, left_block, right_block
        # Then for a query [l, r], we find the first block starting at or after l, and the last block ending at or before r.
        # Then we consider candidate 0-blocks fully inside [l, r] with positive left and right neighbors also inside [l, r] (considering augmented 1's at ends).
        # And candidate 1-blocks fully inside [l, r] with left and right neighbors (which might be partially inside or the augmented 1's).
        
        # Since we have augmented '1' at both ends, the first and last block in the substring might be adjacent to these augmented 1's, which we must consider as existing 1's of length 1.
        
        # Let's implement this idea:
        
        # Preprocess block information
        block_data = []  # (start_pos, end_pos, char, length)
        start_idx = 0
        for i in range(1, n):
            if s[i] != s[i-1]:
                block_data.append((start_idx, i-1, s[start_idx], i - start_idx))
                start_idx = i
        block_data.append((start_idx, n-1, s[start_idx], n - start_idx))
        
        m = len(block_data)
        # For each block, store its index, and precompute prefix sums of lengths of 0-blocks and 1-blocks for quick sums
        prefix_ones = [0] * (m + 1)
        prefix_zeros = [0] * (m + 1)
        prefix_len_zeros = [0] * (m + 1)
        prefix_len_ones = [0] * (m + 1)
        for i in range(m):
            char, length = block_data[i][2], block_data[i][3]
            if char == '1':
                prefix_ones[i+1] = prefix_ones[i] + length
                prefix_len_ones[i+1] = prefix_len_ones[i] + length
                prefix_zeros[i+1] = prefix_zeros[i]
                prefix_len_zeros[i+1] = prefix_len_zeros[i]
            else:
                prefix_zeros[i+1] = prefix_zeros[i] + length
                prefix_len_zeros[i+1] = prefix_len_zeros[i] + length
                prefix_ones[i+1] = prefix_ones[i]
                prefix_len_ones[i+1] = prefix_len_ones[i]
        
        import bisect
        
        res = []
        for l, r in queries:
            # Find the first block that starts at or after l
            start_block_idx = bisect.bisect_left([b[0] for b in block_data], l)
            # Find the last block that ends at or before r
            end_block_idx = bisect.bisect_right([b[1] for b in block_data], r) - 1
            
            if start_block_idx > end_block_idx:
                # No block in the range? Impossible since substring nonempty
                total_ones = prefix[r+1] - prefix[l]
                res.append(total_ones)
                continue
            
            # Number of 1's in the substring before trade
            original_active = prefix[r+1] - prefix[l]
            
            # We need to consider candidate 0-blocks and 1-blocks within [l, r] with their neighbors.
            # The augmented string has '1' at both ends, so if first block is 0, its left neighbor in augmented string is '1' (length 1).
            # Similarly, if last block is 0, its right neighbor is '1' (length 1).
            
            # Candidate 0-blocks: those with 1's on both sides in the augmented substring
            # Candidate 1-blocks: those with 0's on both sides in the augmented substring
            
            max_gain = 0
            
            # We'll check for possible gains:
            # The best trade: take a 0-block (with surrounding 1's) to make it all 1's, and take a 1-block (with surrounding 0's) to make it all 0's.
            # But they can be the same block? No, because if we turn a 1-block to 0's and also turn some 0-block to 1's, they must be distinct.
            
            # First, find the best 0-block candidate
            best_zero = 0
            for i in range(start_block_idx, end_block_idx + 1):
                if block_data[i][2] == '0':
                    # Check left neighbor
                    left_neighbor_len = 0
                    if i > start_block_idx:
                        if i > 0 and block_data[i-1][2] == '1':
                            left_neighbor_len = block_data[i-1][3]
                        else:
                            continue  # not surrounded by 1 on left
                    else:
                        # First block in substring, and it's 0, so left neighbor is augmented '1' length 1
                        left_neighbor_len = 1
                    
                    # Check right neighbor
                    right_neighbor_len = 0
                    if i < end_block_idx:
                        if i + 1 < m and block_data[i+1][2] == '1':
                            right_neighbor_len = block_data[i+1][3]
                        else:
                            continue  # not surrounded by 1 on right
                    else:
                        # Last block in substring, and it's 0, so right neighbor is augmented '1' length 1
                        right_neighbor_len = 1
                    
                    # Potential gain from converting this 0-block to 1's: +block_len + left_neighbor_len + right_neighbor_len
                    gain_if_convert_0 = block_data[i][3] + left_neighbor_len + right_neighbor_len
                    best_zero = max(best_zero, gain_if_convert_0)
            
            # Now find the best 1-block candidate to convert to 0's
            best_one = 0
            for i in range(start_block_idx, end_block_idx + 1):
                if block_data[i][2] == '1':
                    # Check left neighbor
                    left_neighbor_zero = False
                    left_neighbor_len = 0
                    if i > start_block_idx:
                        if i > 0 and block_data[i-1][2] == '0':
                            left_neighbor_zero = True
                            left_neighbor_len = block_data[i-1][3]
                    else:
                        # First block in substring, and it's 1, left neighbor is augmented '1' length 1? Wait, augmented ends are 1's, so left neighbor is '1', not '0'.
                        left_neighbor_zero = False  # not surrounded by 0 on left
                    
                    # Check right neighbor
                    right_neighbor_zero = False
                    right_neighbor_len = 0
                    if i < end_block_idx:
                        if i + 1 < m and block_data[i+1][2] == '0':
                            right_neighbor_zero = True
                            right_neighbor_len = block_data[i+1][3]
                    else:
                        # Last block in substring, right neighbor is augmented '1' length 1
                        right_neighbor_zero = False
                    
                    if left_neighbor_zero and right_neighbor_zero:
                        # This 1-block can be turned to 0's, losing its length
                        loss_if_convert_1 = block_data[i][3]
                        best_one = max(best_one, loss_if_convert_1)
            
            # Net gain = best_zero - best_one (if both exist)
            if best_zero > 0 and best_one > 0:
                max_gain = max(max_gain, best_zero - best_one)
            # Also, it's possible that we just convert one block to 1's without losing anything? No, trade requires both parts.
            # So both must be present.
            
            # But wait, they can be the same block? No, because a block can't be both 0 and 1.
            
            # Also, if best_zero > 0 and we choose no 1-block to convert to 0's, we can't, because the operation requires both steps.
            
            # So we need to find the best possible gain = max over zero_blocks (val_zero) - min over one_blocks (val_one) such that zero_block and one_block are distinct and the substring contains both with their surroundings.
            
            # Let's compute max_val_zero and min_val_one over valid candidate blocks.
            
            # But note: if we take a zero-block with gain g, we lose a one-block with loss l, so net = g - l.
            # To maximize net, we want max g - min l, with g from zero-blocks and l from one-blocks.
            
            # So find max possible g and min possible l, if both exist.
            max_g_val = 0
            min_l_val = float('inf')
            zero_exists = False
            one_exists = False
            for i in range(start_block_idx, end_block_idx + 1):
                if block_data[i][2] == '0':
                    left_len = 0
                    right_len = 0
                    # Left neighbor
                    if i > start_block_idx:
                        if i > 0 and block_data[i-1][2] == '1':
                            left_len = block_data[i-1][3]
                        else:
                            continue
                    else:
                        left_len = 1  # augmented '1'
                    # Right neighbor
                    if i < end_block_idx:
                        if i+1 < m and block_data[i+1][2] == '1':
                            right_len = block_data[i+1][3]
                        else:
                            continue
                    else:
                        right_len = 1
                    g = block_data[i][3] + left_len + right_len
                    max_g_val = max(max_g_val, g)
                    zero_exists = True
                elif block_data[i][2] == '1':
                    # Check if surrounded by 0's
                    left_zero = False
                    right_zero = False
                    if i > start_block_idx:
                        if i > 0 and block_data[i-1][2] == '0':
                            left_zero = True
                    else:
                        left_zero = False  # left neighbor is augmented '1' not 0
                    if i < end_block_idx:
                        if i+1 < m and block_data[i+1][2] == '0':
                            right_zero = True
                    else:
                        right_zero = False  # right neighbor is augmented '1'
                    
                    if left_zero and right_zero:
                        l_val = block_data[i][3]
                        min_l_val = min(min_l_val, l_val)
                        one_exists = True
            
            if zero_exists and one_exists and max_g_val > min_l_val:
                max_gain = max(max_gain, max_g_val - min_l_val)
            elif zero_exists and not one_exists:
                # Can't do the trade because we need to zero out a 1-block
                max_gain = 0
            elif not zero_exists and one_exists:
                max_gain = 0
            else:
                max_gain = 0
            
            # Also check the case where we choose the same zero-block and one-block? Not possible.
            
            res.append(original_active + max_gain)
        
        return res

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(s = "0100",queries = [[0, 3], [0, 2], [1, 3], [2, 3]]) == [4, 3, 1, 1]
    assert candidate(s = "01",queries = [[0, 1]]) == [1]
    assert candidate(s = "01010",queries = [[0, 3], [1, 4], [1, 3]]) == [4, 4, 2]
    assert candidate(s = "1000100",queries = [[1, 5], [0, 6], [0, 4]]) == [6, 7, 2]
    assert candidate(s = "111111111111111111111111111111111111111111111111",queries = [[0, 39], [1, 38], [2, 37], [3, 36], [4, 35], [5, 34], [6, 33], [7, 32], [8, 31], [9, 30]]) == [48, 48, 48, 48, 48, 48, 48, 48, 48, 48]
    assert candidate(s = "11111111111111111",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [17, 17, 17, 17, 17]
    assert candidate(s = "10000000010000000001000000001",queries = [[0, 20], [5, 15], [10, 19]]) == [21, 14, 4]
    assert candidate(s = "000000000000000000000000000000000000000000000000",queries = [[0, 39], [1, 38], [2, 37], [3, 36], [4, 35], [5, 34], [6, 33], [7, 32], [8, 31], [9, 30]]) == [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
    assert candidate(s = "11001100110011001100110011",queries = [[0, 20], [5, 15], [0, 9], [10, 19], [15, 25]]) == [18, 18, 18, 18, 18]
    assert candidate(s = "111100001111000011110000",queries = [[0, 23], [4, 19], [5, 18], [6, 17], [7, 16], [8, 15], [9, 14], [10, 13], [11, 12]]) == [20, 20, 19, 18, 17, 12, 12, 12, 12]
    assert candidate(s = "1001001001001001001001001",queries = [[0, 24], [2, 22], [3, 21], [4, 20], [5, 19], [6, 18], [7, 17], [8, 16], [9, 15], [10, 14], [11, 13]]) == [13, 13, 13, 13, 13, 13, 13, 13, 13, 13, 11]
    assert candidate(s = "00101010101010101010",queries = [[0, 9], [5, 15], [10, 19]]) == [12, 11, 11]
    assert candidate(s = "10101010101010101010101010",queries = [[0, 25], [1, 24], [2, 23], [3, 22], [4, 21]]) == [15, 15, 15, 15, 15]
    assert candidate(s = "101010101010101010101010101010101010101010101010101010101010",queries = [[0, 59], [1, 58], [2, 57], [3, 56], [4, 55], [5, 54], [6, 53], [7, 52], [8, 51], [9, 50]]) == [32, 32, 32, 32, 32, 32, 32, 32, 32, 32]
    assert candidate(s = "111000111000111",queries = [[0, 14], [1, 13], [2, 12], [3, 11], [4, 10]]) == [15, 15, 15, 15, 13]
    assert candidate(s = "000011110000111100001111",queries = [[0, 23], [4, 19], [5, 18], [6, 17], [7, 16], [8, 15], [9, 14], [10, 13], [11, 12]]) == [20, 20, 19, 18, 17, 12, 12, 12, 12]
    assert candidate(s = "111000111000",queries = [[0, 11], [3, 8], [4, 7], [5, 6]]) == [12, 6, 6, 6]
    assert candidate(s = "01010101010101010101010101010101",queries = [[0, 15], [15, 30], [0, 29]]) == [18, 18, 18]
    assert candidate(s = "10101010101010101010",queries = [[0, 19], [1, 18], [2, 17], [3, 16], [4, 15], [5, 14], [6, 13], [7, 12], [8, 11], [9, 10]]) == [12, 12, 12, 12, 12, 12, 12, 12, 12, 10]
    assert candidate(s = "1001001001001001001",queries = [[0, 18], [1, 17], [2, 16], [5, 13], [3, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "11110000111100001111",queries = [[0, 9], [5, 15], [10, 19]]) == [12, 19, 12]
    assert candidate(s = "1010101010",queries = [[0, 9], [1, 8], [2, 7], [3, 6]]) == [7, 7, 7, 7]
    assert candidate(s = "0000011111000001111100000111110000011111",queries = [[0, 9], [10, 19], [20, 29], [30, 39], [0, 39]]) == [20, 20, 20, 20, 30]
    assert candidate(s = "1100001100011110001000000011001",queries = [[5, 15], [2, 20], [0, 30], [10, 25]]) == [16, 19, 22, 22]
    assert candidate(s = "00000100000100000",queries = [[0, 14], [1, 13], [2, 12], [5, 10], [3, 8]]) == [12, 11, 10, 2, 7]
    assert candidate(s = "00000000000000000",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [0, 0, 0, 0, 0]
    assert candidate(s = "0101010101010101010",queries = [[0, 18], [1, 17], [2, 16], [5, 13], [3, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "000100010001000100010001000100010001000100010001000100010001",queries = [[0, 59], [1, 58], [2, 57], [3, 56], [4, 55], [5, 54], [6, 53], [7, 52], [8, 51], [9, 50]]) == [21, 21, 21, 21, 21, 21, 21, 21, 21, 21]
    assert candidate(s = "10101010101010101",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "0101010101",queries = [[0, 9], [1, 8], [2, 7], [3, 6]]) == [7, 7, 7, 7]
    assert candidate(s = "01010101010101010101010101",queries = [[0, 25], [1, 24], [2, 23], [3, 22], [4, 21]]) == [15, 15, 15, 15, 15]
    assert candidate(s = "1100110011",queries = [[0, 9], [1, 8], [2, 7], [3, 6], [4, 5]]) == [10, 10, 10, 8, 6]
    assert candidate(s = "1001001001",queries = [[0, 9], [1, 8], [2, 7], [3, 6], [4, 5]]) == [8, 8, 7, 4, 4]
    assert candidate(s = "1001001001001001001",queries = [[0, 18], [1, 17], [2, 16], [3, 15], [4, 14]]) == [11, 11, 11, 11, 11]
    assert candidate(s = "0000000000",queries = [[0, 9], [2, 7], [4, 6]]) == [0, 0, 0]
    assert candidate(s = "1111111111",queries = [[0, 9], [2, 7], [4, 6]]) == [10, 10, 10]
    assert candidate(s = "110001100110001",queries = [[0, 14], [1, 13], [2, 12], [5, 10], [3, 8]]) == [12, 12, 12, 7, 11]
    assert candidate(s = "0000011111000001111100000",queries = [[0, 24], [1, 23], [2, 22], [3, 21], [4, 20], [5, 19], [6, 18], [7, 17], [8, 16], [9, 15]]) == [20, 19, 18, 17, 16, 10, 10, 10, 10, 10]
    assert candidate(s = "100100100100100",queries = [[0, 14], [1, 13], [2, 12], [3, 11], [4, 10], [5, 9]]) == [9, 9, 9, 9, 9, 8]
    assert candidate(s = "1001001001001",queries = [[0, 12], [2, 9], [3, 8], [4, 7], [5, 6]]) == [9, 9, 9, 8, 5]
    assert candidate(s = "1000000001",queries = [[1, 8], [0, 9], [2, 7], [3, 6]]) == [2, 2, 2, 2]
    assert candidate(s = "0000011110001110000",queries = [[0, 18], [1, 17], [2, 16], [3, 15], [4, 14], [5, 13]]) == [15, 14, 13, 12, 11, 7]
    assert candidate(s = "00110011001100110",queries = [[0, 16], [1, 15], [2, 14], [5, 11], [3, 12]]) == [12, 12, 12, 11, 12]


# === INVOCATION ===
check(Solution().maxActiveSectionsAfterTrade)
print("All tests passed")
