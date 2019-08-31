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

struct UnionFind {
  UnionFind() {
    parent.resize(10000);
    std::iota(parent.begin(), parent.end(), 0);
  }

  void join(int a, int b) {
    int pa = find(a);
    int pb = find(b);
    if (pa != pb) {
      // cout << "joining:" << a << ", " << b << endl;
      parent[pa] = pb;
    }
  }

  int find(int a) {
    if (parent[a] == a) {
      return a;
    }
    return parent[a] = find(parent[a]);
  }

  vector<int> parent;
};

class Solution {
public:
  vector<vector<string>> accountsMerge(vector<vector<string>> &accounts) {
    // assign each unique email with a unique id
    // connect all emails to the first emails

    unordered_map<std::string, int> emailMap;
    unordered_map<int, std::string> idMap;
    unordered_map<int, string> nameMap;
    UnionFind uf;

    int firstIdx = 0;
    int idx = 0;

    for (const auto &acnt : accounts) {
      firstIdx = idx;
      bool hasAdd = false;
      for (size_t i = 1; i < acnt.size(); ++i) {
        if (emailMap.count(acnt[i]) == 0) {
          hasAdd = true;
          emailMap[acnt[i]] = idx;
          idMap[idx] = acnt[i];
          uf.join(firstIdx, idx);
          nameMap[idx] = acnt[0];
          idx++;
        } else {
          int oldIdx = emailMap[acnt[i]];
          uf.join(firstIdx, oldIdx);
        }
      }
      if (!hasAdd) {
        idx++;
      }
    }

    std::unordered_map<int, std::set<std::string>> out;

    /*
    cout << "uf result" << endl;
    for (size_t i = 0; i < idx; ++i) {
      cout << uf.parent[i] << ", ";
    }
    */

    for (size_t i = 0; i < idx; ++i) {
      if (idMap.count(i) != 0) {
        out[uf.find(i)].insert(idMap[i]);
      }
    }

    vector<vector<string>> res;
    for (const auto &item : out) {
      res.emplace_back();
      res.back().push_back(nameMap[item.first]);
      std::copy(item.second.begin(), item.second.end(),
                std::back_inserter(res.back()));
    }
    return res;
  }
};
