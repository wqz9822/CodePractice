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
    int maxLevel = -1;
    dfsHelper(root, res, 0, maxLevel);
    return res;
  }

private:
  void dfsHelper(TreeNode *node, vector<int> &res, int curLevel,
                 int &maxLevel) {
    if (!node) {
      return;
    }
    if (curLevel > maxLevel) {
      res.push_back(node->val);
      maxLevel = curLevel;
    }
    dfsHelper(node->right, res, curLevel + 1, maxLevel);
    dfsHelper(node->left, res, curLevel + 1, maxLevel);
  }
};
