from typing import List

class Solution:
    def maxActiveSectionsAfterTrade(self, s: str, queries: List[List[int]]) -> List[int]:
        n = len(s)
        
        pref = [0] * (n + 1)
        for i in range(n):
            pref[i + 1] = pref[i] + (1 if s[i] == '1' else 0)
            
        def get_ones(l, r):
            if l > r: return 0
            return pref[r + 1] - pref[l]

        segments = []
        if n > 0:
            curr_char = s[0]
            start = 0
            for i in range(1, n):
                if s[i] != curr_char:
                    segments.append((curr_char, start, i - 1))
                    curr_char = s[i]
                    start = i
            segments.append((curr_char, start, n - 1))
            
        m = len(segments)
        seg_idx = [0] * n
        for idx, (char, start, end) in enumerate(segments):
            for i in range(start, end + 1):
                seg_idx[i] = idx
    
        one_seg_lens = [] 
        zero_seg_lens = [] 
        
        results = []
        for l, r in queries:
            initial_ones = get_ones(l, r)
            
            idx_l = seg_idx[l]
            idx_r = seg_idx[r]
            
            q_segments = []
            if idx_l == idx_r:
                q_segments.append((s[l], r - l + 1))
            else:
                # First
                q_segments.append((s[l], segments[idx_l][2] - l + 1))
                # Middles
                for i in range(idx_l + 1, idx_r):
                    q_segments.append((segments[i][0], segments[i][2] - segments[i][1] + 1))
                # Last
                q_segments.append((s[r], r - segments[idx_r][1] + 1))
            
            max_zero = 0
            min_one = float('inf')
            
            # Find 0-blocks (all are candidates)
            for char, length in q_segments:
                if char == '0':
                    max_zero = max(max_zero, length)
    
            for i in range(1, len(q_segments) - 1):
                char, length = q_segments[i]
                if char == '1':
                    min_one = min(min_one, length)
            
            if min_one == float('inf') or max_zero == 0:
                results.append(initial_ones)
            else:
                results.append(initial_ones + max_zero - min_one)
                
        return results