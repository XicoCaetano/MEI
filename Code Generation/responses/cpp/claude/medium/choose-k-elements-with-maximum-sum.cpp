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