from typing import List

class Solution:
    def minTime(self, skill: List[int], mana: List[int]) -> int:
        n = len(skill)
        m = len(mana)
        
        # prefix_skills[i] = sum(skill[0...i-1])
        prefix_skills = [0] * (n + 1)
        for i in range(n):
            prefix_skills[i+1] = prefix_skills[i] + skill[i]
            
        # Let S[i] be the prefix sum of skills up to wizard i.
        # Let T_j be the start time of potion j.
        # For a potion j, wizard i finishes at: T_j + S[i+1] * mana[j]
        # The constraint is that wizard i must finish potion j before or at 
        # the time wizard i starts potion j+1.
        # Since wizard i starts potion j+1 at T_{j+1} + S[i] * mana[j+1],
        # we need: T_j + S[i+1] * mana[j] <= T_{j+1} + S[i] * mana[j+1]
        # Rearranging for T_{j+1}:
        # T_{j+1} >= T_j + S[i+1] * mana[j] - S[i] * mana[j+1] for all i in [0, n-1]
        
        # To minimize total time, T_0 = 0.
        # T_{j+1} = max(T_{j+1}, T_j + max_{i=0..n-1} (S[i+1] * mana[j] - S[i] * mana[j+1]))
        
        current_start_time = 0
        
        for j in range(m - 1):
            max_diff = -float('inf')
            m_j = mana[j]
            m_next = mana[j+1]
            
            # We need to find max over i: S[i+1]*m_j - S[i]*m_next
            # Note: S[i+1] = S[i] + skill[i]
            # Expression = (S[i] + skill[i])*m_j - S[i]*m_next
            #            = S[i]*(m_j - m_next) + skill[i]*m_j
            
            for i in range(n):
                diff = prefix_skills[i] * (m_j - m_next) + skill[i] * m_j
                if diff > max_diff:
                    max_diff = diff
            
            current_start_time += max_diff
            
        # Total time is the time when the last wizard finishes the last potion.
        # Total = T_{m-1} + S[n] * mana[m-1]
        return current_start_time + prefix_skills[n] * mana[m-1]