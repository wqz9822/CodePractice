/*
 * @lc app=leetcode id=394 lang=cpp
 *
 * [394] Decode String
 *
 * https://leetcode.com/problems/decode-string/description/
 *
 * algorithms
 * Medium (43.79%)
 * Total Accepted:    116.4K
 * Total Submissions: 254.8K
 * Testcase Example:  '"3[a]2[bc]"'
 *
 * Given an encoded string, return its decoded string.
 *
 * The encoding rule is: k[encoded_string], where the encoded_string inside the
 * square brackets is being repeated exactly k times. Note that k is guaranteed
 * to be a positive integer.
 *
 * You may assume that the input string is always valid; No extra white spaces,
 * square brackets are well-formed, etc.
 *
 * Furthermore, you may assume that the original data does not contain any
 * digits and that digits are only for those repeat numbers, k. For example,
 * there won't be input like 3a or 2[4].
 *
 * Examples:
 *
 *
 * s = "3[a]2[bc]", return "aaabcbc".
 * s = "3[a2[c]]", return "accaccacc".
 * s = "2[abc]3[cd]ef", return "abcabccdcdcdef".
 *
 *
 *
 *
 */
class Solution {
public:
  string decodeString(string s) {
    for (size_t i = 0; i < s.size(); ++i) {
      if (s[i] == ']') {
        string temp;
        while (seq.top() != '[') {
          temp.push_back(seq.top());
          seq.pop();
        }
        seq.pop();
        string repStr;
        while (!seq.empty() && (seq.top() - '0' >= 0) &&
               (seq.top() - '0' < 10)) {
          repStr.push_back(seq.top());
          seq.pop();
        }
        int rep = std::stoi(string(repStr.rbegin(), repStr.rend()));
        // cout << "rep: " << rep << endl;
        for (size_t j = 0; j < rep; ++j) {
          for (size_t k = 0; k < temp.size(); ++k) {
            seq.push(temp[temp.size() - k - 1]);
          }
        }
      } else {
        seq.push(s[i]);
      }
    }
    string res;
    while (!seq.empty()) {
      res.push_back(seq.top());
      seq.pop();
    }
    return std::string(res.rbegin(), res.rend());
  }

private:
  stack<char> seq;
};
