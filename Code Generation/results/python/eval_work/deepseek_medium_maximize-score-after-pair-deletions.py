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
    def maxScore(self, nums: List[int]) -> int:
        n = len(nums)
        if n <= 2:
            return 0
        
        # dp[i][j] = maximum score from subarray nums[i:j+1]
        # But n can be 10^5, so we need an O(n) solution
        
        # Observations:
        # The process always picks two elements at a time, removing them.
        # The order matters, so we need to find the best sequence of removals.
        # Since we always remove pairs, the total number of operations is (n-1)//2 if n is odd, (n-2)//2 if n is even.
        # However, we can think recursively: f(i,j) = max(
        #   nums[i] + nums[i+1] + f(i+2,j),  # remove first two
        #   nums[j-1] + nums[j] + f(i,j-2),  # remove last two
        #   nums[i] + nums[j] + f(i+1,j-1)   # remove first and last
        # )
        # But this is O(n^2) and too slow for n=10^5.
        
        # Alternative approach:
        # The key insight is that when we remove two elements, their sum is added to the score.
        # So our total score is the sum of pairs we remove.
        # Since we always remove from the ends, the order of removals determines which elements are paired.
        # This is equivalent to: choose (n-1)//2 or (n-2)//2 pairs from the ends such that each pair is a prefix, suffix, or prefix-suffix combination, and their total sum is maximized.
        
        # Actually, we can think in terms of what remains in the end:
        # If n is odd, we'll end with 1 element (can't be removed)
        # If n is even, we'll end with 0 elements (all removed)
        # The final remaining elements are those that are not paired.
        # But since we can only remove from ends, the remaining elements form a contiguous subarray in the middle.
        
        # Better approach: Let's consider the elements we don't take (the ones left in the end).
        # If n is even, we end with 0 elements.
        # If n is odd, we end with 1 element.
        # The total sum of all elements is fixed. Our score = total_sum - sum_of_remaining.
        # So to maximize score, we need to minimize sum_of_remaining.
        # But we cannot choose the remaining elements arbitrarily - they must be:
        # - If n is odd: a contiguous subarray of odd length? Actually, since we end with 1 element, it's just 1 element.
        # - If n is even: we end with 0 elements, so sum_of_remaining = 0 always? That would mean score = total_sum. But that's not correct, because the example with even length shows we don't get all elements.
        
        # Let's re-evaluate: In example 2, nums = [5,-1,4,2], total_sum = 10, but max score is 7, not 10.
        # So the "remaining elements" concept is not simply what's left in the end - because the way we pair them matters.
        # Actually, when we remove two elements, we add their sum to score. So total score over all operations = sum of all elements in all pairs we remove.
        # The elements that are never removed (the 1 remaining when n odd, or 0 when n even) don't contribute to score.
        # But in example 2 (n=4 even), we end with 0 remaining, so all elements were removed. Yet score is 7, not 10 (sum of all elements).
        # Why? Because when we remove two elements, we add their sum to score. But if we remove all elements, it means we added each element exactly once to the score? Wait, each element is removed exactly once, so it appears in exactly one addition. So if we remove all elements, score should be sum of all elements. But in example 2, that would be 10, yet answer is 7.
        # That means in example 2, they didn't remove all elements? But n=4, operations: removal removes 2 elements each time. After 2 operations, all 4 elements should be removed if we always have more than 2 elements. But the description says "while the array has more than two elements". Wait, when we have 4 elements, we have more than 2, so we do an operation, removing 2, leaving 2. Now the array has 2 elements, so we stop. We don't remove the last two. So we only do 1 operation when n=4, not 2 operations! That's the catch.
        
        # So: For array of length n, we stop when length <= 2. The number of operations = floor((n-1)/2).
        # For n=4: floor(3/2) = 1 operation. So we remove 2 elements, leaving 2.
        # For n=3: floor(2/2) = 1 operation. Remove 2, leaving 1.
        # For n=2: 0 operations.
        # For n=5: floor(4/2) = 2 operations. Remove 4 elements, leaving 1.
        
        # So we always perform k = (n-1)//2 operations if n>2, removing 2k elements, leaving n-2k elements (which is 1 if n odd, 2 if n even).
        
        # Our goal: choose k pairs to remove from the ends (each pair is either first two, last two, or first+last), to maximize sum of these pairs.
        # Equivalent to: choose which n-2k elements remain (at the ends or middle), not necessarily contiguous? Actually, the remaining elements after removals will always form a subarray in the middle.
        
        # Let's formalize:
        # For n=4, k=1, we remove exactly 2 elements, leaving 2 consecutive in the middle.
        # For n=5, k=2, we remove 4 elements, leaving 1 element in the middle.
        # So: We will have n-2k elements remaining as a contiguous subarray [l..r] in the middle.
        # The score = total_sum - sum(remaining subarray), but we must verify.
        # In example 2: total_sum=10. Remaining subarray? We removed first and last (5+2=7), remaining = [-1,4], sum=3. 10-3=7. Yes!
        # In example 1: total_sum=7. Remaining? We removed first two (2+4=6), remaining=[1], sum=1, 7-1=6. Yes.
        # So score = total_sum - sum(remaining_subarray), where remaining_subarray has length = n-2k = 1 if n odd, 2 if n even.
        # And it must be a contiguous subarray of the original array.
        
        # But can the remaining subarray be any contiguous subarray? Let's test n=4 with different remaining positions.
        # n=4, k=1, remaining length 2. If we remove first two (nums[0]+nums[1]), remaining [2,3]. That's contiguous.
        # If we remove last two (nums[2]+nums[3]), remaining [0,1]. That's contiguous.
        # If we remove first and last (nums[0]+nums[3]), remaining [1,2]. That's contiguous.
        # Yes, any contiguous subarray of length 2 can be the remaining elements if n=4.
        # For n=5, k=2, remaining length 1. Any single element can be remaining.
        # For n=6, k=2? Wait n=6: k=(6-1)//2? (5)//2=2 operations, remove 4, left 2. But 2 operations leave 2 elements? Let's check: start with 6, after 1 operation -> 4, after 2 operations -> 2 (stop). Yes, left 2. So remaining length=2.
        
        # General: For n>2, we do k = (n-1)//2 operations. Remaining elements = n-2k.
        # If n is odd: n=2m+1, k=(2m+1-1)//2=m, remaining=2m+1-2m=1.
        # If n is even: n=2m, k=(2m-1)//2=m-1, remaining=2m-2(m-1)=2.
        # So remaining length is 1 if n odd, 2 if n even.
        # And the remaining subarray must be contiguous.
        
        # So the problem becomes:
        # total_sum = sum(nums)
        # If n odd: minimize sum of a contiguous subarray of length 1 (i.e., find min element)
        # If n even: minimize sum of a contiguous subarray of length 2
        # Then answer = total_sum - min_remaining_sum.
        
        # But wait, is that always valid? Let's test n=3, n odd: min element in [2,4,1] is 1, total_sum=7, answer=6. Works.
        # n=4: total_sum=10, min contiguous subarray sum of length 2: [-1,4] sum=3, [5,-1] sum=4, [4,2] sum=6, min=3, answer=7. Works.
        # Let's test another: nums=[10, -5, 20, 30], n=4, total_sum=55, min length-2 contiguous subarray sum:
        # [10,-5]=5, [-5,20]=15, [20,30]=50, min=5, score=50. Is 50 achievable?
        # Remove first two: 10+(-5)=5, remaining [20,30] (sum 50), total score=5? Wait, we stop after 1 operation, so score=5. But we said score = total_sum - remaining = 55-50=5. So yes, score=5. But we want maximum score, so we should minimize remaining, so we want remaining sum=5 gives score=50? That's wrong math.
        # I made a mistake: score = total_sum - sum(remaining). So to maximize score, we minimize sum(remaining).
        # In example, total_sum=55, min remaining=5 (subarray [10,-5]), score=50. But can we get score=50? That would mean we removed only the other two elements? But we must remove exactly 2 elements (since n=4, only 1 operation). To leave remaining sum 5, we must leave [10,-5] as remaining. That means we removed [20,30] (last two) with sum 50. Yes! That's allowed. So score = 50. Correct.
        
        # Let's test n=6: nums=[1,2,3,4,5,6], total_sum=21, n even so remaining length=2, minimize sum of any contiguous subarray of length 2: min is [1,2]=3, score=18. Can we achieve 18?
        # n=6, k=(5)//2=2 operations, remove 4 elements, leave 2.
        # To leave [1,2] as remaining, we must have removed [3,4,5,6] in two operations starting from ends.
        # Is that possible? Start: [1,2,3,4,5,6], to remove [3,4,5,6] and leave [1,2], we would need to remove from the right end: first remove last two [5,6]=11, then we have [1,2,3,4], then remove last two [3,4]=7, left [1,2]. Score=11+7=18. Works.
        
        # So the solution:
        # 1. Compute total_sum
        # 2. If n is odd: find minimum element, answer = total_sum - min_element
        # 3. If n is even: find minimum sum of any contiguous subarray of length 2, answer = total_sum - min_pair_sum
        
        total = sum(nums)
        n = len(nums)
        
        if n == 1:
            return 0
        if n == 2:
            return 0
        
        if n % 2 == 1:
            # n odd, need min element
            min_val = min(nums)
            return total - min_val
        else:
            # n even, need min sum of contiguous pair
            min_pair = float('inf')
            for i in range(n - 1):
                min_pair = min(min_pair, nums[i] + nums[i + 1])
            return total - min_pair

