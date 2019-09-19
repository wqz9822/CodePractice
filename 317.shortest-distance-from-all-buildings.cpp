/*
 * @lc app=leetcode id=317 lang=cpp
 *
 * [317] Shortest Distance from All Buildings
 *
 * https://leetcode.com/problems/shortest-distance-from-all-buildings/description/
 *
 * algorithms
 * Hard (38.49%)
 * Total Accepted:    45.8K
 * Total Submissions: 118.3K
 * Testcase Example:  '[[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]'
 *
 * You want to build a house on an empty land which reaches all buildings in
 * the shortest amount of distance. You can only move up, down, left and right.
 * You are given a 2D grid of values 0, 1 or 2, where:
 *
 *
 * Each 0 marks an empty land which you can pass by freely.
 * Each 1 marks a building which you cannot pass through.
 * Each 2 marks an obstacle which you cannot pass through.
 *
 *
 * Example:
 *
 *
 * Input: [[1,0,2,0,1],[0,0,0,0,0],[0,0,1,0,0]]
 *
 * 1 - 0 - 2 - 0 - 1
 * |   |   |   |   |
 * 0 - 0 - 0 - 0 - 0
 * |   |   |   |   |
 * 0 - 0 - 1 - 0 - 0
 *
 * Output: 7
 *
 * Explanation: Given three buildings at (0,0), (0,4), (2,2), and an obstacle
 * at (0,2),
 * ⁠            the point (1,2) is an ideal empty land to build a house, as
 * the
 * total
 * travel distance of 3+3+1=7 is minimal. So return 7.
 *
 * Note:
 * There will be at least one building. If it is not possible to build such
 * house according to the above rules, return -1.
 *
 */
class Solution {
public:
  int shortestDistance(vector<vector<int>> &grid) {

    // from all builds, floodfill the board
    // add all floodfill to get min
  }

private:
  const std::vector<std::pair<int, int>> dirs{{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

  void floodFill(vector<vector<int>> &grid, int startRow, int startCol) {
    queue<pair<int, int>> q;
    unordered_map<int> visited;
    q.push(std::make_pair(startRow, startCol));
    while (!q.empty()) {
      auto cur = q.front();
      q.pop();
      for (const auto &d : dirs) {
        auto r = cur.first + d.first;
        auto c = cur.second + d.second;
        auto idx = r * grid[0].size() + c;
        if (visited.count(idx) == 0 && inBound(grid, r, c)) {
          q.push(std::make_pair(r, c));
        }
      }
    }
  }

  bool inBound(const vector<vector<int>> &grid, int r, int c) {
    return (r >= 0 && r < grid.size() && c >= 0 && c < grid[0].size());
  }
};
