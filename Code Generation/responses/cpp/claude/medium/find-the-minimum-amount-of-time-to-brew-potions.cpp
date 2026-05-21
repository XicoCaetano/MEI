#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    long long minTime(vector<int> skill, vector<int> mana) {
        int n = skill.size(), m = mana.size();
        // start[j] = start time of potion j
        vector<long long> start(m, 0);
        
        // For each potion, compute earliest start time
        // given the previous potion's schedule
        // We track finish[i] = when wizard i finishes potion j
        vector<long long> finish(n, 0);
        
        for (int j = 0; j < m; j++) {
            // Try to start potion j as early as possible
            // Must ensure wizard i starts exactly when potion arrives
            // i.e., finish[i-1] (of this potion) == start of wizard i on this potion
            
            // Compute prefix sums of skill
            // wizard i works from (start + prefix[i]) to (start + prefix[i+1])
            // where prefix[i] = sum(skill[0..i-1]) * mana[j]
            
            long long s = 0; // candidate start time
            if (j == 0) {
                s = 0;
            } else {
                s = finish[0] - (long long)skill[0] * mana[j];
                if (s < 0) s = 0;
            }
            
            // Now check each wizard: wizard i must start at s + prefixSkill[i]*mana[j]
            // wizard i must start >= finish[i] (done with previous potion)
            // So s >= finish[i] - prefixSkill[i]*mana[j]
            
            long long prefSkill = 0;
            for (int i = 0; i < n; i++) {
                // wizard i starts at s + prefSkill * mana[j]
                // must be >= finish[i]
                long long earliest = finish[i] - prefSkill * (long long)mana[j];
                if (earliest > s) s = earliest;
                prefSkill += skill[i];
            }
            
            start[j] = s;
            // Update finish times
            prefSkill = 0;
            for (int i = 0; i < n; i++) {
                prefSkill += skill[i];