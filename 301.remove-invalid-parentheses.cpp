/*
 * @lc app=leetcode id=301 lang=cpp
 *
 * [301] Remove Invalid Parentheses
 *
 * https://leetcode.com/problems/remove-invalid-parentheses/description/
 *
 * algorithms
u* Hard (39.89%)
 * Total Accepted:    137.9K
 * Total Submissions: 345K
 * Testcase Example:  '"()())()"'
 *
 * Remove the minimum number of invalid parentheses in order to make the input
 * string valid. Return all possible results.
 *
 * Note: The input string may contain letters other than the parentheses ( and
 * ).
 *
 * Example 1:
 *
 *
 * Input: "()())()"
 * Output: ["()()()", "(())()"]
 *
 *
 * Example 2:
 *
 *
 * Input: "(a)())()"
 * Output: ["(a)()()", "(a())()"]
 *
 *
 * Example 3:
 *
 *
 * Input: ")("
 * Output: [""]
 *
 */
class Solution {
public:
  vector<string> removeInvalidParentheses(const string &s) {
    set<string> res;
    string curStr;
    int maxLen = 0;
    if (s.empty()) {
      return vector<string>{""};
    }
    auto pairToRemove = getMisplacedPair(s);
    backtrack(s, curStr, 0, 0, 0, pairToRemove.first, pairToRemove.second, res);
    return vector<string>(res.begin(), res.end());
  }

private:
  std::pair<int, int> getMisplacedPair(const string &str) {
    int left = 0;
    int right = 0;
    for (size_t i = 0; i < str.size(); ++i) {
      if (str[i] == '(') {
        left++;
      } else if (str[i] == ')') {
        if (left > 0) {
          left--;
        } else {
          right++;
        }
      }
    }
    return std::make_pair(left, right);
  }

  void backtrack(const string &s, string &curStr, int curPos, int left,
                 int right, int leftTarget, int rightTarget, set<string> &res) {
    // base case
    if (curPos == s.size()) {
      if ((left == right) && leftTarget == 0 && rightTarget == 0) {
        res.insert(curStr);
      }
      return;
    }
    if (left < right || leftTarget < 0 || rightTarget < 0) {
      return;
    }
    // include current (parenthese or character)
    curStr.push_back(s[curPos]);
    if (s[curPos] == '(') {
      backtrack(s, curStr, curPos + 1, left + 1, right, leftTarget, rightTarget,
                res);
    } else if (s[curPos] == ')') {
      backtrack(s, curStr, curPos + 1, left, right + 1, leftTarget, rightTarget,
                res);
    } else if (s[curPos] != '(' && s[curPos] != ')') {
      backtrack(s, curStr, curPos + 1, left, right, leftTarget, rightTarget,
                res);
    }
    // backtrack
    curStr.pop_back();
    // exclude current parenthese
    if (s[curPos] == '(') {
      backtrack(s, curStr, curPos + 1, left, right, leftTarget - 1, rightTarget,
                res);
    } else if (s[curPos] == ')') {
      backtrack(s, curStr, curPos + 1, left, right, leftTarget, rightTarget - 1,
                res);
    }
  }
};
