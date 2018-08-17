#pragma once
#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0164 {
public:
	int maximumGap(vector<int>& nums) {
		if (nums.size() < 2)
			return 0;
		if (nums.size() == 2)
			return abs(nums[1] - nums[0]);

		int nMin = INT_MAX, nMax = INT_MIN;
		for (auto iter = nums.begin(); iter != nums.end(); iter++)
		{
			if (*iter < nMin)
				nMin = *iter;
			if (*iter > nMax)
				nMax = *iter;
		}
		if (nMin == nMax)
			return 0;

		const int minGap	= (int)ceil((double)(nMax - nMin) / (nums.size() - 1));
		const int binSize	= minGap + 1;
		const int numBins	= (nMax - nMin) / binSize + 1;

		vector<int> minBins(numBins, INT_MAX);
		vector<int> maxBins(numBins, INT_MIN);

		for (size_t i = 0; i < nums.size(); i++)
		{
			const int bin = (nums[i] - nMin) / binSize;
			if (nums[i] < minBins[bin])
				minBins[bin] = nums[i];
			if (nums[i] > maxBins[bin])
				maxBins[bin] = nums[i];
		}

		int maxGap = minGap;
		int nLast = -1;
		for (int i = 0; i < (int)minBins.size(); i++)
		{
			if (minBins[i] <= maxBins[i])
			{
				if (nLast >= 0)
				{
					const int gap = minBins[i] - maxBins[nLast];
					if (maxGap < gap)
						maxGap = gap;
				}
				nLast = i;
			}
		}

		return maxGap;
	}
};


void test0164_maximumGap()
{
	int nn;
	vector<int> nums;
	Solution0164 sol;

	nums.clear();
	nums.assign({3, 6, 9, 1});
	nn = sol.maximumGap(nums);
	assert(nn == 3);

	nums.clear();
	nums.assign({ 10 });
	nn = sol.maximumGap(nums);
	assert(nn == 0);
}