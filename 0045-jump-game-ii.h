#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0045 {
public:
	int jump(vector<int>& nums) {
		const int size = (int)nums.size();
		int beg = 0, end = 1, steps = 0;
		while (end < size)
		{
			++steps;

			int reach = beg;
			while (beg < end)
			{
				int nn = beg + nums[beg];
				if (nn > reach)
					reach = nn;
				++beg;
			}
			end = reach + 1;
		}
		return steps;
	}
};