#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;


#include "utils/structs.h"

class Solution0056 {
public:
	vector<Interval> merge(vector<Interval>& intervals) {
		if (intervals.size() < 2)
			return intervals;
		sort(intervals.begin(), intervals.end(), [](const Interval& i1, const Interval& i2)
		{
			return i1.start < i2.start;
		});
		int last = 0;
		for (size_t i = 1; i < intervals.size(); i++)
		{
			if (intervals[last].end >= intervals[i].start)
			{
				intervals[last].end = max(intervals[last].end, intervals[i].end);
			}
			else
			{
				++last;
				intervals[last] = intervals[i];
			}
		}
		++last;
		intervals.resize(last);
		return intervals;
	}
};

void test0056_merge()
{
	Solution0056 sol;
	vector<Interval> intervals;

	intervals.resize(4);
	intervals[0].start = 1; intervals[0].end = 3;
	intervals[1].start = 2; intervals[1].end = 6;
	intervals[2].start = 8; intervals[2].end = 10;
	intervals[3].start = 15; intervals[3].end = 18;
	intervals = sol.merge(intervals);		// [[1, 6], [8, 10], [15, 18]]
	assert(intervals.size() == 3);
}