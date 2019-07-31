/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 *
 * https://leetcode.com/problems/search-in-rotated-sorted-array/description/
 *
 * algorithms
 * Medium (32.62%)
 * Total Accepted:    448.7K
 * Total Submissions: 1.4M
 * Testcase Example:  '[4,5,6,7,0,1,2]\n0'
 *
 * Suppose an array sorted in ascending order is rotated at some pivot unknown
 * to you beforehand.
 *
 * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
 *
 * You are given a target value to search. If found in the array return its
 * index, otherwise return -1.
 *
 * You may assume no duplicate exists in the array.
 *
 * Your algorithm's runtime complexity must be in the order of O(log n).
 *
 * Example 1:
 *
 *
 * Input: nums = [4,5,6,7,0,1,2], target = 0
 * Output: 4
 *
 *
 * Example 2:
 *
 *
 * Input: nums = [4,5,6,7,0,1,2], target = 3
 * Output: -1
 *
 */
class Solution {
public:
  int search(vector<int> &nums, int target) {
    // find pivot point p
    // binary search [0..p), [p, num.size())

    if (nums.empty()) {
      return -1;
    }
    int lo = 0;
    int hi = nums.size() - 1;
    int pivot = 0;
    while (nums[lo] > nums[hi]) {
      if ((hi - lo) <= 1) {
        pivot = hi;
        break;
      }
      int mid = (lo + hi) / 2;
      if (nums[mid] > nums[hi]) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    int maxIdx = (pivot >= 1) ? pivot - 1 : nums.size() - 1;
    int minIdx = pivot;
    // cout << "min:" << minIdx << ", max:" << maxIdx << endl;
    if (target > nums[maxIdx] || target < nums[minIdx]) {
      return -1;
    }
    if (target >= nums[0]) {
      return binarySearch(0, maxIdx, target, nums);
    }
    return binarySearch(minIdx, nums.size() - 1, target, nums);
  }

private:
  int binarySearch(int lo, int hi, int target, const vector<int> &nums) {
    if (lo > hi) {
      return -1;
    }
    int mid = (lo + hi) / 2;
    // cout << "lo:" << lo << ",mid:" << mid << ",hi:" << hi << endl;
    if (nums[mid] == target) {
      return mid;
    }
    if (nums[mid] > target) {
      return binarySearch(lo, mid - 1, target, nums);
    }
    return binarySearch(mid + 1, hi, target, nums);
  }
};
