#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0031 {
public:
	void nextPermutation(vector<int>& nums) {
		int k = 0;
		for (k = (int)nums.size() - 2; k >= 0; k--)
		{
			if (nums[k] < nums[k + 1])
			{
				int m = (int)nums.size();
				while (--m && nums[m] <= nums[k]);
				swap(nums[k], nums[m]);
				++k;
				break;
			}
		}
		if (k < 0)
			k = 0;
		int r = (int)nums.size() - 1;
		while (k < r)
		{
			swap(nums[k], nums[r]);
			k++;
			r--;
		}
	}
};

void test0031_nextPermutation()
{
	Solution0031 sol;
	vector<int> nums;

	nums.clear();
	nums.push_back(1);
	nums.push_back(2);
	nums.push_back(3);
	for (int k = 0; k < 6; k++)
		sol.nextPermutation(nums);
	assert(nums[0] == 1 && nums[1] == 2 && nums[2] == 3);

	nums.clear();
	nums.push_back(1);
	nums.push_back(1);
	nums.push_back(5);
	for (int k = 0; k < 3; k++)
		sol.nextPermutation(nums);
	assert(nums[0] == 1 && nums[1] == 1 && nums[2] == 5);

	nums.clear();
	nums.push_back(1);
	nums.push_back(5);
	nums.push_back(5);
	for (int k = 0; k < 3; k++)
		sol.nextPermutation(nums);
	assert(nums[0] == 1 && nums[1] == 5 && nums[2] == 5);

}