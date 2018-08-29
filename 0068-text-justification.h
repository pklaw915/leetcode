#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>
#include <assert.h>
#include <stdlib.h>
using namespace std;

class Solution0068 {
public:
	vector<string> fullJustify(vector<string>& words, int maxWidth) {
		vector<string> ret;
		size_t beg = 0;
		while (beg < words.size())
		{
			size_t len = 0, end = beg;
			while (end < words.size())
			{
				if (len + words[end].length() + end - beg > maxWidth)
					break;
				len += words[end].length();
				++end;
			}

			double totalSpaces = (double)maxWidth - len;
			string str = words[beg];
			for (size_t nn = beg + 1; nn < end; nn++)
			{
				int nSpaces = 1;
				if (end != words.size())
				{
					nSpaces = (int)ceil(totalSpaces / (end - nn));
					totalSpaces -= nSpaces;
				}
				string spaces(nSpaces, ' ');
				str = str + spaces + words[nn];
			}
			int nSpaces = maxWidth - (int)str.length();
			if (nSpaces > 0)
			{
				string spaces(nSpaces, ' ');
				str += spaces;
			}
			ret.push_back(str);

			beg = end;
		}
		return ret;
	}
};

void test0068_fullJustify()
{
	vector<string> words, result, compare;
	Solution0068 sol;

	words.assign({ "This", "is", "an", "example", "of", "text", "justification." });
	compare.assign({ "This    is    an", "example  of text", "justification.  " });
	result = sol.fullJustify(words, 16);
	assert(result.size() == compare.size());
	for (size_t i = 0; i < compare.size(); i++)
	{
		assert(result[i] == compare[i]);
	}

	words.assign({ "What", "must", "be", "acknowledgment", "shall", "be" });
	compare.assign({ "What   must   be", "acknowledgment  ", "shall be        " });
	result = sol.fullJustify(words, 16);
	assert(result.size() == compare.size());
	for (size_t i = 0; i < compare.size(); i++)
	{
		assert(result[i] == compare[i]);
	}

	words.assign({ "Science", "is", "what", "we", "understand", "well", "enough", "to", "explain",
		"to", "a", "computer.", "Art", "is", "everything", "else", "we", "do" });
	compare.assign({ "Science  is  what we", "understand      well", "enough to explain to", "a  computer.  Art is", "everything  else  we", "do                  " });
	result = sol.fullJustify(words, 20);
	assert(result.size() == compare.size());
	for (size_t i = 0; i < compare.size(); i++)
	{
		assert(result[i] == compare[i]);
	}
}