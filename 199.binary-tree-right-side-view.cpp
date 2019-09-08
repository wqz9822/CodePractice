/*
 * @lc app=leetcode id=199 lang=cpp
 *
 * [199] Binary Tree Right Side View
 *
 * https://leetcode.com/problems/binary-tree-right-side-view/description/
 *
 * algorithms
 * Medium (48.87%)
 * Total Accepted:    189.8K
 * Total Submissions: 384.8K
 * Testcase Example:  '[1,2,3,null,5,null,4]'
 *
 * Given a binary tree, imagine yourself standing on the right side of it,
 * return the values of the nodes you can see ordered from top to bottom.
 *
 * Example:
 *
 *
 * Input: [1,2,3,null,5,null,4]
 * Output: [1, 3, 4]
 * Explanation:
 *
 * ⁠  1            <---
 * ⁠/   \
 * 2     3         <---
 * ⁠\     \
 * ⁠ 5     4       <---
 *
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
  vector<int> rightSideView(TreeNode *root) {
    vector<int> res;
    if (!root) {
      return res;
    }
    std::queue<std::pair<int, TreeNode *>> nodeQueue;
    nodeQueue.push(std::make_pair(0, root));
    int level = 0;
    TreeNode *prev = nullptr;
    while (!nodeQueue.empty()) {
      auto cur = nodeQueue.front();
      nodeQueue.pop();
      if (cur.first > level && prev) {
        res.push_back(prev->val);
        level = cur.first;
      }
      if (cur.second->left) {
        nodeQueue.push(std::make_pair(cur.first + 1, cur.second->left));
      }
      if (cur.second->right) {
        nodeQueue.push(std::make_pair(cur.first + 1, cur.second->right));
      }
      prev = cur.second;
    }
    if (prev) {
      res.push_back(prev->val);
    }
    return res;
  }
};
