#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0055 {
public:
	bool canJump(vector<int>& nums) {
		const int size = (int)nums.size();
		int beg = 0, end = 1;
		while (end < size)
		{
			int reach = beg;
			while (beg < end)
			{
				int nn = beg + nums[beg];
				if (nn > reach)
					reach = nn;
				++beg;
			}
			if (reach < end)
				return false;
			end = reach + 1;
		}
		return true;
	}
};