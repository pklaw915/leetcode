#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0030 {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> ret;
		if (s.empty() || words.empty() || words[0].empty())
			return ret;

		vector<int> times;
		unordered_map<int, unordered_set<int>> map;
		if (!prepare(s, words, times, map))
			return ret;
		const int nWords = (int)words.size();
		const int lenWord = (int)words[0].length();

		const int endPos = (int)s.length() - lenWord * (int)words.size() + 1;
		for (int pos = 0; pos < endPos; pos++)
		{
			auto iPos = map.find(pos);
			if (iPos == map.end())
				continue;

			const unordered_set<int>& set = iPos->second;
			for (auto iSet = set.begin(); iSet != set.end(); ++iSet)
			{
				if (match(map, lenWord, times, *iSet, pos, nWords))
				{
					ret.push_back(pos);
					break;
				}
			}

			map.erase(iPos);
		}

		return ret;
	}

	bool prepare(const string& s, vector<string>& words, vector<int>& times, unordered_map<int, unordered_set<int>>& map) const
	{
		const unordered_set<int> empty_set;
		const char* str = s.c_str();
		const int len = (int)s.length();
		const int len_word = (int)words[0].length();
		sort(words.begin(), words.end());
		for (auto iter = words.begin(); iter != words.end(); iter++)
		{
			if (iter != words.begin() && *iter == *(iter - 1))
			{
				times.back()++;
				continue;
			}

			vector<int> vPos;
			strstr(str, len, iter->c_str(), len_word, vPos);
			if (vPos.empty())
				return false;
			for (auto iPos = vPos.begin(); iPos != vPos.end(); iPos++)
			{
				auto pos = *iPos;
				auto pp = map.emplace(pos, empty_set);
				pp.first->second.insert((int)times.size());
			}
			times.push_back(1);
		}
		return !times.empty();
	}

	void strstr(const char* str, size_t len_str, const char* sub, size_t len_sub, vector<int>& pos) const
	{
		std::vector<int> vNext;
		{
			vNext.resize(len_sub + 1, INT_MAX);

			auto fnNext = [](const char* ps, int length, const vector<int>& vNext)
			{
				int k = length - 1;
				const char cLast = ps[k];
				while (k > 0)
				{
					int p = vNext[k];
					if (p < 0)
						p = 0;
					if (ps[p] == cLast)
						return p + 1;
					k = p;
				}
				return ps[0] == ps[length] ? -1 : 0;
			};

			vNext[0] = -1;
			int ii = 1;
			while (ii <= len_sub)
			{
				vNext[ii] = fnNext(sub, ii, vNext);
				ii++;
			}
		}

		int cur_str = 0;
		int cur_sub = 0;

		pos.clear();
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
			{
				pos.push_back((int)(lps - str));
			}

			int next = vNext[cur_sub];
			if (next < 0)
			{
				cur_sub = 0;
				++cur_str;
			}
			else
			{
				cur_str += (cur_sub - next);
				cur_sub = next;
			}
		}
	}

	bool match(const unordered_map<int, unordered_set<int>>& map, int len, vector<int>& times, int index, int pos, int rest) const
	{
		if (times[index] == 0)
			return false;
		if (rest == 1)
			return true;

		int next = pos + len;
		auto iPos = map.find(next);
		if (iPos == map.end())
			return false;

		bool bMatch = false;
		times[index]--;
		{
			const unordered_set<int>& set = iPos->second;
			for (auto iSet = set.begin(); iSet != set.end(); ++iSet)
			{
				if (match(map, len, times, *iSet, next, rest - 1))
				{
					bMatch = true;
					break;
				}
			}
		}
		times[index]++;

		return bMatch;
	}
};

// probably a faster solution somebody used on website
// but seems it's slower, need more testing cases
class Solution0030_2 {
public:
	vector<int> findSubstring(string s, vector<string>& words) {
		vector<int> ret;
		if (s.empty() || words.empty() || words[0].empty())
			return ret;

		unordered_map<string, int> map;
		for (auto iter = words.begin(); iter != words.end(); iter++)
		{
			auto iWord = map.find(*iter);
			if (iWord != map.end())
			{
				iWord->second++;
				continue;
			}
			map.emplace(*iter, 1);
		}

		const int lenWord = (int)words[0].length();
		const int endPos = (int)s.length() - lenWord * (int)words.size() + 1;
		for (int start = 0; start < endPos; start++)
		{
			unordered_map<string, int> seen;
			size_t k = 0;
			while (k < words.size())
			{
				string sub = s.substr(start + k * lenWord, lenWord);
				auto iter = map.find(sub);
				if (iter == map.end())
					break;
				auto iSeen = seen.emplace(sub, 1);
				if (!iSeen.second)
				{
					iSeen.first->second++;
					if (iSeen.first->second > iter->second)
						break;
				}
				k++;
			}
			if (k == words.size())
				ret.push_back(start);
		}

		return ret;
	}
};

void test0030_findSubstring()
{
	Solution0030_2 sol;
	vector<string> words;
	vector<int> subs;

	words.clear();
	words.push_back("foo");
	words.push_back("bar");
	subs = sol.findSubstring("barfoothefoobarman", words);
	assert(subs.size() == 2 && subs[0] == 0 && subs[1] == 9);

	words.clear();
	words.push_back("word");
	words.push_back("student");
	subs = sol.findSubstring("wordgoodstudentgoodword", words);
	assert(subs.size() == 0);

	words.clear();
	subs = sol.findSubstring("", words);
	assert(subs.size() == 0);


	words.clear();
	for (int ii = 0; ii <2000; ++ii)
	{
		words.push_back("a");
	}
	string s;
	s.resize(100000);
	for (int ii = 0; ii < s.size(); ii++)
		s[ii] = 'a';
	subs = sol.findSubstring(s, words);
	printf("%d\n", (int)subs.size());
	assert(subs.size() == s.length() - words.size() + 1);
}


