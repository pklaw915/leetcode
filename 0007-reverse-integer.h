#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0007 {
	int reverse(int x) {
		if (x == INT_MIN || x == INT_MAX)
			return 0;
		bool minus = x < 0;
		if (minus)
			x = -x;

		const unsigned int M = minus ? 0x80000000 : 0x7FFFFFFF;
		const unsigned int d = M % 10;
		const unsigned int m[] = { M / 10, M / 10 - 1 };

		unsigned int n = 0;
		while (x != 0)
		{
			unsigned int a = x % 10;
			if (n > m[a > d ? 1 : 0])
				return 0;
			n = n * 10 + a;
			x /= 10;
		}

		return minus ? (-(int)n) : (int)n;
	}
};