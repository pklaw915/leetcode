#include <algorithm>
#include <vector>
#include <string>
#include <stack>
#include <assert.h>
#include <stdlib.h>
using namespace std;

#include "utils/structs.h"

class Solution0145 {
public:
	vector<int> postorderTraversal(TreeNode* root) {
		vector<int> vals;
		stack<TreeNode*> st;
		if (root)
			st.push(root);
		while (!st.empty())
		{
			bool bChild = true;
			if (st.top() == nullptr)
			{
				bChild = false;
				st.pop();
			}

			auto p = st.top();
			if (bChild && (p->left || p->right))
			{
				st.push(nullptr);
				if (p->right)
					st.push(p->right);
				if (p->left)
					st.push(p->left);
			}
			else
			{
				vals.push_back(p->val);
				st.pop();
			}
		}
		return vals;
	}
};

void test0145_postorderTraversal()
{

}