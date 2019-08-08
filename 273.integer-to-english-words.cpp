/*
 * @lc app=leetcode id=273 lang=cpp
 *
 * [273] Integer to English Words
 *
 * https://leetcode.com/problems/integer-to-english-words/description/
 *
 * algorithms
 * Hard (23.83%)
 * Total Accepted:    110.7K
 * Total Submissions: 449.1K
 * Testcase Example:  '123'
 *
 * Convert a non-negative integer to its english words representation. Given
 * input is guaranteed to be less than 231 - 1.
 *
 * Example 1:
 *
 *
 * Input: 123
 * Output: "One Hundred Twenty Three"
 *
 *
 * Example 2:
 *
 *
 * Input: 12345
 * Output: "Twelve Thousand Three Hundred Forty Five"
 *
 * Example 3:
 *
 *
 * Input: 1234567
 * Output: "One Million Two Hundred Thirty Four Thousand Five Hundred Sixty
 * Seven"
 *
 *
 * Example 4:
 *
 *
 * Input: 1234567891
 * Output: "One Billion Two Hundred Thirty Four Million Five Hundred Sixty
 * Seven Thousand Eight Hundred Ninety One"
 *
 *
 */
class Solution {
	public:
		string numberToWords(int num) {
			if(num == 0) {
				return "Zero";
			}

			numMap_[1] = "One";
			numMap_[2] = "Two";
			numMap_[3] = "Three";
			numMap_[4] = "Four";
			numMap_[5] = "Five";
			numMap_[6] = "Six";
			numMap_[7] = "Seven";
			numMap_[8] = "Eight";
			numMap_[9] = "Nine";
			numMap_[10] = "Ten";
			numMap_[11] = "Eleven";
			numMap_[12] = "Twelve";
			numMap_[13] = "Thirteen";
			numMap_[14] = "Fourteen";
			numMap_[15] = "Fifteen";
			numMap_[16] = "Sixteen";
			numMap_[17] = "Seventeen";
			numMap_[18] = "Eighteen";
			numMap_[19] = "Nineteen";
			numMap_[20] = "Twenty";
			numMap_[30] = "Thirty";
			numMap_[40] = "Forty";
			numMap_[50] = "Fifty";
			numMap_[60] = "Sixty";
			numMap_[70] = "Seventy";
			numMap_[80] = "Eighty";
			numMap_[90] = "Ninety";
			vector<std::string> powerName{"Billion", "Million", "Thousand"};

			ostringstream res;
			int div = 0;
			int po = 0;
			for(size_t i = 0; i < powerName.size(); ++i) {
				po = 9 - 3 * i;
				div = num / (int)(int)pow(10, po);
				num = num % (int)(int)pow(10, po);
				if(div > 0) {
					printNumUnder1000(div, res);
					res << powerName[i] << " ";
				}
			}
			printNumUnder1000(num, res);
			auto resStr = res.str();
			resStr.pop_back();
			return resStr;
		}

	private:
		void printNumUnder1000(int num, ostringstream& out) {
			// assert(num >= 0 && num < 1000);
			if(num < 100) {
				printNumUnder100(num, out);
				return;
			}
			int div = num / 100;
			out << numMap_[div] << " Hundred ";
			printNumUnder100(num - 100 * div, out);
		}

		void printNumUnder100(int num, ostringstream& out) {
			// assert(num >= 0 && num < 100);
			if(num < 20) {
				printNumUnder20(num, out);
				return;
			}
			int div = num / 10;
			out << numMap_[div * 10] << " ";
			printNumUnder20(num - 10* div, out);
		}

		void printNumUnder20(int num, ostringstream& out) {
			// assert(num >= 0 && num < 20);
			if(num == 0) {
				return;
			}
			out << numMap_[num] << " ";
		}

		unordered_map<int, std::string> numMap_;
};
