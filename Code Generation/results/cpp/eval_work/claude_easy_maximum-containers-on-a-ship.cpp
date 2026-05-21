// task_id: maximum-containers-on-a-ship
// difficulty: Easy

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
#include <algorithm>
using namespace std;

class Solution {
public:
    int maxContainers(int n, int w, int maxWeight) {
        return min(n * n, maxWeight / w);
    }
};

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.maxContainers(10, 5, 25) == 5));
    assert((sol.maxContainers(10, 1, 10) == 10));
    assert((sol.maxContainers(5, 2, 20) == 10));
    assert((sol.maxContainers(5, 10, 50) == 5));
    assert((sol.maxContainers(5, 10, 100) == 10));
    assert((sol.maxContainers(1000, 1000, 1000000000) == 1000000));
    assert((sol.maxContainers(2, 3, 15) == 4));
    assert((sol.maxContainers(7, 10, 50) == 5));
    assert((sol.maxContainers(1, 1, 1) == 1));
    assert((sol.maxContainers(7, 3, 60) == 20));
    assert((sol.maxContainers(4, 5, 10) == 2));
    assert((sol.maxContainers(7, 2, 50) == 25));
    assert((sol.maxContainers(3, 5, 20) == 4));
    assert((sol.maxContainers(1, 1, 1000) == 1));
    assert((sol.maxContainers(333, 334, 100000) == 299));
    assert((sol.maxContainers(150, 150, 22499) == 149));
    assert((sol.maxContainers(600, 50, 25000) == 500));
    assert((sol.maxContainers(800, 125, 10000000) == 80000));
    assert((sol.maxContainers(100, 50, 4500) == 90));
    assert((sol.maxContainers(100, 50, 4900) == 98));
    assert((sol.maxContainers(500, 200, 99999999) == 250000));
    assert((sol.maxContainers(250, 350, 875000) == 2500));
    assert((sol.maxContainers(200, 25, 4999) == 199));
    assert((sol.maxContainers(750, 100, 50000) == 500));
    assert((sol.maxContainers(100, 500, 45000) == 90));
    assert((sol.maxContainers(666, 166, 100000000) == 443556));
    assert((sol.maxContainers(400, 250, 1000000) == 4000));
    assert((sol.maxContainers(550, 800, 4400000) == 5500));
    assert((sol.maxContainers(400, 250, 100000) == 400));
    assert((sol.maxContainers(999, 500, 499500) == 999));
    assert((sol.maxContainers(100, 1001, 100100) == 100));
    assert((sol.maxContainers(750, 300, 675000) == 2250));
    assert((sol.maxContainers(600, 1200, 7200000) == 6000));
    assert((sol.maxContainers(333, 333, 333333333) == 110889));
    assert((sol.maxContainers(678, 9, 6000) == 666));
    assert((sol.maxContainers(250, 50, 12499) == 249));
    assert((sol.maxContainers(750, 200, 150000) == 750));
    assert((sol.maxContainers(5, 200, 999) == 4));
    assert((sol.maxContainers(999, 999, 998001) == 999));
    assert((sol.maxContainers(800, 500, 399999) == 799));
    assert((sol.maxContainers(600, 400, 250000) == 625));
    assert((sol.maxContainers(666, 150, 100000) == 666));
    assert((sol.maxContainers(250, 400, 100000) == 250));
    assert((sol.maxContainers(1000, 1, 500) == 500));
    assert((sol.maxContainers(5, 100, 200) == 2));
    assert((sol.maxContainers(250, 400, 1000000) == 2500));
    assert((sol.maxContainers(1000, 500, 500000) == 1000));
    assert((sol.maxContainers(400, 200, 79999) == 399));
    assert((sol.maxContainers(500, 200, 1000000) == 5000));
    assert((sol.maxContainers(400, 50, 99999) == 1999));
    assert((sol.maxContainers(200, 999, 200000) == 200));
    assert((sol.maxContainers(200, 15, 5000) == 333));
    assert((sol.maxContainers(300, 150, 50000) == 333));
    assert((sol.maxContainers(900, 300, 270000) == 900));
    assert((sol.maxContainers(500, 7, 350000) == 50000));
    assert((sol.maxContainers(500, 750, 300000) == 400));
    assert((sol.maxContainers(200, 1, 100) == 100));
    assert((sol.maxContainers(800, 10, 8000) == 800));
    assert((sol.maxContainers(900, 950, 855000000) == 810000));
    assert((sol.maxContainers(500, 50, 125000) == 2500));
    assert((sol.maxContainers(800, 50, 20000) == 400));
    assert((sol.maxContainers(750, 50, 180000) == 3600));
    assert((sol.maxContainers(666, 667, 500000) == 749));
    assert((sol.maxContainers(10, 10, 99) == 9));
    assert((sol.maxContainers(1000, 900, 900000) == 1000));
    assert((sol.maxContainers(5, 5000, 25000) == 5));
    assert((sol.maxContainers(250, 75, 20000) == 266));
    assert((sol.maxContainers(1000, 1000, 999999999) == 999999));
    assert((sol.maxContainers(999, 1, 999) == 999));
    assert((sol.maxContainers(250, 100, 24900) == 249));
    assert((sol.maxContainers(500, 250, 100000000) == 250000));
    assert((sol.maxContainers(999, 999, 999000000) == 998001));
    assert((sol.maxContainers(999, 1, 1000000000) == 998001));
    assert((sol.maxContainers(1000, 999, 998001) == 999));
    assert((sol.maxContainers(750, 150, 112500) == 750));
    assert((sol.maxContainers(500, 50, 100000) == 2000));
    assert((sol.maxContainers(800, 1000, 800000) == 800));
    assert((sol.maxContainers(333, 333, 33266667) == 99899));
    assert((sol.maxContainers(1, 1000000000, 1000000000) == 1));
    assert((sol.maxContainers(600, 60, 359999) == 5999));
    assert((sol.maxContainers(200, 300, 60000) == 200));
    assert((sol.maxContainers(123, 456, 67890123) == 15129));
    assert((sol.maxContainers(300, 100, 25000) == 250));
    assert((sol.maxContainers(200, 1000, 199000) == 199));
    assert((sol.maxContainers(750, 123, 1000000) == 8130));
    assert((sol.maxContainers(10, 999, 9990) == 10));
    assert((sol.maxContainers(500, 250, 125000) == 500));
    assert((sol.maxContainers(800, 100, 80000) == 800));
    assert((sol.maxContainers(300, 700, 2000000) == 2857));
    assert((sol.maxContainers(500, 2, 1000) == 500));
    assert((sol.maxContainers(300, 200, 60000) == 300));
    assert((sol.maxContainers(800, 10, 7900) == 790));
    assert((sol.maxContainers(500, 10, 4990) == 499));
    assert((sol.maxContainers(800, 150, 1200000) == 8000));
    assert((sol.maxContainers(800, 125, 100000) == 800));
    assert((sol.maxContainers(650, 100, 70000) == 700));
    assert((sol.maxContainers(750, 75, 450000) == 6000));
    assert((sol.maxContainers(50, 200, 19999) == 99));
    assert((sol.maxContainers(500, 750, 375000) == 500));
    assert((sol.maxContainers(400, 400, 599999) == 1499));
    assert((sol.maxContainers(10, 100, 1000) == 10));
    assert((sol.maxContainers(250, 333, 83250) == 250));
    assert((sol.maxContainers(50, 100, 4500) == 45));
    assert((sol.maxContainers(150, 25, 3749) == 149));
    assert((sol.maxContainers(900, 50, 45000) == 900));
    assert((sol.maxContainers(100, 10, 999) == 99));
    assert((sol.maxContainers(1000, 1, 999) == 999));
    assert((sol.maxContainers(750, 300, 500000000) == 562500));
    assert((sol.maxContainers(15, 15, 225) == 15));
    assert((sol.maxContainers(750, 20, 14500) == 725));
    assert((sol.maxContainers(500, 250, 500000) == 2000));
    assert((sol.maxContainers(1000, 10, 9999999) == 999999));
    assert((sol.maxContainers(100, 100, 5000) == 50));
    assert((sol.maxContainers(333, 250, 200000) == 800));
    assert((sol.maxContainers(900, 90, 729000) == 8100));

    cout << "All tests passed for maximum-containers-on-a-ship" << endl;
    return 0;
}
