#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0309 {
public:
	int maxProfit(vector<int>& prices) {
		int profit = 0, cost = INT_MAX, preProfit = 0;
		for (auto iter = prices.begin(); iter != prices.end(); iter++)
		{
			auto old = profit;
			cost = min(cost, *iter - preProfit);
			profit = max(profit, *iter - cost);
			preProfit = old;
		}
		return profit;
	}

	int maxProfit2(vector<int>& prices) {
		int day = -2;
		int p1 = 0, p2 = 0;
		for (int n = 0; n < (int)prices.size() - 1; n++)
		{
			const int delta = prices[n + 1] - prices[n];
			if (delta <= 0)
				continue;
			if (day == n)
			{
				int pp = max(p1 + delta, p2 + prices[n + 1] - prices[n - 1]);
				p1 = max(p1, p2);
				p2 = pp;
			}
			else
			{
				int pp = max(p1, p2) + delta;
				p1 = max(p1, p2);
				p2 = pp;
			}
			day = n + 2;
		}

		return max(p1, p2);
	}
};

void test0309_maxProfit()
{
	int nn;
	vector<int> prices;
	Solution0309 sol;

	prices.assign({ 1, 2, 3, 0, 2 });
	nn = sol.maxProfit(prices);
	assert(nn == 3);
}