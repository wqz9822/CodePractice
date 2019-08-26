/*
 * @lc app=leetcode id=953 lang=cpp
 *
 * [953] Verifying an Alien Dictionary
 *
 * https://leetcode.com/problems/verifying-an-alien-dictionary/description/
 *
 * algorithms
 * Easy (55.91%)
 * Total Accepted:    29.6K
 * Total Submissions: 52.9K
 * Testcase Example:  '["hello","leetcode"]\n"hlabcdefgijkmnopqrstuvwxyz"'
 *
 * In an alien language, surprisingly they also use english lowercase letters,
 * but possibly in a different order. The order of the alphabet is some
 * permutation of lowercase letters.
 *
 * Given a sequence of words written in the alien language, and the order of
 * the alphabet, return true if and only if the given words are sorted
 * lexicographicaly in this alien language.
 *
 *
 *
 *
 * Example 1:
 *
 *
 * Input: words = ["hello","leetcode"], order = "hlabcdefgijkmnopqrstuvwxyz"
 * Output: true
 * Explanation: As 'h' comes before 'l' in this language, then the sequence is
 * sorted.
 *
 *
 *
 * Example 2:
 *
 *
 * Input: words = ["word","world","row"], order = "worldabcefghijkmnpqstuvxyz"
 * Output: false
 * Explanation: As 'd' comes after 'l' in this language, then words[0] >
 * words[1], hence the sequence is unsorted.
 *
 *
 *
 * Example 3:
 *
 *
 * Input: words = ["apple","app"], order = "abcdefghijklmnopqrstuvwxyz"
 * Output: false
 * Explanation: The first three characters "app" match, and the second string
 * is shorter (in size.) According to lexicographical rules "apple" > "app",
 * because 'l' > '∅', where '∅' is defined as the blank character which is less
 * than any other character (More info).
 *
 *
 *
 *
 * Note:
 *
 *
 * 1 <= words.length <= 100
 * 1 <= words[i].length <= 20
 * order.length == 26
 * All characters in words[i] and order are english lowercase letters.
 *
 *
 *
 *
 *
 */
class Solution {
public:
  bool isAlienSorted(vector<string> &words, string order) {
    for (size_t i = 0; i < 26; ++i) {
      alpabet_[order[i] - 'a'] = i;
    }

    for (size_t i = 0; i < words.size() - 1; ++i) {
      const auto &word1 = words[i];
      const auto &word2 = words[i + 1];
      int diff = findFirstDiff(word1, word2);
      if (diff >= 0 &&
          alpabet_[word1[diff] - 'a'] > alpabet_[word2[diff] - 'a']) {
        return false;
      }
      if (diff == -1 && word1.size() > word2.size()) {
        return false;
      }
    }
    return true;
  }

private:
  std::array<int, 26> alpabet_;
  int findFirstDiff(const string &word1, const string &word2) {
    size_t len = min(word1.size(), word2.size());
    for (size_t i = 0; i < len; ++i) {
      if (word1[i] != word2[i]) {
        return i;
      }
    }
    return -1;
  }
};
