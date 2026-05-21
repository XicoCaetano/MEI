from typing import List
import re

class Solution:
    def applySubstitutions(self, replacements: List[List[str]], text: str) -> str:
        # Convert replacements list to a dictionary for O(1) lookup
        mapping = {k: v for k, v in replacements}
        
        # Cache for memoization to handle nested substitutions efficiently
        memo = {}

        def resolve(val: str) -> str:
            """
            Recursively resolves all placeholders within a string.
            Since the problem guarantees no cyclic dependencies, this will terminate.
            """
            if val in memo:
                return memo[val]
            
            # Find all placeholders formatted as %VAR%
            # We use a while loop or regex sub to ensure we catch all nested instances
            result = val
            while '%' in result:
                # Find the first occurrence of a placeholder
                match = re.search(r'%([A-Z])%', result)
                if not match:
                    break
                
                placeholder = match.group(0) # e.g., "%A%"
                key = match.group(1)         # e.g., "A"
                
                # Recursively resolve the replacement value associated with the key
                replacement_resolved = resolve(mapping[key])
                
                # Replace the placeholder with its fully resolved value
                # We replace all occurrences of this specific key to be efficient
                result = result.replace(placeholder, replacement_resolved)
            
            memo[val] = result
            return result

        # The initial text is just another string that may contain placeholders
        return resolve(text)