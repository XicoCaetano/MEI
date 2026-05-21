#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    int maxStudentsOnBench(vector<vector<int>> students) {
        if (students.empty()) {
            return 0;
        }

        // Use a map where the key is the bench_id and the value is a set 
        // of student_ids to handle unique students per bench automatically.
        unordered_map<int, unordered_set<int>> benchMap;

        for (const auto& entry : students) {
            int student_id = entry[0];
            int bench_id = entry[1];
            benchMap[bench_id].insert(student_id);
        }

        int maxUniqueStudents = 0;
        for (auto const& [benchId, studentSet] : benchMap) {
            int currentCount = static_cast<int>(studentSet.size());
            if (currentCount > maxUniqueStudents) {
                maxUniqueStudents = currentCount;
            }
        }

        return maxUniqueStudents;
    }
};