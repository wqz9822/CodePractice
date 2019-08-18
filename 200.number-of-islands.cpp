/*
 * @lc app=leetcode id=200 lang=cpp
 *
 * [200] Number of Islands
 *
 * https://leetcode.com/problems/number-of-islands/description/
 *
 * algorithms
 * Medium (40.21%)
 * Total Accepted:    325.8K
 * Total Submissions: 797.9K
 * Testcase Example:
 * '[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]]'
 *
 * Given a 2d grid map of '1's (land) and '0's (water), count the number of
 * islands. An island is surrounded by water and is formed by connecting
 * adjacent lands horizontally or vertically. You may assume all four edges of
 * the grid are all surrounded by water.
 *
 * Example 1:
 *
 *
 * Input:
 * 11110
 * 11010
 * 11000
 * 00000
 *
 * Output: 1
 *
 *
 * Example 2:
 *
 *
 * Input:
 * 11000
 * 11000
 * 00100
 * 00011
 *
 * Output: 3
 *
 */
class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    int res = 0;
    for (size_t i = 0; i < grid.size(); ++i) {
      for (size_t j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == '1') {
          res++;
          dfs(grid, i, j);
        }
      }
    }
    return res;
  }

private:
  const vector<pair<int, int>> DIRS{{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

  bool inBound(vector<vector<char>> &grid, int r, int c) {
    return (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size());
  }

  void dfs(vector<vector<char>> &grid, int r, int c) {
    if (!inBound(grid, r, c) || grid[r][c] != '1') {
      return;
    }
    grid[r][c] = '0';
    for (const auto &dir : DIRS) {
      dfs(grid, r + dir.first, c + dir.second);
    }
  }
};
