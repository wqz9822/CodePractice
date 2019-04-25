#include <climits>
/*
 * @lc app=leetcode id=121 lang=cpp
 *
 * [121] Best Time to Buy and Sell Stock
 *
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
 *
 * algorithms
 * Easy (46.16%)
 * Total Accepted:    476.8K
 * Total Submissions: 1M
 * Testcase Example:  '[7,1,5,3,6,4]'
 *
 * Say you have an array for which the ith element is the price of a given
 * stock on day i.
 * 
 * If you were only permitted to complete at most one transaction (i.e., buy
 * one and sell one share of the stock), design an algorithm to find the
 * maximum profit.
 * 
 * Note that you cannot sell a stock before you buy one.
 * 
 * Example 1:
 * 
 * 
 * Input: [7,1,5,3,6,4]
 * Output: 5
 * Explanation: Buy on day 2 (price = 1) and sell on day 5 (price = 6), profit
 * = 6-1 = 5.
 * Not 7-1 = 6, as selling price needs to be larger than buying price.
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [7,6,4,3,1]
 * Output: 0
 * Explanation: In this case, no transaction is done, i.e. max profit = 0.
 * 
 * 
 */
class Solution {
public:
    int maxProfit(const vector<int>& prices) {
    vector<int> max_right(prices.size(), -1);
    int cur_max = -1;
    int cur_min = INT_MAX;
    int max_profit = 0;
    for (int i = 0; i < prices.size(); ++i) {
      if (prices[prices.size()- i - 1] > cur_max) {
        cur_max = prices[prices.size() - i - 1];
      }
      max_right[prices.size() - i - 1] = cur_max;
    }

    for (int i = 0; i < prices.size(); ++i) {
      if (prices[i] < cur_min) {
        cur_min = prices[i];
      }
      if ((max_right[i] - cur_min) > max_profit) {
        max_profit = max_right[i] - cur_min;
      }
    }
    return max_profit;
}
};
