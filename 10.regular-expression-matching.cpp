/*
 * @lc app=leetcode id=10 lang=cpp
 *
 * [10] Regular Expression Matching
 *
 * https://leetcode.com/problems/regular-expression-matching/description/
 *
 * algorithms
 * Hard (24.95%)
 * Total Accepted:    289.4K
 * Total Submissions: 1.2M
 * Testcase Example:  '"aa"\n"a"'
 *
 * Given an input string (s) and a pattern (p), implement regular expression
 * matching with support for '.' and '*'.
 *
 *
 * '.' Matches any single character.
 * '*' Matches zero or more of the preceding element.
 *
 *
 * The matching should cover the entire input string (not partial).
 *
 * Note:
 *
 *
 * s could be empty and contains only lowercase letters a-z.
 * p could be empty and contains only lowercase letters a-z, and characters
 * like . or *.
 *
 *
 * Example 1:
 *
 *
 * Input:
 * s = "aa"
 * p = "a"
 * Output: false
 * Explanation: "a" does not match the entire string "aa".
 *
 *
 * Example 2:
 *
 *
 * Input:
 * s = "aa"
 * p = "a*"
 * Output: true
 * Explanation: '*' means zero or more of the precedeng element, 'a'.
 * Therefore, by repeating 'a' once, it becomes "aa".
 *
 *
 * Example 3:
 *
 *
 * Input:
 * s = "ab"
 * p = ".*"
 * Output: true
 * Explanation: ".*" means "zero or more (*) of any character (.)".
 *
 *
 * Example 4:
 *
 *
 * Input:
 * s = "aab"
 * p = "c*a*b"
 * Output: true
 * Explanation: c can be repeated 0 times, a can be repeated 1 time. Therefore
 * it matches "aab".
 *
 *
 * Example 5:
 *
 *
 * Input:
 * s = "mississippi"
 * p = "mis*is*p*."
 * Output: false
 *
 *
 */
class Solution {
public:
  bool isMatch(string src, string pattern) {
    s = src;
    p = pattern;
    memo.resize(s.size() + 1, vector<int>(p.size() + 1, -1));
    memo[s.size()][p.size()] = 1;
    return isMatchHelper(0, 0);
  }

  bool isMatchHelper(int i, int j) {
    if (memo[i][j] != -1) {
      return memo[i][j];
    }

    bool res = false;
    bool first_match =
        (i < s.size()) && (j < p.size()) && (p[j] == '.' || s[i] == p[j]);

    if ((j + 1 < p.size()) && p[j + 1] == '*') {
      res = isMatchHelper(i, j + 2) || first_match && isMatchHelper(i + 1, j);
    } else {
      res = first_match ? isMatchHelper(i + 1, j + 1) : false;
    }
    return memo[i][j] = res;
  }

private:
  vector<vector<int>> memo;
  std::string s;
  std::string p;
};
