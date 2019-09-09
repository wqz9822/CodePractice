/*
 * @lc app=leetcode id=314 lang=cpp
 *
 * [314] Binary Tree Vertical Order Traversal
 *
 * https://leetcode.com/problems/binary-tree-vertical-order-traversal/description/
 *
 * algorithms
 * Medium (41.47%)
 * Total Accepted:    81.9K
 * Total Submissions: 195.8K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, return the vertical order traversal of its nodes'
 * values. (ie, from top to bottom, column by column).
 *
 * If two nodes are in the same row and column, the order should be from left
 * to right.
 *
 * Examples 1:
 *
 *
 * Input: [3,9,20,null,null,15,7]
 *
 * ⁠  3
 * ⁠ /\
 * ⁠/  \
 * ⁠9  20
 * ⁠   /\
 * ⁠  /  \
 * ⁠ 15   7
 *
 * Output:
 *
 * [
 * ⁠ [9],
 * ⁠ [3,15],
 * ⁠ [20],
 * ⁠ [7]
 * ]
 *
 *
 * Examples 2:
 *
 *
 * Input: [3,9,8,4,0,1,7]
 *
 * ⁠    3
 * ⁠   /\
 * ⁠  /  \
 * ⁠  9   8
 * ⁠ /\  /\
 * ⁠/  \/  \
 * ⁠4  01   7
 *
 * Output:
 *
 * [
 * ⁠ [4],
 * ⁠ [9],
 * ⁠ [3,0,1],
 * ⁠ [8],
 * ⁠ [7]
 * ]
 *
 *
 * Examples 3:
 *
 *
 * Input: [3,9,8,4,0,1,7,null,null,null,2,5] (0's right child is 2 and 1's left
 * child is 5)
 *
 * ⁠    3
 * ⁠   /\
 * ⁠  /  \
 * ⁠  9   8
 * ⁠ /\  /\
 * ⁠/  \/  \
 * ⁠4  01   7
 * ⁠   /\
 * ⁠  /  \
 * ⁠  5   2
 *
 * Output:
 *
 * [
 * ⁠ [4],
 * ⁠ [9,5],
 * ⁠ [3,0,1],
 * ⁠ [8,2],
 * ⁠ [7]
 * ]
 *
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
  vector<vector<int>> verticalOrder(TreeNode *root) {
    vector<vector<int>> res;
    if (!root) {
      return res;
    }
    map<int, vector<int>> colMap;
    std::queue<std::pair<int, TreeNode *>> treeQ;
    treeQ.push(make_pair(0, root));
    while (!treeQ.empty()) {
      auto cur = treeQ.front();
      treeQ.pop();
      // cout << "cur:" << cur.first << endl;
      colMap[cur.first].push_back(cur.second->val);
      if (cur.second->left) {
        treeQ.push(make_pair(cur.first - 1, cur.second->left));
      }
      if (cur.second->right) {
        treeQ.push(make_pair(cur.first + 1, cur.second->right));
      }
    }
    for (auto &item : colMap) {
      res.push_back(std::move(item.second));
    }
    return res;
  }
};
