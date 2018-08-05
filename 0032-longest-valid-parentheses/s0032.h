#include <algorithm>
#include <vector>
#include <stack>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0032 {
public:
	int longestValidParentheses(string s) {
		const char* p = s.c_str();

		int max = 0;
		stack<int> st;
		int match = 0;
		while (*p)
		{
			if (*p == ')')
			{
				if (!st.empty() && st.top() == 0)
				{
					st.pop();
					match += 2;
					if (!st.empty() && st.top() > 0)
					{
						match += st.top();
						st.pop();
					}
					if (max < match)
						max = match;
				}
				else
				{
					while (!st.empty())
						st.pop();
					match = 0;
				}
			}
			else
			{
				if (match)
				{
					st.push(match);
					match = 0;
				}
				st.push(0);
			}
			++p;
		}
		return max;
	}
};

void test0032_longestValidParentheses()
{
	int n;
	Solution0032 sol;

	n = sol.longestValidParentheses("(()");
	assert(n == 2);

	n = sol.longestValidParentheses(")()())");
	assert(n == 4);

	n = sol.longestValidParentheses("()(()");
	assert(n == 2);
}