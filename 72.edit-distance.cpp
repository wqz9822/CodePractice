/*
 * @lc app=leetcode id=72 lang=cpp
 *
 * [72] Edit Distance
 *
 * https://leetcode.com/problems/edit-distance/description/
 *
 * algorithms
 * Hard (36.36%)
 * Total Accepted:    168K
 * Total Submissions: 451.3K
 * Testcase Example:  '"horse"\n"ros"'
 *
 * Given two words word1 and word2, find the minimum number of operations
 * required to convert word1 to word2.
 *
 * You have the following 3 operations permitted on a word:
 *
 *
 * Insert a character
 * Delete a character
 * Replace a character
 *
 *
 * Example 1:
 *
 *
 * Input: word1 = "horse", word2 = "ros"
 * Output: 3
 * Explanation:
 * horse -> rorse (replace 'h' with 'r')
 * rorse -> rose (remove 'r')
 * rose -> ros (remove 'e')
 *
 *
 * Example 2:
 *
 *
 * Input: word1 = "intention", word2 = "execution"
 * Output: 5
 * Explanation:
 * intention -> inention (remove 't')
 * inention -> enention (replace 'i' with 'e')
 * enention -> exention (replace 'n' with 'x')
 * exention -> exection (replace 'n' with 'c')
 * exection -> execution (insert 'u')
 *
 *
 */
class Solution {
public:
  int minDistance(string word1, string word2) {
    if (word1.size() == 0 || word2.size() == 0) {
      return max(word1.size(), word2.size());
    }
    dp = vector(word1.size() + 1, vector(word2.size() + 1, 0));
    for (int i = 0; i < word1.size() + 1; ++i) {
      dp[i][0] = i;
    }
    for (int i = 0; i < word2.size() + 1; ++i) {
      dp[0][i] = i;
    }
    for (int i = 1; i < word1.size() + 1; ++i) {
      for (int j = 1; j < word2.size() + 1; ++j) {
        // add 1 cost for insert
        auto left = dp[i][j - 1] + 1;
        auto down = dp[i - 1][j] + 1;
        auto left_down = dp[i - 1][j - 1];
        if (word1[i - 1] != word2[j - 1]) {
          // add 1 cost for substitue
          left_down++;
        }
        dp[i][j] = min(left, min(down, left_down));
      }
    }
    return dp[word1.size()][word2.size()];
  }

private:
  vector<vector<int>> dp;
};
