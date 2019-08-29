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
Point {
  Point(int x_, int y_, int dist_ = 0) : x(x_), y(y_), dist(dist_) {}
  bool operator=(const Point &other) {
    return (this.x == other.x && this.y == other.y);
  }
  int x;
  int y;
  int dist;
};

class Solution {
public:
  using Map = vector<vector<int>>;
  int shortestDistance(const Map &grid) {
    int minDist = INT_MAX;
    unordered_set<int> hasVisited;
    vector<Point> houses;
    vector<Point> obst;
    vector<Point> locations;
    for (size_t i = 0; i < grid.size(); ++i) {
      for (size_t j = 0; j < grid[0].size(); ++j) {
        if (grid[i][j] == 0) {
          locations.emplace_back(i, j);
        } else if (grid[i][j] == 1) {
          houses.emplace_back(i, j);
        } else if (grid[i][j] == 2) {
          obst.emplace_back(i, j);
        }
      }
    }
    for (const auto &src : locations) {
      const auto  dist = findDist(grid, src, dst);
      if (dist < minDist) {
        minDist = dist;
      }
    }
    return minDist;
  }

private:
  const vector<pair<int, int>> dirs{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};

  int getDist(const Map &map, const Point &src, const Point &dst) {
    // TODO custom hash
    unordered_set<Point> hasVisited;
    int res;
    std::queue<Point> que;
    que.push(src);
    while (!que.empty()) {
      const auto cur = que.top();
      que.pop();
      if (hasVisited.count(cur) != 0) {
        continue;
      }
      hasVisited.insert(cur);
      // if reach dst or obstacle
      if (dst.count(cur) != 0) {
        res += cur.dist;
        continue;
      }
      for (const auto &dir : dirs) {
        Point p(cur.x + dir.first, cur.y + dir.second, cur.dist + 1);
        if (inBound(map, p)) {
          que.push(p);
        }
      }
    }
    return minDist;
  }

  size_t getIdx(const Map &map, const Point &p) {
    return map.size() * p.x + p.y;
  }

  bool inBound(const Map &map, const Point &p) {
    return (p.x >= 0 && p.x < map.size() && p.y >= 0 && p.y < map[0].size());
  }
};
