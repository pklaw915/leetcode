#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

#include "utils/structs.h"

class Solution0057 {
public:
	vector<Interval> insert(vector<Interval>& intervals, Interval newInterval) {
		if (intervals.empty() || newInterval.start > intervals.back().end)
		{
			intervals.push_back(newInterval);
			return intervals;
		}
		if (newInterval.end < intervals.front().start)
		{
			intervals.insert(intervals.begin(), newInterval);
			return intervals;
		}

		auto iFirst = lower_bound(intervals.begin(), intervals.end(), newInterval, [](const Interval& l, const Interval& r) {
			return l.start < r.start;
		});
		if (iFirst != intervals.begin())
		{
			auto prev = iFirst - 1;
			if (newInterval.start <= prev->end)
				iFirst = prev;
		}
		if (newInterval.end < iFirst->start)
		{
			intervals.insert(iFirst, newInterval);
			return intervals;
		}
		iFirst->start = min(iFirst->start, newInterval.start);

		auto iLast = lower_bound(iFirst, intervals.end(), newInterval, [](const Interval& l, const Interval& r) {
			return l.end < r.end;
		});
		if (iLast != intervals.end() && iLast->start <= newInterval.end)
		{
			newInterval.end = iLast->end;
			++iLast;
		}
		iFirst->end = newInterval.end;
		intervals.erase(iFirst + 1, iLast);
		return intervals;
	}
};

void test0057_insert()
{
	Solution0057 sol;
	vector<Interval> intervals, ret;
	Interval newInterval;

	intervals.clear();
	intervals.push_back(Interval(1, 3));
	intervals.push_back(Interval(6, 9));
	newInterval = Interval(2, 5);
	ret = sol.insert(intervals, newInterval);
	assert(ret.size() == 2 && ret[0].start == 1 && ret[0].end == 5 && ret[1].start == 6 && ret[1].end == 9);

	intervals.clear();
	intervals.push_back(Interval(1, 2));
	intervals.push_back(Interval(3, 5));
	intervals.push_back(Interval(6, 7));
	intervals.push_back(Interval(8, 10));
	intervals.push_back(Interval(12, 16));
	newInterval = Interval(4, 8);
	ret = sol.insert(intervals, newInterval);
	assert(ret.size() == 3);
	assert(ret[0].start == 1 && ret[0].end == 2);
	assert(ret[1].start == 3 && ret[1].end == 10);
	assert(ret[2].start == 12 && ret[2].end == 16);

	const int points[] = { -1, 0, 1, 2, 3, 4, 5, 6, 7, 9, 12, 15 };
	for (size_t i = 0; i < _countof(points) - 1; i++)
	{
		for (size_t j = i + 1; j < _countof(points); j++)
		{
			intervals.clear();
			intervals.push_back(Interval(1, 3));
			intervals.push_back(Interval(6, 9));

			newInterval = Interval(points[i], points[j]);
			ret = sol.insert(intervals, newInterval);
		}
	}
}