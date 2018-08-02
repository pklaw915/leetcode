#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0871 {
public:
	int minRefuelStops(int target, int startFuel, vector<vector<int>>& stations) {
		if (startFuel >= target)
			return 0;

		vector<int> remains;
		remains.resize(stations.size() + 1);

		int min_stops = 0;
		int max_stops = 0;
		int position = 0;
		remains[0] = startFuel;

		for (auto iter = stations.begin(); iter != stations.end(); ++iter)
		{
			const int dist = (*iter)[0] - position;
			const int max_refuel = target - (*iter)[0];
			const int fuel = min(max_refuel, (*iter)[1]);

			while (min_stops <= max_stops && remains[min_stops] < dist)
				++min_stops;
			if (min_stops > max_stops)
				return -1;
			remains[min_stops] -= dist;

			int last = remains[min_stops];
			for (int nn = min_stops + 1; nn <= max_stops; ++nn)
			{
				remains[nn] -= dist;
				int after_refuel = last + fuel;
				last = remains[nn];
				if (after_refuel > last)
					remains[nn] = after_refuel;
			}

			++max_stops;
			remains[max_stops] = last + fuel;

			if (remains[max_stops] > max_refuel)
			{
				for (int nn = max_stops - 1; nn >= min_stops; nn--)
				{
					if (remains[nn] < max_refuel)
						break;
					max_stops = nn;
				}
			}

			position = (*iter)[0];
		}

		int dist = target - position;
		for (int ii = min_stops; ii <= max_stops; ++ii)
		{
			if (remains[ii] >= dist)
				return ii;
		}
		return -1;
	}
};


void test_minRefuelStops()
{
	int nn;
	int target;
	int startFuel;
	vector<vector<int>> stations;
	vector<int> empty;
	Solution0871 sol;

#ifdef _DEBUG
	target = 1;
	startFuel = 1;
	stations.clear();
	nn = sol.minRefuelStops(target, startFuel, stations);
	assert(nn == 0);

	target = 10;
	startFuel = 1;
	stations.clear();
	nn = sol.minRefuelStops(target, startFuel, stations);
	assert(nn == -1);

	target = 100;
	startFuel = 1;
	stations.clear();
	stations.push_back(empty);
	stations.back().push_back(10);
	stations.back().push_back(100);
	nn = sol.minRefuelStops(target, startFuel, stations);
	assert(nn == -1);

	target = 1000000000;
	startFuel = 10;
	stations.clear();
	stations.push_back(empty);
	stations.back().push_back(10);
	stations.back().push_back(1000000000);
	stations.push_back(empty);
	stations.back().push_back(20);
	stations.back().push_back(1000000000);
	stations.push_back(empty);
	stations.back().push_back(30);
	stations.back().push_back(1000000000);
	stations.push_back(empty);
	stations.back().push_back(40);
	stations.back().push_back(1000000000);
	nn = sol.minRefuelStops(target, startFuel, stations);
	assert(nn == 1);

	target = 100;
	startFuel = 10;
	stations.clear();
	stations.push_back(empty);
	stations.back().push_back(10);
	stations.back().push_back(60);
	stations.push_back(empty);
	stations.back().push_back(20);
	stations.back().push_back(30);
	stations.push_back(empty);
	stations.back().push_back(30);
	stations.back().push_back(30);
	stations.push_back(empty);
	stations.back().push_back(60);
	stations.back().push_back(40);
	nn = sol.minRefuelStops(target, startFuel, stations);
	assert(nn == 2);
#endif // _DEBUG

	target = 10000;
	startFuel = 10;
	stations.clear();
	for (int ii = 1; ii < 1000; ++ii)
	{
		stations.push_back(empty);
		stations.back().push_back(ii * 10);
		stations.back().push_back((ii % 2) ? 10 : 20);
	}

	nn = 0;
	int repeat = 100000;
	for (int ii = 0; ii < repeat; ++ii)
	{
		nn += sol.minRefuelStops(target, startFuel, stations);
	}
	assert(nn == 500 * repeat);
}