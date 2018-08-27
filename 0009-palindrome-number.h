class Solution0009 {
public:
	bool isPalindrome(int x) {
		if (x < 0)
			return false;
		if (x == 0)
			return true;

		int a[10];
		int n2 = 0;
		while (x)
		{
			a[n2++] = x % 10;
			x /= 10;
		}
		--n2;
		int n1 = 0;
		while (n1 < n2)
		{
			if (a[n1] != a[n2])
				return false;
			++n1;
			--n2;
		}
		return true;
	}
};