from typing import List

class Solution:
    def minTime(self, skill: List[int], mana: List[int]) -> int:
        n = len(skill)
        m = len(mana)
        
        # List of start times for each wizard for each potion
        start_times = [[0] * m for _ in range(n)]
        
        # Time when each wizard finishes the previous potion
        finish_time = [0] * n
        
        # Process potions sequentially
        for j in range(m):
            # Start time for wizard 0 on potion j
            # Must be at least the previous finish time of wizard 0
            start_times[0][j] = finish_time[0]
            
            # Compute wizard by wizard
            for i in range(n):
                if i > 0:
                    # Wizard i can start when previous wizard finishes this potion
                    # OR when wizard i finishes previous potion (whichever is later)
                    start_times[i][j] = max(start_times[i-1][j] + skill[i-1] * mana[j], finish_time[i])
                
                # Update finish time for this wizard on this potion
                finish_time[i] = start_times[i][j] + skill[i] * mana[j]
        
        # Return total time (when last wizard finishes last potion)
        return finish_time[n-1]