from typing import List

class Solution:
    def applySubstitutions(self, replacements: List[List[str]], text: str) -> str:
        # Create a dictionary for quick lookup
        mapping = {key: value for key, value in replacements}
        
        # Define a recursive function to resolve placeholders
        def resolve(s: str) -> str:
            result = []
            i = 0
            n = len(s)
            while i < n:
                if i < n - 2 and s[i] == '%' and s[i + 2] == '%' and s[i + 1].isalpha():
                    # Found a placeholder %X%
                    key = s[i + 1]
                    placeholder_content = '%' + key + '%'
                    # Resolve the replacement value recursively
                    resolved_value = resolve(mapping[key])
                    result.append(resolved_value)
                    i += 3  # Skip the placeholder %X%
                else:
                    result.append(s[i])
                    i += 1
            return ''.join(result)
        
        # Resolve the entire text
        return resolve(text)