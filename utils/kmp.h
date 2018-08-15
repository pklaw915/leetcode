#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

#pragma once

int KMP_next_single(const char* ps, int length, const vector<int>& vNext)
{
	int k = length - 1;
	const char cLast = ps[k];

	while (k > 0)
	{
		const int p = vNext[k];
		if (p < 0)
			p = 0;
		if (ps[p] == cLast)
			return p + 1;
		k = p;
	}

	return ps[0] == ps[length] ? -1 : 0;
}

int KMP_next(const char* ps, int length, std::vector<int>& vNext)
{
	if (length >= vNext.size())
	{
		int ii = (int)vNext.size();
		vNext.resize(length + 1, INT_MAX);

		if (ii == 0)
		{
			vNext[0] = -1;
			++ii;
		}
		while (ii <= length)
		{
			vNext[ii] = KMP_next_single(ps, ii, vNext);
			ii++;
		}
	}

	assert(vNext[length] != INT_MAX);
	return vNext[length];
}

const char* KMP_strstr(const char* str, const char* sub)
{
	assert(str && sub);

	const auto len_str = strlen(str);
	const auto len_sub = strlen(sub);

	int cur_str = 0;
	int cur_sub = 0;
	std::vector<int> vNext;

	while (len_str - cur_str >= len_sub)
	{
		const char* lps = str + cur_str;

		while (cur_sub < len_sub)
		{
			if (lps[cur_sub] != sub[cur_sub])
				break;
			++cur_sub;
		}
		if (cur_sub == len_sub)
			return lps;

		int next = KMP_next(sub, cur_sub, vNext);
		if (next < 0)
		{
			cur_sub = 0;
			++cur_str;
		}
		else
		{
			assert(next < cur_sub);
			cur_str += (cur_sub - next);
			cur_sub = next;
		}
	}

	return nullptr;
}