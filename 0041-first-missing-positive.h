#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0041 {
public:
	int firstMissingPositive(vector<int>& nums) {
		const int size = (int)nums.size();
		bool bHasEndding = size == 0;
		for (auto iter = nums.begin(); iter != nums.end(); iter++)
		{
			if (*iter < 0 || *iter >= size)
			{
				if (!bHasEndding)
					bHasEndding = *iter == size;
				*iter = 0;
			}
		}

		for (int ii = 0; ii < size; ++ii)
		{
			int nn = nums[ii];		// nn the number
			if (nn > 0)
			{
				nums[ii] = 0;
				do
				{
					int next = nums[nn];
					nums[nn] = -1;
					nn = next;
				} while (nn > 0);
			}
		}

		for (int ii = 1; ii < size; ++ii)
		{
			if (nums[ii] == 0)
				return ii;
		}

		return bHasEndding ? (size + 1) : size;
	}
};



void test0041_firstMissingPositive()
{
	Solution0041 sol;
	int nn;
	vector<int> nums;

	nums.clear();
	nn = sol.firstMissingPositive(nums);
	assert(nn == 1);

	nums.clear();
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(0);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 3);

	nums.clear();
	nums.push_back(0);
	nums.push_back(1);
	nums.push_back(3);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 2);

	nums.clear();
	nums.push_back(3);
	nums.push_back(4);
	nums.push_back(-1);
	nums.push_back(1);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 2);

	nums.clear();
	nums.push_back(7);
	nums.push_back(8);
	nums.push_back(9);
	nums.push_back(11);
	nums.push_back(12);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 1);

	nums.clear();
	nums.push_back(7);
	nums.push_back(8);
	nums.push_back(9);
	nums.push_back(11);
	nums.push_back(12);
	nums.push_back(1);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 2);

	nums.clear();
	nums.push_back(3);
	nums.push_back(3);
	nums.push_back(1);
	nums.push_back(4);
	nums.push_back(0);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 2);

	nums.clear();
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(2);
	nums.push_back(3);
	nums.push_back(7);
	nums.push_back(8);
	nums.push_back(9);
	nums.push_back(11);
	nums.push_back(12);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 4);

	nums.clear();
	nums.push_back(5);
	nums.push_back(4);
	nums.push_back(2);
	nums.push_back(1);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 3);

	nums.clear();
	nums.push_back(5);
	nums.push_back(4);
	nums.push_back(2);
	nums.push_back(1);
	nums.push_back(3);
	nn = sol.firstMissingPositive(nums);
	assert(nn == 6);
}