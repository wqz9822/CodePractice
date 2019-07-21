/*
 * @lc app=leetcode id=973 lang=cpp
 *
 * [973] K Closest Points to Origin
 *
 * https://leetcode.com/problems/k-closest-points-to-origin/description/
 *
 * algorithms
 * Easy (66.43%)
 * Total Accepted:    78.6K
 * Total Submissions: 127.1K
 * Testcase Example:  '[[1,3],[-2,2]]\n1'
 *
 * We have a list of points on the plane.  Find the K closest points to the
 * origin (0, 0).
 *
 * (Here, the distance between two points on a plane is the Euclidean
 * distance.)
 *
 * You may return the answer in any order.  The answer is guaranteed to be
 * unique (except for the order that it is in.)
 *
 *
 *
 *
 * Example 1:
 *
 *
 * Input: points = [[1,3],[-2,2]], K = 1
 * Output: [[-2,2]]
 * Explanation:
 * The distance between (1, 3) and the origin is sqrt(10).
 * The distance between (-2, 2) and the origin is sqrt(8).
 * Since sqrt(8) < sqrt(10), (-2, 2) is closer to the origin.
 * We only want the closest K = 1 points from the origin, so the answer is just
 * [[-2,2]].
 *
 *
 *
 * Example 2:
 *
 *
 * Input: points = [[3,3],[5,-1],[-2,4]], K = 2
 * Output: [[3,3],[-2,4]]
 * (The answer [[-2,4],[3,3]] would also be accepted.)
 *
 *
 *
 *
 * Note:
 *
 *
 * 1 <= K <= points.length <= 10000
 * -10000 < points[i][0] < 10000
 * -10000 < points[i][1] < 10000
 *
 *
 *
 */
struct Node {
  Node(int x_, int y_) : x(x_), y(y_) {}
  bool operator>(const Node &rhs) const {
    return (x * x + y * y) > (rhs.x * rhs.x) + (rhs.y * rhs.y);
  }
  int x;
  int y;
};

class Solution {
public:
  vector<vector<int>> kClosest(vector<vector<int>> &points, int K) {
    vector<vector<int>> res;
    if (K == 0 || K > points.size()) {
      return res;
    }
    for (const auto &p : points) {
      min_pq.push(Node(p[0], p[1]));
    }
    for (int i = 0; i < K; ++i) {
      res.push_back(vector<int>{min_pq.top().x, min_pq.top().y});
      min_pq.pop();
    }
    return res;
  }

private:
  priority_queue<Node, vector<Node>, std::greater<Node>> min_pq;
};
