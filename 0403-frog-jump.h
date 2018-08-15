#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0403 {
public:
	bool canCross(vector<int>& stones) {
		unordered_map<int, unordered_set<int>> steps;

		const unordered_set<int> empty;
		steps.emplace(0, empty);
		steps.begin()->second.emplace(0);

		for (int ii = 1; ii < (int)stones.size(); ++ii)
		{
			const int stone = stones[ii];
			unordered_set<int> curr;

			auto istone = steps.begin();
			while (istone != steps.end())
			{
				auto& dist = istone->second;
				auto idist = dist.begin();
				while (idist != dist.end())
				{
					const int next = istone->first + *idist;
					if (next >= stone - 1 && next <= stone + 1)
					{
						curr.emplace(stone - istone->first);
					}
					if (next < stone)
						idist = dist.erase(idist);
					else
						idist++;
				}

				if (dist.empty())
					istone = steps.erase(istone);
				else
					istone++;
			}

			if (!curr.empty())
				steps.emplace(stone, curr);
			if (steps.empty())
				return false;
		}

		auto istone = steps.find(stones.back());
		return istone != steps.end();
	}
};
