/*
 * @lc app=leetcode id=253 lang=cpp
 *
 * [253] Meeting Rooms II
 *
 * https://leetcode.com/problems/meeting-rooms-ii/description/
 *
 * algorithms
 * Medium (43.28%)
 * Total Accepted:    180.3K
 * Total Submissions: 414.4K
 * Testcase Example:  '[[0,30],[5,10],[15,20]]'
 *
 * Given an array of meeting time intervals consisting of start and end times
 * [[s1,e1],[s2,e2],...] (si < ei), find the minimum number of conference rooms
 * required.
 *
 * Example 1:
 *
 *
 * Input: [[0, 30],[5, 10],[15, 20]]
 * Output: 2
 *
 * Example 2:
 *
 *
 * Input: [[7,10],[2,4]]
 * Output: 1
 *
 * NOTE: input types have been changed on April 15, 2019. Please reset to
 * default code definition to get new method signature.
 *
 */
class Solution {
public:
  int minMeetingRooms(vector<vector<int>> &intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](const vector<int> &a, const vector<int> &b) -> bool {
                return a[0] < b[0];
              });
    // keep track of earliest end time of all rooms
    std::priority_queue<int, vector<int>, std::greater<int>> roomEndTimes;
    int res = 0;
    for (size_t i = 0; i < intervals.size(); ++i) {
      if (roomEndTimes.empty() || intervals[i][0] < roomEndTimes.top()) {
        // if current interval's start time is earlier than the earliest end
        // time of all rooms, then create new room
        res++;
      } else {
        // update this room's end time with current interval
        roomEndTimes.pop();
      }
      roomEndTimes.push(intervals[i][1]);
      // cout << roomEndTimes.top() << endl;
    }
    return res;
  }
};
