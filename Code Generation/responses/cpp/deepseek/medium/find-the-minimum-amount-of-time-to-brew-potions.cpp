#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    long long minTime(vector<int> skill, vector<int> mana) {
        int n = skill.size();
        int m = mana.size();
        
        // dp[j] will store the start time for wizard 0 on potion j
        vector<long long> start_time(m, 0);
        
        // Calculate prefix sums of skill times
        vector<long long> prefix_skill(n + 1, 0);
        for (int i = 0; i < n; i++) {
            prefix_skill[i + 1] = prefix_skill[i] + skill[i];
        }
        
        // For first potion, wizard 0 starts at 0
        start_time[0] = 0;
        
        // For each potion, we need to compute its start time
        for (int j = 1; j < m; j++) {
            // Initial guess: can start right after previous potion completion for wizard 0
            // But need to check constraints from all wizards
            long long latest_start = start_time[j - 1];
            
            // Check each wizard's availability
            for (int i = 0; i < n; i++) {
                // Time when wizard i finishes previous potion (potions j-1 and earlier)
                // Wizard i finishes previous potion at: start_time[j-1] + prefix_skill[i+1] * mana[j-1]
                // Actually careful: wizard i's finish time for potion k is start_time[k] + sum_{t=0 to i} skill[t] * mana[k]
                
                // Better approach: track when each wizard becomes free
                // Let's compute the earliest time wizard i can start potion j
                // It must be at least the time wizard i finishes previous potion
                // And wizard 0's start time determines everything
            }
            
            // More straightforward approach:
            // For potion j, let s = start_time[j] be what we want to find
            // Constraints:
            // 1. Wizard 0 can't start before previous potion's wizard 0 start time (but already guaranteed)
            // 2. For each wizard i, they must finish previous potion before starting this one
            //    That means: start_time[j] + sum_{t=0 to i} skill[t] * mana[j] >= start_time[j-1] + sum_{t=0 to i} skill[t] * mana[j-1]
            
            // So for each wizard i:
            // start_time[j] >= start_time[j-1] + sum_{t=0 to i} skill[t] * (mana[j-1] - mana[j])
            
            // But careful: wizard i's finish time for previous potion is start_time[j-1] + prefix_skill[i+1] * mana[j-1]
            // Their start time for current potion is start_time[j] + prefix_skill[i] * mana[j] (if we consider wizard i's start, not finish)
            
            // Let's derive properly:
            // For wizard i, they finish potion j-1 at: start_time[j-1] + prefix_skill[i+1] * mana[j-1]
            // They can start potion j at: start_time[j] + prefix_skill[i] * mana[j]
            // Constraint: start_time[j] + prefix_skill[i] * mana[j] >= start_time[j-1] + prefix_skill[i+1] * mana[j-1]
            
            // This gives:
            // start_time[j] >= start_time[j-1] + prefix_skill[i+1] * mana[j-1] - prefix_skill[i] * mana[j]
            
            // We need this for all i from 0 to n-1
            // Also, wizard 0's start time for current potion must be at least its finish time from previous?
            // Actually wizard 0's start time is directly start_time[j], no constraint except from wizard -1? No.
            
            // Let's implement the constraint for all i
            long long max_required = start_time[j-1];
            for (int i = 0; i < n; i++) {
                long long required = start_time[j-1] + prefix_skill[i+1] * mana[j-1] - prefix_skill[i] * mana[j];
                max_required = max(max_required, required);
            }
            
            start_time[j] = max_required;
        }
        
        // Calculate total time
        long long total_time = 0;
        for (int j = 0; j < m; j++) {
            total_time = max(total_time, start_time[j] + prefix_skill[n] * mana[j]);
        }
        
        return total_time;
    }
};