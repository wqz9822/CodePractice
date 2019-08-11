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
  int maxPathSum(TreeNode *root) {
    findMax(root);
    return globalMax;
  }

  int findMax(TreeNode *n) {
    if (!n) {
      return 0;
    }
    int leftMax = max(findMax(n->left), 0);
    int rightMax = max(findMax(n->right), 0);

    // max result if choose current node as the highest
    int localMax = n->val + leftMax + rightMax;
    globalMax = localMax > globalMax ? localMax : globalMax;
    // return larger one of the path for upper level to build localMax
    return n->val + max(leftMax, rightMax);
  }

private:
  int globalMax = INT_MIN;
};
