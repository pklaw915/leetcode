#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;


class Solution0233 {
public:
	int countDigitOne(int n) {
		if (n <= 0)
			return 0;
		int digits[11], remains[11];
		int size = 0;
		while (n)
		{
			digits[size++] = n % 10;
			n /= 10;
		}

		int remain = 0, factor = 1;
		for (size_t i = 0; i < size; i++)
		{
			remains[i] = remain;
			remain = digits[i] * factor + remain;
			factor *= 10;
		}

		return countDigitOne(digits, remains, size - 1);
	}

	int countDigitOne(const int* digits, const int* remains, int pos) const
	{
		static const int powOf10[] = { 1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000 };
		static const int digit1s[] = { 0, 1, 20, 300, 4000, 50000, 600000, 7000000, 80000000, 900000000 };
		while (pos >= 0 && digits[pos] == 0)
			--pos;
		if (pos < 0)
			return 0;
		if (pos == 0)
			return digits[0] == 0 ? 0 : 1;

		int cnt = digits[pos] * digit1s[pos];
		if (digits[pos] == 1)
		{
			cnt += remains[pos] + 1;
		}
		else
		{
			cnt += powOf10[pos];
		}

		return cnt + countDigitOne(digits, remains, pos - 1);
	}
};

int countDigitOne_bf(int n, const vector<int>& vDigitsOne)
{
	if (n == 0)
		return 0;
	if (n == 1)
		return 1;

	int cnt = vDigitsOne[n - 1];
	while (n)
	{
		if ((n % 10) == 1)
			cnt++;
		n /= 10;
	}

	return cnt;
}

void test0233_countDigitOne()
{
	int cnt;
	Solution0233 sol;

#ifdef _DEBUG
	const int repeat = 1;
#else
	const int repeat = 100;
#endif // _DEBUG
	const int N = 1000002;
	vector<int> vDigitsOne;
	vDigitsOne.resize(N);
	for (int i = 0; i < N; i++)
		vDigitsOne[i] = countDigitOne_bf(i, vDigitsOne);

	cnt = sol.countDigitOne(INT_MAX/2);

	for (int i = 0; i < N; i++)
	{
		cnt = 0;
		for (size_t r = 0; r < repeat; r++)
		{
			cnt += sol.countDigitOne(i);
		}
		if (cnt != vDigitsOne[i] * repeat)
		{
			assert(false);
			printf("failed: %d = %d, it should be %d\n", i, cnt / repeat, vDigitsOne[i]);
		}
	}
}