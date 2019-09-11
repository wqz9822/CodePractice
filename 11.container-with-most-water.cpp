/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 *
 * https://leetcode.com/problems/container-with-most-water/description/
 *
 * algorithms
 * Medium (45.90%)
 * Total Accepted:    440.9K
 * Total Submissions: 947.2K
 * Testcase Example:  '[1,8,6,2,5,4,8,3,7]'
 *
 * Given n non-negative integers a1, a2, ..., an , where each represents a
 * point at coordinate (i, ai). n vertical lines are drawn such that the two
 * endpoints of line i is at (i, ai) and (i, 0). Find two lines, which together
 * with x-axis forms a container, such that the container contains the most
 * water.
 *
 * Note: You may not slant the container and n is at least 2.
 *
 *
 *
 *
 *
 * The above vertical lines are represented by array [1,8,6,2,5,4,8,3,7]. In
 * this case, the max area of water (blue section) the container can contain is
 * 49.
 *
 *
 *
 * Example:
 *
 *
 * Input: [1,8,6,2,5,4,8,3,7]
 * Output: 49
 *
 */
class Solution {
public:
  int maxArea(vector<int> &height) {
    int res = INT_MIN;
    int len = height.size();
    vector<int> leftMax;
    vector<int> rightMax;
    int left = INT_MIN;
    int right = INT_MIN;
    for (size_t i = 0; i < len; ++i) {
      if (height[i] > left) {
        leftMax.push_back(i);
        left = height[i];
      }
      if (height[len - i - 1] > right) {
        rightMax.push_back(len - i - 1);
        right = height[len - i - 1];
      }
    }

    for (size_t i = 0; i < leftMax.size(); ++i) {
      int curLeft = height[leftMax[i]];
      for (size_t j = 0; j < rightMax.size(); ++j) {
        int curRight = height[rightMax[j]];
        int t = min(curLeft, curRight) * (rightMax[j] - leftMax[i]);
        if (t > res) {
          res = t;
        }
        if (curLeft < curRight) {
          break;
        }
      }
    }
    return res;
  }
};
