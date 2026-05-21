from typing import List
from collections import defaultdict

class Solution:
    def maxStudentsOnBench(self, students: List[List[int]]) -> int:
        bench = defaultdict(set)
        for student_id, bench_id in students:
            bench[bench_id].add(student_id)
        return max((len(s) for s in bench.values()), default=0)