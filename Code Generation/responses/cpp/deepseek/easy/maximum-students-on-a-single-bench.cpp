#include <vector>
#include <unordered_map>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int maxStudentsOnBench(vector<vector<int>> students) {
        unordered_map<int, unordered_set<int>> bench_to_students;
        
        for (const auto& record : students) {
            int student_id = record[0];
            int bench_id = record[1];
            bench_to_students[bench_id].insert(student_id);
        }
        
        int max_unique = 0;
        for (const auto& entry : bench_to_students) {
            int unique_count = entry.second.size();
            if (unique_count > max_unique) {
                max_unique = unique_count;
            }
        }
        
        return max_unique;
    }
};