/*
 * @lc app=leetcode id=269 lang=cpp
 *
 * [269] Alien Dictionary
 *
 * https://leetcode.com/problems/alien-dictionary/description/
 *
 * algorithms
 * Hard (31.71%)
 * Total Accepted:    85.9K
 * Total Submissions: 269.7K
 * Testcase Example:  '["wrt","wrf","er","ett","rftt"]'
 *
 * There is a new alien language which uses the latin alphabet. However, the
 * order among letters are unknown to you. You receive a list of non-empty
 * words from the dictionary, where words are sorted lexicographically by the
 * rules of this new language. Derive the order of letters in this language.
 *
 * Example 1:
 *
 *
 * Input:
 * [
 * ⁠ "wrt",
 * ⁠ "wrf",
 * ⁠ "er",
 * ⁠ "ett",
 * ⁠ "rftt"
 * ]
 *
 * Output: "wertf"
 *
 *
 * Example 2:
 *
 *
 * Input:
 * [
 * ⁠ "z",
 * ⁠ "x"
 * ]
 *
 * Output: "zx"
 *
 *
 * Example 3:
 *
 *
 * Input:
 * [
 * ⁠ "z",
 * ⁠ "x",
 * ⁠ "z"
 * ]
 *
 * Output: "" 
 *
 * Explanation: The order is invalid, so return "".
 *
 *
 * Note:
 *
 *
 * You may assume all letters are in lowercase.
 * You may assume that if a is a prefix of b, then a must appear before b in
 * the given dictionary.
 * If the order is invalid, return an empty string.
 * There may be multiple valid order of letters, return any one of them is
 * fine.
 *
 *
 */
class Graph {
public:
  void addVert(char v) {
    if (list_.count(v) == 0) {
      list_.emplace(v, std::unordered_set<char>());
    }
  }

  void addEdge(char src, char dst) {
    addVert(src);
    addVert(dst);
    list_[src].insert(dst);
  }

  vector<char> topoSort() {
    vector<char> finalPath;
    unordered_set<char> curPath;
    unordered_set<char> visited;
    for (const auto &vert : list_) {
      // assert(curPath.empty());
      if (visited.count(vert.first) == 0 &&
          !topoSortDFS(vert.first, curPath, finalPath, visited)) {
        return vector<char>();
      }
    }
    return vector<char>(finalPath.rbegin(), finalPath.rend());
  }

  bool topoSortDFS(char cur, unordered_set<char> &curPath,
                   vector<char> &finalPath, unordered_set<char> &visited) {
    for (const auto &n : list_[cur]) {
      if (curPath.count(n) != 0) {
        // loop found
        return false;
      }
      if (visited.count(n) == 0) {
        // cout << n << " -> ";
        curPath.insert(n);
        if (!topoSortDFS(n, curPath, finalPath, visited)) {
          return false;
        }
        curPath.erase(n);
      }
    }
    // note: mark visited after traverse all neighbours
    visited.insert(cur);
    finalPath.push_back(cur);
    return true;
  }

  vector<char> topoSortBFS() {
    vector<char> res;
    char minVert = 0;
    while (!list_.empty()) {
      // find min degree node
      bool hasLoop = true;
      for (const auto &item : list_) {
        if (item.second.size() == 0) {
          minVert = item.first;
          hasLoop = false;
          break;
        }
      }
      if (hasLoop) {
        return vector<char>();
      }
      // erase node from all dst
      for (auto &item : list_) {
        if (item.second.count(minVert) != 0) {
          item.second.erase(minVert);
        }
      }
      res.push_back(minVert);
      list_.erase(minVert);
    }
    return res;
  }

  void printList() {
    for (const auto &item : list_) {
      cout << item.first << ": ";
      for (const auto &dst : item.second) {
        cout << dst << ",";
      }
      cout << endl;
    }
  }

private:
  std::unordered_map<char, unordered_set<char>> list_;
};

class Solution {
public:
  string alienOrder(vector<string> &words) {
    // for every adjcent word
    // find first diff char a, b
    // add edge: b->a
    // topo sort
    Graph g;
    for (const auto &word : words) {
      for (const auto &l : word) {
        g.addVert(l);
      }
    }
    for (size_t i = 0; i < words.size() - 1; ++i) {
      auto idx = findFirstDiff(words[i], words[i + 1]);
      if (idx >= 0) {
        g.addEdge(words[i][idx], words[i + 1][idx]);
      }
    }
    const auto finalPath = g.topoSort();
    return std::string(finalPath.begin(), finalPath.end());
  }

private:
  int findFirstDiff(const string &a, const string &b) {
    size_t len = min(a.size(), b.size());
    for (size_t i = 0; i < len; ++i) {
      if (a[i] != b[i]) {
        return i;
      }
    }
    // a is a prefix of b, no order can be infered
    return -1;
  }
};
