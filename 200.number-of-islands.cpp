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
          assert(bfsQueue_.empty());
          grid[i][j] = '0';
          bfsQueue_.emplace(i, j);
          bfs(grid);
        }
      }
    }
    return res;
  }

private:
  const vector<pair<int, int>> DIRS{{0, 1}, {1, 0}, {-1, 0}, {0, -1}};
  queue<pair<int, int>> bfsQueue_;

  bool inBound(vector<vector<char>> &grid, int r, int c) {
    return (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size());
  }

  void bfs(vector<vector<char>> &grid) {
    while (!bfsQueue_.empty()) {
      const auto &top = bfsQueue_.front();
      cout << "row:" << top.first << ",col:" << top.second << endl;
      for (const auto &dir : DIRS) {
        const auto r = top.first + dir.first;
        const auto c = top.second + dir.second;
        if (inBound(grid, r, c) && grid[r][c] == '1') {
          // note: mark neighbour points as visited
          grid[r][c] = '0';
          bfsQueue_.emplace(r, c);
        }
      }
      bfsQueue_.pop();
    }
  }
};
