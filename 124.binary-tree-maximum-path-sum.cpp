/*
 * @lc app=leetcode id=124 lang=cpp
 *
 * [124] Binary Tree Maximum Path Sum
 *
 * https://leetcode.com/problems/binary-tree-maximum-path-sum/description/
 *
 * algorithms
 * Hard (30.55%)
 * Total Accepted:    210K
 * Total Submissions: 687.1K
 * Testcase Example:  '[1,2,3]'
 *
 * Given a non-empty binary tree, find the maximum path sum.
 *
 * For this problem, a path is defined as any sequence of nodes from some
 * starting node to any node in the tree along the parent-child connections.
 * The path must contain at least one node and does not need to go through the
 * root.
 *
 * Example 1:
 *
 *
 * Input: [1,2,3]
 *
 * ⁠      1
 * ⁠     / \
 * ⁠    2   3
 *
 * Output: 6
 *
 *
 * Example 2:
 *
 *
 * Input: [-10,9,20,null,null,15,7]
 *
 * -10
 * / \
 * 9  20
 * /  \
 * 15   7
 *
 * Output: 42
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
  int maxPathSum(TreeNode *root) {}

  int helper(TreeNode *n) {
    if (!n->left && !n->right) {
      return n->val;
    }
    int left_max = 0 int right_max = 0;
    if (n->left) {
      left_max = helper(n->left);
    }
    if (n->right) {
      right_max = helper(n->right);
    }
    int max = left_max + n->val;
    max = (right_max + n->val) > max ? right_max + n->val : max;
    max = (left_max + right_max + n->val) > max ? right_max + n->val : max;
    return max;
  }

private:
  int max = 0;
};
