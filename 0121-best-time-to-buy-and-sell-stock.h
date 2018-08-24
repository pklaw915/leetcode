#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0121 {
public:
	int maxProfit(vector<int>& prices) {
		int profit = 0, cost = INT_MAX;
		for (auto iter = prices.begin(); iter != prices.end(); iter++)
		{
			cost = min(cost, *iter);
			profit = max(profit, *iter - cost);
		}
		return profit;
	}

	int maxProfit2(vector<int>& prices) {
		if (prices.size() < 2)
			return 0;

		int profit = 0, last = 0;

		size_t n = 1;
		while (n < prices.size())
		{
			int delta = 0;
			while (n < prices.size())
			{
				const int d = prices[n] - prices[n - 1];
				if (d * delta < 0)
					break;
				delta += d;
				n++;
			}

			last += delta;
			int prev = max(delta, 0);
			if (prev > last)
				last = prev;
			if (last > profit)
				profit = last;
		}

		return profit;
	}
};

void test0121_maxProfit()
{
	int nn;
	vector<int> prices;
	Solution0121 sol;

	prices.assign({ 7, 1, 5, 3, 6, 4 });
	nn = sol.maxProfit(prices);
	assert(nn == 5);

	prices.assign({ 7, 6, 4, 3, 1 });
	nn = sol.maxProfit(prices);
	assert(nn == 0);
}