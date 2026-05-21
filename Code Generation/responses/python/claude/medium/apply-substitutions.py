from typing import List
import re

class Solution:
    def applySubstitutions(self, replacements: List[List[str]], text: str) -> str:
        mapping = {k: v for k, v in replacements}
        
        def resolve(key):
            val = mapping[key]
            return re.sub(r'%([A-Z])%', lambda m: resolve(m.group(1)), val)
        
        return re.sub(r'%([A-Z])%', lambda m: resolve(m.group(1)), text)