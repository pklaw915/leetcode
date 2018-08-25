
#ifndef __UTIL_NUMERIC_OP__
#define __UTIL_NUMERIC_OP__

template<unsigned int NMAX>
struct numeric_modulo_op
{
	static int mod(int c)
	{
		if (c > NMAX)
			c %= NMAX;
		return  c;
	}

	static int add(int c1, int c2)
	{
		return mod(c1 + c2);
	}

	static int multiply(int c, int n)
	{
		if (n > 0 && c > INT_MAX / n)
		{
			int n1 = n / 2;
			int n2 = n - n1;
			return add(multiply(c, n1), multiply(c, n2));
		}

		return mod(c * n);
	}
};

#endif // __UTIL_NUMERIC_OP__