# === TEST FUNCTION (do dataset) ===
def check(candidate):
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 8
    assert candidate(nums = [5, -1, 4, 2]) == 7
    assert candidate(nums = [10000, -10000, 10000, -10000, 10000]) == 20000
    assert candidate(nums = [1, 2, 3]) == 5
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 52
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 52
    assert candidate(nums = [1]) == 0
    assert candidate(nums = [-5, 5, -5, 5, -5, 5]) == 0
    assert candidate(nums = [1, 2]) == 0
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50]) == 90
    assert candidate(nums = [5, 1, 5, 1, 5, 1, 5, 1, 5, 1]) == 24
    assert candidate(nums = [2, 4, 1]) == 6
    assert candidate(nums = [-1, -2, -3, -4, -5]) == -10
    assert candidate(nums = [-5, -4, -3, -2, -1]) == -10
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1]) == 0
    assert candidate(nums = [10000, -10000, 10000, -10000, 10000]) == 20000
    assert candidate(nums = [1, 2, 3, 4, 5]) == 14
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 8
    assert candidate(nums = [10, -10, 20, -20, 30]) == 50
    assert candidate(nums = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [100, -50, 200, -300, 400, -500, 600, -700, 800, -900]) == -250
    assert candidate(nums = [1, 2]) == 0
    assert candidate(nums = [0, 0, 0, 0, 0]) == 0
    assert candidate(nums = [1, -1, 2, -2, 3, -3]) == 0
    assert candidate(nums = [1, 2, 3]) == 5
    assert candidate(nums = [29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1]) == 224
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31]) == 252
    assert candidate(nums = [100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110]) == 1055
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500]) == 11900
    assert candidate(nums = [10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60, 70, -70, 80, -80, 90, -90, 100, -100]) == 0
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20]) == -171
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000]) == 5200
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 900, 800, 700, 600, 500, 400, 300, 200, 100]) == 9900
    assert candidate(nums = [0, 1, 0, -1, 0, 2, 0, -2, 0, 3, 0, -3, 0, 4, 0, -4, 0, 5, 0, -5]) == 5
    assert candidate(nums = [1000, -1000, 500, -500, 250, -250, 125, -125, 62, -62]) == 500
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29]) == 224
    assert candidate(nums = [5, -5, 5, -5, 5, -5, 5, -5, 5, -5]) == 0
    assert candidate(nums = [100, -100, 200, -200, 300, -300, 400, -400, 500, -500]) == 0
    assert candidate(nums = [100, 100, -50, -50, 200, -300, 400, -500, 600, -700]) == -100
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, 19, -20]) == -9
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000]) == 20700
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130]) == 900
    assert candidate(nums = [99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110]) == 1055
    assert candidate(nums = [-1, -3, -5, -7, -9, -11, -13, -15, -17, -19]) == -64
    assert candidate(nums = [3, 1, -2, 5, 7, -10, 15]) == 29
    assert candidate(nums = [-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110, -120, -130]) == -780
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 28
    assert candidate(nums = [1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000]) == 5000005
    assert candidate(nums = [1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10]) == 65
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10]) == 990
    assert candidate(nums = [10, -20, 30, -40, 50, -60, 70]) == 100
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25]) == 324
    assert candidate(nums = [1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 1, 2, 3, 4, 5]) == 1111111125
    assert candidate(nums = [-10, 100, -20, 200, -30, 300, -40, 400]) == 820
    assert candidate(nums = [5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5]) == 30
    assert candidate(nums = [1000, -1000, 2000, -2000, 3000, -3000, 4000, -4000, 5000, -5000]) == 0
    assert candidate(nums = [5, 1, 3, 7, 9, 2, 6, 4, 8, 10, 12, 14]) == 77
    assert candidate(nums = [5, 3, 8, 1, 9, 4, 7, 6, 2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 202
    assert candidate(nums = [10, 9, 8, 7, 6, 5, 4, 3, 2, 1]) == 52
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10]) == 0
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13, 15, 17, 19]) == 96
    assert candidate(nums = [-1, -3, -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29]) == -196
    assert candidate(nums = [-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110]) == -550
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1]) == 2
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 119
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, -500, -400, -300, -200, -100]) == 4500
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]) == 52
    assert candidate(nums = [1, -2, 3, -4, 5, -6, 7, -8, 9, -10]) == -4
    assert candidate(nums = [-1, 2, -3, 4, -5, 6]) == 4
    assert candidate(nums = [10000, -10000, 10000, -10000, 10000, -10000]) == 0
    assert candidate(nums = [100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100]) == 6500
    assert candidate(nums = [3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5]) == 43
    assert candidate(nums = [1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14]) == 119
    assert candidate(nums = [-100, -200, 300, 400, -500, 600]) == 800
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120]) == 750
    assert candidate(nums = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20]) == 207
    assert candidate(nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15]) == 119
    assert candidate(nums = [-10, -9, -8, -7, -6, -5, -4, -3, -2, -1]) == -36
    assert candidate(nums = [1000, -999, 888, -777, 666, -555, 444, -333, 222, -111]) == 556
    assert candidate(nums = [10, -20, 30, -40, 50, -60, 70, -80, 90, -100]) == -40
    assert candidate(nums = [1, 3, 5, 7, 9, 11, 13]) == 48
    assert candidate(nums = [3, 1, 2, 4, 5, 6]) == 18
    assert candidate(nums = [-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6, -7, 7, -8, 8, -9, 9, -10, 10]) == 1
    assert candidate(nums = [5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5]) == 5
    assert candidate(nums = [-1, 2, -3, 4, -5, 6, -7, 8, -9, 10]) == 6
    assert candidate(nums = [5, 3, 8, 2, 4, 7, 1, 6, 9, 0]) == 39
    assert candidate(nums = [-100, -101, -102, -103, -104, -105, -106, -107, -108, -109, -110]) == -1045
    assert candidate(nums = [-1, -2, -3, -4, -5, -6, -7, -8, -9, -10]) == -36
    assert candidate(nums = [1, -1, 2, -2, 3, -3, 4, -4, 5, -5]) == 0
    assert candidate(nums = [10, 20, 30, 40, 50, 60, 70, 80, 90, 100]) == 520
    assert candidate(nums = [5, -1, 4, 2, 3, 6, -2, 8, -3, 7]) == 26
    assert candidate(nums = [1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1]) == 18
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1]) == 0
    assert candidate(nums = [-1000, 2000, -3000, 4000, -5000, 6000, -7000, 8000, -9000, 10000]) == 6000
    assert candidate(nums = [9, 8, 7, 6, 5, 4, 3, 2, 1, 0]) == 44
    assert candidate(nums = [5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5]) == 70
    assert candidate(nums = [1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89]) == 231
    assert candidate(nums = [1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1]) == 0
    assert candidate(nums = [100, -50, 25, -10, 15, 20, -30]) == 120
    assert candidate(nums = [0, 10000, -10000, 10000, -10000, 0, 10000, -10000, 10000, -10000]) == 10000
    assert candidate(nums = [1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000]) == 52000


# === INVOCATION ===
check(Solution().maxScore)
print("All tests passed")
