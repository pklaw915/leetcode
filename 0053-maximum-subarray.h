#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0053 {
public:
	int maxSubArray(vector<int>& nums) {
		if (nums.empty())
			return 0;
		int maxsum = INT_MIN, minimum = 0, cumu = 0;
		for (auto iter = nums.begin(); iter != nums.end(); iter++)
		{
			cumu += *iter;
			maxsum = max(maxsum, cumu - minimum);
			minimum = min(minimum, cumu);
			
		}
		return maxsum;
	}

	int maxSubArray2(vector<int>& nums) {
		if (nums.size() < 1)
			return 0;

		int maximum = 0, last = 0;

		size_t n = 0;
		while (n < nums.size())
		{
			int delta = 0;
			while (n < nums.size())
			{
				if (nums[n] * delta < 0)
					break;
				delta += nums[n];
				n++;
			}

			last += delta;
			int prev = max(delta, 0);
			if (prev > last)
				last = prev;
			if (last > maximum)
				maximum = last;
		}
		if (maximum == 0)
		{
			n = 0;
			maximum = nums[0];
			while (n < nums.size())
			{
				if (nums[n] > maximum)
					maximum = nums[n];
				n++;
			}
		}
		return maximum;
	}
};

void test0053_maxSubArray()
{
	int nn;
	vector<int> nums;
	Solution0053 sol;

	nums.assign({ -2, 1, -3, 4, -1, 2, 1, -5, 4 });
	nn = sol.maxSubArray(nums);
	assert(nn == 6);

	nums.assign({ -2 });
	nn = sol.maxSubArray(nums);
	assert(nn == -2);

}