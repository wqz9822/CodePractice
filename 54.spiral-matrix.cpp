/*
 * @lc app=leetcode id=54 lang=cpp
 *
 * [54] Spiral Matrix
 *
 * https://leetcode.com/problems/spiral-matrix/description/
 *
 * algorithms
 * Medium (29.57%)
 * Total Accepted:    227.2K
 * Total Submissions: 751.8K
 * Testcase Example:  '[[1,2,3],[4,5,6],[7,8,9]]'
 *
 * Given a matrix of m x n elements (m rows, n columns), return all elements of
 * the matrix in spiral order.
 *
 * Example 1:
 *
 *
 * Input:
 * [
 * ⁠[ 1, 2, 3 ],
 * ⁠[ 4, 5, 6 ],
 * ⁠[ 7, 8, 9 ]
 * ]
 * Output: [1,2,3,6,9,8,7,4,5]
 *
 *
 * Example 2:
 *
 * Input:
 * [
 * ⁠ [1, 2, 3, 4],
 * ⁠ [5, 6, 7, 8],
 * ⁠ [9,10,11,12]
 * ]
 * Output: [1,2,3,4,8,12,11,10,9,5,6,7]
 *
 */
class Solution {
public:
  vector<int> spiralOrder(const vector<vector<int>> &matrix) {
    if (matrix.size() == 0 || matrix[0].size() == 0) {
      return vector<int>();
    }
    if (matrix.size() == 1) {
      return matrix[0];
    }

    using dir = pair<int, int>;
    vector<dir> dirs{{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int min_row, min_col, max_row, max_col;
    min_row = min_col = 0;
    max_row = matrix.size() - 1;
    max_col = matrix[0].size() - 1;

    int total = matrix.size() * matrix[0].size();
    vector<int> res(total, 0);
    int cur, row, col, counter;
    cur = row = col = counter = 0;
    while (counter < total) {
      while (col >= min_col && col <= max_col && row >= min_row &&
             row <= max_row) {
        res[counter] = matrix[row][col];
        counter++;
        row += dirs[cur].first;
        col += dirs[cur].second;
      }
      if (cur == 0)
        min_row++;
      if (cur == 1)
        max_col--;
      if (cur == 2)
        max_row--;
      if (cur == 3)
        min_col++;
      col = (col < min_col) ? min_col : max_col;
      row = (row < min_row) ? min_row : max_row;
      cur = (cur + 1) % 4;
    }
    return res;
  }
};
