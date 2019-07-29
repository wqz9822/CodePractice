/*
 * @lc app=leetcode id=4 lang=cpp
 *
 * [4] Median of Two Sorted Arrays
 *
 * https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * algorithms
 * Hard (25.50%)
 * Total Accepted:    470K
 * Total Submissions: 1.8M
 * Testcase Example:  '[1,3]\n[2]'
 *
 * There are two sorted arrays nums1 and nums2 of size m and n respectively.
 *
 * Find the median of the two sorted arrays. The overall run time complexity
 * should be O(log (m+n)).
 *
 * You may assume nums1 and nums2 cannot be both empty.
 *
 * Example 1:
 *
 *
 * nums1 = [1, 3]
 * nums2 = [2]
 *
 * The median is 2.0
 *
 *
 * Example 2:
 *
 *
 * nums1 = [1, 2]
 * nums2 = [3, 4]
 *
 * The median is (2 + 3)/2 = 2.5
 *
 *
 */
class Solution {
public:
  double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2) {
    int len1 = nums1.size();
    int len2 = nums2.size();
    /*
    for (int i = 0; i < len1; ++i) {
      cout << binarySearch(nums1[i], 0, len2, nums2) << endl;
    }
    */
    int numToFind;
    if ((len1 + len2) % 2 == 0) {
      numToFind = len1 + (len2 - len1) / 2;
    } else {
      numToFind = len1 + (len2 - len1) / 2 - 1;
    }

    cout << "num to find: " << numToFind << endl;
    int i = numToFind;
    int prev = i;
    int j = binarySearch(nums1[i - 1], 0, len2, nums2) + 1;
    int sum = i + j;
    while (sum != numToFind) {
      cout << "[i:" << i << ", j:" << j << ", sum:" << sum << "]" << endl;
      if (sum > numToFind) {
        prev = i;
        i = i / 2;
      } else {
        i = (i + prev) / 2;
      }
      j = binarySearch(nums1[i - 1], 0, len2, nums2) + 1;
      sum = i + j;
    }
    cout << "[i:" << i << ", j:" << j << ", sum:" << sum << "]" << endl;
    if ((len1 + len2) % 2 == 0) {
      int a = min(nums1[i], nums2[j]);
      int b = max(nums1[i - 1], nums2[j - 1]);
      return (a + b) / 2.0;
    }
    return min(nums1[i], nums2[j]);
  }

  int binarySearch(int n, int lo, int hi, const vector<int> &nums) {
    if ((hi - lo) < 1) {
      return -1;
    }
    int mid = lo + (hi - lo) / 2;
    /*
    cout << "target: " << n << ", lo: " << lo << ", mid: " << mid
         << ", hi: " << hi << endl;
         */
    if (nums[mid] < n) {
      if (mid + 1 == nums.size() || nums[mid + 1] >= n) {
        return mid;
      }
      return binarySearch(n, mid, hi, nums);
    }
    return binarySearch(n, lo, mid, nums);
  }
};
