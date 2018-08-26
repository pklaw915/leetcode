#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0213 {
public:
	int rob(vector<int>& nums) {
		if (nums.size() < 2)
			return nums.empty() ? 0 : nums[0];

		int s1 = rob(nums, 0, nums.size() - 1);
		int s2 = rob(nums, 1, nums.size());
		return max(s1, s2);
	}

	int rob(vector<int>& nums, size_t start, size_t end)
	{
		int s1 = 0, s2 = 0;
		for (size_t i = start; i != end; i++)
		{
			auto ss = s1 + nums[i];
			s1 = s2;
			s2 = max(s2, ss);
		}
		return s2;
	}
};

void test0213_rob()
{
	int nn;
	vector<int> nums;
	Solution0213 sol;

	nums.assign({ 2, 3, 2 });
	nn = sol.rob(nums);
	assert(nn == 3);

	nums.assign({ 1, 2, 3, 1 });
	nn = sol.rob(nums);
	assert(nn == 4);

	nums.assign({ 2, 1, 1, 3 });
	nn = sol.rob(nums);
	assert(nn == 4);

	nums.assign({ 2, 1, 3, 1, 3 });
	nn = sol.rob(nums);
	assert(nn == 6);

	nums.assign({ 6, 3, 10, 8, 2, 10, 3, 5, 10, 5, 3 });
	nn = sol.rob(nums);
	assert(nn == 36);

	nums.assign({ 1, 1, 3, 6, 7, 10, 7, 1, 8, 5, 9, 1, 4, 4, 3 });
	nn = sol.rob(nums);
	assert(nn == 41);

	nums.assign({ 2, 2, 4, 3, 2, 5 });
	nn = sol.rob(nums);
	assert(nn == 10);
}