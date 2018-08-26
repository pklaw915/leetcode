#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0198 {
public:
	int rob(vector<int>& nums) {
		int s1 = 0, s2 = 0;
		for (auto iter = nums.begin(); iter != nums.end(); iter++)
		{
			auto ss = s1 + *iter;
			s1 = s2;
			s2 = max(s2, ss);
		}
		return s2;
	}
};