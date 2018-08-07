#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std; 

class Solution0777 {
public:
	bool canTransform(string start, string end) {
		if (start.length() != end.length())
			return false;
		auto p1 = start.c_str();
		auto p2 = end.c_str();
		auto len = (int)start.length();

		return canMoveRight(p1, p2, len, 'R') && canMoveRight(p2, p1, len, 'L');
	}

	bool canMoveRight(const char* src, const char* dst, int length, char chMoved)
	{
		int posSrc = 0, posDst = 0;
		while (posDst < length)
		{
			int cntSepDst = 0;
			posDst = findMovedChar(dst, posDst, length, chMoved, cntSepDst);

			int cntSepSrc = 0;
			posSrc = findMovedChar(src, posSrc, min(posDst + 1, length), chMoved, cntSepSrc);

			if (posSrc > posDst || posDst == length && posSrc < length || cntSepSrc != cntSepDst)
				return false;

			++posSrc;
			++posDst;
		}

		return true;
	}

	int		findMovedChar(const char* p, int beg, int end, char chMoved, int& cntSepChars)
	{
		cntSepChars = 0;
		while (beg < end)
		{
			if (p[beg] == chMoved)
				return beg;
			if (p[beg] != 'X')
				++cntSepChars;
			++beg;
		}

		return end;
	}
};

void test0777_canTransform()
{
	Solution0777 sol;

	assert(sol.canTransform("RXXLRXRXL", "XRLXXRRLX"));
	assert(sol.canTransform("X", "X"));
	assert(!sol.canTransform("X", "R"));
	assert(!sol.canTransform("R", "X"));
	assert(!sol.canTransform("X", "L"));
	assert(!sol.canTransform("L", "X"));
	assert(!sol.canTransform("LX", "XL"));
	assert(sol.canTransform("XL", "LX"));
	assert(sol.canTransform("RX", "XR"));
	assert(!sol.canTransform("XR", "RX"));
	assert(!sol.canTransform("XXRXXLXXXX", "XXXXRXXLXX"));
	assert(sol.canTransform("RL", "RL"));

}