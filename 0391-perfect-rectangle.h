#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0391 {
	vector<int> order;
public:
	bool isRectangleCover(vector<vector<int>>& rectangles) {
		order.resize(rectangles.size());
		for (int ii = 0; ii < (int)order.size(); ii++)
			order[ii] = ii;

		enum
		{
			RECT_Left,
			RECT_Bottom,
			RECT_Right,
			RECT_Top
		};

		int min_y = INT_MAX;
		for_each(rectangles.begin(), rectangles.end(), [&min_y](const vector<int>& rect)
		{
			if (min_y > rect[RECT_Bottom])
				min_y = rect[RECT_Bottom];
		});
		int min_x = 1, max_x = 0;

		auto beg = order.begin();
		while (beg != order.end())
		{
			int min_top = INT_MAX;
			auto end = partition(beg, order.end(), [&rectangles, min_y, &min_top](int n) {
				const vector<int>& rect = rectangles[n];
				if (rect[RECT_Bottom] == min_y)
				{
					if (min_top > rect[RECT_Top])
						min_top = rect[RECT_Top];
					return true;
				}
				return false;
			});
			if (beg == end)
				return false;
			sort(beg, end, [&rectangles](int n1, int n2) {
				const vector<int>& r1 = rectangles[n1];
				const vector<int>& r2 = rectangles[n2];
				return r1[RECT_Left] < r2[RECT_Left];
			});

			bool init = min_x <= max_x;
			if (!init)
				min_x = rectangles[*beg][RECT_Left];
			int x = min_x;
			for (auto iter = beg; iter != end; ++iter)
			{
				auto& rect = rectangles[*iter];
				if (rect[RECT_Left] != x)
					return false;
				x = rect[RECT_Right];

				if (rect[RECT_Top] > min_top)
					rect[RECT_Bottom] = min_top;
				else
					*iter = -1;
			}
			if (!init)
				max_x = x;
			if (x != max_x)
				return false;

			partition(beg, end, [](int n) {return n < 0; });
			while (beg != end && *beg < 0)
				++beg;
			min_y = min_top;
		}

		return true;
	}
};

void add_rectangle(vector<vector<int>>& rectangles, int x1, int y1, int x2, int y2)
{
	vector<int> rect;
	rect.push_back(x1);
	rect.push_back(y1);
	rect.push_back(x2);
	rect.push_back(y2);
	rectangles.push_back(rect);
}

void test0391_isRectangleCover()
{
#ifdef _DEBUG
	const int repeat = 1;
#else
	const int repeat = 100000000;
#endif // 
	Solution0391 sol;
	bool b;
	vector<vector<int>> rectangles;
	vector<int> order;

	rectangles.clear();
	add_rectangle(rectangles, 1, 1, 3, 3);
	add_rectangle(rectangles, 3, 1, 4, 2);
	add_rectangle(rectangles, 3, 2, 4, 4);
	add_rectangle(rectangles, 1, 3, 2, 4);
	add_rectangle(rectangles, 2, 3, 3, 4);
	for (size_t i = 0; i < repeat; i++)
	{
		b = sol.isRectangleCover(rectangles);
	}
	assert(b);

	rectangles.clear();
	add_rectangle(rectangles, 1, 1, 2, 3);
	add_rectangle(rectangles, 1, 3, 2, 4);
	add_rectangle(rectangles, 3, 1, 4, 2);
	add_rectangle(rectangles, 3, 2, 4, 4);
	for (size_t i = 0; i < repeat; i++)
	{
		b = sol.isRectangleCover(rectangles);
	}
	assert(!b);

	rectangles.clear();
	add_rectangle(rectangles, 1, 1, 3, 3);
	add_rectangle(rectangles, 3, 1, 4, 2);
	add_rectangle(rectangles, 1, 3, 2, 4);
	add_rectangle(rectangles, 3, 2, 4, 4);
	for (size_t i = 0; i < repeat; i++)
	{
		b = sol.isRectangleCover(rectangles);
	}
	assert(!b);

	rectangles.clear();
	add_rectangle(rectangles, 1, 1, 3, 3);
	add_rectangle(rectangles, 3, 1, 4, 2);
	add_rectangle(rectangles, 1, 3, 2, 4);
	add_rectangle(rectangles, 2, 2, 4, 4);
	for (size_t i = 0; i < repeat; i++)
	{
		b = sol.isRectangleCover(rectangles);
	}
	assert(!b);
}