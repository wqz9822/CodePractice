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
  node(int level_, int word_id_) : level(level_), word_id(word_id_) {}
  int level = 0;
  int word_id = 0;
};

class Solution {
public:
  int ladderLength(const string &beginWord, const string &endWord,
                   const vector<string> &wordList) {
    int end_id = buildDict(beginWord, endWord, wordList);
    if (end_id < 0) {
      return 0;
    }
    vector<bool> hasVisited(wordList.size() + 1, false);
    queue<node> searchQueue;
    searchQueue.emplace(1, wordList.size());
    while (!searchQueue.empty()) {
      auto &cur = searchQueue.front();
      if (cur.word_id == end_id) {
        return cur.level;
      }
      hasVisited[cur.word_id] = true;
      // push all words not visited with distance 1
      const auto nextWords = findOneDist(cur.word_id, hasVisited, wordList);
      for (const auto word : nextWords) {
        // `cout << wordList[cur.word_id] << "," << cur.level + 1 << ","
        // << wordList[word] << endl;
        searchQueue.emplace(cur.level + 1, word);
        hasVisited[word] = true;
      }
      searchQueue.pop();
    }
    return 0;
  }

private:
  unordered_map<int, unordered_set<int>> dict;

  bool distOfOne(const string &word1, const string &word2) {
    int diff = 0;
    for (int i = 0; i < word1.size(); ++i) {
      if (word1[i] != word2[i]) {
        diff++;
      }
      if (diff > 1) {
        return false;
      }
    }
    return diff == 1;
  }

  int buildDict(const string &beginWord, const string &endWord,
                const vector<string> &wordList) {
    int end_id = -1;
    for (size_t i = 0; i < wordList.size(); ++i) {
      const auto &word1 = wordList[i];
      if (word1 == endWord) {
        end_id = i;
      }
      if (distOfOne(beginWord, word1)) {
        dict[wordList.size()].insert(i);
      }
      for (size_t j = i; j < wordList.size(); ++j) {
        const auto &word2 = wordList[j];
        if (distOfOne(word1, word2)) {
          dict[i].insert(j);
          dict[j].insert(i);
        }
      }
    }
    return end_id;
  }

  vector<int> findOneDist(int cur, const vector<bool> &hasVisited,
                          const vector<string> &wordList) {
    vector<int> res;
    for (const auto id : dict[cur]) {
      if (!hasVisited[id]) {
        res.push_back(id);
      }
    }
    return res;
  }
};
