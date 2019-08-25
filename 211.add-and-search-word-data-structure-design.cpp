/*
 * @lc app=leetcode id=211 lang=cpp
 *
 * [211] Add and Search Word - Data structure design
 *
 * https://leetcode.com/problems/add-and-search-word-data-structure-design/description/
 *
 * algorithms
 * Medium (31.23%)
 * Total Accepted:    125.2K
 * Total Submissions: 397.9K
 * Testcase Example:
 * '["WordDictionary","addWord","addWord","addWord","search","search","search","search"]\n[[],["bad"],["dad"],["mad"],["pad"],["bad"],[".ad"],["b.."]]'
 *
 * Design a data structure that supports the following two operations:
 *
 *
 * void addWord(word)
 * bool search(word)
 *
 *
 * search(word) can search a literal word or a regular expression string
 * containing only letters a-z or .. A . means it can represent any one
 * letter.
 *
 * Example:
 *
 *
 * addWord("bad")
 * addWord("dad")
 * addWord("mad")
 * search("pad") -> false
 * search("bad") -> true
 * search(".ad") -> true
 * search("b..") -> true
 *
 *
 * Note:
 * You may assume that all words are consist of lowercase letters a-z.
 *
 */
struct TrieNode {
  TrieNode() { list.resize(26); }
  std::vector<std::unique_ptr<TrieNode>> list;
  bool isWordEnd = false;
};

class WordDictionary {
public:
  /** Initialize your data structure here. */
  WordDictionary() : root(new TrieNode()) {}

  /** Adds a word into the data structure. */
  void addWord(const string &word) {
    if (word.empty()) {
      return;
    }
    TrieNode *cur = root.get();
    for (size_t i = 0; i < word.size(); ++i) {
      if (!cur->list[word[i] - 'a']) {
        cur->list[word[i] - 'a'] = std::make_unique<TrieNode>();
      }
      if (i == word.size() - 1) {
        cur->isWordEnd = true;
      }
      cur = cur->list[word[i] - 'a'].get();
    }
  }

  /** Returns if the word is in the data structure. A word could contain the dot
   * character '.' to represent any one letter. */
  bool search(const string &word) {
    if (word.empty()) {
      return true;
    }
    return searchHelper(root.get(), word, 0);
  }

private:
  std::unique_ptr<TrieNode> root;

  bool searchHelper(const TrieNode *cur, const string &word, size_t curPos) {
    // cout << word << "," << word[curPos] << endl;
    if (word[curPos] != '.') {
      const auto next = cur->list[word[curPos] - 'a'].get();
      if (!next) {
        return false;
      }
      if (curPos == word.size() - 1) {
        return cur->isWordEnd;
      }
      return searchHelper(next, word, curPos + 1);
    }
    // wildcard
    if (curPos == word.size() - 1) {
      return cur->isWordEnd;
    }
    for (const auto &next : cur->list) {
      if (next.get() && curPos < word.size() - 1 &&
          searchHelper(next.get(), word, curPos + 1)) {
        return true;
      }
    }
    return false;
  }
};

/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */
