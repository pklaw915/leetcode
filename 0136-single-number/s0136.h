#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0136 {
public:
	int singleNumber(vector<int>& nums) {
		auto beg = nums.begin();
		auto end = nums.end();
		while (distance(beg, end) > 1)
		{
			int v = max(max(*beg, *(beg + 1)), *(beg + 2));
			auto iter = partition(beg, end, [v](int n) {return n < v; });
			if ((distance(beg, iter) & 1) == 0)
				beg = iter;
			else
				end = iter;
		}

		return *beg;
	}
};

void test_singleNumber()
{
	Solution0136 sol;
	vector<int> nums;
	int nn;

	nn = sol.singleNumber(nums);
	assert(nn == 1);
}