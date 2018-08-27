#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0065 {
public:
	bool isNumber(string s) {
		const char* ps = s.c_str();
		while (*ps == ' ')
			++ps;
		if (*ps == '\0')
			return false;
		if (*ps == '0')
		{
			switch (*(ps + 1))
			{
			case 'b':
			case 'B':
			{
				vector<pair<char, char>> ranges;
				ranges.push_back(make_pair('0', '1'));
				return isInteger(ps + 2, ranges);
			}

			case 'x':
			case 'X':
			{
				vector<pair<char, char>> ranges;
				ranges.push_back(make_pair('0', '9'));
				ranges.push_back(make_pair('a', 'f'));
				ranges.push_back(make_pair('A', 'F'));
				return isInteger(ps + 2, ranges);
			}
			}
		}

		return isDecimal(ps);
	}

	bool isInteger(const char* ps, const vector<pair<char, char>>& ranges)
	{
		int len = 0;
		do
		{
			if (*ps == ' ' || *ps == '\0')
				break;
			bool b = false;
			for (auto iter = ranges.begin(); iter != ranges.end(); iter++)
			{
				if (*ps >= iter->first && *ps <= iter->second)
				{
					b = true;
					break;
				}
			}
			if (!b)
				return false;
			len++;
			ps++;
		} while (true);

		if (len == 0)
			return false;

		while (*ps != '\0')
		{
			if (*ps != ' ')
				return false;
			++ps;
		}

		return true;
	}

	bool isDecimal(const char* ps)
	{
		if (*ps == '-' || *ps == '+')
			++ps;

		int len = 0;
		bool bExp = false, bDot = false;
		do
		{
			if (*ps == ' ' || *ps == '\0')
				break;
			if (*ps == 'e' || *ps == 'E')
			{
				bExp = true;
				ps++;
				break;
			}
			if (*ps == '.')
			{
				if (bDot)
					return false;
				bDot = true;
			}
			else
			{
				if (*ps < '0' || *ps > '9')
					return false;
				len++;
			}
			ps++;
		} while (true);

		if (len == 0)
			return false;

		if (bExp)
		{
			if (*ps == '-' || *ps == '+')
				++ps;
			int len = 0;
			do
			{
				if (*ps == ' ' || *ps == '\0')
					break;
				if (*ps < '0' || *ps > '9')
					return false;
				len++;
				ps++;
			} while (true);
			if (len == 0)
				return false;
		}

		while (*ps != '\0')
		{
			if (*ps != ' ')
				return false;
			++ps;
		}

		return true;
	}
};

void test0065_isNumber()
{
	bool b;
	Solution0065 sol;

	b = sol.isNumber("0");
	assert(b);

	b = sol.isNumber("0x125Feee");
	assert(b);

	b = sol.isNumber(" 0.1");
	assert(b);

	b = sol.isNumber(" .1");
	assert(b);

	b = sol.isNumber("- 0.");
	assert(!b);

	b = sol.isNumber("abc");
	assert(!b);

	b = sol.isNumber("1 a");
	assert(!b);

	b = sol.isNumber("2e10 ");
	assert(b);

	b = sol.isNumber("O62");
	assert(!b);

	b = sol.isNumber("+.8");
	assert(b);

	b = sol.isNumber("+ 8");
	assert(!b);

	b = sol.isNumber(" 005047e+6");
	assert(b);
}