from typing import List

class Solution:
    def maxStudentsOnBench(self, students: List[List[int]]) -> int:
        if not students:
            return 0
        
        bench_students = {}
        
        for student_id, bench_id in students:
            if bench_id not in bench_students:
                bench_students[bench_id] = set()
            bench_students[bench_id].add(student_id)
        
        max_unique = 0
        for students_set in bench_students.values():
            max_unique = max(max_unique, len(students_set))
        
        return max_unique