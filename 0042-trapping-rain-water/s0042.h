#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0042 {
public:
	int trap(vector<int>& height) {
		vector<int> width; width.resize(height.size());
		int traps = 0, last = -1;
		for (auto iter = height.begin(); iter != height.end(); iter++)
		{
			const int h = *iter;
			if (last < 0)
			{
				if (h > 0)
				{
					height[++last] = h;
					width[last] = 1;
				}
			}
			else if (h < height[last])
			{
				height[++last] = h;
				width[last] = 1;
			}
			else if (h == height[last])
			{
				width[last]++;
			}
			else	// h > height[last]
			{
				const int top = min(height[0], h);
				int count = 1;
				while (last >= 0)
				{
					if (height[last] > h)
						break;
					count += width[last];
					traps += (top - height[last]) * width[last];
					--last;
				}
				if (last < 0)
				{
					last = 0;
					height[last] = h;
					width[last] = 1;
				}
				else
				{
					++last;		// height[last] > h
					height[last] = h;
					width[last] = count;
				}
			}
		}
		return traps;
	}
};

void test0042_trap()
{
	int n;
	Solution0042 sol;
	vector<int> height;

	height.clear();
	height.assign({ 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 });
	n = sol.trap(height);
	assert(n == 6);

	height.clear();
	height.assign({ 5, 4, 10, 9, 8, 7, 6, 7, 8, 9, 4, 3 });
	n = sol.trap(height);
	assert(n == 10);
}