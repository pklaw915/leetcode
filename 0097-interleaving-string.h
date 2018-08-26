#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0097 {
public:
	bool isInterleave(string s1, string s2, string s3) {
		if (s1.length() + s2.length() != s3.length())
			return false;
		if (s1.length() < s2.length())
			swap(s1, s2);
		const char* const p1 = s1.c_str();
		const char* const p2 = s2.c_str();
		const char* const p3 = s3.c_str();

		int n1 = 0, n2 = 0, n3 = 0;
		vector<int> st(s3.length(), false);
		while (p3[n3])
		{
			if (st[n3] = p1[n1] == p3[n3])
			{
				n1++;
			}
			else if (p2[n2] == p3[n3])
			{
				n2++;
			}
			else
			{
				while (--n3 >= 0)
				{
					if (st[n3])
					{
						n1--;
						if (p2[n2] == p3[n3])
							break;
					}
					else
					{
						n2--;
					}
				}
				if (n3 < 0)
					return false;
				n2++;
				st[n3] = false;
			}
			n3++;
		}

		return true;
	}
};


void test0097_isInterleave()
{
	bool b;
	Solution0097 sol;

	b = sol.isInterleave("aabcc", "dbbca", "aadbbcbcac");
	assert(b);

	b = sol.isInterleave("aabcc", "dbbca", "aadbbbaccc");
	assert(!b);
}