#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0072 {
public:
	int minDistance(string word1, string word2) {
		const int length1 = (int)word1.length();
		const int length2 = (int)word2.length();
		if (length1 == 0 || length2 == 0)
			return length1 + length2;

		vector<int> dists(length1 + 1, 0);
		for (int n = 0; n < (int)dists.size(); n++)
			dists[n] = n;
		for (int L2 = 1; L2 <= length2; L2++)
		{
			const char chLast = word2[L2 - 1];

			int L1 = length1;
			while (L1 > 0)
			{
				size_t pos = word1.rfind(chLast, L1 - 1);
				if (pos == word1.npos)
					break;
				while (L1 > pos)
				{
					dists[L1] = min(min(dists[L1 - 1], dists[L1]) + 1, dists[pos] + (L1 - (int)pos - 1));
					L1--;
				}
			}
			do
			{
				if (L1 > 0)
					dists[L1] = min(dists[L1 - 1], dists[L1]);
				dists[L1] = min(dists[L1] + 1, max(L1, L2));
				if (L1 == 0)
					break;
				L1--;
			} while (true);
		}
		return dists[length1];
	}

	int minDistance2(string word1, string word2) {
		const char* ps1 = word1.c_str();
		const char* ps2 = word2.c_str();
		return minDistance(ps1, word1.size(), ps2, word2.size());
	}

	int minDistance(const char* ps1, size_t len1, const char* ps2, size_t len2)
	{
		if (len1 == 0 || len2 == 0)
			return (int)(len1 + len2);
		if (len1 == 1 || len2 == 1)
		{
			char ch = len1 == 1 ? *ps1 : *ps2;
			const char* ps = len1 == 1 ? ps2 : ps1;
			const size_t len = len1 == 1 ? len2 : len1;
			for (int nn = 0; nn < len; nn++)
			{
				if (ps[nn] == ch)
					return (int)len - 1;
			}
			return (int)max(len1, len2);
		}

		int d;
		int dist = (int)max(len1, len2);

		const char chLast = ps2[len2 - 1];
		const size_t left = min(len1, len2) / 2;
		for (size_t k = len1 - 1; k >= left; k--)
		{
			if (ps1[k] == chLast)
			{
				d = minDistance(ps1, k, ps2, len2 - 1) + (int)(len1 - k - 1);
				if (d < dist)
					dist = d;
				break;
			}
		}
		d = minDistance(ps1, len1, ps2, len2 - 1) + 1;
		if (d < dist)
			dist = d;
		d = minDistance(ps1, len1 - 1, ps2, len2 - 1) + 1;
		if (d < dist)
			dist = d;
		return dist;
	}
};

void test0072_minDistance()
{
	string word1, word2;
	Solution0072 sol;
	int nn;

	word1 = "horse";
	word2 = "ros";
	nn = sol.minDistance(word1, word2);
	assert(nn == 3);

	word1 = "intention";
	word2 = "execution";
	nn = sol.minDistance(word1, word2);
	assert(nn == 5);

	word1 = "mart";
	word2 = "karma";
	nn = sol.minDistance(word1, word2);
	assert(nn == 3);

	word1 = "food";
	word2 = "money";
	nn = sol.minDistance(word1, word2);
	assert(nn == 4);
}