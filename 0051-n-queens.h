#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0051 {
public:
	vector<vector<string>> solveNQueens(int n) {
		this->n = n;
		this->m.clear();
		this->v.resize(n);
		solve(0);
		return this->m;
	}

	void solve(int r)
	{
		if (r == this->n)
		{
			output();
			return;
		}
		for (int c = 0; c < this->n; c++)
		{
			if (valid(r, c))
			{
				this->v[r] = c;
				solve(r + 1);
			}
		}
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

	void output()
	{
		vector<string> vs;
		for (int r = 0; r < this->n; ++r)
		{
			vs.push_back(output(this->v[r]));
		}
		this->m.push_back(vs);
	}

	string output(int c) const
	{
		string str;
		int k = c;
		while (k--)
			str.push_back('.');
		str.push_back('Q');
		k = this->n - c - 1;
		while (k--)
			str.push_back('.');
		return str;
	}

private:
	int						n;
	vector<int>				v;
	vector<vector<string>>	m;
};

void test0051_solveNQueens()
{
	Solution0051 sol;
	vector<vector<string>> v;

	v = sol.solveNQueens(1);
	assert(1 == v.size());

	v = sol.solveNQueens(2);
	assert(0 == v.size());

	v = sol.solveNQueens(3);
	assert(0 == v.size());

	v = sol.solveNQueens(4);
	assert(2 == v.size());

	v = sol.solveNQueens(8);
	assert(92 == v.size());
}