#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
#include <unordered_map>
using namespace std;


#include "../utils/numeric.h"

class Solution0828 {
public:
	int uniqueLetterString(string S) {
		const char* const ps = S.c_str();
		const int length = (int)S.length();

		int preCnt = 0;
		unordered_map<char, pair<int, int>> preIndices;

		int count = 0;

		for (int idx = 0; idx < length; idx++)
		{
			auto iter = preIndices.find(ps[idx]);
			if (iter == preIndices.end())
			{
				pair<int, int> p = { -1, -1 };
				iter = preIndices.emplace(ps[idx], p).first;
			}
			pair<int, int>& preIdx = iter->second;

			auto num_of_0 = idx - 1 - preIdx.second;
			auto num_of_1 = preIdx.second - preIdx.first;
			preCnt += num_of_0 - num_of_1;
			++preCnt;

			preIdx.first = preIdx.second;
			preIdx.second = idx;

			count = numeric_modulo_op<1000000007>::add(count, preCnt);
		}

		return count;
	}
};


void test0828_uniqueLetterString()
{
	Solution0828 sol;
	int nn;

	nn = sol.uniqueLetterString("");
	assert(nn == 0);
	nn = sol.uniqueLetterString("A");
	assert(nn == 1);
	nn = sol.uniqueLetterString("AA");
	assert(nn == 2);
	nn = sol.uniqueLetterString("AAA");
	assert(nn == 3);
	nn = sol.uniqueLetterString("ABC");
	assert(nn == 10);
	nn = sol.uniqueLetterString("ABA");
	assert(nn == 8);
	nn = sol.uniqueLetterString("AAABBB");
	assert(nn == 12);
	nn = sol.uniqueLetterString("AAABBBAAA");
	assert(nn == 21);
}