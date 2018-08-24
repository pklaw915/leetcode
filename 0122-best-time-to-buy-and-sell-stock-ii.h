#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0122 {
public:
	int maxProfit(vector<int>& prices) {
		int profit = 0, cost = INT_MAX;
		for (auto iter = prices.begin(); iter != prices.end(); iter++)
		{
			cost = min(cost, *iter - profit);
			profit = max(profit, *iter - cost);
		}
		return profit;
	}

	int maxProfit2(vector<int>& prices) {
		int sum = 0;
		for (size_t n = 1; n < prices.size(); n++)
		{
			int delta = prices[n] - prices[n - 1];
			if (delta > 0)
				sum += delta;
		}
		return sum;
	}
};

void test0122_maxProfit()
{
	int nn;
	vector<int> prices;
	Solution0122 sol;

	prices.assign({ 7, 1, 5, 3, 6, 4 });
	nn = sol.maxProfit(prices);
	assert(nn == 7);

	prices.assign({ 1, 2, 3, 4, 5 });
	nn = sol.maxProfit(prices);
	assert(nn == 4);

	prices.assign({ 7, 6, 4, 3, 1 });
	nn = sol.maxProfit(prices);
	assert(nn == 0);
}