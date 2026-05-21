#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution {
public:
    vector<long long> findMaxSum(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<long long> result(n, 0);
        
        // Store indices and sort them based on values in nums1
        vector<int> indices(n);
        for (int i = 0; i < n; ++i) {
            indices[i] = i;
        }
        
        sort(indices.begin(), indices.end(), [&](int a, int b) {
            return nums1[a] < nums1[b];
        });
        
        // Min-priority queue to keep track of the k largest elements seen so far
        priority_queue<int, vector<int>, greater<int>> pq;
        long long current_sum = 0;
        
        int j = 0;
        for (int i = 0; i < n; ++i) {
            int curr_idx = indices[i];
            
            // If the current nums1 value is the same as the previous, 
            // it will have the same sum as calculated for the first instance of this value.
            if (i > 0 && nums1[curr_idx] == nums1[indices[i - 1]]) {
                result[curr_idx] = result[indices[i - 1]];
            } else {
                // Add all elements from nums2 whose corresponding nums1 value 
                // is strictly less than the current nums1[curr_idx]
                while (j < i) {
                    int prev_idx = indices[j];
                    if (nums1[prev_idx] < nums1[curr_idx]) {
                        pq.push(nums2[prev_idx]);
                        current_sum += nums2[prev_idx];
                        
                        if (pq.size() > k) {
                            current_sum -= pq.top();
                            pq.pop();
                        }
                        j++;
                    } else {
                        break;
                    }
                }
                result[curr_idx] = current_sum;
            }
        }
        
        return result;
    }
};