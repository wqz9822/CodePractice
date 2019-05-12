/*
 * @lc app=leetcode id=621 lang=cpp
 *
 * [621] Task Scheduler
 *
 * https://leetcode.com/problems/task-scheduler/description/
 *
 * algorithms
 * Medium (44.26%)
 * Total Accepted:    82K
 * Total Submissions: 181.4K
 * Testcase Example:  '["A","A","A","B","B","B"]\n2'
 *
 * Given a char array representing tasks CPU need to do. It contains capital
 * letters A to Z where different letters represent different tasks. Tasks
 * could be done without original order. Each task could be done in one
 * interval. For each interval, CPU could finish one task or just be idle.
 *
 * However, there is a non-negative cooling interval n that means between two
 * same tasks, there must be at least n intervals that CPU are doing different
 * tasks or just be idle.
 *
 * You need to return the least number of intervals the CPU will take to finish
 * all the given tasks.
 *
 *
 *
 * Example:
 *
 *
 * Input: tasks = ["A","A","A","B","B","B"], n = 2
 * Output: 8
 * Explanation: A -> B -> idle -> A -> B -> idle -> A -> B.
 *
 *
 *
 *
 * Note:
 *
 *
 * The number of tasks is in the range [1, 10000].
 * The integer n is in the range [0, 100].
 *
 *
 */
struct Job {
  char name;
  int num;
  int time;
  Job(char name_, int num_) : name(name_), num(num_) {}
};

class Solution {
public:
  int leastInterval(const vector<char> &tasks, int n) {
    auto cmp = [](const Job &a, const Job &b) { return a.num < b.num; };
    std::priority_queue<Job, vector<Job>, decltype(cmp)> pq{cmp};
    std::queue<Job> off_queue;
    std::unordered_map<char, int> map;
    for (const auto t : tasks) {
      map[t]++;
    }
    for (const auto t : map) {
      pq.push(Job(t.first, t.second));
    }
    int res = 0;
    while (!pq.empty() || !off_queue.empty()) {
      if (!off_queue.empty()) {
        if (off_queue.front().time == res) {
          pq.push(off_queue.front());
          off_queue.pop();
        }
      }
      if (!pq.empty()) {
        auto job = pq.top();
        if (--job.num != 0) {
          job.time = res + n + 1;
          off_queue.push(job);
        }
        pq.pop();
      }
      res++;
    }
    return res;
  }
};
