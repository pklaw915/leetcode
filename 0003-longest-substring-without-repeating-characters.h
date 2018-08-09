#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0003 {
public:
	int lengthOfLongestSubstring(string s) {
		const char* p = s.c_str();
		int len = 0;
		int fst = 0;
		unordered_map<char, int> map;
		for (int nn = 0; p[nn]; ++nn)
		{
			auto iter = map.find(p[nn]);
			if (iter != map.end())
			{
				if (len < (int)map.size())
					len = (int)map.size();

				const int nxt = iter->second + 1;
				while (fst < nxt)
					map.erase(p[fst++]);
			}
			map.emplace(p[nn], nn);
		}

		if (len < (int)map.size())
			len = (int)map.size();
		return len;
	}
};

void test0003_lengthOfLongestSubstring()
{
	Solution0003 sol;
	int n;

	n = sol.lengthOfLongestSubstring("aab");
	assert(n == 2);

	n = sol.lengthOfLongestSubstring("abcabcbb");
	assert(n == 3);

	n = sol.lengthOfLongestSubstring("bbbbb");
	assert(n == 1);

	n = sol.lengthOfLongestSubstring("pwwkew");
	assert(n == 3);

	n = sol.lengthOfLongestSubstring("abb");
	assert(n == 2);
}