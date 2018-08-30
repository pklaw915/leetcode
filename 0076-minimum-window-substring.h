#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0076 {
public:
	string minWindow(string s, string t) {
		if (t.empty() || t.length() > s.length())
			return "";

		int nMax = 0;
		std::sort(t.begin(), t.end());
		if (!prepare(s, t, nMax))
			return "";

		auto fnCmpIdx = [](int i1, int i2)
		{
			return i1 > i2;
		};
		make_heap(indices.begin(), indices.end(), fnCmpIdx);

		int minBeg = indices.front();
		int minCnt = nMax - minBeg + 1;
		while (true)
		{
			int nMin = indices.front();
			pop_heap(indices.begin(), indices.end(), fnCmpIdx);
			auto iterMax = map_max.find(s[nMin]);
			if (iterMax != map_max.end())
				nMin = iterMax->second;
			auto pos = s.find(s[nMin], nMin + 1);
			if (pos == s.npos)
				break;
			if (iterMax != map_max.end())
				iterMax->second = (int)pos;

			indices.back() = (int)pos;
			push_heap(indices.begin(), indices.end(), fnCmpIdx);
			if (pos > nMax)
				nMax = (int)pos;
			const int cnt = nMax - indices.front() + 1;
			if (cnt < minCnt)
			{
				minBeg = indices.front();
				minCnt = cnt;
			}
		}

		return string(s.c_str() + minBeg, minCnt);
	}

	bool prepare(const string& s, const string& t, int& max)
	{
		max = 0;
		indices.resize(t.length());
		map_max.clear();

		for (size_t n = 0; n < t.length(); n++)
		{
			bool repeat = n > 0 && t[n] == t[n - 1];
			auto pos = s.find(t[n], repeat ? indices[n - 1] + 1 : 0);
			if (pos == s.npos)
				return false;

			if (pos > max)
				max = (int)pos;
			indices[n] = (int)pos;
			if (repeat)
			{
				auto pp = map_max.emplace(t[n], (int)pos);
				if (!pp.second)
					pp.first->second = (int)pos;
			}
		}

		return true;
	}

	vector<int>					indices;
	unordered_map<char, int>	map_max;
};

void test0076_minWindow()
{
	Solution0076 sol;
	string str;

	str = sol.minWindow("ADOBECODEBANC", "ABC");
	assert(str == "BANC");

	str = sol.minWindow("a", "aa");
	assert(str == "");

	str = sol.minWindow("abbbabbbbaba", "aa");
	assert(str == "aba");
}