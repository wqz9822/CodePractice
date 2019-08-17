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
    backtrack(s, &curStr, 0, 0, 0, &maxLen, res);
    return vector<string>(res.begin(), res.end());
  }

private:
  void backtrack(const string &s, string *curStr, int curPos, int left,
                 int right, int *maxLen, set<string> &res) {
    // base case
    if (curPos == s.size()) {
      if ((left == right) && (curStr->size() >= *maxLen)) {
        // cout << "left:" << left << ",right:" << right << ",curStr:" <<
        // *curStr
        //    << endl;
        *maxLen = curStr->size();
        res.insert(*curStr);
      }
      return;
    }
    if (left < right) {
      return;
    }
    // include current character
    curStr->push_back(s[curPos]);
    if (s[curPos] == '(') {
      backtrack(s, curStr, curPos + 1, left + 1, right, maxLen, res);
    } else if (s[curPos] == ')' && left > right) {
      backtrack(s, curStr, curPos + 1, left, right + 1, maxLen, res);
    } else if (s[curPos] != '(' && s[curPos] != ')') {
      backtrack(s, curStr, curPos + 1, left, right, maxLen, res);
    }
    curStr->pop_back();
    // exclude current character
    backtrack(s, curStr, curPos + 1, left, right, maxLen, res);
  }
};
