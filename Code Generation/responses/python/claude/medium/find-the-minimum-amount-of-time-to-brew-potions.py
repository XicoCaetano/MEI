from typing import List

class Solution:
    def minTime(self, skill: List[int], mana: List[int]) -> int:
        n = len(skill)
        m = len(mana)
        
        # prefix_skill[i] = sum of skill[0..i-1]
        prefix = [0] * (n + 1)
        for i in range(n):
            prefix[i+1] = prefix[i] + skill[i]
        
        # start[j] = start time of potion j
        start = [0] * m
        
        for j in range(m):
            if j == 0:
                start[0] = 0
            else:
                # start[j] must be >= start[j-1] + skill[0]*mana[j-1]
                # (wizard 0 finishes potion j-1 before starting potion j)
                min_start = start[j-1] + skill[0] * mana[j-1]
                
                # For each wizard i, wizard i finishes potion j-1 at:
                # start[j-1] + prefix[i+1]*mana[j-1]
                # Wizard i can start potion j no earlier than that time.
                # Wizard i starts potion j at: start[j] + prefix[i]*mana[j]
                # So: start[j] + prefix[i]*mana[j] >= start[j-1] + prefix[i+1]*mana[j-1]
                # start[j] >= start[j-1] + prefix[i+1]*mana[j-1] - prefix[i]*mana[j]
                
                for i in range(1, n):
                    candidate = start[j-1] + prefix[i+1] * mana[j-1] - prefix[i] * mana[j]
                    if candidate > min_start:
                        min_start = candidate
                
                start[j] = max(0, min_start)
        
        # Total time = start of last potion + time for all wizards on last potion
        return start[m-1] + prefix[n] * mana[m-1]