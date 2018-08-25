#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0037 {
public:
	void solveSudoku(vector<vector<char>>& board) {
		bool rowUsed[81] = { false }, colUsed[81] = { false }, subUsed[81] = { false };
		for (size_t row = 0; row < 9; row++)
		{
			for (size_t col = 0; col < 9; col++)
			{
				if (board[row][col] != '.')
				{
					const size_t sub = (row / 3) * 3 + (col / 3);
					const int n = board[row][col] - '1';
					rowUsed[row * 9 + n] = true;
					colUsed[col * 9 + n] = true;
					subUsed[sub * 9 + n] = true;
				}
			}
		}

		solve(board, 0, 0, rowUsed, colUsed, subUsed);
	}

	bool solve(vector<vector<char>>& board, size_t row, size_t col, bool* rowUsed, bool* colUsed, bool* subUsed) {
		while (board[row][col] != '.')
		{
			++col;
			if (col == 9)
			{
				++row;
				col = 0;
				if (row == 9)
					return true;
			}
		}

		const size_t sub = (row / 3) * 3 + (col / 3);
		auto rset = rowUsed + row * 9;
		auto cset = colUsed + col * 9;
		auto sset = subUsed + sub * 9;
		for (int n = 0; n < 9; n++)
		{
			if (rset[n] || cset[n] || sset[n])
				continue;

			board[row][col] = '1' + n;
			rset[n] = true;
			cset[n] = true;
			sset[n] = true;
			if (solve(board, row, col, rowUsed, colUsed, subUsed))
				return true;
			board[row][col] = '.';
			rset[n] = false;
			cset[n] = false;
			sset[n] = false;
		}

		return false;
	}
};

void test0037_solveSudoku()
{
	Solution0037 sol;
	vector<vector<char>> board;

	board.resize(9);
	board[0].assign({ '5', '3', '.', '.', '7', '.', '.', '.', '.' });
	board[1].assign({ '6', '.', '.', '1', '9', '5', '.', '.', '.' });
	board[2].assign({ '.', '9', '8', '.', '.', '.', '.', '6', '.' });
	board[3].assign({ '8', '.', '.', '.', '6', '.', '.', '.', '3' });
	board[4].assign({ '4', '.', '.', '8', '.', '3', '.', '.', '1' });
	board[5].assign({ '7', '.', '.', '.', '2', '.', '.', '.', '6' });
	board[6].assign({ '.', '6', '.', '.', '.', '.', '2', '8', '.' });
	board[7].assign({ '.', '.', '.', '4', '1', '9', '.', '.', '5' });
	board[8].assign({ '.', '.', '.', '.', '8', '.', '.', '7', '9' });
	sol.solveSudoku(board);
}