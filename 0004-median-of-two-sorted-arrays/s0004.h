#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0004 {
public:
	double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
		size_t beg1 = 0, end1 = nums1.size();
		size_t beg2 = 0, end2 = nums2.size();

		size_t nn = (end1 + end2 - 1) / 2;

		while (beg1 < end1 && beg2 < end2 && nn > 1)
		{
			const size_t skip1 = min(nn / 2, end1 - beg1);
			const size_t skip2 = min(nn / 2, end2 - beg2);
			size_t last1 = beg1 + skip1 - 1;
			size_t last2 = beg2 + skip2 - 1;

			if (nums1[last1] < nums2[last2])
			{
				nn -= skip1;
				beg1 += skip1;
			}
			else
			{
				nn -= skip2;
				beg2 += skip2;
			}
		}

		if (nn)
		{
			if (beg1 == end1)
				beg2 += nn;
			else if (beg2 == end2)
				beg1 += nn;
			else
			{
				//	assert(nn == 1);
				if (nums1[beg1] < nums2[beg2])
				{
					++beg1;
				}
				else
					++beg2;
			}
		}

		bool odd = ((end1 + end2) & 1) != 0;
		if (beg1 == end1)
		{
			return odd ? nums2[beg2] : (nums2[beg2] + nums2[beg2 + 1]) * 0.5;
		}
		else if (beg2 == end2)
		{
			return odd ? nums1[beg1] : (nums1[beg1] + nums1[beg1 + 1]) * 0.5;
		}
		else if (odd)
		{
			return std::min(nums1[beg1], nums2[beg2]);
		}

		double m1 = nums1[beg1++];
		double m2 = nums2[beg2++];
		if (beg1 < end1 && nums1[beg1] < m2)
			m2 = nums1[beg1];
		else if (beg2 < end2 && nums2[beg2] < m1)
			m1 = nums2[beg2];
		return (m1 + m2) * 0.5;
	}
};

void test_speed_findMedianSortedArrays(size_t size, size_t repeat)
{
	Solution0004 sol;
	vector<int> nums1, nums2;
	nums1.resize(size);
	nums2.resize(size);

	srand(254856925);
	for (size_t ii = 0; ii < nums1.size(); ii++)
	{
		nums1[ii] = rand();
		nums2[ii] = rand();
	}
	std::sort(nums1.begin(), nums1.end());
	std::sort(nums2.begin(), nums2.end());

	double median = 0;
	for (size_t nn = 0; nn < repeat; ++nn)
	{
		median += sol.findMedianSortedArrays(nums2, nums1);
	}
	printf("%g\n", median);
}

void test_findMedianSortedArrays()
{
	Solution0004 sol;
	double median = 0;
	vector<int> nums1, nums2, nums_empty;

	nums1.clear();
	nums1.push_back(1);
	nums1.push_back(3);
	nums2.clear();
	nums2.push_back(2);
	median = sol.findMedianSortedArrays(nums1, nums2);
	assert(median == 2);

	nums1.clear();
	nums1.push_back(1);
	nums1.push_back(2);
	nums2.clear();
	nums2.push_back(3);
	nums2.push_back(4);
	median = sol.findMedianSortedArrays(nums1, nums2);
	assert(median == 2.5);

	nums1.clear();
	nums1.push_back(1);
	nums1.push_back(2);
	nums2.clear();
	nums2.push_back(1);
	nums2.push_back(2);
	nums2.push_back(3);
	median = sol.findMedianSortedArrays(nums1, nums2);
	assert(median == 2);

	nums1.clear();
	nums1.push_back(1);
	nums1.push_back(3);
	nums2.clear();
	nums2.push_back(2);
	nums2.push_back(4);
	nums2.push_back(5);
	median = sol.findMedianSortedArrays(nums1, nums2);
	assert(median == 3);

	nums1.clear();
	nums1.push_back(1);
	nums1.push_back(2);
	nums2.clear();
	nums2.push_back(1);
	nums2.push_back(2);
	median = sol.findMedianSortedArrays(nums1, nums2);
	assert(median == 1.5);

	nums1.clear();
	nums1.push_back(1);
	nums1.push_back(2);
	nums2.clear();
	nums2.push_back(-1);
	nums2.push_back(3);
	median = sol.findMedianSortedArrays(nums1, nums2);
	assert(median == 1.5);

	nums1.clear();
	nums1.push_back(1);
	nums2.clear();
	nums2.push_back(2);
	nums2.push_back(3);
	nums2.push_back(4);
	nums2.push_back(5);
	nums2.push_back(6);
	nums2.push_back(7);
	nums2.push_back(8);
	nums2.push_back(9);
	median = sol.findMedianSortedArrays(nums1, nums2);
	assert(median == 5);

#ifdef _DEBUG
	const size_t repeat = 1;
#else
	const size_t repeat = 0xFFFFFFFF;
#endif // 
	test_speed_findMedianSortedArrays(1000000, repeat);
}