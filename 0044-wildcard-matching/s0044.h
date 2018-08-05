#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0044 {
public:
	bool isMatch(string s, string p) {
		const char* src = s.c_str();
		const char* ptn = p.c_str();

		const int length = (int)s.length();
		std::vector<bool> vMatch;
		vMatch.resize(length + 1);

		vMatch[0] = true;
		int minMatch = 0, maxMatch = 0;

		while (*ptn)
		{
			const char ch = *ptn++;
			int nextMinMatch = 1, nextMaxMatch = 0;
			for (int nn = maxMatch; nn >= minMatch; --nn)
			{
				if (!vMatch[nn])
					continue;
				vMatch[nn] = false;

				int nMin = 1, nMax = 0;
				switch (ch)
				{
				case '?':
					if (nn < length)
						nMin = nMax = nn + 1;
					break;

				case '*':
					nMin = nn;
					nMax = length;
					break;

				default:
					if (nn < length && src[nn] == ch)
					{
						nMin = nMax = nn + 1;
					}
					break;
				}

				if (nMin <= nMax)
				{
					if (nextMinMatch > nextMaxMatch)
					{
						nextMinMatch = nMin;
						nextMaxMatch = nMax;
					}
					else
					{
						if (nMin < nextMinMatch)
							nextMinMatch = nMin;
						if (nMax > nextMaxMatch)
							nextMaxMatch = nMax;
					}
					for (int kk = nMin; kk <= nMax; ++kk)
						vMatch[kk] = true;
				}
			}

			if (nextMinMatch > nextMaxMatch)
				return false;
			minMatch = nextMinMatch;
			maxMatch = nextMaxMatch;
		}

		return vMatch[length];
	}
};


void test0044_isMatch()
{
	bool b;
	string s, p;
	Solution0044 sol;

	b = sol.isMatch(s, p);
	assert(b);

	p = "*";
	b = sol.isMatch(s, p);
	assert(b);

	p = "?";
	b = sol.isMatch(s, p);
	assert(!b);

	s = "";
	p = "";
	b = sol.isMatch(s, p);
	assert(b);

	s = "";
	p = "*";
	b = sol.isMatch(s, p);
	assert(b);

	s = "";
	p = "?";
	b = sol.isMatch(s, p);
	assert(!b);

	s = "a";
	p = "?";
	b = sol.isMatch(s, p);
	assert(b);

	s = "a";
	p = "a";
	b = sol.isMatch(s, p);
	assert(b);

	s = "a";
	p = "a*";
	b = sol.isMatch(s, p);
	assert(b);


	s = "aa";
	p = "a";
	b = sol.isMatch(s, p);
	assert(!b);

	s = "aa";
	p = "*";
	b = sol.isMatch(s, p);
	assert(b);

	s = "aa";
	p = "a?";
	b = sol.isMatch(s, p);
	assert(b);

	s = "cb";
	p = "*a";
	b = sol.isMatch(s, p);
	assert(!b);

	s = "adceb";
	p = "a*b";
	b = sol.isMatch(s, p);
	assert(b);

	s = "acdcb";
	p = "a*c?b";
	b = sol.isMatch(s, p);
	assert(!b);

	s = "ab";
	p = "*";
	b = sol.isMatch(s, p);
	assert(b);

	s = "aab";
	p = "c*a*b";
	b = sol.isMatch(s, p);
	assert(!b);

	s = "mississippi";
	p = "mis*is*p*?";
	b = sol.isMatch(s, p);
	assert(b);
}
