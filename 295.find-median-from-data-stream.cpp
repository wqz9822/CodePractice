/*
 * @lc app=leetcode id=295 lang=cpp
 *
 * [295] Find Median from Data Stream
 *
 * https://leetcode.com/problems/find-median-from-data-stream/description/
 *
 * algorithms
 * Hard (34.78%)
 * Total Accepted:    116.9K
 * Total Submissions: 311.5K
 * Testcase Example:
 * '["MedianFinder","addNum","addNum","findMedian","addNum","findMedian"]\n[[],[1],[2],[],[3],[]]'
 *
 * Median is the middle value in an ordered integer list. If the size of the
 * list is even, there is no middle value. So the median is the mean of the two
 * middle value.
 * For example,
 *
 * [2,3,4], the median is 3
 *
 * [2,3], the median is (2 + 3) / 2 = 2.5
 *
 * Design a data structure that supports the following two operations:
 *
 *
 * void addNum(int num) - Add a integer number from the data stream to the data
 * structure.
 * double findMedian() - Return the median of all elements so far.
 *
 *
 *
 *
 * Example:
 *
 *
 * addNum(1)
 * addNum(2)
 * findMedian() -> 1.5
 * addNum(3)
 * findMedian() -> 2
 *
 *
 *
 *
 * Follow up:
 *
 *
 * If all integer numbers from the stream are between 0 and 100, how would you
 * optimize it?
 * If 99% of all integer numbers from the stream are between 0 and 100, how
 * would you optimize it?
 *
 *
 */
class MedianFinder {
public:
  /** initialize your data structure here. */
  MedianFinder() {}

  void addNum(int num) {
    if (lo.empty() || num <= mid) {
      lo.push(num);
      // note: push number first, then swap hi/lo, because
      // new element might be the top
      if (lo.size() > hi.size() + 1) {
        hi.push(lo.top());
        lo.pop();
      }
    } else {
      hi.push(num);
      if (lo.size() < hi.size()) {
        lo.push(hi.top());
        hi.pop();
      }
    }
    assert(!lo.empty());
    if ((lo.size() + hi.size()) % 2 == 0) {
      mid = hi.empty() ? lo.top() : (lo.top() + hi.top()) / 2.0;
    } else {
      mid = lo.top();
    }
  }

  double findMedian() { return mid; }

private:
  std::priority_queue<int, std::vector<int>, std::less<int>> lo;    // max heap
  std::priority_queue<int, std::vector<int>, std::greater<int>> hi; // min heap
  double mid = 0;
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */
