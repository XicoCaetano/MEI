#include <vector>
#include <algorithm>
#include <queue>
#include <numeric>
using namespace std;

class Solution {
public:
    vector<long long> findMaxSum(vector<int> nums1, vector<int> nums2, int k) {
        int n = nums1.size();
        
        // Create array of indices and sort by nums1[i]
        vector<int> idx(n);
        iota(idx.begin(), idx.end(), 0);
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return nums1[i] < nums1[j];
        });
        
        // Min-heap to store top k nums2 values
        priority_queue<int, vector<int>, greater<int>> pq;
        vector<long long> result(n);
        
        // For each element in sorted order
        long long currentSum = 0;
        for (int i = 0; i < n; i++) {
            int originalIndex = idx[i];
            
            // For current element, result is currentSum (sum of top k from all prev smaller nums1)
            result[originalIndex] = currentSum;
            
            // Add current nums2 value to candidate set
            int val = nums2[originalIndex];
            
            // If we have less than k elements, add and update sum
            if (pq.size() < k) {
                pq.push(val);
                currentSum += val;
            } 
            // If we have k elements and current val is larger than smallest in heap
            else if (!pq.empty() && val > pq.top()) {
                currentSum -= pq.top();
                pq.pop();
                pq.push(val);
                currentSum += val;
            }
        }
        
        return result;
    }
};