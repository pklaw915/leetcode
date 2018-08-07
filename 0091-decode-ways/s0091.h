#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0091 {
public:
	int numDecodings(string s) {
		const char* p = s.c_str();

		int c1 = 1, c2 = numDecodings(*p++);
		while (*p)
		{
			int c3 = c2 * numDecodings(*p) + c1 * numDecodings(*(p - 1), *p);
			c1 = c2;
			c2 = c3;
			++p;
		}
		return c2;
	}

	int numDecodings(char c) const
	{
		return c == '0' ? 0 : 1;
	}

	int numDecodings(char c1, char c2) const
	{
		if (c1 == '1')
			return 1;
		if (c1 == '2')
		{
			if (c2 <= '6')
				return 1;
		}
		return 0;
	}
};

#include "../0639-decode-ways-ii/s0639.h"
void test0091_numDecodings()
{
	int nn;
	Solution0091 sol;
	Solution0639 sol2;
	nn = sol.numDecodings("0");
	assert(nn == 0 && nn == sol2.numDecodings("0"));
	nn = sol.numDecodings("1");
	assert(nn == 1 && nn == sol2.numDecodings("1"));
	nn = sol.numDecodings("2839");
	assert(nn == 1 && nn == sol2.numDecodings("2839"));
	nn = sol.numDecodings("11");
	assert(nn == 2 && nn == sol2.numDecodings("11"));
	nn = sol.numDecodings("19");
	assert(nn == 2 && nn == sol2.numDecodings("19"));
	nn = sol.numDecodings("21");
	assert(nn == 2 && nn == sol2.numDecodings("21"));
	nn = sol.numDecodings("29");
	assert(nn == 1 && nn == sol2.numDecodings("29"));
	nn = sol.numDecodings("31");
	assert(nn == 1 && nn == sol2.numDecodings("31"));
	nn = sol.numDecodings("39");
	assert(nn == 1 && nn == sol2.numDecodings("39"));
	nn = sol.numDecodings("112");
	assert(nn == 3 && nn == sol2.numDecodings("112"));
	nn = sol.numDecodings("192");
	assert(nn == 2 && nn == sol2.numDecodings("192"));
	nn = sol.numDecodings("123456789123456789");
	assert(nn == 9 && nn == sol2.numDecodings("123456789123456789"));
}