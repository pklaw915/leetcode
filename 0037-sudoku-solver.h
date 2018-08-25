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
		vector<unordered_set<char>> rowUsed(9), colUsed(9), subUsed(9);
		for (size_t row = 0; row < 9; row++)
		{
			for (size_t col = 0; col < 9; col++)
			{
				if (board[row][col] != '.')
				{
					const size_t sub = (row / 3) * 3 + (col / 3);
					rowUsed[row].insert(board[row][col]);
					colUsed[col].insert(board[row][col]);
					subUsed[sub].insert(board[row][col]);
				}
			}
		}

		solve(board, 0, 0, rowUsed, colUsed, subUsed);
	}

	bool solve(vector<vector<char>>& board, size_t row, size_t col, vector<unordered_set<char>>& rowUsed, vector<unordered_set<char>>& colUsed, vector<unordered_set<char>>& subUsed) {
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
		auto& rset = rowUsed[row];
		auto& cset = colUsed[col];
		auto& sset = subUsed[sub];
		for (char c = '1'; c <= '9'; c++)
		{
			if (rset.find(c) != rset.end() || cset.find(c) != cset.end() || sset.find(c) != sset.end())
				continue;

			board[row][col] = c;
			rset.insert(c);
			cset.insert(c);
			sset.insert(c);
			if (solve(board, row, col, rowUsed, colUsed, subUsed))
				return true;
			board[row][col] = '.';
			rset.erase(c);
			cset.erase(c);
			sset.erase(c);
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