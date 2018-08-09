#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

#ifndef __SOLUTION_0639__
#define __SOLUTION_0639__
class Solution0639 {
public:
	int numDecodings(char c) const
	{
		switch (c)
		{
		case '*':
			return 9;
		case '0':
			return 0;
		}
		return 1;
	}

	int numDecodings(char c1, char c2) const
	{
		if (c1 == '0' || c1 > '2')
			return 0;
		if (c1 == '*')
		{
			if (c2 == '*')
				return 15;
			return 1 + (c2 < '7' ? 1 : 0);		// 1# or 2#
		}
		if (c2 == '*')
		{
			return c1 == '1' ? 9 : 6;
		}
		if (c1 == '2' && c2 > '6')
			return 0;
		return 1;
	}

	int add(int c1, int c2) const
	{
		const int NMAX = 1000000007;
		c1 += c2;
		if (c1 > NMAX)
			c1 -= NMAX;
		return  c1;
	}

	int multiply(int c, int n) const
	{
		const int NMAX = 1000000007;
		if (n > 0 && c > INT_MAX / n)
		{
			int n1 = n / 2;
			int n2 = n - n1;
			return add(multiply(c, n1), multiply(c, n2));
		}

		c *= n;
		if (c > NMAX)
			c %= NMAX;
		return c;
	}

	int numDecodings(string s) {
		const char* p = s.c_str();

		int c1 = 1, c2 = numDecodings(*p++);
		while (*p)
		{
			int c3 = add(multiply(c2, numDecodings(*p)), multiply(c1, numDecodings(*(p - 1), *p)));
			c1 = c2;
			c2 = c3;
			++p;
		}
		return c2;
	}
};

void test0639_numDecodings()
{
	int nn;
	Solution0639 sol;
	nn = sol.numDecodings("*");
	assert(nn == 9);
	nn = sol.numDecodings("2839");
	assert(nn == 1);
	nn = sol.numDecodings("1*");
	assert(nn == 18);
	nn = sol.numDecodings("2*");
	assert(nn == 15);
	nn = sol.numDecodings("3*");
	assert(nn == 9);
	nn = sol.numDecodings("**");
	assert(nn == 96);
	nn = sol.numDecodings("*1");
	assert(nn == 11);
	nn = sol.numDecodings("1*2");
	assert(nn == 20);
	nn = sol.numDecodings("2*3");
	assert(nn == 17);
	nn = sol.numDecodings("3*5");
	assert(nn == 11);
	nn = sol.numDecodings("3*7");
	assert(nn == 10);
	nn = sol.numDecodings("**9");
	assert(nn == 105);
	nn = sol.numDecodings("***");
	assert(nn == 999);
	nn = sol.numDecodings("*****************************");
	assert(nn == 226137644);
}
#endif // __SOLUTION_0639__