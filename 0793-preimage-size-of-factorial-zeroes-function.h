#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0793 {
public:
	int preimageSizeFZF(int K) {
		static const int v[] = { 6, 31, 156, 781, 3906, 19531, 97656, 488281, 2441406, 12207031, 61035156, 305175781, 1525878906 };
		auto iter = upper_bound(v, v + sizeof(v) / sizeof(int), K);
		int n = (int)distance(v, iter);
		while (n >= 0)
		{
			const int p = v[n--];
			if ((K % p) == p - 1)
				return 0;
			K -= K / p;
		}

		return 5;
	}
};

void preimageSizeFZF_test(vector<int>& v, int N)
{
	int n = 5;
	int k = 1;
	while (k < N)
	{
		v.push_back(n++);
		if ((k % 5) == 0)
		{
			int p = k;
			do
			{
				v.push_back(n++);
				p /= 5;
			} while ((p % 5) == 0);
		}

		n += 5;
		++k;
	}
}

void test0793_preimageSizeFZF()
{
	Solution0793 sol;

	vector<int> vZeros;
	preimageSizeFZF_test(vZeros, 10000);

	int k = 0;
	for (size_t i = 0; i < vZeros.size(); i++)
	{
		while (k < vZeros[i])
		{
			assert( 5 == sol.preimageSizeFZF(k++) );
		}

		assert(0 == sol.preimageSizeFZF(k++));
	}
}