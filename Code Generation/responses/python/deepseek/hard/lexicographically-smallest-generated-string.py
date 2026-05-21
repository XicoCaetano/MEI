class Solution:
    def generateString(self, str1: str, str2: str) -> str:
        n = len(str1)
        m = len(str2)
        
        # Create constraints: for each position i, we need to ensure str2 matches or doesn't match
        # We'll build a graph where each node represents a position in the word (0 to n+m-2)
        # and we'll store constraints as equalities or inequalities between characters
        
        # First, handle the case when n == 1
        if n == 1:
            if str1[0] == 'T':
                return str2
            else:
                # Find smallest character not equal to str2[0] at position 0
                result = []
                # We need a string of length m, with word[0..m-1] != str2
                # Try to make it lexicographically smallest
                for i in range(m):
                    # At position i, try to put a character different from str2[i] if possible
                    # But we need to make the whole string as small as possible
                    # Actually simpler: try to find smallest string of length m that is not equal to str2
                    result.append('a')
                result_str = ''.join(result)
                if result_str == str2:
                    # If it equals str2, change last character to next smallest
                    result = list(result_str)
                    for j in range(m-1, -1, -1):
                        if result[j] < 'z':
                            result[j] = chr(ord(result[j]) + 1)
                            return ''.join(result)
                    return ''
                return result_str
        
        # For n > 1, we need to construct the string
        # The word length is L = n + m - 1
        L = n + m - 1
        word = [''] * L
        
        # First, handle all 'T' constraints
        # They force the string to have str2 at those positions
        forced_chars = [None] * L  # None means not forced, otherwise a character
        for i in range(n):
            if str1[i] == 'T':
                # word[i:i+m] must equal str2
                for j in range(m):
                    if forced_chars[i + j] is not None and forced_chars[i + j] != str2[j]:
                        return ""  # Conflict
                    forced_chars[i + j] = str2[j]
        
        # Now fill in forced characters
        for i in range(L):
            if forced_chars[i] is not None:
                word[i] = forced_chars[i]
        
        # Now handle 'F' constraints
        # For each 'F', we need word[i:i+m] != str2
        # This means there must be at least one position j in [0,m-1] where 
        # either word[i+j] is already set to a character different from str2[j],
        # or we can set it to a character different from str2[j]
        
        # For each position, we need to find the earliest character to put
        # to make the string lexicographically smallest
        
        # First pass: fill as many 'a's as possible
        for i in range(L):
            if word[i] == '':
                word[i] = 'a'
        
        # Now check all constraints and adjust if needed
        # For 'F', if the current word[i:i+m] == str2, we need to change
        # at least one character in that segment
        
        # We need to process positions from left to right to ensure lexicographically smallest
        for i in range(n):
            if str1[i] == 'F':
                # Check if word[i:i+m] == str2
                matches = True
                for j in range(m):
                    if word[i + j] != str2[j]:
                        matches = False
                        break
                
                if matches:
                    # Need to change at the rightmost position possible to get smallest lex order
                    # Try to increase the last character to next character
                    changed = False
                    for j in range(m-1, -1, -1):
                        pos = i + j
                        # Try to increase this character if possible
                        if word[pos] < 'z':
                            word[pos] = chr(ord(word[pos]) + 1)
                            changed = True
                            # Make all following positions 'a' again
                            for k in range(pos + 1, L):
                                word[k] = 'a'
                            break
                    if not changed:
                        return ""  # Cannot change any character
        
        # Second pass: check all constraints again
        # Also need to consider indirect conflicts: changing one position might
        # violate other constraints
        
        # We need to be more thorough: treat as a graph of constraints
        # Let's use backtracking for correctness since n<=10^4 is large but m<=500
        # Actually, we can solve greedily from left to right
        
        # Better approach: process from left to right, making decisions
        # Reset and try greedy with backtracking if needed
        return self.greedy_solve(str1, str2, n, m, L)
    
    def greedy_solve(self, str1: str, str2: str, n: int, m: int, L: int) -> str:
        word = [''] * L
        
        # First, handle forced characters from 'T'
        forced = [None] * L
        for i in range(n):
            if str1[i] == 'T':
                for j in range(m):
                    if forced[i+j] is not None and forced[i+j] != str2[j]:
                        return ""
                    forced[i+j] = str2[j]
        
        # Fill forced characters
        for i in range(L):
            if forced[i] is not None:
                word[i] = forced[i]
        
        # Now fill remaining positions with 'a'
        for i in range(L):
            if word[i] == '':
                word[i] = 'a'
        
        # We'll use a list of constraints for 'F' positions that currently match
        # and fix them from right to left
        
        # Process multiple times until stable
        changed = True
        while changed:
            changed = False
            # Process from left to right
            for i in range(n):
                if str1[i] == 'F':
                    # Check if this segment equals str2
                    matches = True
                    match_pos = -1
                    for j in range(m):
                        if word[i+j] != str2[j]:
                            matches = False
                            break
                    
                    if matches:
                        # Need to change at some position in [i, i+m-1]
                        # Choose the rightmost position that can be increased
                        for j in range(m-1, -1, -1):
                            pos = i + j
                            if word[pos] < 'z' and (forced[pos] is None or word[pos] != forced[pos]):
                                # This position is not forced to be something specific
                                # Increase it
                                word[pos] = chr(ord(word[pos]) + 1)
                                # Reset all positions to the right to 'a'
                                for k in range(pos + 1, L):
                                    if forced[k] is None:
                                        word[k] = 'a'
                                changed = True
                                break
                        if not changed:
                            return ""  # Cannot fix this constraint
        
        # Final check all constraints
        for i in range(n):
            segment = ''.join(word[i:i+m])
            if str1[i] == 'T':
                if segment != str2:
                    return ""
            else:  # 'F'
                if segment == str2:
                    return ""
        
        return ''.join(word)