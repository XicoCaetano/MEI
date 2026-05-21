from typing import List
from collections import defaultdict

class Solution:
    def maxStudentsOnBench(self, students: List[List[int]]) -> int:
        if not students:
            return 0
            
        benches = defaultdict(set)
        
        for student_id, bench_id in students:
            benches[bench_id].add(student_id)
            
        return max(len(unique_students) for unique_students in benches.values())