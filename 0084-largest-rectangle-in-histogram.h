#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0084 {
public:
	int largestRectangleArea(vector<int>& heights) {
		int size = 0, largest = 0;
		vector<int> indices(heights.size());
		for (int n = 0; n < (int)heights.size(); n++)
		{
			if (heights[n] <= 0)
			{
				largest = max(largest, largestArea(heights, indices, 0, size, n));
				size = 0;
				continue;
			}

			auto iter = lower_bound(heights.begin(), heights.begin() + size, heights[n]);
			auto last = (int)distance(heights.begin(), iter);
			largest = max(largest, largestArea(heights, indices, last, size, n));
			if (last == size)
				indices[last] = n;
			heights[last] = heights[n];
			size = last + 1;
		}

		largest = max(largest, largestArea(heights, indices, 0, size, (int)heights.size()));
		return largest;
	}

	int largestArea(const vector<int>& heights, const vector<int>& indices, int beg, int end, int right)
	{
		int largest = 0;
		for (int n = beg; n < end; n++)
		{
			int area = (right - indices[n]) * heights[n];
			if (largest < area)
				largest = area;
		}
		return largest;
	}
};

void test0084_largestRectangleArea()
{
	vector<int> heights;
	Solution0084 sol;
	int nn;

	heights.assign({ 2, 1, 5, 6, 2, 3 });
	nn = sol.largestRectangleArea(heights);
	assert(nn == 10);

	heights.assign({ 2, 1, 5, 0, 6, 2, 3 });
	nn = sol.largestRectangleArea(heights);
	assert(nn == 6);
}