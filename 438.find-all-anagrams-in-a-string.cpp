/*
 * @lc app=leetcode id=438 lang=cpp
 *
 * [438] Find All Anagrams in a String
 *
 * https://leetcode.com/problems/find-all-anagrams-in-a-string/description/
 *
 * algorithms
 * Medium (37.88%)
 * Total Accepted:    143.4K
 * Total Submissions: 374.6K
 * Testcase Example:  '"cbaebabacd"\n"abc"'
 *
 * Given a string s and a non-empty string p, find all the start indices of p's
 * anagrams in s.
 *
 * Strings consists of lowercase English letters only and the length of both
 * strings s and p will not be larger than 20,100.
 *
 * The order of output does not matter.
 *
 * Example 1:
 *
 * Input:
 * s: "cbaebabacd" p: "abc"
 *
 * Output:
 * [0, 6]
 *
 * Explanation:
 * The substring with start index = 0 is "cba", which is an anagram of "abc".
 * The substring with start index = 6 is "bac", which is an anagram of
 * "abc".
 *
 *
 *
 * Example 2:
 *
 * Input:
 * s: "abab" p: "ab"
 *
 * Output:
 * [0, 1, 2]
 *
 * Explanation:
 * The substring with start index = 0 is "ab", which is an anagram of "ab".
 * The substring with start index = 1 is "ba", which is an anagram of "ab".
 * The substring with start index = 2 is "ab", which is an anagram of "ab".
 *
 *
 */
class Solution {
public:
  vector<int> findAnagrams(string s, string p) {
    vector<int> res;
    if (s.size() < p.size()) {
      return res;
    }
    unordered_map<char, int> target;
    for (const auto &c : p) {
      target[c]++;
    }
    unordered_map<char, int> src;
    for (size_t i = 0; i < p.size(); ++i) {
      src[s[i]]++;
    }
    int front = 0;
    int back = front + p.size() - 1;
    while (back < s.size()) {
      if (src == target) {
        res.push_back(front);
      }
      if (--src[s[front]] == 0) {
        src.erase(s[front]);
      }
      front++;
      back++;
      src[s[back]]++;
    }
    return res;
  }
};
