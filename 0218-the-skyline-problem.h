#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0218 {
public:
	vector<pair<int, int>> getSkyline(vector<vector<int>>& buildings) {
		vector < pair<int, int>> skyline;
		if (buildings.empty())
			return skyline;

		vector<pair<int, int>> hp;
		{
			const vector<int>& b = buildings[0];
			skyline.push_back(make_pair(b[0], b[2]));
			push_point(hp, b[1], b[2]);
		}

		for (size_t i = 1; i < buildings.size(); i++)
		{
			const vector<int>& b = buildings[i];

			while (!hp.empty() && hp[0].first < b[0])
			{
				pair<int, int> pt = pop_point(hp);
				if (pt.first >= b[0])
				{
					push_point(hp, pt.first, skyline.back().second);
					break;
				}
				skyline.push_back(pt);
			}
			// hp.empty() || b[0] <= hp[0].first

			if (b[0] == skyline.back().first)
			{
				skyline.back().second = max(skyline.back().second, b[2]);
			}
			else if (hp.empty() || hp[0].second < b[2])
			{
				skyline.push_back(make_pair(b[0], b[2]));
			}

			push_point(hp, b[1], b[2]);
		}

		while (!hp.empty())
		{
			pair<int, int> pt = pop_point(hp);
			skyline.push_back(pt);
		}

		return skyline;
	}

	static bool comp_point(const pair<int, int>& pt1, const pair<int, int>& pt2)
	{
		return pt1.second < pt2.second;
	}

	void push_point(vector<pair<int, int>>& hp, int x, int y)
	{
		hp.push_back(make_pair(x, y));
		push_heap(hp.begin(), hp.end(), comp_point);
	}

	pair<int, int> pop_point(vector<pair<int, int>>& hp)
	{
		auto beg = hp.begin();
		auto end = hp.end();
		assert(beg != end);

		pair<int, int> rt = *beg;
		do {
			rt.first = max(rt.first, beg->first);
			pop_heap(beg, end, comp_point);
			--end;
		} while (beg != end && beg->second == rt.second);

		while (beg != end && beg->first < rt.first)
		{
			pop_heap(beg, end, comp_point);
			--end;
		}

		hp.erase(end, hp.end());

		rt.second = hp.empty() ? 0 : hp[0].second;

		return rt;
	}
};

void test0218_getSkyline()
{
	Solution0218 sol;
	vector<vector<int>> buildings;
	vector<pair<int, int>> skyline;

	buildings.resize(5);
	buildings[0].assign({2, 9, 10});
	buildings[1].assign({3, 7, 15});
	buildings[2].assign({5, 12, 12});
	buildings[3].assign({15, 20, 10});
	buildings[4].assign({19, 24, 8});
	skyline = sol.getSkyline(buildings);
	assert(skyline.size() == 7);	// [[2 10], [3 15], [7 12], [12 0], [15 10], [20 8], [24, 0]]

	buildings.resize(2);
	buildings[0].assign({ 0, 2, 3 });
	buildings[1].assign({ 2, 5, 3 });
	skyline = sol.getSkyline(buildings);
	assert(skyline.size() == 2);	// [[0 3], [5 0]]

	buildings.resize(3);
	buildings[0].assign({ 0, 2, 3 });
	buildings[1].assign({ 2, 4, 3 });
	buildings[2].assign({ 4, 6, 3 });
	skyline = sol.getSkyline(buildings);
	assert(skyline.size() == 2);	// [[0 3], [6 0]]
}