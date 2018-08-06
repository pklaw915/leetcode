#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0052 {
public:
	int totalNQueens(int n) {
		this->n = n;
		this->v.resize(n);
		return solve(0);
	}

	int solve(int r)
	{
		if (r == this->n)
			return 1;

		int cnt = 0;
		for (int c = 0; c < this->n; c++)
		{
			if (valid(r, c))
			{
				this->v[r] = c;
				cnt += solve(r + 1);
			}
		}
		return cnt;
	}

	bool valid(int r, int c) const
	{
		int offset = 1;
		for (int k = r - 1; k >= 0; --k)
		{
			if (this->v[k] == c || this->v[k] - offset == c || this->v[k] + offset == c)
				return false;
			offset++;
		}
		return true;
	}

private:
	int						n;
	vector<int>				v;
};

void test0052_totalNQueens()
{
	Solution0052 sol;
	int n;

	n = sol.totalNQueens(1);
	assert(1 == n);

	n = sol.totalNQueens(2);
	assert(0 == n);

	n = sol.totalNQueens(3);
	assert(0 == n);

	n = sol.totalNQueens(4);
	assert(2 == n);

	n = sol.totalNQueens(8);
	assert(92 == n);
}