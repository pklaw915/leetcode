#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0005 {
public:
	string longestPalindrome(string s) {
		const char* ps = s.c_str();
		const int len = (int)s.length();
		if (len == 0)
			return "";

		int max = 1;
		pair<int, int> mlr = { 0, 0 };

		int nn;
		pair<int, int> lr;

		for (int k = 0; k < len - max / 2; k++)
		{
			lr.first = k;
			lr.second = k;
			nn = sizeOfPalindrome(ps, len, lr);
			if (nn > max)
			{
				max = nn;
				mlr = lr;
			}

			lr.first = k;
			lr.second = k + 1;
			nn = sizeOfPalindrome(ps, len, lr);
			if (nn > max)
			{
				max = nn;
				mlr = lr;
			}
		}

		string ret;
		ret.assign(ps + mlr.first, ps + mlr.first + max);
		return ret;
	}

	int sizeOfPalindrome(const char* ps, int length, pair<int, int>& lr) const
	{
		assert(lr.first == lr.second || lr.first + 1 == lr.second);
		const int left = max(0, lr.first - (length - 1 - lr.second));
		do
		{
			if (ps[lr.first] != ps[lr.second])
				break;
			--lr.first;
			++lr.second;
		} while (lr.first >= left);

		lr.first++;
		lr.second--;
		return lr.second - lr.first + 1;
	}
};

void test0005_longestPalindrome()
{
	string str;
	Solution0005 sol;

	str = sol.longestPalindrome("babad");
	assert(str == "bab");

	str = sol.longestPalindrome("cbbd");
	assert(str == "bb");

	str = sol.longestPalindrome("c");
	assert(str == "c");

	str = sol.longestPalindrome("ccc");
	assert(str == "ccc");
}