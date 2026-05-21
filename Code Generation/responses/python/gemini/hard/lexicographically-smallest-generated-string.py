class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n = len(str1)
        m = len(str2)
        total_len = n + m - 1
        
        # res stores the characters of the resulting word. 
        # None indicates the character is not yet determined.
        res = [None] * total_len
        
        # Phase 1: Fill mandatory characters based on 'T' constraints.
        for i, char in enumerate(str1):
            if char == 'T':
                for j in range(m):
                    if res[i + j] is not None and res[i + j] != str2[j]:
                        return ""
                    res[i + j] = str2[j]
        
        # Phase 2: Handle 'F' constraints and fill remaining slots lexicographically.
        # To make it lexicographically smallest, we prefer 'a' for empty slots.
        for i in range(total_len):
            if res[i] is None:
                res[i] = 'a'
        
        # Phase 3: Validate 'F' constraints.
        # If a substring at index i equals str2 but str1[i] is 'F', we must change it.
        # To keep it lexicographically smallest, we try changing the LAST character 
        # of that substring to the smallest possible character that isn't str2[m-1].
        
        # Pre-calculate KMP-like pi array or just use direct comparison since m <= 500.
        for i in range(n):
            if str1[i] == 'F':
                # Check if the current substring matches str2
                match = True
                for j in range(m):
                    if res[i + j] != str2[j]:
                        match = False
                        break
                
                if match:
                    # We must break this match. We modify the last possible character (index i + m - 1)
                    # to keep the string lexicographically small for previous indices.
                    # However, we must ensure we don't break any 'T' constraints.
                    
                    found_fix = False
                    # Try changing the last character of the substring (index i + m - 1)
                    # to 'b' if str2[m-1] is 'a', or 'a' otherwise.
                    idx_to_change = i + m - 1
                    
                    # We check if idx_to_change is part of a 'T' constraint.
                    # A character at k is fixed if there exists j such that str1[j] == 'T' and j <= k < j + m.
                    # We can pre-calculate fixed positions to speed this up.
                    
                    # For this specific problem, the only character we can safely change 
                    # without potentially violating a previous 'T' or 'F' check is the one 
                    # that isn't covered by a 'T'.
                    
                    # Let's refine: If the current substring matches str2 but it shouldn't,
                    # we must change one character res[i+j] that is NOT fixed by any 'T'.
                    # To keep it lexicographically smallest, we look at the rightmost character 
                    # in the substring that is not fixed by 'T' and increment it.
                    
                    fixed = [False] * total_len
                    for k in range(n):
                        if str1[k] == 'T':
                            for l in range(m):
                                fixed[k + l] = True
                    
                    # Re-check with fixed info
                    for k in range(n):
                        if str1[k] == 'F':
                            cur_match = True
                            for l in range(m):
                                if res[k + l] != str2[l]:
                                    cur_match = False
                                    break
                            
                            if cur_match:
                                # Try to change the rightmost non-fixed character in this window
                                changed = False
                                for l in range(m - 1, -1, -1):
                                    if not fixed[k + l]:
                                        # Change to 'b' if it was 'a' and str2[l] was 'a'
                                        # Or just the smallest character != str2[l]
                                        original = res[k + l]
                                        for char_code in range(ord('a'), ord('z') + 1):
                                            candidate = chr(char_code)
                                            if candidate != str2[l]:
                                                res[k + l] = candidate
                                                changed = True
                                                break
                                        if changed: break
                                if not changed:
                                    return ""
                    return "".join(res)
        
        return "".join(res)