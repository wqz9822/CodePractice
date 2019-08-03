/*
 * @lc app=leetcode id=341 lang=cpp
 *
 * [341] Flatten Nested List Iterator
 *
 * https://leetcode.com/problems/flatten-nested-list-iterator/description/
 *
 * algorithms
 * Medium (48.38%)
 * Total Accepted:    118.2K
 * Total Submissions: 243.3K
 * Testcase Example:  '[[1,1],2,[1,1]]'
 *
 * Given a nested list of integers, implement an iterator to flatten it.
 *
 * Each element is either an integer, or a list -- whose elements may also be
 * integers or other lists.
 *
 * Example 1:
 *
 *
 *
 * Input: [[1,1],2,[1,1]]
 * Output: [1,1,2,1,1]
 * Explanation: By calling next repeatedly until hasNext returns
 * false,
 * the order of elements returned by next should be: [1,1,2,1,1].
 *
 *
 * Example 2:
 *
 *
 * Input: [1,[4,[6]]]
 * Output: [1,4,6]
 * Explanation: By calling next repeatedly until hasNext returns
 * false,
 * the order of elements returned by next should be: [1,4,6].
 *
 *
 *
 *
 */
/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than
 * a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a
 * single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a
 * nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
class NestedIterator {
public:
  explicit NestedIterator(vector<NestedInteger> &nestedList) {
    const auto res = flatten(nestedList);
    for (const auto &item : res) {
      buf_.push(item);
    }
  }

  int next() {
    int res = buf_.front();
    buf_.pop();
    return res;
  }

  bool hasNext() { return !buf_.empty(); }

private:
  vector<int> flatten(const vector<NestedInteger> &list) {
    vector<int> res;
    for (const auto &item : list) {
      if (item.isInteger()) {
        res.push_back(item.getInteger());
      } else {
        const auto newList = flatten(item.getList());
        res.insert(res.end(), newList.begin(), newList.end());
      }
    }
    return res;
  }

  queue<int> buf_;
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
