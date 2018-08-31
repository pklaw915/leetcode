#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0221 {
public:
	int maximalSquare(vector<vector<char>>& matrix) {
		if (matrix.empty())
			return 0;

		const size_t rows = matrix.size();
		const size_t cols = matrix[0].size();

		int maximal = 0;
		vector<int> widths(cols);
		for (size_t r = 0; r < rows; r++)
		{
			const vector<char>& row = matrix[r];

			int prev = 0;
			for (size_t c = 0; c < cols; c++)
			{
				int n = 0;
				if (row[c] == '1')
				{
					if (c > 0)
					{
						n = min(widths[c - 1], widths[c]);
						n = min(n, prev);
					}
					n += 1;
					maximal = max(maximal, n);
				}
				prev = widths[c];
				widths[c] = n;
			}
		}
		return maximal * maximal;
	}
};

void test0221_maximalSquare()
{
	int nn;
	Solution0221 sol;
	vector<vector<char>> matrix;

	char mat1[][5] = {
		{ '1', '0', '1', '0', '0' },
		{ '1', '0', '1', '1', '1' },
		{ '1', '1', '1', '1', '1' },
		{ '1', '0', '0', '1', '0' },
	};
	matrix.resize(_countof(mat1));
	for (size_t ii = 0; ii < matrix.size(); ii++)
	{
		auto beg = mat1[ii];
		auto end = mat1[ii] + _countof(mat1[ii]);
		matrix[ii].assign(beg, end);
	}
	nn = sol.maximalSquare(matrix);
	assert(nn == 4);

	char mat2[][5] = {
		{ '0','1','1','0','1' },
		{ '1','1','0','1','0' },
		{ '0','1','1','1','0' },
		{ '1','1','1','1','0' },
		{ '1','1','1','1','1' },
		{ '0','0','0','0','0' },
	};
	matrix.resize(_countof(mat2));
	for (size_t ii = 0; ii < matrix.size(); ii++)
	{
		auto beg = mat2[ii];
		auto end = mat2[ii] + _countof(mat2[ii]);
		matrix[ii].assign(beg, end);
	}
	nn = sol.maximalSquare(matrix);
	assert(nn == 9);

	matrix.resize(5);
	matrix[0].assign({ '1', '1', '1', '1', '1', '1', '1', '1' });
	matrix[1].assign({ '1', '1', '1', '1', '1', '1', '1', '0' });
	matrix[2].assign({ '1', '1', '1', '1', '1', '1', '1', '0' });
	matrix[3].assign({ '1', '1', '1', '1', '1', '0', '0', '0' });
	matrix[4].assign({ '0', '1', '1', '1', '1', '0', '0', '0' });
	nn = sol.maximalSquare(matrix);
	assert(nn == 16);
}