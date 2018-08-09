#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0088 {
public:
	void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
		int k = m + n;
		--m;
		while (n-- > 0)
		{
			int n2 = nums2[n];
			while (m >= 0 && nums1[m] > n2)
				nums1[--k] = nums1[m--];
			nums1[--k] = n2;
		}
	}
};

void test0088_merge()
{
	Solution0088 sol;
	vector<int> nums1, nums2;
	nums1.resize(10);
	nums2.resize(10);

	sol.merge(nums1, 0, nums2, 0);

	nums1[0] = 100;
	nums1[1] = 101;
	sol.merge(nums1, 2, nums2, 0);

	
	nums2[0] = 100;
	nums2[1] = 101;
	sol.merge(nums1, 0, nums2, 2);
	sol.merge(nums1, 2, nums2, 2);

	nums1[0] = 1;
	nums1[1] = 2;
	nums1[2] = 3;
	nums2[0] = 2;
	nums2[1] = 5;
	nums2[2] = 6;
	sol.merge(nums1, 3, nums2, 3);

	nums1[0] = 100;
	nums1[1] = 101;
	nums2[0] = 102;
	nums2[1] = 103;
	sol.merge(nums1, 2, nums2, 2);

	nums1[0] = 102;
	nums1[1] = 103;
	nums2[0] = 100;
	nums2[1] = 101;
	sol.merge(nums1, 2, nums2, 2);

	nums1[0] = 100;
	nums1[1] = 101;
	nums2[0] = 99;
	nums2[1] = 103;
	sol.merge(nums1, 2, nums2, 2);

	nums1[0] = 99;
	nums1[1] = 103;
	nums2[0] = 100;
	nums2[1] = 101;
	sol.merge(nums1, 2, nums2, 2);
}