#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

class Solution {
public:
    long long minTime(vector<int> skill, vector<int> mana) {
        int n = skill.size();
        int m = mana.size();

        // Let S[i] be the prefix sum of skills: S[i] = skill[0] + ... + skill[i-1].
        // The time wizard i finishes potion j is:
        // T(i, j) = StartTime(j) + (skill[0] + ... + skill[i]) * mana[j]
        // T(i, j) = StartTime(j) + S[i+1] * mana[j]
        
        // The core constraint: Wizard i must finish potion j before or at the same time
        // they start potion j+1. 
        // Potion j+1 arrives at wizard i at time: StartTime(j+1) + S[i] * mana[j+1]
        // So: T(i, j) <= StartTime(j+1) + S[i] * mana[j+1]
        // StartTime(j) + S[i+1] * mana[j] <= StartTime(j+1) + S[i] * mana[j+1]
        // StartTime(j+1) >= StartTime(j) + S[i+1] * mana[j] - S[i] * mana[j+1]
        
        // This must hold for all i from 0 to n-1. To minimize total time, 
        // we minimize StartTime(j+1):
        // StartTime(j+1) = StartTime(j) + max_{0 <= i < n} (S[i+1] * mana[j] - S[i] * mana[j+1])
        
        vector<long long> S(n + 1, 0);
        for (int i = 0; i < n; ++i) {
            S[i + 1] = S[i] + skill[i];
        }

        long long currentStartTime = 0;
        for (int j = 0; j < m - 1; ++j) {
            long long maxWait = 0;
            for (int i = 0; i < n; ++i) {
                long long constraint = (long long)S[i + 1] * mana[j] - (long long)S[i] * mana[j + 1];
                if (constraint > maxWait) {
                    maxWait = constraint;
                }
            }
            currentStartTime += maxWait;
        }

        // The total time is the time the last wizard (n-1) finishes the last potion (m-1)
        // Total Time = StartTime(m-1) + S[n] * mana[m-1]
        return currentStartTime + (long long)S[n] * mana[m - 1];
    }
};