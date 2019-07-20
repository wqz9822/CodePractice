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
  node(const string &word_, int level_) : word(word_), level(level_) {}
  string word;
  int level = 1;
};

struct SearchQueue {
  queue<node> q;
  unordered_map<string, int> hasVisited;
};

class Solution {
public:
  int ladderLength(const string &beginWord, const string &endWord,
                   const vector<string> &wordList) {
    if (!buildDict(beginWord, endWord, wordList)) {
      return 0;
    }
    SearchQueue front;
    SearchQueue back;
    front.q.emplace(beginWord, 1);
    front.hasVisited.emplace(beginWord, 1);
    back.q.emplace(endWord, 1);
    back.hasVisited.emplace(endWord, 1);
    while (!front.q.empty() && !back.q.empty()) {
      if (front.q.size() > back.q.size()) {
        std::swap(front, back);
      }
      int res = push_node(&front, &back, wordList);
      if (res != -1) {
        return res;
      }
    }
    return 0;
  }

private:
  unordered_map<string, unordered_set<string>> dict;

  int push_node(SearchQueue *sq1, SearchQueue *sq2,
                const vector<string> &wordList) {
    // push all words not visited with distance 1
    const auto &cur = sq1->q.front();
    const auto nextWords = findOneDist(cur.word, sq1->hasVisited, wordList);
    for (const auto &word : nextWords) {
      if (sq2->hasVisited.count(word)) {
        return cur.level + sq2->hasVisited[word];
      }
      sq1->q.emplace(word, cur.level + 1);
      sq1->hasVisited.emplace(word, cur.level + 1);
    }
    sq1->q.pop();
    return -1;
  }

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

  bool buildDict(const string &beginWord, const string &endWord,
                 const vector<string> &wordList) {
    bool hasEndWord = false;
    for (size_t i = 0; i < wordList.size(); ++i) {
      const auto &word1 = wordList[i];
      if (word1 == endWord) {
        hasEndWord = true;
      }
      if (distOfOne(beginWord, word1)) {
        dict[beginWord].insert(word1);
      }
      for (size_t j = i + 1; j < wordList.size(); ++j) {
        const auto &word2 = wordList[j];
        if (distOfOne(word1, word2)) {
          dict[word1].insert(word2);
          dict[word2].insert(word1);
        }
      }
    }
    return hasEndWord;
  }

  vector<string> findOneDist(const string &cur,
                             const unordered_map<string, int> &hasVisited,
                             const vector<string> &wordList) {
    vector<string> res;
    for (const auto &word : dict[cur]) {
      if (!hasVisited.count(word)) {
        res.push_back(word);
      }
    }
    return res;
  }
};
