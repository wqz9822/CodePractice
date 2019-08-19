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
class UnionFind {
public:
  explicit UnionFind(size_t n) {
    parent_.resize(n, -1);
    rank_.resize(n, 0);
  }

  void join(int idx1, int idx2) {
    if (rank_[idx1] < rank_[idx2]) {
      swap(idx1, idx2);
    }
    parent_[idx2] = find(idx1);
    if (rank_[idx1] == rank_[idx2]) {
      rank_[idx1]++;
    }
  }

  int find(int idx) {
    if (parent_[idx] == -1) {
      return idx;
    }
    // path compression
    return parent_[idx] = find(parent_[idx]);
  }

private:
  vector<int> parent_;
  vector<int> rank_;
};

class Solution {
public:
  int numIslands(vector<vector<char>> &grid) {
    if (grid.empty() || grid[0].empty()) {
      return 0;
    }
    size_t rowNum = grid.size();
    size_t colNum = grid[0].size();
    UnionFind uf(rowNum * colNum);
    int res = 0;
    for (size_t i = 0; i < grid.size(); ++i) {
      for (size_t j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == '0') {
          continue;
        }
        res++;
        const auto idx1 = i * colNum + j;
        for (const auto &dir : DIRS) {
          const auto r = i + dir.first;
          const auto c = j + dir.second;
          const auto idx2 = r * colNum + c;
          if (inBound(grid, r, c) && grid[r][c] == '1') {
            auto root1 = uf.find(idx1);
            auto root2 = uf.find(idx2);
            if (root1 != root2) {
              // note: join the root nodes, not idx
              uf.join(root1, root2);
              res--;
            }
          }
        }
      }
    }
    return res;
  }

private:
  const vector<pair<int, int>> DIRS{{1, 0}, {0, 1}};

  bool inBound(vector<vector<char>> &grid, int r, int c) {
    return (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size());
  }
};
