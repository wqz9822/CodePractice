/*
 * @lc app=leetcode id=127 lang=cpp
 *
 * [127] Word Ladder
 *
 * https://leetcode.com/problems/word-ladder/description/
 *
 * algorithms
 * Medium (22.88%)
 * Total Accepted:    269.1K
 * Total Submissions: 1.1M
 * Testcase Example:  '"hit"\n"cog"\n["hot","dot","dog","lot","log","cog"]'
 *
 * Given two words (beginWord and endWord), and a dictionary's word list, find
 * the length of shortest transformation sequence from beginWord to endWord,
 * such that:
 *
 *
 * Only one letter can be changed at a time.
 * Each transformed word must exist in the word list. Note that beginWord is
 * not a transformed word.
 *
 *
 * Note:
 *
 *
 * Return 0 if there is no such transformation sequence.
 * All words have the same length.
 * All words contain only lowercase alphabetic characters.
 * You may assume no duplicates in the word list.
 * You may assume beginWord and endWord are non-empty and are not the same.
 *
 *
 * Example 1:
 *
 *
 * Input:
 * beginWord = "hit",
 * endWord = "cog",
 * wordList = ["hot","dot","dog","lot","log","cog"]
 *
 * Output: 5
 *
 * Explanation: As one shortest transformation is "hit" -> "hot" -> "dot" ->
 * "dog" -> "cog",
 * return its length 5.
 *
 *
 * Example 2:
 *
 *
 * Input:
 * beginWord = "hit"
 * endWord = "cog"
 * wordList = ["hot","dot","dog","lot","log"]
 *
 * Output: 0
 *
 * Explanation: The endWord "cog" is not in wordList, therefore no possible
 * transformation.
 *
 *
 *
 *
 *
 */
struct node {
  node(int level_, const std::string &word_) : level(level_), word(word_) {}
  int level = 0;
  std::string word;
};

class Solution {
public:
  int ladderLength(const string &beginWord, const string &endWord,
                   const vector<string> &wordList) {
    if (find(wordList.begin(), wordList.end(), endWord) == wordList.end()) {
      return 0;
    }
    int minPath = INT_MAX;
    bool hasResult = false;
    unordered_set<string> hasVisited;
    queue<node> searchQueue;
    searchQueue.emplace(1, beginWord);
    while (!searchQueue.empty()) {
      auto &cur = searchQueue.front();
      if (cur.word == endWord) {
        minPath = min(minPath, cur.level);
        hasResult = true;
        cout << "has result: " << minPath << endl;
        searchQueue.pop();
        continue;
      }
      hasVisited.insert(cur.word);
      // push all words not visited with distance 1
      const auto nextWords = findOneDist(cur.word, hasVisited, wordList);
      for (const auto &word : nextWords) {
        // cout << cur.word << "," << cur.level + 1 << "," << word << endl;
        if (!hasResult || (cur.level < minPath - 1)) {
          searchQueue.emplace(cur.level + 1, word);
        }
      }
      searchQueue.pop();
    }
    return hasResult ? minPath : 0;
  }

private:
  unordered_map<string, unordered_map<string, int>> memo;

  int dist(const string &word1, const string &word2) {
    if (memo.count(word1) > 0 && memo[word1].count(word2) > 0) {
      return memo[word1][word2];
    }
    if (memo.count(word2) > 0 && memo[word2].count(word1) > 0) {
      return memo[word2][word1];
    }
    int diff = 0;
    for (int i = 0; i < word1.size(); ++i) {
      if (word1[i] != word2[i]) {
        diff++;
      }
    }
    memo[word1][word2] = diff;
    memo[word2][word1] = diff;
    return diff;
  }

  vector<string> findOneDist(const string &cur,
                             const unordered_set<string> &hasVisited,
                             const vector<string> &wordList) {
    vector<string> res;
    for (const auto &word : wordList) {
      if (hasVisited.count(word) == 0) {
        if (dist(cur, word) == 1) {
          res.push_back(word);
        }
      }
    }
    return res;
  }
};
