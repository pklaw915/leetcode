class Solution0006 {
public:
	string convert(string s, int numRows) {
		const char* ps = s.c_str();
		const int length = (int)s.length();
		if (numRows <= 1 || numRows >= length)
			return s;

		int count = 0;
		char* pd = new char[length + 1];
		pd[length] = '\0';

		for (int row = 0; row < numRows; row++)
		{
			int last = -1;
			int nn = 0;
			while (nn < length + row)
			{
				const int n1 = nn - row;
				if (n1 >= 0 && n1 != last)
				{
					last = n1;
					pd[count++] = ps[n1];
				}
				const int n2 = nn + row;
				if (n2 < length && n2 != last)
				{
					last = n2;
					pd[count++] = ps[n2];
				}
				nn += (numRows - 1) * 2;
			}
		}

		string str = pd;
		delete[] pd;

		return str;
	}
};

void test0006_convert()
{
	string s;
	Solution0006 sol;

	s = sol.convert("ABCD", 3);
	assert(s == "ABDC");

	s = sol.convert("PAYPALISHIRING", 3);
	assert(s == "PAHNAPLSIIGYIR");

	s = sol.convert("PAYPALISHIRING", 4);
	assert(s == "PINALSIGYAHRPI");
}