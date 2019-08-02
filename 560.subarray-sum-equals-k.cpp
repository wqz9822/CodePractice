/*
 * @lc app=leetcode id=560 lang=cpp
 *
 * [560] Subarray Sum Equals K
 *
 * https://leetcode.com/problems/subarray-sum-equals-k/description/
 *
 * algorithms
 * Medium (41.61%)
 * Total Accepted:    120.4K
 * Total Submissions: 283.2K
 * Testcase Example:  '[1,1,1]\n2'
 *
 * Given an array of integers and an integer k, you need to find the total
 * number of continuous subarrays whose sum equals to k.
 *
 * Example 1:
 *
 * Input:nums = [1,1,1], k = 2
 * Output: 2
 *
 *
 *
 * Note:
 *
 * The length of the array is in range [1, 20,000].
 * The range of numbers in the array is [-1000, 1000] and the range of the
 * integer k is [-1e7, 1e7].
 *
 *
 *
 */
class Solution {
public:
  int subarraySum(vector<int> &nums, int k) {
    vector<int> sum(nums.size(), 0);
    vector<int> neg(nums.size(), 0);
    int t = 0;
    int res = 0;
    int n = 0;
    for (int i = 0; i < nums.size(); ++i) {
      if (nums[i] == k) {
        res++;
      }
      if (nums[nums.size() - i] < 0) {
        n++;
        neg[i] = n;
      }

      t += nums[i];
      sum[i] = t;
      // cout << sum[i] << ", ";
    }
    for (int i = 0; i < nums.size(); ++i) {
      for (int j = i + 1; j < nums.size(); ++j) {
        if (i >= 1) {
          t = sum[j] - sum[i - 1];
        } else {
          t = sum[j];
        }
        //  cout << "i:" << i << ", j:" << j << ", t:" << t << endl;
        if (t == k) {
          res++;
        }
      }
    }
    return res;
  }
};
