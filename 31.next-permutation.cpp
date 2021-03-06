/*
 * @lc app=leetcode id=31 lang=cpp
 *
 * [31] Next Permutation
 *
 * https://leetcode.com/problems/next-permutation/description/
 *
 * algorithms
 * Medium (30.02%)
 * Total Accepted:    251.5K
 * Total Submissions: 818.1K
 * Testcase Example:  '[1,2,3]'
 *
 * Implement next permutation, which rearranges numbers into the
 * lexicographically next greater permutation of numbers.
 *
 * If such arrangement is not possible, it must rearrange it as the lowest
 * possible order (ie, sorted in ascending order).
 *
 * The replacement must be in-place and use only constant extra memory.
 *
 * Here are some examples. Inputs are in the left-hand column and its
 * corresponding outputs are in the right-hand column.
 *
 * 1,2,3 → 1,3,2
 * 3,2,1 → 1,2,3
 * 1,1,5 → 1,5,1
 *
 */
class Solution {
public:
  void nextPermutation(vector<int> &nums) {
    for (int i = nums.size() - 1; i > 0; --i) {
      if (nums[i - 1] < nums[i]) {
        // swap i-1 with first element larger than i-1 in [i, nums.size())
        // reverse order in [i, nums.size())
        for (int j = nums.size() - 1; j >= i; j--) {
          if (nums[j] > nums[i - 1]) {
            std::swap(nums[i - 1], nums[j]);
            break;
          }
        }
        std::reverse(nums.begin() + i, nums.end());
        return;
      }
    }
    std::reverse(nums.begin(), nums.end());
    return;
  }
};
