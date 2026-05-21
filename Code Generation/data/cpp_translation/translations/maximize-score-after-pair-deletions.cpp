// task_id: maximize-score-after-pair-deletions
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


class Solution {
public:
    long long maxScore(vector<int> nums) {
        long long s = 0;
        for (int x : nums) s += x;
        int n = (int)nums.size();
        if (n & 1) {
            int mn = nums[0];
            for (int x : nums) mn = min(mn, x);
            return s - mn;
        }
        long long best = LLONG_MAX;
        for (int i = 0; i + 1 < n; ++i) {
            best = min(best, (long long)nums[i] + nums[i+1]);
        }
        return s - best;
    }
};

int main() {
    Solution sol;

    assert((sol.maxScore(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 8LL));
    assert((sol.maxScore(vector<int>{5, -1, 4, 2}) == 7LL));
    assert((sol.maxScore(vector<int>{10000, -10000, 10000, -10000, 10000}) == 20000LL));
    assert((sol.maxScore(vector<int>{1, 2, 3}) == 5LL));
    assert((sol.maxScore(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 52LL));
    assert((sol.maxScore(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 52LL));
    assert((sol.maxScore(vector<int>{1}) == 0LL));
    assert((sol.maxScore(vector<int>{-5, 5, -5, 5, -5, 5}) == 0LL));
    assert((sol.maxScore(vector<int>{1, 2}) == 0LL));
    assert((sol.maxScore(vector<int>{10, -10, 20, -20, 30, -30, 40, -40, 50}) == 90LL));
    assert((sol.maxScore(vector<int>{5, 1, 5, 1, 5, 1, 5, 1, 5, 1}) == 24LL));
    assert((sol.maxScore(vector<int>{2, 4, 1}) == 6LL));
    assert((sol.maxScore(vector<int>{-1, -2, -3, -4, -5}) == -10LL));
    assert((sol.maxScore(vector<int>{-5, -4, -3, -2, -1}) == -10LL));
    assert((sol.maxScore(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1}) == 0LL));
    assert((sol.maxScore(vector<int>{10000, -10000, 10000, -10000, 10000}) == 20000LL));
    assert((sol.maxScore(vector<int>{1, 2, 3, 4, 5}) == 14LL));
    assert((sol.maxScore(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 8LL));
    assert((sol.maxScore(vector<int>{10, -10, 20, -20, 30}) == 50LL));
    assert((sol.maxScore(vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}) == 0LL));
    assert((sol.maxScore(vector<int>{100, -50, 200, -300, 400, -500, 600, -700, 800, -900}) == -250LL));
    assert((sol.maxScore(vector<int>{1, 2}) == 0LL));
    assert((sol.maxScore(vector<int>{0, 0, 0, 0, 0}) == 0LL));
    assert((sol.maxScore(vector<int>{1, -1, 2, -2, 3, -3}) == 0LL));
    assert((sol.maxScore(vector<int>{1, 2, 3}) == 5LL));
    assert((sol.maxScore(vector<int>{29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1}) == 224LL));
    assert((sol.maxScore(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29, 31}) == 252LL));
    assert((sol.maxScore(vector<int>{100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110}) == 1055LL));
    assert((sol.maxScore(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500}) == 11900LL));
    assert((sol.maxScore(vector<int>{10, -10, 20, -20, 30, -30, 40, -40, 50, -50, 60, -60, 70, -70, 80, -80, 90, -90, 100, -100}) == 0LL));
    assert((sol.maxScore(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10, -11, -12, -13, -14, -15, -16, -17, -18, -19, -20}) == -171LL));
    assert((sol.maxScore(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}) == 5200LL));
    assert((sol.maxScore(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 900, 800, 700, 600, 500, 400, 300, 200, 100}) == 9900LL));
    assert((sol.maxScore(vector<int>{0, 1, 0, -1, 0, 2, 0, -2, 0, 3, 0, -3, 0, 4, 0, -4, 0, 5, 0, -5}) == 5LL));
    assert((sol.maxScore(vector<int>{1000, -1000, 500, -500, 250, -250, 125, -125, 62, -62}) == 500LL));
    assert((sol.maxScore(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29}) == 224LL));
    assert((sol.maxScore(vector<int>{5, -5, 5, -5, 5, -5, 5, -5, 5, -5}) == 0LL));
    assert((sol.maxScore(vector<int>{100, -100, 200, -200, 300, -300, 400, -400, 500, -500}) == 0LL));
    assert((sol.maxScore(vector<int>{100, 100, -50, -50, 200, -300, 400, -500, 600, -700}) == -100LL));
    assert((sol.maxScore(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9, -10, 11, -12, 13, -14, 15, -16, 17, -18, 19, -20}) == -9LL));
    assert((sol.maxScore(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100, 1200, 1300, 1400, 1500, 1600, 1700, 1800, 1900, 2000}) == 20700LL));
    assert((sol.maxScore(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130}) == 900LL));
    assert((sol.maxScore(vector<int>{99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110}) == 1055LL));
    assert((sol.maxScore(vector<int>{-1, -3, -5, -7, -9, -11, -13, -15, -17, -19}) == -64LL));
    assert((sol.maxScore(vector<int>{3, 1, -2, 5, 7, -10, 15}) == 29LL));
    assert((sol.maxScore(vector<int>{-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110, -120, -130}) == -780LL));
    assert((sol.maxScore(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 28LL));
    assert((sol.maxScore(vector<int>{1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000, 1, 1000000}) == 5000005LL));
    assert((sol.maxScore(vector<int>{1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10}) == 65LL));
    assert((sol.maxScore(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 90, 80, 70, 60, 50, 40, 30, 20, 10}) == 990LL));
    assert((sol.maxScore(vector<int>{10, -20, 30, -40, 50, -60, 70}) == 100LL));
    assert((sol.maxScore(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25}) == 324LL));
    assert((sol.maxScore(vector<int>{1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000, 1, 2, 3, 4, 5}) == 1111111125LL));
    assert((sol.maxScore(vector<int>{-10, 100, -20, 200, -30, 300, -40, 400}) == 820LL));
    assert((sol.maxScore(vector<int>{5, 4, 3, 2, 1, 0, 1, 2, 3, 4, 5}) == 30LL));
    assert((sol.maxScore(vector<int>{1000, -1000, 2000, -2000, 3000, -3000, 4000, -4000, 5000, -5000}) == 0LL));
    assert((sol.maxScore(vector<int>{5, 1, 3, 7, 9, 2, 6, 4, 8, 10, 12, 14}) == 77LL));
    assert((sol.maxScore(vector<int>{5, 3, 8, 1, 9, 4, 7, 6, 2, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 202LL));
    assert((sol.maxScore(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}) == 52LL));
    assert((sol.maxScore(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5, 6, -6, 7, -7, 8, -8, 9, -9, 10, -10}) == 0LL));
    assert((sol.maxScore(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}) == 96LL));
    assert((sol.maxScore(vector<int>{-1, -3, -5, -7, -9, -11, -13, -15, -17, -19, -21, -23, -25, -27, -29}) == -196LL));
    assert((sol.maxScore(vector<int>{-10, -20, -30, -40, -50, -60, -70, -80, -90, -100, -110}) == -550LL));
    assert((sol.maxScore(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1}) == 2LL));
    assert((sol.maxScore(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == 119LL));
    assert((sol.maxScore(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, -500, -400, -300, -200, -100}) == 4500LL));
    assert((sol.maxScore(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}) == 52LL));
    assert((sol.maxScore(vector<int>{1, -2, 3, -4, 5, -6, 7, -8, 9, -10}) == -4LL));
    assert((sol.maxScore(vector<int>{-1, 2, -3, 4, -5, 6}) == 4LL));
    assert((sol.maxScore(vector<int>{10000, -10000, 10000, -10000, 10000, -10000}) == 0LL));
    assert((sol.maxScore(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 1100}) == 6500LL));
    assert((sol.maxScore(vector<int>{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5}) == 43LL));
    assert((sol.maxScore(vector<int>{1, 3, 2, 5, 4, 7, 6, 9, 8, 11, 10, 13, 12, 15, 14}) == 119LL));
    assert((sol.maxScore(vector<int>{-100, -200, 300, 400, -500, 600}) == 800LL));
    assert((sol.maxScore(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120}) == 750LL));
    assert((sol.maxScore(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}) == 207LL));
    assert((sol.maxScore(vector<int>{0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}) == 119LL));
    assert((sol.maxScore(vector<int>{-10, -9, -8, -7, -6, -5, -4, -3, -2, -1}) == -36LL));
    assert((sol.maxScore(vector<int>{1000, -999, 888, -777, 666, -555, 444, -333, 222, -111}) == 556LL));
    assert((sol.maxScore(vector<int>{10, -20, 30, -40, 50, -60, 70, -80, 90, -100}) == -40LL));
    assert((sol.maxScore(vector<int>{1, 3, 5, 7, 9, 11, 13}) == 48LL));
    assert((sol.maxScore(vector<int>{3, 1, 2, 4, 5, 6}) == 18LL));
    assert((sol.maxScore(vector<int>{-1, 1, -2, 2, -3, 3, -4, 4, -5, 5, -6, 6, -7, 7, -8, 8, -9, 9, -10, 10}) == 1LL));
    assert((sol.maxScore(vector<int>{5, 4, 3, 2, 1, 0, -1, -2, -3, -4, -5}) == 5LL));
    assert((sol.maxScore(vector<int>{-1, 2, -3, 4, -5, 6, -7, 8, -9, 10}) == 6LL));
    assert((sol.maxScore(vector<int>{5, 3, 8, 2, 4, 7, 1, 6, 9, 0}) == 39LL));
    assert((sol.maxScore(vector<int>{-100, -101, -102, -103, -104, -105, -106, -107, -108, -109, -110}) == -1045LL));
    assert((sol.maxScore(vector<int>{-1, -2, -3, -4, -5, -6, -7, -8, -9, -10}) == -36LL));
    assert((sol.maxScore(vector<int>{1, -1, 2, -2, 3, -3, 4, -4, 5, -5}) == 0LL));
    assert((sol.maxScore(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}) == 520LL));
    assert((sol.maxScore(vector<int>{5, -1, 4, 2, 3, 6, -2, 8, -3, 7}) == 26LL));
    assert((sol.maxScore(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}) == 18LL));
    assert((sol.maxScore(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1}) == 0LL));
    assert((sol.maxScore(vector<int>{-1000, 2000, -3000, 4000, -5000, 6000, -7000, 8000, -9000, 10000}) == 6000LL));
    assert((sol.maxScore(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}) == 44LL));
    assert((sol.maxScore(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5}) == 70LL));
    assert((sol.maxScore(vector<int>{1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89}) == 231LL));
    assert((sol.maxScore(vector<int>{1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1, 1, -1}) == 0LL));
    assert((sol.maxScore(vector<int>{100, -50, 25, -10, 15, 20, -30}) == 120LL));
    assert((sol.maxScore(vector<int>{0, 10000, -10000, 10000, -10000, 0, 10000, -10000, 10000, -10000}) == 10000LL));
    assert((sol.maxScore(vector<int>{1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000}) == 52000LL));

    cout << "All tests passed for maximize-score-after-pair-deletions" << endl;
    return 0;
}
