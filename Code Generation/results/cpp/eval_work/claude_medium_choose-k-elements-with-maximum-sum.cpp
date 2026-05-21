// task_id: choose-k-elements-with-maximum-sum
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
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

class Solution {
public:
    vector<long long> findMaxSum(vector<int> nums1, vector<int> nums2, int k) {
        int n = nums1.size();
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int a, int b){
            return nums1[a] < nums1[b];
        });
        
        vector<long long> ans(n, 0);
        priority_queue<int, vector<int>, greater<int>> minHeap; // min-heap of size k
        long long heapSum = 0;
        
        int i = 0;
        while (i < n) {
            // Group all indices with same nums1 value
            int j = i;
            while (j < n && nums1[idx[j]] == nums1[idx[i]]) j++;
            
            // For all in [i, j), the heap currently holds eligible nums2 values
            for (int t = i; t < j; t++) {
                ans[idx[t]] = heapSum;
            }
            
            // Now add nums2 values for indices in [i, j) to heap
            for (int t = i; t < j; t++) {
                int val = nums2[idx[t]];
                minHeap.push(val);
                heapSum += val;
                if ((int)minHeap.size() > k) {
                    heapSum -= minHeap.top();
                    minHeap.pop();
                }
            }
            
            i = j;
        }
        
        return ans;
    }
};

