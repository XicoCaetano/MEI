// task_id: find-the-minimum-amount-of-time-to-brew-potions
// difficulty: Medium

#include <cassert>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <set>
#include <algorithm>
#include <cmath>
#include <climits>
#include <numeric>
#include <queue>
#include <stack>
#include <deque>
#include <functional>
#include <utility>
#include <tuple>

using namespace std;



// === MODEL RESPONSE ===
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

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.minTime(vector<int>{10, 20, 30}, vector<int>{1, 2, 3, 4, 5}) == 490LL));
    assert((sol.minTime(vector<int>{3, 2, 1}, vector<int>{6, 5, 4}) == 57LL));
    assert((sol.minTime(vector<int>{1, 1, 1}, vector<int>{1, 1, 1}) == 5LL));
    assert((sol.minTime(vector<int>{1, 2, 3}, vector<int>{4, 5, 6, 7}) == 78LL));
    assert((sol.minTime(vector<int>{5000, 5000}, vector<int>{1, 5000}) == 50005000LL));
    assert((sol.minTime(vector<int>{1, 2, 3}, vector<int>{4, 5, 6, 7, 8}) == 102LL));
    assert((sol.minTime(vector<int>{1, 5, 2, 4}, vector<int>{5, 1, 4, 2}) == 110LL));
    assert((sol.minTime(vector<int>{10, 20, 30}, vector<int>{1, 2, 3, 4, 5}) == 490LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4}, vector<int>{1, 2}) == 21LL));
    assert((sol.minTime(vector<int>{5000, 5000, 5000}, vector<int>{5000, 5000, 5000}) == 125000000LL));
    assert((sol.minTime(vector<int>{3, 1, 4, 1, 5}, vector<int>{9, 2, 6, 5, 3, 5}) == 275LL));
    assert((sol.minTime(vector<int>{2, 3, 4, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7}) == 159LL));
    assert((sol.minTime(vector<int>{1, 1, 2, 2, 3, 3}, vector<int>{1, 2, 3, 4, 5, 6}) == 94LL));
    assert((sol.minTime(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 10, 15, 20, 25}) == 4750LL));
    assert((sol.minTime(vector<int>{2, 3, 5, 7, 11, 13, 17, 19}, vector<int>{23, 29, 31, 37, 41, 43, 47, 53, 59, 61}) == 9500LL));
    assert((sol.minTime(vector<int>{2, 3, 5, 7, 11}, vector<int>{13, 17, 19, 23, 29, 31, 37, 41}) == 2531LL));
    assert((sol.minTime(vector<int>{100, 100, 100, 100, 100}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 9500LL));
    assert((sol.minTime(vector<int>{5, 5, 5, 5, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 475LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 3375LL));
    assert((sol.minTime(vector<int>{4999, 4998, 4997, 4996}, vector<int>{5000, 4999, 4998, 4997, 4996}) == 199820050LL));
    assert((sol.minTime(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{10, 20, 30, 40, 50}) == 29500LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400, 500}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}) == 295000LL));
    assert((sol.minTime(vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}, vector<int>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29}) == 4585LL));
    assert((sol.minTime(vector<int>{300, 200, 100, 400, 500}, vector<int>{100, 200, 300, 400, 500}) == 1050000LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5, 6}, vector<int>{6, 5, 4, 3, 2, 1}) == 216LL));
    assert((sol.minTime(vector<int>{4, 3, 2, 1}, vector<int>{100, 200, 300, 400, 500}) == 9000LL));
    assert((sol.minTime(vector<int>{1000, 2000, 3000, 4000, 5000}, vector<int>{1000, 2000, 3000, 4000, 5000}) == 95000000LL));
    assert((sol.minTime(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) == 2660LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{5000, 5000, 5000, 5000, 5000}) == 475000LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400, 500, 600}, vector<int>{600, 500, 400, 300, 200, 100}) == 2160000LL));
    assert((sol.minTime(vector<int>{10, 20, 30, 40, 50}, vector<int>{5, 10, 15, 20, 25, 30}) == 6250LL));
    assert((sol.minTime(vector<int>{25, 50, 75, 100, 125, 150, 175, 200, 225, 250}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}) == 1787500LL));
    assert((sol.minTime(vector<int>{100, 200, 300}, vector<int>{50, 25, 75, 100}) == 100000LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}) == 2950LL));
    assert((sol.minTime(vector<int>{5, 3, 8, 2, 4}, vector<int>{15, 25, 10, 40, 5}) == 1395LL));
    assert((sol.minTime(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}) == 1771LL));
    assert((sol.minTime(vector<int>{29, 65, 12, 48, 77}, vector<int>{31, 89, 17, 63, 54, 20, 41, 73}) == 54255LL));
    assert((sol.minTime(vector<int>{1, 5, 10, 20, 50, 100, 200}, vector<int>{1, 2, 3, 4, 5, 6, 7}) == 5786LL));
    assert((sol.minTime(vector<int>{1500, 1500, 1500, 1500}, vector<int>{2500, 2500, 2500, 2500, 2500}) == 30000000LL));
    assert((sol.minTime(vector<int>{4000, 3000, 2000, 1000}, vector<int>{1000, 2000, 3000, 4000, 5000}) == 90000000LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400, 500}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 29500LL));
    assert((sol.minTime(vector<int>{3, 6, 9, 12}, vector<int>{10, 20, 30, 40, 50}) == 2100LL));
    assert((sol.minTime(vector<int>{1, 1, 1, 1, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 95LL));
    assert((sol.minTime(vector<int>{1000, 2000, 3000}, vector<int>{500, 1000, 1500, 2000, 2500}) == 24500000LL));
    assert((sol.minTime(vector<int>{100, 150, 200, 250, 300}, vector<int>{50, 100, 150, 200, 250, 300, 350}) == 505000LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}) == 7150LL));
    assert((sol.minTime(vector<int>{7, 14, 21, 28}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16}) == 2156LL));
    assert((sol.minTime(vector<int>{2, 4, 6, 8, 10, 12}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15}) == 908LL));
    assert((sol.minTime(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}, vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}) == 17875LL));
    assert((sol.minTime(vector<int>{3000, 2500, 2000, 1500}, vector<int>{1000, 1200, 1400, 1600, 1800}) == 31800000LL));
    assert((sol.minTime(vector<int>{500, 1000, 1500, 2000}, vector<int>{200, 400, 600, 800, 1000, 1200}) == 9400000LL));
    assert((sol.minTime(vector<int>{100, 100, 100, 100, 100}, vector<int>{100, 100, 100, 100, 100, 100, 100, 100, 100, 100}) == 140000LL));
    assert((sol.minTime(vector<int>{2, 4, 6, 8, 10, 12}, vector<int>{12, 10, 8, 6, 4, 2}) == 864LL));
    assert((sol.minTime(vector<int>{100, 200, 150, 50, 250}, vector<int>{50, 75, 100, 125, 150}) == 172500LL));
    assert((sol.minTime(vector<int>{2, 4, 6, 8, 10}, vector<int>{1, 3, 5, 7, 9}) == 330LL));
    assert((sol.minTime(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}) == 35750LL));
    assert((sol.minTime(vector<int>{4, 2, 6, 5, 1}, vector<int>{9, 3, 7, 8, 2, 10}) == 465LL));
    assert((sol.minTime(vector<int>{2, 4, 6, 8, 10}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 120LL));
    assert((sol.minTime(vector<int>{5000, 5000, 5000, 5000}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 425000LL));
    assert((sol.minTime(vector<int>{1, 3, 2, 4, 5}, vector<int>{2, 1, 3, 4, 5}) == 115LL));
    assert((sol.minTime(vector<int>{5, 10, 15, 20, 25}, vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == 1500LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 715LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}) == 71500LL));
    assert((sol.minTime(vector<int>{100, 200, 150, 50}, vector<int>{300, 250, 400, 100, 350}) == 440000LL));
    assert((sol.minTime(vector<int>{50, 40, 30, 20, 10}, vector<int>{25, 20, 15, 10, 5}) == 4750LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400}, vector<int>{10, 20, 30, 40, 50, 60}) == 94000LL));
    assert((sol.minTime(vector<int>{7, 14, 21, 28, 35}, vector<int>{35, 28, 21, 14, 7}) == 6125LL));
    assert((sol.minTime(vector<int>{42, 15, 88, 34, 99, 56}, vector<int>{72, 33, 19, 55, 48, 62, 28}) == 53845LL));
    assert((sol.minTime(vector<int>{2500, 1000, 5000, 3000}, vector<int>{5000, 2000, 1000, 3000, 4000}) == 115000000LL));
    assert((sol.minTime(vector<int>{500, 1000, 1500, 2000}, vector<int>{500, 1000, 1500, 2000, 2500}) == 17500000LL));
    assert((sol.minTime(vector<int>{10, 20, 30, 40, 50}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 2950LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 10, 15, 20, 25}) == 475LL));
    assert((sol.minTime(vector<int>{3, 7, 5, 2, 8}, vector<int>{4, 6, 2, 9, 1}) == 377LL));
    assert((sol.minTime(vector<int>{5, 3, 8, 6, 2}, vector<int>{7, 1, 4, 2, 9, 5, 3}) == 469LL));
    assert((sol.minTime(vector<int>{500, 1000, 1500, 2000}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800}) == 7700000LL));
    assert((sol.minTime(vector<int>{1000, 2000, 3000, 4000, 5000}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 295000LL));
    assert((sol.minTime(vector<int>{1000, 2000, 3000, 4000, 5000}, vector<int>{1, 10, 100, 1000, 10000}) == 151111000LL));
    assert((sol.minTime(vector<int>{10, 15, 20, 25, 30}, vector<int>{35, 40, 45, 50, 55, 60, 65, 70}) == 15050LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400}, vector<int>{5, 10, 15, 20, 25, 30}) == 47000LL));
    assert((sol.minTime(vector<int>{1000, 2000, 3000, 4000, 5000}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150}) == 6200000LL));
    assert((sol.minTime(vector<int>{300, 200, 100}, vector<int>{5, 15, 25, 35, 45, 55}) == 70500LL));
    assert((sol.minTime(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}) == 3439LL));
    assert((sol.minTime(vector<int>{2, 5, 7, 8}, vector<int>{1, 3, 6, 9, 12}) == 341LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}) == 715000LL));
    assert((sol.minTime(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 1000LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400}, vector<int>{50, 60, 70, 80, 90}) == 170000LL));
    assert((sol.minTime(vector<int>{100, 200, 300, 400, 500}, vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}) == 147500LL));
    assert((sol.minTime(vector<int>{300, 200, 100}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == 40500LL));
    assert((sol.minTime(vector<int>{3, 7, 2, 8}, vector<int>{6, 4, 9, 1, 5}) == 356LL));
    assert((sol.minTime(vector<int>{1, 3, 2, 4}, vector<int>{2, 3, 4, 5}) == 74LL));
    assert((sol.minTime(vector<int>{1, 10, 100, 1000}, vector<int>{1, 10, 100, 1000, 10000}) == 11111111LL));
    assert((sol.minTime(vector<int>{5, 10, 15, 20, 25, 30}, vector<int>{1, 3, 5, 7, 9}) == 1095LL));
    assert((sol.minTime(vector<int>{1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 24LL));
    assert((sol.minTime(vector<int>{500, 1000, 1500, 2000, 2500}, vector<int>{250, 500, 750, 1000, 1250}) == 11875000LL));
    assert((sol.minTime(vector<int>{3, 6, 9, 12, 15}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) == 1770LL));
    assert((sol.minTime(vector<int>{5000, 4000, 3000, 2000, 1000}, vector<int>{1000, 2000, 3000, 4000, 5000}) == 125000000LL));
    assert((sol.minTime(vector<int>{1, 10, 100, 1000, 5000}, vector<int>{1, 10, 100, 1000, 5000}) == 31111111LL));
    assert((sol.minTime(vector<int>{4000, 3000, 2000, 1000, 500}, vector<int>{500, 1000, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000}) == 142500000LL));
    assert((sol.minTime(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}) == 2660LL));
    assert((sol.minTime(vector<int>{3, 5, 7, 9}, vector<int>{2, 4, 6, 8}) == 238LL));
    assert((sol.minTime(vector<int>{5000, 1000, 2000, 3000, 4000}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}) == 37500000LL));
    assert((sol.minTime(vector<int>{1500, 1500, 1500, 1500}, vector<int>{500, 1000, 1500, 2000, 2500, 3000}) == 29250000LL));
    assert((sol.minTime(vector<int>{2, 3, 5, 7, 11}, vector<int>{13, 17, 19, 23, 29, 31, 37}) == 2080LL));

    cout << "All tests passed for find-the-minimum-amount-of-time-to-brew-potions" << endl;
    return 0;
}
