#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0008 {
public:
	int myAtoi(string str) {
		const char* lpcsz = str.c_str();
		if (lpcsz == nullptr)
			return 0;
		while (true)
		{
			if (*lpcsz == '\0')
				return 0;
			if (*lpcsz != ' ')
				break;
			++lpcsz;
		}

		bool minus = false;
		if (*lpcsz == '-')
		{
			minus = true;
			++lpcsz;
		}
		else if (*lpcsz == '+')
			++lpcsz;

		const unsigned int M = minus ? 0x80000000 : 0x7FFFFFFF;
		const unsigned int d = M % 10;
		const unsigned int m[] = { M / 10, M / 10 - 1 };

		unsigned int n = 0;
		while (*lpcsz >= '0' && *lpcsz <= '9')
		{
			unsigned int a = (int)(*lpcsz - '0');
			if (n > m[a > d ? 1 : 0])
				return minus ? INT_MIN : INT_MAX;
			n = n * 10 + a;
			++lpcsz;
		}

		return minus ? (-(int)n) : (int)n;
	}
};



void test_atoi()
{
	Solution0008 sol;
	int nn;
	string str;
	str = "42";
	nn = sol.myAtoi(str);
	assert(nn == 42);

	str = "   -42";
	nn = sol.myAtoi(str);
	assert(nn == -42);

	str = "4193 with words";
	nn = sol.myAtoi(str);
	assert(nn == 4193);

	str = "words and 987";
	nn = sol.myAtoi(str);
	assert(nn == 0);

	str = "-91283472332";
	nn = sol.myAtoi(str);
	assert(nn == INT_MIN);

	str = "2147483648";
	nn = sol.myAtoi(str);
	assert(nn == INT_MAX);
}