// === TEST HARNESS ===
int main() {
    Solution sol;

    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50}, vector<int>{50, 40, 30, 20, 10}, 2) == vector<long long>{0LL, 50LL, 90LL, 90LL, 90LL}));
    assert((sol.findMaxSum(vector<int>{100000, 90000, 80000, 70000, 60000}, vector<int>{1, 2, 3, 4, 5}, 4) == vector<long long>{14LL, 12LL, 9LL, 5LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1}, vector<int>{5, 5, 5, 5, 5}, 5) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5}, 2) == vector<long long>{9LL, 9LL, 9LL, 5LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 5, 5, 5, 5}, vector<int>{1, 2, 3, 4, 5}, 5) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, 3) == vector<long long>{0LL, 5LL, 9LL, 12LL, 12LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50}, vector<int>{1, 1, 1, 1, 1}, 5) == vector<long long>{0LL, 1LL, 2LL, 3LL, 4LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 5, 7, 9}, vector<int>{9, 7, 5, 3, 1}, 3) == vector<long long>{0LL, 9LL, 16LL, 21LL, 21LL}));
    assert((sol.findMaxSum(vector<int>{4, 2, 1, 5, 3}, vector<int>{10, 20, 30, 40, 50}, 2) == vector<long long>{80LL, 30LL, 0LL, 80LL, 50LL}));
    assert((sol.findMaxSum(vector<int>{2, 2, 2, 2}, vector<int>{3, 1, 2, 3}, 1) == vector<long long>{0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3) == vector<long long>{0LL, 10LL, 30LL, 60LL, 90LL, 120LL, 150LL, 180LL, 210LL, 240LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{5, 5, 4, 4, 3, 3, 2, 2, 1, 1}, 3) == vector<long long>{0LL, 0LL, 10LL, 10LL, 14LL, 14LL, 14LL, 14LL, 14LL, 14LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 10) == vector<long long>{0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 6LL, 7LL, 8LL, 9LL}));
    assert((sol.findMaxSum(vector<int>{100, 200, 300, 400, 500}, vector<int>{5, 10, 15, 20, 25}, 1) == vector<long long>{0LL, 5LL, 10LL, 15LL, 20LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 10) == vector<long long>{0LL, 1LL, 4LL, 9LL, 16LL, 25LL, 36LL, 49LL, 64LL, 81LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == vector<long long>{0LL, 1LL, 3LL, 6LL, 10LL, 15LL, 20LL, 25LL, 30LL, 35LL}));
    assert((sol.findMaxSum(vector<int>{100000, 100000, 100000, 100000, 100000}, vector<int>{50000, 60000, 70000, 80000, 90000}, 3) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1, 0, 6, 7, 8, 9}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3) == vector<long long>{150LL, 150LL, 150LL, 110LL, 60LL, 0LL, 150LL, 180LL, 210LL, 240LL}));
    assert((sol.findMaxSum(vector<int>{5, 5, 5, 5, 5, 5, 5, 5, 5, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, 2) == vector<long long>{0LL, 100LL, 300LL, 500LL, 700LL, 900LL, 1100LL, 1300LL, 1500LL, 1700LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 2, 4, 5}, vector<int>{5, 3, 8, 2, 7}, 2) == vector<long long>{0LL, 13LL, 5LL, 13LL, 13LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50}, vector<int>{50, 40, 30, 20, 10, 50, 40, 30, 20, 10}, 4) == vector<long long>{0LL, 100LL, 180LL, 180LL, 180LL, 0LL, 100LL, 180LL, 180LL, 180LL}));
    assert((sol.findMaxSum(vector<int>{1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == vector<long long>{40LL, 40LL, 40LL, 40LL, 40LL, 34LL, 27LL, 19LL, 10LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{100, 1, 200, 2, 300, 3, 400, 4, 500, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 2) == vector<long long>{18LL, 0LL, 18LL, 2LL, 18LL, 6LL, 18LL, 10LL, 18LL, 14LL}));
    assert((sol.findMaxSum(vector<int>{10, 10, 10, 10, 10}, vector<int>{1000, 1001, 1002, 1003, 1004}, 3) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1, 0}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 5) == vector<long long>{400LL, 400LL, 400LL, 400LL, 400LL, 340LL, 270LL, 190LL, 100LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19, 21, 23, 25, 27, 29}, vector<int>{29, 27, 25, 23, 21, 19, 17, 15, 13, 11, 9, 7, 5, 3, 1}, 7) == vector<long long>{0LL, 29LL, 56LL, 81LL, 104LL, 125LL, 144LL, 161LL, 161LL, 161LL, 161LL, 161LL, 161LL, 161LL, 161LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3) == vector<long long>{27LL, 27LL, 27LL, 27LL, 27LL, 27LL, 27LL, 19LL, 10LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{50000, 40000, 30000, 20000, 10000, 60000, 70000, 80000, 90000, 100000}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 5) == vector<long long>{140LL, 120LL, 90LL, 50LL, 0LL, 150LL, 200LL, 250LL, 300LL, 350LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, 3) == vector<long long>{0LL, 100LL, 190LL, 270LL, 270LL, 270LL, 270LL, 270LL, 270LL, 270LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 2, 4, 5, 3, 4, 5, 6, 7}, vector<int>{100, 200, 300, 400, 500, 100, 200, 300, 400, 500}, 3) == vector<long long>{0LL, 400LL, 100LL, 600LL, 900LL, 400LL, 600LL, 900LL, 1200LL, 1300LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 2, 4, 6, 5, 8, 7, 10, 9}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 4) == vector<long long>{0LL, 40LL, 10LL, 60LL, 150LL, 100LL, 230LL, 180LL, 310LL, 260LL}));
    assert((sol.findMaxSum(vector<int>{500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000, 500000}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20}, vector<int>{20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 5) == vector<long long>{0LL, 20LL, 39LL, 57LL, 74LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL, 90LL}));
    assert((sol.findMaxSum(vector<int>{10, 15, 20, 25, 30, 35, 40, 45, 50, 55}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, 2) == vector<long long>{0LL, 100LL, 300LL, 500LL, 700LL, 900LL, 1100LL, 1300LL, 1500LL, 1700LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{100, 200, 300, 400, 500}, vector<int>{500, 400, 300, 200, 100}, 3) == vector<long long>{0LL, 500LL, 900LL, 1200LL, 1200LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1}, vector<int>{100, 200, 300, 400, 500}, 1) == vector<long long>{500LL, 500LL, 500LL, 500LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{20, 20, 20, 20, 20, 20, 20, 20, 20, 20}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 5) == vector<long long>{0LL, 10LL, 30LL, 60LL, 100LL, 150LL, 200LL, 250LL, 300LL, 350LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, 5) == vector<long long>{0LL, 100LL, 190LL, 270LL, 340LL, 400LL, 400LL, 400LL, 400LL, 400LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 5) == vector<long long>{14LL, 12LL, 9LL, 5LL, 0LL, 15LL, 20LL, 25LL, 30LL, 35LL}));
    assert((sol.findMaxSum(vector<int>{1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 10) == vector<long long>{540LL, 520LL, 490LL, 450LL, 400LL, 340LL, 270LL, 190LL, 100LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 3, 8, 6, 2, 7, 4, 10, 9, 1}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 4) == vector<long long>{240LL, 150LL, 280LL, 240LL, 100LL, 260LL, 170LL, 320LL, 280LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 3, 8, 6, 2, 7, 4, 1, 9, 10}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3) == vector<long long>{200LL, 130LL, 210LL, 200LL, 80LL, 200LL, 150LL, 0LL, 210LL, 240LL}));
    assert((sol.findMaxSum(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{1000, 900, 800, 700, 600, 500, 400, 300, 200, 100}, 3) == vector<long long>{0LL, 1000LL, 1900LL, 2700LL, 2700LL, 2700LL, 2700LL, 2700LL, 2700LL, 2700LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, 4) == vector<long long>{0LL, 100LL, 190LL, 270LL, 340LL, 340LL, 340LL, 340LL, 340LL, 340LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1}, vector<int>{10, 20, 30, 40, 50}, 5) == vector<long long>{140LL, 120LL, 90LL, 50LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1}, vector<int>{5, 4, 3, 2, 1}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}, 5) == vector<long long>{0LL, 19LL, 36LL, 51LL, 64LL, 75LL, 75LL, 75LL, 75LL, 75LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5) == vector<long long>{0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 5LL, 5LL, 5LL, 5LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{100000, 90000, 80000, 70000, 60000, 50000, 40000, 30000, 20000, 10000}, 5) == vector<long long>{0LL, 100000LL, 190000LL, 270000LL, 340000LL, 400000LL, 400000LL, 400000LL, 400000LL, 400000LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 2) == vector<long long>{19LL, 19LL, 19LL, 19LL, 19LL, 19LL, 19LL, 19LL, 10LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1000000, 500000, 250000, 125000, 62500}, vector<int>{62500, 125000, 250000, 500000, 1000000}, 2) == vector<long long>{1500000LL, 1500000LL, 1500000LL, 1000000LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 2) == vector<long long>{190LL, 190LL, 190LL, 190LL, 190LL, 190LL, 190LL, 190LL, 100LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4) == vector<long long>{0LL, 10LL, 19LL, 27LL, 34LL, 34LL, 34LL, 34LL, 34LL, 34LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 2, 3, 4, 4, 5, 5, 5, 6}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 2) == vector<long long>{0LL, 10LL, 10LL, 50LL, 70LL, 70LL, 110LL, 110LL, 110LL, 170LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{100, 99, 98, 97, 96, 95, 94, 93, 92, 91}, 5) == vector<long long>{0LL, 100LL, 199LL, 297LL, 394LL, 490LL, 490LL, 490LL, 490LL, 490LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 4) == vector<long long>{0LL, 1LL, 3LL, 6LL, 10LL, 14LL, 18LL, 22LL, 26LL, 30LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 4, 3, 2, 1}, 5) == vector<long long>{0LL, 5LL, 9LL, 12LL, 14LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 3) == vector<long long>{0LL, 1LL, 2LL, 3LL, 3LL, 3LL, 3LL, 3LL, 3LL, 3LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1, 0}, vector<int>{100, 200, 300, 400, 500, 600}, 3) == vector<long long>{1500LL, 1500LL, 1500LL, 1100LL, 600LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{100, 99, 98, 97, 96, 95, 94, 93, 92, 91}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3) == vector<long long>{27LL, 27LL, 27LL, 27LL, 27LL, 27LL, 27LL, 19LL, 10LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1}, vector<int>{10, 20, 30, 40, 50}, 2) == vector<long long>{90LL, 90LL, 90LL, 50LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 1) == vector<long long>{0LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL}));
    assert((sol.findMaxSum(vector<int>{1, 10, 2, 9, 3, 8, 4, 7, 5, 6}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 3) == vector<long long>{0LL, 25LL, 10LL, 24LL, 18LL, 24LL, 24LL, 24LL, 24LL, 24LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10) == vector<long long>{0LL, 1LL, 3LL, 6LL, 10LL, 15LL, 21LL, 28LL, 36LL, 45LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{100000, 90000, 80000, 70000, 60000, 50000, 40000, 30000, 20000, 10000}, 1) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 3, 8, 6, 2, 7, 4, 10, 1}, vector<int>{9, 1, 8, 7, 2, 6, 3, 10, 4}, 3) == vector<long long>{9LL, 6LL, 22LL, 16LL, 4LL, 20LL, 7LL, 24LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 3) == vector<long long>{0LL, 1LL, 3LL, 6LL, 9LL, 12LL, 15LL, 18LL, 21LL, 24LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 4) == vector<long long>{340LL, 340LL, 340LL, 340LL, 340LL, 340LL, 270LL, 190LL, 100LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 2) == vector<long long>{0LL, 10LL, 30LL, 50LL, 70LL, 90LL, 110LL, 130LL, 150LL, 170LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 1) == vector<long long>{10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1}, vector<int>{1, 2, 3, 4, 5}, 1) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 2, 3, 3, 3, 4, 4, 5, 5}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 3) == vector<long long>{0LL, 10LL, 10LL, 60LL, 60LL, 60LL, 150LL, 150LL, 210LL, 210LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5}, vector<int>{5, 5, 5, 5, 5}, 3) == vector<long long>{0LL, 5LL, 10LL, 15LL, 15LL}));
    assert((sol.findMaxSum(vector<int>{9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17}, 4) == vector<long long>{56LL, 56LL, 56LL, 56LL, 56LL, 45LL, 32LL, 17LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1}, vector<int>{1, 1, 1, 1, 1}, 3) == vector<long long>{3LL, 3LL, 2LL, 1LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15}, vector<int>{15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 3) == vector<long long>{0LL, 15LL, 29LL, 42LL, 42LL, 42LL, 42LL, 42LL, 42LL, 42LL, 42LL, 42LL, 42LL, 42LL, 42LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 2, 5, 4, 7, 6, 9, 8, 10}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 4) == vector<long long>{0LL, 18LL, 10LL, 33LL, 27LL, 34LL, 34LL, 34LL, 34LL, 34LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991}, 3) == vector<long long>{0LL, 1000000LL, 1999999LL, 2999997LL, 2999997LL, 2999997LL, 2999997LL, 2999997LL, 2999997LL, 2999997LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10) == vector<long long>{54LL, 52LL, 49LL, 45LL, 40LL, 34LL, 27LL, 19LL, 10LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 5) == vector<long long>{0LL, 1LL, 2LL, 3LL, 4LL, 5LL, 5LL, 5LL, 5LL, 5LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 10, 2, 20, 3, 30, 4, 40, 5, 50}, 4) == vector<long long>{140LL, 140LL, 140LL, 125LL, 125LL, 99LL, 95LL, 55LL, 50LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{2, 4, 6, 8, 10, 12, 14, 16, 18, 20}, vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, 5) == vector<long long>{0LL, 1LL, 4LL, 9LL, 16LL, 25LL, 35LL, 45LL, 55LL, 65LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, 1) == vector<long long>{0LL, 0LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL, 10LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 10) == vector<long long>{54LL, 52LL, 49LL, 45LL, 40LL, 34LL, 27LL, 19LL, 10LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1}, vector<int>{500, 400, 300, 200, 100}, 1) == vector<long long>{400LL, 300LL, 200LL, 100LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{500000, 400000, 300000, 200000, 100000}, vector<int>{50000, 40000, 30000, 20000, 10000}, 2) == vector<long long>{70000LL, 50000LL, 30000LL, 10000LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{100000, 90000, 80000, 70000, 60000, 50000, 40000, 30000, 20000, 10000}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 5) == vector<long long>{400LL, 400LL, 400LL, 400LL, 400LL, 340LL, 270LL, 190LL, 100LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{90, 80, 70, 60, 50, 40, 30, 20, 10, 0}, 5) == vector<long long>{0LL, 90LL, 170LL, 240LL, 300LL, 350LL, 350LL, 350LL, 350LL, 350LL}));
    assert((sol.findMaxSum(vector<int>{10, 9, 8, 7, 6, 5, 4, 3, 2, 1}, vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, 1) == vector<long long>{1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 1LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{500000, 400000, 300000, 200000, 100000}, vector<int>{10, 20, 30, 40, 50}, 5) == vector<long long>{140LL, 120LL, 90LL, 50LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{100, 200, 300, 400, 500, 600, 700, 800, 900, 1000}, 4) == vector<long long>{0LL, 0LL, 300LL, 300LL, 1000LL, 1000LL, 1800LL, 1800LL, 2600LL, 2600LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, 3) == vector<long long>{0LL, 100LL, 190LL, 270LL, 270LL, 270LL, 270LL, 270LL, 270LL, 270LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{20, 18, 16, 14, 12, 10, 8, 6, 4, 2}, 5) == vector<long long>{0LL, 20LL, 38LL, 54LL, 68LL, 80LL, 80LL, 80LL, 80LL, 80LL}));
    assert((sol.findMaxSum(vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 5) == vector<long long>{0LL, 10LL, 30LL, 60LL, 100LL, 150LL, 200LL, 250LL, 300LL, 350LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 2, 2, 3, 3, 4, 4, 5, 5}, vector<int>{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, 2) == vector<long long>{0LL, 0LL, 3LL, 3LL, 7LL, 7LL, 11LL, 11LL, 15LL, 15LL}));
    assert((sol.findMaxSum(vector<int>{1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 2) == vector<long long>{0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{100, 50, 75, 25, 150, 125, 200, 175, 225, 15}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 4) == vector<long long>{190LL, 140LL, 160LL, 100LL, 230LL, 190LL, 290LL, 250LL, 310LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 2, 3, 4, 5, 1, 2, 3, 4, 5}, vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50}, 3) == vector<long long>{0LL, 20LL, 50LL, 80LL, 110LL, 0LL, 20LL, 50LL, 80LL, 110LL}));
    assert((sol.findMaxSum(vector<int>{1000000, 999999, 999998, 999997, 999996, 999995, 999994, 999993, 999992, 999991}, vector<int>{10, 20, 30, 40, 50, 60, 70, 80, 90, 100}, 5) == vector<long long>{400LL, 400LL, 400LL, 400LL, 400LL, 340LL, 270LL, 190LL, 100LL, 0LL}));
    assert((sol.findMaxSum(vector<int>{1, 3, 5, 7, 9, 11, 13, 15, 17, 19}, vector<int>{19, 17, 15, 13, 11, 9, 7, 5, 3, 1}, 2) == vector<long long>{0LL, 19LL, 36LL, 36LL, 36LL, 36LL, 36LL, 36LL, 36LL, 36LL}));
    assert((sol.findMaxSum(vector<int>{5, 10, 15, 20, 25, 30, 35, 40, 45, 50}, vector<int>{100, 90, 80, 70, 60, 50, 40, 30, 20, 10}, 5) == vector<long long>{0LL, 100LL, 190LL, 270LL, 340LL, 400LL, 400LL, 400LL, 400LL, 400LL}));
    assert((sol.findMaxSum(vector<int>{5, 4, 3, 2, 1, 1, 2, 3, 4, 5}, vector<int>{10, 20, 30, 40, 50, 10, 20, 30, 40, 50}, 2) == vector<long long>{90LL, 90LL, 90LL, 60LL, 0LL, 0LL, 60LL, 90LL, 90LL, 90LL}));

    cout << "All tests passed for choose-k-elements-with-maximum-sum" << endl;
    return 0;
}
