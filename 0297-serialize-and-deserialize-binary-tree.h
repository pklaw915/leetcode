#include <algorithm>
#include <vector>
#include <string>
#include <assert.h>
#include <stdlib.h>
using namespace std;

#include "utils/structs.h"

class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode* root) {
		string str = "[";
		serialize(root, str, false);
		str += "]";
		return str;
	}

	// Decodes your encoded data to tree.
	TreeNode* deserialize(string data) {
		string val;
		const char* ps = data.c_str();
		ps = next(ps, val);
		TreeNode* root = deserialize(ps, val);
		assert(strcmp(ps, "]") == 0);
		return root;
	}

private:
	void serialize(TreeNode* p, string& str, bool bSep) const
	{
		if (bSep)
			str += ",";
		if (p == nullptr)
		{
			str += "null";
		}
		else
		{
			char buf[15];
			sprintf(buf, "%d", p->val);
			str += buf;
			serialize(p->left, str, true);
			serialize(p->right, str, true);
		}
	}

	TreeNode* deserialize(const char* &ps, string& val) const
	{
		ps = next(ps, val);
		if (strcmp(val.c_str(), "null") == 0)
			return nullptr;

		int nVal = atoi(val.c_str());
		TreeNode* p = new TreeNode(nVal);
		p->left = deserialize(ps, val);
		p->right = deserialize(ps, val);
		return p;
	}

	const char* next(const char* ps, string& word) const
	{
		if (*ps == '[')
		{
			word = "[";
			++ps;
		}
		else if (*ps == ']')
		{
			word = "]";
			++ps;
		}
		else
		{
			int n = 0;
			while (ps[n])
			{
				if (ps[n] == '[' || ps[n] == ']' || ps[n] == ',')
					break;
				++n;
			}
			word.assign(ps, ps + n);
			ps += n;
		}

		while (*ps == ',')
			++ps;
		return ps;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec codec;
// codec.deserialize(codec.serialize(root));