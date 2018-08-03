#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <unordered_set>
using namespace std;

class Solution0136 {
public:
	int singleNumber(vector<int>& nums) {
		unordered_set<int> s;
		for (auto iter = nums.begin(); iter != nums.end(); iter++)
		{
			if (s.count(*iter))
				s.erase(*iter);
			else
				s.emplace(*iter);
		}
		return *s.begin();
		/*
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
		*/
	}
};

void test0136_singleNumber()
{
	Solution0136 sol;
	vector<int> nums;
	int nn;

	nums.clear();
	nums.push_back(2);
	nums.push_back(1);
	nums.push_back(3);
	nums.push_back(3);
	nums.push_back(2);
	nn = sol.singleNumber(nums);
	assert(nn == 1);
}