/*
 * @lc app=leetcode id=721 lang=cpp
 *
 * [721] Acnts Merge
 *
 * https://leetcode.com/problems/accounts-merge/description/
 *
 * algorithms
 * Medium (41.62%)
 * Total Accepted:    40.5K
 * Total Submissions: 96.3K
 * Testcase Example:
 * '[["John","johnsmith@mail.com","john_newyork@mail.com"],["John","johnsmith@mail.com","john00@mail.com"],["Mary","mary@mail.com"],["John","johnnybravo@mail.com"]]'
 *
 * Given a list accounts, each element accounts[i] is a list of strings, where
 * the first element accounts[i][0] is a name, and the rest of the elements are
 * emails representing emails of the account.
 *
 * Now, we would like to merge these accounts.  Two accounts definitely belong
 * to the same person if there is some email that is common to both accounts.
 * Note that even if two accounts have the same name, they may belong to
 * different people as people could have the same name.  A person can have any
 * number of accounts initially, but all of their accounts definitely have the
 * same name.
 *
 * After merging the accounts, return the accounts in the following format: the
 * first element of each account is the name, and the rest of the elements are
 * emails in sorted order.  The accounts themselves can be returned in any
 * order.
 *
 * Example 1:
 *
 * Input:
 * accounts = [["John", "johnsmith@mail.com", "john00@mail.com"], ["John",
 * "johnnybravo@mail.com"], ["John", "johnsmith@mail.com",
 * "john_newyork@mail.com"], ["Mary", "mary@mail.com"]]
 * Output: [["John", 'john00@mail.com', 'john_newyork@mail.com',
 * 'johnsmith@mail.com'],  ["John", "johnnybravo@mail.com"], ["Mary",
 * "mary@mail.com"]]
 * Explanation:
 * The first and third John's are the same person as they have the common email
 * "johnsmith@mail.com".
 * The second John and Mary are different people as none of their email
 * addresses are used by other accounts.
 * We could return these lists in any order, for example the answer [['Mary',
 * 'mary@mail.com'], ['John', 'johnnybravo@mail.com'],
 * ['John', 'john00@mail.com', 'john_newyork@mail.com', 'johnsmith@mail.com']]
 * would still be accepted.
 *
 *
 *
 * Note:
 * The length of accounts will be in the range [1, 1000].
 * The length of accounts[i] will be in the range [1, 10].
 * The length of accounts[i][j] will be in the range [1, 30].
 *
 */

struct Account {
  explicit Account(int id, const vector<string> &entry) {
    uniqueId = id;
    name = entry[0];
    emails = std::set(entry.begin() + 1, entry.end());
  }

  void mergeAcnt(Account *other) { emails.merge(other->emails); }

  std::vector<string> toList() {
    std::vector<std::string> res;
    res.push_back(name);
    std::copy(emails.begin(), emails.end(), std::back_inserter(res));
    return res;
  }

  int uniqueId;
  std::string name;
  std::set<std::string> emails;
};

class Solution {
public:
  vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
    // build a graph
    // connect all emails to the first emails

    unordered_map<string, unordered_set<string>> graph;
    unordered_map<string, string> nameMap;
    for (const auto &acnt : accounts) {
      for (size_t i = 1; i < acnt.size(); ++i) {
        nameMap[acnt[i]] = acnt[0];
        graph[acnt[1]].insert(acnt[i]);
        graph[acnt[i]].insert(acnt[1]);
      }
    }
    vector<vector<string>> res;
    unordered_set<string> visited;
    for (const auto &node : graph) {
      if (visited.count(node.first) == 0) {
        visited.insert(node.first);
        // bfs or dfs to iterate all neighbors
        queue<string> nodeQue;
        vector<string> nodeList;
        nodeQue.push(node.first);
        nodeList.push_back(nameMap[node.first]);
        while (!nodeQue.empty()) {
          nodeList.push_back(std::move(nodeQue.front()));
          nodeQue.pop();
          for (const auto &nei : graph[nodeList.back()]) {
            if (visited.count(nei) == 0) {
              visited.insert(nei);
              nodeQue.push(nei);
            }
          }
        }
        std::sort(nodeList.begin() + 1, nodeList.end());
        res.push_back(std::move(nodeList));
      }
    }
    return res;
  }
};
