/*
 * @lc app=leetcode id=340 lang=cpp
 *
 * [340] Longest Substring with At Most K Distinct Characters
 *
 * https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/description/
 *
 * algorithms
 * Hard (40.47%)
 * Total Accepted:    84.5K
 * Total Submissions: 207.3K
 * Testcase Example:  '"eceba"\n2'
 *
 * Given a string, find the length of the longest substring T that contains at
 * most k distinct characters.
 *
 * Example 1:
 *
 *
 *
 * Input: s = "eceba", k = 2
 * Output: 3
 * Explanation: T is "ece" which its length is 3.
 *
 *
 * Example 2:
 *
 *
 * Input: s = "aa", k = 1
 * Output: 2
 * Explanation: T is "aa" which its length is 2.
 *
 *
 *
 */
class Solution {
public:
  int lengthOfLongestSubstringKDistinct(string s, int k) {
    int front = 0;
    int end = 0;
    int res = INT_MIN;
    std::unordered_map<char, int> slide;
    if (s.size() == 0 || k == 0) {
      return 0;
    }
    while (end < s.size()) {
      slide[s[end]] = end;
      if (slide.size() > k) {
        // Note: remove leftmost char in the current window
        int newFront = INT_MAX;
        for (const auto &item : slide) {
          if (item.second < newFront) {
            newFront = item.second;
          }
        }
        slide.erase(s[newFront]);
        front = newFront + 1;
      }
      res = max(res, end - front + 1);
      end++;
    }
    return max(res, 0);
  }
};
