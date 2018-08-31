#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0085 {
public:
	int maximalRectangle(vector<vector<char>>& matrix) {
		if (matrix.empty())
			return 0;
		const size_t cols = matrix[0].size();
		if (cols == 0)
			return 0;

		int maximal = 0;
		vector<int> heights1(matrix.size(), 0);
		vector<int> heights2(matrix.size(), 0);

		for (size_t c = 0; c < cols; c++)
		{
			// heights1 and heights2 has the same values
			int changed = prepareHeights(matrix, c, heights2);
			if (changed == 0)
				continue;
			if (changed & 2)	// some '0'
				maximal = max(maximal, largestRectangleArea(heights1));
			heights1 = heights2;
		}
		maximal = max(maximal, largestRectangleArea(heights1));

		return maximal;
	}

	int prepareHeights(const vector<vector<char>>& matrix, size_t c, vector<int>& heights) {
		bool bInc = false, bDec = false;
		for (size_t r = 0; r < matrix.size(); r++)
		{
			const auto& row = matrix[r];
			if (row[c] == '0')
			{
				if (heights[r] > 0)
					bDec = true;
				heights[r] = 0;
			}
			else
			{
				bInc = true;
				heights[r]++;
			}
		}
		return (bInc ? 1 : 0) + (bDec ? 2 : 0);
	}

	int largestRectangleArea(vector<int>& heights) {
		int size = 0, largest = 0;
		vector<int> indices(heights.size());
		for (int n = 0; n < (int)heights.size(); n++)
		{
			if (heights[n] <= 0)
			{
				largest = max(largest, largestArea(heights, indices, 0, size, n));
				size = 0;
				continue;
			}

			auto iter = lower_bound(heights.begin(), heights.begin() + size, heights[n]);
			auto last = (int)distance(heights.begin(), iter);
			largest = max(largest, largestArea(heights, indices, last, size, n));
			if (last == size)
				indices[last] = n;
			heights[last] = heights[n];
			size = last + 1;
		}

		largest = max(largest, largestArea(heights, indices, 0, size, (int)heights.size()));
		return largest;
	}

	int largestArea(const vector<int>& heights, const vector<int>& indices, int beg, int end, int right) {
		int largest = 0;
		for (int n = beg; n < end; n++)
		{
			int area = (right - indices[n]) * heights[n];
			if (largest < area)
				largest = area;
		}
		return largest;
	}
};

void test0085_maximalRectangle()
{
	int nn;
	Solution0085 sol;
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
	nn = sol.maximalRectangle(matrix);
	assert(nn == 6);

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
	nn = sol.maximalRectangle(matrix);
	assert(nn == 9);
}