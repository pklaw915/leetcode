#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0224 {
public:
	int calculate(string s) {
		const char* ps = s.c_str();
		string word;
		return eval(ps, word);
	}

private:
	int eval(const char* &ps, string& word) const
	{
		int val = 0, nn;
		bool add = true;
		while (*ps)
		{
			ps = next(ps, word);
			if (word.empty())
				break;
			switch (word[0])
			{
			case '+':
				add = true;
				break;

			case '-':
				add = false;
				break;

			case '(':
				nn = eval(ps, word);
				if (add)
					val += nn;
				else
					val -= nn;
				break;

			case ')':
				return val;

			default:
				nn = ::atoi(word.c_str());
				if (add)
					val += nn;
				else
					val -= nn;
			}
		}
		return val;
	}

	const char* next(const char* ps, string& word) const
	{
		while (*ps == ' ')
			++ps;

		switch (*ps)
		{
		case '\0':
			word.clear();
			break;

		case '+':
		case '-':
		case '(':
		case ')':
			word = *ps;
			++ps;
			break;

		default:
			{
				const char* p = ps;
				do
				{
					++p;
				} while (*p != ' ' && *p != '+' && *p != '-' && *p != '(' && *p != ')'&& *p != '\0');
				word.assign(ps, p);
				ps = p;
			}
		}

		return ps;
	}
};

void test0224_calculate()
{
	int nn;
	Solution0224 sol;

	nn = sol.calculate("1 + 1");
	assert(nn == 2);

	nn = sol.calculate(" 2-1 + 2");
	assert(nn == 3);

	nn = sol.calculate(" (2-1) + 2");
	assert(nn == 3);

	nn = sol.calculate(" (2-1) - (2 - 5)");
	assert(nn == 4);

	nn = sol.calculate("(1+(4+5+2)-3)+(6+8)");
	assert(nn == 23);
}