/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 *
 * https://leetcode.com/problems/group-anagrams/description/
 *
 * algorithms
 * Medium (44.66%)
 * Total Accepted:    365.1K
 * Total Submissions: 760.1K
 * Testcase Example:  '["eat","tea","tan","ate","nat","bat"]'
 *
 * Given an array of strings, group anagrams together.
 *
 * Example:
 *
 *
 * Input: ["eat", "tea", "tan", "ate", "nat", "bat"],
 * Output:
 * [
 * ⁠ ["ate","eat","tea"],
 * ⁠ ["nat","tan"],
 * ⁠ ["bat"]
 * ]
 *
 * Note:
 *
 *
 * All inputs will be in lowercase.
 * The order of your output does not matter.
 *
 *
 */
class Solution {
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs) {
    vector<vector<string>> res;
    unordered_map<string, vector<string>> dict;
    for (const auto &str : strs) {
      multiset<char> anagram;
      for (const auto &ch : str) {
        anagram.insert(ch);
      }
      auto newStr = string(anagram.begin(), anagram.end());
      dict[newStr].push_back(str);
    }
    for (auto &kv : dict) {
      res.push_back(std::move(kv.second));
    }
    return res;
  }
};
