#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0001 {
public:
	vector<int> twoSum(vector<int>& nums, int target) {
		vector<int> ret;
		unordered_map<int, int> m;
		for (int i = 0; i < (int)nums.size(); ++i)
		{
			auto iter = m.find(nums[i]);
			if (iter != m.end())
			{
				ret.push_back(iter->second);
				ret.push_back(i);
				return ret;
			}
			m.emplace(target - nums[i], i);
		}
		return ret;
	}
};

void test_twoSum()
{
	Solution0001 sol;
	vector<int> nums;
	vector<int> ret;

	nums.clear();
	nums.push_back(2); nums.push_back(11); nums.push_back(15); nums.push_back(7);
	ret = sol.twoSum(nums, 9);
}