#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0214 {
public:
	string shortestPalindrome(string s) {
		int length = findBegPalindrome(s);
		if (length == s.length())
			return s;

		string ret;
		ret.assign(s.rbegin(), s.rbegin() + s.length() - length);
		ret += s;
		return ret;
	}

	int findBegPalindrome(const string& s)
	{
		const char* ps = s.c_str();
		int left = 0;
		int length = (int)s.length();

		std::vector<int> vNext;
		vNext.reserve(length / 2);

		while (length > 1)
		{
			int right = length - 1 - left;
			while (left < right)
			{
				if (ps[left] != ps[right])
					break;
				++left;
				--right;
			}
			if (left >= right)
				return length;

			// use KMP
			int next = KMPNext(ps, left, vNext);
			if (next < 0)
			{
				length -= left + 1;
				left = 0;
			}
			else
			{
				length -= (left - next);
				left = next;
			}
		}
		return length;
	}

	int KMPNext(const char* ps, int length, std::vector<int>& vNext)
	{
		if (length >= vNext.size())
		{
			int ii = (int)vNext.size();
			vNext.resize(length + 1, INT_MAX);

			auto fnNext = [ps, &vNext](int length)
			{
				int k = length - 1;
				const char cLast = ps[k];
				while (true)
				{
					const int p = vNext[k];
					if (p < 0)
					{
						if (k > 0 && ps[0] == cLast)
							return 1;
						break;
					}
					if (ps[p] == cLast)
						return p + 1;
					k = p;
				}

				return ps[0] == ps[length] ? -1 : 0;
			};

			if (ii == 0)
			{
				vNext[0] = -1;
				++ii;
			}
			while (ii <= length)
			{
				vNext[ii] = fnNext(ii);
				ii++;
			}
		}

		return vNext[length];
	}
};

void test0214_shortestPalindrome()
{
	string str;
	Solution0214 sol;

	str = sol.shortestPalindrome("abcd");
	assert(strcmp(str.c_str(), "dcbabcd") == 0);

	str = sol.shortestPalindrome("aacecaaa");
	assert(strcmp(str.c_str(), "aaacecaaa") == 0);

	str = sol.shortestPalindrome("abcdba");
	assert(strcmp(str.c_str(), "abdcbabcdba") == 0);
}